#include "Vofa.h"
#include "usart.h"
#include "Vofa_STM32G474.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


// 添加函数声明
static void parse_command_directly(uint8_t* data, uint16_t length);

extern UART_HandleTypeDef hlpuart1;

// 接收通道数据存储
static volatile float received_channel_data[RX_CHANNEL_COUNT] = {0};

// 串口接收双缓冲
uint8_t rx_buffer[2][RX_BUFFER_SIZE];
volatile uint8_t active_buffer = 0;

// DMA传输状态
static volatile uint8_t dma_tx_complete = 1;

// 优化的浮点数解析函数
static float fast_atof(const uint8_t *str, uint16_t len)
{
    float value = 0.0f;
    float decimal_factor = 0.1f;
    uint8_t decimal_flag = 0;
    uint8_t negative = 0;

    for (uint16_t i = 0; i < len; i++) {
        uint8_t c = str[i];

        if (c == '-') {
            negative = 1;
        } else if (c == '.') {
            decimal_flag = 1;
        } else if (c >= '0' && c <= '9') {
            if (decimal_flag) {
                value += (c - '0') * decimal_factor;
                decimal_factor *= 0.1f;
            } else {
                value = value * 10.0f + (c - '0');
            }
        } else if (c == ' ' || c == '\t' || c == '\r' || c == '\n') {
            // 跳过空白字符
        } else {
            // 遇到非法字符，提前退出
            break;
        }
    }

    return negative ? -value : value;
}

void Vofa_SendDataCallBack(Vofa_HandleTypedef* handle, uint8_t* data, uint16_t length)
{
    (void)handle;
    // 等待之前的传输完成
    while (!dma_tx_complete) {}
    dma_tx_complete = 0;
    HAL_UART_Transmit_DMA(&hlpuart1, data, length);
}

// 添加UART发送完成回调函数
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart == &hlpuart1) {
        dma_tx_complete = 1;
    }
}

void set_received_channel_data(uint8_t channel, float value)
{
    if (channel < RX_CHANNEL_COUNT) {
        received_channel_data[channel] = value;
    }
}

float get_received_channel_data(uint8_t channel)
{
    if (channel < RX_CHANNEL_COUNT) {
        return received_channel_data[channel];
    }
    return 0.0f;
}

// 初始化VOFA接收功能
void Vofa_STM32G474_Init(void)
{
    // 清空缓冲区
    memset(rx_buffer[0], 0, RX_BUFFER_SIZE);
    memset(rx_buffer[1], 0, RX_BUFFER_SIZE);

    // 启动双缓冲DMA接收
    HAL_UARTEx_ReceiveToIdle_DMA(&hlpuart1,
                                 rx_buffer[active_buffer],
                                 RX_BUFFER_SIZE);
    // 禁用DMA半传输中断
    __HAL_DMA_DISABLE_IT(hlpuart1.hdmarx, DMA_IT_HT);
}

// 接收完成回调函数
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
    if (huart->Instance != LPUART1) return;

    // 智能数据结束检测
    uint8_t processed_buffer = active_buffer;
    uint16_t actual_size = Size;
    
    // 检查数据是否包含结束符
    uint8_t has_terminator = 0;
    for (uint16_t i = 0; i < Size; i++) {
        uint8_t c = rx_buffer[processed_buffer][i];
        if (c == ';' || c == '\r' || c == '\n' || c == '\0') {
            has_terminator = 1;
            break;
        }
    }
    
    // 如果数据不包含结束符，可能是DMA超时中断，需要特殊处理
    if (!has_terminator && Size > 0) {
        // 检查是否是有效的命令格式
        uint8_t valid_command = 0;
        for (uint16_t i = 0; i < Size - 3; i++) {
            if (rx_buffer[processed_buffer][i] == 'c' && 
                rx_buffer[processed_buffer][i+1] == 'h' && 
                isdigit(rx_buffer[processed_buffer][i+2]) &&
                rx_buffer[processed_buffer][i+3] == '=') {
                valid_command = 1;
                break;
            }
        }
        
        if (valid_command) {
            // 有效命令但没有结束符，手动添加结束符
            if (Size < RX_BUFFER_SIZE - 1) {
                rx_buffer[processed_buffer][Size] = ';';
                rx_buffer[processed_buffer][Size + 1] = '\0';
                actual_size = Size + 1;
            } else {
                rx_buffer[processed_buffer][RX_BUFFER_SIZE - 2] = ';';
                rx_buffer[processed_buffer][RX_BUFFER_SIZE - 1] = '\0';
                actual_size = RX_BUFFER_SIZE - 1;
            }
        } else {
            // 无效数据，直接丢弃
            actual_size = 0;
        }
    } else {
        // 正常数据，确保以null结尾
        if (Size < RX_BUFFER_SIZE) {
            rx_buffer[processed_buffer][Size] = '\0';
        } else {
            rx_buffer[processed_buffer][RX_BUFFER_SIZE - 1] = '\0';
            actual_size = RX_BUFFER_SIZE - 1;
        }
    }

    // 切换到下一个缓冲区
    active_buffer = 1 - active_buffer;

    // 重新启动接收
    HAL_UARTEx_ReceiveToIdle_DMA(huart,
                                 rx_buffer[active_buffer],
                                 RX_BUFFER_SIZE);

    // 处理接收到的数据（只有有效数据才处理）
    if (actual_size > 0) {
        parse_command_directly(rx_buffer[processed_buffer], actual_size);
    }
}

static void parse_command_directly(uint8_t* data, uint16_t length)
{
    uint16_t index = 0;
    uint8_t state = 0; // 0: 等待命令, 1: 在通道号中, 2: 在值中
    uint8_t channel = 0;
    uint16_t value_start = 0;

    for (index = 0; index < length; index++) {
        uint8_t c = data[index];
        
        switch (state) {
            case 0: // 等待'c'
                if (c == 'c') {
                    state = 1;
                }
                break;
                
            case 1: // 期待'h'
                if (c == 'h') {
                    state = 2;
                } else {
                    state = 0;
                }
                break;
                
            case 2: // 期待数字
                if (isdigit(c)) {
                    channel = c - '0';
                    state = 3;
                } else {
                    state = 0;
                }
                break;
                
            case 3: // 期待'='
                if (c == '=') {
                    state = 4;
                    value_start = index + 1;
                } else {
                    state = 0;
                }
                break;

            case 4: // 在值中
                // 检查终止条件
                if (c == ';' || c == '\r' || c == '\n' || c == '\0') {
                    // 提取值
                    if (value_start < index) {
                        float value = fast_atof(&data[value_start], index - value_start);
                        set_received_channel_data(channel, value);
                    }
                    state = 0; // 重置状态
                }
                // 优化的前瞻检测 - 只在明确的多命令情况下使用
                else if (index + 3 < length &&
                         c == 'c' &&
                         data[index+1] == 'h' &&
                         isdigit(data[index+2]) &&
                         data[index+3] == '=') {
                    
                    // 检查当前值是否已经处理到合理长度
                    // 如果当前值长度过短，可能是误检测，继续处理当前值
                    if (index - value_start < 3) {
                        // 当前值太短，可能是误检测，继续处理当前值
                        break;
                    }
                    
                    // 检查当前值是否包含有效数字内容
                    uint8_t has_digits = 0;
                    for (uint16_t i = value_start; i < index; i++) {
                        if (isdigit(data[i]) || data[i] == '.' || data[i] == '-') {
                            has_digits = 1;
                            break;
                        }
                    }
                    
                    if (!has_digits) {
                        // 当前值没有有效数字内容，可能是误检测，继续处理当前值
                        break;
                    }

                    // 提取下一个命令的通道号
                    uint8_t next_channel = data[index+2] - '0';

                    // 保存当前值
                    if (value_start < index) {
                        float value = fast_atof(&data[value_start], index - value_start);
                        set_received_channel_data(channel, value);
                    }
                    
                    // 准备处理新命令
                    state = 1; // 回到状态1，准备处理新的"ch"
                    // 注意：这里不需要index--，因为下一个字符就是'c'
                }
                break;
        }
    }

    // 处理最后一个值（如果需要）
    if (state == 4 && value_start < length) {
        float value = fast_atof(&data[value_start], length - value_start);
        set_received_channel_data(channel, value);
    }
}
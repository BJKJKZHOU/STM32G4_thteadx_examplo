#ifndef VOFA_STM32G474_H
#define VOFA_STM32G474_H

#include "Vofa.h"
#include "stm32g4xx_hal.h"

// 定义接收通道枚举
enum ReceiveChannels {
    RX_CH0 = 0,
    RX_CH1,
    RX_CH2,
    RX_CH3,
    RX_CHANNEL_COUNT
};

// 定义数据通道枚举
enum DataChannels {
    CH_TEST_DATA1 = 0,    // 测试数据1 (对应上位机通道0)
    CH_TEST_DATA2,        // 测试数据2 (对应上位机通道1)
    CH_TEST_DATA3,        // 测试数据3 (对应上位机通道2)
    CH_RECEIVED_CH0,      // 接收到的通道0数据 (对应上位机通道3)
    CH_RECEIVED_CH1,      // 接收到的通道1数据 (对应上位机通道4)
    CH_CHANNEL_COUNT      // 通道总数
};

// 添加外部声明
#define RX_BUFFER_SIZE 256
extern uint8_t rx_buffer[2][RX_BUFFER_SIZE];  // 双缓冲
extern volatile uint8_t active_buffer;    // 当前活动缓冲区



void Vofa_STM32G474_Init(void);
float get_received_channel_data(uint8_t channel);
void set_received_channel_data(uint8_t channel, float value);
void Vofa_ProcessReceivedData(Vofa_HandleTypedef* handle);
void Vofa_UART_IdleCallback(UART_HandleTypeDef *huart);  // 添加声明
void Vofa_SendMixedData(Vofa_HandleTypedef* handle, const float *floatData, uint8_t floatCount, const char *text);
#endif // VOFA_STM32G474_H
#ifndef VOFA_STM32G474_H
#define VOFA_STM32G474_H

#include "Vofa.h"
#include "stm32g4xx_hal.h"

// 双缓冲接收配置
#define RX_BUFFER_SIZE 256
extern uint8_t rx_buffer[2][RX_BUFFER_SIZE]; // 双缓冲
extern volatile uint8_t active_buffer;       // 当前活动缓冲区索引
extern volatile uint16_t rx_data_length[2];  // 两个缓冲区的数据长度

void Vofa_STM32G474_Init(void);
void Vofa_UART_IdleCallback(UART_HandleTypeDef *huart);

// 获取接收到的原始数据（双缓冲版本）
uint16_t Vofa_GetReceivedData(uint8_t *buffer, uint16_t max_length);

// 自定义协议解析函数
void Vofa_ParseCustomProtocol(uint8_t *data, uint16_t length);

/* void Vofa_SendMixedData(Vofa_HandleTypedef* handle, const float *floatData, uint8_t floatCount, const char *text); */
#endif // VOFA_STM32G474_H
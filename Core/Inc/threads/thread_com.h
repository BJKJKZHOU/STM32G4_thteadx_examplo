/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    thread_com.h
  * @author  MCD Application Team
  * @brief   VOFA通讯线程头文件
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2020-2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

#ifndef __THREAD_COM_H
#define __THREAD_COM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "tx_api.h"
#include "Vofa.h"
#include "tim.h"
#include "usart.h"
#include "stdint.h"

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* VOFA线程参数结构体 */
typedef struct
{
    float motor_speed;      /* 电机转速 RPM */
    float motor_current;    /* 电机电流 A */
    float motor_position;   /* 电机位置 度 */
    float motor_temperature;/* 电机温度 ℃ */
} Vofa_Thread_Params_t;

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* VOFA线程配置 */
#define VOFA_THREAD_STACK_SIZE     1024
#define VOFA_THREAD_PRIORITY       10
#define VOFA_THREAD_PREEMPTION_THRESHOLD 10
#define VOFA_THREAD_TIME_SLICE     TX_NO_TIME_SLICE
#define VOFA_THREAD_AUTO_START     TX_AUTO_START

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
/* USER CODE BEGIN EFP */

/**
  * @brief  VOFA通讯线程入口函数
  * @param  thread_input: 线程输入参数
  * @retval None
  */
void vofa_thread_entry(ULONG thread_input);

/**
  * @brief  创建VOFA通讯线程
  * @param  byte_pool: 内存池指针
  * @retval TX_SUCCESS: 成功, 其他: 失败
  */
UINT vofa_thread_create(TX_BYTE_POOL *byte_pool);

/**
  * @brief  创建TIM2信号量
  * @retval TX_SUCCESS: 成功, 其他: 失败
  */
UINT vofa_tim2_semaphore_create(void);

/* USER CODE END EFP */

#ifdef __cplusplus
}
#endif

#endif /* __THREAD_COM_H */
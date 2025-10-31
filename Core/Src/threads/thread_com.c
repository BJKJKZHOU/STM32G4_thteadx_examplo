/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    thread_com.c
 * @author  MCD Application Team
 * @brief   VOFA通讯线程实现文件
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

/* Includes ------------------------------------------------------------------*/
#include "thread_com.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Vofa.h"
#include "Vofa_STM32G474.h"
#include <string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* 外部变量声明 */
extern TIM_HandleTypeDef htim2;

/* VOFA通讯线程 */
TX_THREAD vofa_thread;

/* TIM2信号量 */
TX_SEMAPHORE tx_tim2_semaphore;

/* 接收数据缓冲区 */
static uint8_t rx_data_buffer[256];

/* 电机控制参数 */
static float motor_speed_ref = 0.0f;      // 速度参考值
static float motor_torque_ref = 0.0f;     // 转矩参考值
static float motor_current_limit = 10.0f; // 电流限制

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Exported functions --------------------------------------------------------*/

/**
 * @brief  VOFA通讯线程入口函数
 * @param  thread_input: 线程输入参数
 * @retval None
 */
void vofa_thread_entry(ULONG thread_input)
{
  /* USER CODE BEGIN vofa_thread_entry */

  Vofa_HandleTypedef vofa_handle;
  float motor_data[4]; // 电机数据数组：速度、电流、位置、温度
  UINT status;

  // 初始化VOFA
  Vofa_Init(&vofa_handle, VOFA_MODE_SKIP);

  // 初始化通道名称（设置有意义的中文名称）
  Vofa_SetChannelName(RECEIVING_CHANNEL_1, "速度参考");
  Vofa_SetChannelName(RECEIVING_CHANNEL_2, "转矩参考");
  Vofa_SetChannelName(RECEIVING_CHANNEL_3, "电流限制");
  Vofa_SetChannelName(RECEIVING_CHANNEL_4, "位置参考");
  Vofa_SetChannelName(RECEIVING_CHANNEL_5, "温度保护");

  // 启动TIM2定时器（如果尚未启动）
  HAL_TIM_Base_Start_IT(&htim2);

  // 无限循环，每次中断触发执行一次数据发送和接收处理
  while (1)
  {
    // 等待TIM2信号量（超时时间设置为TX_WAIT_FOREVER）
    status = tx_semaphore_get(&tx_tim2_semaphore, TX_WAIT_FOREVER);

    if (status == TX_SUCCESS)
    {
      // 步骤1：处理接收数据
      uint16_t received_length = Vofa_GetReceivedData(rx_data_buffer, sizeof(rx_data_buffer));
      if (received_length > 0)
      {
        // 解析接收到的自定义协议数据
        Vofa_ParseCustomProtocol(rx_data_buffer, received_length);

        // 更新电机控制参数
        motor_speed_ref = Vofa_GetChannelData(RECEIVING_CHANNEL_1);     // 速度参考
        motor_torque_ref = Vofa_GetChannelData(RECEIVING_CHANNEL_2);    // 转矩参考
        motor_current_limit = Vofa_GetChannelData(RECEIVING_CHANNEL_3); // 电流限制
      }

      // 步骤2：获取电机数据（这里需要根据实际应用填充数据）
      // 示例数据：速度、电流、位置、温度
      motor_data[0] = motor_speed_ref;     // 电机转速参考值
      motor_data[1] = motor_torque_ref;    // 电机转矩参考值
      motor_data[2] = motor_current_limit; // 电机电流限制
      motor_data[3] = 65.0f;               // 电机温度 ℃

      // 步骤3：通过VOFA发送JustFloat格式数据
      Vofa_JustFloat(&vofa_handle, motor_data, 4);

      // 数据发送完成，线程自动挂起等待下一次中断
      // 不需要额外的延时或循环，ThreadX会自动调度
    }
    else if (status == TX_DELETED)
    {
      // 信号量被删除，退出线程
      break;
    }
  }

  // 线程退出前的清理工作
  HAL_TIM_Base_Stop_IT(&htim2); // 停止TIM2定时器

  /* USER CODE END vofa_thread_entry */
}

/**
 * @brief  创建VOFA通讯线程
 * @param  byte_pool: 内存池指针
 * @retval TX_SUCCESS: 成功, 其他: 失败
 */
UINT vofa_thread_create(TX_BYTE_POOL *byte_pool)
{
  UINT ret = TX_SUCCESS;
  CHAR *pointer;

  /* USER CODE BEGIN vofa_thread_create */

  // 分配线程栈空间
  if (tx_byte_allocate(byte_pool, (VOID **)&pointer,
                       VOFA_THREAD_STACK_SIZE, TX_NO_WAIT) != TX_SUCCESS)
  {
    return TX_POOL_ERROR;
  }

  // 创建VOFA通讯线程
  if (tx_thread_create(&vofa_thread, "VOFA Thread", vofa_thread_entry, 0, pointer,
                       VOFA_THREAD_STACK_SIZE, VOFA_THREAD_PRIORITY,
                       VOFA_THREAD_PREEMPTION_THRESHOLD, VOFA_THREAD_TIME_SLICE,
                       VOFA_THREAD_AUTO_START) != TX_SUCCESS)
  {
    return TX_THREAD_ERROR;
  }

  /* USER CODE END vofa_thread_create */

  return ret;
}

/**
 * @brief  创建TIM2信号量
 * @retval TX_SUCCESS: 成功, 其他: 失败
 */
UINT vofa_tim2_semaphore_create(void)
{
  UINT ret;

  /* USER CODE BEGIN vofa_tim2_semaphore_create */

  /* 创建TIM2信号量，初始计数为0 */
  ret = tx_semaphore_create(&tx_tim2_semaphore, "TIM2 Semaphore", 0);

  /* USER CODE END vofa_tim2_semaphore_create */

  return ret;
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
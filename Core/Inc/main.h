/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.h
 * @brief          : Header for main.c file.
 *                   This file contains the common defines of the application.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32c0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
  typedef struct
  {
    uint8_t button; // IN1 PA1
    float MCU_Temperature;
    float MCU_Vref;
    float MCU_VDD;
    float MCU_VSS;
    float current_MOS; // IN17  PB0
    float voltage_MOS; // IN18  PB1
  } ADCData;

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_Alarm_Pin GPIO_PIN_14
#define LED_Alarm_GPIO_Port GPIOC
#define L_LED_Pin GPIO_PIN_0
#define L_LED_GPIO_Port GPIOA
#define LED_Proc1_Pin GPIO_PIN_3
#define LED_Proc1_GPIO_Port GPIOA
#define LED_Proc2_Pin GPIO_PIN_4
#define LED_Proc2_GPIO_Port GPIOA
#define LED_Proc3_Pin GPIO_PIN_5
#define LED_Proc3_GPIO_Port GPIOA
#define LED_Proc4_Pin GPIO_PIN_6
#define LED_Proc4_GPIO_Port GPIOA
#define LED_Proc5_Pin GPIO_PIN_7
#define LED_Proc5_GPIO_Port GPIOA
#define H_LED_Pin GPIO_PIN_15
#define H_LED_GPIO_Port GPIOA
#define LED_Normal_Pin GPIO_PIN_6
#define LED_Normal_GPIO_Port GPIOB
#define PluginCheck_Pin GPIO_PIN_7
#define PluginCheck_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
#define ADC_BUFFER_SIZE 77
#define SELECT_FREQ 109000

  /* Exported variables --------------------------------------------------------*/
  extern volatile uint16_t adcBuffer[ADC_BUFFER_SIZE];
  extern volatile float ADC_Value[ADC_BUFFER_SIZE]; // ???????ADC????
  extern ADCData adcData;
  extern uint32_t last_interrupt_tick;
  extern uint32_t pulse_cnt;

  // 主状态机枚举
typedef enum {
    NEB_STATE_IDLE,        // 无信号状�?
    NEB_STATE_NEB
} NebState;

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

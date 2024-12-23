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
#include "stm32g0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
  typedef struct
  {

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
#define LED_15mins_Pin GPIO_PIN_14
#define LED_15mins_GPIO_Port GPIOC
#define PWM_Output_Pin GPIO_PIN_0
#define PWM_Output_GPIO_Port GPIOA
#define PWM_Capture_Pin GPIO_PIN_1
#define PWM_Capture_GPIO_Port GPIOA
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
#define ADC_Voltage_Pin GPIO_PIN_0
#define ADC_Voltage_GPIO_Port GPIOB
#define ADC_Current_Pin GPIO_PIN_1
#define ADC_Current_GPIO_Port GPIOB
#define PWM_Generate_Pin GPIO_PIN_8
#define PWM_Generate_GPIO_Port GPIOA
#define LED_30mins_Pin GPIO_PIN_15
#define LED_30mins_GPIO_Port GPIOA
#define LED_Normal_Pin GPIO_PIN_6
#define LED_Normal_GPIO_Port GPIOB
#define LED_Alarm_Pin GPIO_PIN_7
#define LED_Alarm_GPIO_Port GPIOB
#define PlugInCheck_Pin GPIO_PIN_8
#define PlugInCheck_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
#define ADC_BUFFER_SIZE 22

  /* Exported variables --------------------------------------------------------*/
  extern volatile uint16_t adcBuffer[ADC_BUFFER_SIZE];
  extern volatile float ADC_Value[ADC_BUFFER_SIZE];
  extern ADCData adcData;
  extern uint32_t last_interrupt_tick;
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

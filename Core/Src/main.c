/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "sweep_freq.h"
#include "func.h"
#include "median_average_filtering.h"
#include "adc_calc.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define ENABLE_BUTTON 0 // 1 启用功能, 0 禁用功能
#define WEIGHTED_MOVING_AVERAGE_FILTER 0

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
ADCData adcData = {0};

volatile uint16_t adcBuffer[ADC_BUFFER_SIZE];
volatile float ADC_Value[ADC_BUFFER_SIZE]; // 声明数组来存储ADC采样结果
uint16_t filtered_adc_values[7];           // 过滤后的ADC
uint16_t filtered_voltage[7];              // 过滤后的电压
uint32_t last_interrupt_tick = 0;
uint32_t pulse_cnt = 0; // 在TIM3CH3中断中计数，通过main查询不同的�?�，做不同的操作
uint32_t starttime, endtime = 0;
uint32_t lastpulsetime = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_TIM1_Init();
  MX_TIM3_Init();
  MX_TIM14_Init();
  MX_TIM16_Init();
  MX_TIM17_Init();
  /* USER CODE BEGIN 2 */

  if (HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adcBuffer, ADC_BUFFER_SIZE) != HAL_OK)
  {
    Error_Handler();
  }

  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
  HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_3);

  HAL_TIM_Base_Start_IT(&htim14); // 启动TIM14的定时器中断
  HAL_TIM_Base_Start_IT(&htim16); // 启动TIM16的定时器中断
  HAL_TIM_Base_Start_IT(&htim17); // 启动TIM17的定时器中断

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  //  sweepFreq();
  NebState currentState = NEB_STATE_IDLE;
  // 扫频完成后，设置TIM1为最佳频�??

  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    uint16_t pr;
    CheckSignalTimeout();

    switch (currentState)
    {
    case NEB_STATE_IDLE:
      // 停止雾化逻辑
      Handle_Unknown_Signal();
      if (pulse_cnt == 1)
      {
        starttime = HAL_GetTick();
      }
      else if (pulse_cnt == 10)
      {
        endtime = HAL_GetTick();
        // 计算周期
        pr = endtime - starttime;
        if (pr > 900 && pr < 1100)
        {
          // 8hz喷雾设置

          // 切换状�??
          currentState = NEB_STATE_NEB;
        }
        else if (pr > 1900 && pr < 2100)
        {
          // 4hz喷雾设置

          // 切换状�??
          currentState = NEB_STATE_NEB;
        }
        else
        {
          // 不正常情�?
        }
        // 清除cnt
        pulse_cnt = 0;
      }
      break;

    case NEB_STATE_NEB:
      // 执行喷雾
      startNeb();
      // 持续�?测周期，并判断停止或通讯错误
      if (pulse_cnt > 0)
      {
        // 仍有收到上升沿，更新最后一次上升沿的时间
        lastpulsetime = HAL_GetTick();
        // 通过计算周期的范围，判断通讯信号是否正常
        if (pulse_cnt == 1)
        {
          starttime = HAL_GetTick();
        }
        else if (pulse_cnt == 10)
        {
          endtime = HAL_GetTick();
          // 清除cnt
          pulse_cnt = 0;
          // 计算周期
          pr = endtime - starttime;
          // 判断周期是否在合理范围内
          if (pr < 900 && pr > 2100)
          {
            // 通讯信号出错
            Handle_Unknown_Signal();
            // 切换状态
            currentState = NEB_STATE_IDLE;
          }
        }
      }
      else
      {
        // 不再收到上升沿
        // 判断是否达到无上升沿的时间上限
        if ((HAL_GetTick() - lastpulsetime) > 800) // 已经过800ms未收到上升沿
        {
          // 已结束，停止喷雾
          Handle_Unknown_Signal();
          // 切换状态
          currentState = NEB_STATE_IDLE;
        }
      }

      break;
    default:
      currentState = NEB_STATE_IDLE;
      break;
    }
  }
  /* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
   * in the RCC_OscInitTypeDef structure.
   */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
   */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

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

#define ADC_BUFFER_SIZE 77
#define START_FREQ 108000    // 起始频率 108kHz
#define END_FREQ 132000      // 结束频率 132kHz
#define STEP_FREQ 500        // 步进频率 0.5kHz，即 500Hz
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint16_t adcBuffer[ADC_BUFFER_SIZE];
volatile uint16_t ADC_Value[ADC_BUFFER_SIZE]; // 声明数组来存储ADC采样结果
uint16_t filtered_adc_values[7]; // 过滤后的ADC
uint16_t filtered_voltage[7];     // 过滤后的电压


float voltage = 0.0f, current = 0.0f, power = 0.0f;  // 电压、电流�?�功�?
float max_power = 0.0f;  // �?大功�?
uint32_t best_freq = START_FREQ;  // �?佳频�?
uint32_t freq = 130000;
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
    if (HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adcBuffer, ADC_BUFFER_SIZE) != HAL_OK)
    {
      Error_Handler();
    }

  //HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
  HAL_TIM_Base_Start_IT(&htim14); // 启动TIM14的定时器中断
  HAL_TIM_Base_Start_IT(&htim16); // 启动TIM16的定时器中断
  HAL_TIM_Base_Start_IT(&htim17); // 启动TIM17的定时器中断
    
    
    
//        for (uint32_t freq = START_FREQ; freq <= END_FREQ; freq += STEP_FREQ)
//    {
//        // 设置PWM频率
//        __HAL_TIM_SET_AUTORELOAD(&htim2, (SystemCoreClock / (2 * freq)) - 1);
//        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, (SystemCoreClock / (4 * freq))); // 50% 占空�? 
//        // 启动PWM 
//        HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1); 
//        // 延迟�?段时间，让系统稳�?
//        HAL_Delay(1000);                                                              // 例如延迟1�? 
//        // 读取电压和电�?
//        float voltage = readVoltage();
//        float current = readCurrent();                                                                                // 计算功率
//        float power = voltage * current;                                                                              // 打印结果
//        printf("Frequency: %d Hz, Voltage: %.2f V, Current: %.2f A, Power: %.2f W\n", freq, voltage, current, power); // 可以在这里添加更多数据采集和处理代码
//    } // 测试完成后，关闭PWM输出
//    HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1);
    
    
    
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
//   for (uint32_t freq = START_FREQ; freq <= END_FREQ; freq += STEP_FREQ)
//  {
//      // 设置PWM频率
//      __HAL_TIM_SET_AUTORELOAD(&htim1, (SystemCoreClock / freq) - 1);
//      __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, (SystemCoreClock / (2 * freq))); // 50% 占空�?
//      HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);

//      HAL_Delay(500); // 延迟，确保系统稳�?

//      // 读取电压和电流（假设IN17和IN18分别是电压和电流通道�?
//      voltage = (adcBuffer[0] * 3.3f) / 4095.0f;  // IN17电压
//      current = (adcBuffer[1] * 3.3f) / 4095.0f;  // IN18电流

//      power = voltage * current; // 计算功率

//      // 判断�?大功�?
//      if (power > max_power)
//      {
//          max_power = power;
//          best_freq = freq;
//      }
//  }

//  // 扫频完成后，设置TIM1为最佳频�?
//  __HAL_TIM_SET_AUTORELOAD(&htim1, (SystemCoreClock / best_freq) - 1);
//  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, (SystemCoreClock / (2 * best_freq))); // 50% 占空�?
//  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);

  __HAL_TIM_SET_AUTORELOAD(&htim1, (SystemCoreClock / freq) - 1);
  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, (SystemCoreClock / (2 * freq))); // 50% 占空�?
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);

  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

      for (int i = 0; i < ADC_BUFFER_SIZE; i++) 
      {
        ADC_Value[i] = (adcBuffer[i] * 3.3f) / 4095.0f;
    }
      
//    for (int channel = 0; channel < 7; channel++)
//    {
//      // 选择当前通道的数�??
//      uint16_t *channel_data = (uint16_t *)&ADC_Value[channel * 11]; // 每个通道11个�??
//      filtered_adc_values[channel] = MedianAverageFilter(channel_data, 11);
//      // 然后将过滤后的ADC值转换为电压
//      for (int i = 0; i < 7; i++)
//      {
//        filtered_voltage[i] = ADC_To_Voltage(filtered_adc_values[i]);
//      }
//    }

    //    HAL_GPIO_WritePin(LED_Alarm_GPIO_Port, LED_Alarm_Pin, GPIO_PIN_RESET);
    //    HAL_GPIO_WritePin(LED_Normal_GPIO_Port, LED_Normal_Pin, GPIO_PIN_SET);
    //    HAL_Delay(500);
    //    HAL_GPIO_WritePin(LED_Alarm_GPIO_Port, LED_Alarm_Pin, GPIO_PIN_SET);
    //    HAL_GPIO_WritePin(LED_Normal_GPIO_Port, LED_Normal_Pin, GPIO_PIN_RESET);
    //    HAL_Delay(500);

    // if (HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK)
    // {
    //   uint32_t adcValue = HAL_ADC_GetValue(&hadc1);
    // }
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
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
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

#ifdef  USE_FULL_ASSERT
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

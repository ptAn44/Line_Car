/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <control_motor_line.h>

PID_parameter PID_set_parameters = {.Kp =40,.Ki=0.0001,.Kd=25,.Ts = 0.005,.PID_Saturation = 180
																			,.error =0,.pre_error =0,.pre2_error=0,.pre_Out =0,.Out = 0};

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef enum{
	STOP_CONTROL=0,
	LINE_CAPTURE,
	CONTROL_BY_HAND,
}mode_t;				

typedef enum{
	HC05_WAIT_START=0,
	HC05_APP,
}HC05_t;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
mode_t mode_status = STOP_CONTROL;
HC05_t HC05_status = HC05_WAIT_START;

uint8_t Rx_buff[4];
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance==htim3.Instance)
	{
		if(mode_status == LINE_CAPTURE)
		{
			Sensor_CalculateSumValue();
			Control_CalculateValuePosition(Sensor_ReadSumValue());
			PID_PROCESS(&PID_set_parameters,Control_ReadValuePosition(),0);
			Control_SetMotorLine(PID_ReadValue(&PID_set_parameters),Control_ReadValuePosition());
			Sensor_ResetSumValue();
	  }
		else if (mode_status==CONTROL_BY_HAND)
		{
			Control_MotorByHand(Rx_buff[0]);
		}
		else if (mode_status==STOP_CONTROL)
		{
			Motor_Set_Speed(MOTOR_0,0);
			Motor_Set_Speed(MOTOR_1,0);
		}
  }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance==huart1.Instance)
	{
		switch(HC05_status)
		{
			case HC05_WAIT_START:
			{
				if(Rx_buff[0]=='s'){
					HC05_status=HC05_APP;
					HAL_UART_Receive_DMA(&huart1,Rx_buff,1);
					break;
				}
				else if(Rx_buff[0] == '1')
				{
					HC05_status= HC05_WAIT_START;
					HAL_UART_Receive_DMA(&huart1,Rx_buff,1);
					break;
				}
			}
			case HC05_APP:
			{
				HAL_UART_Receive_DMA(&huart1,(uint8_t*)Rx_buff,1);
				if (Rx_buff[0] == 'f' || Rx_buff[0] == 'b' || Rx_buff[0] == 'r'||Rx_buff[0] == 'l'){
					mode_status = CONTROL_BY_HAND;
					HC05_status=HC05_APP;
					HAL_UART_Receive_DMA(&huart1,Rx_buff,1);
				}
				else if(Rx_buff[0] =='i'){
					mode_status = STOP_CONTROL;
				}
				else if(Rx_buff[0] =='d'){
					mode_status = LINE_CAPTURE;
					HC05_status=HC05_APP;
					HAL_UART_Receive_DMA(&huart1,Rx_buff,1);
				}
				else if(Rx_buff[0] == 'k' ){
					mode_status=CONTROL_BY_HAND;
					HC05_status=HC05_WAIT_START;
					HAL_UART_Receive_DMA(&huart1,Rx_buff,1);
				}
			}
		}
	}
}
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
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_USART1_UART_Init();
  MX_DMA_Init();
  /* USER CODE BEGIN 2 */
  Motor_Init();
	HAL_TIM_Base_Start_IT(&htim3);
	HAL_UART_Receive_DMA(&huart1,Rx_buff,1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

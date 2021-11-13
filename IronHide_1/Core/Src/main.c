/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ROBOTIN.h"
#include "IMAGES.h"
#include "max7219.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
uint8_t data;
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
float distance;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void sendDataSPI(uint8_t reg, uint8_t data);

void MAX72xx_putChar(char ch);

void MAX72xx_print(uint8_t* str);

float HCSR04_Read(void);


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
  MX_USART1_UART_Init();
  MX_SPI2_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  HAL_UART_Receive_IT(&huart1, &data, 1);
  MAX72xx_Init();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  //distance = HCSR04_Read();
//	  if(distance>20){
//		  Straight();
//		  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_SET);
//		  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_RESET);
//	  }
//	  else if(distance<20){
//		  TurnLeft();
//		  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_SET);
//		  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_RESET);
//		  HAL_Delay(300);
//	  }





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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void sendDataSPI(uint8_t reg, uint8_t data){
	//NSS -> LOW
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, RESET);
	//send address
	HAL_SPI_Transmit(&hspi2, (uint8_t*)&reg, 1, HAL_MAX_DELAY);
	while(HAL_SPI_GetState(&hspi2)!=HAL_SPI_STATE_READY);
	//send data
	HAL_SPI_Transmit(&hspi2, (uint8_t*)&data, 1, HAL_MAX_DELAY);
	while(HAL_SPI_GetState(&hspi2)!=HAL_SPI_STATE_READY);
	//NSS ->HIGH
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
}



void MAX72xx_print(uint8_t* str){
	while(*str){
		if(*str != ' '){
			for(uint8_t i = 0;i<8;i++){
				sendDataSPI(i+1, LETTERS[*str - 48][i]);
			}
		}
		else{//si el caracter es un espacio en blanco
			for(uint8_t i = 0;i<8;i++){
				sendDataSPI(i+1, 0x00);	//no se muestra nada
			}
		}
		str++;
		HAL_Delay(400);
	}
}
void MAX72xx_putChar(char ch){
	for(uint8_t i = 0;i<8;i++){
		MAX72xx_write(i+1,LETTERS[ch - 48][i]);
		//sendDataSPI(i+1, LETTERS[ch - 48][i]);
	}
}


float HCSR04_Read(void){
	/*local variables*/
	uint32_t capture[2];
	float diffCapture;
	float timeUs;
	float dist;
	uint32_t TIM2_CLK = SystemCoreClock/2;
	__HAL_TIM_SET_COUNTER(&htim2,0);					//reset CNT
	HAL_TIM_Base_Start(&htim2);							//start input capture
	/*generate pulse 10us*/
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);
	while(__HAL_TIM_GET_COUNTER(&htim2)<=10);			//10us
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET);
	//wait rising edge
	HAL_TIM_Base_Stop(&htim2);
	HAL_TIM_IC_Start(&htim2, TIM_CHANNEL_1);
	TIM2->SR =0 ;
	while(!(TIM2->SR & TIM_SR_CC1IF));
	TIM2->SR &=~ TIM_SR_CC1IF;
	capture[0] = TIM2->CCR1;
	/*wait falling edge*/
	while(!(TIM2->SR & TIM_SR_CC1IF));
	TIM2->SR &=~ TIM_SR_CC1IF;
	capture[1] = TIM2->CCR1;
	HAL_TIM_IC_Stop(&htim2, TIM_CHANNEL_1);
	/*calc diference*/
	if(capture[1] >= capture[0]){
		diffCapture = capture[1] - capture[0];
	}
	else{
		diffCapture = TIM2->ARR - capture[0] + capture[1];
	}
	/*se calcula el tiempo del ancho de pulso en us*/
	timeUs = (diffCapture * ((float)(TIM2->PSC + 1)/TIM2_CLK)) * 1000000;
	/*Se calcula la distancia*/
	dist = timeUs / 58;
	/*ser retorna el valor calculado*/
	if(dist>400){
		return 0.0;
	}
	else{
		return dist;
	}

}
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

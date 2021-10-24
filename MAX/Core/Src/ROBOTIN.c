/*
 * ROBOTIN.c
 *
 *  Created on: Oct 19, 2021
 *      Author: Lenovo
 */

#include "ROBOTIN.h"



extern uint8_t data;
extern UART_HandleTypeDef huart1;


extern const uint8_t LETTERS[][8];
extern const uint8_t NUMBERS[][8];
extern const uint8_t ICONS[][8] ;

extern void MAX72xx_putChar(char ch);

/**
 * @fn
 * @brief
 * @param []
 * @return none
 */
void TurnLeft(void){
	//M1
	HAL_GPIO_WritePin(GPIOE, IN11, HIGH);
	HAL_GPIO_WritePin(GPIOB, IN21, LOW);
	//M2
	HAL_GPIO_WritePin(GPIOE, IN42, HIGH);
	HAL_GPIO_WritePin(GPIOB, IN32, LOW);
	//M3
	HAL_GPIO_WritePin(GPIOE, IN12, HIGH);
	HAL_GPIO_WritePin(GPIOE, IN22, LOW);
	//M4
	HAL_GPIO_WritePin(GPIOB, IN31, LOW);
	HAL_GPIO_WritePin(GPIOE, IN41, HIGH);
	return;
}
 /**
 * @fn
 * @brief
 * @param []
 * @return none
 */
void TurnRight(void){
	//M1
	HAL_GPIO_WritePin(GPIOE, IN11, LOW);
	HAL_GPIO_WritePin(GPIOB, IN21, HIGH);
	//M2
	HAL_GPIO_WritePin(GPIOB, IN32, HIGH);
	HAL_GPIO_WritePin(GPIOE, IN42, LOW);
	//M3
	HAL_GPIO_WritePin(GPIOE, IN12, LOW);
	HAL_GPIO_WritePin(GPIOE, IN22, HIGH);
	//M4
	HAL_GPIO_WritePin(GPIOB, IN31, HIGH);
	HAL_GPIO_WritePin(GPIOE, IN41, LOW);
	return;
}
 /**
 * @fn
 * @brief
 * @param []
 * @return none
 */
void Straight(void){
	//M1
	HAL_GPIO_WritePin(GPIOE, IN11, HIGH);
	HAL_GPIO_WritePin(GPIOB, IN21, LOW);
	  //M2
	HAL_GPIO_WritePin(GPIOE, IN42, LOW);
	HAL_GPIO_WritePin(GPIOB, IN32, HIGH);
	  //M3
	HAL_GPIO_WritePin(GPIOE, IN12, LOW);
	HAL_GPIO_WritePin(GPIOE, IN22, HIGH);
	  //M4
	HAL_GPIO_WritePin(GPIOB, IN31, LOW);
	HAL_GPIO_WritePin(GPIOE, IN41, HIGH);
	return;
}
 /**
 * @fn
 * @brief
 * @param []
 * @return none
 */
void back(void){
	//M1
	HAL_GPIO_WritePin(GPIOE, IN11, LOW);
	HAL_GPIO_WritePin(GPIOB, IN21, HIGH);
	//M2
	HAL_GPIO_WritePin(GPIOE, IN42, HIGH);
	HAL_GPIO_WritePin(GPIOB, IN32, LOW);
	//M3
	HAL_GPIO_WritePin(GPIOE, IN12, HIGH);
	HAL_GPIO_WritePin(GPIOE, IN22, LOW);
	//M4
	HAL_GPIO_WritePin(GPIOB, IN31, HIGH);
	HAL_GPIO_WritePin(GPIOE, IN41, LOW);
	return;
}

/**
 * @fn
 * @brief
 * @param []
 * @return none
 */
void stopMotor(void){
	//M1
	HAL_GPIO_WritePin(GPIOE, IN11, LOW);
	HAL_GPIO_WritePin(GPIOB, IN21, LOW);
	//M2
	HAL_GPIO_WritePin(GPIOE, IN42, LOW);
	HAL_GPIO_WritePin(GPIOB, IN32, LOW);
	//M3
	HAL_GPIO_WritePin(GPIOE, IN12, LOW);
	HAL_GPIO_WritePin(GPIOE, IN22, LOW);
	//M4
	HAL_GPIO_WritePin(GPIOB, IN31, LOW);
	HAL_GPIO_WritePin(GPIOE, IN41, LOW);

	return;
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(data == 'W'){
		Straight();
	}
	else if(data == 'S'){
		back();
	}else if(data == 'A'){
		TurnLeft();
	}else if(data == 'D'){
		TurnRight();
	}
	else if(data == 'X'){
		stopMotor();
	}
	MAX72xx_putChar(data);
	HAL_UART_Receive_IT(&huart1, &data, 1);
	return;
}


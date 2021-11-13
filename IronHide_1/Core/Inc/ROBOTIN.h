/*
 * ROBOTIN.h
 *
 *  Created on: Oct 19, 2021
 *      Author: Lenovo
 */

#ifndef INC_ROBOTIN_H_
#define INC_ROBOTIN_H_

/**************INCLUDES***************************/
#include "stm32f4xx_hal.h"
#include "max7219.h"
/******************MACROS***********************/


#define HIGH 	GPIO_PIN_SET
#define LOW  	GPIO_PIN_RESET

//M1
#define IN11    GPIO_PIN_10
#define IN21    GPIO_PIN_14
//M2
#define IN32    GPIO_PIN_10
#define IN42    GPIO_PIN_15
//M3
#define IN12    GPIO_PIN_14
#define IN22    GPIO_PIN_13
//M4
#define IN31    GPIO_PIN_11
#define IN41    GPIO_PIN_7

/***********FUNCTION PROTOTYPE***********************/
/**
 * @fn  IronHide gira a la izquierda
 * @brief esta funcion se usa para que robot gire a la derecha
 * @param []
 * @return
 */
void TurnLeft(void);
 /**
 * @fn
 * @brief
 * @param []
 * @return none
 */
void TurnRight(void);
 /**
 * @fn
 * @brief
 * @param []
 * @return none
 */
void Straight(void);
 /**
 * @fn
 * @brief
 * @param []
 * @return none
 */
void back(void);

/**
 * @fn
 * @brief
 * @param []
 * @return none
 */
void stopMotor(void);


/**
 * @fn
 * @brief
 * @param []
 * @return none
 */
void IronHide_setImage(uint8_t icon);


#endif /* INC_ROBOTIN_H_ */

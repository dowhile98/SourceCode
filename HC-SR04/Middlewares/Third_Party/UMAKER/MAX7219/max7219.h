/*
 * max7912.h
 *
 *  Created on: 26 dic. 2020
 *      Author: Lenovo
 */

#ifndef THIRD_PARTY_UMAKER_MAX7219_MAX7219_H_
#define THIRD_PARTY_UMAKER_MAX7219_MAX7219_H_

/*************includes**************************/
#include "stm32f4xx_hal.h"				//cambiar de adecuerdo al mcu usado
#include "spi.h"

/************ MACRO DEFINES*******************************/
/*****************USER DEFINES***************************/
#define USE_SPI

#ifdef USE_SPI
#define MAX_SPI			hspi2		//cambiar de acuerdo al spi usado
#define MAX_CS_PORT		GPIOB		//Cambiar de acurdo al puerto del cs elegido
#define MAX_CS_PIN		GPIO_PIN_12	//cambiar de acuerdo al pin usado

#else
#define MAX_CS_PORT		GPIOA
#define MAX_CS_PIN		GPIO_PIN_1
#define MAX_DIN_PORT	GPIOA
#define MAX_DIN_PIN		GPIO_PIN_2
#define	MAX_CLK_PORT	GPIOA
#define MAX_CLK_PIN		GPIO_PIN_0
#endif /*NOT USE_SPI*/


/********************************************************/

//Intensity Register Format (Address (Hex) = 0xXA)
#define MAX72xx_INTENSITY_ADDR		0x0A
#define MAX72xx_INTENSITY_1_32		0x00
#define MAX72xx_INTENSITY_3_32		0x01
#define MAX72xx_INTENSITY_5_32		0x02
#define MAX72xx_INTENSITY_7_32		0x03
#define MAX72xx_INTENSITY_9_32		0x04
#define MAX72xx_INTENSITY_11_32		0x05
#define MAX72xx_INTENSITY_13_32		0x06
#define MAX72xx_INTENSITY_15_32		0x07
#define MAX72xx_INTENSITY_17_32		0x08
#define MAX72xx_INTENSITY_19_32		0x09
#define MAX72xx_INTENSITY_21_32		0x0A
#define MAX72xx_INTENSITY_23_32		0x0B
#define MAX72xx_INTENSITY_25_32		0x0C
#define MAX72xx_INTENSITY_27_32		0x0D
#define MAX72xx_INTENSITY_29_32		0x0E
#define MAX72xx_INTENSITY_31_32		0x0F

//Scan-Limit Register Format (Address (Hex) = 0xXB
#define MAX72xx_SCAN_ADDR			0x0B
#define MAX72xx_SCAN_DISP_D_0		0x00
#define MAX72xx_SCAN_DISP_D_0_1		0x01
#define MAX72xx_SCAN_DISP_D_0_2		0x02
#define MAX72xx_SCAN_DISP_D_0_3		0x03
#define MAX72xx_SCAN_DISP_D_0_4		0x04
#define MAX72xx_SCAN_DISP_D_0_5		0x05
#define MAX72xx_SCAN_DISP_D_0_6		0x06
#define MAX72xx_SCAN_DISP_D_0_7		0x07

//Shutdown Register Format (Address (Hex) = 0xXC)
#define MAX72xx_SHUTDOWN_ADDR		0x0C
#define MAX72xx_SHUTDOWN_MODE		0x00
#define MAX72xx_SHUTDOWN_NORMAL_MODE	0x01

// Decode-Mode Register Examples (Address (Hex) = 0xX9)
#define MAX72xx_DECODE_ADDR			0x09

//Display-Test Register Format (Address (Hex) = 0xXF)
#define MAX72xx_TEST_ADDR			0x0F
#define MAX72xx_TEST_NORMAL_M		0x00
#define MAX72xx_TEST_MODE			0x01


/***************DEFINITION OF PROTOTYPE OF FUNCTIONS*********************/

void MAX72xx_Init(void);
void MAX72xx_putChar(char ch);
void MAX72xx_write(uint8_t reg, uint8_t data);




#endif /* THIRD_PARTY_UMAKER_MAX7219_MAX7219_H_ */

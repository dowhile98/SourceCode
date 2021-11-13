/*
 * max7912.c
 *
 *  Created on: 26 dic. 2020
 *      Author: Lenovo
 */
#include "max7219.h"


extern const uint8_t LETTERS[][8];
extern const uint8_t NUMBERS[][8];
extern const uint8_t ICONS[][8] ;
extern const int ICONS_LEN;

/*private functions*/




void MAX72xx_Init(void){
	/*
	sendDataSPI(0x09, 0x00);		//decode mode --- no decode
	sendDataSPI(0x0A, 0x02);		//intensity
	sendDataSPI(0x0B, 0x07);		//Scan limit
	sendDataSPI(0x0C, 0x01);		//shutdown
	sendDataSPI(0x0F, 0x00);
	*/
	MAX72xx_write(MAX72xx_DECODE_ADDR, 0x00);
	MAX72xx_write(MAX72xx_INTENSITY_ADDR, MAX72xx_INTENSITY_3_32);
	MAX72xx_write(MAX72xx_SCAN_ADDR, MAX72xx_SCAN_DISP_D_0_7);
	MAX72xx_write(MAX72xx_SHUTDOWN_ADDR, MAX72xx_SHUTDOWN_NORMAL_MODE);
	MAX72xx_write(MAX72xx_TEST_ADDR, MAX72xx_TEST_NORMAL_M);
}

void MAX72xx_write(uint8_t reg, uint8_t data){
#ifdef USE_SPI
	//NSS -> LOW
	HAL_GPIO_WritePin(MAX_CS_PORT, MAX_CS_PIN, RESET);
	//send address
	HAL_SPI_Transmit(&MAX_SPI, (uint8_t*)&reg, 1, HAL_MAX_DELAY);
	while(HAL_SPI_GetState(&MAX_SPI)!=HAL_SPI_STATE_READY);
	//send data
	HAL_SPI_Transmit(&MAX_SPI, (uint8_t*)&data, 1, HAL_MAX_DELAY);
	while(HAL_SPI_GetState(&MAX_SPI)!=HAL_SPI_STATE_READY);
	//NSS ->HIGH
	HAL_GPIO_WritePin(MAX_CS_PORT, MAX_CS_PIN, GPIO_PIN_SET);
#else
	uint8_t i;
	uint8_t bit;
	//NSS -> LOW
	HAL_GPIO_WritePin(MAX_CS_PORT,  MAX_CS_PIN, GPIO_PIN_RESET);
	//send address
	for(i = 0; i<8;i++){
		bit = (reg >> i) & 0b1;
		if(bit == 1){
			HAL_GPIO_WritePin( MAX_DIN_PORT, MAX_DIN_PIN, GPIO_PIN_SET);
		}
		else{
			HAL_GPIO_WritePin(MAX_DIN_PORT, MAX_DIN_PIN, GPIO_PIN_RESET);
		}
		HAL_GPIO_WritePin(MAX_CLK_PORT, MAX_CLK_PIN, GPIO_PIN_SET);
		//RETARDO
		HAL_GPIO_WritePin(MAX_CLK_PORT, MAX_CLK_PIN, GPIO_PIN_RESET);
	}
	//send data
	for(i = 0; i<8;i++){
		bit = (data >> i) & 0b1;
		if(bit == 1){
			HAL_GPIO_WritePin( MAX_DIN_PORT, MAX_DIN_PIN, GPIO_PIN_SET);
		}
		else{
			HAL_GPIO_WritePin(MAX_DIN_PORT, MAX_DIN_PIN, GPIO_PIN_RESET);
		}
		HAL_GPIO_WritePin(MAX_CLK_PORT, MAX_CLK_PIN, GPIO_PIN_SET);
		//RETARDO
		HAL_GPIO_WritePin(MAX_CLK_PORT, MAX_CLK_PIN, GPIO_PIN_RESET);
	}
	//NSS ->HIGH
	HAL_GPIO_WritePin(MAX_CS_PORT,  MAX_CS_PIN, GPIO_PIN_SET);
#endif

}

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






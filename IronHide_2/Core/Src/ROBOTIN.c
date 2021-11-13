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
extern const int ICONS_LEN;

extern void MAX72xx_putChar(char ch);
extern void sendDataSPI(uint8_t reg, uint8_t data);
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
	if(data == 'U'){
		Straight();
		IronHide_setImage(10);
	}
	else if(data == 'D'){
		back();
		IronHide_setImage(8);
	}else if(data == 'L'){
		TurnLeft();
		IronHide_setImage(11);
	}else if(data == 'R'){
		TurnRight();
		IronHide_setImage(9);
	}
	else if(data == 'S'){
		stopMotor();
		MAX72xx_putChar('x');
	}
	HAL_UART_Receive_IT(&huart1, &data, 1);
	return;
}



/**
 * @fn
 * @brief
 * @param []
 * @return none
 */
void IronHide_setImage(uint8_t icon){
	for(uint8_t j = 0;j<8; j++){
		sendDataSPI(j+1, ICONS[icon][j]);
	}
	return;
}

/**
 * @fn
 * @brief
 * @param []
 * @return none
 */
void IronHide_setNumber(uint8_t num){
	uint8_t i;
	if(num == 0){
		for(i = 0;i<8;i++){
			sendDataSPI(i+1, NUMBERS[9][i]);
		}
	}
	else{
		for(i = 1;i<9;i++){
			sendDataSPI(i+1, NUMBERS[num-1][i]);
		}
	}
	return;
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

/**
 * @fn
 * @brief
 * @param []
 * @return none
 */
void IronHide_Init(void){
	IronHide_setNumber(3);
	HAL_GPIO_TogglePin(YELOW_PORT, YELOW_PIN);
	HAL_Delay(1000);
	IronHide_setNumber(2);
	HAL_GPIO_TogglePin(YELOW_PORT, YELOW_PIN);
	HAL_Delay(1000);
	IronHide_setNumber(1);
	HAL_GPIO_TogglePin(YELOW_PORT, YELOW_PIN);
	HAL_Delay(1000);
	HAL_GPIO_TogglePin(YELOW_PORT, YELOW_PIN);
	IronHide_setImage(7);
	HAL_GPIO_WritePin(YELOW_PORT, YELOW_PIN,GPIO_PIN_RESET);

	//probar la luz de la sirena
	HAL_GPIO_WritePin(BLUE_PORT, BLUE_PIN,GPIO_PIN_SET);
	HAL_GPIO_WritePin(RED_PORT, RED_PIN,GPIO_PIN_RESET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(BLUE_PORT, BLUE_PIN,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(RED_PORT, RED_PIN,GPIO_PIN_SET);
	HAL_Delay(50);
	HAL_GPIO_WritePin(BLUE_PORT, BLUE_PIN,GPIO_PIN_SET);
	HAL_GPIO_WritePin(RED_PORT, RED_PIN,GPIO_PIN_RESET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(BLUE_PORT, BLUE_PIN,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(RED_PORT, RED_PIN,GPIO_PIN_SET);
	HAL_Delay(50);
	HAL_GPIO_WritePin(BLUE_PORT, BLUE_PIN,GPIO_PIN_SET);
	HAL_GPIO_WritePin(RED_PORT, RED_PIN,GPIO_PIN_RESET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(BLUE_PORT, BLUE_PIN,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(RED_PORT, RED_PIN,GPIO_PIN_RESET);
	return;
}

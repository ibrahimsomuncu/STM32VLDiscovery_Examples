#include "stm32f10x.h"                  // Device header

void gpioConfig(void);
void delay(uint32_t time);

int main(){
	
	gpioConfig();
	
	uint16_t	buttonState=0;	
	uint16_t	counter=0;
	
	while(1){
	
		buttonState = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6);
	
		if(buttonState==1){
			counter++;
		}		
			
	}

}
void delay(uint32_t time){
	while(time--);
}


void gpioConfig(){
	GPIO_InitTypeDef		GPIOInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);		//	 LED
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);		//	 BUTTON
	
	//	LED
	GPIOInitStructure.GPIO_Mode		=	GPIO_Mode_Out_PP;
	GPIOInitStructure.GPIO_Pin		=	GPIO_Pin_0;
	GPIOInitStructure.GPIO_Speed	=	GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIOInitStructure);
	
	//	BUTTON
	GPIOInitStructure.GPIO_Mode		=	GPIO_Mode_IPD;
	GPIOInitStructure.GPIO_Pin		=	GPIO_Pin_6;
	GPIO_Init(GPIOC, &GPIOInitStructure);

}


#include "stm32f10x.h"                  // Device header

void gpioConfig(void);
void delay(uint32_t time);

int main(){
	
	gpioConfig();
	
	uint16_t	buttonStatus=0;
	uint16_t	counter=0;
	
	while(1){
		
		buttonStatus	=	GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_3);
		
		if(buttonStatus == 1){
			
			counter++;
			for(int i=1000000; i >0; i--);
		
			if(counter % 3 == 1){
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				GPIO_ResetBits(GPIOB, GPIO_Pin_1	|	GPIO_Pin_2);
			}else if(counter % 3 == 2){
				GPIO_SetBits(GPIOB,	GPIO_Pin_0	|	GPIO_Pin_1);
				GPIO_ResetBits(GPIOB, GPIO_Pin_2);
			}else if(counter % 3 == 0){
				GPIO_SetBits(GPIOB, GPIO_Pin_0	|	GPIO_Pin_1	| GPIO_Pin_2);
			}else{
				GPIO_ResetBits(GPIOB, GPIO_Pin_0	|	GPIO_Pin_1	|	GPIO_Pin_2);
			}
	
	}

}

}

void delay(uint32_t time){
	while(time--);
}
void gpioConfig(void){
	GPIO_InitTypeDef		GPIOInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);		// For LEDS
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);		// For BUTTONS
		
	
	// LED
	GPIOInitStructure.GPIO_Mode		=	GPIO_Mode_Out_PP;
	GPIOInitStructure.GPIO_Pin		=	GPIO_Pin_0	|	GPIO_Pin_1	|	GPIO_Pin_2;
	GPIOInitStructure.GPIO_Speed	=	GPIO_Speed_10MHz;
	
	GPIO_Init(GPIOB, &GPIOInitStructure);
	
	
	// BUTTONS
	GPIOInitStructure.GPIO_Mode		=	GPIO_Mode_IPD;
	GPIOInitStructure.GPIO_Pin		=	GPIO_Pin_3;	
	
	GPIO_Init(GPIOC, &GPIOInitStructure);

}

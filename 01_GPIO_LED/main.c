#include "stm32f10x.h"                  // Device header

void gpioConfig (void);

void delay(uint32_t time);

int main(){

	gpioConfig();

	while(1){
		for(int i=0; i<3; i++){
		GPIO_SetBits(GPIOB, GPIO_Pin_0);
		delay(720000);
		GPIO_SetBits(GPIOB, GPIO_Pin_0	|	GPIO_Pin_1);
		delay(720000);
		GPIO_SetBits(GPIOB, GPIO_Pin_0	|	GPIO_Pin_1	|	GPIO_Pin_2);
		delay(720000);
		GPIO_ResetBits(GPIOB, GPIO_Pin_0);
		delay(720000);
		GPIO_ResetBits(GPIOB, GPIO_Pin_0	|	GPIO_Pin_1);
		delay(720000);
		GPIO_ResetBits(GPIOB, GPIO_Pin_0	|	GPIO_Pin_1	|	GPIO_Pin_2);
		delay(720000);
		}
		for(int i=0; i<5; i++){
		GPIO_SetBits(GPIOB, GPIO_Pin_0);
		delay(360000);
		GPIO_SetBits(GPIOB, GPIO_Pin_0	|	GPIO_Pin_1);
		delay(360000);
		GPIO_SetBits(GPIOB, GPIO_Pin_0	|	GPIO_Pin_1	|	GPIO_Pin_2);
		delay(360000);
		GPIO_ResetBits(GPIOB, GPIO_Pin_0);
		delay(360000);
		GPIO_ResetBits(GPIOB, GPIO_Pin_0	|	GPIO_Pin_1);
		delay(360000);
		GPIO_ResetBits(GPIOB, GPIO_Pin_0	|	GPIO_Pin_1	|	GPIO_Pin_2);
		delay(360000);
		}
	}
	
}

void delay(uint32_t time){
	while(time--);
}

void gpioConfig (void)
{

	GPIO_InitTypeDef GPIOInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

	GPIOInitStructure.GPIO_Mode		= GPIO_Mode_Out_PP;
	GPIOInitStructure.GPIO_Pin		= GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
	GPIOInitStructure.GPIO_Speed	= GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB, &GPIOInitStructure);
	
}

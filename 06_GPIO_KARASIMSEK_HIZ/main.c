#include "stm32f10x.h"                  // Device header

void gpioConfig(void);
void delay(uint32_t	time);

int main(){
	gpioConfig();
	
	uint16_t	buttonState	=	0;
	uint16_t	ledArray[]	=	{GPIO_Pin_0, GPIO_Pin_1, GPIO_Pin_2};

	while(1){
		buttonState	=	GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_3);
		if(buttonState==1){		
			for(int	i	=	0;	i<3	;	i++){
				GPIO_SetBits(GPIOB, ledArray[i]);
				delay(720000);
				GPIO_ResetBits(GPIOB, ledArray[i]);
			}
				GPIO_SetBits(GPIOB,	ledArray[1]);
				delay(720000);
				GPIO_ResetBits(GPIOB,	ledArray[1]);
			}else{
				for(int	i	=	0;	i<3	;	i++){
				GPIO_SetBits(GPIOB, ledArray[i]);
				delay(280000);
				GPIO_ResetBits(GPIOB, ledArray[i]);
			}
				GPIO_SetBits(GPIOB,	ledArray[1]);
				delay(280000);
				GPIO_ResetBits(GPIOB,	ledArray[1]);
			}
		
	}

}

void delay(uint32_t	time){
	while(time--);
}

void gpioConfig(void){

	GPIO_InitTypeDef		GPIOInitStructure;
	
	//	For	LEDS
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIOInitStructure.GPIO_Mode		=	GPIO_Mode_Out_PP;
	GPIOInitStructure.GPIO_Pin		=	GPIO_Pin_0	|	GPIO_Pin_1	|	GPIO_Pin_2;
	GPIOInitStructure.GPIO_Speed	=	GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIOInitStructure);
	
	//	For	BUTTON
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIOInitStructure.GPIO_Mode		=	GPIO_Mode_IPD;
	GPIOInitStructure.GPIO_Pin		=	GPIO_Pin_3;
	GPIO_Init(GPIOC, &GPIOInitStructure);
	
}


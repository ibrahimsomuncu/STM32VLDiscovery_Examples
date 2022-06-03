#include "stm32f10x.h"                  // Device header
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM

void gpioConfig(void);
void timerConfig(void);
static int	counter=0;
static uint16_t	led[] =	{GPIO_Pin_0, GPIO_Pin_1, GPIO_Pin_2};

int main(){
	gpioConfig();
	timerConfig();
	while(1){
		
		counter= TIM_GetCounter(TIM6);
		
		if(counter==1999){
			GPIO_SetBits(GPIOB, led[0] | led[1] | led[2]);
		}else if(counter==3999){
			GPIO_ResetBits(GPIOB, led[0] | led[1] | led[2]);
		}
		
	}

}

void timerConfig(void){
	TIM_TimeBaseInitTypeDef	TIMERInitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
	
	TIMERInitStructure.TIM_ClockDivision	=	TIM_CKD_DIV1;
	TIMERInitStructure.TIM_CounterMode		=	TIM_CounterMode_Up;
	TIMERInitStructure.TIM_Period					=	3999;
	TIMERInitStructure.TIM_Prescaler			= 5999;
	TIMERInitStructure.TIM_RepetitionCounter	=	0;
	
	TIM_TimeBaseInit(TIM6, &TIMERInitStructure);
	TIM_Cmd(TIM6, ENABLE);
}

void gpioConfig(void){
	
	GPIO_InitTypeDef		GPIOInitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIOInitStructure.GPIO_Mode		=	GPIO_Mode_Out_PP;
	GPIOInitStructure.GPIO_Pin		=	GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
	GPIOInitStructure.GPIO_Speed	=	GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIOInitStructure);
	
}

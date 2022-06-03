#include "stm32f10x.h"                  // Device header
#include "stm32f10x_exti.h"             // Keil::Device:StdPeriph Drivers:EXTI

void gpioConfig(void);
void extiConfig(void);
void EXTI3_IRQHandler(void);
void delay(uint32_t time);
static uint16_t counter=0;

int main(){
	gpioConfig();
	extiConfig();
	while(1){
		GPIO_SetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2);
		delay(250000);
		GPIO_ResetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2);
		delay(5000000);
	}

}

void delay(uint32_t time){
	while(time--);
}

void gpioConfig(void){
	GPIO_InitTypeDef	GPIOInitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIOInitStructure.GPIO_Mode		=	GPIO_Mode_Out_PP;
	GPIOInitStructure.GPIO_Pin		=	GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
	GPIOInitStructure.GPIO_Speed	= GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIOInitStructure);
	
	GPIOInitStructure.GPIO_Mode		=	GPIO_Mode_IPD;
	GPIOInitStructure.GPIO_Pin		=	GPIO_Pin_3;
	GPIO_Init(GPIOC, &GPIOInitStructure);
	
}
void extiConfig(void){
	EXTI_InitTypeDef	EXTIInitStructure;
	NVIC_InitTypeDef	NVICInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource3);
	
	//	INTERRUPT 
	EXTIInitStructure.EXTI_Line	= EXTI_Line3;
	EXTIInitStructure.EXTI_LineCmd	=	ENABLE;
	EXTIInitStructure.EXTI_Mode	=	EXTI_Mode_Interrupt;
	EXTIInitStructure.EXTI_Trigger	=	EXTI_Trigger_Rising;
	EXTI_Init(&EXTIInitStructure);
	
	//	NVIC
	NVICInitStructure.NVIC_IRQChannel	=	EXTI3_IRQn;
	NVICInitStructure.NVIC_IRQChannelCmd	= ENABLE;
	NVICInitStructure.NVIC_IRQChannelPreemptionPriority	= 1;
	NVICInitStructure.NVIC_IRQChannelSubPriority	=	1;
	NVIC_Init(&NVICInitStructure);
}
void EXTI3_IRQHandler(void){
	if(EXTI_GetITStatus(EXTI_Line3) != RESET ){
		counter++;
	}
	EXTI_ClearITPendingBit(EXTI_Line3);
}


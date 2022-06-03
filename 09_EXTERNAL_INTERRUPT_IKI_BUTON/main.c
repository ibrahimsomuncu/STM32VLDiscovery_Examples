#include "stm32f10x.h"                  // Device header
#include "stm32f10x_exti.h"             // Keil::Device:StdPeriph Drivers:EXTI

void gpioConfig(void);
void extiConfig(void);
void delay(uint32_t time);
void EXTI2_IRQHandler(void);
void EXTI3_IRQHandler(void);
static uint16_t ledArray[3]	=	{GPIO_Pin_0, GPIO_Pin_1, GPIO_Pin_2};

int main(){
	gpioConfig();
	extiConfig();
	
	while(1){
		GPIO_SetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2);
		delay(75000);
		GPIO_ResetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2);
		delay(1000000);
	}

}

void gpioConfig(){
	GPIO_InitTypeDef	GPIOInitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIOInitStructure.GPIO_Mode		=	GPIO_Mode_Out_PP;
	GPIOInitStructure.GPIO_Pin		=	GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
	GPIOInitStructure.GPIO_Speed	= GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIOInitStructure);
	
	GPIOInitStructure.GPIO_Mode		=	GPIO_Mode_IPD;
	GPIOInitStructure.GPIO_Pin		=	GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_Init(GPIOC, &GPIOInitStructure);
}
void delay(uint32_t time){
	while(time--);
}
void extiConfig(){
	EXTI_InitTypeDef	EXTIInitStructure;
	NVIC_InitTypeDef	NVICInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource2);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource3);

	
	EXTIInitStructure.EXTI_Line			= EXTI_Line2 | EXTI_Line3;
	EXTIInitStructure.EXTI_LineCmd	= ENABLE;
	EXTIInitStructure.EXTI_Mode			= EXTI_Mode_Interrupt;
	EXTIInitStructure.EXTI_Trigger	= EXTI_Trigger_Rising;
	EXTI_Init(&EXTIInitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	NVICInitStructure.NVIC_IRQChannel			=	EXTI2_IRQn;
	NVICInitStructure.NVIC_IRQChannelCmd	=	ENABLE;
	NVICInitStructure.NVIC_IRQChannelPreemptionPriority	= 0;
	NVICInitStructure.NVIC_IRQChannelSubPriority				= 0;
	NVIC_Init(&NVICInitStructure);
	
	NVICInitStructure.NVIC_IRQChannel			= EXTI3_IRQn;
	NVICInitStructure.NVIC_IRQChannelCmd	= ENABLE;
	NVICInitStructure.NVIC_IRQChannelPreemptionPriority	= 1;
	NVICInitStructure.NVIC_IRQChannelSubPriority				= 0;
	NVIC_Init(&NVICInitStructure);
}
void EXTI2_IRQHandler(void){
	
	if(EXTI_GetITStatus(EXTI_Line2) != RESET){
	for(int j = 0; j<5; j++){
		for(int i = 0; i<3; i++){
			GPIO_SetBits(GPIOB, ledArray[i]);
			delay(100000);
			GPIO_ResetBits(GPIOB, ledArray[i]);
			delay(100000);
			}
			GPIO_SetBits(GPIOB, ledArray[1]);
			delay(100000);
			GPIO_ResetBits(GPIOB, ledArray[1]);
			delay(100000);
		}
	}
	EXTI_ClearITPendingBit(EXTI_Line2);
}
void EXTI3_IRQHandler(void){
	
	if(EXTI_GetITStatus(EXTI_Line3) != RESET){
		for(int i = 0; i<5; i++){
			GPIO_SetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2);
			delay(500000);
			GPIO_ResetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2);
			delay(200000);
		}
	}
	EXTI_ClearITPendingBit(EXTI_Line3);
}

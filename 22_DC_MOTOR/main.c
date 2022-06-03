#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM
#include "stm32f10x_adc.h"              // Keil::Device:StdPeriph Drivers:ADC

void EXTI0_IRQHandler(void);
void extiConfig(void);
void gpioConfig(void);
void timerConfig(void);
void pwmValue(uint16_t pulse);
void adcConfig(void);
uint16_t readAdc(void);
void delay(uint32_t time);

static uint16_t adcValue = 0;
static uint16_t mapValue = 0;
static uint16_t sagDon = 0;
static uint16_t solDon = 0;

int main(){
	gpioConfig();
	timerConfig();
	adcConfig();
	extiConfig();
	GPIO_SetBits(GPIOB, GPIO_Pin_11);	
	while(1){
		
		adcValue	=	readAdc();
		
		mapValue	=	(uint16_t)(adcValue * (float)(2399.0 / 4040.0));
		
		if(adcValue>0 && adcValue<1500){
			sagDon	=	900-mapValue;
			pwmValue(sagDon);
			GPIO_SetBits(GPIOB, GPIO_Pin_2);
			GPIO_ResetBits(GPIOB, GPIO_Pin_10);	
			GPIO_SetBits(GPIOB, GPIO_Pin_1);			//	Green Led
			GPIO_ResetBits(GPIOB, GPIO_Pin_0);		//	Red Led
		
		}else if(adcValue>=1500 && adcValue<2500){
				///**	DUR FONKSIYONU	**///
			pwmValue(0);
			GPIO_ResetBits(GPIOB, GPIO_Pin_2);
			GPIO_ResetBits(GPIOB, GPIO_Pin_10);	
			GPIO_SetBits(GPIOB, GPIO_Pin_0);			//	Red Led	
			GPIO_ResetBits(GPIOB, GPIO_Pin_1);		//	Green Led
		
		}else if(adcValue>=2500 && adcValue<4000){
			solDon	=	mapValue-1450;
			pwmValue(solDon);
			GPIO_SetBits(GPIOB, GPIO_Pin_10);
			GPIO_ResetBits(GPIOB, GPIO_Pin_2);	
			GPIO_SetBits(GPIOB, GPIO_Pin_1);			//	Green Led
			GPIO_ResetBits(GPIOB, GPIO_Pin_0);		//	Red Led	
		}
		
	}


}

void extiConfig(void){
	EXTI_InitTypeDef	EXTI_InitStruct;
	NVIC_InitTypeDef	NVIC_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource0);
	
	EXTI_InitStruct.EXTI_Line		=	EXTI_Line0;
	EXTI_InitStruct.EXTI_LineCmd	=	ENABLE;
	EXTI_InitStruct.EXTI_Mode		=	EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger	=	EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_InitStruct);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	NVIC_InitStruct.NVIC_IRQChannel	=	EXTI0_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd	=	ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority	=	0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority	=	0;
	NVIC_Init(&NVIC_InitStruct);
}

void EXTI0_IRQHandler(void){
	if(EXTI_GetITStatus(EXTI_Line0)	!= RESET){
			GPIO_ResetBits(GPIOB, GPIO_Pin_2);
			GPIO_ResetBits(GPIOB, GPIO_Pin_10);	
			for(int i = 0; i<4; i++){
				GPIO_SetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1	|	GPIO_Pin_11);
				delay(1000000);
				GPIO_ResetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1	|	GPIO_Pin_11);
				delay(250000);
			}	
				GPIO_SetBits(GPIOB, GPIO_Pin_11);
	}
		EXTI_ClearITPendingBit(EXTI_Line0);
}

void gpioConfig(void){
	//	C0	-->	Emergency Stop Button
	//	B0	-->	Red Led
	//	B1	-->	Green Led
	//	B2	-->	Turn Right Pin
	//	B10	-->	Turn Left Pin
	//	B11	-->	Buzzer
	//	A0	-->	Motor Pin PWM
	//	A1	--> POT
	
	
	GPIO_InitTypeDef		GPIO_InitStruct;

	
	/*		PIN CLOCKLARINI AKTIF EDIYORUZ		*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

	

	/*		LED VE YON PINLARI (PB0	- PB1	-	PB2	-	PB3)		*/	
	GPIO_InitStruct.GPIO_Mode		=	GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin		= GPIO_Pin_0	|	GPIO_Pin_1	|	GPIO_Pin_2	|	GPIO_Pin_10	|	GPIO_Pin_11;
	GPIO_InitStruct.GPIO_Speed	=	GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	

	/*		MOTOR ICIN PWM PINI (PA0)		*/
	GPIO_InitStruct.GPIO_Mode		=	GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin		=	GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed	=	GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	
	/*		POT PINI (PA1)		*/	
	GPIO_InitStruct.GPIO_Mode		=	GPIO_Mode_AIN;
	GPIO_InitStruct.GPIO_Pin		=	GPIO_Pin_1;
	
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	
	/*		STOP BUTONU (EXTERN INTERRUPT)		*/
	GPIO_InitStruct.GPIO_Mode		=	GPIO_Mode_IPD;
	GPIO_InitStruct.GPIO_Pin		=	GPIO_Pin_0;
	GPIO_Init(GPIOC, &GPIO_InitStruct);

}

void timerConfig(void){
	TIM_TimeBaseInitTypeDef	TIM_TimeBaseInitStruct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision	=	TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode		=	TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period					=	2399;
	TIM_TimeBaseInitStruct.TIM_Prescaler			=	10;
	
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
	TIM_Cmd(TIM2, ENABLE);
}

void pwmValue(uint16_t pulse){
	TIM_OCInitTypeDef	TIM_OCInitStruct;
	
	TIM_OCInitStruct.TIM_OCMode				=	TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OCPolarity		=	TIM_OCPolarity_High;
	TIM_OCInitStruct.TIM_OutputState	=	TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_Pulse				=	pulse;
	
	TIM_OC1Init(TIM2, &TIM_OCInitStruct);
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
	
}

void adcConfig(void){
	ADC_InitTypeDef	ADC_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	
	ADC_InitStruct.ADC_ContinuousConvMode	=	ENABLE;
	ADC_InitStruct.ADC_DataAlign					=	ADC_DataAlign_Right;
	ADC_InitStruct.ADC_ExternalTrigConv		=	ADC_ExternalTrigConv_None;
	ADC_InitStruct.ADC_Mode								=	ADC_Mode_Independent;
	ADC_InitStruct.ADC_NbrOfChannel				=	1;
	ADC_InitStruct.ADC_ScanConvMode				=	DISABLE;
	
	ADC_Init(ADC1, &ADC_InitStruct);
	ADC_Cmd(ADC1, ENABLE);
}

uint16_t readAdc(void){
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_55Cycles5);
	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
	
	return ADC_GetConversionValue(ADC1);
}

void delay(uint32_t time){
	while(time--);
}

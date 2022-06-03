#include "stm32f10x.h"                  // Device header
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM

void gpioConfig(void);
void timerConfig(void);
void pwmConfig(uint16_t timPulse);
void delay(uint32_t time);



int main(){
	gpioConfig();
	timerConfig();
	
	while(1){
		////	SERVO ICIN		////
		//		----------			//
		//	-90	derece	1199,	//
		//		0	derece	1799,	//
		//	 90	derece	2399,	//
		////////////////////////
		
		   pwmConfig(1100);//0 derece
       delay(3600000);
       pwmConfig(1799);//90 derece
       delay(3600000);
       pwmConfig(2500);//180 derece
       delay(3600000);
		
	}

}
void gpioConfig(void){
	GPIO_InitTypeDef	GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStruct.GPIO_Mode	=	GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin	=	GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed	=	GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);


}

void timerConfig(void){
	TIM_TimeBaseInitTypeDef		TIM_TimeBaseInitStruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision	=	TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode		=	TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period					=	23999;			// Frekans 50 Hz Olmasi Için Hesap
	TIM_TimeBaseInitStruct.TIM_Prescaler			=	20;	// Frekans 50 Hz Olmasi Için Hesap
//	TIM_TimeBaseInitStruct.TIM_RepetitionCounter	=	0;	// Advence Timerde kullaniliyor.
	
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
	TIM_Cmd(TIM2, ENABLE);
}

void pwmConfig(uint16_t timPulse){
	TIM_OCInitTypeDef	TIM_OCInitStruct;		// Output Compare	// Çikti Karsilastirma
	
	TIM_OCInitStruct.TIM_OCMode				=	TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OutputState	=	TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_OCPolarity		=	TIM_OCPolarity_High;
	TIM_OCInitStruct.TIM_Pulse				=	timPulse;
	
	TIM_OC1Init(TIM2, &TIM_OCInitStruct);
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);	
}

void delay(uint32_t time){
	while(time--);
}

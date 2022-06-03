#include "stm32f10x.h"                  // Device header
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM

void gpioConfig(void);
void timerConfig(void);
void pwmConfig(uint16_t timePulse);
void delay(uint32_t time);
int main(){
	gpioConfig();
	timerConfig();
	
	while(1){
//	599 %25, 1199 %50, 1799 %75, 2399 %100	
		pwmConfig(599);
		delay(4000000);
		pwmConfig(1199);
		delay(4000000);
		pwmConfig(1799);
		delay(4000000);
		pwmConfig(2399);
		delay(4000000);
	}


}
void delay(uint32_t time){
	while(time--);
}
void gpioConfig(void){
	GPIO_InitTypeDef	GPIOInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIOInitStructure.GPIO_Mode	=	GPIO_Mode_AF_PP;
	GPIOInitStructure.GPIO_Pin	=	GPIO_Pin_0;
	GPIOInitStructure.GPIO_Speed	=	GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIOInitStructure);
}

void timerConfig(void){
	TIM_TimeBaseInitTypeDef	TIMERInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	TIMERInitStructure.TIM_ClockDivision			=	TIM_CKD_DIV1;
	TIMERInitStructure.TIM_CounterMode				=	TIM_CounterMode_Up;
	TIMERInitStructure.TIM_Period							=	2399;
	TIMERInitStructure.TIM_Prescaler					=	10;
	TIMERInitStructure.TIM_RepetitionCounter	=	0;
	
	TIM_TimeBaseInit(TIM2, &TIMERInitStructure);
	TIM_Cmd(TIM2,ENABLE);
}

void pwmConfig(uint16_t timePulse){
	TIM_OCInitTypeDef	TIMER_OCInitStructure;
	
	TIMER_OCInitStructure.TIM_OCMode	=	TIM_OCMode_PWM1;		//	Cikti Karsilastirma Modunu Belirtir. // PWM1 olursa ilk HIGHden baslar.
	TIMER_OCInitStructure.TIM_OutputState	=	TIM_OutputState_Enable;	// Çikisin Enable mi Disable mi oldugunu belirtir.
	TIMER_OCInitStructure.TIM_OCPolarity	= TIM_OCPolarity_High;	// Verilen ilk oran degeri HIGH'den basliyor.
	TIMER_OCInitStructure.TIM_Pulse		=	timePulse;		//	%50 cycle için ----	Formülden Hesaplaniyor.				//	Bu alanin içerigi CCRx kayninin içinde saklanir ve çikti tetiklemek için kullanilir.
////////////////////////////////////////////////	599 %25, 1199 %50, 1799 %75, 2399 %100
/////// Advence Timer (TIM1 ve TIM8) için diger variableleride girmemiz gerekir. PWM için yukaridaki 4ünü yazmamiz yeterli.
//
//	TIMER_OCInitStructure.TIM_OCIdleState
//	TIMER_OCInitStructure.TIM_OCNIdleState
//	TIMER_OCInitStructure.TIM_OCNPolarity
//	TIMER_OCInitStructure.TIM_OutputNState
	
	TIM_OC1Init(TIM2, &TIMER_OCInitStructure);
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
	
}

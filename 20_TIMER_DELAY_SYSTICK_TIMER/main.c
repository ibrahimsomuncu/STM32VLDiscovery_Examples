#include "stm32f10x.h"                  // Device header

static	uint32_t	counter = 0;

void delay_ms(uint32_t time);
void SysTick_Handler(void);

int main(){
	
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/1000);	// Saati 1 ms olacak sekilde boluyoruz. 1000ms --> 1 saniye olacak.
	
	while(1){
	TIM_TimeBaseInitTypeDef	TIMM;
		TIMM.TIM_RepetitionCounter	=	
	
	
	}
	
}

void SysTick_Handler(void)		//	Her 1 ms'de bir kesme olur.
{
	if (counter>0)
	{
		counter--;			//	1 ms'de bir bu islem yapilir.
	}
}
void delay_ms(uint32_t time){

	counter	=	time;
	while(counter);

}

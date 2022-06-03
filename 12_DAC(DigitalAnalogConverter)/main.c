#include "stm32f10x.h"                  // Device header
#include "stm32f10x_dac.h"              // Keil::Device:StdPeriph Drivers:DAC

void	gpioConfig(void);
void	dacConfig(void);
void	delay(uint32_t time);

int main(){
	gpioConfig();
	dacConfig();
	while(1){
	
		for(uint16_t i = 0; i<4095; i++){
			DAC_SetChannel1Data(DAC_Align_12b_R, i);	
			delay(5000);
		}
		for(uint16_t i = 4095; i>0; i--){
			DAC_SetChannel1Data(DAC_Align_12b_R, i);	
			delay(5000);
		}
	
	}



}

void	delay(uint32_t time){
	while(time--);
}
void	gpioConfig(void){
	GPIO_InitTypeDef	GPIOInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIOInitStructure.GPIO_Mode		=	GPIO_Mode_AIN;
	GPIOInitStructure.GPIO_Pin		=	GPIO_Pin_4;
	GPIOInitStructure.GPIO_Speed	=	GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIOInitStructure);
}
void	dacConfig(void){
	DAC_InitTypeDef	DACInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
	
	DACInitStructure.DAC_LFSRUnmask_TriangleAmplitude	=	DISABLE;
	DACInitStructure.DAC_OutputBuffer	=	DAC_OutputBuffer_Enable;
	DACInitStructure.DAC_Trigger	=	DAC_Trigger_None;
	DACInitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_Init(DAC_Channel_1, &DACInitStructure);
	
	DAC_Cmd(DAC_Channel_1, ENABLE);
}

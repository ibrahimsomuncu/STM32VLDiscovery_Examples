#include "stm32f10x.h"                  // Device header
#include "stm32f10x_adc.h"              // Keil::Device:StdPeriph Drivers:ADC
#include "stm32f10x_dac.h"              // Keil::Device:StdPeriph Drivers:DAC

void gpioConfig(void);
void adcConfig(void);
uint16_t readADC(void);
void dacConfig(void);
void delay(uint32_t time);
static uint16_t dacValue=0;
static float dacDegree=0;
	
int main(){
	gpioConfig();
	adcConfig();
	dacConfig();
	
	while(1){
		dacValue	=	readADC();
		dacDegree = dacValue * (float)(180.0 / 4030.0);
		
		DAC_SetChannel1Data(DAC_Align_12b_R, dacValue);
		
	}
	
}

void gpioConfig(void){
	GPIO_InitTypeDef		GPIOInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);			// for POT and LED
	
	GPIOInitStructure.GPIO_Mode		=	GPIO_Mode_AIN;
	GPIOInitStructure.GPIO_Pin		=	GPIO_Pin_0 | GPIO_Pin_4;	// A4 --> DAC-Led,	A0 --> POT
	GPIOInitStructure.GPIO_Speed	=	GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIOInitStructure);
	
}
void adcConfig(void){
	ADC_InitTypeDef		ADCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	
	ADCInitStructure.ADC_ContinuousConvMode	=	ENABLE;
	ADCInitStructure.ADC_DataAlign	=	ADC_DataAlign_Right;	// En degerli bit saga yasli
	ADCInitStructure.ADC_ExternalTrigConv	=	ADC_ExternalTrigConv_None;
	ADCInitStructure.ADC_Mode	=	ADC_Mode_Independent;	// Bagimsiz Mod
	ADCInitStructure.ADC_NbrOfChannel	= 1;	// 1 Kanal
	ADCInitStructure.ADC_ScanConvMode	=	DISABLE;	// Baska Bi Okuma Yapilacak mi?
	
	ADC_Init(ADC1, &ADCInitStructure);
	ADC_Cmd(ADC1, ENABLE);
	
}

uint16_t readADC(void){
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
	
	return ADC_GetConversionValue(ADC1);
}

void dacConfig(void){
	DAC_InitTypeDef		DACInitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
	
	DACInitStructure.DAC_LFSRUnmask_TriangleAmplitude	= DISABLE;
	DACInitStructure.DAC_OutputBuffer	= ENABLE;
	DACInitStructure.DAC_Trigger	= DAC_Trigger_None;
	DACInitStructure.DAC_WaveGeneration	= DAC_WaveGeneration_None;		// DALGA ÜRETMIYORUZ ONUN IÇIN NONE
	
	DAC_Init(DAC_Channel_1, &DACInitStructure);
	DAC_Cmd(DAC_Channel_1, ENABLE);
}

void delay(uint32_t time){
	while(time--);
}

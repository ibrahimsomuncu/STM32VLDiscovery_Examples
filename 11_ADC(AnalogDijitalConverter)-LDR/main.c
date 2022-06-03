#include "stm32f10x.h"                  // Device header
#include "stm32f10x_adc.h"              // Keil::Device:StdPeriph Drivers:ADC

void gpioConfig(void);
void adcConfig(void);
uint16_t readADC(void);

int main(){
	gpioConfig();
	adcConfig();

}


void gpioConfig(void){
	GPIO_InitTypeDef	GPIOInitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	// POT IÇIN
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	// LEDLER IÇIN
	
	GPIOInitStructure.GPIO_Mode		=	GPIO_Mode_Out_PP;
	GPIOInitStructure.GPIO_Pin		=	GPIO_Pin_0 |	GPIO_Pin_1 |	GPIO_Pin_2;
	GPIOInitStructure.GPIO_Speed	=	GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIOInitStructure);
	
	GPIOInitStructure.GPIO_Mode		=	GPIO_Mode_AIN;
	GPIOInitStructure.GPIO_Pin		=	GPIO_Pin_0;
	GPIO_Init(GPIOA, &GPIOInitStructure);
	
}
void adcConfig(void){
	ADC_InitTypeDef		ADCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	
	ADCInitStructure.ADC_ContinuousConvMode	=	ENABLE;		// DEGERLERI SÜREKLI ALMAK IÇIN
	ADCInitStructure.ADC_DataAlign					=	ADC_DataAlign_Right;
	ADCInitStructure.ADC_ExternalTrigConv		=	ADC_ExternalTrigConv_None;	// TETIKLEME ILE AKTIF ETMIYORUZ 
	ADCInitStructure.ADC_Mode								=	ADC_Mode_Independent;
	ADCInitStructure.ADC_NbrOfChannel				=	1;
	ADCInitStructure.ADC_ScanConvMode				=	DISABLE;	// BIRÇOK ADC OLDUGU ZAMAN TARAMA YAPMAK IÇIN AKTIF EDILIR.
	ADC_Init(ADC1, &ADCInitStructure);
	ADC_Cmd(ADC1, ENABLE);
}

uint16_t readADC(void){
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
	
	return ADC_GetConversionValue(ADC1);
}

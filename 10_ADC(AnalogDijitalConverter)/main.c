#include "stm32f10x.h"                  // Device header
#include "stm32f10x_adc.h"              // Keil::Device:StdPeriph Drivers:ADC

void gpioConfig(void);
void adcConfig(void);
uint16_t readADC(void);
static uint16_t adcValue=0;
static float voltage=0;

int main(){
	gpioConfig ();
	adcConfig();
	
	while(1){
	
		adcValue	=	readADC();
		
		voltage = adcValue * (float)(3.30 / 4040.00);	//Çözünürlügümüz 12 Bit, 2^n = 2^12 - 1 = 4095
		if(adcValue<1000){
			GPIO_ResetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2);
		}else if(adcValue>=1000 && adcValue<2000){
			GPIO_SetBits(GPIOB, GPIO_Pin_0);
			GPIO_ResetBits(GPIOB, GPIO_Pin_1 | GPIO_Pin_2);
		}else if(adcValue>=2000 && adcValue<3000){
			GPIO_SetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1);
			GPIO_ResetBits(GPIOB, GPIO_Pin_2);
		}else if(adcValue>=3000){
			GPIO_SetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2);
		}
		
	}

}

void gpioConfig(void){
	GPIO_InitTypeDef	GPIOInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	// POT IÇIN PORTUMUZU VE CLOCK'u AKTIF ETTIK.
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	// LED IÇIN PORTUMUZU VE CLOCK'u AKTIF ETTIK.
	
	//LED
	GPIOInitStructure.GPIO_Mode		= GPIO_Mode_Out_PP;
	GPIOInitStructure.GPIO_Pin		= GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
	GPIOInitStructure.GPIO_Speed	=	GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIOInitStructure);	
	
	// POT
	GPIOInitStructure.GPIO_Mode		= GPIO_Mode_AIN;		// ANALOG INPUT
	GPIOInitStructure.GPIO_Pin		= GPIO_Pin_0;
	GPIO_Init(GPIOA, &GPIOInitStructure);
	
}
	
void adcConfig(void){
	ADC_InitTypeDef	ADCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);	// ADC1 AKTIF EDILDI
	
	ADCInitStructure.ADC_ContinuousConvMode	=  ENABLE;	// ÇEVRIMIÇI OLMASINI AKTIF ETTIK
	ADCInitStructure.ADC_DataAlign	=	ADC_DataAlign_Right;	// EN DEGERLI BIT SAGA DAYALI
	ADCInitStructure.ADC_ExternalTrigConv	=	ADC_ExternalTrigConv_None;	// TRIGGER KULLANMIYORUZ
	ADCInitStructure.ADC_Mode	=	ADC_Mode_Independent;	
	ADCInitStructure.ADC_NbrOfChannel	= 1;	// KAÇ KANALLI  ADC KULLANDIK
	ADCInitStructure.ADC_ScanConvMode	=	DISABLE;	// MULTI CHANNEL VAR MI ?
	ADC_Init(ADC1, &ADCInitStructure);
	
	ADC_Cmd(ADC1, ENABLE);
}	

uint16_t readADC(void){

	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);	// ADC AYARLARI 1. ADC, HANGI PIN, KACINCI ADC, CYCLE SÜRESI
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);	// ADC BASLATATTIK
	
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
	return ADC_GetConversionValue(ADC1);
}

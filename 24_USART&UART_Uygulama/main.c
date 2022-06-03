#include "stm32f10x.h"                  // Device header
#include "stm32f10x_adc.h"              // Keil::Device:StdPeriph Drivers:ADC
#include "stm32f10x_usart.h"            // Keil::Device:StdPeriph Drivers:USART
#include <stdio.h>

void SysTick_Handler(void);
void delay_ms(uint32_t time);
void timerConfig(void);
void gpioConfig(void);
void uartConfig(void);
void adcConfig(void);
uint16_t readADC(void);
void uartTransmit(uint16_t data);

static uint32_t counter = 0;
static uint16_t data = 0;

int main(){
	gpioConfig();
	uartConfig();
	adcConfig();
	timerConfig();
	
	while(1){		
		
		
		data	=	readADC();
		uartTransmit(data);
		
		delay_ms(1000);


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

void timerConfig(void){
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/1000);
}

void gpioConfig(void){
	
	GPIO_InitTypeDef	GPIO_InitStruct;
	
	/*		ADC		Pin		-->	PA0		*/
	/*		Tx		Pin		-->	PA9		*/
	/*		Rx		Pin		-->	PA10	*/
	/*		Led		Pin		-->	PB0		*/
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	/*		ADC	Pin		*/
	GPIO_InitStruct.GPIO_Mode		=	GPIO_Mode_AIN;
	GPIO_InitStruct.GPIO_Pin		=	GPIO_Pin_0;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	/*		Tx Pin		*/
	GPIO_InitStruct.GPIO_Mode		=	GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin		=	GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Speed	=	GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	/*		Rx Pin		*/
	GPIO_InitStruct.GPIO_Mode		=	GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin		=	GPIO_Pin_10;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	/*		Led Pin		*/
	GPIO_InitStruct.GPIO_Mode		=	GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin		=	GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed	=	GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);

}

void uartConfig(void){
	USART_InitTypeDef		USART_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	USART_InitStruct.USART_BaudRate	=	9600;
	USART_InitStruct.USART_HardwareFlowControl	=	USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode				=	USART_Mode_Rx	|	USART_Mode_Tx;
	USART_InitStruct.USART_Parity			=	USART_Parity_No;
	USART_InitStruct.USART_StopBits		=	USART_StopBits_1;
	USART_InitStruct.USART_WordLength	=	USART_WordLength_8b;
	
	USART_Init(USART1, &USART_InitStruct);
	USART_Cmd(USART1, ENABLE);

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

uint16_t readADC(void){
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);	
	return ADC_GetConversionValue(ADC1);
}

void uartTransmit(uint16_t potValue){
	
	char send[50];
	
	sprintf(send, "Deger: %d\n", potValue);
	int i = 0;
	while(send[i] != '\0'){
		
		while(!(USART1->SR 	& 0x00000040));
		USART_SendData(USART1, *(send+i));
		i++;
		
	}

}

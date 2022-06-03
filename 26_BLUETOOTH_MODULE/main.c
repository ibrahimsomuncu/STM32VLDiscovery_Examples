#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f10x_usart.h"            // Keil::Device:StdPeriph Drivers:USART

void delay(uint32_t time);
void InitGPIOs(void);
void InitUSART(void);
void usartTransmit(char* string);

int main(){
	InitGPIOs();
	InitUSART();

	while(1){
		
		usartTransmit("Ibrahim Somuncu\n");
		delay(2600000);
		
	}
}

void delay(uint32_t time){
	while(time--);
}

void InitGPIOs(void){
	GPIO_InitTypeDef	GPIO_InitStruct;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

//	Tx	-->	PA9
//	Rx	-->	PA10

	//		Tx
	GPIO_InitStruct.GPIO_Mode		=	GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin		=	GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Speed	=	GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void InitUSART(void){
	USART_InitTypeDef	USART_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	USART_InitStruct.USART_BaudRate	=	9600;
	USART_InitStruct.USART_HardwareFlowControl	=	USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode	=	USART_Mode_Tx;
	USART_InitStruct.USART_Parity	=	USART_Parity_No;
	USART_InitStruct.USART_StopBits	= USART_StopBits_1;
	USART_InitStruct.USART_WordLength	= USART_WordLength_8b;
	
	USART_Init(USART1, &USART_InitStruct);
	USART_Cmd(USART1, ENABLE);
}

void usartTransmit(char* string){
	int i = 0;
	while(string[i] != '\0'){
		while(!(USART1->SR & 0x00000040));
		USART_SendData(USART1, string[i]);
		i++;
	}
}

#include "stm32f10x.h"                  // Device header
#include "stm32f10x_usart.h"            // Keil::Device:StdPeriph Drivers:USART

void gpioConfig(void);
void uartConfig(void);
void uartTransmit(char *string);

static char name[]		=	"Ibrahim Somuncu\n";
static uint16_t data	=	0;

int main(){
	
	while(1){
	
		uartTransmit(name);		//	Bilgisayara name'yi gonder ve terminalde yazdir...
		
		data	=	USART_ReceiveData(USART1);
		
		if(data=='1'){
			GPIO_SetBits(GPIOB, GPIO_Pin_0);
		}else if(data=='0'){
			GPIO_ResetBits(GPIOB, GPIO_Pin_0);
		}
	
	
	
	}

}

void gpioConfig(void){
	GPIO_InitTypeDef		GPIO_InitStruct;
	
	
	
	/*		PA9		-->	USART1_TX		-->	TIM1_CH2
				PA10	-->	USART2_RX		-->	TIM1_CH3			
				PB0		-->	LED													*/
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	/*		TX AYARLAMALARI	---	Bilgisayara veri gonderme		*/
	GPIO_InitStruct.GPIO_Mode		=	GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin		=	GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Speed	=	GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	/*		RX AYARLAMALARI	---	Bilgisayardan veri alma			*/
	GPIO_InitStruct.GPIO_Mode		=	GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin		=	GPIO_Pin_10;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	/*		LED ICIN	---	Bilgisayardan aldigimiz veriye gore yanip sonecek		*/
	GPIO_InitStruct.GPIO_Mode		=	GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin		=	GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed	=	GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
}
void uartConfig(void){
	USART_InitTypeDef		UART_InitStruct;
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	UART_InitStruct.USART_BaudRate	=	9600;
	UART_InitStruct.USART_HardwareFlowControl	=	USART_HardwareFlowControl_None;
	UART_InitStruct.USART_Mode	=	USART_Mode_Tx	|	USART_Mode_Rx;								//// Rx ve Tx'i aktif ediyoruz.
	UART_InitStruct.USART_Parity	=	USART_Parity_No;
	UART_InitStruct.USART_StopBits	=	USART_StopBits_1;
	UART_InitStruct.USART_WordLength	=	USART_WordLength_8b;
	
	
	
	USART_Init(USART1, &UART_InitStruct);
	USART_Cmd(USART1, ENABLE);

}

void uartTransmit(char *string){
	
	while(*string){
		
		while(!(USART1->SR & 0x00000040));
		USART_SendData(USART1, *string);
		*string++;
	
	}

}

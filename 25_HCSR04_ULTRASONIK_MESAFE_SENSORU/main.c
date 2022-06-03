#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f10x_usart.h"            // Keil::Device:StdPeriph Drivers:USART
#include <stdio.h>
void gpioConfig(void);
void delayUS(uint32_t time);
float HCSR04_Read(void);
void uartConfig(void);
void uartTransmit(char *string);


static float distance=0;
static char message[20];


int main(){
	gpioConfig();
	uartConfig();
	
	while(1){
		distance=HCSR04_Read();
		sprintf(message,"Mesafe: %f cm \n",distance);
		uartTransmit(message);
		if(distance>=5.0){
			GPIO_SetBits(GPIOB,GPIO_Pin_0);
			GPIO_ResetBits(GPIOB,GPIO_Pin_1);
		
		
		}if(distance<5.0){
		GPIO_SetBits(GPIOB,GPIO_Pin_1);
		GPIO_ResetBits(GPIOB,GPIO_Pin_0);
		}
		
		delayUS(100000);

	}

}

void gpioConfig(void){
	
	GPIO_InitTypeDef GPIOInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	//TRIG PIN CONFIG
	GPIOInitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIOInitStructure.GPIO_Pin=GPIO_Pin_1;
	GPIOInitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIOInitStructure);
	
	
	//ECHO PIN CONFIG
	GPIOInitStructure.GPIO_Mode=GPIO_Mode_IPD;
	GPIOInitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIOInitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIOInitStructure);
	
	
	//TX
   GPIOInitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
   GPIOInitStructure.GPIO_Pin=GPIO_Pin_9;
   GPIOInitStructure.GPIO_Speed=GPIO_Speed_50MHz;
   GPIO_Init(GPIOA,&GPIOInitStructure);
	 
	 //LED
   GPIOInitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
   GPIOInitStructure.GPIO_Pin=GPIO_Pin_0 |GPIO_Pin_1;
   GPIOInitStructure.GPIO_Speed=GPIO_Speed_50MHz;
   GPIO_Init(GPIOB,&GPIOInitStructure);
}

void delayUS(uint32_t time){
  uint32_t newTime=time*24;
	while(newTime--);
}


float HCSR04_Read(void){
	uint32_t time=0;
	float tempDistance=0;
	
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);
	delayUS(10);
	GPIO_SetBits(GPIOA,GPIO_Pin_1);
	delayUS(10);
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);
	delayUS(10);
	
	while(!(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)));
	
	while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)){
		time++;
		delayUS(1);
	}
	
	
	
	tempDistance=(float)time*0.034;
	if(tempDistance>400) tempDistance=400;
	if(tempDistance<2) tempDistance=2;
	delayUS(10000);
	
	return tempDistance;
}

void uartConfig(){
   USART_InitTypeDef UARTInitStructure;
   
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
   
   UARTInitStructure.USART_BaudRate=9600;
   UARTInitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
   UARTInitStructure.USART_Mode=USART_Mode_Tx;
   UARTInitStructure.USART_Parity=USART_Parity_No;
   UARTInitStructure.USART_StopBits=USART_StopBits_1;
   UARTInitStructure.USART_WordLength=USART_WordLength_8b;
   
   USART_Init(USART1,&UARTInitStructure);
   USART_Cmd(USART1,ENABLE);

}

void uartTransmit(char *string){
   while(*string){
      while(!(USART1->SR & 0x00000040));
      USART_SendData(USART1,*string);
      *string++;
   }
}

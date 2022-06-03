#include "stm32f10x.h"                  // Device header

#define		portA		GPIOA
#define		portB		GPIOB
#define		portC		GPIOC
#define		portD		GPIOD

#define		PIN0		(uint16_t)GPIO_Pin_0
#define		PIN1		(uint16_t)GPIO_Pin_1
#define		PIN2		(uint16_t)GPIO_Pin_2
#define		PIN3		(uint16_t)GPIO_Pin_3
#define		PIN4		(uint16_t)GPIO_Pin_4
#define		PIN5		(uint16_t)GPIO_Pin_5
#define		PIN6		(uint16_t)GPIO_Pin_6
#define		PIN7		(uint16_t)GPIO_Pin_7
#define		PIN8		(uint16_t)GPIO_Pin_8
#define		PIN9		(uint16_t)GPIO_Pin_9
#define		PIN10		(uint16_t)GPIO_Pin_10
#define		PIN11		(uint16_t)GPIO_Pin_11
#define		PIN12		(uint16_t)GPIO_Pin_12
#define		PIN13		(uint16_t)GPIO_Pin_13
#define		PIN14		(uint16_t)GPIO_Pin_14
#define		PIN15		(uint16_t)GPIO_Pin_15

#define		NUMBERSIZE				10
#define		LETTERSIZE				23
#define		CHARACTERSIZE			4
#define		CLEANDISPLAYSIZE	6

void	seg7DisplayInit(GPIO_TypeDef*	port, uint8_t pin0,
																					uint8_t pin1,
																					uint8_t pin2,
																					uint8_t pin3,
																					uint8_t pin4,
																					uint8_t pin5,
																					uint8_t pin6,
																					uint8_t pin7);

void printNumber(GPIO_TypeDef*	port,	uint8_t	number);
void printLetter(GPIO_TypeDef* port, char letter);
void printChar(GPIO_TypeDef* port);


void delay(uint32_t	time);


static	uint8_t	numberArray[]				=	{0x3F,	0x06,	0x5B,	0x4F,	0x66,	0x6D,	0x7C,	0x07,	0x7F,	0x67};
static	uint8_t	letterArray[]				=	{0x77,	0x7c,	0x39,	0x5E,	0x79,	0x71,	0x6F,	0x74,	0x10,	0xE,	0x78,	0x38,	0x40,	0x54,	0x5C,	0x73,	0x50,	0x6D,	0x78,	0x1C,	0x40,	0x66,	0x49};
static	uint8_t	characterArray[]		=	{0x40,	0x49,	0x5C,	0x52};
static	uint8_t	cleanDisplayArray[]	=	{0x1,	0x2,	0x4,	0x8,	0x10,	0x20};

void	seg7DisplayInit(GPIO_TypeDef*	port, uint8_t pin0,
																					uint8_t pin1,
																					uint8_t pin2,
																					uint8_t pin3,
																					uint8_t pin4,
																					uint8_t pin5,
																					uint8_t pin6,
																					uint8_t pin7){
		if(port==portA){
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		}else if(port==portB){
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		}else if(port==portC){
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
		}else if(port==portD){
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
		}
		
		GPIO_InitTypeDef		GPIO_InitStruct;
		
		GPIO_InitStruct.GPIO_Mode		=	GPIO_Mode_Out_PP;
		GPIO_InitStruct.GPIO_Speed	=	GPIO_Speed_50MHz;
		GPIO_InitStruct.GPIO_Pin		=	pin0	|	pin1	|	pin2	|	pin3	|	pin4	|	pin5	|	pin6	|	pin7;
		
		GPIO_Init(port, &GPIO_InitStruct);

}

void printNumber(GPIO_TypeDef*	port,	uint8_t	number){
	for(int i=0 ; i<NUMBERSIZE ; i++)
	{
		if(number==i){
			port->ODR	=	numberArray[i];
			delay(3000000);
			break;
		}else
		{
			for(int j=0 ; j<6 ; j++){
				port->ODR	=	cleanDisplayArray[j];
				delay(100000);
			}
		}
	}
}

void printLetter(GPIO_TypeDef* port, char letter){
		if(letter == 'A' || letter == 'a')
			port->ODR	= letterArray[0];
		else	if(letter == 'B' || letter == 'b')
			port->ODR	= letterArray[1];
		else	if(letter == 'C' || letter == 'c')
			port->ODR	= letterArray[2];
		else	if(letter == 'D' || letter == 'd')
			port->ODR	= letterArray[3];
		else	if(letter == 'E' || letter == 'e')
			port->ODR	= letterArray[4];
		else	if(letter == 'F' || letter == 'f')
			port->ODR	= letterArray[5];
		else	if(letter == 'G' || letter == 'g')
			port->ODR	= letterArray[6];
		else	if(letter == 'H' || letter == 'h')
			port->ODR	= letterArray[7];
		else	if(letter == 'I' || letter == 'i')
			port->ODR	= letterArray[8];
		else	if(letter == 'J' || letter == 'j')
			port->ODR	= letterArray[9];
		else	if(letter == 'K' || letter == 'k')
			port->ODR	= letterArray[10];
		else	if(letter == 'L' || letter == 'l')
			port->ODR	= letterArray[11];
		else	if(letter == 'M' || letter == 'm')
			port->ODR	= letterArray[12];
		else	if(letter == 'N' || letter == 'n')
			port->ODR	= letterArray[13];
		else	if(letter == 'O' || letter == 'o')
			port->ODR	= letterArray[14];
		else	if(letter == 'P' || letter == 'p')
			port->ODR	= letterArray[15];
		else	if(letter == 'R' || letter == 'r')
			port->ODR	= letterArray[16];
		else	if(letter == 'S' || letter == 's')
			port->ODR	= letterArray[17];
		else	if(letter == 'T' || letter == 't')
			port->ODR	= letterArray[18];
		else	if(letter == 'U' || letter == 'u')
			port->ODR	= letterArray[19];
		else	if(letter == 'V' || letter == 'v')
			port->ODR	= letterArray[20];
		else	if(letter == 'Y' || letter == 'y')
			port->ODR	= letterArray[21];
		else	if(letter == 'Z' || letter == 'z')
			port->ODR	= letterArray[22];	
		else{
			for(int i = 0 ; i<6 ; i++){
				port->ODR	=	cleanDisplayArray[i];
				delay(200000);
			}
		}
		
}

void printChar(GPIO_TypeDef* port){
	for(int i = 0; i<CHARACTERSIZE; i++)
	{
		port->ODR = characterArray[i];
		delay(500000);
	}
}

void delay(uint32_t	time){
	while(time--);
}


int main(){
	seg7DisplayInit(portA, PIN0, PIN1, PIN2, PIN3, PIN4, PIN5, PIN6, PIN7);
	while(1)
	{
		char isim[]	=	"nasilsin";
		int i = 0;
		while(isim[i] != '\0')
		{
			printLetter(portA, isim[i]);
			i++;
			delay(3000000);
		}	
		printChar(portA);
			delay(3600000);
	}
}

#include "stm32f10x.h"                  // Device header
#include "stm32f10x_dac.h"              // Keil::Device:StdPeriph Drivers:DAC

void gpioConfig(void);
void dacConfig(void);
void delay(uint32_t time);

static uint16_t sinArray[] = {2048,2248,2447,2642,2831,3013,3185,3346,
3495,3630,3750,3853,3939,4007,4056,4085,
4095,4085,4056,4007,3939,3853,3750,3630,
3495,3346,3185,3013,2831,2642,2447,2248,
2048,1847,1648,1453,1264,1082,910,749,
600,465,345,242,156,88,39,10,
0,10,39,88,156,242,345,465,
600,749,910,1082,1264,1453,1648,1847};

static uint16_t triArray[] = {128,256,384,512,640,768,896,1024,
1152,1280,1408,1536,1664,1792,1920,2048,
2175,2303,2431,2559,2687,2815,2943,3071,
3199,3327,3455,3583,3711,3839,3967,4095,
3967,3839,3711,3583,3455,3327,3199,3071,
2943,2815,2687,2559,2431,2303,2175,2048,
1920,1792,1664,1536,1408,1280,1152,1024,
896,768,640,512,384,256,128,0,};

int main(){
	gpioConfig();
	dacConfig();
	while(1){
		for(int i = 0 ; i < 64 ; i++){
		//	DAC_SetChannel1Data(DAC_Align_12b_R, sinArray[i]);
				DAC_SetChannel1Data(DAC_Align_12b_R, triArray[i]);
				delay(300000);
		}
	}
	
}
void delay(uint32_t time){
	while(time--);
}

void gpioConfig(void){
	GPIO_InitTypeDef	GPIOInitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIOInitStructure.GPIO_Mode	=	GPIO_Mode_AIN;
	GPIOInitStructure.GPIO_Pin	= GPIO_Pin_4;
	GPIOInitStructure.GPIO_Speed	=	GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIOInitStructure);

}

void dacConfig(void){
	DAC_InitTypeDef	DACInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
	
	DACInitStructure.DAC_LFSRUnmask_TriangleAmplitude	=	DISABLE;
	DACInitStructure.DAC_OutputBuffer	=	ENABLE;
	DACInitStructure.DAC_Trigger	=	DAC_Trigger_None;
	DACInitStructure.DAC_WaveGeneration	= DAC_WaveGeneration_None;
	
	DAC_Init(DAC_Channel_1, &DACInitStructure);
	DAC_Cmd(DAC_Channel_1, ENABLE);
}

#ifndef ADC_DAC_H
#define ADC_DAC_H

#ifdef __cplusplus
extern "C" {
#endif 

#include "stm32f4xx.h"
		
#define ADC_IN0   0     // If use this ADC channel   PA0 
#define ADC_IN1   0     // If use this ADC channel   PA1
#define ADC_IN2   0     // If use this ADC channel   PA2
#define ADC_IN3   0     // If use this ADC channel   PA3
#define ADC_IN4   0     // If use this ADC channel   PA4
#define ADC_IN5   0     // If use this ADC channel   PA5
#define ADC_IN6   0     // If use this ADC channel   PA6  
#define ADC_IN7   0     // If use this ADC channel   PA7
#define ADC_IN8   0     // If use this ADC channel   PB0
#define ADC_IN9   0     // If use this ADC channel   PB1
#define ADC_IN10   1     // If use this ADC channel   PC0
#define ADC_IN11   1     // If use this ADC channel   PC1
#define ADC_IN12   1     // If use this ADC channel   PC2
#define ADC_IN13   1     // If use this ADC channel   PC3
#define ADC_IN14   0     // If use this ADC channel   PC4
#define ADC_IN15   0     // If use this ADC channel   PC5
#define ADC_IN16   1     // If use this ADC channel   CPU temperture
	
#define ADC_NUM     5     // ENABLE ADC channel add 1, and last channel to collect inner voltage to calculate CPU temperature   

typedef struct ADC_DAC_Data{
  	volatile unsigned int ADC_Sample_Value[ADC_NUM];        //ADC sample values
		float    ADC_Standard_Value[ADC_NUM];          //ADC standard voltage values
    float    Cpu_Standard_T;                       //standard CPU temperture             
    unsigned int   DAC_C_1;                  // vol:0~3300,  represet : 0~3.3V
    unsigned int   DAC_C_2;                  // vol:0~3300,  represet : 0~3.3V
}ADC_DAC_Data;
extern ADC_DAC_Data adc_dac_data_r;       //ADC data interface

void HF_ADC_Moder_Init(void);            //ADC channel initialization,
void HF_ADC_Data_Anl(void);              //external call, data will update once be called
void HF_Dac_Init(unsigned int DAC_Channel_x); //DAC output initialization, DAC_Channel_x = DAC_Channel_1 PA4 || DAC_Channel_2 PA5
//DAC_Channel_x = DAC_Channel_1|| DAC_Channel_2 vol:0~3300,  represet : 0~3.3V //set voltage of output Channelx
void HF_Dac_Set_Vol(unsigned int DAC_Channel_x, unsigned  short int  vol);

#ifdef __cplusplus
}
#endif 

#endif //#ifndef ADC_DAC_H


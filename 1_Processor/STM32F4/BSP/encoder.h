#ifndef ENCODER_H
#define ENCODER_H

#ifdef __cplusplus
extern "C" {
#endif 

#include "stm32f4xx.h"

/*TIM2 CHI1 CHI2---PA0 PA1  TIM3 CHI1 CHI2---PA6 PA7||TIM3 CHI1 CHI2---PB4 PB5 TIM4 CHI1 CHI2---PB6 PB7 */
void HF_Encoder_Init(TIM_TypeDef* TIMx, unsigned char GPIO_AF);       //Initialize encoder mode, input parameter TIM1 TIM2 TIM3

typedef struct ENCODER_Data{
    float TIM2_Count;         //current pulse number, Negative or positive mean different direction
    float TIM3_Count;         //current pulse number, Negative or positive mean different direction
    float TIM4_Count;         //current pulse number, Negative or positive mean different direction
}ENCODER_Data;

float Get_Encoder_CNT_TIM2(void);
float Get_Encoder_CNT_TIM3(void);
float Get_Encoder_CNT_TIM4(void);

extern ENCODER_Data encoder_data_r;

#ifdef __cplusplus
}
#endif 

#endif // #ifndef ENCODER_H



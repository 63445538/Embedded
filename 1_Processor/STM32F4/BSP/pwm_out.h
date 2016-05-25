#ifndef PWM_OUT_H
#define PWM_OUT_H

#ifdef __cplusplus
extern "C" {
#endif 
	
#include "stm32f4xx.h"
	
typedef struct PWM_Out_Data{
    unsigned short int TIM1_PWM_Period;
    unsigned short int TIM8_PWM_Period;
    unsigned short int TIM12_PWM_Period;

    unsigned short int TIM1_PWM1;
    unsigned short int TIM1_PWM2;
    unsigned short int TIM1_PWM3;
    unsigned short int TIM1_PWM4;
    unsigned short int TIM8_PWM1;
    unsigned short int TIM8_PWM2;
    unsigned short int TIM8_PWM3;
    unsigned short int TIM8_PWM4;
    unsigned short int TIM12_PWM1;
    unsigned short int TIM12_PWM2;
}PWM_Out_Data;
extern PWM_Out_Data pwm_out_data_r;

//PWM initialization, parameter TIM1,PA8,9,10,11 TIM8 PC6,7,8,9    default Prescaler :72-1  frequency:1MHZ   default cycle:2000-->20ms
void HF_PwmOut_Init(TIM_TypeDef* TIMx, unsigned short int Prescaler, unsigned short int Period, unsigned char GPIO_AF);

void Pwm_Set_TIM1_CCR1(unsigned short int Pwm_Value);
void Pwm_Set_TIM1_CCR2(unsigned short int Pwm_Value);
void Pwm_Set_TIM1_CCR3(unsigned short int Pwm_Value);
void Pwm_Set_TIM1_CCR4(unsigned short int Pwm_Value);
void Pwm_Set_TIM8_CCR1(unsigned short int Pwm_Value);
void Pwm_Set_TIM8_CCR2(unsigned short int Pwm_Value);
void Pwm_Set_TIM8_CCR3(unsigned short int Pwm_Value);
void Pwm_Set_TIM8_CCR4(unsigned short int Pwm_Value);
void Pwm_Set_TIM12_CCR1(unsigned short int Pwm_Value);
void Pwm_Set_TIM12_CCR2(unsigned short int Pwm_Value);

#ifdef __cplusplus
}
#endif 

#endif // #ifndef PWM_OUT_H



#ifndef PWM_IN_H__
#define PWM_IN_H__

#ifdef __cplusplus
extern "C" {
#endif 

#include "stm32f4xx.h"

#define PWM_Input_CH0_ENABLE 1    // if use this channel to capture PWM  PC0
#define PWM_Input_CH1_ENABLE 0    // if use this channel to capture PWM  PC1
#define PWM_Input_CH2_ENABLE 0    // if use this channel to capture PWM  PC2
#define PWM_Input_CH3_ENABLE 0    // if use this channel to capture PWM  PC3
#define PWM_Input_CH4_ENABLE 0    // if use this channel to capture PWM  PC4

typedef struct PWM_In_Data{
    volatile float PWM_Input_CH0;   //current input value of PWM (us)
    volatile float PWM_Input_CH1;
    volatile float PWM_Input_CH2;
    volatile float PWM_Input_CH3;
    volatile float PWM_Input_CH4;
}PWM_In_Data;
extern PWM_In_Data pwm_in_data_r;

void HF_PwmIn_Init(void);

#ifdef __cplusplus
}
#endif 

#endif //#ifndef PWM_IN_H__



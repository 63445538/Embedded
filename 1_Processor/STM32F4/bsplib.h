/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: BSP_TOP.c
* Contact:  QQ Exchange Group -- 521037187
* Version:  V2.0
*
* LICENSING TERMS:
* The Hands Free is licensed generally under a permissive 3-clause BSD license.
* Contributions are requiredto be made under the same license.
*
* History:
* <author>      <time>      <version>      <desc>
* mawenke       2015.10.1   V1.0           creat this file
*
* Description:
* BSP Distribution of hardware source
* TIM2 TIM5 32BIT , others are 16BIT timer
* SysTick(24Bits) used by operation system, nor using to make accurate delay  if no operation system
* TIM5 32BIT  used by time measurement system
* TIM2 3 4 reserved for encoder
* TIM6 7   reserved for interruption of timer
* TIM1 8   reserved for PWM generater
* TIM1 TIM8 TIM9 TIM10 TIM11   168M clock   others are 84 Mhz clock
***********************************************************************************************************************/

#ifndef BSPLIB_H
#define	BSPLIB_H

#include "stm32f4xx.h"
#include "nvic.h"
#include "delay.h"
#include "rtc.h"	 	
#include "wdg_wkup.h"
#include "flash.h"
#include "usart.h"
#include "adc_dac.h"
#include "timer.h"
#include "pwm_in.h" 
#include "pwm_out.h"
#include "encoder.h"
#include "i2c.h"
#include "can.h"
#include "spi.h"

/**********************************************************************************************************************/
//compilation function
//__asm void WFI_SET(void)
//{
//    WFI;
//}
////close all interruption
//__asm void INTX_DISABLE(void)
//{
//    CPSID   I
//            BX      LR
//}
////enable all interruption
//__asm void INTX_ENABLE(void)
//{
//    CPSIE   I
//            BX      LR
//}
////set stack address
////addr:address of stack top
//__asm void MSR_MSP(u32 addr)
//{
//    MSR MSP, r0 			//set Main Stack value
//            BX r14
//}
/**********************************************************************************************************************/

#endif //#ifndef BSPLIB_H




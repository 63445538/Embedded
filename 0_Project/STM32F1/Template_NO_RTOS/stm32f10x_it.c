/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName:
* Contact:  QQ Exchange Group -- 521037187
* Version:  V2.0
*
* LICENSING TERMS:
* The Hands Free is licensed generally under a permissive 3-clause BSD license.
* Contributions are requiredto be made under the same license.
*
* History:
* <author>      <time>      <version>      <desc>
*
* Description:
***********************************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include "main_includes.h"
#include "stm32f10x_it.h"

extern "C" void USART1_IRQHandler(void)
{
    unsigned char data;
#if SYSTEM_SUPPORT_OS == 1
    OSIntEnter();
#endif

    if(USART1->SR&(1<<5))//接收到数据
    {
        data=USART1->DR;
        USART_ClearITPendingBit(USART1, USART_IT_RXNE);   //清除中断标志位
    }

#if SYSTEM_SUPPORT_OS == 1
    OSIntExit();
#endif

}

extern "C" void USART2_IRQHandler(void)
{
    unsigned char data;
#if SYSTEM_SUPPORT_OS == 1
    OSIntEnter();
#endif

    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {
        data = USART_ReceiveData(USART2);
        USART_ClearITPendingBit(USART2, USART_IT_RXNE);  //清除中断标志位
    }

#if SYSTEM_SUPPORT_OS == 1
    OSIntExit();
#endif

}

extern "C" void USART3_IRQHandler(void)
{
    unsigned char data;
#if SYSTEM_SUPPORT_OS == 1
    OSIntEnter();
#endif

    if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
    {
        data = USART_ReceiveData(USART2);
        //gps_nmea.GPS_Usart_IRQ( USART_ReceiveData(USART3) ) ;
        USART_ClearITPendingBit(USART3, USART_IT_RXNE); //清除中断标志位
    }

#if SYSTEM_SUPPORT_OS == 1
    OSIntExit();
#endif

}


extern "C" void TIM5_IRQHandler(void)
{

#if SYSTEM_SUPPORT_OS == 1
    OSIntEnter();
#endif

    if(TIM_GetITStatus(TIM5 , TIM_IT_Update)== SET  )	   //检测是否发生溢出更新事件
    {
        TIM_ClearITPendingBit(TIM5 , TIM_FLAG_Update);     //清除中断标志位
    }

#if SYSTEM_SUPPORT_OS == 1
    OSIntExit();
#endif

}

extern "C" void TIM6_IRQHandler(void)
{

#if SYSTEM_SUPPORT_OS == 1
    OSIntEnter();
#endif

    if(TIM_GetITStatus(TIM6 , TIM_IT_Update)== SET  )	   //检测是否发生溢出更新事件
    {
        system_data.cnt_1ms++;
        system_data.cnt_2ms++;
        system_data.cnt_5ms++;
        system_data.cnt_10ms++;
        system_data.cnt_20ms++;
        system_data.cnt_50ms++;
        TIM_ClearITPendingBit(TIM6 , TIM_FLAG_Update);     //清除中断标志位
    }

#if SYSTEM_SUPPORT_OS == 1
    OSIntExit();
#endif

}

#ifdef __cplusplus
}
#endif

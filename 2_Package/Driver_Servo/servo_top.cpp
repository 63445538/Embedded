/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: robot_wheel_config.h
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
* Description:
*
***********************************************************************************************************************/
#include "servo_top.h"

ServoTop hf_head;

#define PITCH_OFFSET  512
#define PITCH_RANGE  30
#define YAW_OFFSET    512
#define YAW_RANGE  80

//extern "C"  void USART3_IRQHandler(void)
//{
//    unsigned char data;
//#if SYSTEM_SUPPORT_OS == 1
//    OSIntEnter();
//#endif
//    if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
//    {
//        data=USART_ReceiveData(USART3);
//        hf_head.gbpRxInterruptBuffer[hf_head.gbRxBufferWritePointer++] = data;
//        USART_ClearITPendingBit(USART3,USART_IT_RXNE);  //clear interrupt flag
//    }
//#if SYSTEM_SUPPORT_OS == 1
//    OSIntExit();
//#endif
//}

void ServoTop::init(void)
{
    axServoInit();
}

void ServoTop::headTopCall(void)
{

    if(first_call==0)
    {
        first_call=1;
        getServoConnective();
        axSendPosition(1, PITCH_OFFSET, 0x50);
        axSendPosition(2, YAW_OFFSET , 0x50);
    }
    else
    {
        if(set_head_state_renew == 1 )
        {
            set_head_state_renew = 0;
            if(expect_head_pitch >= PITCH_RANGE) expect_head_pitch=PITCH_RANGE;
            if(expect_head_pitch <= -PITCH_RANGE) expect_head_pitch=-PITCH_RANGE;
            if(expect_head_yaw >= YAW_RANGE) expect_head_pitch=YAW_RANGE;
            if(expect_head_yaw <= -YAW_RANGE) expect_head_pitch=-YAW_RANGE;
            setState(expect_head_pitch , expect_head_yaw);
        }
        if(read_head_state_renew == 1 )
        {
            read_head_state_renew = 0;
            getState(&measure_head_pitch , &measure_head_yaw);
        }
    }
}

void ServoTop::setState(float pitch , float yaw)
{
    unsigned short int set_pitch, set_yaw;
    set_pitch=-(pitch/300)*1024+PITCH_OFFSET;
    set_yaw=(yaw/300)*1024+YAW_OFFSET;
    axSendPosition(1, set_pitch , 0x50);
    axSendPosition(2, set_yaw , 0x50);
}

void ServoTop::getState(float* pitch , float* yaw)
{
    //	unsigned short int read_pitch , read_yaw;
    //  read_pitch = axReadPosition(1);
    //	read_yaw = axReadPosition(2);
}

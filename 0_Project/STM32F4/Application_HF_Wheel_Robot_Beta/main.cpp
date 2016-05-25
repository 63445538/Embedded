/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: main.c
* Contact:  QQ Exchange Group -- 521037187
* Version:  V2.0
*
* LICENSING TERMS:
* The Hands Free is licensed generally under a permissive 3-clause BSD license.
* Contributions are requiredto be made under the same license.
*
* History:
* <author>      <time>      <version>      <desc>
* mawenke      2015.10.1    V1.0          creat this file
*s
* Description:   
***********************************************************************************************************************/
		
#include "main_includes.h"

void System_Init(void)
{
    //SCB->VTOR = FLASH_BASE | 0x10000;  //Bootloader
    //INTX_DISABLE();  //close all interruption

    HF_BSP_Init();

    motor_top.motorTopInit();

    hf_head.axServoInit();

    hands_free_robot.robotWheelTopInit();

    sbus.sbusInit();

    IMU_Top_Init();

    //INTX_ENABLE();	 //enable all interruption

    printf("app start \r\n");

}
  
int main(void)
{
    System_Init();
    while(1)
    {

        if(usart1_queue.emptyCheck()==0){
            hf_link_pc_node.byteAnalysisCall(usart1_queue.getData());
        }

        if ( system_data.cnt_1ms >= 1 )      // 1000hz
        {
            system_data.cnt_1ms=0;
            IMU_Top_Call();					         // stm32f4 -- 631us(fpu)
        }
        if ( system_data.cnt_2ms >= 2 )      // 500hz
        {
            system_data.cnt_2ms=0;
        }
        if ( system_data.cnt_5ms >= 5 )      // 200hz
        {
            system_data.cnt_5ms=0;
        }
        if ( system_data.cnt_10ms >= 10 )   // 100hz
        {
            system_data.cnt_10ms=0;
            HF_BSP_Cycle_Call();            // need time stm32f1  35us
        }
        if ( system_data.cnt_20ms >= 20 )   // 50hz
        {
            system_data.cnt_20ms = 0 ;
            motor_top.motorTopCall();       //motor speed control
        }
        if ( system_data.cnt_50ms >= 50 )   // 20hz
        {
            system_data.cnt_50ms = 0 ;
            hf_head.headTopCall();
            hands_free_robot.robotWheelTopCall();    //robot control interface
            HF_Set_Led_State(0,2);
        }

    }

    return 0;
}



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
*
* Description:   
***********************************************************************************************************************/

#include "main_includes.h"

void constructorInit(void)
{
    board = Board();
	  Ultrasonic = ULTRASONIC();
    my_robot = RobotAbstract();
    motor_top = MotorTop();
    //robot_head = HeadAX();
    hands_free_robot = RobotWheel();
    //sbus = SBUS();
    imu = IMU();
    usart1_queue = Queue();
    hf_link_pc_node =  HFLink(0x11,0x01,&my_robot);
    hf_link_node_pointer=&hf_link_pc_node;
}

void systemInit(void)
{
#ifdef BOOTLOADER_ENABLE
    SCB->VTOR = FLASH_BASE | 0x4000;  //16k Bootloader
#endif
    //INTX_DISABLE();  //close all interruption
    board.boardBasicInit();
    motor_top.motorTopInit(3 , 1560 , 0.02 , 0);
    //robot_head.axServoInit();
    hands_free_robot.robotWheelTopInit();
    //sbus.sbusInit();
    imu.topInit(1,1,1,0,0,0);
		Ultrasonic.Ultra_Init(1);
	  board.analogServoInterfaceInit();
    //INTX_ENABLE();	 //enable all interruption
    printf("app start \r\n");
}

int main(void)
{	 	
//		float temp;
    constructorInit();
    systemInit();
//		int i = 1500;
    while(1)
    {

        if(usart1_queue.emptyCheck()==0){
            hf_link_pc_node.byteAnalysisCall(usart1_queue.getData());
        }
        if ( board.cnt_1ms >= 1 )      // 1000hz
        {
            board.cnt_1ms=0;
            imu.topCall();             // stm32f4 -- 631us(fpu)
        }
        if ( board.cnt_2ms >= 2 )      // 500hz
        {
            board.cnt_2ms=0;
        }
        if ( board.cnt_5ms >= 5 )      // 200hz
        {
            board.cnt_5ms=0;
        }
        if ( board.cnt_10ms >= 10 )    // 100hz
        {
            board.cnt_10ms=0;
            board.boardBasicCall();    // need time stm32f1  35us
        }
        if ( board.cnt_20ms >= 20 )    // 50hz
        {
            board.cnt_20ms = 0 ;
            motor_top.motorTopCall();  //motor speed control
//					  float temp_cpu;
//						temp_cpu = my_robot.robot_system_info.system_time;
//					  temp_cpu = my_robot.robot_system_info.cpu_temperature;
//					  my_robot.robot_system_info.cpu_usage = 1;
        }
        if ( board.cnt_50ms >= 50 )    // 20hz
        {
            board.cnt_50ms = 0 ;
            //robot_head.headTopCall();
            hands_free_robot.robotWheelTopCall();  //robot control interface
//            board.setLedState(0,2);
					  //motor_top.motorTest();
        }
				if ( board.cnt_500ms >= 500 )    // 2hz
        {		
            board.cnt_500ms = 0 ;
            //robot_head.headTopCall();
					  //board.debugPutChar(0x01);
            board.setLedState(0,2);
				
					  board.analogServoSetPWM(1,1250);
//					i = i +100;
//					if(i == 2000)
//					{i=1500;}
//						printf("%d\n",i);
					  //hf_link_pc_node.setCommandAnalysis(SET_MOTOR_SPEED , (unsigned char *)&my_robot.expect_motor_speed, sizeof(my_robot.expect_motor_speed));
            //hf_link_pc_node.readCommandAnalysis(READ_MOTOR_SPEED , (unsigned char *)&my_robot.measure_motor_speed , sizeof(my_robot.measure_motor_speed));					
//					  temp = Ultrasonic.Ultra_Ranging(1);
//						printf("%f\n",temp);
				}

    }

    return 0;
}



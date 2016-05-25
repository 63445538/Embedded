/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: motor_config.h
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

#ifndef MOTOR_CONFIG_H
#define MOTOR_CONFIG_H

#include "main_config.h"
#include "BSP_TOP.h"

/***********************************************************************************************************************
this is a motor simulator of handsfree ,if you don't have real robot or real motor , you can use it
and you an use it for
: practice motor pid control , validation your control algorithm
: established virtual robot model , and connect to ROS, you can see the virtual robot run in the RVIZ
  this means you only need a stm32 board for practice ros
: use it for establish PC software,debug communications
***********************************************************************************************************************/

#define  SYSTEM_SUPPORT_MOTOR_SIMULATION  0u
#if  SYSTEM_SUPPORT_MOTOR_SIMULATION > 0u
#define SIMULATION_MAX_ANGEL_SPEED  3000   //set the max speed for virtual motor degrees/s
#define SIMULATION_MOTOR_CURVE      1      // set the virtual motor's curve  1 : linear
#endif

#define  MOTOR_PWM_MAX      5000     //set the max value for pwm
#define  MOTOR_DEAD_ZONE    5        //when the pwm in this zone , the motor disable

/***********************************************************************************************************************
motor's parameters
***********************************************************************************************************************/        
#define  MOTOR_EN_NUM  3             //the motor's num of yor need to control
#define  MOTOR_PID_T        0.02f    //the interval time of  motor pid control  the unit is second
#define  MOTOR_ENCODER_NUM  1560.0f  //the encoder sensor count when the  motor turning one circle

#endif  // #ifndef MOTOR_CONFIG_H


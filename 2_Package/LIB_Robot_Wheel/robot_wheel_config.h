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

#ifndef ROBOT_WHEEL_CONFIG_H
#define ROBOT_WHEEL_CONFIG_H

#include "main_config.h"
#include "BSP_TOP.h"

#ifndef LIB_ROBOT_WHEEL
#error "!!! the LIB_ROBOT_WHEEL package must dependent on DRIVER_MOTOR package at least"
#endif

#ifdef  DRIVER_SERVO
#include "servo_top.h"
#endif

#ifdef DRIVER_MOTOR
#include "motor_top.h"
#endif

#ifdef DRIVER_IMU
#define  COORD_CALC_IMU_EN  0    ////use the IMU data to calculating coordinates
#include "imu_top.h"
#endif

#include "robot_abstract.h"

#define  PI_   3.141592653f

#endif    // #ifndef ROBOT_WHEEL_CONFIG_H


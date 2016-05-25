/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: main_config.h
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
* Description:   syetem include  file
***********************************************************************************************************************/
#ifndef MAIN_INCLUDES_H
#define MAIN_INCLUDES_H

/*******************************************************processor.h****************************************************/
#include "BSP_TOP.h"

/******************************************************package.h*******************************************************/
#ifdef LIB_COMMON
#include "queue.h"
#endif

#ifdef LIB_ROBOT_ABSTRACT
#include "robot_abstract.h"
#endif

#ifdef LIB_MATH
#include "base_math_top.h"
#endif

#ifdef DRIVER_IMU
#include "imu_top.h"
#endif

#ifdef DRIVER_MOTOR
#include "motor_top.h"
#endif

#ifdef DRIVER_SERVO
#include "servo_top.h"
#endif

#ifdef LIB_ROBOT_WHEEL
#include "robot_wheel_top.h"
#endif

#ifdef LIB_HF_LINK
#include "hf_link.h"
#endif

#ifdef LIB_SBUS_PPM
#include "sbus_ppm.h"
#endif
/**********************************************************************************************************************/


/*****************************************************OS.h*************************************************************/

//GUI/EMWIN
#if SYSTEM_SUPPORT_GUI == 1
#include "GUI.h"
#include "GUIDEMO.h"
#endif

//RTOS
#if SYSTEM_SUPPORT_OS==1
#include "includes.h"
#endif

/**********************************************************************************************************************/



/*****************************************************API.h************************************************************/


/**********************************************************************************************************************/


#endif // #ifndef MAIN_INCLUDES_H




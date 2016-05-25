/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: imu_config.h
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
* chenyingbing  2015.12.1   V1.6           update
* Description:  
*
***********************************************************************************************************************/

#ifndef __imu_config_H__
#define __imu_config_H__

#include "main_config.h"
#include "BSP_TOP.h"

#ifdef LIB_MATH
#include "base_math_top.h"
#endif

#define SYSTEM_SUPPORT_IMU_Debug     			  0u      	//是否使能printf 打印调试信息

//设备类
#if BSP_CFG_I2C_EN > 0u
#define SYSTEM_SUPPORT_IMU_I2C       			  1u     		//是否使能IMUI2C接口
#define SIMULAT_I2C_ID_IMU					     	  1			    //模拟I2C1
#endif

#define SYSTEM_SUPPORT_IMU_MPU6050   				1u     		//是否使能3轴加速计 和 三轴陀螺仪 MPU6050  1使能 0不使能  

#define SYSTEM_SUPPORT_IMU_BMP085    				0u      	//是否使能气压计  1使能 0不使能  

#define SYSTEM_SUPPORT_IMU_HMC5883l  				1u      	//是否使能磁力计HMC5883l 1使能 0不使能  

#define SYSTEM_SUPPORT_IMU_GPS       				0u        //是否使能GPS   默认使用usart3


// 算法类
#define SYSTEM_SUPPROT_FUSION_ARITHMETIC		    1u		//是否使能IMU融合算法

#if SYSTEM_SUPPROT_FUSION_ARITHMETIC > 0u

#if (SYSTEM_SUPPORT_IMU_I2C&&(SYSTEM_SUPPORT_IMU_MPU6050||SYSTEM_SUPPORT_IMU_HMC5883l)) > 0
#define ACTIVE_CALCULATE_MESANGLE						1u		  	//动态 计算加速度计/磁罗盘 测量角度
#endif

#if (SYSTEM_SUPPORT_IMU_I2C&&SYSTEM_SUPPORT_IMU_MPU6050&&SYSTEM_SUPPORT_IMU_HMC5883l) > 0
#define ARITHMETIC_MPUHMC5883_EGyroCorrect	1u				//使能 基于 叉积误差修正的融合算法 > Yaw
#endif

#if (SYSTEM_SUPPORT_IMU_I2C&&SYSTEM_SUPPORT_IMU_MPU6050) > 0
#define ARITHMETIC_MPU6050_EXTENDEDKALMAN		1u				//使能 基于 加速度计陀螺仪的扩展卡尔曼滤波融合算法 > Pitch Roll
#endif

#endif

// 调试算法类
#define	HMC_Correct_X 			-0.11f	    //HMC矫正值X
#define	HMC_Correct_Y 			 0.08f		  //HMC矫正值Y
#define HMC_Correct_Z 			-0.48f	    //HMC矫正值Z

#define K_Amplify_AccCov	     300.0f 	//ACC协方差增益
#define K_Amplify_GyroCov 		 0.1f	  	//GYRO协方差增益

typedef float IPType;

#endif  //__imu_config_H__



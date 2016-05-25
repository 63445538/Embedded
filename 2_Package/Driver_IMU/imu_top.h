#ifndef __imu_top_H__
#define __imu_top_H__

#include "imu_config.h"

#if SYSTEM_SUPPORT_IMU_I2C > 0u	

#if SYSTEM_SUPPORT_IMU_MPU6050  > 0u
#include "imu_mpu6050_driver.h"
#endif

#if SYSTEM_SUPPORT_IMU_BMP085  > 0u
#include "imu_bmp085_driver.h"
#endif

#if SYSTEM_SUPPORT_IMU_HMC5883l  > 0u
#include "imu_hmc5883l_driver.h"
#endif

#if SYSTEM_SUPPROT_FUSION_ARITHMETIC  > 0u
#include "imu_top_arithmetic_model.h"
#include "imu_arithmetic_kalman.h"
#endif

#endif    //#if SYSTEM_SUPPORT_IMU_I2C > 0u	

#if SYSTEM_SUPPORT_IMU_GPS  > 0u
#include "imu_gps_driver.h"
#endif

void IMU_Top_Init(void);    		//和IMU有关的模拟IIC接口  各传感器的初始化程序
void IMU_Top_Call(void);    		//1ms调用一次   不断更新IMU数据

#endif  //#ifndef __imu_top_H__


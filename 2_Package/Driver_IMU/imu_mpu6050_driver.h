#ifndef __imu_mpu6050_driver_H__
#define __imu_mpu6050_driver_H__

#include "imu_config.h"

#define GYRO_OFFSET_ENALBE  1           //是否使能陀螺数据的0漂读取       0 否  1是
#define ACC_OFFSET_ENALBE   1           //是否使能加速计数据的0漂读取     0 否  1是   

#define FILTER_ACC_Long				100				//加速计长滑动窗口滤波窗口大小			2ms*100 = 200ms
#define FILTER_ACC_Long_Avr		    0.01f
#define FILTER_ACC_Short			25				//加速计短滑动窗口滤波窗口大小			2ms*25 = 50ms
#define FILTER_ACC_Short_Avr	    0.04f

#define FILTER_GYRO_Long			10				//陀螺仪长滑动窗口滤波窗口大小			2ms*10 = 20ms
#define FILTER_GYRO_Long_Avr	    0.1f
#define FILTER_GYRO_Short			5			    //陀螺仪短滑动窗口滤波窗口大小			2ms*5 = 10ms
#define FILTER_GYRO_Short_Avr	    0.2f

typedef struct MPU_INT16_XYZ{
    short int  X;
    short int  Y;
    short int  Z;} MPU_INT16_XYZ;

typedef struct MPU_FLOAT_XYZ{
    float X;
    float Y;
    float Z;}MPU_FLOAT_XYZ;

typedef struct MPU_FLOAT_PRY{
    float Pitch;
    float Rool;
    float Yaw;}MPU_FLOAT_PRY;

class MPU6050
{

public:
    MPU6050(void);
    void MPU6050_Init(void);                        	//MPU6050初始化，传入参数：采样率，低通滤波频率
    void MPU6050_Check(void);							//MPU6050设备检查 更新 Mpu6050_State
    void MPU6050_Data_Update(void);                 	//need time stm32f1  380us

    unsigned char   GYRO_OFFSET_OK;   								//零漂还没有读取的标志0  已读取1
    unsigned char   ACC_OFFSET_OK;    								//零漂误差还没有读取的标志0  已读取1
    unsigned char 	Device_State;									//Mpu6050设备状态标志位 1正常在位  0非正常

    MPU_FLOAT_XYZ   ACC_Normal,GYRO_Normal;		    		        //瞬时acc和gryo的归一化数据
    MPU_FLOAT_XYZ   ACC_Normal_LongFilter,ACC_Normal_ShortFilter; 			//平均滤波后acc归一化数据
    MPU_FLOAT_XYZ 	GYRO_Normal_LongFilter,GYRO_Normal_ShortFilter;			//平均滤波后gyro归一化数据
    MPU_FLOAT_XYZ	ACC_Covariance_LongFliter,ACC_Covariance_ShortFliter;	//平均滤波里计算的acc的协方差
    MPU_FLOAT_XYZ	GYRO_Covariance;										//平均滤波里计算的gyro的协方差

private:
    unsigned char   Mpu_Rx_Buf[14];  //接收数据缓存区
    MPU_INT16_XYZ   GYRO_OFFSET,ACC_OFFSET;     	          //零漂
    MPU_INT16_XYZ 	MPU6050_ACC_LAST,MPU6050_GYRO_LAST;		  //最新一次减去0漂的值

    void MPU_delay_ms(unsigned int t);
    void MPU_Read_Buf(void);
    void MPU_Write_Byte(unsigned char REG_Address,unsigned char REG_data);
    unsigned char MPU_Read_Byte(unsigned char REG_Address);

    void MPU_Read_GYRO_Drift(void);   		    // 0漂读取
    void MPU_Read_ACC_Drift(void);   			// 0漂读取
    void MPU_Renew(void);        				// 更新一次数据读取     need time stm32f1  170us
    void MPU_GYRO_Normalize(void)  ; 			// 归一化数据 GYRO     need time stm32f1  20us
    void MPU_ACC_Normalize(void)  ;  			// 归一化数据  ACC     need time stm32f1  20us
    void MPU_GYRO_Normalize_Filter(void) ;      // 归一化数据  滤波     need time stm32f1  50us
    void MPU_ACC_Normalize_Filter(void) ;       // 归一化数据  滤波   	  need time stm32f1  50us

};

extern MPU6050 mpu6050;

#endif  //__imu_mpu6050_driver_H__


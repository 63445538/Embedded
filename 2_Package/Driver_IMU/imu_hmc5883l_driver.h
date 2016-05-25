#ifndef __imu_hmc5883l_driver_H__
#define __imu_hmc5883l_driver_H__

#include "imu_config.h"

typedef struct HMC_INT16_XYZ{
    short int  X;
    short int  Y;
    short int  Z;} HMC_INT16_XYZ;

typedef struct HMC_FLOAT_XYZ{
    float X;
    float Y;
    float Z;}HMC_FLOAT_XYZ;

class HMC5883L
{

public:

    HMC5883L(void);
    void HMC_Init(void);         				// HMC6050初始化
    void HMC_Check(void);
    void HMC_Data_Update(void);  				// 处理磁力计的数据  循环调用  建议20ms 运行一次  need time stm32f1 260us
    unsigned char 	Device_State;				// 	HMC设备状态标志位 1正常 0非常

    HMC_INT16_XYZ  HMC_LAST;    				// HMC测量的原始值
    HMC_FLOAT_XYZ  HMC_Normal;  				// HMC的归一化数据    单位  gauss
    HMC_FLOAT_XYZ  HMC_Correct;					// HMC的矫正值

private:
    unsigned char   HMC_Rx_Buf[6];     	// 接收数据缓存区

    void HMC_delay_ms(unsigned int t);
    void HMC_Read_Buf(void);
    void HMC_Write_Byte(unsigned char REG_Address,unsigned char REG_data);
    unsigned char HMC_Read_Byte(unsigned char REG_Address);
    void HMC_Get_Data(void) ;

};

extern HMC5883L hmc5883l;

#endif  //__imu_hmc5883l_driver_H__



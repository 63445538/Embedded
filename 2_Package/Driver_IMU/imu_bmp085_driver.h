#ifndef __imu_bmp085_driver_H__
#define __imu_bmp085_driver_H__

#include "imu_config.h"

class BMP085
{

public:

    BMP085(void);
    void BMP_Init(void);
    void BMP_Data_Update(void);   // need time stm32f1  140us

    float  Bmp_Temper;       //单位  度
    float  Bmp_Pressure;     //单位 PA
    float  Bmp_Altitude;     //海拔 单位 M

private:

    void BMP_delay_ms(unsigned int t);
    void BMP_Read_Buf(void);
    void BMP_Write_Byte(unsigned char REG_Address,unsigned char REG_data);
    unsigned char BMP_Read_Byte(unsigned char REG_Address);

    void BMP_Get_Data(void) ;

    //***BMP085使用
    short ac1;
    short ac2;
    short ac3;
    unsigned short ac4;
    unsigned short ac5;
    unsigned short ac6;
    short b1;
    short b2;
    short mb;
    short mc;
    short md;

};

extern BMP085 bmp085;

#endif  //__imu_bmp085_driver_H__



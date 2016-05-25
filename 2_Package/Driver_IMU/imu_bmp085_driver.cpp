/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: imu_bmp085_driver.h
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
* Description:  本文件封装了IMU中 气压计模块bmp085的驱动代码
*
***********************************************************************************************************************/

#include "imu_bmp085_driver.h"
#include "math.h"		

#if SYSTEM_SUPPORT_IMU_BMP085  > 0u

#define BMP085_ADDRESS  0xee	 //磁场传感器器件地址
#define   OSS 0	               //BMP085使用

BMP085 bmp085;

BMP085::BMP085()
{

}

/***********************************************************************************************************************
***                                                                                                                  ***
***                                           以下为底层接口函数                                                        ***
***                                                                                                                  ***
***********************************************************************************************************************/

void BMP085::BMP_delay_ms(unsigned int t)
{
    delay_ms(t);
}

void BMP085::BMP_Read_Buf(void)
{
    //unsigned char FastMode = 1;					//是否采用快速模式  1是  0否
    //Simulat_I2C_Read_Buf(SIMULAT_I2C_ID_IMU, BMP085_ADDRESS, BMP58X3_R_XM, BMP_Rx_Buf, 6, FastMode);
}

void BMP085::BMP_Write_Byte(unsigned char REG_Address,unsigned char REG_data)
{
    unsigned char FastMode = 1;						//是否采用快速模式  1是  0否
    Simulat_I2C_Write_Byte(SIMULAT_I2C_ID_IMU, BMP085_ADDRESS, REG_Address, REG_data, FastMode);
}  

unsigned char BMP085::BMP_Read_Byte(unsigned char REG_Address)
{
    unsigned char FastMode = 1;						//是否采用快速模式  1是  0否
    return( Simulat_I2C_Read_Byte(SIMULAT_I2C_ID_IMU, BMP085_ADDRESS, REG_Address, FastMode) );
}

/***********************************************************************************************************************
***                                                                                                                  ***
***                                                                                                                  ***
***                                                                                                                  ***
***********************************************************************************************************************/

//滑动平均滤波  算术平均滤波算法 输入最近采样值，返回最近NUM个值的平均值   NUM < 30 
#define AAF_NUM_MAX 30   
template<typename TYPE>  TYPE Arithmetic_Average_F ( TYPE new_value , unsigned short int NUM)   
{   
    static TYPE value_buf[AAF_NUM_MAX];
    static unsigned short int count;
    TYPE SUM;
    unsigned short int i;

    value_buf[count] = new_value;
    count++;
    if(count >= NUM) count=0;      //滑动更新窗口

    for ( i=0;i<NUM;i++)
    {
        SUM += value_buf[i];
    }
    return SUM/NUM;
} 

/***********************************************************************************************************************
* Function:     void BMP085::BMP_Get_Data(void)
*
* Scope:         private
*
* Description:   处理BMP的数据  循环调用  建议5ms 运行一次(200hz)   气压和温度更新速度各为100hz
*
* Arguments: 
* 
* Return: 
*
* Cpu_Time:     
*
* History:
* mawenke  2015.10.1   V1.0      creat
***********************************************************************************************************************/
void BMP085::BMP_Get_Data(void)
{
    static uint8_t BMP_i;
    static int ut;
    static int up;
    static int x1, x2, b5, b6, x3, b3, p;
    static unsigned int b4, b7;

    if(BMP_i==0)
    {
        BMP_i=1;
        ut = ( BMP_Read_Byte(0xF6) <<8 ) |  BMP_Read_Byte(0xF7);  //读取数据低八位
        BMP_Write_Byte(0xF4,0x34);        //选择了BMP085模块，写入读气压指令
    }
    else
    {
        BMP_i=0;
        up = ( BMP_Read_Byte(0xF6) <<8 ) |  BMP_Read_Byte(0xF7);
        up &= 0x0000FFFF;
        BMP_Write_Byte(0xF4,0x2E);    //选择了BMP085模块，写入读温度指令

        //以下为温补代码
        x1 = ((int)ut - ac6) * ac5 >> 15;
        x2 = ((int) mc << 11) / (x1 + md);
        b5 = x1 + x2;
        Bmp_Temper = (b5 + 8) >> 4;
        Bmp_Temper = Bmp_Temper/10 ;  //单位  度

        //****************

        b6 = b5 - 4000;
        x1 = (b2 * (b6 * b6 >> 12)) >> 11;
        x2 = ac2 * b6 >> 11;
        x3 = x1 + x2;
        b3 = (((int)ac1 * 4 + x3) + 2)/4;
        x1 = ac3 * b6 >> 13;
        x2 = (b1 * (b6 * b6 >> 12)) >> 16;
        x3 = ((x1 + x2) + 2) >> 2;
        b4 = (ac4 * (unsigned int) (x3 + 32768)) >> 15;
        b7 = ((unsigned int) up - b3) * (50000 >> OSS);
        if( b7 < 0x80000000)
            p = (b7 * 2) / b4 ;
        else
            p = (b7 / b4) * 2;
        x1 = (p >> 8) * (p >> 8);
        x1 = (x1 * 3038) >> 16;
        x2 = (-7357 * p) >> 16;
        Bmp_Pressure = p + ((x1 + x2 + 3791) >> 4); // 单位 PA

        //以下为计算海拔的代码 // 海拔 单位 M
        Bmp_Altitude = (float)44330.0 * (1 - pow( (float)( Bmp_Pressure / (float)101325 ) , (float)0.1903 ) );
        //	Bmp_Altitude = Arithmetic_Average_F ( Bmp_Altitude , 10);
    }
}

/***********************************************************************************************************************
* Function:    void BMP085::BMP_Init(void) 
*
* Scope:        public
*
* Description:   初始化 
*
* Arguments: 
* 
* Return: 
*
* Cpu_Time:     
*
* History:
* mawenke  2015.10.1   V1.0      creat
***********************************************************************************************************************/
void BMP085::BMP_Init(void) 
{

    ac1 = BMP_Read_Byte(0xAA);
    ac1 = (ac1<<8)|BMP_Read_Byte(0xAB);

    ac2 = BMP_Read_Byte(0xAC);
    ac2 = (ac2<<8)| BMP_Read_Byte(0xAD);

    ac3 = BMP_Read_Byte(0xAE);
    ac3 = (ac3<<8)| BMP_Read_Byte(0xAF);

    ac4 = BMP_Read_Byte(0xB0);
    ac4 = (ac4<<8)| BMP_Read_Byte(0xB1);

    ac5 = BMP_Read_Byte(0xB2);
    ac5 = (ac5<<8)| BMP_Read_Byte(0xB3);

    ac6 = BMP_Read_Byte(0xB4);
    ac6 = (ac6<<8)| BMP_Read_Byte(0xB5);

    b1 = BMP_Read_Byte(0xB6);
    b1 = (b1<<8)| BMP_Read_Byte(0xB7);

    b2 = BMP_Read_Byte(0xB8);
    b2 = (b2<<8)| BMP_Read_Byte(0xB9);

    mb = BMP_Read_Byte(0xBA);
    mb = (mb<<8)| BMP_Read_Byte(0xBB);

    mc = BMP_Read_Byte(0xBC);
    mc = (mc<<8)| BMP_Read_Byte(0xBD);

    md = BMP_Read_Byte(0xBE);
    md = (md<<8)| BMP_Read_Byte(0xBF);

    BMP_Write_Byte(0xF4,0x2E);    //选择了BMP085模块，写入读温度指令
}

/***********************************************************************************************************************
* Function:      void BMP085::BMP_Data_Update(void)
*
* Scope:         public
*
* Description:   处理BMP的数据  循环调用  建议5ms 运行一次(200hz)   气压和温度更新速度各为100hz
*
* Arguments: 
* 
* Return: 
*
* Cpu_Time:     stm32f1(140 us)  stm32f4+nofpu(unknow us) stm32f4+fpu(unknow us)
*
* History:
* mawenke  2015.10.1   V1.0      creat
***********************************************************************************************************************/
void BMP085::BMP_Data_Update(void)  
{
    BMP_Get_Data();
}

#endif


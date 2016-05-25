/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: imu_mpu6050_driver.h
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
* Description:  本文件封装了IMU 中三轴加速计和三轴陀螺仪模块mpu6050驱动代码
*
***********************************************************************************************************************/

#include "imu_mpu6050_driver.h"
#include "math.h"

#if SYSTEM_SUPPORT_IMU_MPU6050  > 0u

#define pi            3.1415926f
#define angletorad    0.01745329252f      //度到角度
#define radtoangle    57.295779513f	      //弧度到角度       

#define MPU6050_ADDRESS 0xD0        //mpu6050 address

#define	SMPLRT_DIV		0x19	
#define	CONFIG	        0x1A
#define	GYRO_CONFIG		0x1B	
#define	ACCEL_CONFIG	0x1C
#define	ACCEL_XOUT_H	0x3B
#define	ACCEL_XOUT_L	0x3C
#define	ACCEL_YOUT_H	0x3D
#define	ACCEL_YOUT_L	0x3E
#define	ACCEL_ZOUT_H	0x3F
#define	ACCEL_ZOUT_L	0x40
#define	TEMP_OUT_H		0x41
#define	TEMP_OUT_L		0x42
#define	GYRO_XOUT_H		0x43
#define	GYRO_XOUT_L		0x44
#define	GYRO_YOUT_H		0x45
#define	GYRO_YOUT_L		0x46
#define	GYRO_ZOUT_H		0x47
#define	GYRO_ZOUT_L		0x48
#define	PWR_MGMT_1		0x6B
#define	WHO_AM_I	    0x75


MPU6050 mpu6050;

MPU6050::MPU6050()
{
    Device_State = 0;
}

/***********************************************************************************************************************
***                                                                                                                  ***
***                                          以下为底层接口函数                                                         ***
***                                                                                                                  ***
***********************************************************************************************************************/

void MPU6050::MPU_delay_ms(unsigned int t)
{
    delay_ms(t);
}

void MPU6050::MPU_Read_Buf(void)
{
    unsigned char FastMode = 1;						//是否采用快速模式  1是  0否
    Simulat_I2C_Read_Buf(SIMULAT_I2C_ID_IMU, MPU6050_ADDRESS, ACCEL_XOUT_H, Mpu_Rx_Buf, 14, FastMode);
}

void MPU6050::MPU_Write_Byte(unsigned char REG_Address,unsigned char REG_data)
{
    unsigned char FastMode = 1;						//是否采用快速模式  1是  0否
    Simulat_I2C_Write_Byte(SIMULAT_I2C_ID_IMU, MPU6050_ADDRESS, REG_Address, REG_data, FastMode);
}  

unsigned char MPU6050::MPU_Read_Byte(unsigned char REG_Address)
{
    unsigned char FastMode = 1;						//是否采用快速模式  1是  0否
    return( Simulat_I2C_Read_Byte(SIMULAT_I2C_ID_IMU, MPU6050_ADDRESS, REG_Address, FastMode) );
}

/***********************************************************************************************************************
***                                                                                                                  ***
***                                                                                                                  ***
***                                                                                                                  ***
***********************************************************************************************************************/
/***********************************************************************************************************************
* Function:      void MPU6050::MPU_Read_GYRO_Drift(void)   
*
* Scope:         private
*
* Description:   读取mpu6050零漂
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
void MPU6050::MPU_Read_GYRO_Drift(void)     
{

    static int32_t tempgx=0,tempgy=0,tempgz=0;
    static uint16_t cnt_g=0;

    if(GYRO_OFFSET_OK != 1)
    {

        MPU_Read_Buf();
        MPU6050_GYRO_LAST.X=((((int16_t)Mpu_Rx_Buf[8]) << 8) | Mpu_Rx_Buf[9]);	 //陀螺仪数值
        MPU6050_GYRO_LAST.Y=((((int16_t)Mpu_Rx_Buf[10]) << 8) | Mpu_Rx_Buf[11]);
        MPU6050_GYRO_LAST.Z=((((int16_t)Mpu_Rx_Buf[12]) << 8) | Mpu_Rx_Buf[13]);
        if(cnt_g==0)
        {
            GYRO_OFFSET.X=0;
            GYRO_OFFSET.Y=0;
            GYRO_OFFSET.Z=0;
            tempgx = 0;
            tempgy = 0;
            tempgz = 0;
            cnt_g = 1;
            return ;
        }
        tempgx+= MPU6050_GYRO_LAST.X;
        tempgy+= MPU6050_GYRO_LAST.Y;
        tempgz+= MPU6050_GYRO_LAST.Z;
        if(cnt_g>=200)
        {
            GYRO_OFFSET.X=tempgx/cnt_g;
            GYRO_OFFSET.Y=tempgy/cnt_g;
            GYRO_OFFSET.Z=tempgz/cnt_g;
            GYRO_OFFSET_OK = 1;
            cnt_g=0;
            return ;
        }
        cnt_g++;

    }
}

/***********************************************************************************************************************
* Function:      void MPU6050::MPU_Read_ACC_Drift(void)     
*
* Scope:         private
*
* Description:   读取mpu6050零漂
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
void MPU6050::MPU_Read_ACC_Drift(void)    
{	
    static int32_t	tempax=0,tempay=0,tempaz=0;
    static uint16_t cnt_a=0;

    if(ACC_OFFSET_OK != 1)
    {

        MPU_Read_Buf();

        MPU6050_ACC_LAST.X=((((int16_t)Mpu_Rx_Buf[0]) << 8) | Mpu_Rx_Buf[1]);	  //加速度数值
        MPU6050_ACC_LAST.Y=((((int16_t)Mpu_Rx_Buf[2]) << 8) | Mpu_Rx_Buf[3]);
        MPU6050_ACC_LAST.Z=((((int16_t)Mpu_Rx_Buf[4]) << 8) | Mpu_Rx_Buf[5]);
        if(cnt_a==0)
        {
            ACC_OFFSET.X = 0;
            ACC_OFFSET.Y = 0;
            ACC_OFFSET.Z = 0;
            tempax = 0;
            tempay = 0;
            tempaz = 0;
            cnt_a = 1;
            return ;
        }
        tempax+= MPU6050_ACC_LAST.X;
        tempay+= MPU6050_ACC_LAST.Y;
        tempaz+= MPU6050_ACC_LAST.Z;
        if(cnt_a>=200)
        {
            ACC_OFFSET.X=tempax/cnt_a;
            ACC_OFFSET.Y=tempay/cnt_a;
            ACC_OFFSET.Z=tempaz/cnt_a-4096;
            ACC_OFFSET_OK = 1;
            cnt_a = 0;
            return ;
        }
        cnt_a++;

    }

}	


/***********************************************************************************************************************
* Function:      void MPU6050::MPU_Renew(void)      
*
* Scope:         private
*
* Description:   更新一次数据读取
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
void MPU6050::MPU_Renew(void)  
{

    MPU_Read_Buf();

    MPU6050_ACC_LAST.X=((((int16_t)Mpu_Rx_Buf[0]) << 8) | Mpu_Rx_Buf[1]) - ACC_OFFSET.X;	  //加速度数值
    MPU6050_ACC_LAST.Y=((((int16_t)Mpu_Rx_Buf[2]) << 8) | Mpu_Rx_Buf[3]) - ACC_OFFSET.Y;
    MPU6050_ACC_LAST.Z=((((int16_t)Mpu_Rx_Buf[4]) << 8) | Mpu_Rx_Buf[5]) - ACC_OFFSET.Z;
    //跳过温度ADC
    MPU6050_GYRO_LAST.X=((((int16_t)Mpu_Rx_Buf[8]) << 8) | Mpu_Rx_Buf[9]) - GYRO_OFFSET.X;	  //陀螺仪数值
    MPU6050_GYRO_LAST.Y=((((int16_t)Mpu_Rx_Buf[10]) << 8) | Mpu_Rx_Buf[11]) - GYRO_OFFSET.Y;
    MPU6050_GYRO_LAST.Z=((((int16_t)Mpu_Rx_Buf[12]) << 8) | Mpu_Rx_Buf[13]) - GYRO_OFFSET.Z;

}


/***********************************************************************************************************************
* Function:      void MPU6050::MPU_GYRO_Normalize(void)      
*
* Scope:         private
*
* Description:   陀螺仪数据归一化
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
void MPU6050::MPU_GYRO_Normalize(void)  
{
   // 250deg/s--131   500deg/s--65.5 1000deg/s--32.8 2000deg/s--16.4
    GYRO_Normal.X = (float)MPU6050_GYRO_LAST.X *0.061f;// /16.4f;
    GYRO_Normal.Y = (float)MPU6050_GYRO_LAST.Y *0.061f;// /16.4f;
    GYRO_Normal.Z = (float)MPU6050_GYRO_LAST.Z *0.061f;// /16.4f;

}

/***********************************************************************************************************************
* Function:      void MPU6050::MPU_ACC_Normalize(void)        
*
* Scope:         private
*
* Description:   加速计数据归一化
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
void MPU6050::MPU_ACC_Normalize(void)  
{
    ACC_Normal.X = (float)MPU6050_ACC_LAST.X*0.000244f;// /4096.0f;  //+-2g--16384 +-4g--8192 +-8g--4096 +-16g--2048
    ACC_Normal.Y = (float)MPU6050_ACC_LAST.Y*0.000244f;// /4096.0f;
    ACC_Normal.Z = (float)MPU6050_ACC_LAST.Z*0.000244f;// /4096.0f;

}


/***********************************************************************************************************************
* Function:      void MPU6050::MPU_GYRO_Normalize_Filter(void)         
*
* Scope:         private
*
* Description:    陀螺归一化数据低通滤波器
*
* Arguments: 
* 
* Return: 
*
* Cpu_Time:     
*
* History:
* mawenke  2015.10.1   V1.0      creat
* chenyingbing  2015.12.1   V1.6      update
***********************************************************************************************************************/
void MPU6050::MPU_GYRO_Normalize_Filter(void) 
{
    static 	unsigned char filter_cnt=0;
    static float GYRO_X_BUF[FILTER_GYRO_Long],GYRO_Y_BUF[FILTER_GYRO_Long],GYRO_Z_BUF[FILTER_GYRO_Long];

    static unsigned char i;
    static float temp_l1,temp_l2,temp_l3;
    static float temp_s1,temp_s2,temp_s3;

    temp_l1 = 0; temp_l2 = 0; temp_l3 = 0;
    temp_s1 = 0; temp_s2 = 0; temp_s3 = 0;

    //FIFO
    for(i=0;i<(FILTER_GYRO_Long-1);i++)
    {
        GYRO_X_BUF[i] = GYRO_X_BUF[i+1];
        GYRO_Y_BUF[i] = GYRO_Y_BUF[i+1];
        GYRO_Z_BUF[i] = GYRO_Z_BUF[i+1];

        //Long_Avr_Process
        temp_l1 += GYRO_X_BUF[i] * FILTER_GYRO_Long_Avr;
        temp_l2 += GYRO_Y_BUF[i] * FILTER_GYRO_Long_Avr;
        temp_l3 += GYRO_Z_BUF[i] * FILTER_GYRO_Long_Avr;

        //Short_Avr_Process
        if(i > (FILTER_GYRO_Long-FILTER_GYRO_Short)){
            temp_s1 += GYRO_X_BUF[i] * FILTER_GYRO_Short_Avr;
            temp_s2 += GYRO_Y_BUF[i] * FILTER_GYRO_Short_Avr;
            temp_s3 += GYRO_Z_BUF[i] * FILTER_GYRO_Short_Avr;
        }
    }

    //The New
    GYRO_X_BUF[FILTER_GYRO_Long-1] = GYRO_Normal.X;
    GYRO_Y_BUF[FILTER_GYRO_Long-1] = GYRO_Normal.Y;
    GYRO_Z_BUF[FILTER_GYRO_Long-1] = GYRO_Normal.Z;

    //Replenish the New
    temp_l1 += GYRO_X_BUF[FILTER_GYRO_Long-1] * FILTER_GYRO_Long_Avr;
    temp_l2 += GYRO_Y_BUF[FILTER_GYRO_Long-1] * FILTER_GYRO_Long_Avr;
    temp_l3 += GYRO_Z_BUF[FILTER_GYRO_Long-1] * FILTER_GYRO_Long_Avr;

    temp_s1 += GYRO_X_BUF[FILTER_GYRO_Long-1] * FILTER_GYRO_Short_Avr;
    temp_s2 += GYRO_Y_BUF[FILTER_GYRO_Long-1] * FILTER_GYRO_Short_Avr;
    temp_s3 += GYRO_Z_BUF[FILTER_GYRO_Long-1] * FILTER_GYRO_Short_Avr;

    //Get Avr
    GYRO_Normal_LongFilter.X = temp_l1;
    GYRO_Normal_LongFilter.Y = temp_l2;
    GYRO_Normal_LongFilter.Z = temp_l3;

    GYRO_Normal_ShortFilter.X = temp_s1;
    GYRO_Normal_ShortFilter.Y = temp_s2;
    GYRO_Normal_ShortFilter.Z = temp_s3;

    filter_cnt++;
    if(filter_cnt==FILTER_GYRO_Long)	filter_cnt=0;

    //由于gyro误差很小，也没必要去计算，赋予常值即可。单位化 1,1，1
    GYRO_Covariance.X = 1;
    GYRO_Covariance.Y = 1;
    GYRO_Covariance.Z = 1;
}

/***********************************************************************************************************************
* Function:      void MPU6050::MPU_ACC_Normalize_Filter(void)         
*
* Scope:         private
*
* Description:   加速计归一化数据低通滤波器
*
* Arguments: 
* 
* Return: 
*
* Cpu_Time:     
*
* History:
* mawenke  2015.10.1   V1.0      creat
* chenyingbing  2015.12.1   V1.6      update
***********************************************************************************************************************/
void MPU6050::MPU_ACC_Normalize_Filter(void) 
{
    static 	unsigned char filter_cnt=0;
    static float	ACC_X_BUF[FILTER_ACC_Long],ACC_Y_BUF[FILTER_ACC_Long],ACC_Z_BUF[FILTER_ACC_Long];

    static unsigned char i;
    static float temp_l1,temp_l2,temp_l3;
    static float temp_s1,temp_s2,temp_s3;

    static float cova_deal;
    static float cova_l1,cova_l2,cova_l3;
    static float cova_s1,cova_s2,cova_s3;

    temp_l1 = 0; temp_l2 = 0; temp_l3 = 0;
    temp_s1 = 0; temp_s2 = 0; temp_s3 = 0;

    //FIFO
    for(i=0;i<(FILTER_ACC_Long-1);i++)
    {
        ACC_X_BUF[i] = ACC_X_BUF[i+1];
        ACC_Y_BUF[i] = ACC_Y_BUF[i+1];
        ACC_Z_BUF[i] = ACC_Z_BUF[i+1];

        //Long_Avr_Process
        temp_l1 += ACC_X_BUF[i] * FILTER_ACC_Long_Avr;
        temp_l2 += ACC_Y_BUF[i] * FILTER_ACC_Long_Avr;
        temp_l3 += ACC_Z_BUF[i] * FILTER_ACC_Long_Avr;

        //Short_Avr_Process
        if(i > (FILTER_ACC_Long-FILTER_ACC_Short)){
            temp_s1 += ACC_X_BUF[i] * FILTER_ACC_Short_Avr;
            temp_s2 += ACC_Y_BUF[i] * FILTER_ACC_Short_Avr;
            temp_s3 += ACC_Z_BUF[i] * FILTER_ACC_Short_Avr;
        }
    }

    //The New
    ACC_X_BUF[FILTER_ACC_Long-1] = ACC_Normal.X;
    ACC_Y_BUF[FILTER_ACC_Long-1] = ACC_Normal.Y;
    ACC_Z_BUF[FILTER_ACC_Long-1] = ACC_Normal.Z;

    //Replenish the New
    temp_l1 += ACC_X_BUF[FILTER_ACC_Long-1] * FILTER_ACC_Long_Avr;
    temp_l2 += ACC_Y_BUF[FILTER_ACC_Long-1] * FILTER_ACC_Long_Avr;
    temp_l3 += ACC_Z_BUF[FILTER_ACC_Long-1] * FILTER_ACC_Long_Avr;

    temp_s1 += ACC_X_BUF[FILTER_ACC_Long-1] * FILTER_ACC_Short_Avr;
    temp_s2 += ACC_Y_BUF[FILTER_ACC_Long-1] * FILTER_ACC_Short_Avr;
    temp_s3 += ACC_Z_BUF[FILTER_ACC_Long-1] * FILTER_ACC_Short_Avr;

    //Get Avr
    ACC_Normal_LongFilter.X = temp_l1;
    ACC_Normal_LongFilter.Y = temp_l2;
    ACC_Normal_LongFilter.Z = temp_l3;

    ACC_Normal_ShortFilter.X = temp_s1;
    ACC_Normal_ShortFilter.Y = temp_s2;
    ACC_Normal_ShortFilter.Z = temp_s3;

    filter_cnt++;
    if(filter_cnt==FILTER_ACC_Long)	filter_cnt=0;

    //计算方差
    cova_l1 = 0; cova_l2 = 0; cova_l3 = 0;
    cova_s1 = 0; cova_s2 = 0; cova_s3 = 0;
    for(i=0;i<FILTER_ACC_Long;i++)
    {
        //Long_Avr_Process
        cova_deal = (ACC_X_BUF[i]-ACC_Normal_LongFilter.X);
        cova_l1 += cova_deal*cova_deal * FILTER_ACC_Long_Avr;
        cova_deal = (ACC_Y_BUF[i]-ACC_Normal_LongFilter.Y);
        cova_l2 += cova_deal*cova_deal * FILTER_ACC_Long_Avr;
        cova_deal = (ACC_Z_BUF[i]-ACC_Normal_LongFilter.Z);
        cova_l3 += cova_deal*cova_deal * FILTER_ACC_Long_Avr;

        //Short_Avr_Process
        if(i > (FILTER_ACC_Long-FILTER_ACC_Short)){
            cova_deal = (ACC_X_BUF[i]-ACC_Normal_ShortFilter.X);
            cova_s1 += cova_deal*cova_deal * FILTER_ACC_Short_Avr;
            cova_deal = (ACC_Y_BUF[i]-ACC_Normal_ShortFilter.Y);
            cova_s2 += cova_deal*cova_deal * FILTER_ACC_Short_Avr;
            cova_deal = (ACC_Z_BUF[i]-ACC_Normal_ShortFilter.Z);
            cova_s3 += cova_deal*cova_deal * FILTER_ACC_Short_Avr;
        }
    }

    cova_l1 = cova_l1;
    cova_l2 = cova_l2;
    cova_l3 = cova_l3;
    cova_s1 = cova_s1;
    cova_s2 = cova_s2;
    cova_s3 = cova_s3;

    ACC_Covariance_LongFliter.X = cova_l1;
    ACC_Covariance_LongFliter.Y = cova_l2;
    ACC_Covariance_LongFliter.Z = cova_l3;
    ACC_Covariance_ShortFliter.X = cova_s1;
    ACC_Covariance_ShortFliter.Y = cova_s2;
    ACC_Covariance_ShortFliter.Z = cova_s3;
}


/***********************************************************************************************************************
***                                                                                                                  ***
***                                  以下是外部调用接口函数   并和驱动隔离                                                 ***
***                                                                                                                  ***
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function:    void MPU6050::MPU6050_Init(void) 
*
* Scope:        public
*
* Description:   初始化 	MPU6050 以进入可用状态
*
* Arguments: 
* 
* Return: 
*
* Cpu_Time:     
*
* History:
* mawenke  2015.10.1   V1.0      creat
* chenyingbing  2015.12.1   V1.6      update
***********************************************************************************************************************/
void MPU6050::MPU6050_Init(void) 
{
    // 1000hz_sample_rate  42hzlpf
    MPU_Write_Byte(PWR_MGMT_1, 0x80); // 设备复位
    MPU_delay_ms(5);
    MPU_Write_Byte(PWR_MGMT_1, 0x01); //设置设备时钟源
    MPU_delay_ms(5);
    MPU_Write_Byte(CONFIG , 0x03);  //低通滤波 42hz
    MPU_delay_ms(5);
    MPU_Write_Byte(SMPLRT_DIV, 0x00);//1KHz sample rate,acc output rate is 1KHz,so is the gyro
    MPU_delay_ms(5);
    //2000deg/s for full scale range,without self-test   00<<3 250deg/s
    //01<<3 500deg/s  10<<3 1000deg/s 11<<3 2000deg/s
    MPU_Write_Byte(GYRO_CONFIG, 0x18);
    MPU_delay_ms(5);
    //+-8g for full scale range,without self-test  00<<3 2g  01<<3 4g  10<<3 8g 11<<3 16g
    MPU_Write_Byte(ACCEL_CONFIG, 0x10);
    MPU_delay_ms(5);

    MPU_Write_Byte(PWR_MGMT_1,0x00);		//进入工作状态
    MPU_Write_Byte(0X6A,0X00);					//不让MPU6050控制AUXI2C
    MPU_delay_ms(5);
    //MPU_Write_Byte(0X37,0X01);				//主控制器的I2C与AUXI2C直通
    MPU_Write_Byte(0x37,0x02);					//使能后面的hmc5883l
    MPU_delay_ms(5);

    MPU6050_Check();
#if SYSTEM_SUPPORT_IMU_Debug>0u
    if(mpu6050.Device_State){
        printf(" Mpu6050_Init Success ! \r\n");
    }else{
        printf(" Mpu6050_Init Failure ! \r\n");
    }
#endif

}

/***********************************************************************************************************************
* Function:    		void MPU6050::MPU6050_Check(void)
*
* Scope:        	public
*
* Description:   	设备检查 mpu6050.Device_State 1 设备有效 0 设备无效
*
* Arguments: 
* 
* Return: 
*
* Cpu_Time:     
*
* History:
*
* chenyingbing  2015.12.1   V1.6      creat
***********************************************************************************************************************/
void MPU6050::MPU6050_Check(void)
{
    if(MPU_Read_Byte(WHO_AM_I)==104)
    {
        Device_State = 1;
    }else{
        Device_State = 0;
    }
}


/***********************************************************************************************************************
* Function:      void MPU6050::MPU6050_Data_Update(void)
*
* Scope:         public
*
* Description:   MPU主函数，和外部的接口,周期性调用，建议2ms调用一次
*								#define FILTER_ACC_Long  	100		//加速计长滑动窗口滤波窗口大小			2ms*100 = 200ms
*								#define FILTER_ACC_Short	25		//加速计短滑动窗口滤波窗口大小			2ms*25 = 50ms
*
* Arguments: 
* 
* Return: 
*
* Cpu_Time:  stm32f4 -- 280us(fpu) s   
*
* History:
* mawenke  2015.10.1   V1.0      creat
* chenyingbing  2015.12.1   V1.6      update
***********************************************************************************************************************/
void MPU6050::MPU6050_Data_Update(void)
{
    static unsigned int MPU6050_i=0;
    static unsigned int Data_Update_i=0;

    if( MPU6050_i <= 500)     //上电开始前500次读的数据无效
    {
        MPU6050_i++;
        MPU_Renew();
        return;
    }
    Data_Update_i++;
#if GYRO_OFFSET_ENALBE == 1  //GYRO零漂
    if(GYRO_OFFSET_OK != 1) { MPU_Read_GYRO_Drift(); return;}
#endif
#if ACC_OFFSET_ENALBE == 1   //ACC零漂
    if(ACC_OFFSET_OK != 1) { MPU_Read_ACC_Drift(); return;}
#endif

    MPU_Renew();            	  //读取更新            			//stm32f1  170us	stm32f4	78us
    MPU_GYRO_Normalize(); 		  //陀螺数据归一化      			//stm32f1  20us		stm32f4 1us
    MPU_ACC_Normalize();  		  //加速计数据归一化    			//stm32f1  20us		stm32f4 1us

    MPU_ACC_Normalize_Filter();	  //归一化数据低通滤波器		//					stm32f4	 2us/16us
    MPU_GYRO_Normalize_Filter();  //陀螺归一化数据低通滤波器 	//					stm32f4	 2us
    if(Data_Update_i>=50)
    {
        Data_Update_i = 0;
        MPU6050_Check();
    }
}

#endif


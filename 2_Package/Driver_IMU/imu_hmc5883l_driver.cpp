/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: imu_hmc5883l_driver.h
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
* Description:  本文件封装了IMU中 三轴磁力计模块hmc5883l的驱动代码
*
***********************************************************************************************************************/

/***********************************************************************************************************************

  Refer the following application note for heading calculation.
  http://www.ssec.honeywell.com/magnetic/datasheets/lowcost.pdf
  ----------------------------------------------------------------------------------------
  atan2(y, x) is the angle in radians between the positive x-axis of a plane and the point
  given by the coordinates (x, y) on it.
  ----------------------------------------------------------------------------------------

  This sketch does not utilize the magnetic component Z as tilt compensation can not be done without an Accelerometer

  ----------------->y
  |
  |
  |
  |
  |
  |
 \/
  x



                     N 180
     125 NW  |  NE 180+45
                     |
    90  W----------E 270
                     |
     45  SW  |  SE 270+45
                     S 0

***********************************************************************************************************************/

#include "imu_hmc5883l_driver.h"
#include "math.h"

#if SYSTEM_SUPPORT_IMU_HMC5883l  > 0u

#define HMC5883L_ADDRESS  0x3C	//磁场传感器器件地址
#define HMC_POS_BIAS 1
#define HMC_NEG_BIAS 2

//HMC58X3 register map. For details see HMC58X3 datasheet
#define HMC58X3_R_CONFA 0x00
#define HMC58X3_R_CONFB 0x01
#define HMC58X3_R_MODE  0x02

#define HMC58X3_R_XM 0x03   //!< Register address for XM.
#define HMC58X3_R_XL 0x04   //!< Register address for XL.
#define HMC58X3_R_ZM 0x05   //!< Register address for ZM.
#define HMC58X3_R_ZL 0x06   //!< Register address for ZL.
#define HMC58X3_R_YM 0x07   //!< Register address for YM.
#define HMC58X3_R_YL 0x08   //!< Register address for YL.

#define HMC58X3_R_STATUS 0X09

#define HMC58X3_R_IDA 0X10
#define HMC58X3_R_IDB 0X11
#define HMC58X3_R_IDC 0X12

HMC5883L hmc5883l;

HMC5883L::HMC5883L()
{
    Device_State = 0;

    HMC_Correct.X = HMC_Correct_X;
    HMC_Correct.Y = HMC_Correct_Y;
    HMC_Correct.Z = HMC_Correct_Z;
}

/***********************************************************************************************************************
***                                                                                                                  ***
***                                           以下为底层接口函数                                                        ***
***                                                                                                                  ***
***********************************************************************************************************************/

void HMC5883L::HMC_delay_ms(unsigned int t)
{
    delay_ms(t);
}

void HMC5883L::HMC_Read_Buf(void)
{
    unsigned char FastMode = 1;						//是否采用快速模式  1是  0否
    Simulat_I2C_Read_Buf(SIMULAT_I2C_ID_IMU, HMC5883L_ADDRESS, HMC58X3_R_XM, HMC_Rx_Buf, 6, FastMode);
}

void HMC5883L::HMC_Write_Byte(unsigned char REG_Address,unsigned char REG_data)
{
    unsigned char FastMode = 1;						//是否采用快速模式  1是  0否
    Simulat_I2C_Write_Byte(SIMULAT_I2C_ID_IMU, HMC5883L_ADDRESS, REG_Address, REG_data, FastMode);
}  

unsigned char HMC5883L::HMC_Read_Byte(unsigned char REG_Address)
{
    unsigned char FastMode = 1;						//是否采用快速模式  1是  0否
    return( Simulat_I2C_Read_Byte(SIMULAT_I2C_ID_IMU, HMC5883L_ADDRESS, REG_Address, FastMode) );
}


/***********************************************************************************************************************
***                                                                                                                  ***
***                                                                                                                  ***
***                                                                                                                  ***
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function:      
*
* Scope:         
*
* Description:   
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
void HMC5883L::HMC_Get_Data(void)  
{

    HMC_LAST.X = HMC_Rx_Buf[0] << 8 | HMC_Rx_Buf[1]; //Combine MSB and LSB of X Data output register  -2048~~2047
    HMC_LAST.Z = HMC_Rx_Buf[2] << 8 | HMC_Rx_Buf[3]; //Combine MSB and LSB of Z Data output register
    HMC_LAST.Y = HMC_Rx_Buf[4] << 8 | HMC_Rx_Buf[5]; //Combine MSB and LSB of Y Data output register
    HMC_Normal.X = (float)(HMC_LAST.X*0.00435f);// /230;
    HMC_Normal.Z = (float)(HMC_LAST.Z*0.00435f);// /230;
    HMC_Normal.Y = (float)(HMC_LAST.Y*0.00435f);// /230;

    HMC_Normal.X += HMC_Correct.X;		//JZ
    HMC_Normal.Y += HMC_Correct.Y;		//JZ
    HMC_Normal.Z += HMC_Correct.Z;		//JZ
}

/***********************************************************************************************************************
* Function:    void HMC5883L::HMC_Init(void) 
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
void HMC5883L::HMC_Init(void) 
{
    //HMC_Write_Byte(0x00,0x60);   	    //配置寄存器A：系统默认
    HMC_Write_Byte(0x02,0x00);   		//模式寄存器： 连续测量模式
    HMC_Write_Byte(0x01,0xE0);   		//配置寄存器B：增益控制    +- 8.1Ga   增益230

    HMC_Check();
#if SYSTEM_SUPPORT_IMU_Debug>0u
    if(hmc5883l.Device_State){
        printf(" Hmc5883_Init Success ! \r\n");

    }else{
        printf(" Hmc5883_Init Failure ! \r\n");
    }
#endif
}

/***********************************************************************************************************************
* Function:    	void HMC5883L::HMC_Check(void) 
*
* Scope:        public
*
* Description: 	设备检查  hmc5883l.Device_State 1 设备有效 0 设备无效
*
* Arguments: 
* 
* Return: 
*
* Cpu_Time:     
*
* History:
* chenyingbing  2015.10.1   V1.0      creat
***********************************************************************************************************************/
void HMC5883L::HMC_Check(void)
{
    if(HMC_Read_Byte(0x01)==0xE0)
    {
        Device_State = 1;
    }else{
        Device_State = 0;
    }
}

/***********************************************************************************************************************
* Function:      void HMC5883L::HMC_Data_Update(void)
*
* Scope:         public
*
* Description:   处理磁力计的数据  循环调用  建议20ms 运行一次
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
void HMC5883L::HMC_Data_Update(void)  //need time stm32f1--260us  
{
    static unsigned int Data_Update_i=0;
    Data_Update_i++;
    HMC_Read_Buf();       //need time stm32f1--96us  stm32f4--43us
    HMC_Get_Data();       //need time stm32f1--40us  stm32f4--6us
    if(Data_Update_i>=5)
    {
        Data_Update_i = 0;
        HMC_Check();
    }
}

#endif


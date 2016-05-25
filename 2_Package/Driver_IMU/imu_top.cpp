/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: imu_top.cpp
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

#include "imu_top.h"

/***********************************************************************************************************************
* Function:      void IMU_Top_Init(void)
*
* Scope:         public
*
* Description:   IMU设备的初始化
*
* Arguments:
*
* Return:
*
* Cpu_Time:    
*
* History:
* mawenke       2015.10.1   V1.0           creat 
* chenyingbing  2015.12.1   V1.6           update
***********************************************************************************************************************/
void IMU_Top_Init(void)
{

#if SYSTEM_SUPPORT_IMU_I2C > 0u

    HF_Simulat_I2C_Init(SIMULAT_I2C_ID_IMU);

#if SYSTEM_SUPPORT_IMU_MPU6050  > 0u
    mpu6050.MPU6050_Init();
#endif
#if SYSTEM_SUPPORT_IMU_BMP085  > 0u
    bmp085.BMP_Init ();
#endif
#if SYSTEM_SUPPORT_IMU_HMC5883l  > 0u
    hmc5883l.HMC_Init();
#endif

#endif     //#if SYSTEM_SUPPORT_IMU_I2C > 0u

#if SYSTEM_SUPPORT_IMU_GPS  > 0u
    gps_nmea.GPS_Init();
#endif

}

/***********************************************************************************************************************
* Function:      void IMU_Top_Init(void)
*
* Scope:         public
*
* Description:   IMU设备数据更新    1ms调用一次 
*
* Arguments:
*
* Return:
*
* Cpu_Time:  stm32f1(unknow us)  stm32f4+nofpu(unknow us) stm32f4+fpu(631 us)   
*
* History:
* mawenke       2015.10.1   V1.0           creat 
* chenyingbing  2015.12.1   V1.6           update
***********************************************************************************************************************/
void IMU_Top_Call(void)
{
    static unsigned int imu_1=0,imu_2=0,imu_3=0,imu_4=0,imu_5=0;
    imu_1++;
    imu_2++;
    imu_3++;
    imu_4++;
    imu_5++;

#if SYSTEM_SUPPORT_IMU_I2C  > 0u

    if( imu_1 >= 2 ) //T=2ms
    {
        imu_1=0;

        //设备*****************************//
        mpu6050.MPU6050_Data_Update();   											// stm32f4--280us(fcu)

#if SYSTEM_SUPPROT_FUSION_ARITHMETIC > 0u

        // 通用	更新
        imu_arithmetic_model.Set_ModelInitial();	 							// stm32f4--2us(fcu) instantly > 45us
        imu_arithmetic_model.ModelCommanState_Update();							// stm32f4--35us(fpu)

        if(imu_arithmetic_model.Imu_Top_fusion_HavingInitial == 1)		           // 已初始化条件
        {
            imu_arithmetic_model.XState1_Predict(0.002f);							// stm32f4--54us(fpu)
            imu_arithmetic_model.XState2_Predict(0.002f);							// stm32f4--54us(fpu)

#if ARITHMETIC_MPU6050_EXTENDEDKALMAN > 0u
            // 算法1
            imu_arithmetic_model.ExtendedKalman_State_Update1();			// stm32f4--37us(fpu)
            imu_arithmetic_model.XState_KalmanFusionCall_Process1();	    // stm32f4--55us(fpu)

#endif

#if ARITHMETIC_MPUHMC5883_EGyroCorrect > 0u
            // 算法2
            imu_arithmetic_model.YawError_Correct_State_Update2();		// stm32f4--37us(fpu)
            imu_arithmetic_model.YawError_Correct_Process2();			// stm32f4--3us(fpu)

#endif

            // 接口变量更新
            imu_arithmetic_model.UpdateState_to_PortVariable();				// stm32f4--35us(fpu)

        }
#endif

    }

    if( imu_2 >= 5 ) //T=5ms
    {
        imu_2=0;

        //设备*****************************//
#if SYSTEM_SUPPORT_IMU_HMC5883l  > 0u
        hmc5883l.HMC_Data_Update();      											// stm32f4--50us
#endif

#if SYSTEM_SUPPORT_IMU_BMP085  > 0u
        bmp085.BMP_Data_Update ();
#endif
    }

    if( imu_3 >= 10 ) //T=10ms
    {
        imu_3 = 0;
    }

    if( imu_4 >= 25 ) //T=25ms
    {
        imu_4=0;
        if(mpu6050.Device_State && hmc5883l.Device_State){
            imu_arithmetic_model.Fusion_State = 1;
        }else{
            imu_arithmetic_model.Fusion_State = 0;
        }
#if SYSTEM_SUPPROT_FUSION_ARITHMETIC > 0u
        //普通量测
#if ACTIVE_CALCULATE_MESANGLE > 0u
        imu_arithmetic_model.GetAccHmc_MesAngle_dgree(2);							// stm32f4--9us(fcu)
#endif

#endif
    }

    if( imu_5 >= 50 ) //T=50ms
    {
        imu_5=0;

#if SYSTEM_SUPPORT_IMU_Debug > 0u

#if SYSTEM_SUPPORT_IMU_MPU6050  > 0u
        //printf("\r\n MPU6050姿态 pitch=%f rool=%f yaw=%f\r\n"
        //, mpu6050.ACC_Angel.Pitch , mpu6050.ACC_Angel.Rool , mpu6050.GYRO_Angel.Yaw);
#endif

#if SYSTEM_SUPPORT_IMU_BMP085  > 0u
        //printf("\r\n BMP数据  温度=%f 气压=%f 海拔=%f\r\n"
        //, bmp085.Bmp_Temper , bmp085.Bmp_Pressure , bmp085.Bmp_Altitude);
#endif

#if SYSTEM_SUPPORT_IMU_HMC5883l  > 0u
        //printf("\r %f\n",hmc5883l.HMC_Normal.X);
        //printf("%f %f %f \n",hmc5883l.HMC_Normal.X,hmc5883l.HMC_Normal.Y,hmc5883l.HMC_Normal.Z);
#endif

#if SYSTEM_SUPPROT_FUSION_ARITHMETIC > 0u
        //printf(" %d \n",imu_arithmetic_model.Fusion_State);
        printf("%lf %lf %lf \n",imu_arithmetic_model.Fus_Angle.pitch
               ,imu_arithmetic_model.Fus_Angle.roll,imu_arithmetic_model.Fus_Angle.yaw);
        //printf("%lf %lf %lf \n",imu_arithmetic_model.AccHmcMes_Angle_dgree.pitch
        //, imu_arithmetic_model.AccHmcMes_Angle_dgree.roll
, imu_arithmetic_model.AccHmcMes_Angle_dgree.yaw);
        //printf("%f %f %f \n",imu_arithmetic_model.Error_Ut[0]
        //,imu_arithmetic_model.Error_Ut[1],imu_arithmetic_model.Error_Ut[2]);
        //printf("%lf %lf %lf \n",imu_arithmetic_model.ControlVector_Position.pitch
        //,imu_arithmetic_model.ControlVector_Position.roll,imu_arithmetic_model.ControlVector_Position.yaw);
        //printf("%lf %lf %lf \n",imu_arithmetic_model.ControlVector_Velocity.pitch
        //,imu_arithmetic_model.ControlVector_Velocity.roll,imu_arithmetic_model.ControlVector_Velocity.yaw);
#endif

#endif  //#if SYSTEM_SUPPORT_IMU_Debug > 0u

    }

#endif  //#if SYSTEM_SUPPORT_IMU_I2C  > 0u
}


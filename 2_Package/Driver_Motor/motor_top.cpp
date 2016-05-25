/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: motor_top.c
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
* Description: The file defined a Class for motor control ， you can use it Conveniently and modify a litter 
*              for a different circuit board
***********************************************************************************************************************/

#include "motor_top.h"

MotorTop motor_top;

/***********************************************************************************************************************
* Function:     void MotorTop::motor_set_pwm(unsigned char motor_id , float pid_out)
*
* Scope:        private
*
* Description:  The underlying interface of motor control，you need to modify it for a different circuit board
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:
***********************************************************************************************************************/

void MotorTop::motor_set_pwm(unsigned char motor_id , float pid_out)
{

    if( motor_id ==1 ){
        if( enable_m1 !=1 )
        {
            MOTOREN1_OFF();     //motor disable
            Pwm_Set_TIM1_CCR1(0);
            Pwm_Set_TIM1_CCR2(0);
            return;
        }
        else if( ( pid_out < MOTOR_DEAD_ZONE ) && (pid_out > -MOTOR_DEAD_ZONE) )   // enter dead line
        {
            MOTOREN1_OFF();     //motor disable
            Pwm_Set_TIM1_CCR1(0);
            Pwm_Set_TIM1_CCR2(0);
            return;
        }
        else if( pid_out > 0) {
            MOTOREN1_ON();   //motor enable
            Pwm_Set_TIM1_CCR1((unsigned short int)pid_out);
            Pwm_Set_TIM1_CCR2(0);
            return;
        }
        else{
            MOTOREN1_ON();   //motor enable
            Pwm_Set_TIM1_CCR1(0);
            Pwm_Set_TIM1_CCR2((unsigned short int)-pid_out);
            return;
        }
    }
    else if(motor_id == 2 ){
        if( enable_m2 !=1 )
        {
            MOTOREN2_OFF();
            Pwm_Set_TIM1_CCR3(0);
            Pwm_Set_TIM1_CCR4(0);
            return;
        }
        else if( ( pid_out < MOTOR_DEAD_ZONE ) && (pid_out > -MOTOR_DEAD_ZONE) )   // enter dead line
        {
            MOTOREN2_OFF();
            Pwm_Set_TIM1_CCR3(0);
            Pwm_Set_TIM1_CCR4(0);
            return;
        }
        else if( pid_out > 0) {
            MOTOREN2_ON();
            Pwm_Set_TIM1_CCR3((unsigned short int)pid_out);
            Pwm_Set_TIM1_CCR4(0);
            return;
        }
        else{
            MOTOREN2_ON();
            Pwm_Set_TIM1_CCR3(0);
            Pwm_Set_TIM1_CCR4((unsigned short int)-pid_out);
            return;
        }
    }
    else if(motor_id ==3 ){
        if( enable_m3 !=1 )
        {
            MOTOREN3_OFF();
            Pwm_Set_TIM12_CCR1(0);
            Pwm_Set_TIM12_CCR2(0);
            return;
        }
        else if( ( pid_out < MOTOR_DEAD_ZONE ) && (pid_out > - MOTOR_DEAD_ZONE) )   // enter dead line
        {
            MOTOREN3_OFF();
            Pwm_Set_TIM12_CCR1(0);
            Pwm_Set_TIM12_CCR2(0);
            return;
        }
        else if( pid_out > 0) {
            MOTOREN3_ON();
            Pwm_Set_TIM12_CCR1((unsigned short int)pid_out);
            Pwm_Set_TIM12_CCR2(0);
            return;
        }
        else{
            MOTOREN3_ON();
            Pwm_Set_TIM12_CCR1(0);
            Pwm_Set_TIM12_CCR2((unsigned short int)-pid_out);
            return;
        }
    }
}	


/***********************************************************************************************************************
* Function:     void MotorTop::motorTopInit(void)
*
* Scope:        public
*
* Description:  motor control interface init
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:
***********************************************************************************************************************/
void MotorTop::motorTopInit(void)
{

    GPIO_InitTypeDef  GPIO_InitStructure;
    GPIO_StructInit(&GPIO_InitStructure);

#if HARDWARE_PLATFORM== 1  //if the MCU is STM32F1 Series

#endif

#if HARDWARE_PLATFORM== 4  //if the MCU is STM32F4 Series

#if  SYSTEM_SUPPORT_MOTOR_SIMULATION != 1u   //if not use motor_simulation
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;

    if ( MOTOR_EN_NUM > 0u )
    {
        RCC_AHB1PeriphClockCmd(RCC_MOTOREN1 , ENABLE);
        GPIO_InitStructure.GPIO_Pin = GPIO_MOTOREN1_Pin ;
        GPIO_Init(GPIO_MOTOREN1 , &GPIO_InitStructure);
        MOTOREN1_OFF() ;
        HF_Encoder_Init(TIM2,0);	          //encoder init for PID speed control
    }
    if ( MOTOR_EN_NUM > 1u )
    {
        RCC_AHB1PeriphClockCmd(RCC_MOTOREN2 , ENABLE);
        GPIO_InitStructure.GPIO_Pin = GPIO_MOTOREN2_Pin ;
        GPIO_Init(GPIO_MOTOREN2 , &GPIO_InitStructure);
        MOTOREN2_OFF() ;
        HF_Encoder_Init(TIM3,1);
    }
    if ( MOTOR_EN_NUM > 2u )
    {
        RCC_AHB1PeriphClockCmd(RCC_MOTOREN3 , ENABLE);
        GPIO_InitStructure.GPIO_Pin = GPIO_MOTOREN3_Pin ;
        GPIO_Init(GPIO_MOTOREN3 , &GPIO_InitStructure);
        MOTOREN3_OFF() ;
        HF_Encoder_Init(TIM4,1);
    }
    
    /*****here we can init ADC for collect motor current electricity ******/


    //TIM1 motor pwm frequency  = (168M/4) / Motor_PWM_MAX  = 16.8K
    HF_PwmOut_Init(TIM1 , 2-1 , MOTOR_PWM_MAX , 1);
    //TIM12 motor pwm frequency = (84M/2) / Motor_PWM_MAX  = 16.8K
    HF_PwmOut_Init(TIM12 , 0 , MOTOR_PWM_MAX , 0);
#endif   //#if  SYSTEM_SUPPORT_MOTOR_SIMULATION != 1u   //if not use motor_simulation

#endif   //if the MCU is STM32F4 Series

    enable_m1 = 1 ;   //enable motor control
    enable_m2 = 1 ;
    enable_m3 = 1 ;
}	

/***********************************************************************************************************************
* Function:     void MotorTop::motorTopCall(void)
*
* Scope:        public
*
* Description:  motor control function ，cycle call it ，and the call frequency is PID frequency
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:
***********************************************************************************************************************/

void MotorTop::motorTopCall(void)
{

    /* here comments code is for motor test ，you do not include·it in normal unless you need to test the motor*/
//    static unsigned short int i;
//    i++;
//    if(i<1000)
//    {
//        expect_angle_speed_m1=2000;
//        expect_angle_speed_m2=2000;
//        expect_angle_speed_m3=2000;
//    }
//    else if (i>1000 && i<1500)
//    {
//        expect_angle_speed_m1=0;
//        expect_angle_speed_m2=0;
//        expect_angle_speed_m3=0;
//    }
//    else if (i>1500 && i<2500)
//    {
//        expect_angle_speed_m1=-1000;
//        expect_angle_speed_m2=-1000;
//        expect_angle_speed_m3=-1000;
//    }
//    else if(i>2500) i=0;

    // *Count--the address of encoder D_value   MAX_PWM_OUT--PWM max value
    // need time    stm32f4+nofpu 25us  stm32f4+fpu 5us
    motor_set_pwm( 1 , motor1.motorControl(expect_angle_speed_m1 , Get_Encoder_CNT_TIM2() ) );
    motor_set_pwm( 2 , motor2.motorControl(expect_angle_speed_m2 , Get_Encoder_CNT_TIM3() ) );
    motor_set_pwm( 3 , motor3.motorControl(expect_angle_speed_m3 , Get_Encoder_CNT_TIM4() ) );
}



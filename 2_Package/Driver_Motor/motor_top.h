#ifndef MOTOR_TOP_H
#define MOTOR_TOP_H

#include "motor_config.h"
#include "motor_control.h"

/*******************MOTOR1************************/	
#define RCC_MOTOREN1            RCC_AHB1Periph_GPIOE
#define GPIO_MOTOREN1           GPIOE
#define GPIO_MOTOREN1_Pin       GPIO_Pin_8
#define MOTOREN1_OFF()          GPIO_ResetBits(GPIO_MOTOREN1 , GPIO_MOTOREN1_Pin)
#define MOTOREN1_ON()           GPIO_SetBits(GPIO_MOTOREN1 , GPIO_MOTOREN1_Pin)
/*********************************************/	

/*******************MOTOREN2************************/	
#define RCC_MOTOREN2            RCC_AHB1Periph_GPIOE
#define GPIO_MOTOREN2           GPIOE
#define GPIO_MOTOREN2_Pin       GPIO_Pin_10
#define MOTOREN2_OFF()          GPIO_ResetBits(GPIO_MOTOREN2 , GPIO_MOTOREN2_Pin)
#define MOTOREN2_ON()           GPIO_SetBits(GPIO_MOTOREN2 , GPIO_MOTOREN2_Pin)
/*********************************************/		

/*******************MOTOREN2************************/	
#define RCC_MOTOREN3            RCC_AHB1Periph_GPIOE
#define GPIO_MOTOREN3           GPIOE
#define GPIO_MOTOREN3_Pin       GPIO_Pin_12
#define MOTOREN3_OFF()          GPIO_ResetBits(GPIO_MOTOREN3 , GPIO_MOTOREN3_Pin)
#define MOTOREN3_ON()           GPIO_SetBits(GPIO_MOTOREN3 , GPIO_MOTOREN3_Pin)
/*********************************************/		

class MotorTop
{

public:
    MotorTop()
    {
        enable_m1=0;
        enable_m2=0;
        enable_m3=0;
        expect_angle_speed_m1=0;
        expect_angle_speed_m2=0;
        expect_angle_speed_m3=0;
    }
    void motorTopInit(void);
    void motorTopCall(void);

public:
    MotorControl motor1,motor2,motor3;
    unsigned char enable_m1,enable_m2,enable_m3 ;    //Whether or not enable motor control
    float expect_angle_speed_m1,expect_angle_speed_m2,expect_angle_speed_m3;

private:
    void motor_set_pwm(unsigned char motor_id , float pid_out);
};

extern MotorTop motor_top;

#endif // #ifndef MOTOR_TOP_H


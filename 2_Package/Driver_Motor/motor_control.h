#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include "motor_config.h"

struct PIDData{
    unsigned char i_flag;         // pid Integral enable falg
    float p1;                     //1 is pid outside ring parameters
    float i1;                     //2 is pid inside ring parameters
    float d1;
    float p2;
    float i2;
    float d2;
    float o_error_now;
    float o_error_last;
    float o_error_before_last;
    float o_error_p;
    float o_error_i;
    float o_error_d;
    float o_pidout;
    float i_error_now;
    float i_error_last;
    float i_error_before_last;
    float i_error_p;
    float i_error_i;
    float i_error_d;
    float i_pidout;
};

class MotorControl
{
public:

    MotorControl();
    //float  expect_speed  ; motor degree/s
    //float unit_count ; the count of encoder sensor in one control cycle
    // Return: motor control pwm
    float motorControl(float expect_speed , float unit_count);

public:
    void set_pid_parameters(float p1_ , float i1_ , float d1_ , float p2_ ,float i2_ , float d2_){
        pid_parameters_.p1=p1_;
        pid_parameters_.i1=i1_;
        pid_parameters_.d1=d1_;
        pid_parameters_.p2=p2_;
        pid_parameters_.i2=i2_;
        pid_parameters_.d2=d2_;
    }
    float get_p1(void) const {return pid_parameters_.p1;}
    float get_i1(void) const {return pid_parameters_.i1;}
    float get_d1(void) const {return pid_parameters_.d1;}
    float get_p2(void) const {return pid_parameters_.p2;}
    float get_i2(void) const {return pid_parameters_.i2;}
    float get_d2(void) const {return pid_parameters_.d2;}

    float get_d_past_angel(void){  //recording d angle for robot coordinate calculation
        float temp;
        temp=d_past_angle;
        d_past_angle=0;
        return temp;
    }
    float get_measure_angle_speed(void) const {return measure_angle_speed;}
    float get_past_total_angle(void) const {return past_total_angle;}
    void  clear_past_total_angle(void){ past_total_angle = 0;}

private:
    float  expect_angle_speed;   //degree/s
    float  expect_unit_encoder;
    float  expect_total_encoder;
    float  measure_unit_encoder;
    float  measure_total_encoder;
    float  d_past_angle;  //recording d angle for robot coordinate calculation
    float  measure_angle_speed;  //degree/s measure motor speed for user
    float  past_total_angle;

    PIDData pid_parameters_;
    float pidLimit(float data , float range);
    void pidOrdinaryCall(float outside_expect , float outside_measure
                         , float inside_expect , float inside_measure , float pwm_range);
    void pidSeriesCall(float outside_expect , float outside_measure ,
                       float inside_expect , float inside_measure , float pwm_range);

};

#endif // #ifndef MOTOR_CONTROL_H


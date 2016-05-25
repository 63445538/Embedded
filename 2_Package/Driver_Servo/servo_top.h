#ifndef SERVO_TOP_H
#define SERVO_TOP_H

#include "servo_config.h"
#include "servo_digital.h"

class ServoTop:public ServoDigital
{
public:
    ServoTop()
    {
        set_head_state_renew=0;
        read_head_state_renew=0;
        expect_head_pitch=0;
        expect_head_yaw=0;
        measure_head_pitch=0;
        measure_head_yaw=0;
        first_call=0;
    }
    void init(void);
    void headTopCall(void);
public:
    unsigned char set_head_state_renew , read_head_state_renew;
    float   expect_head_pitch , expect_head_yaw;
    float   measure_head_pitch , measure_head_yaw;

private:
    unsigned char first_call;
    void setState(float pitch , float yaw);
    void getState(float* pitch , float* yaw);
};

extern ServoTop hf_head;

#endif // #ifndef SERVO_TOP_H







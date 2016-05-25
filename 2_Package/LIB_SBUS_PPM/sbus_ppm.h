#ifndef SBUS_PPM_H
#define SBUS_PPM_H

#include "sbus_ppm_config.h"

#define   SBUS_USART_INIT		HF_Usart_Init(USART2,100000,1)
#define   SBUS_D_TIME		    3000			      //us   Sbus message Time interval

class SBUS
{
public:
    SBUS()
    {
        sbus_rx_update=0;
        sbus_channel[0]=0;
        sbus_flag=0;

        sbus_frequency_=0;
        sbus_mes_count_=0;
        sbus_rx_buffer_[0]=0;
        last_time=0;
        this_time=0;
        d_time_new=0;
        d_time=0;
        last_time_=0;
        this_time_=0;
        d_time_=0;
        sbus_bufi_=0;
        sbus_mes_i_=0;
    }
    void sbusInit(void){
        SBUS_USART_INIT;
    }
    void receiveByteAnl(unsigned char receive_byte);  //put this function in serial port interrupt
    unsigned char   sbus_rx_update;
    unsigned short int  sbus_channel[16];     //temp sbus decode channel data
    unsigned char   sbus_flag;                //flag of sbus remote control signal

private:
    void sbusDataAnl(void);
    float sbus_frequency_;
    float sbus_mes_count_;
    unsigned char sbus_rx_buffer_[25];
    float last_time,this_time,d_time_new,d_time;
    float last_time_,this_time_,d_time_;
    unsigned char sbus_bufi_,sbus_mes_i_;
    float sbusFrequencyMeasure(void);
};
extern SBUS sbus ;

class PPM
{
public:
    PPM(){ }	
    void receiveFloatAnl(float pwm_value);
    unsigned short int 	ppm_rc_value[16];
private:
	 uint8_t ch_;
};
extern PPM ppm ;

#endif // #ifndef SBUS_PPM_H


#ifndef __delay_H__
#define __delay_H__

#ifdef __cplusplus
extern "C" {
#endif 

#include "stm32f4xx.h"
#include "main_config.h"

#if  SYSTEM_SUPPORT_OS > 0u   
#include "includes.h"					//used by ucos 
#endif	
	
/**********************************************************************************************************************/
void delay_init(void);
void delay_ms(unsigned short int t);    //using timer to delay time, max delay time is 1864ms
void delay_us(unsigned short int t);    //using timer to delay time, max delay time is 1864ms
/**********************************************************************************************************************/

void Init_Measurement_Timer(void);  //Initialize the Time measurement system
float GET_System_time(void);        //Return the current time(us), max:281474976s--->3257.8 days
float GET_microstime(void);         // Return the time difference(us). max:655s

/**********************************************************************************************************************/
void Get_CPU_Information(void);             //Only calls once to get ID of CPU the capacity of Flash
typedef struct CPU_Hardware_Data{
    unsigned int ChipUniqueID[3];
    unsigned short int  flash_Size;         //  Unit: KB
}CPU_Hardware_Data;
extern CPU_Hardware_Data cpu_hardware_data_r;

//以下为汇编函数
void WFI_SET(void);		//执行WFI指令
void INTX_DISABLE(void);//关闭所有中断
void INTX_ENABLE(void);	//开启所有中断
void MSR_MSP(u32 addr); //设置堆栈地址

#ifdef __cplusplus
}
#endif 


#endif

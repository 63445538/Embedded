/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: BSP_TOP.c
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
*
* Description:    
* BSP Distribution of hardware source
* SysTick(24Bits) used by operation system, nor using to make accurate delay  if no operation system
* TIM5 32BIT  used by time measurement system
* TIM2 3 4 reserved for encoder   
* TIM6 7   reserved for interruption of timer
* TIM1 8   reserved for PWM generater
* TIM2 TIM5 32BIT     others are 16BIT timer
* TIM1 TIM8 TIM9 TIM10 TIM11   168M clock   others are 84 Mhz clock
***********************************************************************************************************************/

#include "BSP_TOP.h"

#ifdef __cplusplus
extern "C" {
#endif 


HF_System_Data system_data;

/***********************************************************************************************************************
* Function:     void HF_BSP_Cycle_Call(void) 
*
* Scope:        public
*
* Description:  update the underlying hardware information: feeding dog, cycle calling. Suggest calling every 10us
*
* Arguments:
*
* Return:
*
* Cpu_Time:  stm32f1(35 us)  stm32f4+nofpu(unknow us) stm32f4+fpu(unknow us)
*
* History:
***********************************************************************************************************************/
static const float Battery_Voltage_Alarm=10.00 ;
static const float Battery_Proportion = 11.00 ;

static void System_Monitoring(void)
{
    static unsigned char Beep_Alarm_i;
    system_data.System_Time = GET_System_time();   //system working time (unit:us), start after power-on
    system_data.CPU_Temperature = adc_dac_data_r.Cpu_Standard_T;
#if  SYSTEM_SUPPORT_OS > 0u
		//support UCOSII
		#ifdef 	OS_CRITICAL_METHOD						
		#endif                                        
		//support UCOSIII                             
		#ifdef 	CPU_CFG_CRITICAL_METHOD				
		system_data.CPU_Usage=OSStatTaskCPUUsage;
		#endif
#endif
    //0.33 is the loss voltage of diode
    system_data.Battery_Voltage = 0.33f + adc_dac_data_r.ADC_Standard_Value[0] * Battery_Proportion ;
    if( (system_data.Battery_Voltage > 7) && (system_data.Battery_Voltage < Battery_Voltage_Alarm))
    {
        Beep_Alarm_i++;
        if(Beep_Alarm_i>=20)
        {
           HF_Set_Beep_State(0,2);
        }
    }
    else if( system_data.Battery_Voltage > (Battery_Voltage_Alarm+0.2f) )
    {
        Beep_Alarm_i=0;
        HF_Set_Beep_State(0,0);
    }
}


void HF_BSP_Cycle_Call(void)  //100HZ
{

    static unsigned char Call_i;
    Call_i++;
#if	BSP_CFG_LED_KEY_EN > 0u         //if using LED and Key
    HF_Key_Cycle();                 //cycle calling every 10ms, update the LED and Key data
#endif
    if(Call_i >= 20)      //5HZ
    {
        Call_i=0;
#if	BSP_CFG_RTC_EN > 0u              //if using RTC Timer
        static unsigned char BSP_Cycle_i;
        BSP_Cycle_i++;
        if(BSP_Cycle_i >= 50)           //updating every 500ms
        {
            BSP_Cycle_i=0;
            HF_RTC_Time_Renew();	      //updating time
        }
#endif

#if	BSP_CFG_WDG_WKUP_EN > 0u           //if using Watch Dog
        HF_IWDG_Feed();                //Feeding Dog
#endif

#if	BSP_CFG_ADC_DAC_EN > 0u             //if using ADC
        HF_ADC_Data_Anl();              //transfering the data of ADC
#endif

        System_Monitoring();
    }

}


/***********************************************************************************************************************
* Function:     void BSP_Init(void)
*
* Scope:        public
*
* Description:  BSP init  The initialization of  most underlying hardware, only calls once
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:
***********************************************************************************************************************/
void HF_BSP_Init(void)
{
    int i;
    for(i=0;i<0x8fff;i++);

    delay_init();                   // Initialize the delay system
    Init_Measurement_Timer();       // Initialize the measurement systemm
    Get_CPU_Information() ;         // Get the ID of CPU and the capacity of Flash
    
#if	BSP_CFG_RTC_EN  > 0u
    HF_RTC_Init();                  // Initialize the RTC, if return 0:failed,else if return 1:succeeded
#endif
    
#if	BSP_CFG_WDG_WKUP_EN > 0u
    HF_IWDG_Init();                 //  Initialize the independed watch dog, system will reset if not feeding dog over 1s
#endif
    
#if	BSP_CFG_FLASH_EN > 0u
#endif
    
#if	BSP_CFG_LED_KEY_EN > 0u
    HF_Led_Key_Init();
#endif
    
#if	BSP_CFG_USART_EN > 0u
    HF_Usart_Init(USART1,921600,0);  //Initilaize the debug USART, First Parameter:USARTx
    //2nd Para:bits rate; 3rd: IO reuse
#endif
    
#if	BSP_CFG_ADC_DAC_EN > 0u
    HF_ADC_Moder_Init();             //Initialize ADC:ADC0--ADC9  PA0--7  PB0,1
    //HF_Dac_Init(DAC_Channel_1);      //Initialize DAC:DAC_Channel_x = DAC_Channel_1 PA4 || DAC_Channel_2 PA5
#endif
    
#if	BSP_CFG_TIMER_EN > 0u
    HF_Timer_Init(TIM6 , 1000);      //Input parameter :TIMx and delay time(us), *timer2--7  1ms
#endif
    
#if	BSP_CFG_PWMIN_EN > 0u
    //HF_PwmIn_Init();                 //Initialize capturing PWM. Using 5 channels maximum. PC0 PC1 PC2 PC3 PC4
#endif
    
#if	BSP_CFG_PWMOUT_EN > 0u
#endif
    
#if	BSP_CFG_ENCODER_EN > 0u
#endif
    
#if	BSP_CFG_SPI_EN > 0u
#endif
    
#if	BSP_CFG_I2C_EN > 0u
#endif
    
#if	BSP_CFG_CAN_EN > 0u
#endif

    HF_Set_Beep_State(0,1);
    delay_ms(500);
    HF_Set_Beep_State(0,0);
}

#ifdef __cplusplus
}
#endif 

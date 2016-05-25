/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: led_key.c
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
* Description:  this file define 6 keys and leds
***********************************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include "led_key.h"

LED_KEY_DATA led_key_data_r;

/***********************************************************************************************************************
* Function:     void HF_Led_Key_Init(void)
*
* Scope:        public
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
***********************************************************************************************************************/
void HF_Led_Key_Init(void)
{
    uint8_t LED_Init_Num=0 , KEY_Init_Num=0 , BEEP_Init_Num=0;

    GPIO_InitTypeDef  GPIO_InitStruct;

#if LED_NUM > 0	
    /********************************LED Initialization of Pin*********************************************/

    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;//normal output mode
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;//push-pull mode
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;//pull up
	
    if ( LED_Init_Num++ < LED_NUM )      //if enable LED0, initialize this
    {
        LED0_GPIO_CLK_ENABLE();
        GPIO_InitStruct.GPIO_Pin = LED0_GPIO_PIN ;
        GPIO_Init(LED0_GPIO , &GPIO_InitStruct);
    }
    if ( LED_Init_Num++ < LED_NUM )      //if enable LED1, initialize this
    {
        LED1_GPIO_CLK_ENABLE();
        GPIO_InitStruct.GPIO_Pin = LED1_GPIO_PIN ;
        GPIO_Init(LED1_GPIO , &GPIO_InitStruct);
    }
    if ( LED_Init_Num++ < LED_NUM )      //if enable LED2, initialize this
    {
        LED2_GPIO_CLK_ENABLE();
        GPIO_InitStruct.GPIO_Pin = LED2_GPIO_PIN ;
        GPIO_Init(LED2_GPIO , &GPIO_InitStruct);
    }
    if ( LED_Init_Num++ < LED_NUM )      //if enable LED3, initialize this
    {
        LED3_GPIO_CLK_ENABLE();
        GPIO_InitStruct.GPIO_Pin = LED3_GPIO_PIN ;
        GPIO_Init(LED3_GPIO , &GPIO_InitStruct);
    }
    if ( LED_Init_Num++ < LED_NUM )      //if enable LED4, initialize this
    {
        LED4_GPIO_CLK_ENABLE();
        GPIO_InitStruct.GPIO_Pin = LED4_GPIO_PIN ;
        GPIO_Init(LED4_GPIO , &GPIO_InitStruct);
    }
    if ( LED_Init_Num++ < LED_NUM )      //if enable LED5, initialize this
    {
        LED5_GPIO_CLK_ENABLE();
        GPIO_InitStruct.GPIO_Pin = LED5_GPIO_PIN ;
        GPIO_Init(LED5_GPIO , &GPIO_InitStruct);
    }
#endif
		
#if KEY_NUM > 0	
    /********************************KEY Initialization of Pin*********************************************/

    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;//normal output mode
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;//100M
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;//pull up
	
    if ( KEY_Init_Num++ < KEY_NUM)      //if enable KEY0, initialize this
    {
        KEY0_GPIO_CLK_ENABLE();
        GPIO_InitStruct.GPIO_Pin = KEY0_GPIO_PIN ;
        GPIO_Init(KEY0_GPIO , &GPIO_InitStruct);
    }
    if ( KEY_Init_Num++ < KEY_NUM)      //if enable KEY1, initialize this
    {
        KEY1_GPIO_CLK_ENABLE();
        GPIO_InitStruct.GPIO_Pin = KEY1_GPIO_PIN ;
        GPIO_Init(KEY1_GPIO , &GPIO_InitStruct);
    }
    if ( KEY_Init_Num++ < KEY_NUM)      //if enable KEY2, initialize this
    {
        KEY2_GPIO_CLK_ENABLE();
        GPIO_InitStruct.GPIO_Pin = KEY2_GPIO_PIN ;
        GPIO_Init(KEY2_GPIO , &GPIO_InitStruct);
    }
    if ( KEY_Init_Num++ < KEY_NUM)      //if enable KEY3, initialize this
    {
        KEY3_GPIO_CLK_ENABLE();
        GPIO_InitStruct.GPIO_Pin = KEY3_GPIO_PIN ;
        GPIO_Init(KEY3_GPIO , &GPIO_InitStruct);
    }
    if ( KEY_Init_Num++ < KEY_NUM)      //if enable KEY4, initialize this
    {
        KEY4_GPIO_CLK_ENABLE();
        GPIO_InitStruct.GPIO_Pin = KEY4_GPIO_PIN ;
        GPIO_Init(KEY4_GPIO , &GPIO_InitStruct);
    }
    if ( KEY_Init_Num++ < KEY_NUM)      //if enable KEY5, initialize this
    {
        KEY5_GPIO_CLK_ENABLE();
        GPIO_InitStruct.GPIO_Pin = KEY5_GPIO_PIN ;
        GPIO_Init(KEY5_GPIO , &GPIO_InitStruct);
    }
#endif

#if BEEP_NUM > 0			
    /********************************BEEP Initialization of Pin*********************************************/

    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;//normal output mode
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;//push-pull mode
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;//pull up

    if (BEEP_Init_Num++ < BEEP_NUM )      //if enable LED0, initialize this
    {
        BEEP0_GPIO_CLK_ENABLE();
        GPIO_InitStruct.GPIO_Pin = BEEP0_GPIO_PIN ;
        GPIO_Init(BEEP0_GPIO , &GPIO_InitStruct);
    }
    if (BEEP_Init_Num++ < BEEP_NUM )      //if enable LED1, initialize this
    {
        BEEP1_GPIO_CLK_ENABLE();
        GPIO_InitStruct.GPIO_Pin = BEEP1_GPIO_PIN ;
        GPIO_Init(BEEP1_GPIO , &GPIO_InitStruct);
    }
#endif
}

/***********************************************************************************************************************
* Function:     static void Get_Key_State(void)
*
* Scope:        public
*
* Description:  update state of Pin : 0-->not pressed   1-->pressed. Cycle call every 10ms, and use software to Debounce
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
***********************************************************************************************************************/

#if KEY_NUM > 0	
static uint8_t Read_Key(uint8_t Key_Id )
{

    if( Key_Id >= (uint8_t)KEY_NUM){return 1;}      //not pressed
    if( Key_Id == 0){return KEY0_GPIO_READ ;}
    if( Key_Id == 1){return KEY1_GPIO_READ ;}
    if( Key_Id == 2){return KEY2_GPIO_READ ;}
    if( Key_Id == 3){return KEY3_GPIO_READ ;}
    if( Key_Id == 4){return KEY4_GPIO_READ ;}
    if( Key_Id == 5){return KEY5_GPIO_READ ;} 
	 return 1;         //not pressed
}
#endif

void HF_Key_Cycle(void)
{
#if KEY_NUM > 0
    static uint8_t Key_State=0,This_temp=0,Last_temp=0;
    uint8_t i;
    This_temp= Read_Key(0)<<0 | Read_Key(1)<<1 | Read_Key(2)<<2 | Read_Key(3)<<3 | Read_Key(4)<<4 | Read_Key(5)<<5 ;
    Key_State=~(This_temp | Last_temp);    //0-->not pressed   1-->pressed
    Last_temp=This_temp;
    for(i=0 ; i< KEY_NUM ; i++)
    {
       led_key_data_r.Key[i] = ( Key_State & ( (uint8_t)0X01 << i ) ) >> i ;   //  use first bit  0--7
    }
#endif
}

/***********************************************************************************************************************
* Function:     void Set_Led_State(uint8_t Led_Id , uint8_t Operation)
*
* Scope:        public
*
* Description:  set state of LED : Led_Id  Operation= 0,1,2 0 OFF 1ON 2TOGGLE
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
***********************************************************************************************************************/
void HF_Set_Led_State(uint8_t Led_Id , uint8_t Operation)
{
#if LED_NUM > 0
    if( Led_Id >= LED_NUM){return;}
    if(Led_Id == 0)
    {
        if( Operation == 0){LED0_OFF();}
        else if( Operation == 1){LED0_ON();}
        else if( Operation == 2){LED0_TOGGLE();}
    }
    if(Led_Id == 1)
    {
        if( Operation == 0){LED1_OFF();}
        else if( Operation == 1){LED1_ON();}
        else if( Operation == 2){LED1_TOGGLE();}
    }
    if(Led_Id == 2)
    {
        if( Operation == 0){LED2_OFF();}
        else if( Operation == 1){LED2_ON();}
        else if( Operation == 2){LED2_TOGGLE();}
    }
    if(Led_Id == 3)
    {
        if( Operation == 0){LED3_OFF();}
        else if( Operation == 1){LED3_ON();}
        else if( Operation == 2){LED3_TOGGLE();}
    }
    if(Led_Id == 4)
    {   if( Operation == 0){LED4_OFF();}
        else if( Operation == 1){LED4_ON();}
        else if( Operation == 2){LED4_TOGGLE();} }
    if(Led_Id == 5)
    {
        if( Operation == 0){LED5_OFF();}
        else if( Operation == 1) {LED5_ON();}
        else if( Operation == 2){LED5_TOGGLE();}
    }
#endif		
}

/***********************************************************************************************************************
* Function:     HF_Set_Beep_State(uint8_t beep_id , uint8_t operation)
*
* Scope:        public
*
* Description:  set state of BEEP  0 OFF 1ON  2TOGGLE()
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
***********************************************************************************************************************/
void HF_Set_Beep_State(uint8_t beep_id , uint8_t operation)
{
#if BEEP_NUM > 0
	if(beep_id==0){
	  if(operation==1) BEEP0_ON();
		else if(operation==0) BEEP0_OFF();
		else if(operation==2) BEEP0_TOGGLE();
	}
	else if (beep_id==1){
	  if(operation==1) BEEP1_ON();
		else if(operation==0) BEEP1_OFF();
		else if(operation==2) BEEP1_TOGGLE();
	}
#endif
}

#ifdef __cplusplus
}
#endif


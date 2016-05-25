#ifndef LED_KEY_H
#define LED_KEY_H

#ifdef __cplusplus
extern "C" {
#endif 

#include "stm32f4xx.h"

/*******************LED0************************/
#define LED0_GPIO_PIN             GPIO_Pin_15
#define LED0_GPIO                 GPIOG
#define LED0_GPIO_CLK_ENABLE()    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG,ENABLE)  
#define LED0_GPIO_CLK_DISABLE()   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG,DISABLE)  
#define LED0_ON()                 GPIO_ResetBits(LED0_GPIO,LED0_GPIO_PIN)
#define LED0_OFF()                GPIO_SetBits(LED0_GPIO,LED0_GPIO_PIN)
#define LED0_TOGGLE()             GPIO_ToggleBits(LED0_GPIO,LED0_GPIO_PIN)
/********************LED1***********************/
#define LED1_GPIO_PIN             GPIO_Pin_13
#define LED1_GPIO                 GPIOD
#define LED1_GPIO_CLK_ENABLE()    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE)  
#define LED1_GPIO_CLK_DISABLE()   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,DISABLE)  
#define LED1_ON()                 GPIO_ResetBits(LED1_GPIO,LED1_GPIO_PIN)
#define LED1_OFF()                GPIO_SetBits(LED1_GPIO,LED1_GPIO_PIN)
#define LED1_TOGGLE()             GPIO_ToggleBits(LED1_GPIO,LED1_GPIO_PIN)
/*******************LED2************************/
#define LED2_GPIO_PIN             GPIO_Pin_13
#define LED2_GPIO                 GPIOD
#define LED2_GPIO_CLK_ENABLE()    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE)  
#define LED2_GPIO_CLK_DISABLE()   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,DISABLE)  
#define LED2_ON()                 GPIO_ResetBits(LED2_GPIO,LED2_GPIO_PIN)
#define LED2_OFF()                GPIO_SetBits(LED2_GPIO,LED2_GPIO_PIN)
#define LED2_TOGGLE()             GPIO_ToggleBits(LED2_GPIO,LED2_GPIO_PIN)
/*******************LED3************************/
#define LED3_GPIO_PIN             GPIO_Pin_13
#define LED3_GPIO                 GPIOD
#define LED3_GPIO_CLK_ENABLE()    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE)  
#define LED3_GPIO_CLK_DISABLE()   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,DISABLE)  
#define LED3_ON()                 GPIO_ResetBits(LED3_GPIO,LED3_GPIO_PIN)
#define LED3_OFF()                GPIO_SetBits(LED3_GPIO,LED3_GPIO_PIN)
#define LED3_TOGGLE()             GPIO_ToggleBits(LED3_GPIO,LED3_GPIO_PIN)
/*******************LED4************************/
#define LED4_GPIO_PIN             GPIO_Pin_13
#define LED4_GPIO                 GPIOD
#define LED4_GPIO_CLK_ENABLE()    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE)  
#define LED4_GPIO_CLK_DISABLE()   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,DISABLE)  
#define LED4_ON()                 GPIO_ResetBits(LED4_GPIO,LED4_GPIO_PIN)
#define LED4_OFF()                GPIO_SetBits(LED4_GPIO,LED4_GPIO_PIN)
#define LED4_TOGGLE()             GPIO_ToggleBits(LED4_GPIO,LED4_GPIO_PIN)
/*******************LED5************************/
#define LED5_GPIO_PIN             GPIO_Pin_13
#define LED5_GPIO                 GPIOD
#define LED5_GPIO_CLK_ENABLE()    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE)  
#define LED5_GPIO_CLK_DISABLE()   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,DISABLE)  
#define LED5_ON()                 GPIO_ResetBits(LED5_GPIO,LED5_GPIO_PIN)
#define LED5_OFF()                GPIO_SetBits(LED5_GPIO,LED5_GPIO_PIN)
#define LED5_TOGGLE()             GPIO_ToggleBits(LED5_GPIO,LED5_GPIO_PIN)
/***********************************************/

/*******************KEY0************************/
#define KEY0_GPIO_PIN             GPIO_Pin_14
#define KEY0_GPIO                 GPIOC
#define KEY0_GPIO_CLK_ENABLE()    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE) 
#define KEY0_GPIO_CLK_DISABLE()   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,DISABLE)  
#define KEY0_GPIO_READ            GPIO_ReadInputDataBit(KEY0_GPIO,KEY0_GPIO_PIN)
/*******************KEY1************************/
#define KEY1_GPIO_PIN             GPIO_Pin_13
#define KEY1_GPIO                 GPIOC
#define KEY1_GPIO_CLK_ENABLE()    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE) 
#define KEY1_GPIO_CLK_DISABLE()   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,DISABLE)  
#define KEY1_GPIO_READ            GPIO_ReadInputDataBit(KEY1_GPIO,KEY1_GPIO_PIN)
/*******************KEY2************************/
#define KEY2_GPIO_PIN             GPIO_Pin_13
#define KEY2_GPIO                 GPIOC
#define KEY2_GPIO_CLK_ENABLE()    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE) 
#define KEY2_GPIO_CLK_DISABLE()   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,DISABLE)  
#define KEY2_GPIO_READ            GPIO_ReadInputDataBit(KEY2_GPIO,KEY2_GPIO_PIN)
/*******************KEY3************************/
#define KEY3_GPIO_PIN             GPIO_Pin_13
#define KEY3_GPIO                 GPIOC
#define KEY3_GPIO_CLK_ENABLE()    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE) 
#define KEY3_GPIO_CLK_DISABLE()   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,DISABLE)  
#define KEY3_GPIO_READ            GPIO_ReadInputDataBit(KEY3_GPIO,KEY3_GPIO_PIN)
/*******************KEY4************************/
#define KEY4_GPIO_PIN             GPIO_Pin_13
#define KEY4_GPIO                 GPIOC
#define KEY4_GPIO_CLK_ENABLE()    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE) 
#define KEY4_GPIO_CLK_DISABLE()   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,DISABLE)  
#define KEY4_GPIO_READ            GPIO_ReadInputDataBit(KEY4_GPIO,KEY4_GPIO_PIN)
/*******************KEY5*************************/
#define KEY5_GPIO_PIN             GPIO_Pin_13
#define KEY5_GPIO                 GPIOC
#define KEY5_GPIO_CLK_ENABLE()    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE) 
#define KEY5_GPIO_CLK_DISABLE()   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,DISABLE)  
#define KEY5_GPIO_READ            GPIO_ReadInputDataBit(KEY5_GPIO,KEY5_GPIO_PIN)
/************************************************/

/*******************BEEP0************************/
#define BEEP0_GPIO_PIN             GPIO_Pin_9
#define BEEP0_GPIO                 GPIOB
#define BEEP0_GPIO_CLK_ENABLE()    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE)  
#define BEEP0_GPIO_CLK_DISABLE()   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,DISABLE)  
#define BEEP0_ON()                 GPIO_SetBits(BEEP0_GPIO,BEEP0_GPIO_PIN)
#define BEEP0_OFF()                GPIO_ResetBits(BEEP0_GPIO,BEEP0_GPIO_PIN)
#define BEEP0_TOGGLE()             GPIO_ToggleBits(BEEP0_GPIO,BEEP0_GPIO_PIN)
/*******************BEEP1************************/
#define BEEP1_GPIO_PIN             GPIO_Pin_9
#define BEEP1_GPIO                 GPIOB
#define BEEP1_GPIO_CLK_ENABLE()    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE)  
#define BEEP1_GPIO_CLK_DISABLE()   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,DISABLE)  
#define BEEP1_ON()                 GPIO_SetBits(BEEP1_GPIO,BEEP1_GPIO_PIN)
#define BEEP1_OFF()                GPIO_ResetBits(BEEP1_GPIO,BEEP1_GPIO_PIN)
#define BEEP1_TOGGLE()             GPIO_ToggleBits(BEEP1_GPIO,BEEP1_GPIO_PIN)
/************************************************/

/************************************************/

#define LED_NUM          6       //the number of enable LED 0--6
#define KEY_NUM          6       //the number of enable KEY 0--6
#define BEEP_NUM         2       //if enable beep

typedef struct LED_KEY_DATA{
#if LED_NUM > 0             
    uint8_t Led[LED_NUM];   //read variable 0 OFF  1ON
#endif

#if KEY_NUM > 0
    uint8_t Key[KEY_NUM];  //read variable : 0-->not pressed, 1-->pressed
#endif
	
#if BEEP_NUM  > 0	
uint8_t Beep_State[BEEP_NUM];	    //read variable 0 OFF  1ON	
#endif
	   
}LED_KEY_DATA;

extern LED_KEY_DATA led_key_data_r;

void HF_Led_Key_Init(void);
void HF_Key_Cycle(void);                                           //10ms cycle call, update data of KEY
void HF_Set_Led_State(uint8_t Led_Id, uint8_t Operation);          // 0 OFF 1ON  2 TOGGLE
void HF_Set_Beep_State(uint8_t beep_id , uint8_t operation);       // 0 OFF  1ON

#ifdef __cplusplus
}
#endif 

#endif // #ifndef LED_KEY_H



/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: main_config.h
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
* Description:   syetem config file
***********************************************************************************************************************/
#ifndef __main_config_H__
#define __main_config_H__

/*****************************system config****************************************************************************/
#define Hands_Free_Version  2.0                   //THE Version of HANDS FREE
//Whether or not printf DEBUG info to usart1
#define DEBUG 0
/**********************************************************************************************************************/


/********************************************processor config**********************************************************/
// Precompiled  choose  you can Include the file you want to save flash
#define BSP_CFG_RTC_EN                0u          //Whether or not Include code RTC time
#define BSP_CFG_WDG_WKUP_EN           0u          //Whether or not Include code watch dog  and Low power consumption
#define BSP_CFG_FLASH_EN              0u          //Whether or not Include code FLASH
#define BSP_CFG_LED_KEY_EN            1u          //Whether or not Include code led and key
#define BSP_CFG_USART_EN              1u          //Whether or not Include code led and keyUSART
#define BSP_CFG_ADC_DAC_EN            0u          //Whether or not Include code ADC_DAC
#define BSP_CFG_TIMER_EN              1u          //Whether or not Include code TIMER
#define BSP_CFG_PWMIN_EN              0u          //Whether or not Include code pwm input
#define BSP_CFG_PWMOUT_EN             0u          //Whether or not Include code pwm output
#define BSP_CFG_ENCODER_EN            0u          //Whether or not Include code motor encoder
#define BSP_CFG_SPI_EN                0u          //Whether or not Include code SPI
#define BSP_CFG_I2C_EN                1u          //Whether or not Include code I2C
#define BSP_CFG_CAN_EN                0u          //Whether or not Include code CAN
/**********************************************************************************************************************/


/*****************************************package config***************************************************************/
#define Driver_IMU
#define LIB_Math
/**********************************************************************************************************************/


/********************************************OSconfig******************************************************************/

//Whether or not include RTOS  UCOSII or UCOSIII
#define SYSTEM_SUPPORT_OS 0
//Whether or not include GUI STWIN or EMWIN
#define SYSTEM_SUPPORT_GUI 0

/**********************************************************************************************************************/


/*******************************************API config*****************************************************************/


/**********************************************************************************************************************/

#endif


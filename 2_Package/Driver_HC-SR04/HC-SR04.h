/***********************************************************************************************************************
* Copyright (c) IDM OF PKU Team. All rights reserved.
* FileName: HC-SR04.h
* Contact:  18611105612 QQ:523482730 mail£ºslayerkillme@gmail.com 
* Version:  V1.0
*
* LICENSING TERMS:
* The Hands Free is licensed generally under a permissive 3-clause BSD license.
* Contributions are requiredto be made under the same license.
*
* History:
* <author>      <time>      <version>      <desc>
* caorui       2016.10.3     V1.0         create this file
* Description:
* this file is analog servo configuration header.
*
***********************************************************************************************************************/

#ifndef HC_SR04_H
#define HC_SR04_H

#include "HC-SR04_config.h"

//#define ULTRA_PORT	    GPIOC
//#define ULTRA_CLK       RCC_APB2Periph_GPIOC
//#define ULTRA_TRIG			GPIO_Pin_4
//#define ULTRA_ECHO			GPIO_Pin_5
//
//
class ULTRASONIC 
{
public: ULTRASONIC() {}
	      void Ultra_Init(int8_t ultra_id);
	      float Ultra_Ranging(int8_t ultra_id);
		
};


extern ULTRASONIC Ultrasonic;
#endif   

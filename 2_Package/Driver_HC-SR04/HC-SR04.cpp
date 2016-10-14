/***********************************************************************************************************************
* Copyright (c) IDM OF PKU Team. All rights reserved.
* FileName: analog_servo.cpp
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
* this is the analog servo driver code.
*
***********************************************************************************************************************/
#include "HC-SR04.h"

ULTRASONIC Ultrasonic;

void ULTRASONIC::Ultra_Init(int8_t ultra_id)
{	
	if(ultra_id == 1)
	{		
			GPIO_InitTypeDef GPIO_InitStructure;
			RCC_APB2PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
			GPIO_InitStructure.GPIO_Pin =GPIO_Pin_4;
		 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
			GPIO_Init(GPIOC, &GPIO_InitStructure);
			GPIO_ResetBits(GPIOC,GPIO_Pin_4);
		
			GPIO_InitStructure.GPIO_Pin =GPIO_Pin_5;		
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
			GPIO_Init(GPIOC, &GPIO_InitStructure);	
	}
	else if(ultra_id == 2)
	{		
			GPIO_InitTypeDef GPIO_InitStructure;
			RCC_APB2PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
			GPIO_InitStructure.GPIO_Pin =GPIO_Pin_2;
		 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
			GPIO_Init(GPIOD, &GPIO_InitStructure);
			GPIO_ResetBits(GPIOD,GPIO_Pin_2);
		
			GPIO_InitStructure.GPIO_Pin =GPIO_Pin_3;		
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
			GPIO_Init(GPIOD, &GPIO_InitStructure);
	}

}	

float ULTRASONIC::Ultra_Ranging(int8_t ultra_id)
{		
 if(	ultra_id == 1){
	u32 j;
	float Ultr_Temp;	
	 
		GPIO_SetBits(GPIOC,GPIO_Pin_4);
		delay_ms(10);
		GPIO_ResetBits(GPIOC,GPIO_Pin_4);
		int time_temp = HF_Get_System_Time();
		while(!((GPIOC->IDR & GPIO_Pin_5) || (HF_Get_System_Time()- time_temp > 500000))){};
	  //while(!(GPIOC->IDR & GPIO_Pin_5));
	  time_temp = HF_Get_System_Time();
		while((GPIOC->IDR & GPIO_Pin_5) && (HF_Get_System_Time()- time_temp < 500000))
		{
			delay_us(10);
			j++;
		}
		Ultr_Temp+=340/2*j*10;
		j=0;
		delay_ms(60);
	return Ultr_Temp/1000000;
}
 else if(ultra_id == 2)
 {	return 0;
 }
	return 0;
}

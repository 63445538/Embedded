/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: main.c
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
* Description:   
***********************************************************************************************************************/
#include "main_includes.h"

#define START_TASK_PRIO			10  
#define START_STK_SIZE			500
OS_STK START_TASK_STK[START_STK_SIZE];
void start_task(void *pdata);

#define LED0_TASK_PRIO			7
#define LED0_STK_SIZE			  500
OS_STK LED0_TASK_STK[LED0_STK_SIZE];
void led0_task(void *pdata);

#define BEEP_TASK_PRIO			6
#define BEEP_STK_SIZE			  500
OS_STK BEEP_TASK_STK[BEEP_STK_SIZE];
void beep_task(void *pdata);

#define FLOAT_TASK_PRIO			5
#define FLOAT_STK_SIZE			500
__align(8) OS_STK FLOAT_TASK_STK[FLOAT_STK_SIZE]; 
void float_task(void *pdata);

												 
/***********************************************************************************************************************
* Function:   
*
* Scope:      
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
void System_Init(void)
{
    //SCB->VTOR = FLASH_BASE | 0x10000;  //Bootloader
    INTX_DISABLE();  //close all interruption
    HF_BSP_Init();
    INTX_ENABLE();	 //enable all interruption
}


int main(void)
{
	System_Init();
	printf("app start \r\n");
	OSInit();   
	//Create start task
	OSTaskCreate(start_task,(void *)0,(OS_STK *)&START_TASK_STK[START_STK_SIZE-1],START_TASK_PRIO );
	OSStart();	
}


void start_task(void *pdata)
{
	OS_CPU_SR cpu_sr=0;
	pdata = pdata; 
  printf("task start \r\n");
	OSStatInit();         
	OS_ENTER_CRITICAL();	 
	OSTaskCreate(led0_task,(void *)0,(OS_STK*)&LED0_TASK_STK[LED0_STK_SIZE-1],LED0_TASK_PRIO);	  //Create led0 task					   
	OSTaskCreate(beep_task,(void *)0,(OS_STK*)&BEEP_TASK_STK[BEEP_STK_SIZE-1],BEEP_TASK_PRIO);	  //Create beep task			   
	OSTaskCreate(float_task,(void*)0,(OS_STK*)&FLOAT_TASK_STK[FLOAT_STK_SIZE-1],FLOAT_TASK_PRIO); //Create float test task
	OSTaskSuspend(START_TASK_PRIO);	
	OS_EXIT_CRITICAL();				      
}


void led0_task(void *pdata)
{	 	
	while(1)
	{
		HF_Set_Led_State(0,0);
	  OSTimeDlyHMSM (0 , 0 , 0 , 80);
		HF_Set_Led_State(0,1);
		OSTimeDlyHMSM (0 , 0 , 0 , 920);
	};
}


void beep_task(void *pdata)
{	  
	while(1)
	{
		//BEEP_ON();
		OSTimeDlyHMSM (0 , 0 , 1 , 0);
		//BEEP_OFF();
		OSTimeDlyHMSM (0 , 0 , 1 , 0);
	};
}

void float_task(void *pdata)
{
	OS_CPU_SR cpu_sr=0;
	static float float_num=0.01;
	while(1)
	{
		float_num+=0.01f;
		OS_ENTER_CRITICAL();	
		printf("float_num is: %.4f\r\n",float_num); 
		OS_EXIT_CRITICAL();		
		OSTimeDlyHMSM (0 , 0 , 0 , 500);
	}
}

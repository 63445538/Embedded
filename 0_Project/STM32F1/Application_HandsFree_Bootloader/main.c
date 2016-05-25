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
* by   mawenke   2015.12.1   creat
***********************************************************************************************************************/
unsigned short int enter_bootloader_flag;	

void System_Init(void)
{
    INTX_DISABLE();  //close all interruption
    HF_BSP_Init();
    enter_bootloader_flag=STMFLASH_ReadWord(FLASH_APP1_ADDR - 4);
    if(enter_bootloader_flag !=256 )    //jump to app code
    {
        enter_bootloader_flag=256;
        STMFLASH_Write(FLASH_APP1_ADDR - 4 , &enter_bootloader_flag , 1);
        HF_Set_Beep_State(1);
        delay_ms(500);
        delay_ms(500);
        HF_Set_Beep_State(0);
        enter_bootloader_flag=0;
        STMFLASH_Write(FLASH_APP1_ADDR - 4 , &enter_bootloader_flag , 1);
        Load_Flash_APP(FLASH_APP1_ADDR);
    }
    enter_bootloader_flag = 0;
    STMFLASH_Write(FLASH_APP1_ADDR - 4 , &enter_bootloader_flag , 1);
    HF_Set_Beep_State(1);
    delay_ms(500);
    delay_ms(500);
    delay_ms(500);
    delay_ms(500);
    HF_Set_Beep_State(0);
    INTX_ENABLE();	 //enable all interruption
}

int main(void)
{
    System_Init();
    printf("bootloader start \r\n");
    while(1)
    {
        Boot_Loader_Call();
        delay_ms(500);
        if(USART_RX_CNT) {
            HF_Set_Led_State(0,2);
        }
        else{

            HF_Set_Led_State(0,1);
        }
    }
}


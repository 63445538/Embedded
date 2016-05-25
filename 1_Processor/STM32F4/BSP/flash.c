/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: flash.c
* Contact:  QQ Exchange Group -- 521037187
* Version:  V2.0
*
* LICENSING TERMS:
* The Hands Free is licensed generally under a permissive 3-clause BSD license.
* Contributions are requiredto be made under the same license.
*
* History: 
* <author>      <time>      <version>      <desc>
*
* Description:
*       STM32F4--------------
*       no using Pin source
***********************************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif 

#include "flash.h"

/***********************************************************************************************************************
* Function:     u32 STMFLASH_ReadWord(u32 faddr)
*
* Scope: 
*
* Description:  read half word data(16 bits) from assign address
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:
***********************************************************************************************************************/
u32 STMFLASH_ReadWord(u32 faddr)
{
    return *(vu32*)faddr;
}  

/***********************************************************************************************************************
* Function:     uint16_t STMFLASH_GetFlashSector(u32 addr) 
*
* Scope:   
*
* Description:  get flash sector of address
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:
***********************************************************************************************************************/
uint16_t STMFLASH_GetFlashSector(u32 addr)
{
    if(addr<ADDR_FLASH_SECTOR_1)return FLASH_Sector_0;
    else if(addr<ADDR_FLASH_SECTOR_2)return FLASH_Sector_1;
    else if(addr<ADDR_FLASH_SECTOR_3)return FLASH_Sector_2;
    else if(addr<ADDR_FLASH_SECTOR_4)return FLASH_Sector_3;
    else if(addr<ADDR_FLASH_SECTOR_5)return FLASH_Sector_4;
    else if(addr<ADDR_FLASH_SECTOR_6)return FLASH_Sector_5;
    else if(addr<ADDR_FLASH_SECTOR_7)return FLASH_Sector_6;
    else if(addr<ADDR_FLASH_SECTOR_8)return FLASH_Sector_7;
    else if(addr<ADDR_FLASH_SECTOR_9)return FLASH_Sector_8;
    else if(addr<ADDR_FLASH_SECTOR_10)return FLASH_Sector_9;
    else if(addr<ADDR_FLASH_SECTOR_11)return FLASH_Sector_10;
    return FLASH_Sector_11;
}

/***********************************************************************************************************************
* Function:     void STMFLASH_Write(u32 WriteAddr,u32 *pBuffer,u32 NumToWrite)
*
* Scope: 
*
* Description:  write the wanted length data from assign address
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:
***********************************************************************************************************************/
void STMFLASH_Write(u32 WriteAddr,u32 *pBuffer,u32 NumToWrite)	
{ 
    FLASH_Status status = FLASH_COMPLETE;
    u32 addrx=0;
    u32 endaddr=0;
    if(WriteAddr<STM32_FLASH_BASE||WriteAddr%4)return;	//Illegal address
    FLASH_Unlock();									    //unlock
    FLASH_DataCacheCmd(DISABLE);//must disable data cache while FLASH erasing
    
    addrx=WriteAddr;				//start address to write
    endaddr=WriteAddr+NumToWrite*4;	//end address to write
    if(addrx<0X1FFF0000)			//only master store area need be erased
    {
        while(addrx<endaddr)		//erase all
        {
            if(STMFLASH_ReadWord(addrx)!=0XFFFFFFFF)//if not is 0XFFFFFFFF, need to be erased
            {
                status=FLASH_EraseSector(STMFLASH_GetFlashSector(addrx),VoltageRange_3);//VCC=2.7~3.6V之间!!
                if(status!=FLASH_COMPLETE)break;	//have error
            }else addrx+=4;
        }
    }
    if(status==FLASH_COMPLETE)
    {
        while(WriteAddr<endaddr)//write data
        {
            if(FLASH_ProgramWord(WriteAddr,*pBuffer)!=FLASH_COMPLETE)//writing data
            {
                break;	       //error to writing
            }
            WriteAddr+=4;
            pBuffer++;
        }
    }
    FLASH_DataCacheCmd(ENABLE);	//finish FLASH eraseing, enable data cache
    FLASH_Lock();//lock
} 

/***********************************************************************************************************************
* Function:     void STMFLASH_Read(u32 ReadAddr,u32 *pBuffer,u32 NumToRead) 
*
* Scope:   
*
* Description:  read the wanted length data from assign address
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:
***********************************************************************************************************************/
void STMFLASH_Read(u32 ReadAddr,u32 *pBuffer,u32 NumToRead)   	
{
    u32 i;
    for(i=0;i<NumToRead;i++)
    {
        pBuffer[i]=STMFLASH_ReadWord(ReadAddr);//read 4 bytes
        ReadAddr+=4;//offset 4 bytes
    }
}

#ifdef __cplusplus
}
#endif 

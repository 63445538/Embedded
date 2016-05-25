#ifndef __flash_H__
#define __flash_H__

#ifdef __cplusplus
extern "C" {
#endif 

#include "stm32f4xx.h"

//start address of FLASH
#define STM32_FLASH_BASE 0x08000000 	//start address of STM32 FLASH

//FLASH start address of sector
#define ADDR_FLASH_SECTOR_0     ((u32)0x08000000) 	//start address of sector 0,  16 Kbytes  
#define ADDR_FLASH_SECTOR_1     ((u32)0x08004000) 	//start address of sector 1,  16 Kbytes  
#define ADDR_FLASH_SECTOR_2     ((u32)0x08008000) 	//start address of sector 2,  16 Kbytes  
#define ADDR_FLASH_SECTOR_3     ((u32)0x0800C000) 	//start address of sector 3,  16 Kbytes  
#define ADDR_FLASH_SECTOR_4     ((u32)0x08010000) 	//start address of sector 4,  64 Kbytes  
#define ADDR_FLASH_SECTOR_5     ((u32)0x08020000) 	//start address of sector 5,  128 Kbytes  
#define ADDR_FLASH_SECTOR_6     ((u32)0x08040000) 	//start address of sector 6,  128 Kbytes  
#define ADDR_FLASH_SECTOR_7     ((u32)0x08060000) 	//start address of sector 7,  128 Kbytes  
#define ADDR_FLASH_SECTOR_8     ((u32)0x08080000) 	//start address of sector 8,  128 Kbytes  
#define ADDR_FLASH_SECTOR_9     ((u32)0x080A0000) 	//start address of sector 9,  128 Kbytes  
#define ADDR_FLASH_SECTOR_10    ((u32)0x080C0000) 	//start address of sector 10, 128 Kbytes  
#define ADDR_FLASH_SECTOR_11    ((u32)0x080E0000) 	//start address of sector 11, 128 Kbytes  

u32 STMFLASH_ReadWord(u32 faddr);		  	//read word (16bits)
void STMFLASH_Write(u32 WriteAddr, u32 *pBuffer, u32 NumToWrite);		//write the wanted length data from assign address
void STMFLASH_Read(u32 ReadAddr, u32 *pBuffer, u32 NumToRead);   		//read half word data(16 bits) from assign address

#ifdef __cplusplus
}
#endif 

#endif //#ifndef __flash_H__



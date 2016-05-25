#ifndef __wdg_wkup_H__
#define __wdg_wkup_H__

#ifdef __cplusplus
extern "C" {
#endif 

#include "stm32f4xx.h"

void HF_IWDG_Init(void);
void HF_IWDG_Feed(void);

void HF_WWDG_Init(u8 tr, u8 wr, u32 fprer);//Initialize WDG
void HF_WWDG_Set_Counter(u8 cnt);          //Set the counter of WDG

void HF_WKUP_Init(void);

#ifdef __cplusplus
}
#endif 

#endif //__wdg_wkup_H__



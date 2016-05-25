#ifndef CAN_H
#define CAN_H

#ifdef __cplusplus
extern "C" {
#endif 

#include "stm32f4xx.h"

#define MYCAN_ID  0x01

void HF_Can_Init(CAN_TypeDef *CANx, unsigned char GPIO_AF);
void Can_Tx_Message(CAN_TypeDef* CANx, uint8_t MY_ID, uint8_t Receiver_ID, uint8_t *TxBuf, uint8_t Length);

#ifdef __cplusplus
}
#endif 

#endif // #ifndef CAN_H



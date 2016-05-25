#ifndef SPI_H
#define SPI_H

#ifdef __cplusplus
extern "C" {
#endif 
	
#include "stm32f4xx.h"

//Initialize serial external interface of SPI, config SPI working on master mode
void HF_SPI_Init(SPI_TypeDef *SPIx, unsigned char GPIO_AF);     //SPI interface initialization, input parameter SPI1 SPI2
unsigned char HF_SPI_ReadWriteByte(SPI_TypeDef *SPIx, unsigned char TxData);      //SPI w/r data function

#ifdef __cplusplus
}
#endif 

#endif // #ifndef SPI_H



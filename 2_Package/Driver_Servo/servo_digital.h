#ifndef SERVO_DIGITAL_H
#define SERVO_DIGITAL_H

#include "servo_config.h"

#define SERVO_DEBUG_USART      USART1
#define SERVO_CONTROL_USART    USART3

#if HARDWARE_PLATFORM== 1 
// AX_IO CONFIG
#define RCC_AX_IO            RCC_APB1Periph_GPIOA
#define GPIO_AX_IO           GPIOA
#define GPIO_AX_IO_Pin       GPIO_Pin_4
#define AX_TXD               GPIO_SetBits(GPIO_AX_IO , GPIO_AX_IO_Pin)
#define AX_RXD               GPIO_ResetBits(GPIO_AX_IO , GPIO_AX_IO_Pin)
#endif

#if HARDWARE_PLATFORM== 4 
// AX_IO CONFIG
#define RCC_AX_IO            RCC_AHB1Periph_GPIOD
#define GPIO_AX_IO           GPIOD
#define GPIO_AX_IO_Pin       GPIO_Pin_10
#define AX_TXD               GPIO_SetBits(GPIO_AX_IO , GPIO_AX_IO_Pin)
#define AX_RXD               GPIO_ResetBits(GPIO_AX_IO , GPIO_AX_IO_Pin)
#endif

#define AX_MAX_NUM   20      //最大舵机编号,检测舵机号只检测从0到AX_MAX_NUM-1.

class ServoDigital
{
public:

    volatile uint8_t gbpParameter[128];				     //数据包缓存
    volatile uint8_t gbRxBufferReadPointer;
    volatile uint8_t gbpRxBuffer[128];				     //经过处理的缓冲数据
    volatile uint8_t gbpTxBuffer[128];				     //发送缓存
    volatile uint8_t gbRxBufferWritePointer;
    volatile uint8_t gbpRxInterruptBuffer[256];	         //中断接收的缓冲数据
    volatile uint8_t Timer_count;
    volatile uint8_t axOline[AX_MAX_NUM];
    volatile uint8_t axOlineNum;
    volatile uint8_t delayCount;

    ServoDigital();
    void axServoInit(void);
    void getServoConnective(void);
    void disableServo(uint8_t *p, uint8_t num);
    void enableServo(uint8_t *p, uint8_t num);

    uint8_t axSendPosition(uint8_t bID, uint16_t target_pos, uint16_t target_speed);
    uint16_t axReadPosition(uint8_t bID);

    void playMicroAction(uint8_t *p, uint16_t poolSize);

private:
    uint8_t TxPacket(uint8_t bID, uint8_t bInstruction, uint8_t bParameterLength);
    uint8_t RxPacket(uint8_t bRxPacketLength);
    uint8_t axPing(uint8_t bID);
    uint8_t axTorqueOn(uint8_t bID);
    uint8_t axTorqueOff(uint8_t bID);
    void  axTorqueOffAll(void);
    void  axTorqueOnAll(void);

    void TxPacketBroadSynWrite(uint8_t bInstruction, uint8_t bParameterLength);
    void changeServoID(uint8_t *p, uint8_t num);
    uint8_t axSendSpeed(uint8_t bID, uint16_t target_speed);
    void executeInstruction(uint8_t *p, uint8_t num);

    void  moveServoPosition(uint8_t *p, uint8_t num);
    void getServoPosition(uint8_t *p, uint8_t num);
    void moveServoPosWithSpeed(uint8_t *p, uint8_t num);

    void packageReplyToDebug(USART_TypeDef* USARTx, unsigned char command_type,unsigned char * data, unsigned int length); //length只包含data的长度

};

#endif  // #ifndef SERVO_DIGITAL_H


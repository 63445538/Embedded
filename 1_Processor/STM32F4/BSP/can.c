/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: can.c
* Contact:  QQ Exchange Group -- 521037187
* Version:  V2.0
*
* LICENSING TERMS:
* The Hands Free is licensed generally under a permissive 3-clause BSD license.
* Contributions are requiredto be made under the same license.
*
* History: 
* <author>      <time>      <version>      <desc>
* mawenke       2015.10.1   V1.0           creat this file
*
* Description: 
***********************************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif 

#include "can.h"
#include "nvic.h"

/***********************************************************************************************************************
***                                                                                                                  ***
***                                          CAN Interrupt Config                                                    ***
***                                                                                                                  ***
***********************************************************************************************************************/

//static void CAN1_NVIC_Configuration(void) 
//{
//	NVIC_InitTypeDef NVIC_InitStructure;
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		 	/*interrupt config*/
//	NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;	  //CAN1 RX0interrupt
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;		   //PreemptionPriority0
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			   //SubPriority0
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
//	
//}
//static void CAN2_NVIC_Configuration(void) 
//{
//	NVIC_InitTypeDef NVIC_InitStructure;
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		 	/*interrupt config*/
//	NVIC_InitStructure.NVIC_IRQChannel = CAN2_RX0_IRQn;	  //CAN1 RX0interrupt
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;		   //PreemptionPriority0
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			   //SubPriority0
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
//	
//}


/***********************************************************************************************************************
* Function:     void HF_Can_Init(void)
*
* Scope:        public
*
* Description:  can1 initialization
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:
***********************************************************************************************************************/
void HF_Can_Init(CAN_TypeDef *CANx , unsigned char GPIO_AF)
{
    
    CAN_InitTypeDef        CAN_InitStructure;
    CAN_FilterInitTypeDef  CAN_FilterInitStructure;
    GPIO_InitTypeDef  GPIO_InitStructure;
    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//Multiplexing
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//push-pull output
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//pull up
    
    if(CANx == CAN1){
        
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
        
        if(GPIO_AF == 0){
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
            GPIO_PinAFConfig(GPIOA, GPIO_PinSource12, GPIO_AF_CAN1); 	//Pin Multiplexing remapping to CAN1
            GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_CAN1);
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11| GPIO_Pin_12;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        }
        else if(GPIO_AF == 1){
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
            GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_CAN1);
            GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_CAN1);
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8| GPIO_Pin_9;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
        }
        else if(GPIO_AF == 2){
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
            GPIO_PinAFConfig(GPIOD, GPIO_PinSource0, GPIO_AF_CAN1);
            GPIO_PinAFConfig(GPIOD, GPIO_PinSource1, GPIO_AF_CAN1);
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0| GPIO_Pin_1;
            GPIO_Init(GPIOD, &GPIO_InitStructure);
            CAN1_RX1_NVIC_Configuration();
        }
        
    }
    else if(CANx == CAN2){
        
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2, ENABLE);
        
        if(GPIO_AF == 0){
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
            GPIO_PinAFConfig(GPIOB, GPIO_PinSource5,GPIO_AF_CAN2);
            GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_CAN2);
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5| GPIO_Pin_6;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
        }
        else if(GPIO_AF == 1){
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
            GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_CAN2);
            GPIO_PinAFConfig(GPIOB, GPIO_PinSource12, GPIO_AF_CAN2);
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12| GPIO_Pin_13;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
        }
        
        CAN2_NVIC_Configuration() ;
        
    }
    
    CAN_DeInit(CANx);
    CAN_StructInit(&CAN_InitStructure);
    CAN_InitStructure.CAN_TTCM = DISABLE;			  //MCR-TTCM  enable time touch communicate mode
    CAN_InitStructure.CAN_ABOM = DISABLE;			  //MCR-ABOM  auto manage offline
    CAN_InitStructure.CAN_AWUM = DISABLE;			  //MCR-AWUM  auto wake-up
    CAN_InitStructure.CAN_NART = DISABLE;			  //MCR-NART  禁止报文自动重传	  0-自动重传   1-报文只传一次
    //MCR-RFLM  接收FIFO 锁定模式  0-溢出时新报文会覆盖原有报文  1-溢出时，新报文丢弃
    CAN_InitStructure.CAN_RFLM = DISABLE;
    //MCR-TXFP  发送FIFO优先级 0-优先级取决于报文标示符 1-优先级取决于发送请求的顺序
    CAN_InitStructure.CAN_TXFP = ENABLE;
    CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;	  //BTR-SILM/LBKM   CAN normal communicate mode
    CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;		  //BTR-SJW 重新同步跳跃宽度 1个时间单元
    CAN_InitStructure.CAN_BS1 = CAN_BS1_9tq;		  //BTR-TS1 时间段1 占用了2个时间单元
    CAN_InitStructure.CAN_BS2 = CAN_BS2_4tq;		  //BTR-TS1 时间段2 占用了3个时间单元
    CAN_InitStructure.CAN_Prescaler =3;               //CAN BaudRate 42/(1+9+4)/3=1Mbps
    CAN_Init(CANx, &CAN_InitStructure);
    
    //配置过滤器
    CAN_FilterInitStructure.CAN_FilterNumber=0;	  //过滤器0
    CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask;
    CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit; //32位
    CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;////32位ID
    CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;//32位MASK
    CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;
    CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_Filter_FIFO1;//过滤器0关联到FIFO0
    CAN_FilterInitStructure.CAN_FilterActivation=ENABLE; //激活过滤器0
    CAN_FilterInit(&CAN_FilterInitStructure);//滤波器初始化
    
    CAN_ITConfig(CANx, CAN_IT_FMP1, ENABLE);  //中断使能
    CAN_ITConfig(CANx, CAN_IT_TME, ENABLE);
    
}	


/***********************************************************************************************************************
***                                                                                                                  ***
***                                         Interrupt Function                                                       ***
***                                                                                                                  ***
***********************************************************************************************************************/


/***********************************************************************************************************************
* Function:     void Can_Tx_Message(void)
*
* Scope:        public
*
* Description:  CAN Send one Message
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:
***********************************************************************************************************************/
void Can_Tx_Message(CAN_TypeDef* CANx , uint8_t Sender_ID  , uint8_t Receiver_ID , uint8_t *TxBuf , uint8_t Length)
{
    
    CanTxMsg TxMessageBuffer;
    uint8_t i;
    TxMessageBuffer.StdId=0x00;
    TxMessageBuffer.ExtId=( (Sender_ID << 8) | Receiver_ID ); //Sender ID | Receiver ID
    TxMessageBuffer.RTR=CAN_RTR_DATA;	     // 传输消息的帧类型为数据帧（还有远程帧）
    TxMessageBuffer.IDE=CAN_ID_EXT;		     // 消息标志符实验标准标识符
    
    TxMessageBuffer.DLC=Length;				 // 发送两帧，一帧8位
    
    for(i=0;i<Length;i++)
    {
        TxMessageBuffer.Data[i]=*(TxBuf+i);
    }
    
    CAN_Transmit(CANx, &TxMessageBuffer);
    
}	

#ifdef __cplusplus
}
#endif


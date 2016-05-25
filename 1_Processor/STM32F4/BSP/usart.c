/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: usart.c
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
* Description:    STM32F4 Initialization of USART
***********************************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif 

#include "usart.h"
#include "nvic.h"

/***********************************************************************************************************************
***                                                                                                                  ***
***                                  USART Interruption Configuration                                                ***
***                                                                                                                  ***
***********************************************************************************************************************/

//void USART1_NVIC_Configuration(void) 
//{
//	NVIC_InitTypeDef NVIC_InitStructure;
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  
//	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;    
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //PreemptionPriority  0--4 Lower value, Higher Priority.
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;	      //SubPriority 0--4 Lower value, Higher Priority.
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		      //ENABLE Interrupt
//	NVIC_Init(&NVIC_InitStructure); 
//}	

//void USART2_NVIC_Configuration(void) 
//{
//	NVIC_InitTypeDef NVIC_InitStructure;
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  
//	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;     
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //PreemptionPriority  0--4 Lower value, Higher Priority.
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;	       //SubPriority 0--4 Lower value, Higher Priority.
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		       //ENABLE Interrupt
//	NVIC_Init(&NVIC_InitStructure); 
//}	


//void USART3_NVIC_Configuration(void) 
//{
//	NVIC_InitTypeDef NVIC_InitStructure;
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  
//	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;    
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //PreemptionPriority  0--4 Lower value, Higher Priority.
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;	       //SubPriority 0--4 Lower value, Higher Priority.
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		       //ENABLE Interrupt
//	NVIC_Init(&NVIC_InitStructure); 
//}	

//void UART4_NVIC_Configuration(void) 
//{
//	NVIC_InitTypeDef NVIC_InitStructure;
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  
//	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;     
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //PreemptionPriority  0--4 Lower value, Higher Priority.
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;	       //SubPriority 0--4 Lower value, Higher Priority.
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		       //ENABLE Interrupt
//	NVIC_Init(&NVIC_InitStructure); 
//}	


//void UART5_NVIC_Configuration(void) 
//{
//	NVIC_InitTypeDef NVIC_InitStructure;
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  
//	NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;     
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //PreemptionPriority  0--4 Lower value, Higher Priority.
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;	       //SubPriority 0--4 Lower value, Higher Priority.
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		       //ENABLE Interrupt
//	NVIC_Init(&NVIC_InitStructure); 
//}	

//void USART6_NVIC_Configuration(void) 
//{
//	NVIC_InitTypeDef NVIC_InitStructure;
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  
//	NVIC_InitStructure.NVIC_IRQChannel = USART6_IRQn;     
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //PreemptionPriority  0--4 Lower value, Higher Priority.
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;	       //SubPriority 0--4 Lower value, Higher Priority.
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		       //ENABLE Interrupt
//	NVIC_Init(&NVIC_InitStructure); 
//}	


/***********************************************************************************************************************
* Function:     HF_Usart_Init(USART_TypeDef* USARTx,u32 bound)
*
* Scope:        public
*
* Description:  Initialize USART 
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:
***********************************************************************************************************************/
void HF_Usart_Init(USART_TypeDef* USARTx , unsigned int BaudRate , unsigned char GPIO_AF)
{

    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    GPIO_StructInit(&GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//Multiplexing
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//frequency 50MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //Multiplexing push-pull output
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;   //pull up
    
    if(USARTx==USART1){
        
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
        
        if(GPIO_AF == 0){
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
            GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);
            GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
            GPIO_Init(GPIOA,&GPIO_InitStructure);
        }
        else if(GPIO_AF == 1){
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
            GPIO_PinAFConfig(GPIOB,GPIO_PinSource6,GPIO_AF_USART1);
            GPIO_PinAFConfig(GPIOB,GPIO_PinSource7,GPIO_AF_USART1);
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
            GPIO_Init(GPIOB,&GPIO_InitStructure);
        }
        USART1_NVIC_Configuration();
    }
    else if(USARTx==USART2){
        
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
        
        if(GPIO_AF == 0) {
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
            GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2);
            GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2);
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        }
        else if(GPIO_AF == 1){
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
            GPIO_PinAFConfig(GPIOD,GPIO_PinSource5,GPIO_AF_USART2);
            GPIO_PinAFConfig(GPIOD,GPIO_PinSource6,GPIO_AF_USART2);
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6;
            GPIO_Init(GPIOD, &GPIO_InitStructure);
        }
        
        USART2_NVIC_Configuration();
        
    }
    
    else if(USARTx==USART3){
        
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
        
        if(GPIO_AF == 0){
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
            GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_USART3);
            GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3);
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
        }
        else if(GPIO_AF == 1){
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
            GPIO_PinAFConfig(GPIOC,GPIO_PinSource10,GPIO_AF_USART3);
            GPIO_PinAFConfig(GPIOC,GPIO_PinSource11,GPIO_AF_USART3);
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;
            GPIO_Init(GPIOC, &GPIO_InitStructure);
        }
        else if(GPIO_AF == 2){
            
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
            GPIO_PinAFConfig(GPIOD,GPIO_PinSource8,GPIO_AF_USART3);
            GPIO_PinAFConfig(GPIOD,GPIO_PinSource9,GPIO_AF_USART3);
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;
            GPIO_Init(GPIOD, &GPIO_InitStructure);
        }
        
        USART3_NVIC_Configuration();
    }
    else if(USARTx==UART4){
        
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
        
        if(GPIO_AF == 0)
        {
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
            GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_UART4);
            GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_UART4);
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        }
        else if(GPIO_AF == 1){
            
        }
        UART4_NVIC_Configuration();
    }
    else if(USARTx==UART5){
        
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);
        
        if(GPIO_AF == 0)
        {
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOD, ENABLE);
            GPIO_PinAFConfig(GPIOC,GPIO_PinSource12,GPIO_AF_UART5);
            GPIO_PinAFConfig(GPIOD,GPIO_PinSource2,GPIO_AF_UART5);
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
            GPIO_Init(GPIOC, &GPIO_InitStructure);
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
            GPIO_Init(GPIOD, &GPIO_InitStructure);
        }
        else if(GPIO_AF == 1){
            
        }
        UART5_NVIC_Configuration();
        
    }
    else if(USARTx==USART6){
        
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6,ENABLE);
        
        if(GPIO_AF == 0)
        {
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
            GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_USART6);
            GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_USART6);
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
            GPIO_Init(GPIOC,&GPIO_InitStructure);
        }
        else if(GPIO_AF == 1)
        {
            
        }
        USART6_NVIC_Configuration();
    }
    
    USART_InitStructure.USART_BaudRate = BaudRate ;  //set naud rate 9600 115200 256000 921600
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USARTx, &USART_InitStructure);
    
    USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE); //enable interrupt
    USART_ClearITPendingBit(USARTx, USART_IT_RXNE);
    USART_Cmd(USARTx, ENABLE);                     //enable usart
    
}

/***********************************************************************************************************************
* Function:     void Usart_Put_Char(USART_TypeDef* USARTx  , unsigned char Tx_Byte)
*
* Scope:        public
*
* Description:  USARTx prints 1 byte
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:
***********************************************************************************************************************/
void Usart_Put_Char(USART_TypeDef* USARTx  , unsigned char Tx_Byte)
{
    USART_SendData(USARTx , Tx_Byte);
    while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
}

/***********************************************************************************************************************
* Function:     int fputc(int ch, FILE *f)
*
* Scope:        public
*
* Description:  support printf function without tick use MicroLIB	
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:
***********************************************************************************************************************/
#ifdef __cplusplus                      //if use C++ compiler   

#pragma import(__use_no_semihosting)    //add this line and you do not need to tick use micro lib   

//support function that standard library  need             
struct std::__FILE 
{ 
    int handle;
}; 

std::FILE __stdout;   

//define sys_exit() to avoid half-master mode
void _sys_exit(int x) 
{ 
    x = x;
} 

int std::fputc(int ch, std::FILE *f) 
{ 
    while((USART1->SR&0X40)==0);         //cycle send until succeed
    USART1->DR = (u8) ch;
    return ch;
}

#else                                   //if use C compiler

#pragma import(__use_no_semihosting)    //add this line and you do not need to tick use micro lib       
//support function that standard library  need             
struct __FILE 
{ 
    int handle;
}; 

FILE __stdout;   

//define sys_exit() to avoid half-master mode
void _sys_exit(int x) 
{ 
    x = x;
} 

//Redirect fput
int fputc(int ch, FILE *f)
{ 	
    while((USART1->SR&0X40)==0);//cycle send until succeed
    USART1->DR = (u8) ch;
    return ch;
}

#endif

/***********************************************************************************************************************
* Function:     static char *itoa(int value, char *string, int radix)
*
* Scope:        private
*
* Description:  transform int type data to char type data
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:
***********************************************************************************************************************/
static char *itoa(int value, char *string, int radix)
{
    int     i, d;
    int     flag = 0;
    char    *ptr = string;
    
    /* This implementation only works for decimal numbers. */
    if (radix != 10)
    {
        *ptr = 0;
        return string;
    }
    
    if (!value)
    {
        *ptr++ = 0x30;
        *ptr = 0;
        return string;
    }
    
    /* if this is a negative value insert the minus sign. */
    if (value < 0)
    {
        *ptr++ = '-';
        
        /* Make the value positive. */
        value *= -1;
    }
    
    for (i = 10000; i > 0; i /= 10)
    {
        d = value / i;
        
        if (d || flag)
        {
            *ptr++ = (char)(d + 0x30);
            value -= (d * i);
            flag = 1;
        }
    }
    
    /* Null terminate the string. */
    *ptr = 0;
    
    return string;
    
} /* NCL_Itoa */


/***********************************************************************************************************************
* Function:     void USART_printf(USART_TypeDef* USARTx, uint8_t *Data,...)
*
* Scope:        public
*
* Description:  格式化输出，类似于C库中的printf，但这里没有用到C库
*   典型应用    USART_printf( USART1, "\r\n this is a demo \r\n" );
*            		USART_printf( USART1, "\r\n %d \r\n", i );
*            		USART_printf( USART1, "\r\n %s \r\n", j );
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:
***********************************************************************************************************************/
void USART_printf(USART_TypeDef* USARTx, uint8_t *Data,...)
{
    const char *s;
    int d;
    char buf[16];
    
    va_list ap;
    va_start(ap, Data);
    
    while ( *Data != 0)     // 判断是否到达字符串结束符
    {
        if ( *Data == 0x5c )  //'\'
        {
            switch ( *++Data )
            {
            case 'r':							          //回车符
                USART_SendData(USARTx, 0x0d);
                Data ++;
                break;
                
            case 'n':							          //换行符
                USART_SendData(USARTx, 0x0a);
                Data ++;
                break;
                
            default:
                Data ++;
                break;
            }
        }
        else if ( *Data == '%')
        {
            switch ( *++Data )
            {
            case 's':										  //字符串
                s = va_arg(ap, const char *);
                for ( ; *s; s++)
                {
                    USART_SendData(USARTx,*s);
                    while( USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET );
                }
                Data++;
                break;
                
            case 'd':										//十进制
                d = va_arg(ap, int);
                itoa(d, buf, 10);
                for (s = buf; *s; s++)
                {
                    USART_SendData(USARTx,*s);
                    while( USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET );
                }
                Data++;
                break;
            default:
                Data++;
                break;
            }
        } /* end of else if */
        else USART_SendData(USARTx, *Data++);
        while( USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET );
    }
}

#ifdef __cplusplus
}
#endif 

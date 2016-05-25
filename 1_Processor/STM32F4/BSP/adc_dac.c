/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: adc_dac.c
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
* Lidexin       2016.1.16   V1.58
*
* Description: use to  ADC, and use DMA
*        STM32F4--------------
*        ADC0 - PA0	-	ADC_IN0
*        ADC1	-	PA1	-	ADC_IN1
*        ADC2	-	PA2	-	ADC_IN2
*        ADC3	-	PA3	-	ADC_IN3
*        ADC4	-	PA4	-	ADC_IN4
*        ADC5	-	PA5	-	ADC_IN5
*        ADC6	-	PA6	-	ADC_IN6
*        ADC7	-	PA7	-	ADC_IN7
*
*        ADC8	-	PB0	-	ADC_IN8
*        ADC9	-	PB1	-	ADC_IN9
***********************************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif 

#include "adc_dac.h"
#include "delay.h"

ADC_DAC_Data adc_dac_data_r;

/***********************************************************************************************************************
***                                                                                                                  ***
***                                        ADC Initialization                                                        ***
***                                                                                                                  ***
***********************************************************************************************************************/

#define ADC1_DR_Address    ((u32)0x4001204c)
#define V25  0x6EE    //4.3mV every temperature degree, correspond 0x05 every temperture degree
#define AVG_SLOPE 0x05 

/***********************************************************************************************************************
* Function:     static void ADC1_GPIO_Config(void)
*
* Scope:        private
*
* Description:  ADC GPIO configuration
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:
***********************************************************************************************************************/
static void ADC_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC, ENABLE);
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;   //analog input
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;//no pull up or down

#if ADC_IN0 == 1
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
#endif
    
#if ADC_IN1 == 1
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
#endif
    
#if ADC_IN2 == 1
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
#endif
    
#if ADC_IN3 == 1
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
#endif
    
#if ADC_IN4 == 1
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
#endif
    
#if ADC_IN5 == 1
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
#endif
    
#if ADC_IN6 == 1
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
#endif
    
#if ADC_IN7 == 1
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
#endif
    
#if ADC_IN8 == 1
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
#endif
    
#if ADC_IN9 == 1
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
#endif

#if ADC_IN10 == 1
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
#endif

#if ADC_IN11 == 1
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
#endif


#if ADC_IN12 == 1
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
#endif


#if ADC_IN13 == 1
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
#endif


#if ADC_IN14 == 1
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
#endif

#if ADC_IN15 == 1
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
#endif


#if ADC_IN16 == 1

#endif
    
}

/***********************************************************************************************************************
* Function:     static void ADC1_Mode_Config(void)
*
* Scope:        private
*
* Description:  configure working mode of ADC in MDA mode
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:
***********************************************************************************************************************/
static void ADC_Mode_Config(void)
{
    DMA_InitTypeDef DMA_InitStructure;
    ADC_InitTypeDef ADC_InitStructure;
    ADC_CommonInitTypeDef ADC_CommonInitStructure;
    unsigned char ADC_ADC_Channel;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
    DMA_DeInit(DMA2_Stream0);
    DMA_InitStructure.DMA_Channel = DMA_Channel_0;
    DMA_InitStructure.DMA_PeripheralBaseAddr =ADC1_DR_Address;
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)adc_dac_data_r.ADC_Sample_Value;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
    DMA_InitStructure.DMA_BufferSize = ADC_NUM;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
    DMA_Init(DMA2_Stream0, &DMA_InitStructure);
    DMA_Cmd(DMA2_Stream0, ENABLE);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 , ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,ENABLE);	  //ADC1 reset
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,DISABLE);	//end reset
    ADC_CommonInitStructure.ADC_Mode = ADC_DualMode_RegSimult; //ADC_Mode_Independent;//indepedent ADC mode
    //delay 5 clock period between 2 collection
    ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
    ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_1; //DMA enable
    /*configure ADC clock, the frequency must below 36MHz*/
    ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;
    ADC_CommonInit(&ADC_CommonInitStructure);
    
    ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;//12 BIT mode
    ADC_InitStructure.ADC_ScanConvMode = ENABLE; //DISABLE;//disable scan mode
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;//enable continuous convert mode
    //not use external interrupt to start convert
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
    ADC_InitStructure.ADC_ExternalTrigConv=ADC_ExternalTrigConv_T1_CC1;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//align right
    ADC_InitStructure.ADC_NbrOfConversion = ADC_NUM;//number of channel need be convert
    ADC_Init(ADC1, &ADC_InitStructure);//ADC initialize
    
    ADC_ADC_Channel = 0;
    
#if ADC_IN0 == 1
    ADC_RegularChannelConfig(ADC1, ADC_Channel_0, ++ADC_ADC_Channel , ADC_SampleTime_84Cycles);
#endif
    
#if ADC_IN1 == 1
    ADC_RegularChannelConfig(ADC1, ADC_Channel_1, ++ADC_ADC_Channel , ADC_SampleTime_84Cycles);
#endif
    
#if ADC_IN2 == 1
    ADC_RegularChannelConfig(ADC1, ADC_Channel_2,  ++ADC_ADC_Channel , ADC_SampleTime_84Cycles);
#endif
    
#if ADC_IN3 == 1
    ADC_RegularChannelConfig(ADC1, ADC_Channel_3,  ++ADC_ADC_Channel , ADC_SampleTime_84Cycles);
#endif
    
#if ADC_IN4 == 1
    ADC_RegularChannelConfig(ADC1, ADC_Channel_4,  ++ADC_ADC_Channel , ADC_SampleTime_84Cycles);
#endif
    
#if ADC_IN5 == 1
    ADC_RegularChannelConfig(ADC1, ADC_Channel_5,  ++ADC_ADC_Channel , ADC_SampleTime_84Cycles);
#endif
    
#if ADC_IN6 == 1
    ADC_RegularChannelConfig(ADC1, ADC_Channel_6,  ++ADC_ADC_Channel , ADC_SampleTime_84Cycles);
#endif
    
#if ADC_IN7 == 1
    ADC_RegularChannelConfig(ADC1, ADC_Channel_7,  ++ADC_ADC_Channel , ADC_SampleTime_84Cycles);
#endif
    
#if ADC_IN8 == 1
    ADC_RegularChannelConfig(ADC1, ADC_Channel_8,  ++ADC_ADC_Channel , ADC_SampleTime_84Cycles);
#endif
    
#if ADC_IN9 == 1
    ADC_RegularChannelConfig(ADC1, ADC_Channel_9,  ++ADC_ADC_Channel , ADC_SampleTime_84Cycles);
#endif

#if ADC_IN10 == 1
    ADC_RegularChannelConfig(ADC1, ADC_Channel_10,  ++ADC_ADC_Channel , ADC_SampleTime_84Cycles);
#endif

#if ADC_IN11 == 1
    ADC_RegularChannelConfig(ADC1, ADC_Channel_11,  ++ADC_ADC_Channel , ADC_SampleTime_84Cycles);
#endif
    
#if ADC_IN12 == 1
    ADC_RegularChannelConfig(ADC1, ADC_Channel_12,  ++ADC_ADC_Channel , ADC_SampleTime_84Cycles);
#endif
    
#if ADC_IN13 == 1
    ADC_RegularChannelConfig(ADC1, ADC_Channel_13,  ++ADC_ADC_Channel , ADC_SampleTime_84Cycles);
#endif

#if ADC_IN14 == 1
    ADC_RegularChannelConfig(ADC1, ADC_Channel_14,  ++ADC_ADC_Channel , ADC_SampleTime_84Cycles);
#endif

#if ADC_IN15 == 1
    ADC_RegularChannelConfig(ADC1, ADC_Channel_15,  ++ADC_ADC_Channel , ADC_SampleTime_84Cycles);
#endif

#if ADC_IN16 == 1
    //set collect channel IN16,set collect time
    ADC_RegularChannelConfig(ADC1, ADC_Channel_16,  ++ADC_ADC_Channel , ADC_SampleTime_84Cycles);
    //enable inner standard voltage and temperture sensor
    ADC_TempSensorVrefintCmd(ENABLE);
#endif

    //Enable DMA request after last transfer(Sing-ADC mode)
    ADC_MultiModeDMARequestAfterLastTransferCmd(ENABLE);
    ADC_DMARequestAfterLastTransferCmd (ADC1,ENABLE);
    ADC_DMACmd(ADC1, ENABLE);
    ADC_Cmd(ADC1, ENABLE);//enable ADC
    ADC_SoftwareStartConv(ADC1);
}


/***********************************************************************************************************************
* Function:     void ADC_Moder_Init(void)
*
* Scope:        public
*
* Description:  ADC initialize
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:
***********************************************************************************************************************/
void HF_ADC_Moder_Init(void)
{
    ADC_GPIO_Config();
    ADC_Mode_Config();
}

/***********************************************************************************************************************
* Function:     void ADC_Data_Anl(void)
*
* Scope:        public
*
* Description:  external call, data will update once be called.  Suggest call it every 10ms.
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:
***********************************************************************************************************************/
void HF_ADC_Data_Anl(void)
{
    uint8_t i;
    for(i=0 ; i<ADC_NUM ; i++){
        adc_dac_data_r.ADC_Standard_Value[i] = ( (float)adc_dac_data_r.ADC_Sample_Value[i]/4096 ) * (float)3.3;
    }
    //adc_dac_data_r.Battery_Voltage = adc_dac_data_r.ADC_Standard_Value[0]*11;
    adc_dac_data_r.Cpu_Standard_T = ( (float)V25- adc_dac_data_r.ADC_Standard_Value[ADC_NUM-1] ) / (float)AVG_SLOPE+25;
}

/**********************************************************************************************************************
***                                                                                                                 ***
***                                      DAC Initialization                                                         ***
***                                                                                                                 ***
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function:     void Dac_Init(unsigned int DAC_Channel_x)
*
* Scope:        public
*
* Description:  DAC Output Initialization
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:
***********************************************************************************************************************/
void HF_Dac_Init(unsigned int DAC_Channel_x)
{
    
    GPIO_InitTypeDef GPIO_InitStructure;
    DAC_InitTypeDef DAC_InitType;
    
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE );	  //enable PORTA clock
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE );	    //enable DAC clock
    
    DAC_InitType.DAC_Trigger=DAC_Trigger_None;	   //disable trigger, TEN1=0
    DAC_InitType.DAC_WaveGeneration=DAC_WaveGeneration_None;//disable wave generate
    DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;//mask amplitude set
    DAC_InitType.DAC_OutputBuffer=DAC_OutputBuffer_Disable ;	//disable DAC1  output cache,  BOFF1=1
    
    if(DAC_Channel_x == DAC_Channel_1)
    {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;				  // GPIO configuration
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;      //Analog Input
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;     //pull down
        GPIO_Init(GPIOA, &GPIO_InitStructure);
        
        DAC_Init(DAC_Channel_1,&DAC_InitType);	  //initialize DAC output channel1
        DAC_Cmd(DAC_Channel_1, ENABLE);           //enable DAC1
        DAC_SetChannel1Data(DAC_Align_12b_R, 0);  //12 Bits align right mode to set value of DAC
        
    }
    else 	if(DAC_Channel_x == DAC_Channel_2)
    {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;		   // GPIO Configuration
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;       //Analog Input
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;     //pull down
        GPIO_Init(GPIOA, &GPIO_InitStructure);
        
        DAC_Init(DAC_Channel_2,&DAC_InitType);	 //initialize DAC output channel1
        DAC_Cmd(DAC_Channel_2, ENABLE);  //enable DAC1
        DAC_SetChannel2Data(DAC_Align_12b_R, 0);  //12 Bits align right mode to set value of DAC
        
    }
    
    adc_dac_data_r.DAC_C_1 = 0;
    adc_dac_data_r.DAC_C_2 = 0;
}

/***********************************************************************************************************************
* Function:     void Dac_Set_Vol(unsigned int DAC_Channel_x , unsigned  short int  vol) 
*
* Scope:        public
*
* Description:  DAC_Channel_x = DAC_Channel_1|| DAC_Channel_2 vol:0~3300,  represent : 0~3.3V
*               set voltage of output Channelx
*
* Arguments:
*
* Return:
*
* Cpu_Time:  
*
* History:
***********************************************************************************************************************/
void HF_Dac_Set_Vol(unsigned int DAC_Channel_x , unsigned  short int  vol) 
{  
    float temp=vol;
    temp/=1000;
    temp=temp*4096/(float)3.3;
    if( DAC_Channel_x == DAC_Channel_1){
        DAC_SetChannel1Data(DAC_Align_12b_R,temp);//12 Bits align right mode to set value of DAC
        adc_dac_data_r.DAC_C_1 = vol ;
    }
    else if(DAC_Channel_x == DAC_Channel_2){
        DAC_SetChannel2Data(DAC_Align_12b_R,temp);//12 Bits align right mode to set value of DAC
        adc_dac_data_r.DAC_C_2 = vol ;
    }
}


#ifdef __cplusplus
}
#endif 


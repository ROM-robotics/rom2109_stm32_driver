/*******************************************************************************
 *                    ROM ROBOTICS Co,.Ltd ( Myanmar )    										 *
 *			(ɔ) COPYLEFT 2021		| www.romrobots.com | (+95) 9-259-288-229 				 *
 *******************************************************************************/ 
 
#include "usart.h"
#include "stdio.h"
#include "string.h"
// usart1(tx) dma1 channel 4, usart1(rx) dma1 channel 5

static void NVIC_Configuration(void)
{
	//Usart1 NVIC 
	NVIC_InitTypeDef NVIC_InitStructure;
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;																	//
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=6;														//
		NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;																	//
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;																		// 
		NVIC_Init(&NVIC_InitStructure);	
}

void usart1Init(uint32_t bound)
{
	//======================================================= GPIO 
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);			// not to share pin, but Synchronous logic likes its clock to be ticking, CMOS consumes little when its not.
	
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;								// PA9 , TX
		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;			 		// ALTERNATE PUSH PULL
		GPIO_Init(GPIOA,&GPIO_InitStructure);					
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;							// PA10, RX
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;		// INPUT FLOAT 
		GPIO_Init(GPIOA,&GPIO_InitStructure);		
	
	
	//==================================================================================USART1
	USART_InitTypeDef USART_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
		USART_InitStructure.USART_BaudRate = bound;																				// BRR 
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;											  // CR1 -> M    -> 0  , 8bits
		USART_InitStructure.USART_StopBits = USART_StopBits_1;														// CR2 -> STOP -> 00 ( 1 stop bit )
		USART_InitStructure.USART_Parity = USART_Parity_No;				  											// CR1 -> PCE  -> 0  ( parity control disable )
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;   // CR3 -> CTSE -> 0	 ( hardware flow control disable )
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;										// CR1 -> TE,RE-> 1   , both receive and transmit enable
		USART_Init(USART1, &USART_InitStructure);	
		
		USART_ClearFlag(USART1, USART_FLAG_TC); 																					// SR -> TC ->   , clear transmission complete ( USART_SR_TC )
		//USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);																	// CR1-> RXNEIE receive interrupt enable ( check SR-> RXNE or SR->ORE )
		
		NVIC_Configuration();
		
		/**********  USE_USART1_DMA_RX   **********/
		// open serial idle IDL interrupt
		USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);																		// CR1-> IDLEIE , idle interrupt enable ( check SR-> IDLE -> 1 )
		// enable serial DMA reception
		USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE);																		// CR3-> DMAR , DMA enable receiver
		// enable serial DMA
		USART1_DMA_Rx_Config();
	
		/**********  USE_USART1_DMA_TX   **********/
		// enable serial DMA Transmission
		// USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
		// USART1_DMA_Tx_Config();
		
		USART_Cmd(USART1, ENABLE);																												// CR1-> UE -> 1 , usart enable

	
}


static void USART1_DMA_Rx_Config(void)
{
	DMA_InitTypeDef dma_structure;
	
	// turn on DMA clock
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	// set DMA source address: serial port data register address
  dma_structure.DMA_PeripheralBaseAddr = (uint32_t) &USART1->DR;				// DMA1_Channel5->CPAR
	// memory address ( pointer to variable transfer ) 
	dma_structure.DMA_MemoryBaseAddr = (uint32_t) &Usart_Rx_Buf;					// DMA1_Channel5->CMAR
	// transmission size
	dma_structure.DMA_BufferSize = USART_RX_BUFF_SIZE;										// DMA1_Channel5->CNDTR = 4
	
	// disable memory to memory transfer 												      		// DMA1_Channel5->CCR |= 0<<14; MEM2MEM
	dma_structure.DMA_M2M = DMA_M2M_Disable;
	// priority: medium																										// DMA1_Channel5->CCR |= 3<<12; PL
	dma_structure.DMA_Priority = DMA_Priority_VeryHigh;
	// memory data unit						memory size															// DMA1_Channel5->CCR |= 0<<10; 8bits MSIZE
	dma_structure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	// peripheral data unit				peripheral size 												// DMA1_Channel5->CCR |= 0<<8; 8bits PSIZE
	dma_structure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	// memory address auto increment																			// DMA1_Channel5->CCR |= 1<<7; MINC
	dma_structure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	// peripheral address does not increase																// DMA1_Channel5->CCR |= 0<<6; PINC
	dma_structure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	// DMA mode, once or cycle mode																				// DMA1_Channel5->CCR |= 1<<5; CIRC
	//dma_structure.DMA_Mode = DMA_Mode_Normal;														
	dma_structure.DMA_Mode = DMA_Mode_Circular;
	// Direction: read from peripheral               								  		// DMA1_Channel5->CCR |= 0<<4; DIR
	dma_structure.DMA_DIR = DMA_DIR_PeripheralSRC; 
	
	// configure DMA channel
	DMA_Init(USART_RX_DMA_CHANNEL, &dma_structure);
	// clear all DMA flags																								// DMA1_Channel5->IFCR
	DMA_ClearFlag(DMA1_FLAG_TC5);
	// transfer error interrupt enable																		// DMA1_Channel5->CCR |= 1<<3; TEIE
	DMA_ITConfig(USART_RX_DMA_CHANNEL, DMA_IT_TE, ENABLE);
	// enabling DMA
	DMA_Cmd( USART_RX_DMA_CHANNEL, ENABLE);																// DMA1_Channel5->CCR |= 1;    EN 
}


/*******************************************************************************
 *                          USART1_IRQHandler																	 *
 *******************************************************************************/ 
void USART1_IRQHandler(void)									 
{
	if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)									// if receive interrupt flag is set
	{
		/* RECEIVE DATA */																
		Receive_DataPack();																									//(USART1->DR);
		// clear the interrupt flag bit
		USART_ReceiveData(USART1);																					// it is clearl automatically when calling USART_SendData() or  USART_ReceiveData()
	} 
} 	

void Receive_DataPack(void)
{
	// received data length
	uint32_t buff_length;
	
	// turn off DMA to prevant interface
	DMA_Cmd(USART_RX_DMA_CHANNEL, DISABLE); // DMA is temporarily shutdown, data has not been processed
	
	// clear DMA flag
	DMA_ClearFlag( DMA1_FLAG_TC5 );         // i think DMA_IFCR BIT 17 CTCIF5 ( not confirm )
	
	// get the received data length in bytes
	buff_length = USART_RX_BUFF_SIZE - DMA_GetCurrDataCounter(USART_RX_DMA_CHANNEL);
	
	// get data length
	Rx_strLength = buff_length;
	
	//PRINT_DEBUG( buff_length = "%d\n", buff_length);
	
	/* Reassign the count value, which must be greater than or equal to the maximum possible number of data frames received */
	USART_RX_DMA_CHANNEL->CNDTR = USART_RX_BUFF_SIZE;								// DMA1_CNDTR , number of data register
	
	
	
	// copy data and process()------------------------------------------------------------------------>>>>
	
	memcpy( Received_Rx_Buf, Usart_Rx_Buf, Rx_strLength);
	
	// copy data and process()------------------------------------------------------------------------>>>>
	
	
	
	/* Yout should open it after processing the data, such as in datapack process() */
	DMA_Cmd(USART_RX_DMA_CHANNEL, ENABLE);					
	
	/* (OS) Give a signal, send and receive a new data flag for ther foreground program to query */
	
	
	/* Mark receiving completed, and handle in datapack */
	Rx_strLength |= 0xC000;   // MARKER FLAG
	
	/*
		DMA open, wait for data, Note that if the rate of interrupt sending data frame is very fast, MCU can not process the received data.
		If the interrupt sends data again, it cannot be enabled here, otherwise the data will be overwritten. There are two solutions;
		
		1. Before reopening the receiving DMA channel, copy the data in Rx buf buffer to another array.
			 Then turn on DMA and process the copied data immediately.
			 
	  2. Set up double buffer, reconfigure the buffer address of DMA - memorybaseaddr, then the next received data will save to a new buffer without being overwritten.
	*/
	
}


/*******************************************************************************
 *                    printf() and related function for Tx										 *
 *******************************************************************************/ 


void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{

	USART_SendData(pUSARTx,ch);
		

	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}


void Usart_SendArray( USART_TypeDef * pUSARTx, uint8_t *array, uint16_t num)
{
  uint8_t i;
	
	for(i=0; i<num; i++)
  {

	    Usart_SendByte(pUSARTx,array[i]);	
  
  }

	while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET);
}


void Usart_SendString( USART_TypeDef * pUSARTx, char *str)
{
	unsigned int k=0;
  do 
  {
      Usart_SendByte( pUSARTx, *(str + k) );
      k++;
  } while(*(str + k)!='\0');
  
  
  while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET)
  {}
}



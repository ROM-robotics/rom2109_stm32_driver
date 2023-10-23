/*******************************************************************************
 *                    ROM ROBOTICS Co,.Ltd ( Myanmar )    										 *
 *			(ɔ) COPYLEFT 2021		| www.romrobots.com | (+95) 9-259-288-229 				 *
 *******************************************************************************/ 
#ifndef _ROM_USART_H_
#define _ROM_USART_H_
#include <stdio.h>
#include "stm32f10x.h"
#include "stm32f10x_dma.h"
#include "sys.h" 


// USART2 ---------------------------------------------------------------------------------------------//
#define  USE_USART2_DMA_RX  	1
#define  USART2_RX_DMA_CHANNEL     DMA1_Channel6
#define  USART2_DR_ADDRESS        (&USART2->DR)
#define  USART2_RX_BUFF_SIZE            24  // original 15 

extern uint8_t Usart_Rx_Buf_2[USART2_RX_BUFF_SIZE];
extern uint8_t Received_Rx_Buf_2[USART2_RX_BUFF_SIZE];
extern uint16_t Rx_strLength_2;

#define  USE_USART2_DMA_TX 	1
#define  USART2_TX_DMA_CHANNEL     DMA1_Channel7
#define  USART2_DR_ADDRESS        (&USART2->DR)
#define  USART2_TX_BUFF_SIZE            1000 

extern uint8_t Usart_Tx_Buf_2[USART2_TX_BUFF_SIZE];

//--------------------------------------------------------

void usart2Init(uint32_t bound);

//------------------------------------

static void USART2_DMA_Rx_Config(void);

static void NVIC_Configuration_2(void);
void Receive_DataPack_2(void);

void Usart_SendByte_2( USART_TypeDef * pUSARTx, uint8_t ch);
void Usart_SendString_2( USART_TypeDef * pUSARTx, char *str);
void Usart_SendArray_2( USART_TypeDef * pUSARTx, uint8_t *array, uint16_t num);

// END USART2 //
#endif



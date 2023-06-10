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


#define  USE_USART_DMA_RX  	1
#define  USART_RX_DMA_CHANNEL     DMA1_Channel5
#define  USART_DR_ADDRESS        (&USART1->DR)
#define  USART_RX_BUFF_SIZE            24  // original 15 
extern uint8_t Usart_Rx_Buf[USART_RX_BUFF_SIZE];
extern uint8_t Received_Rx_Buf[USART_RX_BUFF_SIZE];
extern uint16_t Rx_strLength;

#define  USE_USART_DMA_TX 	1
#define  USART_TX_DMA_CHANNEL     DMA1_Channel4
#define  USART_DR_ADDRESS        (&USART1->DR)
#define  USART_TX_BUFF_SIZE            1000 
extern uint8_t Usart_Tx_Buf[USART_TX_BUFF_SIZE];

//--------------------------------------------------------

void usart1Init(uint32_t bound);

//------------------------------------

static void USART1_DMA_Rx_Config(void);
static void NVIC_Configuration(void);
void Receive_DataPack(void);

void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch);
void Usart_SendString( USART_TypeDef * pUSARTx, char *str);
void Usart_SendArray( USART_TypeDef * pUSARTx, uint8_t *array, uint16_t num);


#endif



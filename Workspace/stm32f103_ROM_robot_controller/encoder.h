/*******************************************************************************
 *                    ROM ROBOTICS Co,.Ltd ( Myanmar )    										 *
 *			(ɔ) COPYLEFT 2021		| www.romrobots.com | (+95) 9-259-288-229 				 *
 *******************************************************************************/ 
#ifndef __ROM_ENCODER_H
#define __ROM_ENCODER_H
#include "sys.h"	


void encoderInit(void);

//void EncoderA_Init(void);   // TIM2
//void EncoderB_Init(void);   // TIM3
void EncoderC_Init(void);     // TIM4
void EncoderD_Init(void);     // TIM5

// rpm calculation
//int32_t getMotorA_rpm(void);
//int32_t getMotorB_rpm(void);
int32_t getMotorC_rpm(void);
int32_t getMotorD_rpm(void);

#endif


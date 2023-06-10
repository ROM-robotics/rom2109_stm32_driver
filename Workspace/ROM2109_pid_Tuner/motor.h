/*******************************************************************************
 *                    ROM ROBOTICS Co,.Ltd ( Myanmar )    										 *
 *			(ɔ) COPYLEFT 2021		| www.romrobots.com | (+95) 9-259-288-229 				 *
 *******************************************************************************/ 
#ifndef __MOTOR_H
#define __MOTOR_H
#include "sys.h"	 

#define Set_MotorB_PWM(x)	TIM_SetCompare3(TIM8, x);   // DRIVER CHIP1 , RIGHT MOTOR
#define INB2   PBout(4)  
#define INB1   PBout(5)  

#define Set_MotorC_PWM(x)	TIM_SetCompare2(TIM8, x);		// DRIVER CHIP2 , LEFT MOTOR
#define INC1   PCout(5)  
#define INC2   PCout(4)  

void motorPWMInit(uint16_t arr,uint16_t psc);
void MotorGpio_Init(void);

#endif


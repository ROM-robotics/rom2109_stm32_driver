/*******************************************************************************
 *                    ROM ROBOTICS Co,.Ltd ( Myanmar )    										 *
 *			(ɔ) COPYLEFT 2021		| www.romrobots.com | (+95) 9-259-288-229 				 *
 *******************************************************************************/ 
#ifndef __MOTOR_H
#define __MOTOR_H
#include "sys.h"	 

/* LEFT */
//#define Set_MotorA_PWM(x)	TIM_SetCompare4(TIM8, x);		// DRIVER CHIP1 , LEFT MOTOR, PC9
//#define INA1   PDout(2)  
//#define INA2   PCout(12)  


/* RIGHT */
//#define Set_MotorB_PWM(x)	TIM_SetCompare3(TIM8, x);   // DRIVER CHIP1 , RIGHT MOTOR , PC8
//#define INB2   PBout(4)  
//#define INB1   PBout(5)  

#define Set_MotorC_PWM(x)	TIM_SetCompare2(TIM8, x);		// DRIVER CHIP2 , LEFT MOTOR, PC7
#define INA1   PCout(4)  
#define INA2   PCout(5)  

#define Set_MotorD_PWM(x)	TIM_SetCompare1(TIM8, x);		// DRIVER CHIP2 , LEFT MOTOR, PC6
#define INB1   PBout(0)  
#define INB2   PBout(1)

void motorPWMInit(uint16_t arr,uint16_t psc);
void MotorGpio_Init(void);

#endif


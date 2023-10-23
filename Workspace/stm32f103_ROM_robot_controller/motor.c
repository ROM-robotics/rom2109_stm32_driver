/*******************************************************************************
 *                    ROM ROBOTICS Co,.Ltd ( Myanmar )    										 *
 *			(ɔ) COPYLEFT 2021		| www.romrobots.com | (+95) 9-259-288-229 				 *
 *******************************************************************************/ 
#include "motor.h"

void MotorGpio_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_JTAGDISABLE;       								// JTAG-DP Disabled, SW-DP Enabled
	AFIO->MAPR |= 2<<24;
	//AFIO->MAPR |= AFIO_MAPR_TIM2_REMAP_0;             							// THIS ARE TIM2 REMAP TO PA15, PB3
	
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;			
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;									// 50M 

	//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;  					// MOTOR B -> INB1(PB4), INB2(PB5)
	//GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;											// MOTOR A -> INA2(PC12)
	//GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;												// MOTOR A -> INA1(PD2)
	//GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 ;						// MOTOR C -> INC1(PC4), INC2(PC5) but alis(INA1,INA2)
	GPIO_Init(GPIOC, &GPIO_InitStructure);
		
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 ;						// MOTOR D -> INC1(PB0), INC2(PB1) but alis(INB1,INB2)
	GPIO_Init(GPIOB, &GPIO_InitStructure);
		

	INB1=0;INA1=0;
	INB2=0;INA2=0;
	
	Set_MotorC_PWM(0);
	Set_MotorD_PWM(0);
}

void motorPWMInit(uint16_t arr,uint16_t psc)
{
	MotorGpio_Init();  //
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE); // RCC->APB2ENR |= RCC_APB2ENR_TIM8EN;
	
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	GPIOC->CRH&=0xFFFFFF00;    
	GPIOC->CRH|=0x000000BB; 		// PC8, PC9 ( PWM )
	GPIOC->CRL&=0x00FFFFFF;    
	GPIOC->CRL|=0xBB000000;			// PC6, PC7 ( PWM ) alternate function output push pull
	
	TIM8->CNT = 0;
	TIM8->PSC= psc;
	TIM8->ARR = arr;

	//====================================================================== MOTOR A
		// INA1(PD2), INA2(PC12),  PWM(PC9)
	
	//TIM8->CCMR2|=6<<12;        // CH4 OUTPUT COMPARE 2 MODE
	//TIM8->CCMR2|=1<<11;        // CH4 OC4PE pre load enable 
	//TIM8->CCER|=1<<12;          // CH4 CC4E	   
	//TIM8->CCR4=0;
	
	//====================================================================== MOTOR B
		// INB1(PB4), INB2(PB5),  PWM(PC8)  **BE CAREFUL** PB4,5 use in jtag or debug so add AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_JTAGDISABLE;
	
	//TIM8->CCMR2|= 6<<4;         // CH3 OUTPUT COMPARE 2 MODE
	//TIM8->CCMR2|= 1<<3;         // CH3 OC3PE pre load enable  
	//TIM8->CCER |= 1<<8;         // CH3 CC3E
	//TIM8->CCR3=0;
	//====================================================================== MOTOR C
		// INC1(PC4), INC2(PC5),  PWM(PC7)
	
	TIM8->CCMR1|=6<<12;        // CH2 OUTPUT COMPARE 2 MODE
	TIM8->CCMR1|=1<<11;        // CH2 OC2PE pre load enable 
	TIM8->CCER|=1<<4;          // CH2 CC2E	   
	TIM8->CCR2=0;
	
	//====================================================================== MOTOR D
	  // IND1(PB0), IND2(PB1),  PWM(PC6)
	
	TIM8->CCMR1|=6<<4;        // CH1 OUTPUT COMPARE 2 MODE
	TIM8->CCMR1|=1<<3;        // CH1 OC1PE pre load enable 
	TIM8->CCER|=1;            // CH1 CC1E	   
	TIM8->CCR2=0;
	
	//================================================================== TIMER start
	//TIM8->CR1=0x8000;        // ? 
	TIM8->BDTR |= 1<<15;			 // MOE
	TIM8->CR1|=0x01;  
} 


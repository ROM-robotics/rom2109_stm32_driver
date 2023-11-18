/*******************************************************************************
 *                    ROM ROBOTICS Co,.Ltd ( Myanmar )    										 *
 *			(ɔ) COPYLEFT 2021		| www.romrobots.com | (+95) 9-259-288-229 				 *
 *******************************************************************************/ 
#include "encoder.h"

volatile uint64_t B_count=0;    
volatile uint64_t C_count=0;

//=============================================================== RPM calculation
/*
int32_t getMotorA_rpm()
{
	A_count = TIM2->CNT; 
	static int32_t A_prev_count=0;
	int16_t A_count_diff=0;	
	int16_t actual_rpm=0;
	int8_t direction_bit = 1;
	
	if( TIM2->CR1 & TIM_CR1_DIR )												// if reverse
	{
		A_count_diff = A_prev_count - A_count;
		if( A_count_diff < 0 ) { A_count_diff += 65536; }
		direction_bit = -1;
	}
	else
	{
		 A_count_diff = A_count - A_prev_count;
		 if(A_count_diff < 0) { A_count_diff += 65536; }  // forward counter overflow
	}
	A_prev_count = A_count;
	//actual_rpm = ( A_count_diff * 10 ) / ( 11 );        // FORMULA -> count_diff/50ms x 1000ms/1s x 60s/1m x 1rev/ppr 
	actual_rpm = A_count_diff * pulse_per_50ms_to_rpm;
	return actual_rpm * direction_bit;
}

int32_t getMotorB_rpm()
{
	B_count = TIM3->CNT; 
	static int32_t B_prev_count=0;
	int16_t B_count_diff=0;
	int16_t actual_rpm=0;
	int8_t direction_bit = 1;
	
	if( TIM3->CR1 & TIM_CR1_DIR )													// if reverse
	{
		B_count_diff = B_prev_count - B_count;
		if( B_count_diff < 0 ) { B_count_diff += 65536; }
		direction_bit = -1;
	}
	else
	{
		B_count_diff = B_count - B_prev_count;
		if( B_count_diff < 0 ) { B_count_diff += 65536; }  	// forward counter overflow
	}
	
	B_prev_count = B_count;
	//actual_rpm = ( B_count_diff * 10 ) / ( 11 );        	// FORMULA -> count_diff/50ms x 1000ms/1s x 60s/1m x 1rev/ppr  
	actual_rpm = B_count_diff * pulse_per_50ms_to_rpm;
	return actual_rpm * direction_bit;
}
*/
/////////////////////////////////////////////////////////

int32_t getMotorC_rpm()
{
	C_count = TIM4->CNT; 
	static int32_t C_prev_count=0;
	int16_t C_count_diff=0;	
	int16_t actual_rpm=0;
	int8_t direction_bit = 1;
	
	if( TIM4->CR1 & TIM_CR1_DIR )												// if reverse
	{
		C_count_diff = C_prev_count - C_count;
		if( C_count_diff < 0 ) { C_count_diff += 65536; }
		direction_bit = -1;
	}
	else
	{
		 C_count_diff = C_count - C_prev_count;
		 if(C_count_diff < 0) { C_count_diff += 65536; }  // forward counter overflow
	}
	/* -----------------------ROS2 CONTROL---------------------------- */
	global_C_count += (C_count_diff * (-direction_bit));
	/* --------------------END ROS2 CONTROL--------------------------- */ 
	C_prev_count = C_count;
	//actual_rpm = ( A_count_diff * 10 ) / ( 11 );        // FORMULA -> count_diff/50ms x 1000ms/1s x 60s/1m x 1rev/ppr 
	actual_rpm = C_count_diff * pulse_per_50ms_to_rpm;
	return actual_rpm * direction_bit * -1;
}

int32_t getMotorD_rpm()
{
	B_count = TIM5->CNT; 
	static int32_t B_prev_count=0;
	int16_t B_count_diff=0;
	int16_t actual_rpm=0;
	int8_t direction_bit = -1;
	
	if( TIM5->CR1 & TIM_CR1_DIR )													// if reverse
	{
		B_count_diff = B_prev_count - B_count;
		if( B_count_diff < 0 ) { B_count_diff += 65536; }
		direction_bit = 1;
	}
	else
	{
		B_count_diff = B_count - B_prev_count;
		if( B_count_diff < 0 ) { B_count_diff += 65536; }  	// forward counter overflow
	}
	/* -----------------------ROS2 CONTROL---------------------------- */
	global_D_count += (B_count_diff * (-direction_bit));
	/* --------------------END ROS2 CONTROL--------------------------- */ 
	B_prev_count = B_count;
	//actual_rpm = ( B_count_diff * 10 ) / ( 11 );        	// FORMULA -> count_diff/50ms x 1000ms/1s x 60s/1m x 1rev/ppr  
	actual_rpm = B_count_diff * pulse_per_50ms_to_rpm;
	return actual_rpm * direction_bit * -1;
}

//=============================================================== Encoder Initialize
void encoderInit(void)
{
	//EncoderA_Init();
	//EncoderB_Init();
	EncoderC_Init();
	EncoderD_Init();
}

/*
void EncoderA_Init(void)
{
	GPIOB->CRL   &= 0xFFFF0FFF; 	// ENCODER(PB3)
	GPIOB->CRL   |= 0x00008000;		// input pull up , if ec11 encoder (they include resistors) , gpio can use float
	GPIOA->CRH   &= 0x0FFFFFFF; 	// ENCODER(PA15)
	GPIOA->CRH   |= 0x80000000;		
	
	RCC->APB1ENR |= 1; 				// timer 2 clock
	TIM2->PSC     = 0;
	TIM2->ARR     = 65535;
	TIM2->CCMR1  |= 1<<8 | 				// cc2 channel---------------------------------------------------------------------
								  1;     				// cc1 channel
	TIM2->SMCR   |= 3;						// timer smcr sms counting both T1 edge, T2 edge
	TIM2->CR1    |= 1;						// timer count enable CEN
}

void EncoderB_Init(void)
{
	GPIOA->CRL   &= 0x00FFFFFF; 
	GPIOA->CRL   |= 0x88000000;		// ENCODER(PA6,PA7)
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN; 
	TIM3->PSC     = 0;
	TIM3->ARR     = 65535;
	TIM3->CCMR1  |= 1<<8 | 				// cc2 channel
								  1;     				// cc1 channel
	TIM3->SMCR   |= 3;						// timer smcr sms counting both T1 edge, T2 edge
	TIM3->CCER 	 |= 1<<2 | 1<<5; 	// reverse for right wheel 
	TIM3->CR1    |= 1;						// timer count enable CEN
}
*/
void EncoderC_Init(void)
{
	GPIOB->CRL   &= 0x00FFFFFF; 	// ENCODER(PB6,PB7)
	GPIOB->CRL   |= 0x88000000;		// input pull up , if ec11 encoder (they include resistors) , gpio can use float
	RCC->APB1ENR |= 1<<2; 				// timer 4 clock
	TIM4->PSC     = 0;
	TIM4->ARR     = 65535;
	TIM4->CCMR1  |= 1<<8 | 				// cc2 channel
								  1;     				// cc1 channel
	TIM4->SMCR   |= 3;						// timer smcr sms counting both T1 edge, T2 edge
	TIM4->CR1    |= 1;						// timer count enable CEN
}
void EncoderD_Init(void)
{
	GPIOA->CRL   &= 0xFFFFFF00; 	// ENCODER(PA0,PA1)
	GPIOA->CRL   |= 0x00000088;		// input pull up , if ec11 encoder (they include resistors) , gpio can use float
	RCC->APB1ENR |= 1<<3; 				// timer 5 clock
	TIM5->PSC     = 0;
	TIM5->ARR     = 65535;
	TIM5->CCMR1  |= 1<<8 | 				// cc2 channel
								  1;     				// cc1 channel
	TIM5->SMCR   |= 3;						// timer smcr sms counting both T1 edge, T2 edge
	TIM5->CR1    |= 1;						// timer count enable CEN
}



#define TRACE_DEBUG
#include "stm32f10x.h"
#include "main.h"
#include "sys.h"

// usart
uint8_t Usart_Rx_Buf[];
uint8_t Received_Rx_Buf[];
uint16_t Rx_strLength;
uint8_t Usart_Tx_Buf[];

int setpoint = 0;
int main(void)
{
	allInitialize();
	#ifdef TRACE_DEBUG
		printf("main() Start Trace Debug... \r\n");
	#endif
	setpoint = 0;
	right_desire_rpm = setpoint;
	left_desire_rpm = right_desire_rpm;
	while(1)
	{
		right_desire_rpm = setpoint;
		left_desire_rpm = setpoint;
		getDesireRPM();
	}
}

/*  FUNCTION IMPLEMENTS  */
void sampleTimeInit(void)
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
	TIM6->PSC = 71; 										// 1us
	TIM6->ARR = 1000*SAMPLE_TIME_mS; 	  // 1ms x 50 = 50000
	TIM6->CNT=0;     										// count flag 0
	TIM6->CR1 |= 1; 										// CEN enable
	TIM6->DIER |=1; 										// update interrupt enable
	NVIC_EnableIRQ(TIM6_IRQn);
}

void TIM6_IRQHandler(void)
{
	if(TIM6->SR & TIM_SR_UIF)
	{ 
		#ifdef TRACE_DEBUG
			//printf("right_DESIRE=%d,left_DESIRE=%d\r\n", right_desire_rpm, left_desire_rpm);
			//printf("right_actual=%d,left_actual=%d\r\n", B_actual_rpm, C_actual_rpm);
		  
		#endif
		updateMotor(); 
	}
	TIM6->SR &= ~ TIM_SR_UIF;
}


void updateMotor(void)
{		
	 B_actual_rpm= getMotorB_rpm();
	 C_actual_rpm= getMotorC_rpm();
	//--------------------------------------------------------------------------------------------


			#ifdef TRACE_DEBUG
				printf("right_actual=%d \n", B_actual_rpm);
			#endif
    
	//--------------------------------------------------------------------------------------------
	 updatePID_B( right_desire_rpm, B_actual_rpm );
	 updatePID_C( left_desire_rpm, C_actual_rpm );
}


void getDesireRPM(void)
{
		// get desire rpm-------------------------------------------------------------------------------------
		
			if( Rx_strLength > 0xC000) // usart rx DMA flag 
			{
				int16_t str_len = Rx_strLength & 0x00ff;
				char new_str[str_len];  // malloc vs size who speed fast?
				
				for(int j=0; j<str_len;j++)
				{
					new_str[j] = (char) Received_Rx_Buf[j];
				}
				char* pend;
				
				right_desire_rpm = (int)(strtof( new_str, &pend));
				left_desire_rpm = (int)(strtof( pend, NULL));
				
				Rx_strLength &= 0x0fff;  // reset flag
				
				#ifdef TRACE_DEBUG
					printf("right=%d \r\n", right_desire_rpm);
				#endif
			}		
		// end get desire rpm-------------------------------------------------------------------------------
}

void variablesInit(void)
{
	//--------------------------------------------
	pi    = 3.1415926;
  two_pi= 6.2831853;
	// change for your robot
	// uints meter, radian
	base_width       = 0.205;
	wheel_diameter   = 0.070;
	pulse_per_revolute = 6533;
	
	B_Kp = 25.0;
	B_Ki = 0.0;
	B_Kd = 1.5;
	
	C_Kp = 1.0;
	C_Ki = 0.00001;
	C_Kd = 0.0001;
	//--------------------------------------------
	
	// rpm
	right_desire_rpm = 0; 				  // motor B desire rpm can be ( +, - )
	left_desire_rpm = 0; 				    // motor C desire rpm can be ( +, - )
	B_actual_rpm=0;				
	C_actual_rpm=0;	
	
	pulse_per_50ms_to_rpm = 0.0;  
	pulse_per_50ms_to_rpm = 60000.0 / (SAMPLE_TIME_mS * pulse_per_revolute);
	
	meter_per_sec_to_rpm = 60.0/ (pi * wheel_diameter);
	
	
}

void allInitialize(void)
{
	variablesInit();
  sampleTimeInit();
	motorPWMInit(7199, 0);
	encoderInit();
	usart1Init(115200);
}




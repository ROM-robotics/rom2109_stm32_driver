//#define TRACE_DEBUG
//#define PID_TUNE
#include "stm32f10x.h"
#include "main.h"
#include "sys.h"

// usart
uint8_t Usart_Rx_Buf[];
uint8_t Received_Rx_Buf[];
uint16_t Rx_strLength;
uint8_t Usart_Tx_Buf[];

#ifdef PID_TUNE
int setpoint = 50;
#endif

int main(void)
{
	allInitialize();
	#ifdef TRACE_DEBUG
		printf("main() Start Trace Debug... \r\n");
	#endif
	
	while(1)
	{
		#ifdef PID_TUNE
			right_desire_rpm = setpoint; left_desire_rpm = setpoint;
		#endif
		//getDesireRPM();
	}
	
}

/*  FUNCTION IMPLEMENTS  */
void sendData(void)
{
		l_ticks = global_C_count; r_ticks= global_D_count;
		/* ROS2 CONTROL 
		global_C_count; // Motor C
		global_D_count; // Motor D
		*/
	
	//--------------------------------------------------------------------------------------------
	  int x_len = snprintf( NULL, 0, "%ld", l_ticks);
    char* l_ticks_str = (char*)malloc( x_len+1 );
    snprintf( l_ticks_str, x_len+1, "%ld", l_ticks);

		int y_len = snprintf( NULL, 0, "%ld", r_ticks);
    char* r_ticks_str = (char*)malloc( y_len+1 );
    snprintf( r_ticks_str, y_len+1, "%ld", r_ticks);

			Usart_SendString(USART1, l_ticks_str);
			Usart_SendString(USART1, " ");
			Usart_SendString(USART1, r_ticks_str);
			Usart_SendString(USART1, " ");
			Usart_SendString(USART1, "\r\n");

			#ifdef TRACE_DEBUG
				printf("right_actual=%d, left_actual=%d,\n", right_actual_rpm, C_actual_rpm);
				//printf("x_pos=%.4f, y_pos=%.4f, theta=%.4f\n", x_pos, y_pos, theta);
				//printf("x_len=%d, y_len=%d, theta=%d\n", x_len, y_len, theta_len);
			#endif
    free(l_ticks_str); free(r_ticks_str);
	//--------------------------------------------------------------------------------------------
}
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
			//printf("right_actual=%d,left_actual=%d\r\n", right_actual_rpm, C_actual_rpm);
		  
		#endif
		updateMotor(); 
	}
	TIM6->SR &= ~ TIM_SR_UIF;
}

void allInitialize(void)
{
	variablesInit();
  sampleTimeInit();
	motorPWMInit(7199, 0);
	encoderInit();
	usart1Init(115200);
}

void updateMotor(void)
{		
	 left_actual_rpm= getMotorC_rpm(); // left
	 right_actual_rpm= getMotorD_rpm(); // right
	
	 getDesireRPM();
	
	 updatePID_right( right_desire_rpm, right_actual_rpm );
	 updatePID_left( left_desire_rpm, left_actual_rpm );
	
	 sendData();
}


void getDesireRPM(void)
{
	//left_desire_rpm=0; right_desire_rpm=0;
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
					char* pend2;
					char* pend3;
					left_desire_rpm = (int)( strtof( new_str, &pend) ); 
					right_desire_rpm = (int) ( strtof( pend, NULL) );
					//l_speed = (int) l_desire;
					//r_speed = (int) r_desire;
					//shutdown_request = strtof(pend2, &pend3);
					//if(shutdown_request > 0.0) { x_pos=0.0; y_pos=0.0; theta=0.0; }//ResetRobotController(); };
					Rx_strLength &= 0x0fff;  // reset flag
					//twist_to_motors();
				
					#ifdef TRACE_DEBUG
						//printf("linear_x=%f, angular_z=%f \r\n", lin_x, ang_z);
						printf("right=%d, left=%d \r\n", right_desire_rpm, left_desire_rpm);
					#endif
				
			}		
			
		// end get desire rpm-------------------------------------------------------------------------------
}

void variablesInit(void)
{
	//--------------------------------------------
	pi    = 3.1415926;
  two_pi= 6.2831853;
	// change for your robot ( uints meter, radian )
	//base_width       = 0.205;
	//wheel_diameter   = 0.070;
	pulse_per_revolute = 6533;
	//L_by_2 = base_width/2.0;
	
	// tune your pid
	R_Kp = 25.0;
	R_Ki = 0.0;
	R_Kd = 1.8; //2.5


	L_Kp = 28;
	L_Ki = 0.0001;
	L_Kd = 1.3;
	//--------------------------------------------
	
	// rpm
	right_desire_rpm = 0; 				  // motor B desire rpm can be ( +, - )
	left_desire_rpm = 0; 				    // motor C desire rpm can be ( +, - )
	right_actual_rpm=0;				
	left_actual_rpm=0;	
	
	pulse_per_50ms_to_rpm = 0.0;  
	pulse_per_50ms_to_rpm = 60000.0 / (SAMPLE_TIME_mS * pulse_per_revolute);
	
	//meter_per_sec_to_rpm = 60.0/ (pi * wheel_diameter);
	
	/* twist */
  //lin_x = 0.0;
  //ang_z = 0.0;
	
	/* fk */
	//linear_velocity_constant = (float) (wheel_diameter*pi/(60.0*2.0));
	//angular_velocity_constant= (float) (wheel_diameter*pi/(60.0*base_width));
	
	//theta = 0.0; 
	//x_pos = 0.0; 
	//y_pos = 0.0;
	
}

void ResetRobotController(void)
{
		NVIC_SystemReset();
}


void resetDesireVelocities(void)
{
	left_desire_rpm = 0; right_desire_rpm = 0;
}
void resetEncoders(void)
{
	/* ROS2 CONTROL */
	global_C_count = 0;	// Motor C
	global_D_count = 0; // Motor D
}


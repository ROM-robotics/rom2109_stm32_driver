/*******************************************************************************
 *                    ROM ROBOTICS Co,.Ltd ( Myanmar )    										 *
 *			(ɔ) COPYLEFT 2021		| www.romrobots.com | (+95) 9-259-288-229 				 *
 *******************************************************************************/ 
#include "pid.h"

//================================================= PWM update ( no use DMA yet )
void updatePID_B( int32_t desire, int32_t actual )
{
	int32_t err = 0;
	static int32_t prev_err = 0;
	static float integral_err = 0;
	float differential_err = 0;
	int16_t pid_term = 0;
	int16_t new_pwm = 0;
	static int16_t old_pwm = 0;
	err = abs(desire) - abs(actual);
	
	integral_err += ( err * SAMPLE_TIME_S ); 
	differential_err = (err-prev_err)/SAMPLE_TIME_S;
	
	pid_term = ( B_Kp * err ) + ( B_Ki * integral_err ) + ( B_Kd * differential_err );
	
	new_pwm = old_pwm + pid_term;
	if( new_pwm > 7199 )   { new_pwm=7199; }
	else if( new_pwm < 0 ) { new_pwm=0; }
	
	if( desire < 0 )			{ INB1=0; INB2=1; } 			// backward
  else if( desire > 0 )	{ INB1=1; INB2=0; } 		 	// default forward
	else									{ INB1=0; INB2=0; }
	
	Set_MotorB_PWM( abs(new_pwm) );
	prev_err = err;
	old_pwm  = new_pwm;
}

//================================================= 
void updatePID_C( int32_t desire, int32_t actual )
{
	int32_t err = 0;
	static int32_t prev_err = 0;																// same static variable name but compiler knows scope
	static float integral_err = 0;
	float differential_err = 0;
	int16_t pid_term = 0;
	int16_t new_pwm = 0;
	static int16_t old_pwm = 0;
	err = abs(desire) - abs(actual);
	
	integral_err += ( err * SAMPLE_TIME_S ); 
	differential_err = (err-prev_err)/SAMPLE_TIME_S;
	
	pid_term = ( C_Kp * err ) + ( C_Ki * integral_err ) + ( C_Kd * differential_err );
	
	new_pwm = old_pwm + pid_term;
	if( new_pwm > 7199 )   { new_pwm=7199; }
	else if( new_pwm < 0 ) { new_pwm=0; }
	
	if( desire < 0 )			{ INC1=0; INC2=1; } 			// backward
  else if( desire > 0 )	{ INC1=1; INC2=0; } 		 	// default forward
	else 									{ INC1=0; INC2=0; } 	
	Set_MotorC_PWM( abs(new_pwm) );
	prev_err = err;
	old_pwm  = new_pwm;
}


/*******************************************************************************
 *                    ROM ROBOTICS Co,.Ltd ( Myanmar )    										 *
 *			(ɔ) COPYLEFT 2021		| www.romrobots.com | (+95) 9-259-288-229 				 *
 *******************************************************************************/ 
#ifndef _ROM_MAIN_H
#define _ROM_MAIN_H
#include <stdint.h>

float pi;
float two_pi;

#ifdef TRACE_DEBUG
#include "stdio.h"
#include "stm32f10x.h"

int _write(int file, char *ptr, int len)
{
	int DataIdx;
	for (DataIdx = 0; DataIdx < len; DataIdx++)
	{
		ITM_SendChar(*ptr++);
	}
	return len;
}

#endif

int32_t right_desire_rpm; 				  // motor B desire rpm can be ( +, - )
int32_t left_desire_rpm; 				    // motor C desire rpm can be ( +, - )
int32_t B_actual_rpm;				
int32_t C_actual_rpm;

float pulse_per_50ms_to_rpm;
float meter_per_sec_to_rpm;


/* twist to motors */
float lin_x;
float ang_z;


/* function prototypes */
void allInitialize(void);
void variablesInit(void);
void updateMotor(void);
void getDesireRPM(void);
void sampleTimeInit(void);


// uints meter, radian
float base_width;
float wheel_diameter;
int pulse_per_revolute;

// need to tune
float B_Kp;
float B_Ki;
float B_Kd;


float C_Kp;
float C_Ki;
float C_Kd;

/* fk */
float linear_velocity_constant;
float angular_velocity_constant;

float theta;
float x_pos;
float y_pos;

#endif

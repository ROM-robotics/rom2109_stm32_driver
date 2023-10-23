/*******************************************************************************
 *                    ROM ROBOTICS Co,.Ltd ( Myanmar )    										 *
 *			(ɔ) COPYLEFT 2021		| www.romrobots.com | (+95) 9-259-288-229 				 *
 *******************************************************************************/ 
#ifndef _ROM_MAIN_H
#define _ROM_MAIN_H
#include <stdint.h>

float pi;
float two_pi;

int32_t right_desire_rpm; 				  // motor B desire rpm can be ( +, - )
int32_t left_desire_rpm; 				    // motor C desire rpm can be ( +, - )
int32_t right_actual_rpm;				
int32_t left_actual_rpm;

float pulse_per_50ms_to_rpm;
float meter_per_sec_to_rpm;

/* twist to motors */
float lin_x;
float ang_z;
float shutdown_request;

/* function prototypes */
void allInitialize(void);
void variablesInit(void);
void updateMotor(void);
void getDesireRPM2(void);
void sampleTimeInit(void);
void ResetRobotController(void);
void resetDesireVelocities(void);
void resetEncoders(void);

float rps_to_rpm_ratio;
// uints meter, radian
float base_width;
float wheel_diameter;
int pulse_per_revolute;
float L_by_2;

// need to tune
float R_Kp;
float R_Ki;
float R_Kd;


float L_Kp;
float L_Ki;
float L_Kd;

/* fk */
float linear_velocity_constant;
float angular_velocity_constant;

float theta;
float x_pos;
float y_pos;

long l_ticks; long r_ticks;
//int l_speed; int r_speed;

/* ROS2 CONTROL */
long global_A_count;	// Motor C
long global_B_count; // Motor D
long global_C_count;	// Motor C
long global_D_count; // Motor D
#endif

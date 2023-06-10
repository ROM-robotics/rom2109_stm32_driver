#ifndef _Sys_H
#define _Sys_H

#include <stdlib.h>
#include "stm32f10x.h"
#include "stdio.h"
#include "math.h"
#include "define.h"
#include "motor.h"
#include "encoder.h"
#include "pid.h"
#include "usart.h"
#include "kinematics.h"
#include "led.h"

#include "iic.h"
#include "mpu9250.h"

#define SAMPLE_TIME_mS 50												// 50 ms
#define SAMPLE_TIME_S (SAMPLE_TIME_mS/1000.0)		// 0.05 s

extern float pi;
extern float two_pi;

extern float R_Kp;
extern float R_Ki;
extern float R_Kd;
extern float L_Kp;
extern float L_Ki;
extern float L_Kd;

extern int32_t right_actual_rpm;
extern int32_t left_actual_rpm;

extern int32_t right_desire_rpm;
extern int32_t left_desire_rpm;

extern float lin_x;
extern float ang_z;

// uints meter, radian
extern float base_width;
extern float wheel_diameter;
extern int pulse_per_revolute;
extern float L_by_2;

extern float pulse_per_50ms_to_rpm;
extern float meter_per_sec_to_rpm;

extern float gyro_rot_x;
extern float gyro_rot_y;
extern float gyro_rot_z;

/* fk */
extern float linear_velocity_constant;
extern float angular_velocity_constant;
extern float theta;
extern float x_pos;
extern float y_pos;

extern long l_ticks; extern long r_ticks;
extern int l_speed; extern int r_speed;

/* ROS2 CONTROL */
extern long global_A_count; // Motor C
extern long global_B_count; // Motor D
#endif

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

#define SAMPLE_TIME_mS 50												// 50 ms
#define SAMPLE_TIME_S (SAMPLE_TIME_mS/1000.0)		// 0.05 s

extern float pi;
extern float two_pi;

extern float B_Kp;
extern float B_Ki;
extern float B_Kd;
extern float C_Kp;
extern float C_Ki;
extern float C_Kd;

extern int32_t B_actual_rpm;
extern int32_t C_actual_rpm;

extern int32_t right_desire_rpm;
extern int32_t left_desire_rpm;

extern float lin_x;
extern float ang_z;

// uints meter, radian
extern float base_width;
extern float wheel_diameter;
extern int pulse_per_revolute;

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

#endif

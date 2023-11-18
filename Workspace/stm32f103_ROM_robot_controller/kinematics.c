#include "kinematics.h"

void twist_to_motors(void){}; void forward_kinematic(void){};
/*
void twist_to_motors(void)
{ 
	float right = lin_x + (ang_z * L_by_2); 
	float left  = lin_x - (ang_z * L_by_2);
	
	right_desire_rpm = (int)(right * meter_per_sec_to_rpm); // vr
	left_desire_rpm  = (int)(left  * meter_per_sec_to_rpm); // vl

}

void forward_kinematic(void)
{
	// input -> actual rpm (right(B),left(C))
	// output-> xpos, ypos, theta

	
	 float linear_velocity = ( right_actual_rpm+ left_actual_rpm)*linear_velocity_constant;		//wheel_diameter*pi/(60.0*2.0);
   float linear_displacement   = linear_velocity * SAMPLE_TIME_S;

   float angular_velocity= (right_actual_rpm - left_actual_rpm)*angular_velocity_constant;		//wheel_diameter*pi/(60.0*track_width);
   float angular_displacement  = angular_velocity *SAMPLE_TIME_S;

	  float x = cos(angular_displacement) * linear_displacement;
    float y = -sin(angular_displacement) * linear_displacement; 

    float delta_x = (cos(theta) * x - sin(theta) * y);
    float delta_y = (sin(theta) * x + cos(theta) * y);
    float delta_theta = angular_displacement;

    x_pos += delta_x;
    y_pos += delta_y;
    theta += delta_theta;

    if(theta >= two_pi) theta -= two_pi;
    if(theta <= -two_pi) theta += two_pi;
}
*/

/*******************************************************************************
 *                    ROM ROBOTICS Co,.Ltd ( Myanmar )    										 *
 *			(ɔ) COPYLEFT 2021		| www.romrobots.com | (+95) 9-259-288-229 				 *
 *******************************************************************************/ 
#ifndef __ROM_PID
#define __ROM_PID
#include "sys.h" 

void updatePID_B( int32_t desire, int32_t actual );
void updatePID_C( int32_t desire, int32_t actual );

#endif


#include "mpu9250.h"

void Init_MPU(void)
{ // read imu 9250 datasheet
	SingleWrite(MPUADDR, REG_PWR_MNG, 0x00); // unlock
	SingleWrite(MPUADDR, SMPLRT_DIV, 0x07);  // to remove bias from gyro x,y,z and check SAMPLE_RATE formula
	
	SingleWrite(MPUADDR, REG_ACC_CONFIG, 0x06);  // 110 -> accelerometer low pass filter setting
	SingleWrite(MPUADDR, REG_ACC_RANGE, 0x01);	 // this is error
	
	SingleWrite(MPUADDR, REG_GYR_CONFIG, 0x06);  // 110 -> gyro 
	SingleWrite(MPUADDR, REG_GYR_RANGE, 0x18);   // 11000 -> gyro Z self test, +1000 dps
	
	SingleWrite(MPUADDR, REG_MAG_CONFIG, 0x02);  // interrupt pin / bypass enable configuration
	SingleWrite(MPUADDR, REG_MAG_MODE, 0x01);		 // magneto single measurement mode
}




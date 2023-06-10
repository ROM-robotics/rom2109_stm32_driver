#ifndef  ROM_MPU_H  
#define  ROM_MPU_H

#include "stm32f10x.h"   
#include "sys.h"

//Global address
#define MPUADDR             0xD0
#define MAGADDR             0x18
#define REG_ACC_CONFIG      0x1D
#define REG_GYR_CONFIG      0x1A
#define REG_GYR_RANGE       0x1B
#define REG_ACC_RANGE       0x1C
#define REG_MAG_CONFIG      0x37
#define REG_MAG_MODE        0x0A
#define REG_PWR_MNG         0x6B
#define SMPLRT_DIV          0x19

//Register address for acceleromter
#define REG_DATA_GX_LOW     0x3C  
#define REG_DATA_GX_HIGH    0x3B
#define REG_DATA_GY_LOW     0x3E
#define REG_DATA_GY_HIGH    0x3D
#define REG_DATA_GZ_LOW     0x40
#define REG_DATA_GZ_HIGH    0x3F

//Register address for gyroscope
#define REG_DATA_WX_LOW     0x44 
#define REG_DATA_WX_HIGH    0x43
#define REG_DATA_WY_LOW     0x46
#define REG_DATA_WY_HIGH    0x45
#define REG_DATA_WZ_LOW     0x48
#define REG_DATA_WZ_HIGH    0x47

//Register address for Magnetometer
#define REG_DATA_BX_LOW     0x03
#define REG_DATA_BX_HIGH    0x04
#define REG_DATA_BY_LOW     0X05
#define REG_DATA_BY_HIGH    0X06
#define REG_DATA_BZ_LOW     0X07
#define REG_DATA_BZ_HIGH    0X08

void Init_MPU(void); 

#endif

extern	short gyro[3], accel[3];
extern int16_t Gx_offset,Gy_offset,Gz_offset;
extern float Acc1G_Values;

//٩΢ҿַԃքAPI
void MPU6050_initialize(void); //Եʼۯ
uint8_t MPU6050_testConnection(void); //ݬӢMPU6050ˇرզ՚
//ׁȡADCֵ
void MPU6050_getMotion6(int16_t* ax, int16_t* ay, int16_t* az, int16_t* gx, int16_t* gy, int16_t* gz);
void MPU6050_getlastMotion6(int16_t* ax, int16_t* ay, 
		int16_t* az, int16_t* gx, int16_t* gy, int16_t* gz);
uint8_t MPU6050_getDeviceID(void); //ׁȡMPU6050քID
void MPU6050_InitGyro_Offset(void);//ԵʼۯΓÝӇƫ׃
void DMP_Init(void);
void Read_DMP(void);
int Read_Temperature(void);




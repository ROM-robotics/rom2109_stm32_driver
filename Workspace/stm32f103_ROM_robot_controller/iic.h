#ifndef  I2C_H  
#define  I2C_H

#include "stm32f10x.h"   
#include "sys.h"

//Pin map for communication
#define PIN_SCL    GPIO_Pin_10 // 6  
#define PIN_SDA    GPIO_Pin_11 // 7
#define I2C_PORT   GPIOB 

#define SDA_IN()			{GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=8<<12;} // 11
#define SDA_OUT()			{GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=3<<12;} // 11
#define IIC_SCL				PBout(10)
#define IIC_SDA				PBout(11)
#define READ_SDA			PBin(11)

void delay_us(uint32_t i);

void I2C_Init(void);                

void I2C_Start(void);  

void I2C_Stop(void); 

void I2C_Send_Byte(uint8_t txd);

uint8_t I2C_Read_Byte(unsigned char ack);    

uint8_t I2C_Wait_Ack(void);

void I2C_Ack(void);

void I2C_NAck(void);   

void SingleWrite(uint8_t daddr,uint8_t addr,uint8_t data);

uint8_t SingleRead(uint8_t daddr,uint8_t addr);  
	

#endif 






/*

void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte(u8 daddr,u8 addr);	 
unsigned char I2C_Readkey(unsigned char I2C_Addr);

unsigned char I2C_ReadOneByte(unsigned char I2C_Addr,unsigned char addr);
unsigned char IICwriteByte(unsigned char dev, unsigned char reg, unsigned char data);
u8 IICwriteBytes(u8 dev, u8 reg, u8 length, u8* data);
u8 IICwriteBits(u8 dev,u8 reg,u8 bitStart,u8 length,u8 data);
u8 IICwriteBit(u8 dev,u8 reg,u8 bitNum,u8 data);
u8 IICreadBytes(u8 dev, u8 reg, u8 length, u8 *data);

int i2cWrite(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *data);
int i2cRead(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf);

*/


#include "iic.h"


void delay_us(uint32_t i)
{
	u32 temp;
	SysTick->LOAD=9*i;		 
	SysTick->CTRL=0X01;		 
	SysTick->VAL=0;		   	
	do
	{
		temp=SysTick->CTRL;		   
	}
	while((temp&0x01)&&(!(temp&(1<<16))));	 
	SysTick->CTRL=0;	
	SysTick->VAL=0;		
}






void I2C_Init(void)
{
		GPIO_InitTypeDef gpio_struct;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	  gpio_struct.GPIO_Pin = PIN_SCL | PIN_SDA;
		gpio_struct.GPIO_Mode = GPIO_Mode_Out_PP;
		gpio_struct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(I2C_PORT, &gpio_struct);
}


void I2C_Start(void)
{ // --> total delay 2 us
	SDA_OUT();
	IIC_SDA = 1;
	IIC_SCL = 1;
	delay_us(1);
	IIC_SDA = 0;  // start
	delay_us(1);
	IIC_SCL = 0;  // clock ground really need? 
	delay_us(1); 
}





void I2C_Stop(void)
{ // --> total delay 2 us
	SDA_OUT();
	IIC_SCL = 0;
	IIC_SDA = 0;
	delay_us(1);
	IIC_SCL = 1;
	IIC_SDA = 1;
	delay_us(1);
}





uint8_t I2C_Wait_Ack(void)
{ // until 50 us
	uint8_t ucErrTime = 0;
	SDA_IN();
	IIC_SDA = 1; // PULL UP
	delay_us(1);
	IIC_SCL = 1; //ready?
	delay_us(1);
	while(READ_SDA) // active low
	{
		ucErrTime++;
		if(ucErrTime>50) // if greater 50 us
		{
			I2C_Stop();
			return 1;
		}
		delay_us(1); 
	}
	IIC_SCL = 0;
	return 0;
}


void I2C_Ack(void)
{ // --> total delay 2 us
	IIC_SCL = 0;
	SDA_OUT();
	IIC_SDA = 0;
	delay_us(1);
	IIC_SCL = 1;
	delay_us(1);
	IIC_SCL = 0;
}



void I2C_NAck(void)
{ // --> total delay 2 us
	IIC_SCL = 0;
	SDA_OUT();
	IIC_SDA = 1;
	delay_us(1);
	IIC_SCL = 1;
	delay_us(1);
	IIC_SCL = 0;
}


void I2C_Send_Byte(uint8_t txd)
{ // --> total delay 24 us
	uint8_t t;
	SDA_OUT();
	IIC_SCL = 0;
	for(t=0;t<8;t++)
	{
		if( (txd & 0x80)==0x80 ) // if MSB is 1
		{
			IIC_SDA = 1;
		}
		else {
			IIC_SDA = 0; // if MSB 
		}
		txd <<= 1;
		delay_us(1);
		IIC_SCL = 1;
		delay_us(1);
		IIC_SCL = 0;
		delay_us(1);
	}
}



uint8_t I2C_Read_Byte(unsigned char ack)
{ // --> total delay 32 us
	unsigned char i, receive = 0;
	SDA_IN();
	// SDA =1
	for(i=0;i<8;i++)
	{
		IIC_SCL = 0;
		delay_us(2);
		IIC_SCL = 1;
		receive <<= 1;
		if(READ_SDA) receive++;
		delay_us(2);
	}
	if(ack)
	{
		I2C_Ack();
	} else {
		I2C_NAck();
	}
	return receive;
}




void SingleWrite(uint8_t dev_addr,uint8_t reg_addr,uint8_t data)
{   // delay 226 us, 0.22 ms
    I2C_Start();
    I2C_Send_Byte(dev_addr);
    I2C_Wait_Ack();
    I2C_Send_Byte(reg_addr);
    I2C_Wait_Ack();
    I2C_Send_Byte(data);
    I2C_Wait_Ack();
    I2C_Stop();
}


uint8_t SingleRead(uint8_t dev_addr,uint8_t reg_addr)
{   // delay 260 us, 0.26 ms
    uint8_t data;
    I2C_Start();
    I2C_Send_Byte(dev_addr);
    I2C_Wait_Ack();
    I2C_Send_Byte(reg_addr);
    I2C_Wait_Ack();
    I2C_Start();
    I2C_Send_Byte(dev_addr+1); // 7bits + 1 ( read bits ) = 8 bits
    I2C_Wait_Ack();
    data=I2C_Read_Byte(0);//no ack
    I2C_Stop();
    return data;
}




















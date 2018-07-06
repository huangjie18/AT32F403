#include "bsp_lcd.h"
#include "delay.h"

static void LcdWriCommand(unsigned char command);
static void LcdWriData(unsigned char Data);

//lcd初始化函数
void lcd_init(void)
{
	lcd_reset = 1;
	delay_ms(100);
	lcd_reset = 0; //LCD复位
	delay_ms(100);
	lcd_reset = 1;
	delay_ms(120);
	
	LcdWriCommand(0x11);
	delay_ms(200);
	
	LcdWriCommand(0x36);  //扫描方式
	LcdWriData(0x00);
	LcdWriCommand(0x3a); 
	LcdWriData(0x05); 

	LcdWriCommand(0xb2); 
	LcdWriData(0x0c); 
	LcdWriData(0x0c); 
	LcdWriData(0x00); 
	LcdWriData(0x33); 
	LcdWriData(0x33); 

	LcdWriCommand(0xb7); 
	LcdWriData(0x35); 

	//---------------------------------ST7789S Power setting--------------------------------------// 

	LcdWriCommand(0xbb); 
	LcdWriData(0x2C); 

	LcdWriCommand(0xc0); 
	LcdWriData(0x2c); 

	LcdWriCommand(0xc2); 
	LcdWriData(0x01); 

	LcdWriCommand(0xc3); 
	LcdWriData(0x0b); 

	LcdWriCommand(0xc4); 
	LcdWriData(0x20); 

	LcdWriCommand(0xc6); 
	LcdWriData(0x0f); 

	LcdWriCommand(0xd0); 
	LcdWriData(0xa4); 
	LcdWriData(0xa1); 
	
	//--------------------------------ST7789S gamma setting---------------------------------------// 
	
	LcdWriCommand(0xe0); 
	LcdWriData(0xd0); 
	LcdWriData(0x06); 
	LcdWriData(0x01); 
	LcdWriData(0x0e); 
	LcdWriData(0x0e); 
	LcdWriData(0x08); 
	LcdWriData(0x32); 
	LcdWriData(0x44); 
	LcdWriData(0x40); 
	LcdWriData(0x08); 
	LcdWriData(0x10); 
	LcdWriData(0x0f); 
	LcdWriData(0x15); 
	LcdWriData(0x19); 

	LcdWriCommand(0xe1); 
	LcdWriData(0xd0); 
	LcdWriData(0x06); 
	LcdWriData(0x01); 
	LcdWriData(0x0f); 
	LcdWriData(0x0e); 
	LcdWriData(0x09); 
	LcdWriData(0x2f); 
	LcdWriData(0x54); 
	LcdWriData(0x44); 
	LcdWriData(0x0f); 
	LcdWriData(0x1d); 
	LcdWriData(0x1a); 
	LcdWriData(0x16); 
	LcdWriData(0x19); 
	
	LcdWriCommand(0x21);	//display inversion on
	LcdWriCommand(0x29);//display on

	delay_ms(120);
	
	//开区
	LcdWriCommand(0x2A);
	LcdWriData(0x00);
	LcdWriData(0x00);
	LcdWriData(0x00);
	LcdWriData(0xef);

	LcdWriCommand(0x2B);
	LcdWriData(0x00);
	LcdWriData(0x00);//3B
	LcdWriData(0x0);
	LcdWriData(0xef);

	LcdWriCommand(0x2C);
}

static void LcdWriCommand(unsigned char command)
{
	lcd_dc = 0;
	SPI_I2S_TxData(SPI1,command);//通过外设SPIx发送一个数据
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TE) == RESET);//检查发送是否完成
	
}

static void LcdWriData(unsigned char Data)
{
	lcd_dc = 1;
	SPI_I2S_TxData(SPI1,Data);//通过外设SPIx发送一个数据
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TE) == RESET);//检查发送是否完成
}

static void gd_WriteDAT(unsigned char DH,unsigned char DL)		
{
	LcdWriData(DH);
	LcdWriData(DL);	
}

void display_rgb(u16 color)
{
	int i,j;
	for(i = 0; i < 240; i++)
	{
		for(j = 0; j < 240; j++)
		{
			gd_WriteDAT(color>>8,color&0xff);
		}
	}
}

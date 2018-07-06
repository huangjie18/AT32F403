#ifndef __BSP_LCD_H
#define __BSP_LCD_H
#include "sys.h"

#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	 0x001F  
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //棕色
#define BRRED 			 0XFC07 //棕红色
#define GRAY  			 0X8430 //灰色

#define lcd_reset  PAout(8)
#define lcd_dc     PAout(6)

void lcd_init(void); //初始化
void display_rgb(u16 color); //刷屏
#endif

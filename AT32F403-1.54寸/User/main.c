#include "sys.h"
#include "bsp_led.h"
#include "delay.h"
#include "bsp_spi.h"
#include "bsp_lcd.h"

#define LED PAout(0)
#define sys_delay (SystemCoreClock/1000000)

unsigned int count=0;

int main(void)
{
	delay_init(sys_delay);  //主频
	
	bsp_led_init();  //led初始化
	
	bsp_spi_gpio_init(SPI_MODE_MASTER); 	//SPI1初始化
	
	lcd_init();  //LCD初始化

	while(1)
	{
		LED = ~LED;  //闪烁LED
		count = 0;
		display_rgb(RED);
		delay_ms(1000);
		
		LED = ~LED;  //闪烁LED
		count = 0;
		display_rgb(GREEN);
		delay_ms(1000);
		
		LED = ~LED;  //闪烁LED
		count = 0;
		display_rgb(BLUE);
		delay_ms(1000);
	}
}
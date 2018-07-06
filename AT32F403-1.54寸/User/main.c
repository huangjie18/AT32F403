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
	delay_init(sys_delay);  //��Ƶ
	
	bsp_led_init();  //led��ʼ��
	
	bsp_spi_gpio_init(SPI_MODE_MASTER); 	//SPI1��ʼ��
	
	lcd_init();  //LCD��ʼ��

	while(1)
	{
		LED = ~LED;  //��˸LED
		count = 0;
		display_rgb(RED);
		delay_ms(1000);
		
		LED = ~LED;  //��˸LED
		count = 0;
		display_rgb(GREEN);
		delay_ms(1000);
		
		LED = ~LED;  //��˸LED
		count = 0;
		display_rgb(BLUE);
		delay_ms(1000);
	}
}
#include "delay.h"

#if (delay_mode == 1)
static u8 	fac_us = 0;
static u16 	fac_ms = 0;

void delay_init(int SYSCLK)
{
	//选择外部时钟  HCLK/8,即是即是一次计时是1/(HCLK/8)=8/HCLK秒
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	
	//需要计时1us,相当于需要1/(1M)秒，计数次数=(1/(1M)) / (8/HCLK) = HCLK/8M
//	fac_us = SYSCLK/8;  //除以8是因为HCLK/8,如果是4分频就除以4
	fac_us = SystemCoreClock/8000000;
	fac_ms = (u16) fac_us*1000;
}

//延时us
//参数为要延时的us数
//最大值为gd_us*fac_us<0xffffff,gd_us<(0xffffff/fac_us)=671088
void delay_us(u32 gd_us)
{
	u32 temp;	    	 
	SysTick->LOAD=gd_us*fac_us; 				//时间加载	  		 
	SysTick->VAL=0x00;        					//清空计数器
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//开始倒数	  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));		//等待时间到达   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//关闭计数器
	SysTick->VAL =0X00;  
}


/************************************************
函数名称 ： gd_delay_ms
功    能 ： 延时ms级
参    数 ： 延时多少ms
返 回 值 ： 无
注    意 ： SysTick->LOAD为24位寄存器，即是(nms*1000*(SYSTICK/8))<=0XFFFFFF
			当72M条件下，nms<=1864
			所以采用分段延时来增大可延时范围
*************************************************/
void delay_ms(u32 ms)
{
	u8 repeat=ms/1000;    //得到要延时多少秒
	u16 remain = ms%1000;
	while(repeat)
	{
//		delay_us(1000000); //1s，不同主频，需要改，可能不能用1000000
		delay_us(600000);  //主频200M时，最大值不能超过671088
		delay_us(400000);
		repeat--;
	}
	if(remain)
	{
//		delay_us(remain*1000); //延时多少ms
		if(remain>500)
		{
			delay_us(500*1000); //延时500ms
			remain = remain - 500;
		}

		delay_us(remain*1000);
	}
}



////////////////////////////////////////////////////////////////////////
#else
volatile static uint32_t delay;

/*!
    \brief      configure systick
    \param[in]  none
    \param[out] none
    \retval     none
*/
void delay_init(int SYSCLK)
{
    /* setup systick timer for 1000Hz interrupts 1ms中断*/
    if (SysTick_Config(SystemCoreClock / 1000U)){
        /* capture error */
        while (1){
        }
    }
    /* configure the systick handler priority */
    NVIC_SetPriority(SysTick_IRQn, 0x00U);
}

/*!
    \brief      delay a time in milliseconds
    \param[in]  count: count in milliseconds
    \param[out] none
    \retval     none
*/
void delay_ms(uint32_t count)
{
    delay = count;

    while(0U != delay){
    }
}

/*!
    \brief      delay decrement
    \param[in]  none
    \param[out] none
    \retval     none
*/
void delay_decrement(void)
{
    if (0U != delay){
        delay--;
    }
}
#endif


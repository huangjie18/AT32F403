#include "delay.h"

#if (delay_mode == 1)
static u8 	fac_us = 0;
static u16 	fac_ms = 0;

void delay_init(int SYSCLK)
{
	//ѡ���ⲿʱ��  HCLK/8,���Ǽ���һ�μ�ʱ��1/(HCLK/8)=8/HCLK��
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	
	//��Ҫ��ʱ1us,�൱����Ҫ1/(1M)�룬��������=(1/(1M)) / (8/HCLK) = HCLK/8M
//	fac_us = SYSCLK/8;  //����8����ΪHCLK/8,�����4��Ƶ�ͳ���4
	fac_us = SystemCoreClock/8000000;
	fac_ms = (u16) fac_us*1000;
}

//��ʱus
//����ΪҪ��ʱ��us��
//���ֵΪgd_us*fac_us<0xffffff,gd_us<(0xffffff/fac_us)=671088
void delay_us(u32 gd_us)
{
	u32 temp;	    	 
	SysTick->LOAD=gd_us*fac_us; 				//ʱ�����	  		 
	SysTick->VAL=0x00;        					//��ռ�����
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//��ʼ����	  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));		//�ȴ�ʱ�䵽��   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//�رռ�����
	SysTick->VAL =0X00;  
}


/************************************************
�������� �� gd_delay_ms
��    �� �� ��ʱms��
��    �� �� ��ʱ����ms
�� �� ֵ �� ��
ע    �� �� SysTick->LOADΪ24λ�Ĵ���������(nms*1000*(SYSTICK/8))<=0XFFFFFF
			��72M�����£�nms<=1864
			���Բ��÷ֶ���ʱ���������ʱ��Χ
*************************************************/
void delay_ms(u32 ms)
{
	u8 repeat=ms/1000;    //�õ�Ҫ��ʱ������
	u16 remain = ms%1000;
	while(repeat)
	{
//		delay_us(1000000); //1s����ͬ��Ƶ����Ҫ�ģ����ܲ�����1000000
		delay_us(600000);  //��Ƶ200Mʱ�����ֵ���ܳ���671088
		delay_us(400000);
		repeat--;
	}
	if(remain)
	{
//		delay_us(remain*1000); //��ʱ����ms
		if(remain>500)
		{
			delay_us(500*1000); //��ʱ500ms
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
    /* setup systick timer for 1000Hz interrupts 1ms�ж�*/
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


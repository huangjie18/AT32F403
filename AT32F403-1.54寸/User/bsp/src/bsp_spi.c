#include "bsp_spi.h"
#define SPI1_GPIO	  GPIOA
#define SPI1_PIN_SCK  GPIO_Pins_5  //PA5
#define SPI1_PIN_MOSI GPIO_Pins_7  //PA7
#define SPI1_PIN_MISO GPIO_Pins_6  //PA6
#define SPI1_PIN_RESET GPIO_Pins_8 //PA8
//使用SPI1
//参数：该SPI设备是主设备还是从设备
void bsp_spi_gpio_init(uint16_t SPI_Mode)
{
	GPIO_InitType GPIO_InitStructure;
	
	//首先开启时钟线
	RCC_APB2PeriphClockCmd(RCC_APB2PERIPH_GPIOA,ENABLE);  //开启GPIOA时钟线
	RCC_APB2PeriphClockCmd(RCC_APB2PERIPH_SPI1, ENABLE);  //开启SPI1时钟线
	
	
	GPIO_InitStructure.GPIO_Pins = SPI1_PIN_SCK|SPI1_PIN_MOSI;
	GPIO_InitStructure.GPIO_MaxSpeed = GPIO_MaxSpeed_50MHz;
	
	if(SPI_Mode == SPI_MODE_MASTER)
	{
		//作为主设备
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //推挽复用输出
	}
	else
	{
		//作为从设备
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
	}
	//SPI1初始化
	GPIO_Init(SPI1_GPIO,&GPIO_InitStructure);
	
	//因为这里把PA6当做LCD的DC指令，PA8当做LCD的复位引脚，所以配置为推挽输出
	GPIO_InitStructure.GPIO_Pins = SPI1_PIN_MISO|SPI1_PIN_RESET;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT_PP;  //推挽输出
	GPIO_InitStructure.GPIO_MaxSpeed = GPIO_MaxSpeed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//配置SPI
	SPI1_Config();
}

//SPI1配置文件
void SPI1_Config(void)
{
	SPI_InitType   SPI_InitStructure;
	
	SPI_InitStructure.SPI_TransMode = SPI_TRANSMODE_TX_HALFDUPLEX; //设置SPI单向发送
	SPI_InitStructure.SPI_Mode = SPI_MODE_MASTER;    //设置SPI设备为主设备
	SPI_InitStructure.SPI_FrameSize = SPI_FRAMESIZE_8BIT; //设置SPI的数据大小:SPI发送接收8位帧结构
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_HIGH;  //串行同步时钟的空闲状态为高电平
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2EDGE; //串行同步时钟的第二个跳变沿（上升或下降）数据被采样
	SPI_InitStructure.SPI_NSSSEL = SPI_NSSSEL_SOFT; //NSS软件设置
	SPI_InitStructure.SPI_MCLKP = SPI_MCLKP_2;    //定义波特率预分频的值
	SPI_InitStructure.SPI_FirstBit = SPI_FIRSTBIT_MSB; //指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
	SPI_InitStructure.SPI_CPOLY = 7;  //CRC值计算的多项式
	SPI_Init(SPI1, &SPI_InitStructure); //根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器
	
	SPI_Enable(SPI1, ENABLE); //使能SPI外设
}

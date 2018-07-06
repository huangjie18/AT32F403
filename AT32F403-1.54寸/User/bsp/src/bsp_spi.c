#include "bsp_spi.h"
#define SPI1_GPIO	  GPIOA
#define SPI1_PIN_SCK  GPIO_Pins_5  //PA5
#define SPI1_PIN_MOSI GPIO_Pins_7  //PA7
#define SPI1_PIN_MISO GPIO_Pins_6  //PA6
#define SPI1_PIN_RESET GPIO_Pins_8 //PA8
//ʹ��SPI1
//��������SPI�豸�����豸���Ǵ��豸
void bsp_spi_gpio_init(uint16_t SPI_Mode)
{
	GPIO_InitType GPIO_InitStructure;
	
	//���ȿ���ʱ����
	RCC_APB2PeriphClockCmd(RCC_APB2PERIPH_GPIOA,ENABLE);  //����GPIOAʱ����
	RCC_APB2PeriphClockCmd(RCC_APB2PERIPH_SPI1, ENABLE);  //����SPI1ʱ����
	
	
	GPIO_InitStructure.GPIO_Pins = SPI1_PIN_SCK|SPI1_PIN_MOSI;
	GPIO_InitStructure.GPIO_MaxSpeed = GPIO_MaxSpeed_50MHz;
	
	if(SPI_Mode == SPI_MODE_MASTER)
	{
		//��Ϊ���豸
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //���츴�����
	}
	else
	{
		//��Ϊ���豸
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
	}
	//SPI1��ʼ��
	GPIO_Init(SPI1_GPIO,&GPIO_InitStructure);
	
	//��Ϊ�����PA6����LCD��DCָ�PA8����LCD�ĸ�λ���ţ���������Ϊ�������
	GPIO_InitStructure.GPIO_Pins = SPI1_PIN_MISO|SPI1_PIN_RESET;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT_PP;  //�������
	GPIO_InitStructure.GPIO_MaxSpeed = GPIO_MaxSpeed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//����SPI
	SPI1_Config();
}

//SPI1�����ļ�
void SPI1_Config(void)
{
	SPI_InitType   SPI_InitStructure;
	
	SPI_InitStructure.SPI_TransMode = SPI_TRANSMODE_TX_HALFDUPLEX; //����SPI������
	SPI_InitStructure.SPI_Mode = SPI_MODE_MASTER;    //����SPI�豸Ϊ���豸
	SPI_InitStructure.SPI_FrameSize = SPI_FRAMESIZE_8BIT; //����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_HIGH;  //����ͬ��ʱ�ӵĿ���״̬Ϊ�ߵ�ƽ
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2EDGE; //����ͬ��ʱ�ӵĵڶ��������أ��������½������ݱ�����
	SPI_InitStructure.SPI_NSSSEL = SPI_NSSSEL_SOFT; //NSS�������
	SPI_InitStructure.SPI_MCLKP = SPI_MCLKP_2;    //���岨����Ԥ��Ƶ��ֵ
	SPI_InitStructure.SPI_FirstBit = SPI_FIRSTBIT_MSB; //ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
	SPI_InitStructure.SPI_CPOLY = 7;  //CRCֵ����Ķ���ʽ
	SPI_Init(SPI1, &SPI_InitStructure); //����SPI_InitStruct��ָ���Ĳ�����ʼ������SPIx�Ĵ���
	
	SPI_Enable(SPI1, ENABLE); //ʹ��SPI����
}

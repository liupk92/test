
#include "spi.h"
#include "TM7707.h"


void SPI1Init(void)
{
	spi_parameter_struct spi_init_struct;
	
	rcu_periph_clock_enable(RCU_GPIOB);
	rcu_periph_clock_enable(RCU_AF);
	rcu_periph_clock_enable(RCU_SPI1);
	
	/* SPI GPIO config:SCK, MOSI */
	gpio_init(GPIOB, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_13 | GPIO_PIN_15);
	/* SPI GPIO config:MISO */
	gpio_init(GPIOB, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_14);


	/* deinitilize SPI and the parameters */
	spi_i2s_deinit(SPI1);

	spi_struct_para_init(&spi_init_struct);

	/* configure SPI parameter */
	spi_init_struct.trans_mode           = SPI_TRANSMODE_FULLDUPLEX;
	spi_init_struct.device_mode          = SPI_MASTER;
	spi_init_struct.frame_size           = SPI_FRAMESIZE_8BIT;
	spi_init_struct.clock_polarity_phase = SPI_CK_PL_HIGH_PH_2EDGE;
	spi_init_struct.nss                  = SPI_NSS_SOFT;
	spi_init_struct.prescale             = SPI_PSC_64;
	spi_init_struct.endian               = SPI_ENDIAN_MSB;
	spi_init(SPI1, &spi_init_struct);
	
	spi_nss_internal_high(SPI1);
	spi_enable(SPI1);
    
}

/*!
    \brief      memory compare function
    \param[in]  src: source data pointer
    \param[in]  dst: destination data pointer
    \param[in]  length: the compare data length
    \param[out] none
    \retval     ErrStatus: ERROR or SUCCESS
*/
uint8_t SPI1Transfer(uint8_t data) 
{
	uint8_t receive;
	CS_0();
	
	while(RESET == spi_i2s_flag_get(SPI1, SPI_FLAG_TBE));
	spi_i2s_data_transmit(SPI1, data);
	
	while(RESET == spi_i2s_flag_get(SPI1, SPI_FLAG_RBNE));
  receive = spi_i2s_data_receive(SPI1);
	
	return receive;
}









//#include "TM7707.h"
///* SPI3初始化 */
//void SPI3Init(void)
//{
//    GPIO_InitTypeDef GPIO_InitStructure;
//    SPI_InitTypeDef  SPI_InitStructure;

//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE );   //使能GPIOB时钟
//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3,  ENABLE );   //使能SPI2时钟
//	
//		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
//		GPIO_PinRemapConfig(GPIO_Remap_SPI3,ENABLE);
//		GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE); 
//			
//	
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_12; //初始化SPI2引脚PB13->SCK,PB15->MOSI
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;          //设置为复用推挽输出
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;        //设置输出速率为50MHz
//    GPIO_Init(GPIOC, &GPIO_InitStructure);                   //初始化GPIOB
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;               //初始化SPI2引脚PB14->MISO
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;    //设置为浮空输入
//    GPIO_Init(GPIOC, &GPIO_InitStructure);                   //初始化GPIOB

//    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; //SPI设置为双线双向全双工
//    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;                      //设置SPI为主机模式
//    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;                  //设置8位数据格式
//    SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;                        //时钟空闲状态为高电平
//    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;                       //时钟第二个边沿沿进行数据锁存(被读取)
//    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;                          //NSS引脚信号由SSI位控制
//    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64; //波特率预分频值为2,波特率为APB1总线频率36M/2=18M
//    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;                 //数据传输为高位在前
//    SPI_InitStructure.SPI_CRCPolynomial = 7;                           //CRC值计算的多项式(实际未使用)
//    SPI_Init(SPI3, &SPI_InitStructure);                                //初始化外设SPI2
//    SPI_Cmd(SPI3, ENABLE);                                             //使能SPI2
//}

///* SPI1数据传输，data-发送的数据;返回值-接收到的数据*/
//uint8_t SPI3Transfer(uint8_t data)                       //使用寄存器操作以提供整体的数据传输速率
//{
//	CS_0();
//    while ((SPI3->SR & SPI_I2S_FLAG_TXE) == 0);  //等待发送完成
//    SPI3->DR = data;                             //写数据到发送缓冲区
//    while ((SPI3->SR & SPI_I2S_FLAG_RXNE) == 0); //等待接收缓冲区非空，表示移位寄存器将数据发送完毕     
//   	CS_1();
//	return SPI3->DR;                             //返回接收到的数据  
//}












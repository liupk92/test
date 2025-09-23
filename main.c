
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

















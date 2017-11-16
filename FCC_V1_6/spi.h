/************************************************************************/
/* \file spi.h                                                          */
/************************************************************************/
#ifndef SPI_H_INCLUDED
#define SPI_H_INCLUDED

#define MAX_SPI_READ_LENGTH 4
#define ADC_CONVERT_TIMEOUT 500
#define SPI_ENABLE_DEFAULT true
#define SPI_ADC_U2_ENABLED true
#define SPI_ADC_U3_ENABLED true
#define SPI_DAC_U5_ENABLED true
void spi_init(void);
void spi_enable(bool);
void poll_spi(void);
void spi_single_ended(bool);

#endif

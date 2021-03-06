/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "driver_examples.h"
#include "driver_init.h"
#include "utils.h"

/**
 * Example of using SPI_ADC to write "Hello World" using the IO abstraction.
 *
 * Since the driver is asynchronous we need to use statically allocated memory for string
 * because driver initiates transfer and then returns before the transmission is completed.
 *
 * Once transfer has been completed the tx_cb function will be called.
 */

static uint8_t example_SPI_ADC[12] = "Hello World!";

static void complete_cb_SPI_ADC(const struct spi_m_async_descriptor *const io_descr)
{
	/* Transfer completed */
}

void SPI_ADC_example(void)
{
	struct io_descriptor *io;
	spi_m_async_get_io_descriptor(&SPI_ADC, &io);

	spi_m_async_register_callback(&SPI_ADC, SPI_M_ASYNC_CB_XFER, (FUNC_PTR)complete_cb_SPI_ADC);
	spi_m_async_enable(&SPI_ADC);
	io_write(io, example_SPI_ADC, 12);
}

/**
 * Example of using USART_CTRL to write "Hello World" using the IO abstraction.
 *
 * Since the driver is asynchronous we need to use statically allocated memory for string
 * because driver initiates transfer and then returns before the transmission is completed.
 *
 * Once transfer has been completed the tx_cb function will be called.
 */

static uint8_t example_USART_CTRL[12] = "Hello World!";

static void tx_cb_USART_CTRL(const struct usart_async_descriptor *const io_descr)
{
	/* Transfer completed */
}

void USART_CTRL_example(void)
{
	struct io_descriptor *io;

	usart_async_register_callback(&USART_CTRL, USART_ASYNC_TXC_CB, tx_cb_USART_CTRL);
	/*usart_async_register_callback(&USART_CTRL, USART_ASYNC_RXC_CB, rx_cb);
	usart_async_register_callback(&USART_CTRL, USART_ASYNC_ERROR_CB, err_cb);*/
	usart_async_get_io_descriptor(&USART_CTRL, &io);
	usart_async_enable(&USART_CTRL);

	io_write(io, example_USART_CTRL, 12);
}

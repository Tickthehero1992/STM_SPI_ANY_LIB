#ifndef SPI_OWN_H_
#define SPI_OWN_H_

#include "main.h"

typedef struct
{
	uint16_t SCK;
	GPIO_TypeDef* SCK_PORT;

	uint16_t MOSI;
	GPIO_TypeDef* MOSI_PORT;

	uint16_t MISO;
	GPIO_TypeDef* MISO_PORT;

	uint16_t CSS;
	GPIO_TypeDef* CSS_PORT;

	_Bool CSS_ON;
	uint16_t speed;
} SPI_OWN_PINS;
extern uint32_t nCount; //counts of Ticks in 1 data Impulse
void spi_own_pins_delay(); // delay function
void spi_own_init(SPI_OWN_PINS, _Bool, uint16_t); //init ports spi, CSS, and speed of trancieve/receive
uint8_t spi_own_trans_recv(SPI_OWN_PINS, uint8_t); // trancieve/receive 1 byte
#endif

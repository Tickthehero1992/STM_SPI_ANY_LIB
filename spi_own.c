#include "spi_own.h"

uint32_t nCount;
void spi_own_pins_delay()
{
	//for (uint32_t i=0; i<80; i++);
}


void spi_own_init(SPI_OWN_PINS Port, _Bool CSS_yes, uint16_t speed) //Port struct, CSStrue or false, speed in Kbit/s
{

	HAL_GPIO_WritePin(Port.SCK_PORT,Port.SCK,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Port.MOSI_PORT,Port.MOSI,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Port.MISO_PORT,Port.MISO,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Port.CSS_PORT,Port.CSS,GPIO_PIN_RESET);

	Port.speed=speed;

	nCount = (HAL_RCC_GetHCLKFreq()/Port.speed);


	GPIO_InitTypeDef GPIO_InitStruct = {0};

	GPIO_InitStruct.Pin = Port.MOSI;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
	HAL_GPIO_Init(Port.MOSI_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = Port.SCK;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
	HAL_GPIO_Init(Port.SCK_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = Port.MISO;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(Port.MISO_PORT, &GPIO_InitStruct);

	if (CSS_yes)
		{
		  GPIO_InitStruct.Pin = Port.CSS;
		  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		  GPIO_InitStruct.Pull = GPIO_PULLUP;
		  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
		  HAL_GPIO_Init(Port.CSS_PORT, &GPIO_InitStruct);
		  HAL_GPIO_WritePin(Port.CSS_PORT,Port.CSS,GPIO_PIN_SET);
		  Port.CSS_ON=1;
		}

}

uint8_t spi_own_trans_recv(SPI_OWN_PINS Port, uint8_t b)
{
	uint8_t output=0;
	if(Port.CSS_ON)
	{
		HAL_GPIO_WritePin(Port.CSS_PORT,Port.CSS,GPIO_PIN_RESET);
	}
	for(uint8_t i=0; i<8; i++)
	{
		if(b&0x80) // if MSB bit is 1
		{
			HAL_GPIO_WritePin(Port.MOSI_PORT,Port.MOSI,GPIO_PIN_SET); // SET pin to 1

		}
		HAL_GPIO_WritePin(Port.SCK_PORT,Port.SCK,GPIO_PIN_SET);//SCK setup to 1 to get/put data
		spi_own_pins_delay();
		if(HAL_GPIO_ReadPin(Port.MISO_PORT, Port.MISO)==GPIO_PIN_SET) //read MISO
		{
			output+=1;
		}
		b=b<<1;
		if(i!=7)
		{
			output*=2;
		}

		HAL_GPIO_WritePin(Port.SCK_PORT,Port.SCK,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Port.MOSI_PORT,Port.MOSI,GPIO_PIN_RESET);
		spi_own_pins_delay();
	}

	if(Port.CSS_ON)
	{
		HAL_GPIO_WritePin(Port.CSS_PORT,Port.CSS,GPIO_PIN_SET);
	}
	return output;
}

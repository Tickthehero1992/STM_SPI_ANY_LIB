STM_SPI_ANY_LIB
This library let You to create your own SPI on STM.
Created SPI is NOT fast, it's speed about 267Kb/s half-duplex
Library contains structure SPI_OWN_PINS, which have elements:
 SCK, SCK_PORT;
MOSI, MOSI_PORT;
MISO, MISO_PORT;
CSS, CSS_PORT;
CSS_ON;
speed.


for initializing SPI Use fonction: 
spi_own_init(SPI_OWN_PINS,_Bool CSS_ON, uint16_t Speed_of_SPT)
for trancieve/recieve message Use function spi_own_trans_recv(SPI_OWN_PINS, uint8_t BYTE) - this function put 1 Byte, and get 1 Byte, if u use CSS,
it will latch after 1 byte.


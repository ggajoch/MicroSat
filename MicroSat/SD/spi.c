#include <avr/io.h>
#include <util/delay.h>
#include "integer.h"


#define DDR_SPI DDRB
#define DD_MOSI 2
#define DD_SCK 1
#define DD_MISO 3
#define DD_SS 0

void spi_init(void)
{
	
	/* Set MOSI and SCK output */
	DDR_SPI |= _BV(DD_MOSI) | _BV(DD_SCK) | _BV(DD_SS);
	DDR_SPI &= ~_BV(DD_MISO);
	
	/* Enable SPI, Master, set clock rate fck/128 */
	SPCR0 = _BV(SPE0) | _BV(MSTR0) | _BV(SPR00) | _BV(SPR10);
	SPSR0 = _BV(SPI2X0);
}
void init_spi(void)
{
	/* Set MOSI and SCK output */
	DDR_SPI |= _BV(DD_MOSI) | _BV(DD_SCK) | _BV(DD_SS);
	DDR_SPI &= ~_BV(DD_MISO);
	
	/* Enable SPI, Master, set clock rate fck/128 */
	SPCR0 = _BV(SPE0) | _BV(MSTR0) | _BV(SPR00) | _BV(SPR10);
	SPSR0 = _BV(SPI2X0);
}
uint8_t spi_send_receive_byte(uint8_t byte)
{
	/* Start transmission */
	SPDR0 = byte;
	
	/* Wait for transmission complete */
	while (!(SPSR0 & _BV(SPIF0)));
	
	/* Read the received byte */
	byte = SPDR0;
	
	return byte;
}

BYTE rcv_spi(void)
{
	BYTE data;

	SPDR0 = 0xff;
	while(!(SPSR0 & (1<<SPIF0)));
	data = SPDR0;

	return data;
}

unsigned char xmit_spi (BYTE data)
{
// Start transmission
SPDR0 = data;

// Wait for transmission complete
while(!(SPSR0 & (1<<SPIF0)));
data = SPDR0;

return(data);
}



void dly_100us (void)
{

_delay_us(100);
}
// spi.c

#include "spi.h"
#define BIT(in)	(1 << (in))	

void wait(unsigned int delay )														// Delay
{
	while(delay--)
	{
		asm("mov r0, r0");																// No-op
	}
}

void spi_pin_init(void)
{
	unsigned int var;

	var = gpioGPFSEL1;																	// Read current value of GPFSEL1- pin 10 & 11

	var &=~((7 << 0) | (7 << 3)); 													// Set as input pins GPIO = 000
	var |= ((4 << 0) | (4 << 3));														// Set to alt function ALT0, GPIO = 000

	gpioGPFSEL1 = var;																	// Write back updated value
	
	var = gpioGPFSEL0;																	// Read current value of GPFSEL1- pin 7,8 & 9

	var &=~((7 << 21) | (7 << 24) | (7 << 27));									// Set as input pins GPIO = 000
	var |= ((4 << 21) | (4 << 24) | (4 << 27));									// Set to alt function ALT0, GPIO = 000
	gpioGPFSEL0 =var;																		// Write back updated value
}

void spi_begin(void)
{	
	unsigned int var;
	spi_pin_init();
        
	SPI0_CONTROL = 0;
	SPI0_CONTROL |= BIT(SPI_C_CLEAR_RX) | BIT(SPI_C_CLEAR_TX);				// Clear TX and RX fifos
	
	var = SPI0_CONTROL;
	var &= ~(BIT(SPI_C_CPOL) | BIT(SPI_C_CPHA));	 								// Set data mode = 0 
	var &= ~(BIT(SPI_C_CS0) | BIT(SPI_C_CS1));									// Set to CS0 and Chip Select Polarity=LOW
	var &= ~BIT(SPI_C_CSPOL0);

	SPI0_CONTROL = var;																	// Write back updated value

 	SPI0_CLK = 1024;       																// Set clock to 250kHz
}

unsigned int spi_transfer(unsigned char value)
{
	unsigned int var = 0;
	unsigned int ret = 0;

	var = SPI0_CONTROL;
	var|= BIT(SPI_C_CLEAR_RX) | BIT(SPI_C_CLEAR_TX);							// Clear TX and RX fifos
	var|= BIT(SPI_C_TA);																	// Set TA = 1

	SPI0_CONTROL =var;																	// Write back updated value

	var = SPI0_CONTROL;																	// Maybe wait for TXD

	while (!(var & BIT(SPI_C_TXD)))
	{
		wait(1000000);   
	}

	SPI0_FIFO = value;																	// Write to TX FIFO

	//while (!(var & BIT(SPI_C_DONE)))												// Wait for DONE to be set

	wait(1000000); 
	
	ret = SPI0_FIFO;																		// Read RX FIFO

  	var = SPI0_CONTROL;																	// Set TA = 0
	var &= ~BIT(SPI_C_TA);
	SPI0_CONTROL =var;																	// Write back updated value

   return ret;
}

void spi_end(void)																		// Set all the SPI0 pins back to input
{
 	unsigned int var;

	var = gpioGPFSEL1;																	// Read current value of GPFSEL1- pin 10 & 11

	var &=~((7 << 0) | (7 << 3));														// Set as input pins GPIO = 000
 	gpioGPFSEL1 =var;																		// Write back updated value
	
	var = gpioGPFSEL0;																	// Read current value of GPFSEL1- pin 7,8 & 9

	var &=~((7 << 21) | (7 << 24) | (7 << 27));									// Set as input pins GPIO = 000
 	gpioGPFSEL1 =var;																		// Write back updated value
}

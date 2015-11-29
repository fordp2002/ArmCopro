// test.c

#include "spi.h"

int notmain(void)
{
	unsigned char data = 0;
	unsigned char ret;

	while (1)
	{
		spi_begin();
		ret = spi_transfer(data++);
		spi_end();
		wait(10000000);
	}

	return 0;
}

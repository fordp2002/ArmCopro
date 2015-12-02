// test.c

#include "spi.h"

u8 TxBuf[] = "\0Acorn Risk Machine!";
u8 RxBuf[sizeof(TxBuf)];

int notmain(void)
{
	while (1)
	{
		spi_begin();
		spi_transfer(TxBuf, RxBuf, sizeof(TxBuf));
		spi_end();
		wait(1000000);
	}

	return 0;
}

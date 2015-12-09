// test.c

#include "spi.h"
#include <stdint.h>
#include <stdio.h>
#include "../cpu80186/cpu80186.h"

u8 TxBuf[] = "\0Acorn Risk Machine!";
u8 RxBuf[sizeof(TxBuf)];

int notmain(void)
{
	while (1)
	{
		spi_begin();
		spi_transfer(TxBuf, RxBuf, sizeof(TxBuf));

		exec86(0xFFFFFFFF);																			// Should not return!

		spi_end();
		//wait(1000000);
	}

	return 0;
}

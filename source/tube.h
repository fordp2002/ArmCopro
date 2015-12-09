#include "spi.h"
#define CMD_WRITE 0x80
#define CMD_READ  0xC0

#define tube_read(Address)				spi_in(CMD_READ | ((Address) << 3))
#define tube_write(Address, Data)	spi_out((CMD_WRITE | ((Address) << 3)), (Data))

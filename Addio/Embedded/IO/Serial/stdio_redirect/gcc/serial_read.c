
#include "../../../stdio_redirect/addio_stdio_io.h"
#include <stdio.h>

#include "../../serial.h"

int _read(int file, char *ptr, int len); /* Remove GCC compiler warning */

int _read(int file, char *ptr, int len)
{
	int n = 0;

	if (file != 0) {
		return -1;
	}

	n = serial_readBytes((uint8_t *)ptr, len);
	if (n < 0) {
		return -1;
	}

	return n;
}


#include "../../../stdio_redirect/addio_stdio_io.h"
#include <stdio.h>

#include "../../serial.h"

int _write(int file, char *ptr, int len); /* Remove GCC compiler warning */

int _write(int file, char *ptr, int len)
{
	int n = 0;

	if ((file != 1) && (file != 2) && (file != 3)) {
		return -1;
	}

	//Force standard printf functions to use our write function.
	n = serial_write((const uint8_t *)ptr, len);
	if (n < 0) {
		return -1;
	}

	return n;
}

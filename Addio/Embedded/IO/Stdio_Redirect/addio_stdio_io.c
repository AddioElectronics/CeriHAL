#include <stdio.h>
#include "addio_stdio_io.h"

/** IO descriptor for STDIO access. */
static struct io_descriptor *stdio_io = NULL;

void stdio_io_init(struct io_descriptor *io)
{
#if defined(__GNUC__)
	/* Specify that stdout and stdin should not be buffered. */
	setbuf(stdout, NULL);
	setbuf(stdin, NULL);
	/* Note: Already the case in IAR's Normal DLIB default configuration
	 * and AVR GCC library:
	 * - printf() emits one character at a time.
	 * - getchar() requests only 1 byte to exit.
	 */
#endif
	stdio_io = io;
}



void stdio_io_set_io(struct io_descriptor* io)
{
	stdio_io = io;	
}

int32_t stdio_io_read(uint8_t* buf, const uint16_t len)
{
	if (stdio_io == NULL) {
		return 0;
	}
	return io_read(stdio_io, buf, len);
}

int32_t stdio_io_write(const uint8_t* buf, const uint16_t len)
{
	if (stdio_io == NULL) {
		return 0;
	}
	return io_write(stdio_io, buf, len);
}

int32_t stdio_io_peek()
{
	if (stdio_io == NULL) {
		return 0;
	}
	return io_peek(stdio_io);
}

//int32_t stdio_io_get()
//{
	//if (stdio_io == NULL) {
		//return 0;
	//}
	//return io_get(stdio_io);
//}

int32_t stdio_io_peekMany(uint8_t* buf, const uint16_t len)
{
	if (stdio_io == NULL) {
		return 0;
	}
	return io_peekMany(stdio_io, buf, len);
}

int32_t stdio_io_rxReady()
{
	if (stdio_io == NULL) {
		return 0;
	}
	return io_rxReady(stdio_io);
}

int32_t stdio_io_txReady()
{
	if (stdio_io == NULL) {
		return 0;
	}
	return io_txReady(stdio_io);
}
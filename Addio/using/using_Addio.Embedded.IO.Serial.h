/*
*	Includes all sub-components of Addio/Embedded/IO/Serial
*/
#ifndef USING_ADDIO_EMBEDDED_IO_SERIAL_H_
#define USING_ADDIO_EMBEDDED_IO_SERIAL_H_


#if __has_include("../embedded/io/serial/serial.h")

#include "../embedded/io/serial/serial.h"
#include "../embedded/io/serial/print/print.h"
#include "../embedded/io/serial/reader/reader.h"

#else
#error Library does not exist.
#endif


#endif /* USING_ADDIO_EMBEDDED_IO_SERIAL_H_ */
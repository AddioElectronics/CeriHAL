/*
*	Includes all sub-components of Addio/Embedded/IO
*/
#ifndef USING_ADDIO_EMBEDDED_IO_H_
#define USING_ADDIO_EMBEDDED_IO_H_

#if __has_include("../embedded/io/addio.embedded.io.h")

#include "../embedded/io/addio_io.h"
#include "../embedded/io/Stdio_Redirect/addio_stdio_io.h"
#include "../embedded/io/Atmel Start/usb_cdc_stdio/usb_cdc_stdio.h"
#include "../embedded/io/serial/serial.h"
#include "../embedded/io/serial/print/print.h"
#include "../embedded/io/serial/reader/reader.h"

#else
#error Library does not exist.
#endif

#endif /* USING_ADDIO_EMBEDDED_IO_H_ */
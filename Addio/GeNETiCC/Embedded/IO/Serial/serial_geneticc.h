#ifndef SERIAL_MACROS_H_
#define SERIAL_MACROS_H_

/*
*	Addio Embedded Serial library required
*/
#if __has_include("Addio/embedded/io/serial/serial.h")

#include "internal/serial_geneticc_internal_macros.h"
#include "print/print_geneticc.h"
#include "reader/reader_geneticc.h"

/*
*	Changes the active IO port using the port's ID.
*	*Serial read, write and print functions/macros will now use the I/O descriptor at port_id.
*
*	/param	port_id		The index of the descriptor to activate.
*/
#define Serial(port_id)				serial_set_port(port_id)


/*
*	Gets the active serial port ID.
*/
#define Serial_ActivePort			serial_get_active_port_id

/*
*	Add an I/O descriptor into the list for quick switching with "Serial(port_id)".
*	The I/O descriptor will also be set as the active descriptor.
*/
#if SERIAL_IO_PORTS == 1
#define Serial_Init(io)			serial_init(io, 0)
#else
#define Serial_Init(io, port_id)	serial_init(io, port_id)
#endif


/*
*	Sets the maximum milliseconds to wait for serial data. It defaults to 1000 milliseconds.
*
*	Serial_SetTimeout(time)
*
*	/param	time		unsigned long		Timeout duration in milliseconds.
*/
#define Serial_SetTimeout(time)				serial_setTimeout(time)

/*
*	Gets the maximum milliseconds to wait for serial data.
*
*	Serial_GetTimeout()
*
*	/returns			unsigned long		Timeout duration in milliseconds.
*/
#define Serial_GetTimeout(time)				serial_getTimeout()

#endif
#endif /* SERIAL_MACROS_H_ */
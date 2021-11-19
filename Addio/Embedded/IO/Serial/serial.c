#include "serial.h"

#include <utils_assert.h>

#if __has_include("hal_io.h")
/*
*	Array of IO ports available to print or read.
*/
struct io_descriptor* serial_io_ports[SERIAL_IO_PORTS] = {0};

/*
*	The ID of the active port, or -1 if no ports have been initialized or if the last port was activated using "serial_set_port_io_descr."
*/
int8_t active_port_id = -1;

/*
*	The active IO port.
*/
struct io_descriptor* serial_io;

/*
*	The timeout value for serial read, write and print functions.
*/
unsigned long serial_timeout = SERIAL_TIMEOUT;


/*
*	Add an I/O descriptor into the list for quick switching with "serial_set_port".
*	If an I/O descriptor has not been set, it will be set as the active descriptor.
*	
*	*If using GeNETiCC, this is required for the Serial(port_id) macro. 
*
*	/param	io_descr	The I/O descriptor to add.
*	/param	port_id		The index at which to add the descriptor.
*/
void serial_init(struct io_descriptor* io_descr, uint8_t port_id)
{
	//Assert the port ID is in range, and the ID is not in use.
	ASSERT(port_id < SERIAL_IO_PORTS && port_id >= 0 && serial_io_ports[port_id] == NULL);
	
	//Set the next port to the IO descriptor.
	serial_io_ports[port_id] = io_descr;	
	serial_io = io_descr;
	
	if(active_port_id != -1)
	{
		active_port_id = port_id;
		stdio_io_set_io(serial_io);
	}
}

/*
*	Sets an I/O descriptor as the active descriptor from its port ID.
*	All Serial read, write and print functions will now use the active descriptor.
*
*	/param	port_id		Activate the I/O descriptor which was initialized with the index.
*/
void __attribute__((__always_inline__)) serial_set_port(uint8_t port_id)
{
	serial_io = serial_io_ports[port_id];
	active_port_id = port_id;
	stdio_io_set_io(serial_io);
	
	ASSERT(serial_io);
}

/*
*	Sets an I/O descriptor as the active descriptor.
*	All Serial read, write and print functions will now use the active descriptor.
*
*	/param	port_id		Activate the I/O descriptor which was initialized with the index.
*/
int8_t __attribute__((__always_inline__)) serial_set_port_io_descr(struct io_descriptor* io_desc)
{
	serial_io = io_desc;
	stdio_io_set_io(serial_io);
	active_port_id = -1;
	
	//int8_t port_id = -1;
	//
	////Try to find the IO descriptor.
	//for(uint8_t i = 0; i < SERIAL_IO_PORTS; i++)
	//{
		//if(serial_io_ports[i] == io_desc)
		//{
			//port_id = i;
			//break;
		//}
	//}
	//
	////Not in list.
	//if(port_id == -1)
	//port_id = serial_get_empty_port();
	//
	////List full
	//ASSERT(!(port_num == -1));
	//
	//serial_set_port(port_id);
	//return port_id;
}

/*
*	Gets the active port ID. If the active I/O descriptor was set using "serial_set_port_io_descr,"
*	the port ID is unknown and will return -1.
*
*	/returns	The ID of the active I/O descriptor, or -1 if it was set using "serial_set_port_io_descr."
*/
int8_t __attribute__((__always_inline__)) serial_get_active_port_id()
{
	return active_port_id;
}

/*
*	Gets the I/O descriptor of the active port.
*
*	/returns	The I/O descriptor of the active port.
*/
struct io_descriptor* __attribute__((__always_inline__)) serial_get_active_port_io_desc()
{
	return serial_io;
}

/*
*	Gets the index of the next empty port.
*
*	/returns	The index of the next empty port, or -1 if there is no free IDs.
*/
int8_t serial_get_empty_port_id()
{
	for(uint8_t i = 0; i < SERIAL_IO_PORTS; i++)
	{
		if(serial_io_ports[i] == NULL)
		return i;
	}
	return -1;
}

/*
*	Sets the maximum number of milliseconds to wait before timeout.
*/
void __attribute__((__always_inline__)) serial_setTimeout(unsigned long timeout)
{
	serial_timeout = timeout;
}

/*
*	Gets the current number of milliseconds to wait before timeout.
*/
unsigned long __attribute__((__always_inline__)) serial_getTimeout()
{
	return serial_timeout;
}

#else
#error Unsupported
#endif
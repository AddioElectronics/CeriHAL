#ifndef SERIAL_H_
#define SERIAL_H_

/*
*	hal_io or Addio Embedded IO library required.
*/
#if __has_include("hal_io.h") || __has_include("../addio_io.h")



#if __has_include("hal_io.h")
#include <hal_io.h>
#elif __has_include("../addio_io.h")
#include "../addio_io.h"
#else
/*Add custom IO library*/
#error Unsupported
#endif

#include "serial_config.h"
#include "serial_defs.h"



#pragma region Functions


void serial_init(struct io_descriptor* io_descr, uint8_t port_num);
void serial_set_port(uint8_t port_num);
int8_t serial_set_port_io_descr(struct io_descriptor* io_desc);
int8_t serial_get_active_port_id();
struct io_descriptor* serial_get_active_port_io_desc();
int8_t serial_get_empty_port_id();

void __attribute__((__always_inline__)) serial_setTimeout(unsigned long timeout);
unsigned long __attribute__((__always_inline__)) serial_getTimeout();


#pragma endregion Functions


#include "print/print.h"
#include "reader/reader.h"


#else
#warning Unsupported
#endif
#endif /* SERIAL_H_ */
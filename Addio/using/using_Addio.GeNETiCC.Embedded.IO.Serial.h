/*
*	Includes all sub-components of Addio/Geneticc/Embedded/IO/Serial
*/
#ifndef USING_GENETICC_EMBEDDED_IO_SERIAL_H_
#define USING_GENETICC_EMBEDDED_IO_SERIAL_H_

#include "../Config/addio_multisystem_config.h"

#if __has_include("../GeNETiCC/Embedded/IO/serial/serial_geneticc.h") && SYSTEM_TYPE == SYSTEM_TYPE_EMBEDDED

#include "../GeNETiCC/geneticc.h"
#include "../GeNETiCC/Embedded/IO/serial/serial_geneticc.h"
#include "../GeNETiCC/Embedded/IO/serial/print/print_geneticc.h"
#include "../GeNETiCC/Embedded/IO/serial/reader/reader_geneticc.h"


#else
#error Library does not exist.
#endif

#endif /* USING_GENETICC_EMBEDDED_IO_SERIAL_H_ */
/*
*	Includes all sub-components of Addio/Geneticc/Embedded/IO
*/
#ifndef USING_GENETICC_EMBEDDED_IO_H_
#define USING_GENETICC_EMBEDDED_IO_H_

#include "Addio/Config/addio_multisystem_config.h"

#if __has_include("Addio/GeNETiCC/Embedded/IO/geneticc_embedded_io.h") && SYSTEM_TYPE == SYSTEM_TYPE_EMBEDDED

#include "Addio/GeNETiCC/geneticc.h"
#include "Addio/GeNETiCC/Embedded/IO/serial/serial_geneticc.h"
#include "Addio/GeNETiCC/Embedded/IO/serial/print/print_geneticc.h"
#include "Addio/GeNETiCC/Embedded/IO/serial/reader/reader_geneticc.h"

#else
#error Library does not exist.
#endif

#endif /* USING_GENETICC_EMBEDDED_IO_H_ */

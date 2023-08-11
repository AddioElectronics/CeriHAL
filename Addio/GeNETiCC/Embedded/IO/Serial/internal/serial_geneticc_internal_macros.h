#ifndef SERIAL_GENETICC_INTERNAL_MACROS_H_
#define SERIAL_GENETICC_INTERNAL_MACROS_H_

#include "Addio/GeNETiCC/preprocess/geneticc_internal_macros.h"

//#define SERIAL_1(port_num)							serial_set_port(port_num)
//#define SERIAL_0									serial_get_active_port
//#define SERIAL_MACRO_CHOOSER(...)	\
//GET_ARGUMENT_1(__VA_ARGS__,			\
//SERIAL_1,							\
//SERIAL_0, )

#define SERIAL_INIT_2(io, port_num)					serial_init(io, port_num)
#define SERIAL_INIT_1(io)							serial_init(io)
#define SERIAL_INIT_MACRO_CHOOSER(...)	\
GET_ARGUMENT_2(__VA_ARGS__,				\
SERIAL_2,								\
SERIAL_1, )

#endif /* SERIAL_GENETICC_INTERNAL_MACROS_H_ */
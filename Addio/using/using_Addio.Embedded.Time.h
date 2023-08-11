/*
*	Includes all sub-components of Addio/Universal/Timing
*/
#ifndef USING_ADDIO_EMBEDDED_TIME_H_
#define USING_ADDIO_EMBEDDED_TIME_H_

#if __has_include("Addio/Embedded/time/Timing/System_Timer/system_timer.h")
#include "Addio/Embedded/time/Timing/System_Timer/system_timer.h"
#else
#error Library does not exist.
#endif

#endif /* USING_ADDIO_EMBEDDED_TIME_H_ */
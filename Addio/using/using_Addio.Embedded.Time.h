/*
*	Includes all sub-components of Addio/Universal/Timing
*/
#ifndef USING_ADDIO_EMBEDDED_TIME_H_
#define USING_ADDIO_EMBEDDED_TIME_H_

#if __has_include("../embedded/time/addio.embedded.timing.h")

#include "../embedded/time/Timing/System_Timer/system_timer.h"
#include "../embedded/time/Timing/timing.h"

#else
#error Library does not exist.
#endif

#endif /* USING_ADDIO_EMBEDDED_TIME_H_ */
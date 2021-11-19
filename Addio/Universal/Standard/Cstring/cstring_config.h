#ifndef CSTRING_CONFIG_H_
#define CSTRING_CONFIG_H_

#include "../../../config/addio_multisystem_config.h"

#define CSTRING_DEFAULT_CAPACITY 16

#define CSTRING_MAX_SIZE		2048

/*
*	When adding items to a list, and the capacity has ran out,
*	how should we determine the amount of extra memory to allocate?
*/
#define CSTRING_CAPACITY_INCREASE_METHOD_ADD		0
#define CSTRING_CAPACITY_INCREASE_METHOD_MULTIPLY	1

#if SYSTEM_TYPE == SYSTEM_TYPE_PC
#define CSTRING_CAPACITY_INCREASE_METHOD CSTRING_CAPACITY_INCREASE_METHOD_MULTIPLY
#elif SYSTEM_TYPE == SYSTEM_TYPE_EMBEDDED
#define CSTRING_CAPACITY_INCREASE_METHOD CSTRING_CAPACITY_INCREASE_METHOD_ADD
#endif

/*
*	When adding items to a list, and the capacity has ran out,
*	how much extra memory should be allocated?
*
*	*Depends on LIST_CAPACITY_INCREASE_METHOD
*
*	The higher the value will of course use more memory,
*	but the next time you add/insert values,
*	there may very well be a performance boost.
*/
#if SYSTEM_TYPE == SYSTEM_TYPE_PC
#define CSTRING_CAPICTY_INCREASE_COUNT			10		//The array will increase by x elements.
#define CSTRING_CAPICTY_INCREASE_MULTIPLIER		2		//The array will increase by x * size.
#elif SYSTEM_TYPE == SYSTEM_TYPE_EMBEDDED
#define CSTRING_CAPICTY_INCREASE_COUNT			10		//The array will increase by x elements.
#define CSTRING_CAPICTY_INCREASE_MULTIPLIER		1.5f	//The array will increase by x * size.
#endif

#if		CSTRING_CAPACITY_INCREASE_METHOD == CSTRING_CAPACITY_INCREASE_METHOD_ADD
#define CSTRING_INCREASE_CAPACITY(capacitySize)		capacitySize + CSTRING_CAPICTY_INCREASE_COUNT
#elif	CSTRING_CAPACITY_INCREASE_METHOD == CSTRING_CAPACITY_INCREASE_METHOD_MULTIPLY
#define CSTRING_INCREASE_CAPACITY(capacitySize)		capacitySize * CSTRING_CAPICTY_INCREASE_MULTIPLIER
#endif


#endif /* CSTRING_CONFIG_H_ */
#ifndef GENETICC_H_
#define GENETICC_H_

#include <stdint.h>
#include <stdbool.h>
#include <limits.h>

#include "config/geneticc_config.h"
#include "geneticc_defs.h"
#include "preprocess/geneticc_internal_macros.h"

/*
*	Union which contains all value types.
*	Useful for converting from int types to and from floating types, without casting the bits.
*	Also makes _Generic macros which call functions to all value types possible.
*
*	*Not all values are included at the moment.
*/
typedef union generic_union
{
	const char* ccp;
	char*cp;
	signed char* scp;
	unsigned char* uscp;
	int* ip;
	unsigned int* uip;
	short* sp;
	unsigned short* usp;
	long* lp;
	unsigned long* ulp;
	long long* llp;
	unsigned long long* ullp;
	_Bool* bp;	
	float* fp;
	double* dp;
	uint8_t* u8p;
	int8_t* s8p;
	uint16_t* u16p;
	int16_t* s16p;
	uint32_t* u32p;
	int32_t* s32p;
	uint64_t* u64p;
	int64_t* s64p;
	void* vp;
	
	char c;
	signed char sc;
	unsigned char usc;
	int i;
	unsigned int ui;
	short s;
	unsigned short us;
	long l;
	unsigned long ul;	
	long long ll;
	unsigned long long ull;
	float f;
	double d;
	_Bool b;
	enum e;
	uint8_t u8;
	int8_t s8;
	uint16_t u16;
	int16_t s16;
	uint32_t u32;
	int32_t s32;
	uint64_t u64;
	int64_t s64;
	
}generic_union_t;

typedef struct
{
	generic_union_t value;
	type_t type;
}geneticc_t;


//typedef struct  
//{
	//generic_union_t value;
	//bool hasValue;
//}nullable_t;


//static uint64_t /*__attribute__(__always_inline)*/ trim_extra_bytes(uint64_t value, size_t elem_size)
//{
	//switch(elem_size)
	//{
		//case 1:
		//return (uint8_t)value;	// & 0xff;
		//case 2:
		//return (uint16_t)value;	// & 0xffff;
		//case 4:
		//return (uint32_t)value;	// & 0xffffffff;
		//case 8:
		//return value;
		//default:				//bool
		//return value & 0x01;
	//}
//}

type_size_t geneticc_get_sized_type_abs(type_sized_t type);

signed_type_size_t geneticc_get_signed_sized_type_abs(type_sized_t type);

generic_union_t geneticc_cast_pointer(uint8_t* value, index_t index, type_sized_t type, type_sized_t cast_to);

//Need to determine which one to keep
generic_union_t geneticc_cast_b(generic_union_t value, type_sized_t type, type_sized_t cast_to);
generic_union_t geneticc_cast(generic_union_t value, type_sized_t type, type_sized_t cast_to, int8_t old_elem_size, int8_t new_elem_size);



#endif /* GENETICC_H_ */
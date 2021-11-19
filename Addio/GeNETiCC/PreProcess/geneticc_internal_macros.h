#ifndef GENETICC_INTERNAL_MACROS_H_
#define GENETICC_INTERNAL_MACROS_H_

#include "geneticc_macro_type_repeater.h"

/*
*	Macros used in ARRAY_..._MACRO_CHOOSER macros, used to change parameter counts.
*/
#define GET_ARGUMENT_1(varg, arg1, ...) arg1

/*
*	Macros used in ARRAY_..._MACRO_CHOOSER macros, used to change parameter counts.
*/
#define GET_ARGUMENT_2(varg, arg1, arg2, ...) arg2

/*
*	Macros used in ARRAY_..._MACRO_CHOOSER macros, used to change parameter counts.
*/
#define GET_ARGUMENT_3(varg, arg1, arg2, arg3, ...) arg3

/*
*	Macros used in ARRAY_..._MACRO_CHOOSER macros, used to change parameter counts.
*/
#define GET_ARGUMENT_4(varg, arg1, arg2, arg3, arg4, ...) arg4

/*
*	Macros used in ARRAY_..._MACRO_CHOOSER macros, used to change parameter counts.
*/
#define GET_ARGUMENT_5(varg, arg1, arg2, arg3, arg4, arg5, ...) arg5

/*
*	Macros used in ARRAY_..._MACRO_CHOOSER macros, used to change parameter counts.
*/
#define GET_ARGUMENT_6(varg, arg1, arg2, arg3, arg4, arg5, arg6, ...) arg6

/*
*	Macros used in ARRAY_..._MACRO_CHOOSER macros, used to change parameter counts.
*/
#define GET_ARGUMENT_7(varg, arg1, arg2, arg3, arg4, arg5, arg6, arg7, ...) arg7

/*
*	/param	pointer		The pointer value to dereference
*	/param	type		The value used to get the type.
*
*	/returns			The index of the smallest value in the array.
*/
#define GENETICC_DEREFERENCE(pointer, type) _Generic((type),			\
const void*:				*(const void**)pointer,						\
void*:						*(void**)pointer,							\
const char*:				*(const char**)pointer,						\
char*:						*(char**)pointer,							\
const unsigned char*:		*(const unsigned char**)pointer,			\
unsigned char*:				*(unsigned char**)pointer,					\
const signed char*:			*(const signed char**)pointer,				\
signed char*:				*(signed char**)pointer,					\
const int*:					*(const int**)pointer,						\
int*:						*(int**)pointer,							\
const unsigned int*:		*(const unsigned int**)pointer,				\
unsigned int*:				*(unsigned int**)pointer,					\
const short*:				*(const short**)pointer,					\
short*:						*(short**)pointer,							\
const unsigned short*:		*(const unsigned short**)pointer,			\
unsigned short*:			*(unsigned short**)pointer,					\
const long*:				*(const long**)pointer,						\
long*:						*(long**)pointer,							\
const unsigned long*:		*(const unsigned long**)pointer,			\
unsigned long*:				*(unsigned long**)pointer,					\
const long long*:			*(const long long**)pointer,				\
long long*:					*(long long**)pointer,						\
const unsigned long long*:	*(const unsigned long long**)pointer,		\
unsigned long long*:		*(unsigned long long**)pointer,				\
_Bool*:						*(_Bool**)pointer,							\
double*:					*(double**)pointer,							\
float *:					*(float**)pointer,							\
const char:					*(const char*)pointer,						\
char:						*(char*)pointer,							\
const unsigned char:		*(const unsigned char*)pointer,				\
unsigned char:				*(unsigned char*)pointer,					\
const signed char:			*(const signed char*)pointer,				\
signed char:				*(signed char*)pointer,						\
const int:					*(const int*)pointer,						\
int:						*(int*)pointer,								\
const unsigned int:			*(const unsigned int*)pointer,				\
unsigned int:				*(unsigned int*)pointer,					\
const short:				*(const short*)pointer,						\
short:						*(short*)pointer,							\
const unsigned short:		*(const unsigned short*)pointer,			\
unsigned short:				*(unsigned short*)pointer,					\
const long:					*(const long*)pointer,						\
long:						*(long*)pointer,							\
const unsigned long:		*(const unsigned long*)pointer,				\
unsigned long:				*(unsigned long*)pointer,					\
const long long:			*(const long long*)pointer,					\
long long:					*(long long*)pointer,						\
const unsigned long long:	*(const unsigned long long*)pointer,		\
unsigned long long:			*(unsigned long long*)pointer,				\
_Bool:						*(_Bool*)pointer,							\
double:						*(double*)pointer,							\
float :						*(float*)pointer)


#endif /* GENETICC_INTERNAL_MACROS_H_ */
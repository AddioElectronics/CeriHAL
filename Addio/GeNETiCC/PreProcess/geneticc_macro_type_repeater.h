#ifndef GENETICC_MACRO_TYPE_REPEATER_H_
#define GENETICC_MACRO_TYPE_REPEATER_H_


#define GENETICC_REPEAT_POINTER_TYPES(macro) \
const char*:				macro,			\
char*:						macro,			\
const unsigned char*:		macro,			\
unsigned char*:				macro,			\
const signed char*:			macro,			\
signed char*:				macro,			\
const int*:					macro,			\
int*:						macro,			\
const unsigned int*:		macro,			\
unsigned int*:				macro,			\
const short*:				macro,			\
short*:						macro,			\
const unsigned short*:		macro,			\
unsigned short*:			macro,			\
const long*:				macro,			\
long*:						macro,			\
const unsigned long*:		macro,			\
unsigned long*:				macro,			\
const long long*:			macro,			\
long long*:					macro,			\
const unsigned long long*:	macro,			\
unsigned long long*:		macro,			\
const float* :				macro,			\
float* :					macro,			\
const double* :				macro,			\
double* :					macro,			\
_Bool* :					macro,			\
const void*:				macro,			\
void*:						macro,			


#define GENETICC_REPEAT_POINTER_TYPES_SIGNED(macro) \
const char*:				macro,			\
char*:						macro,			\
const signed char*:			macro,			\
signed char*:				macro,			\
const int*:					macro,			\
int*:						macro,			\
const short*:				macro,			\
short*:						macro,			\
const long*:				macro,			\
long*:						macro,			\
const long long*:			macro,			\
long long*:					macro,	


#define GENETICC_REPEAT_POINTER_TYPES_UNSIGNED(macro) \
const unsigned char*:		macro,			\
unsigned char*:				macro,			\
const unsigned int*:		macro,			\
unsigned int*:				macro,			\
const unsigned short*:		macro,			\
unsigned short*:			macro,			\
const unsigned long*:		macro,			\
unsigned long*:				macro,			\
const unsigned long long*:	macro,			\
unsigned long long*:		macro,	

#define GENETICC_REPEAT_POINTER_TYPES_NO_FLOAT(macro) \
const char*:				macro,			\
char*:						macro,			\
const unsigned char*:		macro,			\
unsigned char*:				macro,			\
const signed char*:			macro,			\
signed char*:				macro,			\
const int*:					macro,			\
int*:						macro,			\
const unsigned int*:		macro,			\
unsigned int*:				macro,			\
const short*:				macro,			\
short*:						macro,			\
const unsigned short*:		macro,			\
unsigned short*:			macro,			\
const long*:				macro,			\
long*:						macro,			\
const unsigned long*:		macro,			\
unsigned long*:				macro,			\
const long long*:			macro,			\
long long*:					macro,			\
const unsigned long long*:	macro,			\
unsigned long long*:		macro,			\
_Bool* :					macro,			\
const void*:				macro,			\
void*:						macro,

#define GENETICC_REPEAT_POINTER_TYPES_NO_FLOAT_UNION(macro)	\
const char*:				macro.c,						\
char*:						macro.c,						\
const unsigned char*:		macro.usc,						\
unsigned char*:				macro.usc,						\
const signed char*:			macro.c,						\
signed char*:				macro.c,						\
const int*:					macro.i,						\
int*:						macro.i,						\
const unsigned int*:		macro.ui,						\
unsigned int*:				macro.ui,						\
const short*:				macro.s,						\
short*:						macro.s,						\
const unsigned short*:		macro.us,						\
unsigned short*:			macro.us,						\
const long*:				macro.l,						\
long*:						macro.l,						\
const unsigned long*:		macro.ul,						\
unsigned long*:				macro.ul,						\
const long long*:			macro.ll,						\
long long*:					macro.ll,						\
const unsigned long long*:	macro.ull,						\
unsigned long long*:		macro.ull,						\
_Bool* :					macro.b,		


#define GENETICC_REPEAT_TYPES(macro)		\
const char:					macro,			\
char:						macro,			\
const unsigned char:		macro,			\
unsigned char:				macro,			\
const signed char:			macro,			\
signed char:				macro,			\
const int:					macro,			\
int:						macro,			\
const unsigned int:			macro,			\
unsigned int:				macro,			\
const short:				macro,			\
short:						macro,			\
const unsigned short:		macro,			\
unsigned short:				macro,			\
const long:					macro,			\
long:						macro,			\
const unsigned long:		macro,			\
unsigned long:				macro,			\
const long long:			macro,			\
long long:					macro,			\
const unsigned long long:	macro,			\
unsigned long long:			macro,			\
const float :				macro,			\
float :						macro,			\
const double :				macro,			\
double :					macro,			\
_Bool :						macro,			


#define GENETICC_REPEAT_TYPES_SIGNED(macro) \
const char:					macro,			\
char:						macro,			\
const signed char:			macro,			\
signed char:				macro,			\
const int:					macro,			\
int:						macro,			\
const short:				macro,			\
short:						macro,			\
const long:					macro,			\
long:						macro,			\
const long long:			macro,			\
long long:					macro,


#define GENETICC_REPEAT_TYPES_UNSIGNED(macro) \
const unsigned char:		macro,			\
unsigned char:				macro,			\
const unsigned int:			macro,			\
unsigned int:				macro,			\
const unsigned short:		macro,			\
unsigned short:				macro,			\
const unsigned long:		macro,			\
unsigned long:				macro,			\
const unsigned long long:	macro,			\
unsigned long long:			macro,

#define GENETICC_REPEAT_TYPES_NO_FLOAT(macro) \
const char:					macro,			\
char:						macro,			\
const unsigned char:		macro,			\
unsigned char:				macro,			\
const signed char:			macro,			\
signed char:				macro,			\
const int:					macro,			\
int:						macro,			\
const unsigned int:			macro,			\
unsigned int:				macro,			\
const short:				macro,			\
short:						macro,			\
const unsigned short:		macro,			\
unsigned short:				macro,			\
const long:					macro,			\
long:						macro,			\
const unsigned long:		macro,			\
unsigned long:				macro,			\
const long long:			macro,			\
long long:					macro,			\
const unsigned long long:	macro,			\
unsigned long long:			macro,			\
_Bool :						macro,			

#define GENETICC_REPEAT_TYPES_NO_FLOAT_UNION(macro)	\
const char:					macro.c,						\
char:						macro.c,						\
const unsigned char:		macro.usc,						\
unsigned char:				macro.usc,						\
const signed char:			macro.c,						\
signed char:				macro.c,						\
const int:					macro.i,						\
int:						macro.i,						\
const unsigned int:			macro.ui,						\
unsigned int:				macro.ui,						\
const short:				macro.s,						\
short:						macro.s,						\
const unsigned short:		macro.us,						\
unsigned short:				macro.us,						\
const long:					macro.l,						\
long:						macro.l,						\
const unsigned long:		macro.ul,						\
unsigned long:				macro.ul,						\
const long long:			macro.ll,						\
long long:					macro.ll,						\
const unsigned long long:	macro.ull,						\
unsigned long long:			macro.ull,						\
_Bool :						macro.b,


#endif /* GENETICC_MACRO_TYPE_REPEATER_H_ */

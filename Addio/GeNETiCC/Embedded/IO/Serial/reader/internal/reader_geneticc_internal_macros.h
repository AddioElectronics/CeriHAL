#ifndef READER_GENETICC_INTERNAL_MACROS_H_
#define READER_GENETICC_INTERNAL_MACROS_H_
#if __has_include( "Addio/GeNETiCC/preprocess/geneticc_internal_macros.h")

#include "Addio/Embedded/IO/serial/reader/reader.h"
#include "Addio/GeNETiCC/preprocess/geneticc_internal_macros.h"


#define REPEATER_MACRO_GENETICC_READER_FIND_POINTER(target, length) serial_find(target, length)
#define INTERNAL_READER_FIND(target, length) _Generic((target),						\
GENETICC_REPEAT_TYPES(REPEATER_MACRO_GENETICC_READER_FIND_POINTER(target, length))	\
default:				serial_findChar(target)



#define READER_FIND_2(target, length)										INTERNAL_READER_FIND(target, length)
#define READER_FIND_1(target)												INTERNAL_READER_FIND(target, strlen(target))
#define READER_FIND_MACRO_CHOOSER(...)					\
GET_ARGUMENT_2(__VA_ARGS__,								\
READER_FIND_2,											\
READER_FIND_1, )

#define READER_FIND_UNTIL_4(target, targetLen, terminator, termLen)			serial_findUntil(target, targetLen, terminator, termLen)
#define READER_FIND_UNTIL_3(target, targetLen, terminator)					serial_findUntil(target, targetLen, terminator, 1)
#define READER_FIND_UNTIL_2(target, terminator)								serial_findUntil(target, strlen(target), terminator, 1)
#define READER_FIND_UNTIL_MACRO_CHOOSER(...)			\
GET_ARGUMENT_2(__VA_ARGS__,								\
READER_FIND_UNTIL_4,									\
READER_FIND_UNTIL_3,									\
READER_FIND_UNTIL_2, )


#define READER_READBYTES_2(buffer, length)									serial_readBytes(buffer, length)
#define READER_READBYTES_1(buffer)											serial_readBytes(buffer, sizeof(buffer))
#define READER_READBYTES_MACRO_CHOOSER(...)				\
GET_ARGUMENT_2(__VA_ARGS__,								\
READER_READBYTES_2,										\
READER_READBYTES_1, )

#define READER_READBYTESUNTIL_2(terminator, buffer, length)					serial_readBytesUntil(terminator, buffer, length)
#define READER_READBYTESUNTIL_1(terminator, buffer)							serial_readBytesUntil(terminator, buffer, sizeof(buffer))
#define READER_READBYTESUNTIL_MACRO_CHOOSER(...)		\
GET_ARGUMENT_2(__VA_ARGS__,								\
READER_READBYTES_2,										\
READER_READBYTES_1, )

//#define READER_READSTRING_1(terminator)										serial_readStringUntil(terminator)
//#define READER_READSTRING_0													serial_readString()
//#define READER_READSTRING_MACRO_CHOOSER(...)			\
//GET_ARGUMENT_1(__VA_ARGS__,							\
//READER_READSTRING_1,									\
//READER_READSTRING_0, )

static float dummy()
{
	return -1;
}

#define READER_PARSEINT_2(lookahead, ignore)								serial_parseInt(lookahead, ignore)
#define READER_PARSEINT_1(lookahead)										serial_parseInt(lookahead, NO_IGNORE_CHAR)
//#define READER_PARSEINT_1(DUMMY)											serial_parseInt(SKIP_ALL, NO_IGNORE_CHAR)
#define READER_PARSEINT_MACRO_CHOOSER(...)				\
GET_ARGUMENT_2(__VA_ARGS__,								\
READER_PARSEINT_2,										\
READER_PARSEINT_1, )



//#define READER_PARSEFLOAT_2(lookahead, ignore)								serial_parseFloat(lookahead, ignore)
//#define READER_PARSEFLOAT_1(lookahead)										serial_parseFloat(lookahead, NO_IGNORE_CHAR)
////#define READER_PARSEFLOAT_0													serial_parseFloat(SKIP_ALL, NO_IGNORE_CHAR)
//#define READER_PARSEFLOAT_MACRO_CHOOSER(...)			\
//GET_ARGUMENT_2(__VA_ARGS__,								\
//READER_PARSEFLOAT_2,									\
//READER_PARSEFLOAT_1, )

#define READER_PARSEFLOAT_2(lookahead, ignore)								serial_parseFloat(lookahead, ignore)
#define READER_PARSEFLOAT_1(lookahead)										serial_parseFloat(lookahead, NO_IGNORE_CHAR)
/*#define READER_PARSEFLOAT_0()												serial_parseFloat(SKIP_ALL, NO_IGNORE_CHAR)*/
#define READER_PARSEFLOAT_MACRO_CHOOSER(...)			\
GET_ARGUMENT_2(__VA_ARGS__,								\
READER_PARSEFLOAT_2,									\
READER_PARSEFLOAT_1, )									
//READER_PARSEFLOAT_0, )


#endif
#endif /* READER_GENETICC_INTERNAL_MACROS_H_ */
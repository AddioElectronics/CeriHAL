
#ifndef PRINT_GENETICC_INTERNAL_MACROS_H_
#define PRINT_GENETICC_INTERNAL_MACROS_H_

#include "../../../../../geneticc.h"
#include "print_geneticc_internal_functions.h"


#pragma region Arduino Like Macros

/*
*	Macro used to "overload" print functions, without formatting.
*
*	int/short/long	: Displayed in base 10. To customize the number base, use Printf instead.
*	float/double	: Displays 2 decimal digits. To customize digit count use Printf instead.
*
*	Note : Unlike printf, char* are sent one message at a time (unless message is larger than buffer).
*/
#define INTERNAL_PRINT(x) _Generic((x),												\
const char*: call_print_str((generic_union_t){.u64 = (uint32_t)x}),					\
char*: call_print_str((generic_union_t){.u64 = (uint32_t)x}),						\
const char: print_char(x),															\
const unsigned char: print_char(x),													\
const signed char: print_char(x),													\
char: serial_print_char(x),															\
signed char: serial_printNumber(x, 10),												\
unsigned char: serial_printuNumber(x, 10),											\
int : serial_printNumber(x, 10),													\
unsigned int : printuNumber(x, 10),													\
short : serial_printNumber(x, 10),													\
unsigned short : printuNumber(x, 10),												\
long : serial_printNumber(x, 10),													\
unsigned long : serial_printuNumber(x, 10),											\
float : call_printFloat((generic_union_t)x, 2),										\
double : call_printDouble((generic_union_t)x, 2),									\
_Bool : serial_print_bool(x),														\
default:0)

/*
*	Macro used to "overload" print functions, with formatting.
*	Formatting applied for char pointers, and numbers(int...float).
*
*	***Arguments***
*	char*			: Treated exactly like printf, can take an "infinite" amount of arguments
*	char			: Takes 0 variadic arguments.
*	int/short/long	: Takes 1 variadic argument, the base you want displayed.
*	float/double	: Takes 1 variadic argument, the number of decimal digits you want displayed.
*
*	Note : Unlike printf, char* are sent one message at a time (unless message is larger than buffer).
*/
#define INTERNAL_PRINTF(x, ...) _Generic((x),										\
const char*: call_printf_((generic_union_t){.u64 = (uint32_t)x}, ##__VA_ARGS__),	\
char*: call_printf_((generic_union_t){.u64 = (uint32_t)x}, ##__VA_ARGS__),			\
const char: serial_print_char(x),													\
const unsigned char: serial_print_char(x),											\
const signed char: serial_print_char(x),											\
char: serial_print_char(x),															\
signed char: call_printNumber(x, ##__VA_ARGS__),									\
unsigned char: call_printuNumber(x, ##__VA_ARGS__),									\
int : call_printNumber(x, ##__VA_ARGS__),											\
unsigned int : call_printuNumber(x, ##__VA_ARGS__),									\
short : call_printNumber(x, ##__VA_ARGS__),											\
unsigned short : call_printuNumber(x, ##__VA_ARGS__),								\
long : call_printNumber(x, ##__VA_ARGS__),											\
unsigned long : call_printuNumber(x, ##__VA_ARGS__),								\
float : call_printFloat((generic_union_t)x, ##__VA_ARGS__),							\
double : call_printDouble((generic_union_t)x, ##__VA_ARGS__),						\
_Bool : serial_print_bool(x),														\
default:0)

/*
*	Macro used to "overload" println functions, without formatting.
*	Writes \r\n after each message.
*
*	int/short/long	: Displayed in base 10. To customize the number base, use Printfln instead.
*	float/double	: Displays 2 decimal digits. To customize digit count use Printfln instead.
*
*	Note : Unlike printf, char* are sent one message at a time (unless message is larger than buffer).
*/
#define INTERNAL_PRINTLN(x) _Generic((x),											\
const char*: call_println_str((generic_union_t){.u64 = (uint32_t)x}),				\
char*: call_println_str((generic_union_t){.u64 = (uint32_t)x}),						\
const char: serial_println_char(x),													\
const unsigned char: serial_println_char(x),										\
const signed char: serial_println_char(x),											\
char: serial_println_char(x),														\
signed char: serial_printlnNumber(x, 10),											\
unsigned char: serial_printlnuNumber(x, 10),										\
int : serial_printlnNumber(x, 10),													\
unsigned int : serial_printlnuNumber(x, 10),										\
short : serial_printlnNumber(x, 10),												\
unsigned short : serial_printlnuNumber(x, 10),										\
long : serial_printlnNumber(x, 10),													\
unsigned long : printlnuNumber(x, 10),												\
float : call_printlnFloat((generic_union_t)x, 2),									\
double :call_printlnDouble((generic_union_t)x, 2),									\
_Bool : serial_println_bool(x),														\
default: serial_println())

/*
*	Macro used to "overload" println functions, with formatting.
*	Formatting applied for char pointers, and numbers(int...float).
*
*	***Arguments***
*	char*			: Treated exactly like printf, can take an "infinite" amount of arguments
*	char			: Takes 0 variadic arguments.
*	int/short/long	: Takes 1 variadic argument, the number base you want displayed.
*	float/double	: Takes 1 variadic argument, the number of decimal digits you want displayed.
*
*	Note : Unlike printf, char* are sent one message at a time (unless message is larger than buffer).
*/
#define INTERNAL_PRINTFLN(x, ...) _Generic((x),										\
const char*: call_printfln_((generic_union_t){.u64 = (uint32_t)x}, ##__VA_ARGS__),	\
char*:call_printfln_((generic_union_t){.u64 = (uint32_t)x},  ##__VA_ARGS__),		\
const char: serial_println_char(x),													\
const unsigned char: serial_println_char(x),										\
const signed char: serial_println_char(x),											\
char: serial_println_char(x),														\
signed char: call_printlnNumber(x, ##__VA_ARGS__),									\
unsigned char: call_printlnuNumber(x, ##__VA_ARGS__),								\
int : call_printlnNumber(x, ##__VA_ARGS__),											\
unsigned int : call_printlnuNumber(x, ##__VA_ARGS__),								\
short : call_printlnNumber(x, ##__VA_ARGS__),										\
unsigned short : call_printlnuNumber(x, ##__VA_ARGS__),								\
long : call_printlnNumber(x, ##__VA_ARGS__),										\
unsigned long : call_printlnuNumber(x, ##__VA_ARGS__),								\
float : call_printlnFloat((generic_union_t)x, ##__VA_ARGS__),						\
double : call_printlnDouble((generic_union_t)x, ##__VA_ARGS__),						\
_Bool : serial_println_bool(x),														\
default:serial_println())

#pragma endregion Arduino Like Macros


#pragma region GeNETiCC Internal Macros
/*
*	These macros require the full GeNETiCC library, or at the very least "geneticc.h."
*/
#if __has_include( "../../../../../preprocess/geneticc_internal_macros.h")

#include  "../../../../../preprocess/geneticc_internal_macros.h"

//#define REPEATER_MACRO_GENETICC_SERIAL_WRITE_POINTER(b, length)			write(b, length == 0 ? sizeof(b) : length)
//#define INTERNAL_SERIAL_WRITE(b, length) _Generic((b),							\
//GENETICC_REPEAT_TYPES(REPEATER_MACRO_GENETICC_SERIAL_WRITE_POINTER(b, length))	\
//default:				write_byte(b)

#define SERIAL_WRITE_2(b, size)												serial_write(b, size)
#define SERIAL_WRITE_1(b)													serial_write_byte(b)
#define SERIAL_WRITE_MACRO_CHOOSER(...)					\
GET_ARGUMENT_2(__VA_ARGS__,								\
SERIAL_WRITE_2,											\
SERIAL_WRITE_1, )






/*
*	Prints an array of bytes in the specified base.
*
*	/param	*data				Pointer to starting memory address.
*	/param	input_length		The amount of characters to display.
*	/param	base				(Default = 16)The base to display each byte as.
*	/param	separator			(Default = '\0')The character used to separate each byte.
*
*	/returns	size_t			How many bytes were transmitted.
*/
#define INTERNAL_PRINT_DATA_BASE(data, length, base, separator) \
serial_print_data_base_sep(data, length, base, separator);

#define INTERNAL_PRINT_DATA_BASE_4(data, length, base, separator)				INTERNAL_PRINT_DATA_BASE(data, length, base, separator)
#define INTERNAL_PRINT_DATA_BASE_3(data, length, base)							INTERNAL_PRINT_DATA_BASE(data, length, base, '\0')
#define INTERNAL_PRINT_DATA_BASE_2(data, length)								INTERNAL_PRINT_DATA_BASE(data, length, 16, '\0')
#define INTERNAL_PRINT_DATA_BASE_MACRO_CHOOSER(...)			\
GET_ARGUMENT_4(__VA_ARGS__,									\
INTERNAL_PRINT_DATA_BASE_4,									\
INTERNAL_PRINT_DATA_BASE_3,									\
INTERNAL_PRINT_DATA_BASE_2, )

/*
*	Prints an array of bytes in the specified base, as multiple lines.
*
*	/param	*data				Pointer to starting memory address.
*	/param	length				The amount of characters to display.
*	/param	line_length			(Default = 32)The amount of characters displayed on each line.
*	/param	base				(Default = 16)The base to display each byte as.
*	/param	separator			(Default = '\0')The character used to separate each byte.
*
*	/returns	size_t			How many bytes were transmitted.
*/
#define INTERNAL_PRINTLN_DATA_BASE(data, length, line_length, base, separator) \
serial_println_data_base_sep(data, length, base, line_length, separator);

#define INTERNAL_PRINTLN_DATA_BASE_5(data, length, line_length, base, separator)	INTERNAL_PRINTLN_DATA_BASE(data, length, line_length, base, separator)
#define INTERNAL_PRINTLN_DATA_BASE_4(data, length, line_length, base)				INTERNAL_PRINTLN_DATA_BASE(data, length, line_length, base, '\0')
#define INTERNAL_PRINTLN_DATA_BASE_3(data, length, line_length)						INTERNAL_PRINTLN_DATA_BASE(data, length, line_length, base, '\0')
#define INTERNAL_PRINTLN_DATA_BASE_2(data, length)									INTERNAL_PRINTLN_DATA_BASE(data, length, 32, 16, '\0')
#define INTERNAL_PRINTLN_DATA_BASE_1(data)											INTERNAL_PRINTLN_DATA_BASE(data, sizeof(data), 32, 16, '\0')
#define INTERNAL_PRINTLN_DATA_BASE_MACRO_CHOOSER(...)			\
GET_ARGUMENT_5(__VA_ARGS__,										\
INTERNAL_PRINTLN_DATA_BASE_5,									\
INTERNAL_PRINTLN_DATA_BASE_4,									\
INTERNAL_PRINTLN_DATA_BASE_3,									\
INTERNAL_PRINTLN_DATA_BASE_2,									\
INTERNAL_PRINTLN_DATA_BASE_1, )


/*
*	Prints a section of memory, displayed like a hex editor.
*
*	/param	*data				Pointer to starting memory address.
*	/param	length				(Optional)The amount of characters to display.							*Required if data is not a static array.
*	/param	line_length			(Default = 8)The amount of bytes displayed per line.
*	/param	labels				(Default = true)Should the header labels be displayed at the top?
*	/param	print_text			(Default = true)Should a text representation of the data be displayed?
*
*	/returns	size_t			How many bytes were transmitted.
*/
#define INTERNAL_PRINTLN_DATA_HEX_EDITOR(data, length, line_length, labels, print_text) \
serial_print_data_hex_addr(data, length, line_length, labels, print_text);

#define INTERNAL_PRINTLN_DATA_HEX_EDITOR_5(data, length, line_length, labels, print_text)	INTERNAL_PRINTLN_DATA_HEX_EDITOR(data, length, line_length, labels, print_text)
#define INTERNAL_PRINTLN_DATA_HEX_EDITOR_4(data, length, line_length, labels)				INTERNAL_PRINTLN_DATA_HEX_EDITOR(data, length, line_length, labels)
#define INTERNAL_PRINTLN_DATA_HEX_EDITOR_3(data, length, line_length)						INTERNAL_PRINTLN_DATA_HEX_EDITOR(data, length, line_length, true, true)
#define INTERNAL_PRINTLN_DATA_HEX_EDITOR_2(data, length)									INTERNAL_PRINTLN_DATA_HEX_EDITOR(data, length, 16, true, true)
#define INTERNAL_PRINTLN_DATA_HEX_EDITOR_1(data)											INTERNAL_PRINTLN_DATA_HEX_EDITOR(data, sizeof(data),  16, true, true)
#define INTERNAL_PRINTLN_DATA_HEX_EDITOR_MACRO_CHOOSER(...)			\
GET_ARGUMENT_5(__VA_ARGS__,											\
INTERNAL_PRINTLN_DATA_HEX_EDITOR_5,									\
INTERNAL_PRINTLN_DATA_HEX_EDITOR_4,									\
INTERNAL_PRINTLN_DATA_HEX_EDITOR_3,									\
INTERNAL_PRINTLN_DATA_HEX_EDITOR_2,									\
INTERNAL_PRINTLN_DATA_HEX_EDITOR_1, )

#endif

#pragma endregion GeNETiCC Internal Macros

#endif /* PRINT_GENETICC_INTERNAL_MACROS_H_ */

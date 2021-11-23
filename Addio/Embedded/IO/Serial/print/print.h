#ifndef PRINT_H_
#define PRINT_H_

/*
*	Addio Embedded Serial and either hal_io or Addio Embedded IO "library" required.
*/
#if (__has_include("hal_io.h") || __has_include("../../addio_io.h"))/* && __has_include("../serial.h"))*/

#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>
#include <math.h>
#include <stdio.h>

#include "print_config.h"

#include "../../../../Universal/Standard/Cstring/cstring.h"


#pragma region Functions


size_t serial_availableForWrite();


size_t serial_write_byte(uint8_t b);
size_t serial_write(const char *buffer, size_t size);

size_t serial_printf(const char* format, ...);
size_t serial_vprintf(const char* format, va_list ap);
size_t serial_print_str(const char* str);
inline size_t serial_print_string(string_t* string);
inline size_t serial_print_char(const char c);
size_t serial_print_bool(const bool b);



inline size_t serial_print_data_base(const unsigned char *data, size_t input_length, uint8_t base);
size_t serial_print_data_base_sep(const unsigned char *data, size_t input_length, uint8_t base, char separator);
size_t serial_print_data_base64(const unsigned char *data, size_t input_length);
size_t serial_print_data_base64_sep(const unsigned char *data, size_t input_length, char separator);

inline size_t serial_println(void);
size_t serial_printlnf(const char* format, ...);
size_t serial_vprintlnf(const char* format, va_list ap);
size_t serial_println_str(const char* str);
size_t serial_println_string(string_t* string);
size_t serial_println_char(const char c);
size_t serial_println_bool(const bool b);



inline size_t serial_println_data_base(const unsigned char *data, size_t input_length, uint8_t base, uint8_t line_length);
size_t serial_println_data_base_sep(const unsigned char *data, size_t input_length, uint8_t base, uint8_t line_length, char separator);
inline size_t serial_println_data_base64(const unsigned char *data, size_t input_length, uint8_t line_length);
size_t serial_println_data_base64_sep(const unsigned char *data, size_t input_length, uint8_t line_length, char separator);

size_t serial_printNumber(long n, uint8_t base);
size_t serial_printuNumber(unsigned long n, uint8_t base);
inline size_t serial_printlnNumber(long n, uint8_t base);
inline size_t serial_printlnuNumber(unsigned long n, uint8_t base);

size_t serial_printNumberPad(long n, uint8_t base, uint8_t pad);
size_t serial_printuNumberPad(unsigned long n, uint8_t base, uint8_t pad);
inline size_t serial_printlnNumberPad(long n, uint8_t base, uint8_t pad);
inline size_t serial_printlnuNumberPad(unsigned long n, uint8_t base, uint8_t pad);

size_t serial_printFloat(double number, uint8_t digits);
inline size_t serial_printlnFloat(double number, uint8_t digits);

size_t serial_print_data_hex_addr(const unsigned char *data, size_t input_length, uint8_t line_length, bool labels, bool print_text);

#pragma endregion Functions


#pragma region printf Macros
/*
*	These macros use the standard printf function, and are sent 1 character at a time.
*/


#define print_dec_format(type) _Generic((type),		\
char: "%c",											\
signed char: "%hhd",								\
unsigned char: "%hhu",								\
signed short: "%hd",								\
unsigned short: "%hu",								\
signed int: "%d",									\
unsigned int: "%u",									\
long int: "%ld",									\
unsigned long int: "%lu",							\
long long int: "%lld",								\
unsigned long long int: "%llu",						\
float: "%f",										\
double: "%f",										\
long double: "%Lf",									\
char *: "%s",										\
void *: "%p",										\
const char*: "%s")

#define print(x) printf(print_dec_format(x), x)
#define println(x) printf(print_dec_format(x), x), printf(NEWLINE);

#define printfln(x, ...) printf(x, ##__VA_ARGS__), printf(NEWLINE);

#pragma endregion printf Macros

#else
#warning Unsupported
#endif
#endif /* PRINT_H_ */
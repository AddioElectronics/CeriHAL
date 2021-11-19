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


#pragma region Functions


size_t serial_availableForWrite();


size_t write_byte(uint8_t b);
size_t write(const char *buffer, size_t size);

size_t printf_(const char* format, ...);
size_t vprintf_(const char* format, va_list ap);
size_t print_str(const char* str);
inline size_t print_char(const char c);
size_t print_bool(const bool b);

inline size_t print_data_base(const unsigned char *data, size_t input_length, uint8_t base);
size_t print_data_base_sep(const unsigned char *data, size_t input_length, uint8_t base, char separator);
size_t print_data_base64(const unsigned char *data, size_t input_length);
size_t print_data_base64_sep(const unsigned char *data, size_t input_length, char separator);

size_t println_(void);
size_t printlnf_(const char* format, ...);
inline size_t vprintlnf_(const char* format, va_list ap);
size_t println_str(const char* str);
inline size_t println_char(const char c);
inline size_t println_bool(const bool b);

inline size_t println_data_base(const unsigned char *data, size_t input_length, uint8_t base, uint8_t line_length);
size_t println_data_base_sep(const unsigned char *data, size_t input_length, uint8_t base, uint8_t line_length, char separator);
inline size_t println_data_base64(const unsigned char *data, size_t input_length, uint8_t line_length);
size_t println_data_base64_sep(const unsigned char *data, size_t input_length, uint8_t line_length, char separator);

size_t printNumber(long n, uint8_t base);
size_t printuNumber(unsigned long n, uint8_t base);
inline size_t printlnNumber(long n, uint8_t base);
inline size_t printlnuNumber(unsigned long n, uint8_t base);

size_t printNumberPad(long n, uint8_t base, uint8_t pad);
size_t printuNumberPad(unsigned long n, uint8_t base, uint8_t pad);
inline size_t printlnNumberPad(long n, uint8_t base, uint8_t pad);
inline size_t printlnuNumberPad(unsigned long n, uint8_t base, uint8_t pad);

size_t printFloat(double number, uint8_t digits);
inline size_t printlnFloat(double number, uint8_t digits);

size_t print_data_hex_addr(const unsigned char *data, size_t input_length, uint8_t line_length, bool labels, bool print_text);

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
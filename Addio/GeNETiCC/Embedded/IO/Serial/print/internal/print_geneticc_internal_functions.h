#ifndef PRINT_GENETICC_INTERNAL_FUNCTIONS_H_
#define PRINT_GENETICC_INTERNAL_FUNCTIONS_H_


#include "../../../../../../Embedded/IO/serial/print/print.h"


static size_t call_printNumber(long n, ...)
{
	va_list ap;
	va_start(ap, n);
	size_t size;
	uint8_t base = va_arg(ap,uint32_t);
	size = serial_printNumber(n, base);
	va_end(ap);
	return size;
}

static size_t call_printlnNumber(long n, ...)
{
	va_list ap;
	va_start(ap, n);
	size_t size;
	uint8_t base = va_arg(ap,uint32_t);
	size = serial_printlnNumber(n, base);
	va_end(ap);
	return size;
}

static size_t call_printuNumber(unsigned long n, ...)
{
	va_list ap;
	va_start(ap, n);
	size_t size;
	uint8_t base = va_arg(ap,uint32_t);
	size = serial_printuNumber(n, base);
	va_end(ap);
	return size;
}

static size_t call_printlnuNumber(unsigned long n, ...)
{
	va_list ap;
	va_start(ap, n);
	size_t size;
	uint8_t base = va_arg(ap,uint32_t);
	size = serial_printlnuNumber(n, base);
	va_end(ap);
	return size;
}





static size_t call_printFloat(generic_union_t number, ...)
{
	va_list ap;
	va_start(ap, number);
	size_t size;
	uint8_t digits = va_arg(ap,uint32_t);
	size = serial_printFloat((double)number.f, digits);
	va_end(ap);
	return size;
}

static size_t call_printlnFloat(generic_union_t number, ...)
{
	va_list ap;
	va_start(ap, &number);
	size_t size;
	uint8_t digits = va_arg(ap, uint32_t);
	size = serial_printFloat((double)number.f, digits);
	size += serial_println();
	va_end(ap);
	return size;
}

static size_t call_printDouble(generic_union_t number, ...)
{
	va_list ap;
	va_start(ap, number);
	size_t size;
	uint8_t digits = va_arg(ap,uint32_t);
	size = serial_printFloat(number.d, digits);
	size += serial_println();
	va_end(ap);
	return size;
}

static size_t call_printlnDouble(generic_union_t number, ...)
{
	va_list ap;
	va_start(ap, &number);
	size_t size;
	uint8_t digits = va_arg(ap, uint32_t);
	size = serial_printlnFloat(number.d, digits);
	va_end(ap);
	return size;
}

static size_t call_print_str(generic_union_t arr)
{
	return serial_print_str(arr.cp);
}


static size_t call_println_str(generic_union_t arr)
{
	return serial_println_str(arr.cp);
}

static size_t call_printf_(generic_union_t arr, ...)
{
	va_list ap;
	va_start(ap, arr);
	size_t size;
	size = serial_vprintf(arr.cp, ap);
	va_end(ap);
	return size;
	#warning need to add vprintf_
}


static size_t call_printfln_(generic_union_t arr, ...)
{
	va_list ap;
	va_start(ap, arr);
	size_t size;
	size = serial_vprintlnf(arr.cp, ap);
	va_end(ap);
	return size;
}


#endif /* PRINT_GENETICC_INTERNAL_FUNCTIONS_H_ */
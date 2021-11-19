#include "print.h"

#include <stdlib.h>
#include <utils_assert.h>

#include "../../../Time/timing/timing.h"

#include "../serial_defs.h"

#include "../../../../Universal/codecs/base64.h"
#include "internal/print_internal_functions.h"


#if __has_include("hal_io.h")
#include <hal_io.h>
extern struct io_descriptor* serial_io;
#elif __has_include("addio_io.h")
#include <addio_io.h>
extern struct io_descriptor* serial_io;
#else
#error unsupported
#endif


/*
*	What printf function should the internal functions use?
*	*printf_	Formats the string, and sends all at once.
*				Depending on FORMAT_ALLOCATE_MODE, end of string may be lost.
*	*printf		Standard printf function, sends characters 1 at a time.
*				Whole string will always be sent.
*/
#define INTERNAL_PRINTF_FUNC(x, ...) serial_printf(x, ##__VA_ARGS__) //printf_(x, ##__VA_ARGS__)


extern unsigned long serial_timeout;

/*
*	These functions require addio_io.h, and are incompatible with hal_io.h
*/
#if __has_include("../../addio_io.h")
size_t serial_availableForWrite()
{
	if(serial_io->txReady != NULL)
	return serial_io->txReady(serial_io);
	else
	return true; //If txReady is null, the write function should be handling this internally.
}
#endif

unsigned long previous_write_timestamp;

size_t serial_write_byte(uint8_t b)
{
	ASSERT(serial_io);

	//unsigned long start_millis;
//
	//if(serial_io->flags.tx_check_previous_for_completion)
	//{
		//if(serial_io->txReady != NULL)
		//{
			//start_millis = millis();
			////If txReady is not null,
			////the "io_descriptor->write" function does not wait internally,
			////data will be overwritten if we do not wait.
			////If that is not the case, someone didn't do their job.
			//while(!serial_io->txReady(serial_io))
			//{
				//if(check_timeout(serial_timeout, start_millis))
				//{
					//return 0;
				//}
			//}
		//}
	//}
	
	if(serial_io->flags.print_quick)
	return serial_io->write(serial_io, (&b), 1);
	 
	 size_t succesful = io_write(serial_io, (&b), 1);
	 //last_write = millis();

	//if(serial_io->flags.tx_wait_for_complete)
	//{
		//if(serial_io->txReady != NULL)
		//{
			//start_millis = millis();
			////This "io_descriptor->write" function does not wait internally,
			////data will be overwritten if we do not wait.
			//while(!serial_io->txReady(serial_io))
			//{
				//if(check_timeout(serial_timeout, start_millis))
				//{
					////Timed out
					//return 0;
				//}
			//}
		//}
	//}
	
	return succesful;
	 
}

size_t serial_write(const char *buffer, size_t size) 
{
	ASSERT(serial_io);

	//unsigned long start_millis;
//
	//if(serial_io->flags.tx_check_previous_for_completion)
	//{
		//if(serial_io->txReady != NULL)
		//{
			//start_millis = millis();
			////If txReady is not null,
			////the "io_descriptor->write" function does not wait internally,
			////data will be overwritten if we do not wait.
			////If that is not the case, someone didn't do their job.
			//while(!serial_io->txReady(serial_io))
			//{
				//if(check_timeout(serial_timeout, start_millis))
				//{
					//return 0;
				//}
			//}
		//}
	//}
	
	if(serial_io->flags.print_quick)
	return serial_io->write(serial_io, buffer, size);

	size_t succesful = io_write(serial_io, buffer, size);
	
	previous_write_timestamp = millis();
	 
	//if(serial_io->flags.tx_wait_for_complete)
	//{
		//if(serial_io->txReady != NULL)
		//{
			//start_millis = millis();
			////This "io_descriptor->write" function does not wait internally,
			////data will be overwritten if we do not wait.
			//while(!serial_io->txReady(serial_io))
			//{
				//if(check_timeout(serial_timeout, start_millis))
				//{
					////Timed out
					//return 0;
				//}
			//}
		 //}
	//}
	  
	 return succesful;
}
 
 #pragma region Print Functions

 
size_t serial_printf(const char* format, ...)
{
	#warning need to take modes into account
	va_list ap;
	va_start(ap, format);
	size_t total_sent = serial_vprintf(format, ap);
	va_end(ap);
	return total_sent;
}
  
  
  
size_t serial_vprintf(const char* format, va_list ap)
{
	size_t strsize = 0;
	size_t total_sent = 0;
	char format_buffer[PRINT_FORMAT_BUFFER_SIZE];
	
	
	//Get total size of formatted string.
	strsize = vsnprintf(NULL, 0, format, ap);	
		
	//Get size of data block.
	uint16_t block_size = strsize < PRINT_FORMAT_BUFFER_SIZE ? strsize : PRINT_FORMAT_BUFFER_SIZE;	
	
	//Send formatted string off in blocks.
	for(int i = 0; i < strsize; i += PRINT_FORMAT_BUFFER_SIZE)
	{
		total_sent += vsnprintf(format_buffer, block_size + 1, format + i, ap);
		serial_write(format_buffer, block_size);
	}
	
	return total_sent;
}
  
size_t  serial_print_str(const char* str)
{
	size_t s = strlen(str);
	serial_write(str, s);
	return s;
}

size_t __attribute__((__always_inline__)) serial_print_char(const char c)
{
	return serial_write(&c, 1);
}

size_t serial_print_bool(const bool b)
{
	if(b)
	{
		return serial_print_str("true");
	}
	else
	{
		return serial_print_str("false");
	}
}



#pragma endregion Print Functions

#pragma region Print Line Functions

char format_specifier_end[10] = {'c', 'd', 'e', 'f', 'i', 'o', 's', 'u', 'x', '%'};


size_t serial_printlnf(const char* format, ...)
{
	va_list ap;
	va_start(ap, format);
	size_t total_sent = serial_printf(format, ap);
	va_end(ap);
	total_sent += serial_println();
	return total_sent;
}

size_t __attribute__((__always_inline__)) serial_vprintlnf(const char* str, va_list ap)
{
	size_t total_sent = serial_vprintf(str, ap);
	total_sent += serial_println();
	return total_sent;
}


size_t serial_println()
{
	return serial_print_str(NEWLINE);
	//#if NEWLINE_CHAR == '\n'
	//return print_char(NEWLINE_CHAR);
	//#else
	//return print_str("\n\r");
	//#endif
}

size_t serial_println_str(const char* str)
{
	size_t s = strlen(str);
	serial_write(str, s);
	s += serial_println();
	return s;
}

size_t __attribute__((__always_inline__)) serial_println_char(const char c)
{
	size_t s = serial_write_byte((uint8_t)c);
	s += serial_println();
	return s;
}

size_t __attribute__((__always_inline__)) serial_println_bool(const bool b)
{
	size_t size = serial_print_bool(b);
	size += serial_println();
	return size;
}


#pragma endregion Print Line Functions

#pragma region Print Number Functions



size_t serial_printNumber(long n, uint8_t base)
{
	if (base == 0) 
	{
		return serial_write_byte(n);
	} 
	else if (base == 10) 
	{
		if (n < 0) 
		{
			int t = serial_print_char((char)'-');
			n = -n;
			return serial_printuNumber(n, 10) + t;
		}
		return serial_printuNumber(n, 10);
	} 
	else 
	{
		return serial_printuNumber(n, base);
	}
}


size_t serial_printuNumber(unsigned long n, uint8_t base)
{
	char buf[8 * sizeof(long) + 1]; // Assumes 8-bit chars plus zero byte.
	char *str = &buf[sizeof(buf) - 1];

	*str = '\0';

	// prevent crash if called with base == 1
	if (base < 2) base = 10;

	do {
		char c = n % base;
		n /= base;

		*--str = c < 10 ? c + '0' : c + 'A' - 10;
	} while(n);

	return serial_print_str(str);
}

size_t __attribute__((__always_inline__)) serial_printlnNumber(long n, uint8_t base)
{
	size_t size = serial_printNumber(n, base);	
	size += serial_println();
	return size;
}


size_t __attribute__((__always_inline__)) serial_printlnuNumber(unsigned long n, uint8_t base)
{
	size_t size = serial_printuNumber(n, base);
	size += serial_println();
	return size;
}

size_t serial_printNumberPad(long n, uint8_t base, uint8_t pad)
{
	if (base == 0)
	{
		return serial_write_byte(n);
	}
	else if (base == 10)
	{
		if (n < 0)
		{
			int t = serial_print_char((char)'-');
			n = -n;
			return serial_printuNumberPad(n, 10, pad) + t;
		}
		return serial_printuNumberPad(n, 10, pad);
	}
	else
	{
		return serial_printuNumberPad(n, base, pad);
	}
}


size_t serial_printuNumberPad(unsigned long n, uint8_t base, uint8_t pad)
{
	char buf[8 * sizeof(long) + 1]; // Assumes 8-bit chars plus zero byte.
	char *str = &buf[sizeof(buf) - 1];

	*str = '\0';

	// prevent crash if called with base == 1
	if (base < 2) base = 10;

	do {
		char c = n % base;
		n /= base;

		*--str = c < 10 ? c + '0' : c + 'A' - 10;
	} while(n);

	char format [5] = {'%', '0', pad + 48, 's', '\0' };
	return INTERNAL_PRINTF_FUNC(format, str);
}

size_t __attribute__((__always_inline__)) serial_printlnNumberPad(long n, uint8_t base, uint8_t pad)
{
	size_t size = serial_printNumberPad(n, base, pad);
	size += serial_println();
	return size;
}


size_t __attribute__((__always_inline__)) serial_printlnuNumberPad(unsigned long n, uint8_t base, uint8_t pad)
{
	size_t size = serial_printuNumberPad(n, base, pad);
	size += serial_println();
	return size;
}



size_t serial_printFloat(double number, uint8_t digits)
{
	size_t n = 0;
	
	if (isnan(number)) return serial_print_str("nan");
	if (isinf(number)) return serial_print_str("inf");
	if (number > 4294967040.0) return serial_print_str ("ovf");  // constant determined empirically
	if (number <-4294967040.0) return serial_print_str ("ovf");  // constant determined empirically
	
	// Handle negative numbers
	if (number < 0.0)
	{
		n += serial_print_char((char)'-');
		number = -number;
	}

	// Round correctly so that print(1.999, 2) prints as "2.00"
	double rounding = 0.5;
	for (uint8_t i=0; i<digits; ++i)
	rounding /= 10.0;
	
	number += rounding;

	// Extract the integer part of the number and print it
	unsigned long int_part = (unsigned long)number;
	double remainder = number - (double)int_part;
	n += serial_printuNumber(int_part, 10);

	// Print the decimal point, but only if there are digits beyond
	if (digits > 0) {
		n += serial_print_char((char)'.');
	}

	// Extract digits from the remainder one at a time
	while (digits-- > 0)
	{
		remainder *= 10.0;
		unsigned int toPrint = (unsigned int)(remainder);
		n += serial_printuNumber(toPrint, 10);
		remainder -= toPrint;
	}
	
	return n;
}

size_t __attribute__((__always_inline__)) serial_printlnFloat(double number, uint8_t digits)
{
	size_t size = serial_printFloat(number, digits);
	size += serial_println();
	return size;
}





size_t __attribute__((__always_inline__)) serial_print_data_base(const unsigned char *data, size_t input_length, uint8_t base)
{
	return serial_print_data_base_sep(data, input_length, base, '\0');
}

size_t serial_print_data_base_sep(const unsigned char *data, size_t input_length, uint8_t base, char separator)
{

	switch(base)
	{
		case 2:
		case 8:
		case 10:
		case 16:
		break;
		case 64:
		return serial_print_data_base64_sep(data, input_length, separator );
		default: 
		return 0;
	}
	
	size_t total_sent = 0;
	uint8_t padding = internal_get_base_padding(base);
	
	for(int i = 0; i < input_length; i++)
	{
		total_sent += serial_printuNumberPad(data[i], base, padding);
		
		if(separator != '\0')
		{
			total_sent += serial_print_char(separator);
		}
	}
	return total_sent;
}


size_t __attribute__((__always_inline__)) serial_println_data_base(const unsigned char *data, size_t input_length, uint8_t base, uint8_t line_length )
{
	return serial_println_data_base_sep(data, input_length, line_length, base, '\0');
}

size_t serial_println_data_base_sep(const unsigned char *data, size_t input_length, uint8_t base, uint8_t line_length, char separator)
{
	switch(base)
	{
		case 2:
		case 8:
		case 10:
		case 16:
		break;
		case 64:
		return serial_println_data_base64_sep(data, input_length, line_length, separator );
		default:
		return 0;
	}
	
	size_t total_sent = 0;
	uint8_t padding = internal_get_base_padding(base);
	
	for(int i = 0; i < input_length; i += line_length)
	{
		uint8_t current_line_length = input_length - i;
		
		if(current_line_length > line_length)
			current_line_length = line_length;
		
		for(int b = 0; b < current_line_length; b++)
		{
			total_sent += serial_printuNumberPad(data[b + i], base, padding);
			
			if(separator != '\0')
			{
				total_sent += serial_print_char(separator);
			}
		}
		
		total_sent += serial_println();
	}
	
	
	return total_sent;
}


size_t serial_print_data_base64_sep(const unsigned char *data, size_t input_length, char separator)
{
	
	size_t total_sent = 0;

	for(int a = 0; a < input_length; a += PRINT_BASE64_TRUE_CHUNK_SIZE)
	{
		size_t output_length;
		
		//Make sure we don't send more than the input_length.
		uint8_t current_chunk_size = input_length - a;		
		if(current_chunk_size > PRINT_BASE64_TRUE_CHUNK_SIZE)
			current_chunk_size = PRINT_BASE64_TRUE_CHUNK_SIZE;
		
		char* encoded_data = base64_encode(data + a, current_chunk_size, &output_length);
	
		if(separator != '\0')
		{
			for(int i = 0; i < output_length; i += 4)
			{
				//Total sent should always be divisible by 4, as padding is added.
				total_sent += serial_write(encoded_data + i, 4);			
				total_sent += serial_print_char(separator);	
			}
		}
		else
		{
			total_sent = serial_write(encoded_data, output_length);		
		}
		
		free(encoded_data);
	}
	
	return total_sent;
}

size_t __attribute__((__always_inline__)) serial_print_data_base64(const unsigned char *data, size_t input_length)
{
	return serial_print_data_base64_sep(data, input_length, '\0');
}

size_t serial_println_data_base64_sep(const unsigned char *data, size_t input_length, uint8_t line_length, char separator)
{
	size_t total_sent = 0;
	
	for(int a = 0; a < input_length; a += PRINT_BASE64_TRUE_CHUNK_SIZE)
	{
		size_t output_length;
		
		//Make sure we don't send more than the input_length.
		uint8_t current_chunk_size = input_length - a;
		if(current_chunk_size > PRINT_BASE64_TRUE_CHUNK_SIZE)
			current_chunk_size = PRINT_BASE64_TRUE_CHUNK_SIZE;
				
		char* encoded_data = base64_encode(data + a, current_chunk_size, &output_length);
	
		if(separator != '\0')
		{
			//Make sure line length is divisible by 4.
			#ifdef PRINT_UNALIGNED_DATA_INCREASE_LINE_LENGTH
			line_length += (line_length % 4);
			#else
			line_length -= (line_length % 4);
			#endif
		}
	
		for(int i = 0; i < output_length; i += line_length)
		{
			uint8_t current_line_length = output_length - i;
		
			if(current_line_length > line_length)
				current_line_length = line_length;
		
			if(separator != '\0')
			{
				for(int b = 0; b < line_length; b += 4)
				{
					//Total sent should always be divisible by 4, as padding is added.
					total_sent += serial_write(encoded_data + i + b, 4);
					total_sent += serial_print_char(separator);
				}
			}
			else
			{
				total_sent += serial_write(encoded_data + i, line_length);			
			}
		
			total_sent += serial_println();			
		}
		free(encoded_data);		
	}
	return total_sent;
}

size_t __attribute__((__always_inline__)) serial_println_data_base64(const unsigned char *data, size_t input_length, uint8_t line_length)
{
	return serial_println_data_base64_sep(data, input_length, line_length, '\0');
}


/*
*	Displays memory like a HEX editor.
*
*	/Param	data			The starting address.
*	/Param	input_length	How many bytes to display
*	/Param	line_length		How many bytes to display per line.
*	/Param	labels			Should a header be displayed
*	/Param	print_text		Should the bytes be displayed as text on the far right column(s)
*/
size_t serial_print_data_hex_addr(const unsigned char *data, size_t input_length, uint8_t line_length, bool labels, bool print_text)
{
	
	size_t total_sent = 0;
	
	//Make sure line length is divisible by 2.
	#ifdef PRINT_UNALIGNED_DATA_INCREASE_LINE_LENGTH
	line_length += (line_length % 2);
	#else
	line_length -= (line_length % 2);
	#endif
	
	
	//Print header labels
	if(labels)
	{
		
		
		//Add padding
		total_sent +=  serial_println();
		
		
		
		//Label above the address
		total_sent += INTERNAL_PRINTF_FUNC("%-10s%-4", "Offset");
		
		uint8_t base_addr = *data & 0xff;
		
		
		
		//Label for each column
		for(uint8_t a = base_addr; a < line_length + base_addr; a++)
		{
			total_sent += INTERNAL_PRINTF_FUNC("%02X", a);
			
			if(a != line_length - 1)
			total_sent += serial_print_char(' ');
		}
		
		
		//Label for decoded text.
		total_sent += serial_print_str("   ");
		total_sent += serial_println_str("Decoded Text");
		
		total_sent +=  serial_println();		
		
	}
	
	for(int i = 0; i < input_length; i++)
	{
		uint8_t m = i % line_length;	
		
			
		//Start of line
		if(m == 0)	
		{
			//Print address
			total_sent += INTERNAL_PRINTF_FUNC("0x%8X%-4", data + i);
		}
		
		//Print data as hex
		total_sent += INTERNAL_PRINTF_FUNC("%02X", data[i]);
		
		//End of line
		if(line_length - m == 1 || i == input_length - 1)
		{
			//Print data as text
			if(print_text)
			{
				total_sent += serial_print_str("    ");
				
				//Make sure we aren't printing past the last index.
				int current_line_length = input_length - (i + 1 - line_length);
				if(current_line_length > line_length)
					current_line_length = line_length;
				
				
				//Instead of writing all at once, we want to print 0x00 as '.'
				for(uint8_t s = (i+1) - current_line_length; s <= i; s++)
				{
					if(data[s] == 0 || data[s] == '\t')
						total_sent += serial_print_char('.');
					else
						total_sent += serial_print_char(data[s]);
				}

				
			}
			total_sent += serial_println();	
		}
		else
		{
			//Separate data with a space.
			total_sent += serial_print_char(' ');
		}

	}

	//Add bottom padding.
	total_sent +=  serial_println();
	
	return total_sent;
}

#pragma endregion Print Number Functions

#ifndef PRINT_GENETICC_H_
#define PRINT_GENETICC_H_

/*
*	Addio Embedded Print library is required.
*/
#if __has_include("../../../../../Embedded/IO/serial/print/print.h")


#include "internal/print_geneticc_internal_macros.h"


#pragma region Arduino Like Macros

/*
*	These macros require addio_io.h, and are incompatible with hal_io.h
*/
#if __has_include("../../../../../Embedded/io/serial/addio_io.h")
#define AvailableForWrite serial_availableForWrite(false)
#endif
/*
*	Macro used to "overload" print functions, without formatting.
*
*	int/short/long	: Displayed in base 10. To customize the number base, use Printf instead.
*	float/double	: Displays 2 decimal digits. To customize digit count use Printf instead.
*
*	Note : Unlike printf, char* are sent one message at a time (unless message is larger than buffer).
*/
#define Print(x) INTERNAL_PRINT(x)

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
#define Printf(x, ...) INTERNAL_PRINTF(x, ##__VA_ARGS__)

/*
*	Macro used to "overload" println functions, without formatting.
*	Writes \r\n after each message.
*
*	int/short/long	: Displayed in base 10. To customize the number base, use Printfln instead.
*	float/double	: Displays 2 decimal digits. To customize digit count use Printfln instead.
*
*	Note : Unlike printf, char* are sent one message at a time (unless message is larger than buffer).
*/
#define Println(x) INTERNAL_PRINTLN(x)

/*
*	Macro used to "overload" println functions, with formatting.
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
#define Printfln(x, ...) INTERNAL_PRINTFLN(x, ##__VA_ARGS__)

#pragma endregion Arduino Like Macros


#pragma region GeNETiCC Macros
/*
*	These macros require the full GeNETiCC library, or at the very least "geneticc.h."
*/



/*
*	Writes a byte, or array of bytes to the active IO.
*
*	/param	b					Byte sized value, or pointer to buffer.
*	/param	length				(Optional)The amount of characters in the buffer.
*
*	/returns	size_t			How many bytes were transmitted.
*/
#define Serial_Write(...)		SERIAL_WRITE_MACRO_CHOOSER(__VA_ARGS__)(__VA_ARGS__)



/*
*	Displays an array of bytes in the specified base.
*
*	/param	*data				Pointer to starting memory address.
*	/param	input_length		The amount of characters to display.
*	/param	base				(Default = 16)The base to display each byte as.
*	/param	separator			(Default = '\0')The character used to separate each byte.
*
*	/returns	size_t			How many bytes were transmitted.
*/
#define PrintDataBase(...)		INTERNAL_PRINT_DATA_BASE_MACRO_CHOOSER(__VA_ARGS__)(__VA_ARGS__)



/*
*	Displays an array of bytes in the specified base, ending with a new line character.
*
*	/param	*data				Pointer to starting memory address.
*	/param	input_length		The amount of characters to display.
*	/param	base				(Default = 16)The base to display each byte as.
*	/param	separator			(Default = '\0')The character used to separate each byte.
*
*	/returns	size_t			How many bytes were transmitted.
*/
#define PrintlnDataBase(...)	INTERNAL_PRINTLN_DATA_BASE_MACRO_CHOOSER(__VA_ARGS__)(__VA_ARGS__)



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
#define PrintDataHexEditor(...)	INTERNAL_PRINTLN_DATA_HEX_EDITOR_MACRO_CHOOSER(__VA_ARGS__)(__VA_ARGS__)


#pragma endregion GeNETiCC Macros

#else
#error Missing Library
#endif
#endif /* PRINT_GENETICC_H_ */

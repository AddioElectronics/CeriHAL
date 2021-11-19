#ifndef PRINT_CONFIG_H_
#define PRINT_CONFIG_H_



/*
*	The size of the buffer used for methods that use formatting.
*/
#define PRINT_FORMAT_BUFFER_SIZE 64

/*
*	The amount of bytes to convert to base64 at a time.
*	*Should be divisible by 3.
*	Memory allocated per chunk = 4 * ((BASE64_CHUNK_SIZE + 2) / 3)
*/
#define PRINT_BASE64_CHUNK_SIZE 12

/*
*	BASE64_CHUNK_SIZE converted to the nearest number divisble by 3.
*/
#if PRINT_BASE64_CHUNK_SIZE > 3
#define PRINT_BASE64_TRUE_CHUNK_SIZE PRINT_BASE64_CHUNK_SIZE - (PRINT_BASE64_CHUNK_SIZE % 3)
#else
#define PRINT_BASE64_TRUE_CHUNK_SIZE 3
#endif


/*
*	When defined, println_data_hex_addr will display labels above each column.
*/
#define PRINT_DATA_DISPLAY_LABELS


/*
*	If defined, in functions like "println_data_base64_sep,"
*	if the line_length parameter is not aligned with the base64 data,
*	the line_length will be increased until aligned.
*	If not defined, line_length will be decreased.
*/
#define  PRINT_UNALIGNED_DATA_INCREASE_LINE_LENGTH




#endif /* PRINT_CONFIG_H_ */
#ifndef READER_GENETICC_H_
#define READER_GENETICC_H_

/*
*	Addio Embedded Serial/Reader library is required.
*/
#if __has_include("../../../../../Embedded/IO/serial/reader/reader.h") && __has_include("../../../../../Embedded/IO/serial/serial.h")


#include "internal/reader_geneticc_internal_macros.h"

/*
*	These macros require addio_io.h, and are incompatible with hal_io.h
*/
#if __has_include("../../../../../Embedded/IO/addio_io.h")

/*
*	Gets the number of bytes available in the stream. This is only for bytes that have already arrived.
*
*	Warning : This is unreliable with non buffered libraries like "hal usart sync." 
*
*	Serial_Available()
*/
#define Serial_Available					serial_available

/*
*	Returns the next byte (character) of incoming serial data without removing it from the internal serial buffer.
*	That is, successive calls to peek() will return the same character, as will the next call to read().
*
*	*Warning : Not all I/O descriptors are capable of peeking. It is up to you to figure out what libraries are compatible. (ex. hal usart async is compatible, where hal usart sync is not)
*
*	Serial_Peek()
*
*	/returns	The first byte of incoming serial data available (or -1 if no data is available). Data type: int.
*/
#define Serial_Peek							serial_peek

#endif

/*
*	Reads characters from an incoming stream to the buffer.
*
*	Serial_read()
*
*	/returns	The first byte of incoming serial data available (or -1 if no data is available). Data type: int.
*/
#define Serial_Read							serial_read



/*
*	Reads data from the serial buffer until the target is found. 
*
*	Serial_Find(target)
*	Serial_Find(*target, length)
*
*	/param	target		The character or string(char*) to find.
*	/param	length		(Optional)Then length of the target when passing a char*.			*Required if not static array.
*
*	/returns	bool	The function returns true if target is found, false if it times out.
*/
#define Serial_Find(...)					READER_FIND_MACRO_CHOOSER(__VA_ARGS__)(__VA_ARGS__)

/*
*	Reads data from the serial buffer until a target string of given length or terminator string is found.
*
*	Serial_FindUntil(*target, *terminator)
*	Serial_FindUntil(*target, targetLen, *terminator)
*	Serial_FindUntil(*target, targetLen, *terminator, termLen)
*
*	/param	*target		char*		The string to search for.
*	/param	targetLen	size_t		(Optional)The length of the target.						Default = sizeof(target)	*Required if not static array.
*	/param	terminator	char*		The termination string or character.
*	/param	termLen		size_t		(Optional)Then length of the termination string.		Default = 1
*
*	/returns			bool		The function returns true if the target string is found, false if it times out.
*/
#define Serial_FindUntil(...)				READER_FIND_UNTIL_MACRO_CHOOSER(__VA_ARGS__)(__VA_ARGS__)


/*
*	Reads data from the serial buffer for an arbitrary number of strings.
*
*	Serial_FindMulti(*target, *terminator)
*	Serial_FindMulti(*target, targetLen, *terminator)
*	Serial_FindMulti(*target, targetLen, *terminator, termLen)
*
*	/param	*targets	MultiTarget		An array which contains info about the target string.
*	/param	tCount		int				The amount of targets in the array.
*
*	/returns			int				Returns index of the target that is found first or -1 if timeout occurs.
*/
#define Serial_FindMulti(targets, tCount)	serial_findMulti(target, tCount)

/*
*	Reads characters from the serial port into a buffer. 
*	The function terminates if the determined length has been read, or it times out (see Serial_setTimeout()).
*
*	Serial_ReadBytes(buffer)
*	Serial_ReadBytes(buffer, length)
*
*	/param	buffer		char*			The buffer to store the bytes in.
*	/param	length		size_t			(Optional)The number of bytes to read.			*Required if not static array.
*
*	/returns			int				The number of bytes placed in the buffer.
*/
#define Serial_ReadBytes(...)				READER_READBYTES_MACRO_CHOOSER(__VA_ARGS__)(__VA_ARGS__)

/*
*	Reads characters from the serial port into a buffer.
*	The function terminates if the determined length has been read, or it times out (see Serial_setTimeout()).
*
*	Serial_ReadBytesUntil(terminator, buffer)
*	Serial_ReadBytesUntil(terminator, buffer, length)
*
*	/param	terminator	char			The termination character.
*	/param	buffer		char*			The buffer to store the bytes in.
*	/param	length		size_t			(Optional)The number of bytes to read.			*Required if not static array.
*
*	/returns			int				The number of characters read into the buffer. A 0 means that the length parameter <= 0, a time out occurred before any other input, or a termination character was found before any other input.
*/
#define Serial_ReadBytesUntil(...)			READER_READBYTESUNTIL_MACRO_CHOOSER(__VA_ARGS__)(__VA_ARGS__)

/*
*	Reads characters from the serial buffer into a String. The function terminates if it times out (see setTimeout()).
*
*	Serial_ReadString()
*
*	/returns			string_t*			A pointer to a string.
*/
#define Serial_ReadString					serial_readString	//READER_READSTRING_MACRO_CHOOSER(__VA_ARGS__)(__VA_ARGS__)

/*
*	Reads characters from the serial buffer into a String. The function terminates if it times out (see setTimeout()).
*
*	Serial_ReadString(terminator)
*
*	/param	terminator	char				The termination character.
*
*	/returns			string_t*			A pointer to a string, read from the serial buffer, up to the terminator character
*/
#define Serial_ReadStringUntil(terminator)	serial_readStringUntil(terminator)	//READER_READSTRING_MACRO_CHOOSER(__VA_ARGS__)(__VA_ARGS__)

/*
*	Looks for the next valid integer in the incoming serial. The function terminates if it times out (see Serial.setTimeout()).
*
*	*Warning : This macro uses "peek." Not all I/O descriptors are capable of peeking. It is up to you to figure out what libraries are compatible. (ex. hal usart async is compatible, where hal usart sync is not)
*
*	Serial_ParseInt()
*	Serial_ParseInt(lookahead)
*	Serial_ParseInt(lookahead, ignore)
*
*	/param	lookahead	LookaheadMode		(Optional)The mode used to look ahead in the stream for an integer.										Default = SKIP_ALL
*	/param	ignore		char				(Optional)Used to skip the indicated char in the search. Used for example to skip thousands divider.	Default = '\x01'
*
*	/returns			long				The next valid integer.
*/
#define Serial_ParseInt(...)				READER_PARSEINT_MACRO_CHOOSER(__VA_ARGS__)(__VA_ARGS__)

/*
*	Returns the first valid floating point number from the Serial buffer. 
*	parseFloat() is terminated by the first character that is not a floating point number. 
*	The function terminates if it times out (see Serial.setTimeout()).
*
*	*Warning : This macro uses "peek." Not all I/O descriptors are capable of peeking. It is up to you to figure out what libraries are compatible. (ex. hal usart async is compatible, where hal usart sync is not)
*
*	Serial_ParseFloat()
*	Serial_ParseFloat(lookahead)
*	Serial_ParseFloat(lookahead, ignore)
*
*	/param	lookahead	LookaheadMode		(Optional)The mode used to look ahead in the stream for an integer.										Default = SKIP_ALL
*	/param	ignore		char				(Optional)Used to skip the indicated char in the search. Used for example to skip thousands divider.	Default = '\x01'
*
*	/returns			float				The next valid floating point.
*/
#define Serial_ParseFloat(...)				READER_PARSEFLOAT_MACRO_CHOOSER(__VA_ARGS__)(__VA_ARGS__)

#else
#error Missing Library
#endif
#endif /* READER_GENETICC_H_ */
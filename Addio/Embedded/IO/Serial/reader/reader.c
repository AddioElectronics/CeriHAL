
#include "reader.h"

#include <utils_assert.h>

#if __has_include("../../../timing/system_timer/system_timer.h")
#include "../../../timing/system_timer/system_timer.h"
#endif


#if __has_include("hal_io.h")
#include <hal_io.h>
extern struct io_descriptor* serial_io;
#elif __has_include("../../addio_io.h")
#include "../../addio_io.h"
extern struct io_descriptor* serial_io;
#else
#error unsupported
#endif



extern unsigned long serial_timeout;
unsigned long _startMillis;

#pragma region Internal Functions



int reader_timedRead()
{
	int c;
	_startMillis = millis();
	do {
		c = reader_read();
		if (c >= 0) return c;
	} while(millis() - _startMillis < serial_timeout);
	return -1;     // -1 indicates timeout
}

//	*Warning : Not all I/O descriptors are capable of peeking. It is up to you to figure out what libraries are compatible. (ex. hal usart async is compatible, where hal usart sync is not)
int reader_timedPeek()
{
	int c;
	_startMillis = millis();
	do {
		c = reader_peek();
		if (c >= 0) return c;
	} while(millis() - _startMillis < serial_timeout);
	return -1;     // -1 indicates timeout
}

//	*Warning : Not all I/O descriptors are capable of peeking. It is up to you to figure out what libraries are compatible. (ex. hal usart async is compatible, where hal usart sync is not)
// returns peek of the next digit in the stream or -1 if timeout
// discards non-numeric characters
int reader_peekNextDigit(enum LookaheadMode lookahead, bool detectDecimal)
{
	int c;
	while (1) {
		c = reader_timedPeek();

		if( c < 0 ||
		c == '-' ||
		(c >= '0' && c <= '9') ||
		(detectDecimal && c == '.')) return c;

		switch( lookahead ){
			case SKIP_NONE: return -1; // Fail code.
			case SKIP_WHITESPACE:
			switch( c ){
				case ' ':
				case '\t':
				case '\r':
				case '\n': break;
				default: return -1; // Fail code.
			}
			case SKIP_ALL:
			break;
		}
		reader_read();  // discard non-numeric
	}
}

#pragma endregion Internal Functions

#pragma region Public Functions

//	Warning : This is unreliable with non buffered libraries like "hal usart sync." 
int __attribute__((__always_inline__)) reader_available()
{
	#if __has_include("../../addio_io.h")
	
	//Unsupported function.
	ASSERT(serial_io->rxReady);

	return serial_io->rxReady(serial_io);
	#else
	#error unsupported.
	#endif
}


/*
*	Reads characters from an incoming stream to the buffer.
*
*	/returns	The first byte of incoming serial data available (or -1 if no data is available). Data type: int.
*/
int __attribute__((__always_inline__)) reader_read()
{
	//#if __has_include("addio_io.h")
	//
	//return serial_io->get(serial_io);
	#if __has_include("hal_io.h") || __has_include("../../addio_io.h")
	char data;
	
	if(serial_io->read(serial_io, &data, 1) == 0)
	return -1; //0 bytes read, return -1
	
	//Byte was valid, return data.
	return data;
	
	#else
	#error unsupported.
	#endif
}

/*
*	Returns the next byte (character) of incoming serial data without removing it from the internal serial buffer.
*	That is, successive calls to peek() will return the same character, as will the next call to read().
*
*	*Warning : Not all I/O descriptors are capable of peeking. It is up to you to figure out what libraries are compatible. (ex. hal usart async is compatible, where hal usart sync is not)
*
*	/returns	The first byte of incoming serial data available (or -1 if no data is available). Data type: int.
*/
int __attribute__((__always_inline__)) reader_peek()
{
	#if __has_include("../../addio_io.h")
	
	//Unsupported function.
	//Either the function has not been added to the IO descriptor,
	//or the component used is not a buffered system, and is unable to peek.
	ASSERT(serial_io->peek);
	
	return serial_io->peek(serial_io);
	#else
	#error unsupported.
	#endif
}


// reads data from the stream until the target string of given length is found
// returns true if target string is found, false if timed out
bool __attribute__((__always_inline__)) reader_find(char* target, size_t length)
{
	return reader_findUntil(target, length, NULL, 0);
}

bool __attribute__((__always_inline__)) reader_findChar(char target)
{
	return reader_find(&target, 1);
}


// reads data from the stream until the target string of the given length is found
// search terminated if the terminator string is found
// returns true if target string is found, false if terminated or timed out
bool reader_findUntil(char *target, size_t targetLen, char *terminator, size_t termLen)
{
	if (terminator == NULL) {
		struct MultiTarget t[1] = {{target, targetLen, 0}};
		return reader_findMulti(t, 1) == 0 ? true : false;
		} else {
		struct MultiTarget t[2] = {{target, targetLen, 0}, {terminator, termLen, 0}};
		return reader_findMulti(t, 2) == 0 ? true : false;
	}
}


int reader_findMulti( struct MultiTarget *targets, int tCount) 
{
	// any zero length target string automatically matches and would make
	// a mess of the rest of the algorithm.
	for (struct MultiTarget *t = targets; t < targets+tCount; ++t) {
		if (t->len <= 0)
		return t - targets;
	}

	while (1) {
		int c = reader_timedRead();
		if (c < 0)
		return -1;

		for (struct MultiTarget *t = targets; t < targets+tCount; ++t) {
			// the simple case is if we match, deal with that first.
			if (c == t->str[t->index]) {
				if (++t->index == t->len)
				return t - targets;
				else
				continue;
			}

			// if not we need to walk back and see if we could have matched further
			// down the stream (ie '1112' doesn't match the first position in '11112'
			// but it will match the second position so we can't just reset the current
			// index to 0 when we find a mismatch.
			if (t->index == 0)
			continue;

			int origIndex = t->index;
			do {
				--t->index;
				// first check if current char works against the new current index
				if (c != t->str[t->index])
				continue;

				// if it's the only char then we're good, nothing more to check
				if (t->index == 0) {
					t->index++;
					break;
				}

				// otherwise we need to check the rest of the found string
				int diff = origIndex - t->index;
				size_t i;
				for (i = 0; i < t->index; ++i) {
					if (t->str[i] != t->str[i + diff])
					break;
				}

				// if we successfully got through the previous loop then our current
				// index is good.
				if (i == t->index) {
					t->index++;
					break;
				}

				// otherwise we just try the next index
			} while (t->index);
		}
	}
	// unreachable
	return -1;
}



// read characters from stream into buffer
// terminates if length characters have been read, or timeout (see setTimeout)
// returns the number of characters placed in the buffer
// the buffer is NOT null terminated.
//
size_t reader_readBytes(char* buffer, size_t length)
{
	size_t count = 0;
	while (count < length) {
		int c = reader_timedRead();
		if (c < 0) break;
		*buffer++ = (char)c;
		count++;
	}
	return count;
}


// as readBytes with terminator character
// terminates if length characters have been read, timeout, or if the terminator character  detected
// returns the number of characters placed in the buffer (0 means no valid data found)

size_t reader_readBytesUntil(char terminator, char *buffer, size_t length)
{
	if (length < 1) return 0;
	size_t index = 0;
	while (index < length) {
		int c = reader_timedRead();
		if (c < 0 || c == terminator) break;
		*buffer++ = (char)c;
		index++;
	}
	return index; // return number of characters, not including null terminator
}

string_t* __attribute__((__always_inline__)) reader_readString()
{
	return reader_readStringUntil(-1);
	//string_t* ret = new_cstring(16);
	//int c = reader_timedRead();
	//while (c >= 0)
	//{
		//cstring_append(ret, &c, 1);
		//c = reader_timedRead();
	//}
	//return ret;
}

string_t* reader_readStringUntil(char terminator)
{
	string_t* ret = new_cstring(16);
	int c = reader_timedRead();
	while (c >= 0 && c != terminator)
	{
		cstring_append(ret, &c, 1);
		c = reader_timedRead();
	}
	return ret;
}


//	*Warning : This function uses "peek." Not all I/O descriptors are capable of peeking. It is up to you to figure out what libraries are compatible. (ex. hal usart async is compatible, where hal usart sync is not)
// returns the first valid (long) integer value from the current position.
// lookahead determines how parseInt looks ahead in the stream.
// See LookaheadMode enumeration at the top of the file.
// Lookahead is terminated by the first character that is not a valid part of an integer.
// Once parsing commences, 'ignore' will be skipped in the stream.
long reader_parseInt(enum LookaheadMode lookahead, char ignore)
{
	bool isNegative = false;
	long value = 0;
	int c;

	c = reader_peekNextDigit(lookahead, false);
	// ignore non numeric leading characters
	if(c < 0)
	return 0; // zero returned if timeout

	do{
		if(c == ignore)
		; // ignore this character
		else if(c == '-')
		isNegative = true;
		else if(c >= '0' && c <= '9')        // is c a digit?
		value = value * 10 + c - '0';
		reader_read();  // consume the character we got with peek
		c = reader_timedPeek();
	}
	while( (c >= '0' && c <= '9') || c == ignore );

	if(isNegative)
	value = -value;
	return value;
}

//	*Warning : This function uses "peek." Not all I/O descriptors are capable of peeking. It is up to you to figure out what libraries are compatible. (ex. hal usart async is compatible, where hal usart sync is not)
// as parseInt but returns a floating point value
float reader_parseFloat(enum LookaheadMode lookahead, char ignore)
{
	bool isNegative = false;
	bool isFraction = false;
	long value = 0;
	int c;
	float fraction = 1.0;

	c = reader_peekNextDigit(lookahead, true);
	// ignore non numeric leading characters
	if(c < 0)
	return 0; // zero returned if timeout

	do{
		if(c == ignore)
		; // ignore
		else if(c == '-')
		isNegative = true;
		else if (c == '.')
		isFraction = true;
		else if(c >= '0' && c <= '9')  {      // is c a digit?
			value = value * 10 + c - '0';
			if(isFraction)
			fraction *= 0.1;
		}
		reader_read();  // consume the character we got with peek
		c = reader_timedPeek();
	}
	while( (c >= '0' && c <= '9')  || (c == '.' && !isFraction) || c == ignore );

	if(isNegative)
	value = -value;
	if(isFraction)
	return value * fraction;
	else
	return value;
}

#pragma endregion Public Functions
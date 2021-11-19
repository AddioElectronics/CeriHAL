#ifndef READER_H_
#define READER_H_

/*
*	Addio Embedded Serial and either hal_io or Addio Embedded IO "library" required.
*/
#if (__has_include("hal_io.h") || __has_include("../../addio_io.h")) /*&& __has_include("../serial.h"))*/

#include "reader_config.h"
#include "reader_defs.h"

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "../../../../Universal/standard/cstring/cstring.h"

/*
*	These functions require addio_io.h, and are incompatible with hal_io.h
*/
#if __has_include("../../addio_io.h")
int reader_peek();
int reader_available();
#else
#warning Unsupported
#endif


int reader_read();

bool reader_find(char* target, size_t length);
bool reader_findUntil(char *target, size_t targetLen, char *terminate, size_t termLen);
int reader_findMulti( struct MultiTarget *targets, int tCount);

size_t reader_readBytes(char *buffer, size_t length);
size_t reader_readBytesUntil(char terminator, char *buffer, size_t length);

string_t* reader_readString();
string_t* reader_readStringUntil(char terminator);

long reader_parseInt(enum LookaheadMode lookahead, char ignore);
float reader_parseFloat(enum LookaheadMode lookahead, char ignore);


#else
#warning Unsupported
#endif
#endif /* READER_H_ */
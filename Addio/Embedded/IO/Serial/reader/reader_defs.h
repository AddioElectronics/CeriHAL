#ifndef READER_DEFS_H_
#define READER_DEFS_H_

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>


// This enumeration provides the lookahead options for parseInt(), parseFloat()
// The rules set out here are used until either the first valid character is found
// or a time out occurs due to lack of input.
enum LookaheadMode{
	SKIP_ALL,       // All invalid characters are ignored.
	SKIP_NONE,      // Nothing is skipped, and the serial is not touched unless the first waiting character is valid.
	SKIP_WHITESPACE // Only tabs, spaces, line feeds & carriage returns are skipped.
};

struct MultiTarget{
	const char* str;
	size_t len;
	size_t index;
};

#define NO_IGNORE_CHAR  '\x01' // a char not found in a valid ASCII numeric field

#endif /* READER_DEFS_H_ */
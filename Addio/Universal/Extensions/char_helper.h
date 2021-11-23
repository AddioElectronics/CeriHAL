#ifndef CHAR_HELPER_H_
#define CHAR_HELPER_H_

#include <stdint.h>
#include <stdbool.h>

char char_toLower(char c);

char char_toUpper(char c);

bool char_equals(char c, const char* characters, uint32_t count);

#endif /* CHAR_HELPER_H_ */

#ifndef CSTRING_H_
#define CSTRING_H_

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "cstring_config.h"

typedef struct  
{
	char* buf;
	uint16_t length;	//Size of string
	size_t capacity;	//Size of buffer
}string_t;


void cstring_init(string_t* string, uint16_t capacity);

void cstring_delete(string_t* string);

bool cstring_ensure_capacity();

void cstring_shrink_to_fit();

void cstring_append(string_t* a, char* b, size_t length);

#endif /* CSTRING_H_ */
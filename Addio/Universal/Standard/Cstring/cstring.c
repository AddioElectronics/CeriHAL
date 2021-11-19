#include "cstring.h"

string_t* new_cstring(uint16_t capacity)
{
	string_t* string = malloc(sizeof(string_t));
	string->buf = malloc(capacity);
	string->length = 0;
	string->capacity = capacity;
	
	return string;
}

void cstring_init(string_t* string, uint16_t capacity)
{
	string->buf = malloc(capacity);
}

void cstring_delete(string_t* string)
{
	free(string->buf);
	free(string);
}

bool cstring_ensure_capacity(string_t* string, uint32_t min)
{
	if(string->capacity < min)
	{
		size_t newCapacity = string->capacity == 0 ? CSTRING_DEFAULT_CAPACITY: CSTRING_INCREASE_CAPACITY(string->capacity);
		
		if(newCapacity > CSTRING_MAX_SIZE) newCapacity = CSTRING_MAX_SIZE;
		if(newCapacity < min) newCapacity = min;
		
		if(string->capacity == 0)
		{
			string->buf = malloc(newCapacity);
		}
		else
		{
			string->buf = realloc(string->buf, newCapacity);
		}
		string->capacity = newCapacity;
	}
	return true;
	
}


void cstring_shrink_to_fit(string_t* string)
{
	string->capacity = string->length;
	string->buf = realloc(string->buf, string->capacity);
}

void cstring_append(string_t* a, char* b, size_t length)
{
	cstring_ensure_capacity(a, a->length + length);	
	memcpy(a->buf + a->length, b, length);
	a->length += length;
}


void __attribute__((__always_inline__)) cstring_max_size()
{
	return CSTRING_MAX_SIZE;
}
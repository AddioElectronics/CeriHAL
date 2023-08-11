#include "cstring.h"

#include <stdarg.h>
#include <utils_assert.h>

#include "Addio/Universal/Extensions/char_helper.h"

#define CSTRING_ASSERT_MAX_LENGTH(x) ASSERT(x <= CSTRING_MAX_SIZE)

const char whitespace_characters[] = {' ','\t', '\r', '\n', '\f', '\v'};

static void __attribute__((__always_inline__)) string_add_null_terminator(string_t* string)
{
	string->buf[string->length] = 0;
}

static void __attribute__((__always_inline__)) cstring_0_length_get(char* cstring, size_t* length)
{
	if(*length == 0) *length = strlen(cstring);
}

string_t* new_string(int capacity)
{
	string_t* string = malloc(sizeof(string_t));
	string_init(string, capacity);
	return string;
}

void string_init(string_t* string, int capacity)
{
	if(capacity == 0)
	capacity = CSTRING_DEFAULT_CAPACITY;
	
	string->length = 0;
	string->capacity = 0;
	
	//If capacity is < 0, the buffer will be initialized at a later time.
	if(capacity > -1)
	{
		string_ensure_capacity(string, capacity);
		//string->buf = malloc(capacity + 1);
		//
		////Zero out the buffer.
		//memset(string->buf, 0, string->capacity + 1);
	}
	
	string->capacity = capacity;
}

string_t* string_clone(string_t* string)
{
	string_t* clone = new_string(string->capacity);
	string_set_buf(clone->buf, string->buf, string->length);
	//memcpy(clone->buf, string->buf, string->length);
	//clone->length = string->length;	
	return clone;
}

void string_set_buf(string_t* string, char* buf, size_t length)
{
	#if CSTRING_0_LENGTH_GET_STRLEN == true
	cstring_0_length_get(buf, &length);
	#endif
	
	memcpy(string->buf, buf, length);
	string->length = length;
	string_add_null_terminator(string);
}

void __attribute__((__always_inline__)) string_set(string_t* string, char* buf)
{
	string_set_buf(string, buf, 0);
}

void string_delete(string_t* string)
{
	if(string == NULL) return;
	
	free(string->buf);
	free(string);
}

bool string_ensure_capacity(string_t* string, uint32_t min)
{
	if(string->capacity < min)
	{
		size_t newCapacity = string->capacity == 0 ? CSTRING_DEFAULT_CAPACITY: CSTRING_INCREASE_CAPACITY(string->capacity);
		
		if(newCapacity > CSTRING_MAX_SIZE) newCapacity = CSTRING_MAX_SIZE;
		if(newCapacity < min) newCapacity = min;
		
		if(string->capacity <= 0)
		{
			//Add 1 character for null termination.
			string->buf = malloc(newCapacity + 1);
		}
		else
		{
			//Add 1 character for null termination.
			string->buf = realloc(string->buf, newCapacity + 1);
		}
		
		string->capacity = newCapacity;
	
		//Zero out the buffer.
		memset(string->buf + string->length, 0, string->capacity + 1 - string->length);
	}
	return true;
	
}


void string_shrink_to_fit(string_t* string)
{
	string->capacity = string->length;
	string->buf = realloc(string->buf, string->capacity + 1);
}

/*
*	Appends a cstring to a string_t.
*
*	/param	a		The string_t to append b to.
*	/param	b		The cstring to append onto a.
*	/param	length	The size of the string in b.
*/
void cstring_append(string_t* a, char* b, size_t length)
{
	#if CSTRING_0_LENGTH_GET_STRLEN == true
	cstring_0_length_get(b, &length);
	#endif
	
	CSTRING_ASSERT_MAX_LENGTH(a->length + length);
	
	string_ensure_capacity(a, a->length + length);	
	memcpy(a->buf + a->length, b, length);
	a->length += length;
	
	//Ensure null terminator exists.
	string_add_null_terminator(a);
}

/*
*	Appends a string_t to a string_t.
*
*	/param	a		The string_t to append b to.
*	/param	b		The string_t to append onto a.
*/
void __attribute__((__always_inline__)) string_append(string_t* a, string_t* b)
{
	cstring_append(a, b->buf, b->length);
}

/*
*	Combines a and b in to a new string_t.
*
*	/param		a			The string on the left.
*	/param		b			The string on the right.
*	/param		length		The size of the string in b.
*
*	/returns	string_t	The a and b string combined in a new string.
*/
string_t* cstring_concat(string_t* a, char* b, size_t length)
{
	#if CSTRING_0_LENGTH_GET_STRLEN == true
	cstring_0_length_get(b, &length);
	#endif
	
	string_t* combined = new_string(a->length + length);
	memcpy(combined->buf, a->buf, a->length);
	memcpy(combined->buf + a->length, b, length);
	combined->length = a->length + length;
	return combined;
}

/*
*	Combines a and b in to a new string_t.
*
*	/param		a			The string on the left.
*	/param		b			The string on the right.
*
*	/returns	string_t	The a and b string combined in a new string.
*/
string_t* __attribute__((__always_inline__)) string_concat(string_t* a, string_t* b)
{
	return cstring_concat(a, b->buf, b->length);
}

/*
*	Formats a string using a va_list of arguments.
*
*	/param		format		The string to format.
*	/param		newString	If true, a copy will be formatted and returned. If false, the original string will be formatted.
*	/param		ap			List of variadic arguments used for formatting.
*
*	/returns	string_t	The formatted string. If newString is false, format will be returned.
*/
string_t* string_vformat(string_t* format, bool newString, va_list ap)
{
	string_t* result = newString ? string_clone(format) : format;
	
	//Get total size of formatted string.
	size_t formatSize = vsnprintf(NULL, 0, format->buf, ap);
	
	CSTRING_ASSERT_MAX_LENGTH(formatSize);
	
	string_ensure_capacity(format, formatSize);
	
	char* tbuf = alloca(formatSize);
	vsprintf(tbuf, format->buf, ap);
	memcpy(format->buf, tbuf, formatSize);
	format->length = formatSize;
	
	return result;
}

/*
*	Formats a string using a variadic arguments.
*
*	/param		format		The string to format.
*	/param		newString	If true, a copy will be formatted and returned. If false, the original string will be formatted.
*	/param		...			Variadic arguments used for formatting.
*
*	/returns	string_t	The formatted string. If newString is false, format will be returned.
*/
string_t* string_format(string_t* format, bool newString, ...)
{
	va_list ap;
	va_start(ap, newString);	
	string_t* result = string_vformat(format, newString, ap);	
	va_end(ap);
	return result;
}

/*
*	Returns the maximum amount of characters allowed in a string's buffer.
*/
unsigned long __attribute__((__always_inline__)) string_max_size()
{
	return CSTRING_MAX_SIZE;
}




//slen is size of string, not buffer
int cstring_indexOf(char* string, size_t slen, char* compare, size_t clen, bool ignoreCase)
{
	if(slen == 0 || slen < clen) return -1;
	
	#if CSTRING_0_LENGTH_GET_STRLEN == true
	cstring_0_length_get(compare, &clen);
	#endif
	
	uint32_t b;
	uint32_t i;
	
	switch(ignoreCase)
	{
		case false:
		for(i = 0; i < slen; i++)
		{
			for(b = 0; b < clen; b++)
			{
				if(string[i + b] != compare[b]) break;
			}
			
			if(b == clen) return i;
		}
		break;
		
		case true:
		for(i = 0; i < slen; i++)
		{
			for(b = 0; b < clen; b++)
			{
				char s = char_toLower(string[i + b]);
				char c = char_toLower(compare[b]);
				if(s != c) break;
			}
			
			if(b == clen) return i;
		}
		break;
	}
	
	return -1;
}

int __attribute__((__always_inline__)) string_indexOf_char(string_t* string, char compare, bool ignoreCase)
{
	return cstring_indexOf(string->buf, string->length, &compare, 1, ignoreCase);
}

int __attribute__((__always_inline__)) string_indexOf_charp(string_t* string,  char* compare, size_t clen, bool ignoreCase)
{
	return cstring_indexOf(string->buf, string->length, compare, clen, ignoreCase);
}

int __attribute__((__always_inline__)) string_indexOf(string_t* string,  string_t* compare, bool ignoreCase)
{
	return cstring_indexOf(string->buf, string->length, compare->buf, compare->length, ignoreCase);
}

//slen is size of string, not buffer
int cstring_lastIndexOf(char* string, size_t slen, char* compare, size_t clen, bool ignoreCase)
{
	if(slen == 0 || slen < clen) return -1;
	
	#if CSTRING_0_LENGTH_GET_STRLEN == true
	cstring_0_length_get(compare, &clen);
	#endif
	
	uint32_t b;
	
	switch(ignoreCase)
	{
		case false:
		for(int i = slen - clen; i >= 0; i--)
		{
			for(b = clen - 1; b >= 0; b--)
			{
				if(string[i + b] != compare[b]) break;
			}
			
			if(b == -1) 
			return i;
		}
		break;
		
		case true:
		for(int i = slen - clen; i >= 0; i--)
		{
			for(b = clen - 1; b >= 0; b--)
			{
				
				if(char_toLower(string[i + b]) != char_toLower(compare[b])) break;
				
				//if(string[i + b] != compare[b])
				//{
				//if(string[i + b] >= 'A' && (string[i + b] <= 'Z')
				//{
				//if(string[i + b] + 32 != compare[b]) break;
				//}
				//else if(string[i + b] >= 'a' && (string[i + b] <= 'z')
				//{
				//if(string[i + b] - 32 != compare[b]) break;
				//}
				//else
				//{
				//break;
				//}
				//}
			}
			
			if(b == -1) 
			return i;
		}
		break;
	}
	
	return -1;
}

int __attribute__((__always_inline__)) string_lastIndexOf_char(string_t* string, char compare, bool ignoreCase)
{
	return cstring_lastIndexOf(string->buf, string->length, &compare, 1, ignoreCase);	
}

int __attribute__((__always_inline__)) string_lastIndexOf_charp(string_t* string, char* compare, size_t clen, bool ignoreCase)
{
	return cstring_lastIndexOf(string->buf, string->length, compare, clen, ignoreCase);
}

int __attribute__((__always_inline__)) string_lastIndexOf(string_t* string, string_t* compare, bool ignoreCase)
{
	return cstring_lastIndexOf(string->buf, string->length, compare->buf, compare->length, ignoreCase);
}


int cstring_indexOfAny(char* string, size_t slen, char* compare, int cmpCount)
{
	#if CSTRING_0_LENGTH_GET_STRLEN == true
	cstring_0_length_get(compare, &cmpCount);
	#endif
	
	for(uint32_t i = 0; i < slen; i++)
	{
		for(uint32_t b = 0; b < cmpCount; b++)
		{
			if(string[i] == compare[b]) return i;
		}
	}
	
	return -1;
}

int __attribute__((__always_inline__)) string_indexOfAny(string_t* string,  char* compare, int cmpCount)
{
	return cstring_indexOfAny(string->buf, string->length, compare, cmpCount);
}


int cstring_lastIndexOfAny(char* string, size_t slen, char* compare, int cmpCount)
{
	#if CSTRING_0_LENGTH_GET_STRLEN == true
	cstring_0_length_get(compare, &cmpCount);
	#endif
	
	for(int i = slen - 1; i >= 0; i--)
	{
		for(uint32_t b = 0; b < cmpCount; b++)
		{
			if(string[i] == compare[b]) return i;
		}
	}
	
	return -1;
}

int __attribute__((__always_inline__)) string_lastIndexOfAny(string_t* string,  char* compare, int cmpCount)
{
	return cstring_lastIndexOfAny(string->buf, string->length, compare, cmpCount);
}


uint32_t cstring_matchCount(char* string, size_t slen, char* compare, size_t clen, bool ignoreCase)
{
	#if CSTRING_0_LENGTH_GET_STRLEN == true
	cstring_0_length_get(compare, &clen);
	#endif
	
	int32_t index = 0;
	uint32_t count = 0;
	size_t processed = 0;

	while(processed < slen && (index = cstring_indexOf(string + processed, slen - processed, compare, clen, ignoreCase)) != -1)
	{
		count++;
		index++;
		processed += index;
	}
	
	return count;
}

uint32_t __attribute__((__always_inline__)) string_matchCount_char(string_t* string, char compare, bool ignoreCase)
{
	return cstring_matchCount(string->buf, string->length, &compare, 1, ignoreCase);
}

uint32_t __attribute__((__always_inline__)) string_matchCount_charp(string_t* string, char* compare, size_t clen, bool ignoreCase)
{
	return cstring_matchCount(string->buf, string->length, compare, clen, ignoreCase);
}

uint32_t __attribute__((__always_inline__)) string_matchCount(string_t* string, string_t* compare, bool ignoreCase)
{
	return cstring_matchCount(string->buf, string->length, compare->buf, compare->length, ignoreCase);
}


//slen is size of buffer or string
bool cstring_isEmpty(char* string, size_t slen)
{
	#if CSTRING_0_LENGTH_GET_STRLEN == true
	cstring_0_length_get(string, &slen);
	#endif
	
	if(slen == 0) return true;
	
	for(int i = 0; i < slen; i++)
	{
		if(string[i] != 0)
		return false;
	}
	
	return true;
}


bool __attribute__((__always_inline__)) string_isEmpty(string_t* string)
{
	return cstring_isEmpty(string->buf, string->length);
}

//slen is size of buffer or string
bool cstring_isEmptyOrWhitespace(char* string, size_t slen)
{
	#if CSTRING_0_LENGTH_GET_STRLEN == true
	cstring_0_length_get(string, &slen);
	#endif
	
	if(slen == 0) return true;
	
	for(int i = 0; i < slen; i++)
	{
		if(string[i] != 0 && string[i] != ' ')
		return false;
	}
	
	return true;
}


bool __attribute__((__always_inline__)) string_isEmptyOrWhitespace(string_t* string)
{
	return cstring_isEmptyOrWhitespace(string->buf, string->length);
}

/*
*	Inserts a char pointer into a string_t at the specified index.
*
*	
*/
string_t* cstring_insert(string_t* string, char* insert, size_t length, uint32_t index, bool newString)
{
	#if CSTRING_0_LENGTH_GET_STRLEN == true
	cstring_0_length_get(insert, &length);
	#endif
	
	//Make sure new string will be in string size limit.
	CSTRING_ASSERT_MAX_LENGTH(string->length + length);
	
	//Make sure index is in-range.
	ASSERT(index <= string->length);
	
	string_t* result = newString ? new_string(string->length + length) : string;
	
	if(newString)	memcpy(result->buf, string->buf, index);
	else			string_ensure_capacity(result, string->length + length);
	
	memmove(result->buf + index + length, string->buf + index, string->length - index);
	memcpy(result->buf + index, insert, length);
	
	result->length = string->length + length;	
	
	string_add_null_terminator(result);
	
	return result;
}

string_t* __attribute__((__always_inline__)) string_insert_char(string_t* string, char insert, uint32_t index, bool newString)
{
	return cstring_insert(string, &insert, 1, index, newString);
}

string_t* __attribute__((__always_inline__)) string_insert(string_t* string, string_t* insert, uint32_t index, bool newString)
{
	return cstring_insert(string, insert->buf, insert->length, index, newString);
}

string_t* cstring_join(char* seperator, size_t seplen, string_t** values, uint32_t count)
{
	uint32_t values_length = 0;
	
	for(uint32_t i = 0; i < count; i++)
	{
		values_length += values[i]->length;
	}
	
	uint32_t total_length = (seplen*(count-1)) + values_length;
	
	CSTRING_ASSERT_MAX_LENGTH(total_length);
	
	string_t* result = new_string(total_length);
	
	for(uint32_t i = 0; i < count; i++)
	{
		string_append(result, values[i]);
		
		if(i != count - 1)
		cstring_append(result, seperator, seplen);
	}
	
	string_add_null_terminator(result);
	
	return result;
}

string_t* __attribute__((__always_inline__)) string_join_char(char seperator, string_t** values, uint32_t count)
{
	return cstring_join(&seperator, 1, values, count);
}

string_t* __attribute__((__always_inline__)) string_join(string_t* seperator, string_t** values, uint32_t count)
{
	return cstring_join(seperator->buf, seperator->length, values, count);
}


bool __attribute__((__always_inline__)) cstring_contains(char* string, size_t slen, char* compare, size_t clen, bool ignoreCase)
{
	return cstring_indexOf(string, slen, compare, clen, ignoreCase) != -1;
}

bool __attribute__((__always_inline__)) string_contains_char(string_t* string, char compare, bool ignoreCase)
{
	return cstring_indexOf(string->buf, string->length, &compare, 1, ignoreCase) != -1;
}

bool __attribute__((__always_inline__)) string_contains_charp(string_t* string, char* compare, size_t clen, bool ignoreCase)
{
	return cstring_indexOf(string->buf, string->length, compare, clen, ignoreCase) != -1;
}


bool  __attribute__((__always_inline__)) string_contains(string_t* string, string_t* compare, bool ignoreCase)
{
	return cstring_indexOf(string->buf, string->length, compare->buf, compare->length, ignoreCase) != -1;
}


//slen is size of string, not buffer
int cstring_compare(char* string, char* compare, size_t length, bool ignoreCase)
{
	uint32_t i = 0;
	switch(ignoreCase)
	{
		case false:		
			while(i < length || length == 0)
			{
				if(string[i] == 0 && compare[i] == 0)	return 0;
				if(string[i] != compare[i])				return (int)(string[i] - compare[i]);
				
				i++;
			}
		break;
		
		case true:
			while(i < length || length == 0)
			{
				if(string[i] == 0 && compare[i] == 0)	return 0;
				
				char s = char_toLower(string[i]);
				char c = char_toLower(compare[i]);
				
				if(s != c) return (int)(s - c);	
				
				i++;			
			}
		break;
	}
	
	return 0;
}

int __attribute__((__always_inline__)) string_compare(string_t* string, string_t* compare, uint32_t length, bool ignoreCase)
{
	return cstring_compare(string->buf, compare->buf, length, ignoreCase);
}


bool __attribute__((__always_inline__)) cstring_startsWith(char* string, size_t slen, char* compare, size_t clen, bool ignoreCase)
{
	return cstring_indexOf(string, slen, compare, clen, ignoreCase) == 0;
}

bool __attribute__((__always_inline__)) string_startsWith_char(string_t* string, char compare, bool ignoreCase)
{
	return cstring_indexOf(string->buf, string->length, &compare, 1, ignoreCase) == 0;
}

bool __attribute__((__always_inline__)) string_startsWith_charp(string_t* string, char* compare, size_t clen,  bool ignoreCase)
{
	return cstring_indexOf(string->buf, string->length, compare, clen, ignoreCase) == 0;
}

bool __attribute__((__always_inline__)) string_startsWith(string_t* string, string_t* compare, bool ignoreCase)
{
	return cstring_indexOf(string->buf, string->length, compare->buf, compare->length, ignoreCase) == 0;
}


bool __attribute__((__always_inline__)) cstring_endsWith(char* string, size_t slen, char* compare, size_t clen, bool ignoreCase)
{
	#if CSTRING_0_LENGTH_GET_STRLEN == true
	cstring_0_length_get(compare, &clen);
	#endif
	return cstring_lastIndexOf(string, slen, compare, clen, ignoreCase) == slen - clen;
}

bool __attribute__((__always_inline__)) string_endsWith_char(string_t* string, char compare, bool ignoreCase)
{
	return cstring_lastIndexOf(string->buf, string->length, &compare, 1, ignoreCase) == string->length - 1;
}

bool __attribute__((__always_inline__)) string_endsWith_charp(string_t* string, char* compare, size_t clen, bool ignoreCase)
{
	#if CSTRING_0_LENGTH_GET_STRLEN == true
	cstring_0_length_get(compare, &clen);
	#endif
	return cstring_lastIndexOf(string->buf, string->length, compare, clen, ignoreCase) == string->length - clen;
}

bool __attribute__((__always_inline__)) string_endsWith(string_t* string, string_t* compare, bool ignoreCase)
{
	return cstring_lastIndexOf(string->buf, string->length, compare->buf, compare->length, ignoreCase) == string->length - compare->length;
}


string_t* string_padLeft(string_t* string, uint32_t count, char c, bool newString)
{
	CSTRING_ASSERT_MAX_LENGTH(string->length + count);
	
	string_t* result = newString ? new_string(string->length + count) : string;
	
	if(!newString) string_ensure_capacity(result, string->length + count);
	
	
	if(c == 0) c = ' ';
	
	memmove(result->buf + count, string->buf, string->length);
	memset(result->buf, c, count);
	
	result->length = string->length + count;
	
	string_add_null_terminator(result);
	
	return result;
}

string_t* string_padRight(string_t* string, uint32_t count, char c, bool newString)
{
	CSTRING_ASSERT_MAX_LENGTH(string->length + count);
	
	string_t* result = newString ? new_string(string->length + count) : string;
	
	if(newString)	memcpy(result->buf, string->buf, string->length);
	else			string_ensure_capacity(result, string->length + count);
	
	if(c == 0) c = ' ';

	memset(result->buf + result->length, c, count);
	
	result->length = string->length + count;
	
	string_add_null_terminator(result);
	
	return result;
}

//slen size of buffer or string
char* cstring_remove(char* string, size_t slen, uint32_t index, size_t count, bool newString)
{
	if(slen < index + count)
	count = slen - index;
	
	char* result = newString ? malloc(slen) : string;
	
	memmove(string + index, string + index + count, slen - index);
	
	//Add null terminator
	string[slen - count] = 0;
	
	return result;
}


string_t* string_remove(string_t* string, uint32_t index, size_t count, bool newString)
{
	if(string->length < index + count)
	count = string->length - index;
	
	string_t* result = newString ? string_clone(string) : string;
	cstring_remove(result->buf, result->length, index, count, false);
	result->length -= count;
	
	string_add_null_terminator(string);
	
	return result;
}

//char* cstring_replace(char* string, size_t slen, size_t blen, char* oldItem, size_t oldLength, char* newItem, size_t newLength, bool ignoreCase, bool newString, size_t* out_newsize)
//{
	//int idx = 0;
	//uint32_t count = -1;
	//do 
	//{
		//count ++;
		//idx = cstring_indexOf(string, slen - idx, oldItem, oldLength, ignoreCase);
	//} while (idx != -1);
	//
	//size_t newsize = slen - (oldLength * count) + (newLength * count);
	//
	////Make sure buffer can hold new size
	//ASSERT((!newString && newsize <= blen) || newString);
	//
	////If newString, new buffer will be size of old buffer, or if newsize is bigger, newsize.
	//char* result = newString ? malloc(newsize > blen ? newsize : blen) : string;
//}

char* cstring_replace_char(char* string, size_t* slen, char oldItem, char newItem, bool ignoreCase, bool newString)
{
	char* result = newString ? malloc(*slen) : string;
	
	if(newItem != 0) //Replace all matches
	{
		switch(ignoreCase)
		{
			case false:
			for(uint32_t i = 0; i < *slen; i++)
			{
				if(result[i] == oldItem)
				*(result + i) = newItem;
			}
			break;
			
			case true:
			oldItem = char_toLower(oldItem);
			
			for(uint32_t i = 0; i < *slen; i++)
			{
				if(char_toLower(result[i]) == oldItem)
				*(result + i) = newItem;
			}
			break;
		}
	}
	else //Remove all matches
	{
		switch(ignoreCase)
		{
			case false:
			for(uint32_t i = 0; i < *slen; i++)
			{
				RedoOrdinal:
				if(result[i] == oldItem)
				{
					memcpy(result + i,	\
					result + i + 1,		\
					*slen - i - 1);
					
					(*slen)--;
					goto RedoOrdinal;
				}
				
			}
			break;
			
			case true:
			oldItem = char_toLower(oldItem);
			
			for(uint32_t i = 0; i < *slen; i++)
			{
				RedoOrdinalIgnoreCase:
				if(char_toLower(result[i]) == oldItem)
				{
					memcpy(result + i,	\
					result + i + 1,		\
					*slen -i - 1);
					
					(*slen)--;
					goto RedoOrdinalIgnoreCase;
				}
			}
			break;
		}
		
	}
	
	//Null terminator
	result[*slen] = 0;

	return result;
}

string_t* /*__attribute__((__always_inline__))*/ string_replace_char(string_t* string, char oldItem, char newItem, bool ignoreCase, bool newString)
{
	//return cstring_replace(string, oldItem, 1, newItem, 1, ignoreCase, newString);
	
	//if(newItem == 0)
	//return cstring_replace(string, &oldItem, 1, &newItem, 0, ignoreCase, newString );
	
	string_t* result = newString ? string_clone(string) : string;
	
	cstring_replace_char(result->buf, &result->length, oldItem, newItem, ignoreCase, false);
	
	//string_add_null_terminator(string);
	
	return result;
	
}

string_t* cstring_replace(string_t* string, char* oldItem, size_t oldLength, char* newItem, size_t newLength, bool ignoreCase, bool newString)
{
	#if CSTRING_0_LENGTH_GET_STRLEN == true
		cstring_0_length_get(oldItem, &oldLength);
		if(newItem != NULL) cstring_0_length_get(newItem, &newLength);	
		else newLength = 0;
	#else
		//If newItem is NULL, any character matching oldItem will be deleted.
		if(newItem == NULL) newLength = 0;
	#endif
	
	//if(oldLength == 1 && newLength == 1)
	//return string_replace_char(string, *oldItem, *newItem, ignoreCase, newString);	
	
	//New string capacity, will only change if oldLength is less than newLength
	size_t newsize = string->length; 
	
	string_t* result = newString ? new_string(-1) : string;
	
	int index = 0;
	uint32_t processed = 0;
	uint32_t count = -1;
	
	//As original length is smaller than the new length,
	//we will first get the new total size to see if we need to reallocate memory,
	//and so we only need to do it once.
	
	if(oldLength < newLength)
	{
		count = 0;
		while(processed < string->length && (index = cstring_indexOf(string->buf + processed, string->length - processed, oldItem, oldLength, ignoreCase)) != -1)
		{
			processed += index + 1;
			count++;
		}
		
		newsize = string->length - (oldLength * count) + (newLength * count);
		
		CSTRING_ASSERT_MAX_LENGTH(newsize);

		goto EnsureCapacity;
	}
	
	if(!newString)
	goto Replacing;
	
	EnsureCapacity:
	string_ensure_capacity(result, newsize);	
	
	
	if(newString)
	{
		memcpy(result->buf, string->buf, string->length);
	}
	
	//Nothing to replace, return string.
	if(count == 0)
		return result;
	
	Replacing:
	{
		index = 0;
		//int offset = 0;
		processed = 0;
		int difference = newLength - oldLength;
		
		while(processed < newsize && (index = cstring_indexOf(result->buf + processed, result->length - processed, oldItem, oldLength, ignoreCase)) != -1)
		{
			processed += index;
			
			//If oldLength is different than newLength, we must shift the string in memory.
			if(difference != 0)
			{
				memmove(result->buf + processed + newLength,	\
				result->buf + processed + oldLength,			\
				result->length - processed - oldLength);
				
				result->length += difference;
			}
			
			//Replace old item with new item.
			memcpy(result->buf + processed, newItem, newLength);
			
			if(difference > 0)
				processed += newLength;
		}
	}
	
	string_add_null_terminator(result);
	
	return result;
	
}



string_t* __attribute__((__always_inline__)) string_replace(string_t* string, string_t* oldItem, string_t* newItem, bool ignoreCase, bool newString)
{
	return cstring_replace(string, oldItem->buf, oldItem->length, newItem->buf, newItem->length, ignoreCase, newString);
}

string_t** string_split(string_t* string, char* splitter, size_t splitterLength, uint32_t count, string_split_options_t options, int* out_count)
{
	#if CSTRING_0_LENGTH_GET_STRLEN == true
	cstring_0_length_get(splitter, &splitterLength);
	#endif
	
	uint32_t matches = cstring_matchCount(string->buf, string->length, splitter, splitterLength, false);
	
	if(matches < count || count == 0)
	count = matches;
	
	string_t** splits = malloc(sizeof(string_t*) * count);
	
	int32_t index = 0;
	//int32_t lastIndex = 0;
	uint32_t valid_count = 0;
	uint32_t processed = 0;
	bool valid;
	
	while(processed < string->length)
	{
		index = cstring_indexOf(string->buf + processed, string->length - processed, splitter, splitterLength, false);
		
		if(index == -1)
		{
			//No more matches, get the length to end of the string.
			//This will be the last string we need to sub.
			index = string->length - processed;
		}
		
		valid = true;
		//size_t split_length = (index + processed) - processed;
		string_t* split = string_subString(string, processed, index); /*new_string(split_length);*/		
		splits[valid_count] = split;
		
		//Replaced with substring
		//split->length = split_length;		
		//memcpy(split->buf, string->buf + lastIndex, split_length);
		
		switch(options)
		{
			
			case STRING_SPLIT_REMOVE_EMPTY_ENTRIES:
			RemoveEmptyEntries:
			if(index == 0)
			{
				string_delete(split);		
				valid = false;
			}				
			break;
			
			case STRING_SPLIT_TRIM_ENTRIES:
			string_trim(split, whitespace_characters, sizeof(whitespace_characters), false);
			break;
			
			case (STRING_SPLIT_REMOVE_EMPTY_ENTRIES | STRING_SPLIT_TRIM_ENTRIES):
			string_trim(split, whitespace_characters, sizeof(whitespace_characters), false);
			goto RemoveEmptyEntries;
		}
		
		//string_add_null_terminator(split);
		
		valid_count += valid;
		//lastIndex = index;
		
		index++;
		processed += index;
	}
	
	if(valid_count != count)
	splits = realloc(splits, sizeof(string_t*) * valid_count);
	
	*out_count = valid_count;

	return splits;
}

string_t** __attribute__((__always_inline__)) string_split_char(string_t* string, char splitter, uint32_t count, string_split_options_t options, int* out_count)
{
	return string_split(string, &splitter, 1, count, options, out_count);
}

string_t* cstring_subString(char* string, size_t length, uint32_t index, uint32_t count)
{
	#if CSTRING_0_LENGTH_GET_STRLEN == true
	cstring_0_length_get(string, &length);
	#endif
		
	if(length < index + count)
	count = length - index;
	
	string_t* sub = new_string(count);
	
	string_set_buf(sub, string + index, count);
	//memcpy(sub->buf, string->buf + index, count);
	//sub->length = count;
	
	string_add_null_terminator(sub);
	
	return sub;
}

string_t* string_subString(string_t* string, uint32_t index, uint32_t count)
{
	if(string->length < index + count)
	count = string->length - index;
	
	string_t* sub = new_string(count);
	
	string_set_buf(sub, string->buf + index, count);	
	//memcpy(sub->buf, string->buf + index, count);
	//sub->length = count;
	
	string_add_null_terminator(sub);
	
	return sub;
}

void cstring_toLower(char* string, size_t length)
{
	#if CSTRING_0_LENGTH_GET_STRLEN == true
	cstring_0_length_get(string, &length);
	#endif
	
	for(uint32_t i = 0; i < length; i++)
	{
		string[i] = char_toLower(string[i]);
	}
}

string_t* /*__attribute__((__always_inline__))*/ string_toLower(string_t* string, bool newString)
{
	string_t* result = newString ? string_clone(string) : string;
	cstring_toLower(result->buf, result->length);
	return result;
}

void cstring_toUpper(char* string, size_t length)
{
	#if CSTRING_0_LENGTH_GET_STRLEN == true
	cstring_0_length_get(string, &length);
	#endif
	
	for(uint32_t i = 0; i < length; i++)
	{
		string[i] = char_toUpper(string[i]);
	}
}

string_t* /*__attribute__((__always_inline__))*/ string_toUpper(string_t* string, bool newString)
{
	string_t* result = newString ? string_clone(string) : string;
	cstring_toUpper(result->buf, result->length);
	return result;
}


string_t* string_trim(string_t* string, char* chars, uint32_t count, bool newString)
{
	string_t* result = newString ? string_clone(string) : string;
	string_trimStart(result, chars, count, false);
	string_trimEnd(result, chars, count, false);
	return result;
}

string_t* __attribute__((__always_inline__)) string_trim_char(string_t* string, char c, bool newString)
{
	return string_trim(string, &c, 1, newString);
}


string_t* string_trimStart(string_t* string, char* chars, uint32_t count, bool newString)
{
	string_t* result = newString ? string_clone(string) : string;
	
	if(chars == NULL)
	{
		chars = whitespace_characters;
		count = sizeof(whitespace_characters);
	}
	
	uint32_t i, b;
	for(i = 0; i < result->length; i++)
	{
		for(b = 0; b < count; b++)
		{
			if(result->buf[i] == chars[b]) break;
		}
		
		if(b == count) break;		
	}
	
	memcpy(result->buf, result->buf + i, result->length - i);
	result->length -= i;	
	string_add_null_terminator(result);
	return result;
}

string_t* __attribute__((__always_inline__)) string_trimStart_char(string_t* string, char c, bool newString)
{
	return string_trimStart(string, &c, 1, newString);
}

string_t* string_trimEnd(string_t* string, char* chars, uint32_t count, bool newString)
{
	string_t* result = newString ? string_clone(string) : string;
	
	if(chars == NULL)
	{
		chars = whitespace_characters;
		count = sizeof(whitespace_characters);
	}
	
	uint32_t i, c, b;
	for(i = result->length - 1, c = 0; i < result->length; i--, c++)
	{
		for(b = 0; b < count; b++)
		{
			if(result->buf[i] == chars[b]) break;
		}
		if(b == count) break;	
	}
	
	result->length -= c;
	string_add_null_terminator(result);
	return result;
}

string_t* __attribute__((__always_inline__))string_trimEnd_char(string_t* string, char c, bool newString)
{
	return string_trimEnd(string, &c, 1, newString);
}

//slen is size of string, not buffer
bool __attribute__((__always_inline__)) cstring_equals(char* string, size_t slen, const char* compare, size_t clen, bool ignoreCase)
{
	#if CSTRING_0_LENGTH_GET_STRLEN == true
	cstring_0_length_get(string, &slen);
	cstring_0_length_get(compare, &clen);
	#endif

	if(slen != clen) return false;
	return cstring_compare(string, compare, slen, ignoreCase) == 0;
	//#if CSTRING_0_LENGTH_GET_STRLEN == true
	//cstring_0_length_get(string, &slen);
	//cstring_0_length_get(compare, &clen);
	//#endif
	//
	////Not same length, couldn't be equal.
	//if(slen != clen) return false;
	//
	//switch(ignoreCase)
	//{
		//case false:
		//for(uint32_t i = 0; i < clen; i++)
		//{
			//if(string[i] != compare[i]) return false;
		//}
		//break;
		//
		//case true:
		//for(uint32_t i = 0; i < clen; i++)
		//{
			//if(char_toLower(string[i]) != char_toLower(compare[i])) return false;
		//}
		//break;
	//}
	//
	//return true;
}

bool __attribute__((__always_inline__)) string_equals_charp(string_t* string, const char* compare, size_t clen, bool ignoreCase)
{
	return cstring_equals(string->buf, string->length, compare, clen, ignoreCase);
}

bool __attribute__((__always_inline__)) string_equals(string_t* string, string_t* compare, bool ignoreCase)
{
	return cstring_equals(string->buf, string->length, compare->buf, compare->length, ignoreCase);
}
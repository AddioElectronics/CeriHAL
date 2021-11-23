
#ifndef CSTRING_H_
#define CSTRING_H_

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>

#include "cstring_config.h"

typedef struct  
{
	char* buf;
	uint16_t length;	//Size of string
	size_t capacity;	//Size of buffer
}string_t;

//Flags
typedef enum string_split_options
{
	STRING_SPLIT_NONE = 0,
	STRING_SPLIT_REMOVE_EMPTY_ENTRIES = 1,
	STRING_SPLIT_TRIM_ENTRIES = 2	
}string_split_options_t;

//typedef struct string_split_options
//{
	//bool remove_empty_entries : 1;
	//bool trim_entries : 1;
//}string_split_options_t;
//typedef uint8_t string_split_options_t;

/*
	Replaced with "bool ignoreCase"
	If other string_comparison enums are supported they will be changed back.
*/
//enum string_comparison
//{
	////Unsupported
	////STRING_COMPARISON_CURRENTCULTURE,
	////STRING_COMPARISON_CURRENTCULTUREIGNORECASE,
	////STRING_COMPARISON_INVARIANTCULTURE,
	////STRING_COMPARISON_INVARIANTCULTUREIGNORECASE,
	//STRING_COMPARISON_ORDINAL = 4,
	//STRING_COMPARISON_ORDINALIGNORECASE = 5
//};



void string_init(string_t* string, int capacity);
string_t* new_string(int capacity);

string_t* string_clone(string_t* string);

void string_set_buf(string_t* string, char* buf, size_t length);
void string_set(string_t* string, char* buf);

void string_delete(string_t* string);

bool string_ensure_capacity(); 

void string_shrink_to_fit();

void cstring_append(string_t* a, char* b, size_t length);
inline void string_append(string_t* a, string_t* b);
string_t* cstring_concat(string_t* a, char* b, size_t length);
inline string_t* string_concat(string_t* a, string_t* b);

string_t* string_vformat(string_t* format, bool newString, va_list ap);
string_t* string_format(string_t* format, bool newString, ...);

int cstring_indexOf(char* string, size_t slen, char* compare, size_t clen, bool ignoreCase);
inline int string_indexOf_char(string_t* string, char compare, bool ignoreCase);
inline int string_indexOf_charp(string_t* string,  char* compare, size_t clen, bool ignoreCase);
inline int string_indexOf(string_t* string,  string_t* compare, bool ignoreCase);

int cstring_lastIndexOf(char* string, size_t slen, char* compare, size_t clen, bool ignoreCase);
inline int string_lastIndexOf_char(string_t* string, char compare, bool ignoreCase);
inline int string_lastIndexOf_charp(string_t* string, char* compare, size_t clen, bool ignoreCase);
inline int string_lastIndexOf(string_t* string, string_t* compare, bool ignoreCase);

int cstring_indexOfAny(char* string, size_t slen, char* compare, int cmpCount);
inline int string_indexOfAny(string_t* string,  char* compare, int cmpCount);

int cstring_lastIndexOfAny(char* string, size_t slen, char* compare, int cmpCount);
inline int string_lastIndexOfAny(string_t* string,  char* compare, int cmpCount);

uint32_t cstring_matchCount(char* string, size_t slen, char* compare, size_t clen, bool ignoreCase);
inline uint32_t string_matchCount_char(string_t* string, char compare, bool ignoreCase);
inline uint32_t string_matchCount_charp(string_t* string, char* compare, size_t clen, bool ignoreCase);
inline uint32_t string_matchCount(string_t* string, string_t* compare, bool ignoreCase);

bool cstring_isEmpty(char* string, size_t slen);
inline bool string_isEmpty(string_t* string);

bool cstring_isEmptyOrWhitespace(char* string, size_t slen);
inline bool string_isEmptyOrWhitespace(string_t* string);

string_t* cstring_insert(string_t* string, char* insert, size_t length, uint32_t index, bool newString);
//string_t* cstring_insert(char* string, size_t slen, char* insert, size_t length, uint32_t index, bool newString);
inline string_t* string_insert_char(string_t* string, char insert, uint32_t index, bool newString);
inline string_t* string_insert(string_t* string, string_t* insert, uint32_t index, bool newString);

string_t* cstring_join(char* seperator, size_t seplen, string_t** values, uint32_t count);
inline string_t* string_join_char(char seperator, string_t** values, uint32_t count);
inline string_t* string_join(string_t* seperator, string_t** values, uint32_t count);

inline bool cstring_contains(char* string, size_t slen, char* compare, size_t clen, bool ignoreCase);
inline bool string_contains_char(string_t* string, char compare, bool ignoreCase);
inline bool string_contains_charp(string_t* string, char* compare, size_t clen, bool ignoreCase);
inline bool string_contains(string_t* string, string_t* compare, bool ignoreCase);

int cstring_compare(char* string, char* compare, size_t length, bool ignoreCase);
inline int string_compare(string_t* string, string_t* compare, uint32_t length, bool ignoreCase);

inline bool cstring_startsWith(char* string, size_t slen, char* compare, size_t clen, bool ignoreCase);
inline bool string_startsWith_char(string_t* string, char compare, bool ignoreCase);
inline bool string_startsWith_charp(string_t* string, char* compare, size_t clen, bool ignoreCase);
inline bool string_startsWith(string_t* string, string_t* compare, bool ignoreCase);

inline bool cstring_endsWith(char* string, size_t slen, char* compare, size_t clen, bool ignoreCase);
inline bool string_endsWith_char(string_t* string, char compare, bool ignoreCase);
inline bool string_endsWith_charp(string_t* string, char* compare, size_t clen, bool ignoreCase);
inline bool string_endsWith(string_t* string, string_t* compare, bool ignoreCase);

string_t* string_padLeft(string_t* string, uint32_t count, char c, bool newString);
string_t* string_padRight(string_t* string, uint32_t count, char c, bool newString);

char* cstring_remove(char* string, size_t slen, uint32_t index, size_t count, bool newString);
string_t* string_remove(string_t* string, uint32_t index, size_t count, bool newString);


char* cstring_replace_char(char* string, size_t* slen, char oldItem, char newItem, bool ignoreCase, bool newString);
/*inline*/ string_t* string_replace_char(string_t* string, char oldItem, char newItem, bool ignoreCase, bool newString);
string_t* cstring_replace(string_t* string, char* oldItem, size_t oldLength, char* newItem, size_t newLength, bool ignoreCase, bool newString);
//char* cstring_replace(char* string, size_t slen, char* oldItem, size_t oldLength, char* newItem, size_t newLength, bool ignoreCase, bool newString);
inline string_t* string_replace(string_t* string, string_t* oldItem, string_t* newItem, bool ignoreCase, bool newString);

string_t** string_split(string_t* string, char* splitter, size_t splitterLength, uint32_t count, string_split_options_t options, int* out_count);
inline string_t** string_split_char(string_t* string, char splitter, uint32_t count, string_split_options_t options, int* out_count);

string_t* cstring_subString(char* string, size_t length, uint32_t index, uint32_t count);
string_t* string_subString(string_t* string, uint32_t index, uint32_t count);


void cstring_toLower(char* string, size_t length);
string_t* string_toLower(string_t* string, bool newString);

void cstring_toUpper(char* string, size_t length);
string_t*  string_toUpper(string_t* string, bool newString);


string_t*  string_trim(string_t* string, char* chars, uint32_t count, bool newString);
string_t*  string_trim_char(string_t* string, char c, bool newString);

string_t*  string_trimStart(string_t* string, char* chars, uint32_t count, bool newString);
string_t*  string_trimStart_char(string_t* string, char c, bool newString);

string_t*  string_trimEnd(string_t* string, char* chars, uint32_t count, bool newString);
string_t*  string_trimEnd_char(string_t* string, char c, bool newString);

inline bool cstring_equals(char* string, size_t slen, const char* compare, size_t clen, bool ignoreCase);
inline bool string_equals_charp(string_t* string, const char* compare, size_t clen, bool ignoreCase);
inline bool string_equals(string_t* string, string_t* compare, bool ignoreCase);

#endif /* CSTRING_H_ */

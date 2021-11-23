#include "char_helper.h"

char char_toLower(char c)
{
	if(c >= 'A' && c <= 'Z')
	{
		return c + 32;
	}
	else
	{
		return c;
	}
}

char char_toUpper(char c)
{
	if(c >= 'a' && c <= 'z')
	{
		return c - 32;
	}
	else
	{
		return c;
	}
}

bool char_equals(char c, const char* characters, uint32_t count)
{
	if(count == 0) count = strlen(characters);
	
	for(uint32_t i = 0; i < count; i++)
	{
		if(c == characters[i]) return true;
	}
	
	return false;
}
/*
 * cstrings.h
 *
 * Created: 11.12.2019 21:30:24
 *  Author: Ilya Pikin
 */ 

#ifndef _UTILS_H_
#define _UTILS_H_

#include "avr/io.h"
#include <stdbool.h>
#include <string.h>

#define Utils_Round(__VALUE__)              (((__VALUE__) < 0.0f) ? (int)((__VALUE__) - 0.5f) : (int)((__VALUE__) + 0.5f))
#define Utils_CheckIfCharIsNumber(__CHAR__) ((__CHAR__) >= '0' && (__CHAR__) <= '9')
#define Utils_CharToNumber(__CHAR__)        ((__CHAR__) - '0')

bool Utils_CompareStrings(const char * str1, const char * str2, uint16_t length);
uint16_t Utils_GetStringLength(const char * str);
uint16_t Utils_GetStringLengthLimit(const char * str, uint16_t limit);
uint16_t Utils_ParseUnsignedInt(const char * str);

#endif

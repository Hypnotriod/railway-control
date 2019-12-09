#ifndef _UTILS_H_
#define _UTILS_H_

#include "avr/io.h"
#include <stdbool.h>
#include <string.h>

#define Utils_Round(__VALUE__) (((__VALUE__) < 0.0f) ? (int)((__VALUE__) - 0.5f) : (int)((__VALUE__) + 0.5f))

bool Utils_CompareStrings(const char * str1, const char * str2, uint16_t length);
uint16_t Utils_GetStringLength(const char * str);
uint16_t Utils_GetStringLengthLimit(const char * str, uint16_t limit);
int32_t Utils_ParseInt(const char * str);

#endif

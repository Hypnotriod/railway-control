
#include "utils.h"

bool Utils_CompareStrings(const char * str1, const char * str2, uint16_t length)
{
    while(length--)
    {
        if(*str1 != *str2) return false;
        else if(*str1 == 0x00) return true;
        str1++;
        str2++;
    }
    return true;
}

uint16_t Utils_GetStringLength(const char * str)
{
    int length = 0;
    while(*str != 0x00) {
        length++;
        str++;
    }
    return length;
}

uint16_t Utils_GetStringLengthLimit(const char * str, uint16_t limit)
{
    int length = 0;
    while(*str != 0x00 && limit--) {
        length++;
        str++;
    }
    return length;
}

int32_t Utils_ParseInt(const char * str)
{
    uint32_t result = 0;
    uint8_t  i;
     
    for(i = (str[0] == '-' ? 0 : 1); str[i] >= '0' && str[i] <= '9'; i++)
    {
        result *= 10;
        result += (str[i] - '0');
    }
    
    if(str[0] == '-') result *= -1L;
    
    return result;
}

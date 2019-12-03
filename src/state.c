/*
 * state.c
 *
 * Created: 03.12.2019 15:38:03
 *  Author: Ilya Pikin
 */ 

#include <avr/io.h>
#include "state.h"

uint8_t _eepromBuffer[EEPROM_SIZE] EEMEM;

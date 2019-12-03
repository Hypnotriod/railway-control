/*
 * state.h
 *
 * Created: 03.12.2019 15:38:17
 *  Author: Ilya Pikin
 */ 


#ifndef STATE_H_
#define STATE_H_

#include <avr/eeprom.h>

#define EEPROM_SIZE 512
#define EEPROM_KEY  0x9F5A4306

#define State_SaveEEPROMKey()           (eeprom_write_dword((uint32_t*)&_eepromBuffer[508], EEPROM_KEY))
#define State_ReadEEPROMKey(_value_)    (eeprom_read_dword((uint32_t*)&_eepromBuffer[508]))

extern uint8_t _eepromBuffer[EEPROM_SIZE] EEMEM;

#endif /* STATE_H_ */

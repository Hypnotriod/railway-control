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

#define State_SaveEEPROMKey()           (eeprom_write_dword((uint32_t*)&eepromBuffer[508], EEPROM_KEY))
#define State_ReadEEPROMKey(_value_)    (eeprom_read_dword((uint32_t*)&eepromBuffer[508]))

void State_Init(void);
void State_Reset(void);

void State_SaveSensorRailwayIndex(uint8_t sensorIndex, uint8_t railwayIndex);
void State_SaveSensorTimeoutSeconds(uint8_t sensorIndex, uint16_t timeoutSeconds);
void State_SaveSensorDirection(uint8_t sensorIndex, uint8_t direction);
void State_SaveRailwaySpeed(uint8_t railwayIndex, uint8_t direction);

uint8_t State_ReadSensorRailwayIndex(uint8_t sensorIndex);
uint16_t State_ReadSensorTimeoutSeconds(uint8_t sensorIndex);
uint8_t State_ReadSensorDirection(uint8_t sensorIndex);
uint8_t State_ReadRailwaySpeed(uint8_t railwayIndex);

extern uint8_t eepromBuffer[EEPROM_SIZE] EEMEM;

#endif /* STATE_H_ */

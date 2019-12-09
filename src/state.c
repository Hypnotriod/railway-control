/*
* state.c
*
* Created: 03.12.2019 15:38:03
*  Author: Ilya Pikin
*/

#include <avr/io.h>
#include "state.h"

uint8_t eepromBuffer[EEPROM_SIZE] EEMEM;

void State_SaveSensorRailwayIndex(uint8_t sensorIndex, uint8_t railwayIndex)
{
    eeprom_write_byte((uint8_t*)&eepromBuffer[0 + sensorIndex], ((uint8_t)railwayIndex)); // Bytes 0 - 11
}

void State_SaveSensorTimeoutSeconds(uint8_t sensorIndex, uint16_t timeoutSeconds)
{
    eeprom_write_word((uint16_t*)&eepromBuffer[12 + (sensorIndex * 2)], ((uint16_t)timeoutSeconds)); // Bytes 12 - 35
}

uint8_t State_ReadSensorRailwayIndex(uint8_t sensorIndex)
{
    return eeprom_read_byte((uint8_t*)&eepromBuffer[0 + sensorIndex]);
}

uint16_t State_ReadSensorTimeoutSeconds(uint8_t sensorIndex)
{
    return eeprom_read_word((uint16_t*)&eepromBuffer[12 + (sensorIndex * 2)]);
}

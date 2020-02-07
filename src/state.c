/*
* state.c
*
* Created: 03.12.2019 15:38:03
*  Author: Ilya Pikin
*/

#include <avr/io.h>
#include "state.h"
#include "automation.h"

#define State_SaveEEPROMKey()           (eeprom_write_dword((uint32_t*)&eepromBuffer[508], EEPROM_KEY))
#define State_ReadEEPROMKey(_value_)    (eeprom_read_dword((uint32_t*)&eepromBuffer[508]))

uint8_t eepromBuffer[EEPROM_SIZE] EEMEM;

void State_Init(void)
{
    if(State_ReadEEPROMKey() != EEPROM_KEY)
    {
        State_Reset();
    }
}

void State_Reset(void)
{
    int i;
    
    for (i = 0; i < AUTOMATION_RAILWAYS_NUM; i++)
    {
        State_SaveRailwaySpeed(i, 0);
        State_SaveRailwayActivationTimeoutSeconds(i, 0);
    }
    
    for (i = 0; i < AUTOMATION_SENSORS_NUM; i++)
    {
        State_SaveSensorRailwayIndex(i, 0);
        State_SaveSensorRailwayStopTimeoutSeconds(i, 0);
        State_SaveSensorRailwayDirection(i, 0);
    }
    
    State_SaveEEPROMKey();
}

void State_SaveSensorRailwayIndex(uint8_t sensorIndex, uint8_t railwayIndex)
{
    eeprom_write_byte((uint8_t*)&eepromBuffer[0 + sensorIndex], ((uint8_t)railwayIndex)); // Bytes 0 - 11
}

uint8_t State_ReadSensorRailwayIndex(uint8_t sensorIndex)
{
    return eeprom_read_byte((uint8_t*)&eepromBuffer[0 + sensorIndex]);
}


void State_SaveSensorRailwayStopTimeoutSeconds(uint8_t sensorIndex, uint16_t timeoutSeconds)
{
    eeprom_write_word((uint16_t*)&eepromBuffer[12 + (sensorIndex * 2)], ((uint16_t)timeoutSeconds)); // Bytes 12 - 35
}

uint16_t State_ReadSensorRailwayStopTimeoutSeconds(uint8_t sensorIndex)
{
    return eeprom_read_word((uint16_t*)&eepromBuffer[12 + (sensorIndex * 2)]);
}


void State_SaveSensorRailwayDirection(uint8_t sensorIndex, uint8_t direction)
{
    eeprom_write_byte((uint8_t*)&eepromBuffer[36 + sensorIndex], ((uint8_t)direction)); // Bytes 36 - 47
}

uint8_t State_ReadSensorRailwayDirection(uint8_t sensorIndex)
{
    return eeprom_read_byte((uint8_t*)&eepromBuffer[36 + sensorIndex]);
}


void State_SaveRailwaySpeed(uint8_t railwayIndex, uint8_t speed)
{
    eeprom_write_byte((uint8_t*)&eepromBuffer[48 + railwayIndex], ((uint8_t)speed)); // Bytes 48 - 55
}

uint8_t State_ReadRailwaySpeed(uint8_t railwayIndex)
{
    return eeprom_read_byte((uint8_t*)&eepromBuffer[48 + railwayIndex]);
}


void State_SaveRailwayActivationTimeoutSeconds(uint8_t railwayIndex, uint16_t timeoutSeconds)
{
    eeprom_write_word((uint16_t*)&eepromBuffer[56 + (railwayIndex * 2)], ((uint16_t)timeoutSeconds)); // Bytes 56 - 67
}

uint16_t State_ReadRailwayActivationTimeoutSeconds(uint8_t railwayIndex)
{
    return eeprom_read_word((uint16_t*)&eepromBuffer[56 + (railwayIndex * 2)]);
}
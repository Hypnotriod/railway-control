/*
* state.c
*
* Created: 03.12.2019 15:38:03
*  Author: Ilya Pikin
*/

#include <avr/io.h>
#include "state.h"
#include "automation.h"

#define State_SaveEEPROMKey() (eeprom_write_dword((uint32_t*)&eepromBuffer[508], EEPROM_KEY))
#define State_ReadEEPROMKey() (eeprom_read_dword((uint32_t*)&eepromBuffer[508]))

uint8_t eepromBuffer[EEPROM_SIZE] EEMEM;

void State_Init(void)
{
    
}

void State_Reset(void)
{
    
}

void State_SaveSensorRailwayIndex(uint8_t sensorIndex, uint8_t railwayIndex)
{

}

uint8_t State_ReadSensorRailwayIndex(uint8_t sensorIndex)
{
	switch (sensorIndex) {
		case 0: return 0;
		case 1: return 1;
		case 2: return 2;
		case 3: return 2;
		default: return 0;
	}
}


void State_SaveSensorRailwayStopTimeoutSeconds(uint8_t sensorIndex, uint16_t timeoutSeconds)
{

}

uint16_t State_ReadSensorRailwayStopTimeoutSeconds(uint8_t sensorIndex)
{
	switch (sensorIndex) {
		case 0: return 30;
		case 1: return 35;
		case 2: return 40;
		case 3: return 45;
		default: return 0;
	}
}


void State_SaveSensorRailwayDirection(uint8_t sensorIndex, uint8_t direction)
{

}

uint8_t State_ReadSensorRailwayDirection(uint8_t sensorIndex)
{
	switch (sensorIndex) {
		case 0: return 0;
		case 1: return 0;
		case 2: return 0;
		case 3: return 0;
		default: return 0;
	}
}


void State_SaveRailwaySpeed(uint8_t railwayIndex, uint8_t speed)
{

}

uint8_t State_ReadRailwaySpeed(uint8_t railwayIndex)
{
	switch (railwayIndex) {
		case 0: return 100;
		case 1: return 100;
		case 2: return 100;
		default: return 0;
	}
}


void State_SaveRailwayActivationTimeoutSeconds(uint8_t railwayIndex, uint16_t timeoutSeconds)
{

}

uint16_t State_ReadRailwayActivationTimeoutSeconds(uint8_t railwayIndex)
{
	switch (railwayIndex) {
		case 0: return 15;
		case 1: return 15;
		case 2: return 15;
		default: return 0;
	}
}

/*
 * ui.c
 *
 * Created: 25.11.2019 21:04:31
 *  Author: Ilya Pikin
 */ 

#include <stdint.h>
#include <avr/io.h>
#include <stdbool.h>
#include "ui.h"
#include "adc.h"
#include "motors.h"
#include "automation.h"

uint16_t knobsADCValues[UI_KNOBS_NUM] = {0};
enum UI_KnobDirectionEnum knobsDirections[UI_KNOBS_NUM] = {UI_KNOB_DIR_BOUTH_WAYS};
bool manualControlIsOn = false;

void updateKnobs(void);
void updateMotorsWithKnobsValues(void);

void UI_Init(void) 
{
	UI_MANUAL_CONTROL_MODE_DDR &= (~(1 << UI_MANUAL_CONTROL_MODE_INDEX));
	UI_MANUAL_CONTROL_MODE_PORT |= (1 << UI_MANUAL_CONTROL_MODE_INDEX);
}

void UI_Update(void) 
{
	if (UI_IsManualControlModeOn())
	{
		if (manualControlIsOn == false) {
			manualControlIsOn = true;
			UI_ResetKnobs();
		}
		updateKnobs();
		updateMotorsWithKnobsValues();
	}
	else
	{
		if (manualControlIsOn == true) {
			manualControlIsOn = false;
		}
	}
}

void UI_ResetKnobs(void)
{
	uint8_t i;
	uint16_t knobValue;
	
	for (i = 0; i < UI_KNOBS_NUM; i++ )
	{
		knobValue = ADC_Read((UI_KNOBS_NUM - 1) - i);
		knobsADCValues[i] = UI_KNOBS_DEFAULT_ADC_VALUE;
		
		if (knobValue < knobsADCValues[i])
		{
			knobsDirections[i] = UI_KNOB_DIR_UP;
		}
		else if (knobValue > knobsADCValues[i])
		{
			knobsDirections[i] = UI_KNOB_DIR_DOWN;
		}
		else 
		{
			knobsDirections[i] = UI_KNOB_DIR_BOUTH_WAYS;
		}
	}
}

void updateKnobs(void) 
{
	uint8_t i;
	uint16_t knobValue;
	
	for (i = 0; i < UI_KNOBS_NUM; i++) 
	{
		knobValue = ADC_Read((UI_KNOBS_NUM - 1) - i);
		
		if (knobsDirections[i] == UI_KNOB_DIR_UP && knobValue >= knobsADCValues[i]) 
		{
			knobsADCValues[i] = knobValue;
			knobsDirections[i] = UI_KNOB_DIR_BOUTH_WAYS;
		}
		else if (knobsDirections[i] == UI_KNOB_DIR_DOWN && knobValue <= knobsADCValues[i]) 
		{
			knobsADCValues[i] = knobValue;
			knobsDirections[i] = UI_KNOB_DIR_BOUTH_WAYS;
		}
		else 
		{
			knobsADCValues[i] = knobValue;
		}
	}
}

void updateMotorsWithKnobsValues(void)
{
	uint8_t i;
	float value;
	
	for (i = 0; i < UI_KNOBS_NUM; i++ ) 
	{
		value = knobsADCValues[i];
		value = (value - (float)ADC_VALUE_MID) / (float)ADC_VALUE_MID;
		
		if (value < -UI_KNOBS_DEAD_ZONE) 
		{
			value = -value / (1.0f + UI_KNOBS_MIN_VALUE) + UI_KNOBS_MIN_VALUE;
			Motors_SetSpeed(i, value);
			Motors_SetDirection(i, MOTORS_DIRECTION_BACKWARD);
		}
		else if (value > UI_KNOBS_DEAD_ZONE)
		{
			value = value / (1.0f + UI_KNOBS_MIN_VALUE) + UI_KNOBS_MIN_VALUE;
			Motors_SetSpeed(i, value);
			Motors_SetDirection(i, MOTORS_DIRECTION_FORWARD);
		}
		else
		{
			Motors_SetSpeed(i, 0);
		}
	}
}


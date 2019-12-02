/*
 * motors.c
 *
 * Created: 25.11.2019 22:30:34
 *  Author: Ilya Pikin
 */ 

#include <avr/io.h>
#include "motors.h"
#include "pwm.h"

void Motors_Init(void) 
{
	MOTORS_DIR1_DDR	|= (1 << MOTORS_DIR1_INDEX);
	MOTORS_DIR2_DDR	|= (1 << MOTORS_DIR2_INDEX);
	MOTORS_DIR3_DDR	|= (1 << MOTORS_DIR3_INDEX);
	MOTORS_DIR4_DDR	|= (1 << MOTORS_DIR4_INDEX);
	MOTORS_DIR5_DDR	|= (1 << MOTORS_DIR5_INDEX);
	MOTORS_DIR6_DDR	|= (1 << MOTORS_DIR6_INDEX);
}

void Motors_SetSpeed(uint8_t motorIndex, float speed)
{
	uint16_t speedDiscrete = speed * PWM_TOP;
	switch (motorIndex)
	{
		case 0:
			PWM_OC1B_SetDuty(speedDiscrete);
			break;
		
		case 1:
			PWM_OC1C_SetDuty(speedDiscrete);
			break;
			
		case 2:
			PWM_OC3A_SetDuty(speedDiscrete);
			break;
			
		case 3:
			PWM_OC3B_SetDuty(speedDiscrete);
			break;
		
		case 4:
			PWM_OC3C_SetDuty(speedDiscrete);
			break;
		
		case 5:
			PWM_OC1A_SetDuty(speedDiscrete);
			break;
	}
	
}

void Motors_SetDirection(uint8_t motorIndex, enum Motors_Direction direction)
{
	if (direction == MOTORS_DIRECTION_FORWARD)
	{
		switch (motorIndex)
		{
			case 0:
				MOTORS_DIR1_PORT |= (1 << MOTORS_DIR1_INDEX);
				break;
			
			case 1:
				MOTORS_DIR2_PORT |= (1 << MOTORS_DIR2_INDEX);
				break;
			
			case 2:
				MOTORS_DIR3_PORT |= (1 << MOTORS_DIR3_INDEX);
				break;
			
			case 3:
				MOTORS_DIR4_PORT |= (1 << MOTORS_DIR4_INDEX);
				break;
			
			case 4:
				MOTORS_DIR5_PORT |= (1 << MOTORS_DIR5_INDEX);
				break;
			
			case 5:
				MOTORS_DIR6_PORT |= (1 << MOTORS_DIR6_INDEX);
				break;
		}
	} 
	else 
	{
		switch (motorIndex)
		{
			case 0:
				MOTORS_DIR1_PORT &= ~(1 << MOTORS_DIR1_INDEX);
				break;
			
			case 1:
				MOTORS_DIR2_PORT &= ~(1 << MOTORS_DIR2_INDEX);
				break;
			
			case 2:
				MOTORS_DIR3_PORT &= ~(1 << MOTORS_DIR3_INDEX);
				break;
			
			case 3:
				MOTORS_DIR4_PORT &= ~(1 << MOTORS_DIR4_INDEX);
				break;
			
			case 4:
				MOTORS_DIR5_PORT &= ~(1 << MOTORS_DIR5_INDEX);
				break;
			
			case 5:
				MOTORS_DIR6_PORT &= ~(1 << MOTORS_DIR6_INDEX);
				break;
		}
	}
}

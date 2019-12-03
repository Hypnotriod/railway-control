/*
* motors.h
*
* Created: 25.11.2019 22:30:24
*  Author: Ilya Pikin
*/

#ifndef MOTORS_H_
#define MOTORS_H_

#include <stdint.h>

#define MOTORS_DIR1_DDR		DDRB
#define MOTORS_DIR1_PORT	PORTB
#define MOTORS_DIR1_INDEX	3
#define MOTORS_DIR2_DDR		DDRB
#define MOTORS_DIR2_PORT	PORTB
#define MOTORS_DIR2_INDEX	4
#define MOTORS_DIR3_DDR		DDRE
#define MOTORS_DIR3_PORT	PORTE
#define MOTORS_DIR3_INDEX	6
#define MOTORS_DIR4_DDR		DDRE
#define MOTORS_DIR4_PORT	PORTE
#define MOTORS_DIR4_INDEX	7
#define MOTORS_DIR5_DDR		DDRB
#define MOTORS_DIR5_PORT	PORTB
#define MOTORS_DIR5_INDEX	0
#define MOTORS_DIR6_DDR		DDRB
#define MOTORS_DIR6_PORT	PORTB
#define MOTORS_DIR6_INDEX	2

#define MOTORS_NUM		        6

enum Motors_Direction
{
    MOTORS_DIRECTION_FORWARD,
    MOTORS_DIRECTION_BACKWARD
};

void Motors_Init(void);
void Motors_SetSpeed(uint8_t motorIndex, float speed);
void Motors_SetDirection(uint8_t motorIndex, enum Motors_Direction direction);

#endif /* MOTORS_H_ */

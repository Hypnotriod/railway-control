/*
* automation.h
*
* Created: 02.12.2019 14:50:21
*  Author: Ilya Pikin
*/

#ifndef AUTOMATION_H_
#define AUTOMATION_H_

#include <stdbool.h>
#include "motors.h"

#define AUTOMATION_TIMER_INTERRUPT_MICROSECONDS     10000
#define AUTOMATION_SPEED_INCREMENTATION_STEP        0.05f;
#define AUTOMATION_RAILWAYS_NUM                     MOTORS_NUM
#define AUTOMATION_SENSORS_NUM                      IR_NUM

struct Automation_IRSensorConfigStruct
{
    bool isTriggered;
    uint8_t railwayIndex;
    uint16_t timeoutSeconds;
    enum Motors_Direction direction;
};

struct Automation_RailwayConfigStruct
{
    uint16_t timeoutSeconds;
    float speedCurrent;
    float speed;
    enum Motors_Direction direction;
};

void Automation_Init(void);
void Automation_Update(void);

#endif /* AUTOMATION_H_ */

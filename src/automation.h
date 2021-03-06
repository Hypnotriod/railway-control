﻿/*
* automation.h
*
* Created: 02.12.2019 14:50:21
*  Author: Ilya Pikin
*/

#ifndef AUTOMATION_H_
#define AUTOMATION_H_

#include <stdbool.h>
#include "motors.h"
#include "sensors.h"

#define AUTOMATION_TIMER_INTERRUPT_MICROSECONDS     10000UL
#define AUTOMATION_MOTOR_SPEED_INCREMENTATION_STEP  0.01f
#define AUTOMATION_MOTOR_START_SPEED                0.4f
#define AUTOMATION_RAILWAYS_NUM                     MOTORS_NUM
#define AUTOMATION_SENSORS_NUM                      SENSORS_NUM

struct Automation_SensorConfigStruct
{
    uint8_t railwayIndex;
    uint16_t railwayStopTimeoutSeconds;
    enum Motors_Direction direction;
};

struct Automation_RailwayConfigStruct
{
    uint16_t stopTimeoutSeconds;
    uint16_t activationTimeoutSeconds;
    float speedCurrent;
    float speed;
    enum Motors_Direction direction;
};

void Automation_Init(void);
void Automation_Update(void);
void Automation_Reset(void);
void Automation_Apply(void);

extern struct Automation_RailwayConfigStruct raiwals[AUTOMATION_RAILWAYS_NUM];
extern struct Automation_SensorConfigStruct sensors[AUTOMATION_SENSORS_NUM];

#endif /* AUTOMATION_H_ */

/*
* automation.c
*
* Created: 02.12.2019 14:50:08
*  Author: Ilya Pikin
*/

#include "automation.h"
#include "motors.h"
#include "sensors.h"
#include "timer.h"
#include "state.h"

struct Automation_RailwayConfigStruct raiwals[AUTOMATION_RAILWAYS_NUM];
struct Automation_IRSensorConfigStruct sensors[AUTOMATION_SENSORS_NUM];

volatile uint16_t timer0InterruptsCounter = 0;
volatile uint16_t secondsPassed = 0;

void timer0Callback(void);
void updateOnSecondPassed(void);
void updateMotorsState(void);
void updateIRSensorsState(void);

void Automation_Init(void)
{
    Automation_Reset();
    TIMER0_Init(AUTOMATION_TIMER_INTERRUPT_MICROSECONDS, timer0Callback);
}

void Automation_Reset(void)
{
    uint8_t i;
    
    for (i = 0; i < AUTOMATION_RAILWAYS_NUM; i++)
    {
        raiwals[i].direction = MOTORS_DIRECTION_FORWARD;
        raiwals[i].speed = 1.0f; //todo: Get Top speed per railway
        raiwals[i].speedCurrent = AUTOMATION_MOTOR_START_SPEED;
        raiwals[i].timeoutSeconds = 0;
    }
    
    for (i = 0; i < AUTOMATION_SENSORS_NUM; i++)
    {
        sensors[i].isTriggered = false;
        sensors[i].direction = MOTORS_DIRECTION_FORWARD; //todo: Get mapped direction
        sensors[i].railwayIndex = State_ReadSensorRailwayIndex(i);
        sensors[i].timeoutSeconds = State_ReadSensorTimeoutSeconds(i);
    }
}

void Automation_Update(void)
{
    updateIRSensorsState();
    updateMotorsState();
    
    if (secondsPassed != 0)
    {
        secondsPassed--;
        updateOnSecondPassed();
    }
}

void updateIRSensorsState(void)
{
    uint8_t i;
    uint8_t railwayIndex;
    
    for (i = 0; i < AUTOMATION_SENSORS_NUM; i++)
    {
        railwayIndex = sensors[i].railwayIndex;
        
        if (Sensors_Read(i))
        {
            if (sensors[i].isTriggered == false)
            {
                sensors[i].isTriggered = true;
                raiwals[railwayIndex].speed = 0.0f;
                raiwals[railwayIndex].timeoutSeconds = sensors[i].timeoutSeconds;
                raiwals[railwayIndex].direction = sensors[i].direction;
            }
        }
        else
        {
            sensors[i].isTriggered = false;
        }
    }
}

void updateMotorsState(void)
{
    uint8_t i;
    
    for (i = 0; i < AUTOMATION_RAILWAYS_NUM; i++)
    {
        if (raiwals[i].speedCurrent < raiwals[i].speed)
        {
            raiwals[i].speedCurrent += AUTOMATION_MOTOR_SPEED_INCREMENTATION_STEP;
            if (raiwals[i].speedCurrent > raiwals[i].speed) {
                raiwals[i].speedCurrent = raiwals[i].speed;
            }
        }
        else if (raiwals[i].speedCurrent > raiwals[i].speed)
        {
            raiwals[i].speedCurrent -= AUTOMATION_MOTOR_SPEED_INCREMENTATION_STEP;
            if (raiwals[i].speedCurrent < raiwals[i].speed) {
                raiwals[i].speedCurrent = raiwals[i].speed;
            }
        }
        Motors_SetSpeed(i, raiwals[i].speedCurrent);
        Motors_SetDirection(i, raiwals[i].direction);
    }
}

void updateOnSecondPassed(void)
{
    uint8_t i;
    
    for (i = 0; i < AUTOMATION_RAILWAYS_NUM; i++)
    {
        if (raiwals[i].timeoutSeconds > 0) {
            raiwals[i].timeoutSeconds--;
            if (raiwals[i].timeoutSeconds == 0) {
                raiwals[i].speed = 1.0f; //todo: Get Top speed per railway
                raiwals[i].speedCurrent = AUTOMATION_MOTOR_START_SPEED;
            }
        }
    }
}

void timer0Callback(void)
{
    timer0InterruptsCounter++;
    if (timer0InterruptsCounter == (TIMER_MICROSECONDS_IN_1_SECOND / AUTOMATION_TIMER_INTERRUPT_MICROSECONDS))
    {
        secondsPassed++;
        timer0InterruptsCounter = 0;
    }
}


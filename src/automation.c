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
#include "logger.h"

struct Automation_RailwayConfigStruct raiwals[AUTOMATION_RAILWAYS_NUM];
struct Automation_SensorConfigStruct sensors[AUTOMATION_SENSORS_NUM];

volatile uint16_t timer0InterruptsCounter = 0;
volatile uint16_t secondsPassed = 0;

void timer0Callback(void);
void updateOnSecondPassed(void);
void updateMotorsState(void);
void updateSensorsState(void);

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
        raiwals[i].speed = (float)State_ReadRailwaySpeed(i) / 100.f;
        raiwals[i].speedCurrent = AUTOMATION_MOTOR_START_SPEED;
        raiwals[i].stopTimeoutSeconds = 0;
        raiwals[i].activationTimeoutSeconds = 0;
        Motors_SetDirection(i, raiwals[i].direction);
    }
    
    for (i = 0; i < AUTOMATION_SENSORS_NUM; i++)
    {
        sensors[i].isTriggered = false;
        sensors[i].direction = State_ReadSensorRailwayDirection(i);
        sensors[i].railwayIndex = State_ReadSensorRailwayIndex(i);
        sensors[i].railwayStopTimeoutSeconds = State_ReadSensorRailwayStopTimeoutSeconds(i);
    }
    
    secondsPassed = 0;
}

void Automation_Apply(void)
{
    uint8_t i;
    
    for (i = 0; i < AUTOMATION_RAILWAYS_NUM; i++)
    {
        raiwals[i].speed = (float)State_ReadRailwaySpeed(i) / 100.f;
    }
    
    for (i = 0; i < AUTOMATION_SENSORS_NUM; i++)
    {
        sensors[i].direction = State_ReadSensorRailwayDirection(i);
        sensors[i].railwayIndex = State_ReadSensorRailwayIndex(i);
        sensors[i].railwayStopTimeoutSeconds = State_ReadSensorRailwayStopTimeoutSeconds(i);
    }
}

void Automation_Update(void)
{
    updateSensorsState();
    updateMotorsState();
    
    if (secondsPassed != 0)
    {
        secondsPassed--;
        updateOnSecondPassed();
    }
}

void updateSensorsState(void)
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
                
                if (sensors[i].railwayStopTimeoutSeconds != 0 &&
                    raiwals[railwayIndex].stopTimeoutSeconds == 0 &&
                    raiwals[railwayIndex].activationTimeoutSeconds == 0)
                {
                    raiwals[railwayIndex].speed = 0.0f;
                    raiwals[railwayIndex].stopTimeoutSeconds = sensors[i].railwayStopTimeoutSeconds;
                    raiwals[railwayIndex].direction = sensors[i].direction;
                    
                    Logger_LogSensorTriggered(i);
                    Logger_LogRailwayStopped(railwayIndex, sensors[i].railwayStopTimeoutSeconds);
                } else {
                    Logger_LogSensorTriggered(i);
                }
            }
        }
        else if (sensors[i].isTriggered)
        {
            sensors[i].isTriggered = false;
            Logger_LogSensorReleased(i);
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
    }
}

void updateOnSecondPassed(void)
{
    uint8_t i;
    uint8_t railwaySpeedPercents;
    
    for (i = 0; i < AUTOMATION_RAILWAYS_NUM; i++)
    {
        if (raiwals[i].activationTimeoutSeconds > 0) {
            raiwals[i].activationTimeoutSeconds--;
        }
        if (raiwals[i].stopTimeoutSeconds > 0) {
            raiwals[i].stopTimeoutSeconds--;
            if (raiwals[i].stopTimeoutSeconds == 0) {
                railwaySpeedPercents = State_ReadRailwaySpeed(i);
                raiwals[i].speed = (float)railwaySpeedPercents / 100.f;
                raiwals[i].speedCurrent = AUTOMATION_MOTOR_START_SPEED;
                raiwals[i].activationTimeoutSeconds = State_ReadRailwayActivationTimeoutSeconds(i);
                Motors_SetDirection(i, raiwals[i].direction);
                Logger_LogRailwayStarted(i, raiwals[i].direction, railwaySpeedPercents);
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


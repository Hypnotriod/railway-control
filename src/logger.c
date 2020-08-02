/*
 * logger.c
 *
 * Created: 09.02.2020 17:41:01
 *  Author: Ilya Pikin
 */ 

#include <stdio.h>
#include "logger.h"
#include "uart.h"
#include "strings.h"

static bool showLog = false;
static char strBuff[LOGGER_STR_BUFFER_LENGTH] = {0};

void Logger_SetShowLog(bool value)
{
    showLog = value;
}

void Logger_LogSensorTriggered(uint8_t index) 
{
    if (!showLog) return;
    sprintf(strBuff, STR_SENSOR_TRIGGERED, index);
    UART0_WriteString(strBuff);
}

void Logger_LogSensorReleased(uint8_t index) 
{
    if (!showLog) return;
    sprintf(strBuff, STR_SENSOR_RELEASED, index);
    UART0_WriteString(strBuff);
}

void Logger_LogRailwayStopped(uint8_t index, uint16_t timeSec)
{
    if (!showLog) return;
    sprintf(strBuff, STR_RAILWAY_STOPPED, index, timeSec);
    UART0_WriteString(strBuff);
}

void Logger_LogRailwayStarted(uint8_t index, enum Motors_Direction direction, uint8_t speed)
{
    if (!showLog) return;
    if (direction == MOTORS_DIRECTION_FORWARD)
        sprintf(strBuff, STR_RAILWAY_STARTED_FORWARD, index, speed);
    else
        sprintf(strBuff, STR_RAILWAY_STARTED_BACKWARD, index, speed);
    
    UART0_WriteString(strBuff);
}

void Logger_SendParam(const char* cmd, uint8_t index, uint16_t value)
{
    sprintf(strBuff, STR_COMMAND_PATTERN, cmd, index, value);
    UART0_WriteString(strBuff);
}

void Logger_LogFullResetComplete(void)
{
    UART0_WriteString(STR_FULL_RESET_COMPLETE);
}

void Logger_LogLoggerStatus(void)
{
    if (showLog)
        UART0_WriteString(STR_LOGGER_ENABLED);
    else
        UART0_WriteString(STR_LOGGER_DISABLED);
}

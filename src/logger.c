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

static char strBuff[STRINGS_BUFFER_LENGTH] = {0};

void Logger_LogSensorTriggered(uint8_t index) 
{
    sprintf(strBuff, STR_SENSOR_TRIGGERED, index);
    UART0_WriteString(strBuff);
}

void Logger_LogSensorReleased(uint8_t index) 
{
    sprintf(strBuff, STR_SENSOR_RELEASED, index);
    UART0_WriteString(strBuff);
}

void Logger_LogRailwayStopped(uint8_t index, uint16_t timeSec)
{
    sprintf(strBuff, STR_RAILWAY_STOPPED, index, timeSec);
    UART0_WriteString(strBuff);
}

void Logger_LogRailwayStarted(uint8_t index)
{
    sprintf(strBuff, STR_RAILWAY_STARTED, index);
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
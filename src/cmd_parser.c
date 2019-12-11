/*
* cmd_parser.c
*
* Created: 09.12.2019 22:13:15
*  Author: Ilya Pikin
*/

#include <stdio.h>
#include "cmd_parser.h"
#include "uart.h"
#include "utils.h"
#include "automation.h"
#include "state.h"
#include "strings.h"

char   cmdBuffer[CMD_PARSER_BUFFER_LENGTH] = {0};
int8_t cmdBufferIndex = -1;

/**
*   Command set example:        #ABCD01=12@
*   Command execute example:    #ABCDEF?
*/

void CmdParser_ExecuteCommand(void);
void CmdParser_ExecuteSetParam(void);
void CmdParser_SendParam(const char* cmd, uint8_t index, uint16_t value);

void CmdParser_Update(void)
{
    char nextChar;
    
    if (!UART0_Available()) return;
    
    nextChar = UART0_ReadChar();
    
    if (cmdBufferIndex == -1)
    {
        if (nextChar == CMD_PARSER_CHAR_START)
        {
            cmdBufferIndex = 0;
        }
    }
    else if (nextChar == CMD_PARSER_CHAR_START)
    {
        cmdBufferIndex = 0;
    }
    else if (cmdBufferIndex == CMD_PARSER_CMD_FULL_LENGTH)
    {
        if (nextChar == CMD_PARSER_CHAR_EXEC)
        {
            CmdParser_ExecuteCommand();
            cmdBufferIndex = -1;
        }
        else if (nextChar == CMD_PARSER_CHAR_SET)
        {
            cmdBuffer[cmdBufferIndex] = nextChar;
            cmdBufferIndex++;
        }
        else {
            cmdBufferIndex = -1;
        }
    }
    else if (cmdBufferIndex > CMD_PARSER_CMD_FULL_LENGTH)
    {
        if (Utils_CheckIfCharIsNumber(nextChar))
        {
            cmdBuffer[cmdBufferIndex] = nextChar;
            cmdBufferIndex++;
            if (cmdBufferIndex == CMD_PARSER_BUFFER_LENGTH) cmdBufferIndex = -1;
        }
        else if (nextChar == CMD_PARSER_CHAR_END)
        {
            cmdBuffer[cmdBufferIndex] = nextChar;
            CmdParser_ExecuteSetParam();
            cmdBufferIndex = -1;
        }
        else
        {
            cmdBufferIndex = -1;
        }
    }
    else
    {
        cmdBuffer[cmdBufferIndex] = nextChar;
        cmdBufferIndex++;
    }
}

void CmdParser_ExecuteCommand(void)
{
    int i;
    
    if (Utils_CompareStrings(cmdBuffer, CMD_STATUS, CMD_PARSER_CMD_FULL_LENGTH))
    {
        for (i = 0; i < AUTOMATION_RAILWAYS_NUM; i++)
        {
            CmdParser_SendParam(CMD_RWSP, i, State_ReadRailwaySpeed(i));
        }
        
        for (i = 0; i < AUTOMATION_SENSORS_NUM; i++)
        {
            CmdParser_SendParam(CMD_SRWI, i, State_ReadSensorRailwayIndex(i));
            CmdParser_SendParam(CMD_STOS, i, State_ReadSensorTimeoutSeconds(i));
            CmdParser_SendParam(CMD_SDIR, i, State_ReadSensorDirection(i));
        }
    }
    else if (Utils_CompareStrings(cmdBuffer, CMD_FRESET, CMD_PARSER_CMD_FULL_LENGTH))
    {
        State_Reset();
        Automation_Apply();
        UART0_WriteString(STR_FULL_RESET_COMPLETE);
    }
}

void CmdParser_ExecuteSetParam(void)
{
    uint16_t index;
    uint16_t value;
    
    if (Utils_CheckIfCharIsNumber(cmdBuffer[CMD_PARSER_CMD_EXEC_LENGTH]) == false
    || Utils_CheckIfCharIsNumber(cmdBuffer[CMD_PARSER_CMD_EXEC_LENGTH + 1]) == false) return;
    
    index = Utils_ParseUnsignedInt(&cmdBuffer[CMD_PARSER_CMD_EXEC_LENGTH]);
    value = Utils_ParseUnsignedInt(&cmdBuffer[(CMD_PARSER_CMD_FULL_LENGTH + 1)]);
    
    if (Utils_CompareStrings(cmdBuffer, CMD_SRWI, CMD_PARSER_CMD_EXEC_LENGTH))
    {
        index %= AUTOMATION_SENSORS_NUM;
        value %= AUTOMATION_RAILWAYS_NUM;
        State_SaveSensorRailwayIndex(index, value);
        CmdParser_SendParam(CMD_SRWI, index, value);
        Automation_Apply();
    }
    else if (Utils_CompareStrings(cmdBuffer, CMD_STOS, CMD_PARSER_CMD_EXEC_LENGTH))
    {
        index %= AUTOMATION_SENSORS_NUM;
        State_SaveSensorTimeoutSeconds(index, value);
        CmdParser_SendParam(CMD_STOS, index, value);
        Automation_Apply();
    }
    else if (Utils_CompareStrings(cmdBuffer, CMD_SDIR, CMD_PARSER_CMD_EXEC_LENGTH))
    {
        index %= AUTOMATION_SENSORS_NUM;
        if (value > (MOTORS_DIRECTION_BACKWARD + 1)) value = MOTORS_DIRECTION_BACKWARD;
        State_SaveSensorDirection(index, value);
        CmdParser_SendParam(CMD_SDIR, index, value);
        Automation_Apply();
    }
    else if (Utils_CompareStrings(cmdBuffer, CMD_RWSP, CMD_PARSER_CMD_EXEC_LENGTH))
    {
        index %= AUTOMATION_RAILWAYS_NUM;
        if (value > 100) value = 100;
        State_SaveRailwaySpeed(index, value);
        CmdParser_SendParam(CMD_RWSP, index, value);
        Automation_Apply();
    }
}

void CmdParser_SendParam(const char* cmd, uint8_t index, uint16_t value)
{
    sprintf(StrBuff, STR_COMMAND_PATTERN, cmd, index, value);
    UART0_WriteString(StrBuff);
}

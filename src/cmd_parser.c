/*
* cmd_parser.c
*
* Created: 09.12.2019 22:13:15
*  Author: Ilya Pikin
*/

#include "cmd_parser.h"
#include "uart.h"
#include "utils.h"
#include "automation.h"
#include "state.h"

char   cmdBuffer[CMD_PARSER_BUFFER_LENGTH] = {0};
int8_t cmdBufferIndex = -1;

/**
*   Command set example:        #ABCD01=12@
*   Command execute example:    #ABCDEF?
*/

inline void CmdParser_ExecuteCommand(void);
inline void CmdParser_ExecuteSetParam(void);

void CmdParser_Update(void)
{
    char nextChar;
    
    if (UART0_Available())
    {
        nextChar = UART0_ReadChar();
        
        if (cmdBufferIndex == -1)
        {
            if (nextChar == CMD_PARSER_CMD_START)
            {
                cmdBufferIndex = 0;
            }
        }
        else if (nextChar == CMD_PARSER_CMD_START)
        {
            cmdBufferIndex = 0;
        }
        else if (cmdBufferIndex == CMD_PARSER_CMD_FULL_LENGTH)
        {
            if (nextChar == CMD_PARSER_CMD_EXEC)
            {
                CmdParser_ExecuteCommand();
                cmdBufferIndex = -1;
            }
            else if (nextChar == CMD_PARSER_CMD_SET)
            {
                cmdBufferIndex++;
            }
            else {
                cmdBufferIndex = -1;
            }
        }
        else if (cmdBufferIndex > CMD_PARSER_CMD_FULL_LENGTH)
        {
            if ((cmdBufferIndex == (CMD_PARSER_CMD_FULL_LENGTH + 1) && nextChar == '-') || (nextChar >= '0' && nextChar <= '9'))
            {
                cmdBuffer[cmdBufferIndex] = nextChar;
                cmdBufferIndex++;
                if (cmdBufferIndex == CMD_PARSER_BUFFER_LENGTH) cmdBufferIndex = -1;
            }
            else if (nextChar == CMD_PARSER_CMD_END)
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
}

inline void CmdParser_ExecuteCommand(void)
{
    
}

inline void CmdParser_ExecuteSetParam(void)
{
    uint8_t index;
    int32_t value;
    
    index = Utils_ParseInt(&cmdBuffer[CMD_PARSER_CMD_EXEC_LENGTH]);
    value = Utils_ParseInt(&cmdBuffer[(CMD_PARSER_CMD_FULL_LENGTH + 1)]);
    
    if (Utils_CompareStrings(cmdBuffer, CMD_SRWI, CMD_PARSER_CMD_EXEC_LENGTH))
    {
        State_SaveSensorRailwayIndex(index, value);
    }
    else if (Utils_CompareStrings(cmdBuffer, CMD_STOS, CMD_PARSER_CMD_EXEC_LENGTH))
    {
        State_SaveSensorTimeoutSeconds(index, value);
    }
}
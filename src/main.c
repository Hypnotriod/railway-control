/*
* main.c
*
* Created: 25.11.2019 21:02:04
* Author : Ilya Pikin
*/

#include "fcpu.h"
#include <avr/io.h>
#include <util/delay.h>
#include "ui.h"
#include "automation.h"
#include "motors.h"
#include "adc.h"
#include "sensors.h"
#include "pwm.h"
#include "timer.h"
#include "uart.h"
#include "cmd_parser.h"
#include "state.h"
#include "strings.h"

#define UART0_BAUD_RATE 115200

int main(void)
{
    State_Init();
    Motors_Init();
    PWM_Init();
    Sensors_Init();
    ADC_Init();
    UI_Init();
    UART0_Init(UART0_BAUD_RATE);
    Automation_Init();
    
    _delay_ms(100);
    Sensors_Update();
    _delay_ms(100);

    UART0_WriteString(STR_INITIALIZATION_COMPLETED);

    while (1)
    {
        CmdParser_Update();
        Sensors_Update();
        UI_Update();
        _delay_ms(10);
    }
}

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
#include "ir.h"
#include "pwm.h"
#include "timer.h"
#include "uart.h"

#define UART0_BAUD_RATE 9600

int main(void)
{
    Motors_Init();
    PWM_Init();
    IR_Init();
    ADC_Init();
    UI_Init();
    UART0_Init(UART0_BAUD_RATE);
    Automation_Init();
    
    while (1)
    {
        UI_Update();
        _delay_ms(10);
    }
}

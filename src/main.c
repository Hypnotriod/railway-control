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

int main(void)
{
    Motors_Init();
    PWM_Init();
    IR_Init();
    ADC_Init();
    Automation_Init();
    UI_Init();
    
    while (1)
    {
        UI_Update();
        _delay_ms(50);
    }
}

/*
* timer.c
*
* Created: 02.12.2019 18:29:32
*  Author: Ilya Pikin
*/

#include "fcpu.h"
#include "timer.h"

void (*timer0CallBack)() = NULL;

void TIMER0_Init(unsigned long microseconds, void (*pCallBack)())
{
    unsigned long cycles;
    
    cli();
    
    timer0CallBack = pCallBack;
    
    TIMER0_Clear();
    
    cycles = (F_CPU / TIMER_MICROSECONDS_IN_1_SECOND) * microseconds;
    
    if(cycles < TIMER0_RESOLUTION)              TCCR0 |= (0 << CS02) | (0 << CS01) | (1 << CS00); // prescaller 1
    else if((cycles >>= 3) < TIMER0_RESOLUTION)	TCCR0 |= (0 << CS02) | (1 << CS01) | (0 << CS00); // prescaller 8
    else if((cycles >>= 2) < TIMER0_RESOLUTION)	TCCR0 |= (0 << CS02) | (1 << CS01) | (1 << CS00); // prescaller 32
    else if((cycles >>= 1) < TIMER0_RESOLUTION)	TCCR0 |= (1 << CS02) | (0 << CS01) | (0 << CS00); // prescaller 64
    else if((cycles >>= 1) < TIMER0_RESOLUTION)	TCCR0 |= (1 << CS02) | (0 << CS01) | (1 << CS00); // prescaller 128
    else if((cycles >>= 1) < TIMER0_RESOLUTION)	TCCR0 |= (1 << CS02) | (1 << CS01) | (0 << CS00); // prescaller 256
    else if((cycles >>= 2) < TIMER0_RESOLUTION)	TCCR0 |= (1 << CS02) | (1 << CS01) | (1 << CS01); // prescaller 1024
    else            cycles = TIMER0_RESOLUTION,	TCCR0 |= (1 << CS02) | (1 << CS01) | (1 << CS01); // set max timer resolution
    
    TCCR0 |= (1 << WGM01); // CTC on OCR0
    OCR0   = ((unsigned char)(cycles - 1));
    TIMSK |= (1 << OCIE0); // Enable CTC interrupt
    
    sei();
}

ISR(TIMER0_COMP_vect)
{
    timer0CallBack();
}

void TIMER0_Clear(void)
{
    TIMER0_RESET_COUNTER_REGISTER();
    TIMSK &= (~(1 << OCIE0));
    TCCR0 &= (~(1 << WGM01));
}

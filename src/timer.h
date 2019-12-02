/*
* timer.h
*
* Created: 02.12.2019 18:29:21
*  Author: Ilya Pikin
*/

#ifndef TIMER_H_
#define TIMER_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>

#define TIMER_MICROSECONDS_IN_1_SECOND	1000000UL

#define TIMER0_RESOLUTION				256
#define TIMER0_RESET_COUNTER_REGISTER()	(TCNT0 = 0)

void TIMER0_Init(unsigned long microseconds, void (*pCallBack)());

void TIMER0_Clear(void);

#endif /* TIMER_H_ */

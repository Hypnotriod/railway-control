/*
 * pwm.c
 *
 * Created: 25.11.2019 21:05:55
 *  Author: Ilya Pikin
 */ 

#include <avr/io.h>
#include "pwm.h"

void PWM_Init(void) 
{
	//set pins to output
	PWM_OCR1_DDR |= (1 << PWM_OCR1A_INDEX) | (1 << PWM_OCR1B_INDEX) | (1 << PWM_OCR1C_INDEX);
	PWM_OCR3_DDR |= (1 << PWM_OCR3A_INDEX) | (1 << PWM_OCR3B_INDEX) | (1 << PWM_OCR3C_INDEX);
	
	// Set OCnA/OCnB/OCnC on compare match, clear OCnA/OCnB/OCnC at BOTTOM,
	TCCR1A |= (1 << COM1A1) | (1 << COM1B1) | (1 << COM1C1)
		   |  (0 << COM1A0) | (0 << COM1B0) | (0 << COM1C0);
	TCCR3A |= (1 << COM3A1) | (1 << COM3B1) | (1 << COM3C1)
		   |  (0 << COM3A0) | (0 << COM3B0) | (0 << COM3C0);
		   
	// Fast PWM with ICR1 as top
	TCCR1A |= (1 << WGM11) | (0 << WGM10);
	TCCR1B |= (1 << WGM13) | (1 << WGM12);
	TCCR3A |= (1 << WGM31) | (0 << WGM30);
	TCCR3B |= (1 << WGM33) | (1 << WGM32);
	
	TCCR1B |= (1 << CS10); // clk / 1 (No prescaling)
	TCCR3B |= (1 << CS30); // clk / 1 (No prescaling)
	
	ICR1 = PWM_TOP;
	ICR3 = PWM_TOP;
}

/*
 * adc.c
 *
 * Created: 25.11.2019 21:13:39
 *  Author: Ilya Pikin
 */ 

#include <stdint.h>
#include <avr/io.h>
#include "adc.h"

void ADC_Init(void)
{
	// Configure 10 bit ADC
	ADMUX = (0 << REFS1) | (0 << REFS0) | (0 << ADLAR);
	ADCSRA = (1 << ADEN) | (0 << ADFR) | (0 << ADIF) | (0 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

uint16_t ADC_Read(uint8_t index)
{
	ADMUX = (ADMUX & 0xE0) | index;
	ADCSRA |= (1 << ADSC);
	while (ADCSRA & (1 << ADSC));
	return ADC;
}
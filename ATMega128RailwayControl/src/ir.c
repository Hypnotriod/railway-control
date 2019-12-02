/*
 * ir.c
 *
 * Created: 02.12.2019 12:48:10
 *  Author: Ilya Pikin
 */ 

#include <avr/io.h>
#include <stdbool.h>
#include "ir.h"

void IR_Init(void) 
{
	IR_SIG1_DDR &= (~(1 << IR_SIG1_INDEX));
	IR_SIG2_DDR &= (~(1 << IR_SIG2_INDEX));
	IR_SIG3_DDR &= (~(1 << IR_SIG3_INDEX));
	IR_SIG4_DDR &= (~(1 << IR_SIG4_INDEX));
	IR_SIG5_DDR &= (~(1 << IR_SIG5_INDEX));
	IR_SIG6_DDR &= (~(1 << IR_SIG6_INDEX));
	IR_SIG7_DDR &= (~(1 << IR_SIG7_INDEX));
	IR_SIG8_DDR &= (~(1 << IR_SIG8_INDEX));
	IR_SIG9_DDR &= (~(1 << IR_SIG9_INDEX));
	IR_SIG10_DDR &= (~(1 << IR_SIG10_INDEX));
	IR_SIG11_DDR &= (~(1 << IR_SIG11_INDEX));
	IR_SIG12_DDR &= (~(1 << IR_SIG12_INDEX));
} 

bool IR_Read(uint8_t index)
{
	switch (index)
	{
		case 0: return (IR_SIG1_PIN & (1 << IR_SIG1_INDEX));
		case 1: return (IR_SIG2_PIN & (1 << IR_SIG2_INDEX));
		case 2: return (IR_SIG3_PIN & (1 << IR_SIG3_INDEX));
		case 3: return (IR_SIG4_PIN & (1 << IR_SIG4_INDEX));
		case 4: return (IR_SIG5_PIN & (1 << IR_SIG5_INDEX));
		case 5: return (IR_SIG6_PIN & (1 << IR_SIG6_INDEX));
		case 6: return (IR_SIG7_PIN & (1 << IR_SIG7_INDEX));
		case 7: return (IR_SIG8_PIN & (1 << IR_SIG8_INDEX));
		case 8: return (IR_SIG9_PIN & (1 << IR_SIG9_INDEX));
		case 9: return (IR_SIG10_PIN & (1 << IR_SIG10_INDEX));
		case 10: return (IR_SIG11_PIN & (1 << IR_SIG11_INDEX));
		case 11: return (IR_SIG12_PIN & (1 << IR_SIG12_INDEX));
		default: return false;
	}
}

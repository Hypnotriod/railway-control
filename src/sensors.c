/*
* ir.c
*
* Created: 02.12.2019 12:48:10
*  Author: Ilya Pikin
*/

#include <avr/io.h>
#include <stdbool.h>
#include "sensors.h"

void Sensors_Init(void)
{
    SENSORS_SIG1_DDR &= (~(1 << SENSORS_SIG1_INDEX));
    SENSORS_SIG2_DDR &= (~(1 << SENSORS_SIG2_INDEX));
    SENSORS_SIG3_DDR &= (~(1 << SENSORS_SIG3_INDEX));
    SENSORS_SIG4_DDR &= (~(1 << SENSORS_SIG4_INDEX));
    SENSORS_SIG5_DDR &= (~(1 << SENSORS_SIG5_INDEX));
    SENSORS_SIG6_DDR &= (~(1 << SENSORS_SIG6_INDEX));
    SENSORS_SIG7_DDR &= (~(1 << SENSORS_SIG7_INDEX));
    SENSORS_SIG8_DDR &= (~(1 << SENSORS_SIG8_INDEX));
    SENSORS_SIG9_DDR &= (~(1 << SENSORS_SIG9_INDEX));
    SENSORS_SIG10_DDR &= (~(1 << SENSORS_SIG10_INDEX));
    SENSORS_SIG11_DDR &= (~(1 << SENSORS_SIG11_INDEX));
    SENSORS_SIG12_DDR &= (~(1 << SENSORS_SIG12_INDEX));
}

bool Sensors_Read(uint8_t index)
{
    switch (index)
    {
        case 0: return (SENSORS_SIG1_PIN & (1 << SENSORS_SIG1_INDEX));
        case 1: return (SENSORS_SIG2_PIN & (1 << SENSORS_SIG2_INDEX));
        case 2: return (SENSORS_SIG3_PIN & (1 << SENSORS_SIG3_INDEX));
        case 3: return (SENSORS_SIG4_PIN & (1 << SENSORS_SIG4_INDEX));
        case 4: return (SENSORS_SIG5_PIN & (1 << SENSORS_SIG5_INDEX));
        case 5: return (SENSORS_SIG6_PIN & (1 << SENSORS_SIG6_INDEX));
        case 6: return (SENSORS_SIG7_PIN & (1 << SENSORS_SIG7_INDEX));
        case 7: return (SENSORS_SIG8_PIN & (1 << SENSORS_SIG8_INDEX));
        case 8: return (SENSORS_SIG9_PIN & (1 << SENSORS_SIG9_INDEX));
        case 9: return (SENSORS_SIG10_PIN & (1 << SENSORS_SIG10_INDEX));
        case 10: return (SENSORS_SIG11_PIN & (1 << SENSORS_SIG11_INDEX));
        case 11: return (SENSORS_SIG12_PIN & (1 << SENSORS_SIG12_INDEX));
        default: return false;
    }
}

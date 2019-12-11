/*
* ir.h
*
* Created: 02.12.2019 12:48:25
*  Author: Ilya Pikin
*/


#ifndef SENSORS_H_
#define SENSORS_H_

#define SENSORS_SIG1_DDR     DDRA
#define SENSORS_SIG1_PIN     PINA
#define SENSORS_SIG1_INDEX   2
#define SENSORS_SIG2_DDR     DDRA
#define SENSORS_SIG2_PIN     PINA
#define SENSORS_SIG2_INDEX   1
#define SENSORS_SIG3_DDR     DDRA
#define SENSORS_SIG3_PIN     PINA
#define SENSORS_SIG3_INDEX   0
#define SENSORS_SIG4_DDR     DDRA
#define SENSORS_SIG4_PIN     PINA
#define SENSORS_SIG4_INDEX   3
#define SENSORS_SIG5_DDR     DDRA
#define SENSORS_SIG5_PIN     PINA
#define SENSORS_SIG5_INDEX   4
#define SENSORS_SIG6_DDR     DDRA
#define SENSORS_SIG6_PIN     PINA
#define SENSORS_SIG6_INDEX   5
#define SENSORS_SIG7_DDR     DDRA
#define SENSORS_SIG7_PIN     PINA
#define SENSORS_SIG7_INDEX   6
#define SENSORS_SIG8_DDR     DDRA
#define SENSORS_SIG8_PIN     PINA
#define SENSORS_SIG8_INDEX   7
#define SENSORS_SIG9_DDR     DDRC
#define SENSORS_SIG9_PIN     PINC
#define SENSORS_SIG9_INDEX   7
#define SENSORS_SIG10_DDR    DDRC
#define SENSORS_SIG10_PIN    PINC
#define SENSORS_SIG10_INDEX  6
#define SENSORS_SIG11_DDR    DDRC
#define SENSORS_SIG11_PIN    PINC
#define SENSORS_SIG11_INDEX  5
#define SENSORS_SIG12_DDR    DDRC
#define SENSORS_SIG12_PIN    PINC
#define SENSORS_SIG12_INDEX  4

#define SENSORS_NUM          12

void Sensors_Init(void);
bool Sensors_Read(uint8_t index);

#endif /* SENSORS_H_ */

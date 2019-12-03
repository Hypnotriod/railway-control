/*
* ir.h
*
* Created: 02.12.2019 12:48:25
*  Author: Ilya Pikin
*/


#ifndef IR_H_
#define IR_H_

#define IR_SIG1_DDR     DDRA
#define IR_SIG1_PIN     PINA
#define IR_SIG1_INDEX   0
#define IR_SIG2_DDR     DDRA
#define IR_SIG2_PIN     PINA
#define IR_SIG2_INDEX   1
#define IR_SIG3_DDR     DDRA
#define IR_SIG3_PIN     PINA
#define IR_SIG3_INDEX   2
#define IR_SIG4_DDR     DDRA
#define IR_SIG4_PIN     PINA
#define IR_SIG4_INDEX   3
#define IR_SIG5_DDR     DDRA
#define IR_SIG5_PIN     PINA
#define IR_SIG5_INDEX   4
#define IR_SIG6_DDR     DDRA
#define IR_SIG6_PIN     PINA
#define IR_SIG6_INDEX   5
#define IR_SIG7_DDR     DDRA
#define IR_SIG7_PIN     PINA
#define IR_SIG7_INDEX   6
#define IR_SIG8_DDR     DDRA
#define IR_SIG8_PIN     PINA
#define IR_SIG8_INDEX   7
#define IR_SIG9_DDR     DDRC
#define IR_SIG9_PIN     PINC
#define IR_SIG9_INDEX   7
#define IR_SIG10_DDR    DDRC
#define IR_SIG10_PIN    PINC
#define IR_SIG10_INDEX  6
#define IR_SIG11_DDR    DDRC
#define IR_SIG11_PIN    PINC
#define IR_SIG11_INDEX  5
#define IR_SIG12_DDR    DDRC
#define IR_SIG12_PIN    PINC
#define IR_SIG12_INDEX  4

#define IR_NUM          12

void IR_Init(void);
bool IR_Read(uint8_t index);

#endif /* IR_H_ */

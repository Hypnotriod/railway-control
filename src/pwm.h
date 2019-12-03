/*
* pwm.h
*
* Created: 25.11.2019 21:05:46
*  Author: Ilya Pikin
*/

#ifndef PWM_H_
#define PWM_H_

#define PWM_TOP             1023
#define PWM_OCR1_DDR        DDRB
#define PWM_OCR1A_INDEX     5
#define PWM_OCR1B_INDEX     6
#define PWM_OCR1C_INDEX     7
#define PWM_OCR3_DDR        DDRE
#define PWM_OCR3A_INDEX     3
#define PWM_OCR3B_INDEX     4
#define PWM_OCR3C_INDEX     5

#define PWM_OC1A_SetDuty(_DUTY_)    (OCR1A = (_DUTY_))
#define PWM_OC1B_SetDuty(_DUTY_)    (OCR1B = (_DUTY_))
#define PWM_OC1C_SetDuty(_DUTY_)    (OCR1C = (_DUTY_))
#define PWM_OC3A_SetDuty(_DUTY_)    (OCR3A = (_DUTY_))
#define PWM_OC3B_SetDuty(_DUTY_)    (OCR3B = (_DUTY_))
#define PWM_OC3C_SetDuty(_DUTY_)    (OCR3C = (_DUTY_))

void PWM_Init(void);

#endif /* PWM_H_ */

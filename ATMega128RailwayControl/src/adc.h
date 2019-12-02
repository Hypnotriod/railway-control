/*
 * adc.h
 *
 * Created: 25.11.2019 21:13:48
 *  Author: Ilya Pikin
 */ 


#ifndef ADC_H_
#define ADC_H_

#define ADC_VALUE_MAX	1023
#define ADC_VALUE_MID	512

void ADC_Init(void);
uint16_t ADC_Read(uint8_t index);


#endif /* ADC_H_ */
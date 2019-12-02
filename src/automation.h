/*
 * automation.h
 *
 * Created: 02.12.2019 14:50:21
 *  Author: Ilya Pikin
 */ 


#ifndef AUTOMATION_H_
#define AUTOMATION_H_

#include "motors.h"

struct Automation_IRSequenceStruct 
{
	uint16_t timeoutSeconds;
	enum Motors_Direction direction;
};

void Automation_Init(void);

#endif /* AUTOMATION_H_ */
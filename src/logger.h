/*
 * logger.h
 *
 * Created: 09.02.2020 17:41:16
 *  Author: Ilya Pikin
 */ 


#ifndef LOGGER_H_
#define LOGGER_H_

void Logger_LogSensorTriggered(uint8_t index);
void Logger_LogSensorReleased(uint8_t index);
void Logger_LogRailwayStopped(uint8_t index, uint16_t timeSec);
void Logger_LogRailwayStarted(uint8_t index);
void Logger_SendParam(const char* cmd, uint8_t index, uint16_t value);
void Logger_LogFullResetComplete(void);

#endif /* LOGGER_H_ */
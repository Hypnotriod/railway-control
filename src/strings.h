/*
 * cstrings.h
 *
 * Created: 11.12.2019 21:30:24
 *  Author: Ilya Pikin
 */ 


#ifndef STRINGS_H_
#define STRINGS_H_

#define STRINGS_BUFFER_LENGTH       32

#define STR_COMMAND_PATTERN                 "#%s%02i=%i@\n"
#define STR_FULL_RESET_COMPLETE             "Full Reset complete!\n"
#define STR_SENSOR_STATE_CHANGED_TO_HIGH    "Sensor #%02i triggered\n"
#define STR_SENSOR_STATE_CHANGED_TO_LOW     "Sensor #%02i relesed\n"

extern char StrBuff[STRINGS_BUFFER_LENGTH];

#endif /* CSTRINGS_H_ */
/*
 * cstrings.h
 *
 * Created: 11.12.2019 21:30:24
 *  Author: Ilya Pikin
 */ 


#ifndef STRINGS_H_
#define STRINGS_H_

#define STR_INITIALIZATION_COMPLETED    "Initialization completed.\r\n"

#define STR_COMMAND_PATTERN             "#%s%02u=%u@\r\n"
#define STR_FULL_RESET_COMPLETE         "Full Reset complete!\r\n"
#define STR_SENSOR_TRIGGERED            "Sensor #%02i triggered.\r\n"
#define STR_SENSOR_RELEASED             "Sensor #%02i relesed.\r\n"
#define STR_RAILWAY_STOPPED             "Railway #%i stopped for %u seconds.\r\n"
#define STR_RAILWAY_STARTED_FORWARD     "Railway #%i started forward with speed of %u%%.\r\n"
#define STR_RAILWAY_STARTED_BACKWARD    "Railway #%i started backward with speed of %u%%.\r\n"
#define STR_LOGGER_ENABLED              "Logger enabled.\r\n"
#define STR_LOGGER_DISABLED             "Logger disabled.\r\n"

#endif /* CSTRINGS_H_ */
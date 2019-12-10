/*
 * cmd_parser.h
 *
 * Created: 09.12.2019 22:13:02
 *  Author: Ilya Pikin
 */ 


#ifndef CMD_PARSER_H_
#define CMD_PARSER_H_

#define CMD_SRWI    "SRWI"      // Sensor railway index
#define CMD_STOS    "STOS"      // Sensor timeout seconds
#define CMD_SDIR    "SDIR"      // Sensor direction
#define CMD_RWSP    "RWSP"      // Railway speed
#define CMD_STATUS  "STATUS"    // Status
#define CMD_FRESET  "FRESET"    // Full reset 

#define CMD_PARSER_BUFFER_LENGTH        16
#define CMD_PARSER_CMD_FULL_LENGTH      6
#define CMD_PARSER_CMD_EXEC_LENGTH      4

#define CMD_PARSER_CHAR_START    '#'
#define CMD_PARSER_CHAR_END      '@'
#define CMD_PARSER_CHAR_EXEC     '?'
#define CMD_PARSER_CHAR_SET      '='

void CmdParser_Update(void);

#endif /* CMD_PARSER_H_ */
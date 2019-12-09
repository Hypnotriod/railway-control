/*
 * cmd_parser.h
 *
 * Created: 09.12.2019 22:13:02
 *  Author: Ilya Pikin
 */ 


#ifndef CMD_PARSER_H_
#define CMD_PARSER_H_

#define CMD_SRWI    "SRWI"  // Sensor railway index
#define CMD_STOS    "STOS"  // Sensor timeout seconds

#define CMD_PARSER_BUFFER_LENGTH        16
#define CMD_PARSER_CMD_FULL_LENGTH      6
#define CMD_PARSER_CMD_EXEC_LENGTH      4

#define CMD_PARSER_CMD_START    '#'
#define CMD_PARSER_CMD_END      '@'
#define CMD_PARSER_CMD_EXEC     '?'
#define CMD_PARSER_CMD_SET      '='

void CmdParser_Update(void);

#endif /* CMD_PARSER_H_ */
/*
 * uart.h
 *
 * Created: 06.03.2017 12:46:23
 *  Author: ipikin
 */ 

#ifndef __UART_H
#define __UART_H

#include "avr/io.h"
#include "avr/interrupt.h"
#include <stdbool.h>

#define UART0_RX_BUFFER_LENGTH 32
#define UART0_TX_BUFFER_LENGTH 32

#define UART0_PORT      PORTE
#define UART0_RX_PIN    0
#define UART0_TX_PIN    1

void UART0_Init(uint32_t baud);
void UART0_WriteString(const char* data);
char UART0_ReadChar(void);
bool UART0_Available(void);

#endif

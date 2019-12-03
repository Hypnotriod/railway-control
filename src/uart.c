/*
* uart.c
*
* Created: 06.03.2017 12:46:12
*  Author: ipikin
*/

#include "uart.h"
#include "fcpu.h"

volatile char   uart0RXBuffer[UART0_RX_BUFFER_LENGTH] = {0};
volatile int8_t uart0RXBufferReadIndex = 0;
volatile int8_t uart0RXBufferWriteIndex = 0;

volatile char   uart0TXBuffer[UART0_TX_BUFFER_LENGTH] = {0};
volatile int8_t uart0TXBufferReadIndex = 0;
volatile int8_t uart0TXBufferWriteIndex = 0;
volatile bool   uart0TXInProgress = false;

void UART0_Init(uint32_t baud)
{
    uint16_t ubrr;
    
    UART0_PORT |= (1 << UART0_RX_PIN);
    
    UCSR0A |= (1 << U2X0); // Double speed
    ubrr = (F_CPU / 8UL / baud) - 1UL;
    UBRR0H = (ubrr >> 8);
    UBRR0L = ubrr;
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8N1
    UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0) | (1 << TXCIE0);  // UART enable RX, TX and RX, TX Interrupts
}

void UART0_WriteString(const char* data)
{
    while(*data)
    {
        uart0TXBuffer[uart0TXBufferWriteIndex] = *data++;
        uart0TXBufferWriteIndex = (uart0TXBufferWriteIndex + 1) % UART0_TX_BUFFER_LENGTH;
    }
    
    if(uart0TXInProgress == false)
    {
        uart0TXInProgress = true;
        UDR0 = uart0TXBuffer[uart0TXBufferReadIndex];
        uart0TXBufferReadIndex = (uart0TXBufferReadIndex + 1) % UART0_TX_BUFFER_LENGTH;
    }
}

char UART0_ReadChar(void)
{
    char tmp = uart0RXBuffer[uart0RXBufferReadIndex];
    if(uart0RXBufferReadIndex != uart0RXBufferWriteIndex) {
        uart0RXBufferReadIndex = (uart0RXBufferReadIndex + 1) % UART0_RX_BUFFER_LENGTH;
    }
    return tmp;
}

bool UART0_Available(void)
{
    return (uart0RXBufferReadIndex != uart0RXBufferWriteIndex);
}

ISR(USART0_RX_vect)
{
    uart0RXBuffer[uart0RXBufferWriteIndex] = UDR0;
    uart0RXBufferWriteIndex = (uart0RXBufferWriteIndex + 1) % UART0_RX_BUFFER_LENGTH;
}

ISR(USART0_TX_vect)
{
    if(uart0TXBufferReadIndex != uart0TXBufferWriteIndex)
    {
        UDR0 = uart0TXBuffer[uart0TXBufferReadIndex];
        uart0TXBufferReadIndex = (uart0TXBufferReadIndex + 1) % UART0_TX_BUFFER_LENGTH;
    }
    else
    {
        uart0TXInProgress = false;
    }
}

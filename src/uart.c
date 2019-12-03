/*
* uart.c
*
* Created: 06.03.2017 12:46:12
*  Author: ipikin
*/

#include "uart.h"
#include "fcpu.h"

volatile char   UART0_RX_Buffer[UART0_RX_BUFFER_LENGTH] = {0};
volatile int8_t UART0_RX_Buffer_ReadIndex = 0;
volatile int8_t UART0_RX_Buffer_WriteIndex = 0;

volatile char   UART0_TX_Buffer[UART0_TX_BUFFER_LENGTH] = {0};
volatile int8_t UART0_TX_Buffer_ReadIndex = 0;
volatile int8_t UART0_TX_Buffer_WriteIndex = 0;
volatile bool   UART0_TX_InProgress = false;

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
        UART0_TX_Buffer[UART0_TX_Buffer_WriteIndex] = *data++;
        while(((UART0_TX_Buffer_WriteIndex + 1) % UART0_TX_BUFFER_LENGTH) == UART0_TX_Buffer_ReadIndex){};
        UART0_TX_Buffer_WriteIndex = (UART0_TX_Buffer_WriteIndex + 1) % UART0_TX_BUFFER_LENGTH;
    }
    
    if(UART0_TX_InProgress == false)
    {
        UART0_TX_InProgress = true;
        UDR0 = UART0_TX_Buffer[UART0_TX_Buffer_ReadIndex];
        UART0_TX_Buffer_ReadIndex = (UART0_TX_Buffer_ReadIndex + 1) % UART0_TX_BUFFER_LENGTH;
    }
}

char UART0_ReadChar(void)
{
    char tmp = UART0_RX_Buffer[UART0_RX_Buffer_ReadIndex];
    if(UART0_RX_Buffer_ReadIndex != UART0_RX_Buffer_WriteIndex) {
        UART0_RX_Buffer_ReadIndex = (UART0_RX_Buffer_ReadIndex + 1) % UART0_RX_BUFFER_LENGTH;
    }
    return tmp;
}

bool UART0_Available(void)
{
    return (UART0_RX_Buffer_ReadIndex != UART0_RX_Buffer_WriteIndex);
}

ISR(USART0_RX_vect)
{
    UART0_RX_Buffer[UART0_RX_Buffer_WriteIndex] = UDR0;
    UART0_RX_Buffer_WriteIndex = (UART0_RX_Buffer_WriteIndex + 1) % UART0_RX_BUFFER_LENGTH;
}

ISR(USART0_TX_vect)
{
    if(UART0_TX_Buffer_ReadIndex != UART0_TX_Buffer_WriteIndex)
    {
        UDR0 = UART0_TX_Buffer[UART0_TX_Buffer_ReadIndex];
        UART0_TX_Buffer_ReadIndex = (UART0_TX_Buffer_ReadIndex + 1) % UART0_TX_BUFFER_LENGTH;
    }
    else
    {
        UART0_TX_InProgress = false;
    }
}

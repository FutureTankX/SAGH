/*
 * conf_uart.h
 *
 * Created: 2/3/2018 5:01:08 PM
 *  Author: Moath
 */ 

#ifndef CONF_UART_H_
#define CONF_UART_H_

#include <stdio.h>

#define BAUD 9600
#define UBRR F_CPU/16/BAUD-1


void USART_Init(unsigned int ubrr);
int USART_Transmit(char data, FILE *stream);
int USART_Receive(FILE *stream);

/* Link UART to printf  */
static FILE std_uartout = FDEV_SETUP_STREAM(USART_Transmit, NULL, _FDEV_SETUP_WRITE);
static FILE std_uartin = FDEV_SETUP_STREAM(NULL, USART_Receive, _FDEV_SETUP_READ);


void USART_Init(unsigned int ubrr)
{
	/*Enable Power*/
	PRR &= ~(1 << PRUSART0);
	/*Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	/*Enable receiver and transmitter */
	UCSR0B = _BV(RXEN0) | _BV(TXEN0);
	/* Set frame format: 8 data, 1 stop bit */
	/* Config printf to use USART */
	stdout = &std_uartout;
	stdin = &std_uartin;
	}

int USART_Transmit(char data, FILE *stream)
{
	/* Wait for empty transmit buffer */
	while (!(UCSR0A & _BV(UDRE0))) {
	}		
	/* Put data into buffer, sends the data */
	UDR0 = data;
	return 0;
}

int USART_Receive(FILE *stream)
{
	/* Wait for data to be received */
	while (!(UCSR0A & _BV(RXC0))) {
	}
	/* Get and return received data from buffer */
	return UDR0;
}
#endif /* CONF_UART_H_ */
#include "usart.h"
#include <avr/io.h>

/*
 * Set the baud rate and enable the USART 1 functionalities specified.
 * @param[in] tx - 1 to enable transmitter, 0 to disable
 * @param[in] rx - 1 to enable receiver, 0 to disable
 *
 */
void USART1Init( int tx, int rx )
{
	// Baud rate value setting
	UBRR1H = (unsigned char) (USART_BAUD_VALUE>>8);
	UBRR1L = (unsigned char) USART_BAUD_VALUE;

	// Configure for 8 bit data, no parity, and 2 stop bits
	UCSR1C = (0<<UMSEL0) | (0<<UPM0) | (0<<USBS0) | (3<<UCSZ0);
	
	// Enable/disable receiver and transmitter as specified
	UCSR1B = ((tx != 0)<<TXEN0) | ((rx != 0)<<RXEN0);
}

/*
 * Transmit one character using the USART 1 transmitter.
 * @param[in] data - the character to transmit
 *
 */
void USART1Transmit( char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR1A & (1<<UDRE0)));
	/* Copy 9th bit to TXB8 */
	UCSR1B &= ~(1<<TXB80);
	if ( data & 0x0100 )
	UCSR1B |= (1<<TXB80);
	/* Put data into buffer, sends the data */
	UDR1 = data;
}

/*
 * Transmit a string of characters using the USART 1 Transmitter.
 * String must be null terminated.
 * @param[in] data - pointer to start of string
 *
 */
void USART1WriteString( char * data )
{
	uint32_t i = 0;
	
	while( data[i] != 0 )
	{
		USART1Transmit( data[ i ] );
		++i;
	}
}

/*
 * Write a string of characters defined by a pointer to the starting character
 * and an amount of characters to write to the USART 1 bus.
 * Dangerous since this could be used to read memory outside the desired string.
 * @param[in] data - the given pointer
 * @param[in] length - the length of the string to write
 */
void USART1WriteStringDangerous( char * data, unsigned int length )
{
	for( int i = 0; i < length; ++i )
	{
		USART1Transmit( data[i] );
	}
}

/*
 * Wait for and retrieve the next character from the receive buffer.
 * @return 8 bit data from the receive buffer.
 *
 */
char USART1Receive()
{
	// Wait for data to be received
	while ( ! (UCSR1A & (1<<RXC0)));
	// Get and return received data from buffer
	return UDR1;
}

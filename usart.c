#include "uart.h"

/*
 * Set the baud rate and enable the USART 1 functionalities specified.
 * @param[in] baudVal - the value corresponding with the desired baud rate (see data sheet)
 * @param[in] tx - 1 to enable transmitter, 0 to disable
 * @param[in] rx - 1 to enable receiver, 0 to disable
 *
 */
void USART1Init( unsigned int baudVal, int tx, int rx )
{
	// Baud rate value setting
	UBRR1H = (unsigned char) (baudVal>>8);
	UBRR1L = (unsigned char) baudVal;

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
void USART1Transmit( unsigned char data )
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
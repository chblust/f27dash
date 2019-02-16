/*
 * usart.h
 *
 * Created: 1/9/2019 5:59:13 PM
 *  Author: Chris Blust
 */ 

#ifndef USART_H
#define USART_H

// Determines the correct baud rate register values for the given CPU
// speed at 9600 baud.
#if F_CPU == 16000000UL
	#define USART_BAUD_VALUE 103
#else // Must be 8000000UL
	#define USART_BAUD_VALUE 51
#endif

void USART1Init( int tx, int rx );

void USART1Transmit( char data );

void USART1WriteString( char * data );

void USART1WriteStringDangerous( char * data, unsigned int length );

char USART1Receive();

#endif /* USART_H */
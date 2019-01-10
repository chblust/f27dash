/*
 * usart.h
 *
 * Created: 1/9/2019 5:59:13 PM
 *  Author: Chris Blust
 */ 

#ifndef USART_H_
#define USART_H_

void USART1Init( unsigned int baudValue, int tx, int rx );

void USART1Transmit( unsigned char data );

unsigned char USART1Receive();

#endif /* USART_H_ */
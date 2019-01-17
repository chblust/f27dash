#include "port.h"
#include <avr/io.h>

/*
 * Write a given bit to a given position within Port A of the AT90.
 * @param[in] pos - 0-7 the position of the bit in Port A
 * @param[in] data - 1 or 0. The value of the bit to write to Port A
 */
void writePortA( unsigned char pos, unsigned char data )
{
	pos = pos & 7;
	unsigned char value = PORTA;
	value &= ~(1 << pos);
	value |= (data << pos);
	PORTA = value;
}
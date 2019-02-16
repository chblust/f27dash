/*
 * shiftRegisters.c
 *
 * Created: 1/9/2019 6:34:41 PM
 *  Author: chb4299
 */ 

#include "shiftRegisters.h"
#include "port.h"
#include <util/delay.h>

/*
 * Shift a given bit into the shift registers.
 * @param[in] data - 1 or 0, the given bit value
 *
 */
void shiftData( unsigned char data )
{
	_delay_us( SHIFT_DELAY );
	writePortA( STROBE, 0 );
	writePortA( CLOCK, 0 );
	// Protect against anything other than 1 or 0 being written
	writePortA( SIN, data & 1 );
	_delay_us( SHIFT_DELAY );
	writePortA( CLOCK, 1 );
	_delay_us( SHIFT_DELAY );
	writePortA( CLOCK, 0 );
}

/*
 * Tell the SRs to change their outputs to their internally stored data.
 * 
 */
void setSROutputs()
{
	writePortA( STROBE, 1 );
	_delay_us( SHIFT_DELAY );
	writePortA( STROBE, 0 );
}

/*
 * Shift a pattern of bits into the shift registers.
 * @param[in] pattern - the pattern to shift in, as it should be once shifted in (not reverse)
 * @param[in] length - the length of the pattern to shift in
 */
void shiftPattern( unsigned char * pattern, unsigned int length )
{
	for( int i = length; i > 0 ; --i )
	{
		shiftData( pattern[ i - 1 ] );
	}

	setSROutputs();
}
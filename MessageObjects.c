#include "MessageObjects.h"
#include <avr/io.h>
#include <stdint.h>


/*
 * Check the availability of the given mob.
 * @param[in] mob - the index of the mob to check the availability of
 * @return 1 if in use, 0 if not
 *
 */
uint8_t checkMobAvailability( uint8_t mob )
{
	if( mob > 14 )
		mob = 14;

	uint16_t mask = 1 << mob;
	uint8_t inUse = 0;
	inUse |= CANEN2 & (mask & 0x0F);
	inUse |= CANEN2 & ((mask & 0xF0) >> 8);

	return inUse;
}

/*
 * Read the 8-byte data stored in a MOb.
 * @param[out] data - where the data is found after the read
 * @param[in] mobIndex - the index of the MOb
 * 
 */
void readMObData( char * data, uint8_t mobIndex )
{
	// Ensures only 0-14 are written to the MOb index
	if( mobIndex > 14 )
		mobIndex = 14;

	// Zero out the register, setting the starting data array index and auto-increment enabled
	char canPage = 0;

	// Set the MOb pointer to the given MOb index
	canPage |= mobIndex << CONMOB0;

	for( unsigned short int i = 0; i < 8; ++i )
	{
		// Read the byte of the data array at the current index (auto-incrementing)
		data[ i ] = CANMSG;
	}
}

/*
 * Register a MOb for a CAN function. See AT90CAN datasheet for more info.
 * @param[in] mobIndex - the index of the MOb to configure
 * @param[in] mode - the mode to configure the MOb for
 * @param[in] idTag - see data sheet
 * @param[in] idMask - see data sheet
 *
 */
void configureMOb( uint8_t mobIndex, MessageObjectMode mode, uint16_t idTag, uint16_t idMask )
{
	if ( mobIndex > 14 )
		mobIndex = 14;

	// Point to the MOb index specified
	CANPAGE |= mobIndex << CONMOB0;

	// Put LSbs of idTag in MSbs of CANIDT2
	CANIDT2 |= (idTag & 0x07) << 5;
	// Put bits 10-0 into LSbs of CANIDT1;
	CANIDT1 |= (idTag & 0b11111111000) >> 3;

	// Put LSbs of idMask in MSbs of CANIDM2
	CANIDM2 |= (idMask & 0x07) << 5;
	// Put bits 10-0 into LSbs of CANIDM1
	CANIDM1 |= (idMask & 0b11111111000) >> 3;

	// CANCDMOB write must be done last, as writing the mode begins operation of the MOb

	// Automatic reply to not ready, CAN 2.0 version A
	char canCdMob = 0x00;

	// Set mode to the desired mode.
	canCdMob |= mode << CONMOB0;
	
	// Set Data length code to 8
	canCdMob |= 8;
	CANCDMOB = canCdMob;
}




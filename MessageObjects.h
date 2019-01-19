#ifndef MESSAGEOBJECTS_H
#define MESSAGEOBJECTS_H
#include <stdint.h>

typedef enum
{
	DISABLED = 0x0,
	TXDATA = 0x1,
	RXDATA = 0x2
} MessageObjectMode;

uint8_t checkMobAvailability( uint8_t mob );

void readMObData( char * data, uint8_t mobIndex );

void configureMOb( uint8_t mobIndex, MessageObjectMode mode, uint16_t idTag, uint16_t idMask );

#endif // MESSAGEOBJECTS_H
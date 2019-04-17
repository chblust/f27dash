#include "lightControl.h"
#include "shiftRegisters.h"
#include <util/delay.h>

#ifdef DEBUG
	#include "can.h"
#endif


#include <stdint.h>

// Internal model of the LED states
static unsigned char ledStates[ LED_COUNT ];

// The current number of lights lit up representing RPM
static uint8_t currentNumLights = 0;

static uint8_t currentGear = 0;

// Shift register output patterns that produce decimal digits on 7 segment display
static unsigned char segmentPatterns[ NUM_GEARS + 1][ SEGMENT_DISPLAY_LED_COUNT ] = {
	{ 1, 0, 1, 0, 1, 0, 0, 0},
	{ 0, 0, 0, 0, 1, 0, 0, 1},
	{ 1, 0, 1, 1, 0, 0, 1, 1},
	{ 1, 0, 0, 1, 1, 0, 1, 1},
	{ 1, 1, 0, 0, 1, 0, 0, 1}
};

/*
 * Shift the bits stored in the internal model of the LEDS to the outputs of the shift registers.
 *
 */
void updateLights()
{
	#ifdef DEBUG

	// Count lights
	uint8_t count = 0;
	for( uint8_t i = 0; i < 50; ++i )
	{
		if( ledStates[ i ] == 1 )
		{
			count++;
		}
	}


	CANMessage message;
	message.id = 0xAB;
	message.data[0] = count;
	message.data[1] = ledStates[ AUTO_UP_LED_1 ];
	message.data[2] = ledStates[ AUTO_UP_LED_2 ];
	message.data[3] = ledStates[ CRITICAL_ERROR_LED ];
	message.data[4] = ledStates[ WARNING_LED ];
	message.data[5] = ledStates[ DRS_LED ];
	message.data[6] = ledStates[ HOLD_LED ];
	message.data[7] = currentGear;
	message.length = 8;
	sendCAN( &message );

	#endif

	shiftPattern( ledStates, LED_COUNT );
}

/*
 * It's gettin hot in here
 *
 */
void shiftAll()
{
	unsigned char pattern[LED_COUNT];
	for(int i = 0; i < LED_COUNT; ++i)
		pattern[i] = 1;
	shiftPattern( pattern, LED_COUNT );
}

/*
 * Based on a given RPM reading, change the internal model of the shift lights.
 * @param[in] percentLit - percentage of the shift lights to illuminate. 0-100
 *
 */
void setRPM( uint8_t percentLit )
{
	if( percentLit > 100 )
		percentLit = 100;
	unsigned int numLights = ((float) percentLit / 100) * LED_COUNT;

	if( numLights != currentNumLights)
	{
		currentNumLights = numLights;

		for( unsigned short int i = 0; i < SHIFT_LIGHT_COUNT; ++i )
		{
			if( i < numLights )
			{
				ledStates[ i ] = 1;
			}
			else
			{
				ledStates[ i ] = 0;
			}
		}
	}
}

void clearRPM()
{
	for( uint8_t i = 0; i < SHIFT_LIGHT_COUNT; ++i )
	{
		ledStates[i] = 0;
	}

	updateLights();
}

/*
 * Change the internal model for the autoup indicating LEDs to a given state.
 * @param[in] state - 1 or 0, the given state
 *
 */
void setAutoUp( unsigned char state )
{
	ledStates[ AUTO_UP_LED_1 ] = state & 1;
	ledStates[ AUTO_UP_LED_2 ] = state & 1;
}

/*
 * Change the internal model for the critical error indicator LED to a given state.
 * @param[in] state - 1 or 0, the given state
 *
 */
void setError( unsigned char state )
{
	ledStates[ CRITICAL_ERROR_LED ] = state;
}

/*
 * Change the internal model for the warning indicator LED to a given state.
 * @param[in] state - 1 or 0, the given state
 *
 */
void setWarning( unsigned char state )
{
	ledStates[ WARNING_LED ] = state;
}

/*
 * Change the internal model for the DRS indicator LED to a given state.
 * @param[in] state - 1 or 0, the given state
 *
 */
void setDRS( unsigned char state )
{
	ledStates[ DRS_LED ] = state;
}

/*
 * Change the internal model for the hold indicator LED to a given state.
 * @param[in] state - 1 or 0, the given state
 *
 */
void setHold( unsigned char state )
{
	ledStates[ HOLD_LED ] = state;
}

/*
 * Change the internal model for the seven-segment LEDs composing gear position based
 * on a given gear position.
 * @param[in] position - 1-4, the given gear position
 *
 */
void setGearPosition( unsigned short int position )
{
	currentGear = position;

	if( position > NUM_GEARS )	
	{
		for( unsigned short int i = SEGMENT_DISPLAY_START_LED; i < SEGMENT_DISPLAY_LED_COUNT + SEGMENT_DISPLAY_START_LED; ++i )
		{
			ledStates[ i ] = 0;
		}
	}
	else
	{
		for( unsigned short int i = SEGMENT_DISPLAY_START_LED; i < SEGMENT_DISPLAY_LED_COUNT + SEGMENT_DISPLAY_START_LED; ++i )
		{
			ledStates[ i ] = segmentPatterns[ position ][ i - SEGMENT_DISPLAY_START_LED ];
		}
	}
}

void write7Seg( int s0, int s1, int s2, int s3, int s4, int s5, int s6, int s7 )
{
	uint8_t pattern[] = { s0, s1, s2, s3, s4, s5, s6, s7 };
	for( uint8_t i = SEGMENT_DISPLAY_START_LED; i < SEGMENT_DISPLAY_LED_COUNT + SEGMENT_DISPLAY_START_LED; ++i )
	{
		ledStates[ i ] = pattern[ i - SEGMENT_DISPLAY_START_LED ];
	}
	updateLights();
}

void lightShow()
{
	clearRPM();
	setAutoUp(0);
	updateLights();
	for( uint8_t i = 0; i < SHIFT_LIGHT_COUNT/2; ++i )
	{
		ledStates[SHIFT_LIGHT_COUNT/2+i] = 1;
		ledStates[SHIFT_LIGHT_COUNT/2-i] = 1;
		updateLights();
		_delay_ms(5);
	}
	setAutoUp(1);
	updateLights();
	_delay_ms(5);
	setAutoUp(0);
	updateLights();
}

/*
 * For flexing
 */
void writeBinary( uint32_t num )
{
	uint8_t pos = 0;
	for( uint8_t i = SHIFT_LIGHT_COUNT - 1; i > 17; --i )
	{
		ledStates[ i ] = (num & ( 1 << pos )) != 0;
		++pos;
	}
}
















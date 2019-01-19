#include "lightControl.h"
#include "shiftRegisters.h"
#include <stdint.h>

// Internal model of the LED states
static unsigned char ledStates[ LED_COUNT ];

// TODO - define patterns
// Shift register output patterns that produce decimal digits on 7 segment display
static unsigned char segmentPatterns[ NUM_GEARS ][ SEGMENT_DISPLAY_LED_COUNT ] = {
	{ 0, 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 0, 0}
};

/*
 * Shift the bits stored in the internal model of the LEDS to the outputs of the shift registers.
 *
 */
void updateLights()
{
	shiftPattern( ledStates, LED_COUNT );
}

/*
 * Based on a given RPM reading, change the internal model of the shift lights.
 * @param[in] rpm - 0-10500, the given RPM
 *
 */
void setRPM( unsigned int rpm )
{
	unsigned int numLights = ((float) rpm / MAX_RPM) * LED_COUNT;

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
void setCriticalError( unsigned char state )
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
	if( position > NUM_GEARS )
		position = NUM_GEARS;

	for( unsigned short int i = SEGMENT_DISPLAY_START_LED; i < SEGMENT_DISPLAY_LED_COUNT; ++i )
	{
		ledStates[ i ] = segmentPatterns[ position - 1 ][ i - SEGMENT_DISPLAY_START_LED ];
	}
}

void writeBinary( uint32_t num )
{
	uint8_t pos = 0;
	for( uint8_t i = SHIFT_LIGHT_COUNT - 1; i > 17; --i )
	{
		ledStates[ i ] = (num & ( 1 << pos )) != 0;
		++pos;
	}
}
















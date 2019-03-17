#include "configuration.h"

#include <avr/eeprom.h>

// Thresholds for setting the error/warning lights on the dash.
// These values are dynamically set from EEPROM storage

// RPM engine must reach for shift lights to start lighting up
static uint16_t shiftLightStart;

// Temperature (deg C) water must reach to trigger warning light
static uint8_t waterTWarning;

// Temperature (deg C) water must reach to trigger error light
static uint8_t waterTError;

// Pressure (bar) oil must reach to trigger warning light
static uint8_t oilPWarning;

// Pressure (bar) oil must reach to trigger error light
static uint8_t oilPError;

// Temperature (deg C) water must reach before car should be driven
static uint8_t waterTHold;

// Histeresis for warning/error lights around oil pressure
static uint8_t oilPHisteresis;

// Histeresis for warning/error lights around water temperature
static uint8_t waterTHisteresis;

void initializeConfiguration()
{
	shiftLightStart = eeprom_read_word( SHIFT_LIGHT_START_ADDR );

	waterTWarning = eeprom_read_byte( WATER_T_WARNING_ADDR );

	waterTError = eeprom_read_byte( WATER_T_ERROR_ADDR );

	waterTHisteresis = eeprom_read_byte( WATER_T_HISTERESIS_ADDR );

	oilPWarning = eeprom_read_byte( OIL_P_WARNING_ADDR );

	oilPError = eeprom_read_byte( OIL_P_ERROR_ADDR );

	oilPHisteresis = eeprom_read_byte( OIL_P_HISTERESIS_ADDR );

	waterTHold = eeprom_read_byte( WATER_T_HOLD_ADDR );
}

uint16_t getShiftLightStart()
{
	return shiftLightStart;
}

uint8_t getWaterTWarning()
{
	return waterTWarning;
}

uint8_t getWaterTError()
{
	return waterTError;
}

uint8_t getWaterTHisteresis()
{
	return waterTHisteresis;
}

uint8_t getOilPWarning()
{
	return oilPWarning;
}

uint8_t getOilPError()
{
	return oilPError;
}

uint8_t getOilPHisteresis()
{
	return oilPHisteresis;
}

uint8_t getWaterTHold()
{
	return waterTHold;
}

void setShiftLightStart( uint16_t rpm, uint8_t writeFlag )
{
	shiftLightStart = rpm;

	if( writeFlag )
	{
		eeprom_write_word( SHIFT_LIGHT_START_ADDR, rpm );
	}
}

void setWaterTWarning( uint8_t temp, uint8_t writeFlag )
{
	waterTWarning = temp;

	if( writeFlag )
	{
		eeprom_write_byte( WATER_T_WARNING_ADDR, temp );
	}
}

void setWaterTError( uint8_t temp, uint8_t writeFlag )
{
	waterTError = temp;

	if( writeFlag )
	{
		eeprom_write_byte( WATER_T_ERROR_ADDR, temp );
	}
}

void setWaterTHisteresis( uint8_t hist, uint8_t writeFlag )
{
	waterTHisteresis = hist;

	if( writeFlag )
	{
		eeprom_write_byte( WATER_T_HISTERESIS_ADDR, hist );
	}
}

void setOilPWarning( uint8_t pressure, uint8_t writeFlag )
{
	oilPWarning = pressure;

	if( writeFlag )
	{
		eeprom_write_byte( OIL_P_WARNING_ADDR, pressure );
	}
}

void setOilPError( uint8_t pressure, uint8_t writeFlag )
{
	oilPError = pressure;

	if( writeFlag )
	{
		eeprom_write_byte( OIL_P_ERROR_ADDR, pressure );
	}
}

void setOilPHisteresis( uint8_t hist, uint8_t writeFlag )
{
	oilPHisteresis = hist;

	if( writeFlag )
	{
		eeprom_write_byte( OIL_P_HISTERESIS_ADDR, hist );
	}
}

void setWaterTHold( uint8_t temp, uint8_t writeFlag )
{
	waterTHold = temp;

	if( writeFlag )
	{
		eeprom_write_byte( WATER_T_HOLD_ADDR, temp );
	}
}

























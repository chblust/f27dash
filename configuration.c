#include "configuration.h"

#include <avr/eeprom.h>

// Thresholds for setting the error/warning lights on the dash.
// These values are dynamically set from EEPROM storage

// RPM engine must reach for shift lights to start lighting up
static uint16_t shiftLightStart;

static CriticalParameter waterTemperature;

static CriticalParameter oilPressure;

// Temperature (deg C) water must reach before car should be driven
static uint8_t waterTHold;

/**
 * Read the values from the configuration flash into RAM.
 *
 */
void initializeConfiguration()
{
	shiftLightStart = eeprom_read_word( SHIFT_LIGHT_START_ADDR );

	waterTemperature.warningThreshold = 110;//eeprom_read_byte( WATER_T_WARNING_ADDR );

	waterTemperature.errorThreshold = 120;//eeprom_read_byte( WATER_T_ERROR_ADDR );

	waterTemperature.histeresis = 5;//eeprom_read_byte( WATER_T_HISTERESIS_ADDR );

	oilPressure.warningThreshold = 10;//eeprom_read_byte( OIL_P_WARNING_ADDR );

	oilPressure.errorThreshold = 2;//eeprom_read_byte( OIL_P_ERROR_ADDR );

	oilPressure.histeresis = 3;//eeprom_read_byte( OIL_P_HISTERESIS_ADDR );

	waterTHold = eeprom_read_byte( WATER_T_HOLD_ADDR );

	waterTemperature.errorDirection = ABOVE;
	waterTemperature.state = NOMINAL;
	oilPressure.errorDirection = BELOW;
	oilPressure.state = NOMINAL;
}

CriticalParameter* getWaterTemperatureParameter()
{
	return &waterTemperature;
}

CriticalParameter* getOilPressureParameter()
{
	return &oilPressure;
}

uint16_t getShiftLightStart()
{
	return 7000;//shiftLightStart;
}

uint8_t getWaterTHold()
{
	return waterTHold;
}
























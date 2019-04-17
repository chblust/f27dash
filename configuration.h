#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <stdint.h>
#include "CriticalParameter.h"

#define SHIFT_LIGHT_START_ADDR 		(uint16_t*)	0x10
#define WATER_T_WARNING_ADDR 		(uint8_t*)  0x20
#define WATER_T_ERROR_ADDR 			(uint8_t*)  0x21
#define WATER_T_HISTERESIS_ADDR 	(uint8_t*) 	0x22
#define OIL_P_WARNING_ADDR 			(uint8_t*)  0x30
#define OIL_P_ERROR_ADDR 			(uint8_t*) 	0x31
#define OIL_P_HISTERESIS_ADDR 		(uint8_t*) 	0x32
#define WATER_T_HOLD_ADDR 			(uint8_t*) 	0x40

void initializeConfiguration();

uint16_t getShiftLightStart();

CriticalParameter* getWaterTemperatureParameter();

CriticalParameter* getOilPressureParameter();

uint8_t getWaterTHold();

#endif // CONFIGURATION_H
#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <stdint.h>

#define SHIFT_LIGHT_START_ADDR (uint16_t*) 0x10
#define WATER_T_WARNING_ADDR (uint8_t*) 0x20
#define WATER_T_ERROR_ADDR (uint8_t*) 0x21
#define WATER_T_HISTERESIS_ADDR (uint8_t*) 0x22
#define OIL_P_WARNING_ADDR (uint8_t*) 0x30
#define OIL_P_ERROR_ADDR (uint8_t*) 0x31
#define OIL_P_HISTERESIS_ADDR (uint8_t*) 0x32
#define WATER_T_HOLD_ADDR (uint8_t*) 0x40

void initializeConfiguration();

uint16_t getShiftLightStart();

uint8_t getWaterTWarning();

uint8_t getWaterTError();

uint8_t getWaterTHisteresis();

uint8_t getOilPWarning();

uint8_t getOilPError();

uint8_t getOilPHisteresis();

uint8_t getWaterTHold();

void setShiftLightStart( uint16_t rpm, uint8_t writeFlag );

void setWaterTWarning( uint8_t temp, uint8_t writeFlag );

void setWaterTError( uint8_t temp, uint8_t writeFlag );

void setWaterTHisteresis( uint8_t hist, uint8_t writeFlag );

void setOilPWarning( uint8_t pressure, uint8_t writeFlag );

void setOilPError( uint8_t pressure, uint8_t writeFlag );

void setOilPHisteresis( uint8_t hist, uint8_t writeFlag );

void setWaterTHold( uint8_t temp, uint8_t writeFlag );

#endif // CONFIGURATION_H
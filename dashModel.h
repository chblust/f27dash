#ifndef DASH_MODEL_H
#define DASH_MODEL_H

#include <stdint.h>

typedef struct
{
	uint8_t gear;
	uint16_t RPM;
	uint8_t oilTemperature;
	uint8_t waterTemperature;
	uint8_t oilPressure;
	uint16_t batteryVoltage;
	uint8_t lambdaControl;
	uint8_t DRS;
	uint8_t autoUp;
} DashModel;

#endif // DASH_MODEL_H
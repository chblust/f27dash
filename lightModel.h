#ifndef LIGHTMODEL_H
#define LIGHTMODEL_H

#include "dashModel.h"

typedef struct
{
	uint16_t RPM;
	uint8_t gear;
	uint8_t error: 1;
	uint8_t warning: 1;
	uint8_t hold: 1;
	uint8_t DRS: 1;
	uint8_t autoUp: 1;
} LightModel;

void createLightModel( LightModel * lightModel, DashModel * dashModel );

uint8_t compareLightModel( LightModel * a, LightModel * b );

#endif // LIGHTMODEL_H
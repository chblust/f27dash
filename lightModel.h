#ifndef LIGHTMODEL_H
#define LIGHTMODEL_H

#include "dashModel.h"

#define MAX_RPM 10500

typedef struct
{
	uint8_t RPM;
	uint8_t gear;
	uint8_t error: 1;
	uint8_t warning: 1;
	uint8_t hold: 1;
	uint8_t DRS: 1;
	uint8_t autoUp: 1;
} LightModel;

void updateLightModel( LightModel* lightModel, DashModel * dashModel );

void defaultLightModel( LightModel* lightModel );

#endif // LIGHTMODEL_H
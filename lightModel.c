#include "lightModel.h"
#include "CriticalParameter.h"
#include "configuration.h"

#include <stdint.h>

/**
 * Set light values in a given light Model to represent the provided
 * car data.
 * @param[in] lightModel - the given light model
 * @param[in] dashModel - the provided car data
 *
 */
void updateLightModel( LightModel * lightModel, DashModel * dashModel )
{
	// Don't light up any shift lights if the RPM is below the configured value
	if( dashModel->RPM < getShiftLightStart() )
	{
		lightModel->RPM = 0;
	}
	else
	{
		// Simple linear function for the shift lights
		lightModel->RPM = 100 * ((float)(dashModel->RPM-getShiftLightStart())/(MAX_RPM - getShiftLightStart()));
	}

	lightModel->gear = dashModel->gear;

	CriticalParameter* waterTemperature = getWaterTemperatureParameter();
	CriticalParameter* oilPressure = getOilPressureParameter();

	updateParameter( waterTemperature, dashModel->waterTemperature );
	updateParameter( oilPressure, dashModel->oilPressure );

	if( waterTemperature->state == ERROR || oilPressure->state == ERROR )
	{
		lightModel->error = 1;
		lightModel->warning = 0;
	}
	else if( waterTemperature->state == WARNING || oilPressure->state == WARNING )
	{
		lightModel->warning = 1;
		lightModel->error = 0;
	}
	else
	{
		lightModel->error = 0;
		lightModel->warning = 0;
	}

	// These are togglable, no need for histeresis
	lightModel->DRS = dashModel->DRS;
	lightModel->autoUp = dashModel->autoUp;

	// Hold could use histeresis (for water T) but it probably won't go back down
	// below threshold during a driving period.
	lightModel->hold |= !dashModel->lambdaControl;
	lightModel->hold |= dashModel->waterTemperature < getWaterTHold();
}

/**
 * Zero out the values of a given light model to avoid unintented light shows.
 * @param[in] lightModel - the given light model
 *
 */
void defaultLightModel( LightModel* lightModel )
{
	lightModel->RPM = 0;
	lightModel->gear = 0;
	lightModel->DRS = 0;
	lightModel->warning = 0;
	lightModel->error = 0;
	lightModel->hold = 0;
}
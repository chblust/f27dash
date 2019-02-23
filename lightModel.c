#include "lightModel.h"

#include <stdint.h>

// Thresholds for setting the error/warning lights on the dash.
// TODO - define dynamically
static uint8_t waterTWarning = 120;
static uint8_t waterTError = 135;
static uint8_t oilPWarning = 8;
static uint8_t oilPError = 4;

static uint8_t waterTHold = 80;
static uint8_t oilPHisteresis = 1;
static uint8_t waterTHisteresis = 5;

void createLightModel( LightModel * lightModel, DashModel * dashModel )
{
	lightModel->RPM = dashModel->RPM;

	lightModel->gear = dashModel->gear;

	// If there's already an error, check whether it's for oilP or waterT
	if( lightModel->error )
	{
		// Apply waterT histeresis
		if( dashModel->waterTemperature < waterTError - waterTHisteresis )
		{
			lightModel->error = 0;
		}
		// Apply oilP histeresis
		else if( dashModel->oilPressure > oilPError + oilPHisteresis )
		{
			lightModel->error = 0;
		}
	}
	// If no error, check if there should be one
	else if( dashModel->oilPressure < oilPError ||
			 dashModel->waterTemperature > waterTError )
	{
		lightModel->warning = 0;
		lightModel->error = 1;
	}
	// If no error still, check if there's already a warning and determine source
	else if( lightModel->warning )
	{
		if( dashModel->waterTemperature < waterTWarning - waterTHisteresis )
		{
			lightModel->error = 0;
		}
		else if( dashModel->oilPressure > oilPWarning + oilPHisteresis )
		{
			lightModel->error = 0;
		}
	}
	// If no warning, check if there should be one
	else if (dashModel->oilPressure < oilPWarning ||
			dashModel->waterTemperature > waterTWarning )
	{
		lightModel->error = 0;
		lightModel->warning = 1;
	}
	// All clear
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
	lightModel->hold |= dashModel->waterTemperature < waterTHold;
}
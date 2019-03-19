#include "dashModel.h"

/**
 * Zero out the values in the dash model to avoid unintended light shows.
 * @param[in] model - model to zero out
 *
 */
void defaultDashModel( DashModel* model )
{
	model->gear = 0;
	model->RPM = 0;
	model->oilTemperature = 0;
	model->waterTemperature = 0;
	model->oilPressure = 0;
	model->batteryVoltage = 0;
	model->lambdaControl = 0;
	model->DRS = 0;
	model->autoUp = 0;
	model->flowControl = 0;
	model->turboOilPressure = 0;
}
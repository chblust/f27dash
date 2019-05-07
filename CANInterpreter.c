#include "CANInterpreter.h"
#include "dashModel.h"

static void processECU1( CANMessage * message, DashModel * dashModel );
static void processECU2( CANMessage * message, DashModel * dashModel );
//static void processECU3( CANMessage * message, DashModel * dashModel );

static MessageHandler messageHandlers[] = 
{
	{ ECU_MSG_1, processECU1 },
	{ ECU_MSG_2, processECU2 },
	//{ 0x69, processECU3 }
};

/*
 * Service the provided CAN message with its given routine.
 * 
 */
void processIncomingMessage( CANMessage * message, DashModel * dashModel )
{
	for( uint8_t i = 0; i < sizeof( messageHandlers ); ++i )
	{
		if( messageHandlers[i].messageID == message->id )
		{
			messageHandlers[i].function( message, dashModel );
			break;
		}
	}
}

/*
 * Pick apart the primary ECU message to fill the dash model in with current data.
 * @param[in] message - the ECU message
 * @param[out] dashModel - the model to fill in
 *
 */
static void processECU1( CANMessage * message, DashModel * dashModel )
{
	uint16_t rpm = (message->data[RPM_MSB] << 8) | message->data[RPM_LSB];
	if (rpm < 1000)
		rpm = 0;
	else
		rpm -= 1000;
	dashModel->RPM = rpm;

	dashModel->oilTemperature = message->data[OILT_LSB];

	dashModel->waterTemperature = message->data[WATERT_LSB];

	dashModel->oilPressure = message->data[OILP_LSB];

	dashModel->gear = message->data[GEAR_LSB];

	dashModel->DRS = (message->data[DRS_LSB]);

	dashModel->autoUp = (message->data[AUTOUP_LSB]);
}

static void processECU2( CANMessage* message, DashModel* dashModel )
{
	dashModel->turboOilPressure = message->data[ TOILP_MSB ];

	dashModel->flowControl = message->data[ FLC_MSB ];

	dashModel->lambdaControl = message->data[ LCTL ];
}

/*static void processECU3( CANMessage * message, DashModel * dashModel )
{
	dashModel->RPM = (message->data[0]) | (message->data[1] << 8);
}*/

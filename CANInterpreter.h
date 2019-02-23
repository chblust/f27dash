#ifndef CANINTERPRETER_H
#define CANINTERPRETER_H

#include "dashModel.h"
#include "can.h"
#include <stdint.h>

#define ECU_MSG_1 0x00FF
#define ECU_MSG_2 0x00FC
#define ECU_MSG_3 0x00FD
#define ECU_MSG_4 0x00FB

#define CONFIGURATION_MSG 0x0027

// Indexes of components of engine parameters within their respective CAN messages.

// ECU_MSG_1
#define RPM_MSB 0
#define RPM_LSB 1
#define OILT_LSB 2
#define WATERT_LSB 3
#define OILP_LSB 4
#define GEAR_LSB 5

// ECU_MSG_2
#define BATT_MSB 0
#define BATT_LSB 1

// Pairs a CAN message with its associated handler function
typedef struct 
{
	uint16_t messageID;
	void (*function)( CANMessage * message, DashModel * model );
} MessageHandler;

void processIncomingMessage( CANMessage * message, DashModel * model );

#endif // CANINTERPRETER_H
/*
 * DriverTest.c
 *
 * Created: 1/9/2019 5:56:32 PM
 * Author : Chris Blust
 */ 

#include "lightControl.h"
#include "lightModel.h"
#include "can.h"
#include "CANInterpreter.h"
#include "configuration.h"

#include <avr/eeprom.h>
#include <util/delay.h>

/**
 * Write data to the shift registers based on the provided
 * light model and update the lights.
 * @param[in] lightModel - the provided light model
 * 
 */
void writeLightModel( LightModel * lightModel )
{
	// Update the shift register pattern model for each component
	setRPM( lightModel->RPM );
	setGearPosition( lightModel->gear );
	setError( lightModel->error );
	setWarning( lightModel->warning );
	//setHold( lightModel->hold );
	setDRS( lightModel->DRS );
	setAutoUp( lightModel->autoUp );

	// Tell the shift registers to update their outputs.
	updateLights();
}

/**
 * Write data to an eeprom address, all specified by the given CAN message.
 * @param[in] message - the CAN message
 *
 */
void handleConfigurationMessage( CANMessage* message )
{
	// Extract the address and the length from the message
	uint8_t* address = (uint8_t*) ((message->data[0] << 8) | message->data[1]);
	uint8_t length = message->data[2];

	// Write the data to either a word or a byte in eeprom
	if( length == 1 )
	{
		uint8_t toWrite = message->data[3];
		eeprom_write_byte( address, toWrite );
	}
	else
	{
		uint16_t toWrite = (message->data[3] << 8) | message->data[4];
		eeprom_write_word( (uint16_t*)address, toWrite );
	}

	// Read the updated values from eeprom
	initializeConfiguration();
}

void CCSLS()
{
	lightShow();
	write7Seg(0, 1, 1, 1, 0, 0, 1, 0); // C
	_delay_ms(250);
	write7Seg(0, 0, 0, 0, 0, 0, 0, 0);
	lightShow();
	write7Seg(0, 1, 1, 1, 0, 0, 1, 0); // C
	_delay_ms(250);
	write7Seg(0, 0, 0, 0, 0, 0, 0, 0);
	lightShow();
	write7Seg(1, 1, 0, 1, 1, 0, 1, 0); // S
	_delay_ms(250);
	write7Seg(0, 0, 0, 0, 0, 0, 0, 0);
	lightShow();
	write7Seg(0, 1, 1, 1, 0, 0, 0, 0); // L
	_delay_ms(250);
	write7Seg(0, 0, 0, 0, 0, 0, 0, 0);
	lightShow();
	write7Seg(1, 1, 0, 1, 1, 0, 1, 0); // S
	_delay_ms(250);
	clearRPM();
}

void F27()
{
	lightShow();
	write7Seg(1, 1, 1, 0, 0, 0, 1, 0); // F
	_delay_ms(250);
	write7Seg(0, 0, 0, 0, 0, 0, 0, 0);
	lightShow();
	write7Seg(1, 0, 1, 1, 0, 0, 1, 1); // 2
	_delay_ms(250);
	write7Seg(0, 0, 0, 0, 0, 0, 0, 0);
	lightShow();
	write7Seg(0, 0, 0, 0, 1, 0, 1, 1); // 7
	_delay_ms(250);
	clearRPM();
}

int main( void )
{
	//CCSLS();
	F27();
	// Read light thresholds and such from flash
	initializeConfiguration();

	// Configure generic CAN registers
	initCAN();
	
	// Configure generic USART registers
	//USART1Init(1, 1);

	// Create a blank dash model.
	// The dash model encapsulates vehicle information received from CAN messages
	DashModel dashModel;
	defaultDashModel( &dashModel );

	// Create a blank light model.
	// The light model represents the different LEDS on the driver display.
	LightModel lightModel;
	defaultLightModel( &lightModel );
	writeLightModel( &lightModel );

	// Configure receive MObs with single message filters in the CAN controller.
	listenForMessage( ECU_MSG_1, 8 );
	listenForMessage( ECU_MSG_2, 8 );
	listenForMessage( CONFIGURATION_MSG, 8 );

	// Default the shift lights.
	updateLights();
	while(1)
	{
		CANMessage received;

		if( getMessage( &received ) )
		{		
			if( received.id == CONFIGURATION_MSG )
			{
				handleConfigurationMessage( &received );
			}
			else
			{
				// Interpret what's in the message
			 	processIncomingMessage( &received, &dashModel );

			 	// Update the LED representation based on the new data
			 	updateLightModel( &lightModel, &dashModel );

			 	// Update the LEDs on the driver display with the light model
			 	writeLightModel( &lightModel );
			}
		}
	}
	
}


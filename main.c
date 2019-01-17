/*
 * DriverTest.c
 *
 * Created: 1/9/2019 5:56:32 PM
 * Author : chb4299
 */ 

#define F_CPU 8000000UL

#include "lightControl.h"
#include <util/delay.h>

int main(void)
{
	while( 1 )
	{
		setAutoUp(0);
		setCriticalError(0);
		setWarning(0);
		setHold(0);
		for( unsigned int i = 0; i < MAX_RPM; i += 100 )
		{
			setRPM( i );
			_delay_ms( 20 );
			updateLights();
		}
	}
}


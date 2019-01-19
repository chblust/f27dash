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
	uint32_t i = 0;
	while( 1 )
	{
		writeBinary( i );
		updateLights();
		//_delay_ms(25);
		++i;
	}
}


/*
 * DriverTest.c
 *
 * Created: 1/9/2019 5:56:32 PM
 * Author : chb4299
 */ 

#include "lightControl.h"
#include "can.h"
#include "usart.h"

#include <util/delay.h>

int main(void)
{
	initCAN();
	
	USART1Init(1, 1);


	while(1)
	{
		
	}
}


#include "diagnosticLCD.h"
#include "usart.h"

char hexDigit( uint8_t d )
{
	if( d < 10 )
	{
		return '0' + d;
	}
	else
	{
		return 'A' + (d - 10);
	}
}

void updateLCD( DashModel * dashModel )
{
	char message[18];
	message[0] = 'M';
	message[1] = hexDigit((dashModel->RPM & 0xF000) >> 12);
	message[2] = hexDigit((dashModel->RPM & 0x0F00) >> 8);
	message[3] = hexDigit((dashModel->RPM & 0x00F0) >> 4);
	message[4] = hexDigit(dashModel->RPM & 0x000F);
	message[5] = hexDigit((dashModel->oilTemperature & 0xF0) >> 4);
	message[6] = hexDigit(dashModel->oilTemperature & 0x0F);
	message[7] = hexDigit((dashModel->waterTemperature & 0xF0) >> 4);
	message[8] = hexDigit(dashModel->waterTemperature & 0x0F);
	message[9] = hexDigit((dashModel->oilPressure & 0xF0) >> 4);
	message[10] = hexDigit(dashModel->oilPressure & 0x0F);
	message[11] = hexDigit((dashModel->flowControl & 0xF0) >> 4);
	message[12] = hexDigit(dashModel->flowControl & 0x0F);
	message[13] = hexDigit((dashModel->turboOilPressure & 0xF0) >> 4);
	message[14] = hexDigit(dashModel->turboOilPressure & 0x0F);
	message[15] = hexDigit(dashModel->gear);
	message[16] = hexDigit(dashModel->lambdaControl);
	message[17] = 'X';

	USART1WriteStringDangerous( message, 18 );
	USART1Transmit('\n');
}
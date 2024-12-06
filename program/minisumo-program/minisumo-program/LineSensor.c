#include "LineSensor.h"


void LineSensor_Init(void)
{
	DDRC &= ~(0x3 << 0); // Input on pin 0 and 1 of port C
}

uint8_t LineSensor_Read(void)
{
	if ((PORTC & (1 << PC0)) || (PORTC & (1 << PC1))) // If one of the line sensors outputs is high
	{
		return LINE;
	}
	else
	{
		return NOLINE;
	}
}
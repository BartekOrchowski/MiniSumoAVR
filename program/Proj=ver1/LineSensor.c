#include "LineSensor.h"


void LineSensor_Init(void)
{
	DDRC &= ~((1 << PC0) | (1 << PC1)); // Input on pin 0 and 1 of port C
	//PORTC &= ~((1 << PC0) | (1 << PC1)); wlacz&/wylacz| pull up
}

uint8_t LineSensor_Read(void)
{
	if ((PINC & (1 << PC0)) || (PINC & (1 << PC1))) // If one of the line sensors outputs is high
	{
		return NOLINE;
	}
	else
	{
		return LINE;
	}
}
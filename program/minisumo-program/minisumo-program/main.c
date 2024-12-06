/*
 * minisumo-program.c
 *
 * Created: 06.12.2024 23:23:59
 * Author : HP
 */ 

#include <avr/io.h>
#include <stdint.h>
#include "LineSensor.h"

int main(void)
{
	while(1)
	{
		if(LineSensor_Read()==LINE)
		{
			
		}
		else
		{
			
		}
	}
}


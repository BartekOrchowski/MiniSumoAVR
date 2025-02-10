#include <avr/io.h>
#include <stdint.h>
#include <avr/delay.h>
#include <avr/interrupt.h>
#include "LineSensor.h"
#include "DistanceSensor.h"
#include "Motor.h"

#define TOLERANCE 5 
#define F_CPU 16000000U		/////////////////////////////////////////trzeba jakos zmienic na fuseach
	
int main(void)
{
	// Interrupts enable
	sei();
	
	// Line sensor config
	LineSensor_Init();

	// I2C config
	I2C_Init();
	
	// Distance sensors config
	Xshut_Init();
	DistanceSensor_Init();
	//Timeline 
	Timer1_Init();
	
	//Motor config
	Motor_Init();
	
	while (1)
	{
		if(LineSensor_Read())
		{
			// GoBack();
		}

		if((distance1 == 0) && (distance2 == 0) && (distance3 == 0) && (distance4 == 0)) //noone spotted 
		{
			//MotorDriver_Spin();
		}
		
		if ((distance3 < distance2) && (distance3 < distance1) && (distance3 < distance4)) //if oponent on the right
		{
			while((distance1-TOLERANCE)<(distance2-TOLERANCE)) 
			{
				//MotorDriver_GoRight();
			}
		}
		
		if ((distance4 < distance2) && (distance4 < distance1) && (distance4 < distance3)) //if oponent on the left
		{
			while((distance1-TOLERANCE)<(distance2-TOLERANCE))
			{
				//MotorDriver_GoLeft();
			}
		}		
	}
}

volatile uint16_t distance1;
volatile uint16_t distance2;
volatile uint16_t distance3;
volatile uint16_t distance4;

ISR(TIMER1_COMPA_vect)
{
	distance1 = DistanceSensor_Read(SENSOR1_ADDR); //pd0 use a cable	central right = x1
	distance2 = DistanceSensor_Read(SENSOR2_ADDR); //pd1 use a cable	central left = x2
	distance3 = DistanceSensor_Read(SENSOR3_ADDR);	//pb1	right sensor x3
	distance4 = DistanceSensor_Read(SENSOR4_ADDR);	//pb2	left sensor x4
	
}
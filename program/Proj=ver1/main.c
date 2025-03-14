#define F_CPU 16000000UL /////////////////////////////////////////trzeba jakos zmienic na fuseach

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "LineSensor.h"
#include "DistanceSensor.h"
#include "Motor.h"

//typedef enum {
	//uint8_t DIRECTION_FORWARD,
	//uint8_t DIRECTION_RIGHT 2,
	//uint8_t DIRECTION_LEFT 3,
	//uint8_t DIRECTION_CIRCLE 4
//} Direction;	

#define DIRECTION_FORWARD 1
#define DIRECTION_RIGHT 2
#define DIRECTION_LEFT 3
#define DIRECTION_CIRCLE 4
volatile uint16_t distance1;
volatile uint16_t distance2;
volatile uint16_t distance3;
volatile uint16_t distance4;
volatile uint8_t current_direction;
	
int main(void)
{
	sei(); // W³¹czenie przerwañ, 
	
	// Inicjalizacja silników
	Motor_Init(); 
	//Inicjalizacja sensorow linii
	LineSensor_Init();
	//Inicjalizacja sensorow dystansu
	DistanceSensor_Init();
	
	while (1)
	{	
		
		if(LineSensor_Read()==LINE)
		{
			Motor_Backwards();
		}
		switch (current_direction) 
		{
			case DIRECTION_FORWARD:
			Motor_Straight();
			break;
			case DIRECTION_RIGHT:
			Motor_Right();
			break;
			case DIRECTION_LEFT:
			Motor_Left();
			break;
			case DIRECTION_CIRCLE:
			Motor_Circle();
			break;
		}
	}
}

ISR(TIMER1_COMPA_vect)
{
	distance1 = DistanceSensor_Read(SENSOR1_ADDR); // Central right
	distance2 = DistanceSensor_Read(SENSOR2_ADDR); // Central left
	distance3 = DistanceSensor_Read(SENSOR3_ADDR); // Right side
	distance4 = DistanceSensor_Read(SENSOR4_ADDR); // Left side

	// Prosta logika sterowania silnikami
	if (distance1 < 100 || distance2 < 100) // Przeszkoda z przodu
	{
		current_direction = DIRECTION_FORWARD; 
	}
	else if (distance3 < 100) // Przeszkoda z prawej strony
	{
		current_direction = DIRECTION_RIGHT;
	}
	else if (distance4 < 100) // Przeszkoda z lewej strony
	{
		current_direction = DIRECTION_LEFT;
	}
	else
	{
		 current_direction = DIRECTION_CIRCLE;
	}
}


#define F_CPU 16000000UL 

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "LineSensor.h"
#include "DistanceSensor.h"
#include "Motor.h"

void TimeBase_Init(void);


#define DIRECTION_FORWARD 1
#define DIRECTION_RIGHT 2
#define DIRECTION_LEFT 3
#define DIRECTION_CIRCLE 4
#define DIRECTION_BACKWARD 5

volatile uint16_t distance1;
volatile uint16_t distance2;
volatile uint16_t distance3;
volatile uint16_t distance4;
volatile uint8_t current_direction;

	
int main(void)
{
	//Inicjalizacja podzialu czasu
	TimeBase_Init();
	sei(); // W³¹czenie przerwañ, 
	
	// Inicjalizacja silników
	Motor_Init(); 
	//Inicjalizacja sensorow linii
	LineSensor_Init();
	//Inicjalizacja sensorow dystansu
	DistanceSensor_Init();
	
	
	while (1)
	{	
		//// Prosta logika sterowania silnikami
		//if (distance1 < 20 || distance2 < 20) // Przeszkoda z przodu
		//{
		//current_direction = DIRECTION_FORWARD;
		//}
		//else if (distance3 < 10) // Przeszkoda z prawej strony
		//{
		//current_direction = DIRECTION_RIGHT;
		//}
		//else if (distance4 < 10) // Przeszkoda z lewej strony
		//{
		//current_direction = DIRECTION_LEFT;
		//}
		//else
		//{
		//current_direction = DIRECTION_CIRCLE;
		//}
		
		//switch (current_direction)
		//{
			//case DIRECTION_FORWARD:
			//Motor_Test();	
			////Motor_Straight();	
			//break;
			////case DIRECTION_RIGHT:
			////Motor_Right();
			////break;
			////case DIRECTION_LEFT:
			////Motor_Left();
			////break;
			////case DIRECTION_CIRCLE:
			////Motor_Circle();
			////break;
			//case DIRECTION_BACKWARD:
			//Motor_Backwards();
			//break;
			//default:
			//OCR0A = 0;
			//OCR0B = 0;
			//break;
		//}	
		Motor_Test();	
	}
}

ISR(TIMER1_OVF_vect)
{
	/*********************************************************************
	
	zawsze odczytuje wysokie napiêcie nie wazne co jest pod 
	
	*********************************************************************/
	
	if(LineSensor_Read() == LINE)
	{
		current_direction = DIRECTION_BACKWARD;  //nie wiem kiedy niby to odczytuje 
	}
	else
	{
		current_direction = DIRECTION_FORWARD;  //na bia³ym stole odczytuje to
	}
	
	//distance1 = DistanceSensor_Read(SENSOR1_ADDR); // Central right
	//distance2 = DistanceSensor_Read(SENSOR2_ADDR); // Central left
	//distance3 = DistanceSensor_Read(SENSOR3_ADDR); // Right side
	//distance4 = DistanceSensor_Read(SENSOR4_ADDR); // Left side
}

void TimeBase_Init(void)
{
	//inicjalizacja podzialu czasu typu SysTick
	TIMSK1 |= (1<<TOIE1);
	TCCR1B |= (1 << CS10);          // Prescaler = 1 overflow co 4ms przy 16Mhz fcpu
}
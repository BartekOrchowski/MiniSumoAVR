#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "LineSensor.h"
#include "DistanceSensor.h"
#include "Motor.h"

#define TOLERANCE 5 
#define F_CPU 16000000U		/////////////////////////////////////////trzeba jakos zmienic na fuseach
	
int main(void)
{
	sei(); // W��czenie przerwa�, je�li s� potrzebne

	Motor_Init(); // Inicjalizacja silnik�w
	DDRD |= (1 << PD5); // Wymuszenie PD5 jako wyj�cia
	PORTD &= ~(1 << PD5); // Wy��czenie wszelkich stan�w pocz�tkowych

	// Ustawienie kierunku obrotu lewego silnika (PC2 i PC3)
	PORTC |= (1 << PC2);
	PORTC &= ~(1 << PC3);

	// Ustawienie kierunku obrotu prawego silnika (PD4 i PD7)
	PORTD |= (1 << PD4);
	PORTD &= ~(1 << PD7);
	
	while (1)
	{
		//// Tylko lewy silnik na pe�nej mocy
		OCR0A = 128;  // Pe�na moc dla lewego silnika
		OCR0B = 128;    // Prawy silnik wy��czony
		_delay_ms(2000);

		//// Tylko prawy silnik na pe�nej mocy
		OCR0A = 255;    // Lewy silnik wy��czony
		OCR0B = 128;  // Pe�na moc dla prawego silnika
		_delay_ms(2000);
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


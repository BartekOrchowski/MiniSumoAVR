#include "Motor.h"

  //  Timer0  PWM PD6 (OC0A) i PD5 (OC0B)
  void Timer0_Init()
  {
	  //Fast PWM (WGM02 = 0, WGM01 = 1, WGM00 = 1)
	  TCCR0A |= (1 << WGM00) | (1 << WGM01);
	  TCCR0B |= (1 << CS01) | (1 << CS00);  // Prescaler 64

	  //PWM OC0A (PD6) i OC0B (PD5)
	  TCCR0A |= (1 << COM0A1) | (1 << COM0B1);

	  // turn off the motors
	  OCR0A = 0;
	  OCR0B = 0;

	  // output (PWM)
	  DDRD |= (1 << PD6) | (1 << PD5);
  }

  //pins for directions of both motors
  void Motor_Init()
  {
	  Timer0_Init();
	  // Ustawienie PC2, PC3 (lewy silnik) i PD4, PD7 (prawy silnik) jako wyjœcia
	  DDRC |= (1 << PC2) | (1 << PC3);
	  DDRD |= (1 << PD4) | (1 << PD7);
  }
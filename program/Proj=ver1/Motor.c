#include "Motor.h"

//#define TEST 

  // Inicjalizacja Timer0 do generowania PWM na PD6 (OC0A) i PD5 (OC0B)
  void Timer0_Init()
  {
	  // Ustawienie Fast PWM (WGM02 = 0, WGM01 = 1, WGM00 = 1)
	  TCCR0A = 0;
	  TCCR0B = 0;
	  TCCR0A |= (1 << WGM00) | (1 << WGM01);
	  TCCR0B &= ~(1 << WGM02); // Upewnij siê, ¿e WGM02 jest wyzerowane
	  TCCR0B |= (1 << CS01) | (1 << CS00);  // Prescaler 64

	  // W³¹czenie PWM na OC0A (PD6) i OC0B (PD5), tryb nieodwracaj¹cy
	  TCCR0A |= (1 << COM0A1) | (1 << COM0B1);

	  // Ustawienie pocz¹tkowego wype³nienia PWM na 0 (silniki wy³¹czone)
	  OCR0A = 0;
	  OCR0B = 0;

	  // Ustawienie PD6 i PD5 jako wyjœcia (PWM)
	  DDRD |= (1 << PD6) | (1 << PD5);
  }

  // Inicjalizacja pinów kierunku (DIR_1 i DIR_2 dla obu silników)
  void Motor_Init()
  {
	  Timer0_Init();
	  // Ustawienie PC2, PC3 (lewy silnik) i PD4, PD7 (prawy silnik) jako wyjœcia
	  DDRC |= (1 << PC2) | (1 << PC3);
	  DDRD |= (1 << PD4) | (1 << PD7);
  }
  
  void Motor_Backwards(void)
  {
	  //kierunek w tyl
	  PORTD &= ~(1 << PD4);
	  PORTD |= (1 << PD7);
	  PORTC &= ~(1 << PC2);
	  PORTC |= (1 << PC3);
	  
	  OCR0A = 255;    // Pe³na moc dla lewego silnika
	  OCR0B = 255;  // Pe³na moc dla prawego silnika	  
  }
  
  void Motor_Straight(void)
  {
	  //kierunek w przod
	  PORTD |= (1 << PD4);
	  PORTD &= ~(1 << PD7);
	  PORTC |= (1 << PC2);
	  PORTC &= ~(1 << PC3);
	  
	  OCR0A = 255;    // Pe³na moc dla lewego silnika
	  OCR0B = 255;  // Pe³na moc dla prawego silnika
  }
  
  void Motor_Left(void)
  {
	  //kierunek w przod
	  PORTD |= (1 << PD4);
	  PORTD &= ~(1 << PD7);
	  PORTC |= (1 << PC2);
	  PORTC &= ~(1 << PC3);
	  
	  OCR0A = 128;    
	  OCR0B = 255;	// Pe³na moc dla prawego silnika
  }
  
  void Motor_Right(void)
  {
	  //kierunek w przod
	  PORTD |= (1 << PD4);
	  PORTD &= ~(1 << PD7);
	  PORTC |= (1 << PC2);
	  PORTC &= ~(1 << PC3);
	  
	  OCR0A = 255;   // Pe³na moc dla lewego silnika 
	  OCR0B = 128;	
  }
  
  void Motor_Circle(void)
  {
	  PORTD &= ~(1 << PD4);
	  PORTD |= (1 << PD7);
	  PORTC |= (1 << PC2);
	  PORTC &= ~(1 << PC3);
	  
	  OCR0A = 255;    // Pe³na moc dla lewego silnika
	  OCR0B = 255;  // Pe³na moc dla prawego silnika
	  
  }
  
  //#ifdef TEST
   void Motor_Test(void)
   {
	   Motor_Backwards();
	   _delay_ms(500);
	   Motor_Circle();
	   _delay_ms(100);
	   Motor_Left();
	   _delay_ms(500);
	   Motor_Right();
	   _delay_ms(100);
	   Motor_Straight();
	   _delay_ms(1000);
	   OCR0B = 0;
	   OCR0A = 0;
	   _delay_ms(100);
   }
  // #endif
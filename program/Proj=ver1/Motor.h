#pragma once 

#include <stdint.h>
#include <avr/io.h>

  // Inicjalizacja Timer0 do generowania PWM na PD6 (OC0A) i PD5 (OC0B)
  void Timer0_Init(void);

  // Inicjalizacja pinów kierunku (DIR_1 i DIR_2 dla obu silników)
  void Motor_Init(void);
  
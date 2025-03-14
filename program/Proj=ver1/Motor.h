#pragma once 

#include <stdint.h>
#include <avr/io.h>

  // Inicjalizacja Timer0 do generowania PWM na PD6 (OC0A) i PD5 (OC0B)
  void Timer0_Init(void);
  // Inicjalizacja pinów kierunku (DIR_1 i DIR_2 dla obu silników)
  void Motor_Init(void);
   
   //Jazda do tylu
   void Motor_Backwards(void);
   //Jazda do przdou
   void Motor_Straight(void);
   //jazda w kolko
   void Motor_Circle(void);
   //jezda w prawo
   void Motor_Right(void);
   //jazda w lewo
   void Motor_Left(void);
    
    //Test silników
    void Motor_Test(void);
  
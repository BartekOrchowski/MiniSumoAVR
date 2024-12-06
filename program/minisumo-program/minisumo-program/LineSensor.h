#pragma once

#include <stdint.h> // For uint8_t
#include <avr/io.h> // For AVR macros

#define LINE 1
#define NOLINE 0

void LineSensor_Init(void);
uint8_t LineSensor_Read(void);


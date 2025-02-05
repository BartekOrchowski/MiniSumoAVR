#pragma once

#include <stdint.h>
#include <avr/io.h>
#include <avr/delay.h>				/////////////////////////////////////////////zmienic na timer 10ms 

#include "vl53l0x.h"
#include "I2C.h"

//Distance sensors
// XSHUT pins (dla czujników VL53L0X)
#define XSHUT_SENSOR1 PD0
#define XSHUT_SENSOR2 PD1				///////////////////////////////////connect x1 and x2 using jumper cables to pd0 and pd1
#define XSHUT_SENSOR3 PB1
#define XSHUT_SENSOR4 PB2

// I2C Addresses for sensors
#define SENSOR1_ADDR 0x30
#define SENSOR2_ADDR 0x31
#define SENSOR3_ADDR 0x32
#define SENSOR4_ADDR 0x33

void Xshut_Init(void);
void Xshut_Disable(uint8_t pin);
void Xshut_Enable(uint8_t pin);
void DistanceSensor_Init(void);
void DistanceSensor_SetAddr(uint8_t new_address);
uint16_t DistanceSensor_Read(uint8_t sensor_address);
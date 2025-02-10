#include "DistanceSensor.h"


void Timer1_Init(void)
{
	// Ustawienie trybu CTC (WGM12 = 1, WGM11 i WGM10 = 0)
	TCCR1A = 0;
	TCCR1B = (1 << WGM12);  // Tryb CTC

	// Ustawienie prescalera na 64 (CS11 = 1, CS10 = 1)
	TCCR1B |= (1 << CS11) | (1 << CS10);

	// Ustawienie wartoœci porównania OCR1A
	OCR1A = 49999;

	// W³¹czenie przerwañ dla Compare Match A
	TIMSK1 |= (1 << OCIE1A);
}

// XSHUT Initialization
void Xshut_Init(void)
{
	DDRD |= (1 << XSHUT_SENSOR1) | (1 << XSHUT_SENSOR2);
	PORTD |= (1 << XSHUT_SENSOR1) | (1 << XSHUT_SENSOR2);
	DDRB |= (1 << XSHUT_SENSOR3) | (1 << XSHUT_SENSOR4);
	PORTB |=  (1 << XSHUT_SENSOR3) | (1 << XSHUT_SENSOR4); // Enable all sensors
}

void Xshut_DisableD(uint8_t pin)
{
	PORTD &= ~(1 << pin); // Disable sensor
}

void Xshut_EnableD(uint8_t pin)
{
	PORTD |= (1 << pin); // Enable sensor
	_delay_ms(10);       ////////////////////////////// Wait for sensor initialization
}

void Xshut_DisableB(uint8_t pin)
{
	PORTB &= ~(1 << pin); // Disable sensor
}

void Xshut_EnableB(uint8_t pin)
{
	PORTB |= (1 << pin); // Enable sensor
	_delay_ms(10);       ////////////////////////////////// Wait for sensor initialization
}


void DistanceSensor_Init(void)
{
	// Disable all sensors
	Xshut_DisableD(XSHUT_SENSOR1);
	Xshut_DisableD(XSHUT_SENSOR2);
	Xshut_DisableB(XSHUT_SENSOR3);
	Xshut_DisableB(XSHUT_SENSOR4);

	// Enable first sensor and assign address
	Xshut_EnableD(XSHUT_SENSOR1);
	DistanceSensor_SetAddr(SENSOR1_ADDR);
	Xshut_DisableD(XSHUT_SENSOR1);

	// Enable second sensor and assign address
	Xshut_EnableD(XSHUT_SENSOR2);
	DistanceSensor_SetAddr(SENSOR2_ADDR);
	Xshut_DisableD(XSHUT_SENSOR2);

	// Enable third sensor and assign address
	Xshut_EnableB(XSHUT_SENSOR3);
	DistanceSensor_SetAddr(SENSOR3_ADDR);
	Xshut_DisableB(XSHUT_SENSOR3);

	// Enable fourth sensor and assign address
	Xshut_EnableB(XSHUT_SENSOR4);
	DistanceSensor_SetAddr(SENSOR4_ADDR);
	Xshut_DisableB(XSHUT_SENSOR4);

	// Re-enable all sensors for normal operation
	Xshut_EnableD(XSHUT_SENSOR1);
	Xshut_EnableD(XSHUT_SENSOR2);
	Xshut_EnableB(XSHUT_SENSOR3);
	Xshut_EnableB(XSHUT_SENSOR4);
}

// VL53L0X Communication
void DistanceSensor_SetAddr(uint8_t new_address)
{
	I2C_Start();
	I2C_Write(0x52); // Default address (0x29 shifted left)
	I2C_Write(0x8A); // Address register
	I2C_Write(new_address << 1); // New address shifted left
	I2C_Stop();
}

uint16_t DistanceSensor_Read(uint8_t sensor_address)
{
	uint8_t distance_high, distance_low;

	// Start reading from the sensor
	I2C_Start();
	I2C_Write(sensor_address << 1);
	I2C_Write(0x1E); // High byte register
	I2C_Start();
	I2C_Write((sensor_address << 1) | 0x01);
	distance_high = I2C_ReadAck();

	I2C_Start();
	I2C_Write(sensor_address << 1);
	I2C_Write(0x1F); // Low byte register
	I2C_Start();
	I2C_Write((sensor_address << 1) | 0x01);
	distance_low = I2C_ReadNack();
	I2C_Stop();

	return (distance_high << 8) | distance_low;
}




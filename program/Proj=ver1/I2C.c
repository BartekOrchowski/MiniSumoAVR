#include "I2C.h"

// Konfiguracja peryferium I2C
void I2C_Init(void)
{
	// Ustawiamy zegar do odczytu na 400kHz 
	TWSR = 0x00; // Preskaler zegara = 0 
	TWBR = 0x0C; // (0x0C = 12)
	// 16_000_000/(16+2*12*4^0) = 400_000

	TWCR = (1 << TWEN); // W³¹czenie I2C 
}

// Wysy³anie bitu startu
void I2C_Start(void)
{
	TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT); 

	// Czekanie az preryferium zakonczy prace
	while (!(TWCR & (1 << TWINT))); 
}

// Wys³anie bitu stopu
void I2C_Stop(void)
{
	TWCR = (1 << TWSTO) | (1 << TWEN) | (1 << TWINT);
}

// Wpisanie danych na rejsetr
void I2C_Write(uint8_t data)
{
	TWDR = data;
	TWCR = (1 << TWEN) | (1 << TWINT);
	
	while (!(TWCR & (1 << TWINT)));
}

// Zwrot bitu ACK na magistrale po odczycie
uint8_t I2C_ReadAck(void)
{
	// Read data with ACK
	TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA);
	while (!(TWCR & (1 << TWINT)));
	
	return TWDR;
}

// Odczyt bez bitu ACK
uint8_t I2C_ReadNack(void)
{
	// Read data with NACK
	TWCR = (1 << TWEN) | (1 << TWINT);
	
	while (!(TWCR & (1 << TWINT)));
	
	return TWDR;
}
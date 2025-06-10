#include "LineSensor.h"

// Pr�g dla wykrywania linii (dostosuj w zale�no�ci od czujnika i warunk�w o�wietleniowych)
#define LINE_THRESHOLD 512 // Pr�g ADC (0-1023 dla 10-bitowego ADC)

void LineSensor_Init(void)
{
	// Konfiguracja pin�w PC0 (ADC0) i PC1 (ADC1) jako wej�cia
	DDRC &= ~((1 << PC0) | (1 << PC1)); // Piny PC0 i PC1 jako wej�cia
	PORTC &= ~((1 << PC0) | (1 << PC1)); // Wy��cz pull-up (czujniki analogowe tego nie wymagaj�)

	// Konfiguracja ADC
	ADMUX = (1 << REFS0); // Referencja AVCC (5V), wyb�r ADC0 jako domy�lny kana�
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // W��cz ADC, preskaler 128
}

uint8_t LineSensor_Read(void)
{
	uint16_t adc_value0, adc_value1;

	// Odczyt z ADC0 (PC0)
	ADMUX = (ADMUX & 0xF0) | (0x00); // Wybierz kana� ADC0
	ADCSRA |= (1 << ADSC); // Rozpocznij konwersj�
	while (ADCSRA & (1 << ADSC)); // Czekaj na zako�czenie konwersji
	adc_value0 = ADC; // Zapisz wynik

	// Odczyt z ADC1 (PC1)
	ADMUX = (ADMUX & 0xF0) | (0x01); // Wybierz kana� ADC1
	ADCSRA |= (1 << ADSC); // Rozpocznij konwersj�
	while (ADCSRA & (1 << ADSC)); // Czekaj na zako�czenie konwersji
	adc_value1 = ADC; // Zapisz wynik

	// Logika wykrywania linii
	// Zak�adamy, �e linia to niska warto�� ADC (np. ciemna powierzchnia), a brak linii to wysoka warto��
	if (adc_value0 < LINE_THRESHOLD || adc_value1 < LINE_THRESHOLD)
	{
		return LINE; // Linia wykryta pod przynajmniej jednym czujnikiem
	}
	else
	{
		return NOLINE; // Brak linii
	}
}}
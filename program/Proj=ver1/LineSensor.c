#include "LineSensor.h"

// Próg dla wykrywania linii (dostosuj w zale¿noœci od czujnika i warunków oœwietleniowych)
#define LINE_THRESHOLD 512 // Próg ADC (0-1023 dla 10-bitowego ADC)

void LineSensor_Init(void)
{
	// Konfiguracja pinów PC0 (ADC0) i PC1 (ADC1) jako wejœcia
	DDRC &= ~((1 << PC0) | (1 << PC1)); // Piny PC0 i PC1 jako wejœcia
	PORTC &= ~((1 << PC0) | (1 << PC1)); // Wy³¹cz pull-up (czujniki analogowe tego nie wymagaj¹)

	// Konfiguracja ADC
	ADMUX = (1 << REFS0); // Referencja AVCC (5V), wybór ADC0 jako domyœlny kana³
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // W³¹cz ADC, preskaler 128
}

uint8_t LineSensor_Read(void)
{
	uint16_t adc_value0, adc_value1;

	// Odczyt z ADC0 (PC0)
	ADMUX = (ADMUX & 0xF0) | (0x00); // Wybierz kana³ ADC0
	ADCSRA |= (1 << ADSC); // Rozpocznij konwersjê
	while (ADCSRA & (1 << ADSC)); // Czekaj na zakoñczenie konwersji
	adc_value0 = ADC; // Zapisz wynik

	// Odczyt z ADC1 (PC1)
	ADMUX = (ADMUX & 0xF0) | (0x01); // Wybierz kana³ ADC1
	ADCSRA |= (1 << ADSC); // Rozpocznij konwersjê
	while (ADCSRA & (1 << ADSC)); // Czekaj na zakoñczenie konwersji
	adc_value1 = ADC; // Zapisz wynik

	// Logika wykrywania linii
	// Zak³adamy, ¿e linia to niska wartoœæ ADC (np. ciemna powierzchnia), a brak linii to wysoka wartoœæ
	if (adc_value0 < LINE_THRESHOLD || adc_value1 < LINE_THRESHOLD)
	{
		return LINE; // Linia wykryta pod przynajmniej jednym czujnikiem
	}
	else
	{
		return NOLINE; // Brak linii
	}
}}
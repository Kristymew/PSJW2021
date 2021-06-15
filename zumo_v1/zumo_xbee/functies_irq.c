#include <avr/io.h>

#include "functies_irq.h"

void initialiseerGeleLed() {
	DDRC |= geleLED;
}

void zetGeleLedAan() {
	PORTC |= geleLED;    // Zet led aan
}

void zetGeleLedUit() {
	PORTC &= ~geleLED;	// Zet led uit
}
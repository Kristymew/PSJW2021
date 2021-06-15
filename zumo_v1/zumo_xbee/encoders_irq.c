#include <avr/io.h>

#include "encoders_irq.h"

void initEncoders() {
	// Enable interrupt on PE6 for the right encoder
	DDRE &= ~(1<<PORTE6);						// Set PE6 as input, right encoder XORed signal
	DDRF &= ~(1<<PORTF0);						// Set PF0 as input
	PORTE |= (1<<PORTE6);						// OR PORTE PE6 to 1
	EICRB = (1<<ISC60) | (1<<ISC61);			// Trigger off the rising edge of INT6
	EIMSK = 1<<INT6;							// Enable INT6 interrupt

	// Enable pin-change interrupt on PB4 for left encoder, and disable other pin-change interrupts
	DDRB &= ~(1<<PINB4);						// Set PB4 as input, left encoder XORed signal
	DDRE &= ~(1<<PORTE2);						// Set PE2 as input
	PCICR |= 1<<PCIE0;							// Set PCIE0 to enable PCMSK0 scan
	PCMSK0 |= 1<<PCINT4;						// Set PCINT4 to trigger an interrupt on state change
	PCIFR = 1<<PCIF0;							// Clear its interrupt flag by writing a 1
}
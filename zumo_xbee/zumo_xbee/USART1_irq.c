#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "USART1_irq.h"

void initUsart1() {
	UCSR1A = 0;
	UCSR1B = (1 << RXEN1) | (1 << TXEN1) | (1 << RXCIE1) | (1 << RXCIE1);	// Enables the receiver and transmitter, TX=PD1 RX=PD0, also enable RX and TX interrupts
	UCSR1C = (1 << UCSZ11) | (1 << UCSZ10);		// Set data frame format: asynchronous mode, no parity, 1 stop bit, 8 bit size

	/* Set the baudrate to 9600 */
	UBRR1H = 00;              					// Load lower 8-bits UBRR register
	UBRR1L = 103;             					// Load upper 8-bits of to high byte  UBRR register
	sei();										// The sei() function converts the I bit in the SREG of the microcontroller set leaving the microcontroller on	interrupts can respond
}

/* USART RX and TX */
void writeChar(char data) {
	while(!(UCSR1A & (1 << UDRE1)));			// Wait for empty transmit buffer
	UDR1 = data;								// Put data into buffer, sends the data
}

void writeString(char st[]) {					// In c is een string hetzelfde als een array van characters
	uint8_t i;
	for(i = 0; st[i] != 0 ; i++) {				// Aan het einde van een string wordt \0 toegevoegd, de for loop loopt zolang de string niet gelijk is aan 0
		writeChar(st[i]);						// Verstuur de string via USARTn
	}
}

void writeInt(int16_t i) {
	char buffer[8];								// Array in memory waar de string opgeslagen moet worden
	itoa(i, buffer, 10);						// Zet de ingelezen integer i om in een string (weergave: 10 = decimaal, 16 = hex, 2 = binary)
	writeString(buffer);						// Verstuur de waarde van i, die opgeslagen is op de locatie van de buffer
}

unsigned char readChar() {
	while(!(UCSR1A & (1 << RXC1)));				// Wait for data to be received
	return UDR1;								// Get and return received data from buffer
}
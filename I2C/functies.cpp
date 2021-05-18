/*
 * functies.c
 *
 * Created: 1/12/2019 1:17:58 PM
 *  Author: John
 */ 

#define BUTTON_BRD    (1 << PB7)
#define DEBOUNCE_TIME 1000

#define BAUDRATE 9600
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>


 
void initUsart()
{
	UCSR1A = 0;
	UCSR1B = (1 << TXEN1);
	UCSR1C = (1 << UCSZ11) | (1 << UCSZ10);
	UBRR1H=00;
	UBRR1L=103;

}

char readChar() {
	char x;
	while( !(UCSR1A & (1 << RXC1)) );
	x=UDR1;
	return x;
}

void writeChar(char c)
{
	while(~UCSR1A & (1 << UDRE1));
	UDR1 = c;
}

void writeString(char* s)
{
	uint8_t i;
	for(i = 0 ; s[i] != 0 ; i++) {
		writeChar( s[i] );
	}
}

void writeInt(int16_t nr)
{
	char buffer[8];
	itoa(nr,buffer,10);
	writeString(buffer);
}
void writeUnt(uint16_t nr)
{
	writeInt(nr);
}

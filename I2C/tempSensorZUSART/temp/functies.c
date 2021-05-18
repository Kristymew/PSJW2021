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
	UCSR0A = 0;
	UCSR0B = (1 << TXEN0);
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
	UBRR0H=00;
	UBRR0L=103;

}

char readChar() {
	char x;
	while( !(UCSR0A & (1 << RXC0)) );
	x=UDR0;
	return x;
}

void writeChar(char c)
{
	while(~UCSR0A & (1 << UDRE0));
	UDR0 = c;
}

void writeString(char* s)
{
	for(uint8_t i = 0 ; s[i] != 0 ; i++) {
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

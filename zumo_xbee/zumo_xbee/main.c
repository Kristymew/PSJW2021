/* TO-DO:
	1* Probleem is dat de waarde van inputKeyboard, de receivedChar, onthouden wordt, en als je die probeert te veranderen door
	 * receivedByte = ' ' of 0, dan blijft die de waarde onthouden?
	3* De functies turnLeftWide en turnRightWide werken niet.
	4* Moet d.m.v. Timer counter Puls Width Modulation een algoritme schrijven die berekend wat de afstand is
*/

// https//www.youtube.com/watch?v=_almRz0_m9g to see splitting functions into .h and .c files

#define F_CPU 16000000          				// 16MHz

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "motors_irq.h"
#include "USART1_irq.h"

volatile uint8_t counter = 0;					// DUMMY VAR to stimulate "sensor data"
volatile char receivedData = ' ';     			// Create char to store input from keyboard

/*ISR(USART1_TX_vect) {							// When you send data, calls the ISR
	counter++;

	_delay_ms(1000);
}*/

ISR(USART1_RX_vect) {							// When you receive data, calls the ISR
	receivedData = readChar();					// Read the incoming byte (data from the keyboard)
	direction(receivedData);					// Send the receivedData as parameter to the function direction
}

int main(void) {
	initUsart1();								// Initialization for the registers
	initPWM();
	
	while(1) {
		//writeChar('\f');						// Clear screen
		writeString("Sensordata Temp: ");
		writeInt(counter);						// Print the counter data every 1ms, should be done with timer
		writeString("\n");
		
		writeString("Direction: ");
		writeChar(receivedData);				// Show received input from pc
		writeString("\n");
		
		_delay_ms(1000);
	}
}
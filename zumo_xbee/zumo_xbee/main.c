// https//www.youtube.com/watch?v=_almRz0_m9g to see splitting functions into .h and .c files

#define F_CPU 16000000          				// 16MHz

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "motors_irq.h"
#include "USART1_irq.h"

void initEncoders();
void computeDistance();

static volatile char receivedData = ' ';     	// Create char to store input from keyboard

// Encoder variables
static volatile uint16_t ticksLeft;
static volatile uint16_t ticksRight;
static volatile uint16_t ticksTotal;
static volatile uint16_t distance;

ISR(USART1_RX_vect) {							// When you receive data, calls the ISR
	receivedData = UDR1;						// Read the incoming byte (data from the keyboard)
	direction(receivedData);					// Send the receivedData as parameter to the function direction
}

// Right
ISR(INT6_vect) {								// Enable interrupt on PE6 for the right encoder
	uint8_t rightEncoderTicks;
	rightEncoderTicks = PORTE & (1<<PORTE6);

	if(rightEncoderTicks) {
		ticksRight++;
	}
}

// Left
ISR(PCINT0_vect) {								// Enable interrupt on PB4 for the left encoder
	uint8_t leftEncoderTicks;
	leftEncoderTicks = PINB & (1<<PINB4);

	if(leftEncoderTicks) {
		ticksLeft++;
	}
}

int main(void) {
	initUsart1();								// Initialization for the registers
	initPWM();
	initEncoders();
	sei();										// The sei() function converts the I bit in the SREG of the microcontroller set leaving the microcontroller on	interrupts can respond

	//DDRC |= (1<PORTC7);

	while(1) {
		ticksTotal = ticksLeft+ticksRight;		// (ticksLeft/2)+(ticksRight/2);
		distance = (ticksTotal/1204)*12;		// (ticks/cpr)*(pi*diameter), pi*3.9cm = 12.2522113490 ~12
		
		//if(ticksLeft >= 2000) {					// yellow led test 
			//PORTC = 1<<PORTC7;
		//}
		
		writeString("Direction: ");
		writeChar(receivedData);				// Show received input from pc
		writeString("\r\n");

		writeString("ticksLeft: ");
		writeInt(ticksLeft);
		writeString("\n\r");

		writeString("ticksRight: ");
		writeInt(ticksRight);
		writeString("\n\r");

		writeString("Distance: ");
		writeInt(distance);						// Show the distance
		writeString("\r\n");
		writeString("\r\n");

		_delay_ms(1000);						// Show data every second
	}
}

void initEncoders() {
	// Enable interrupt on PE6 for the right encoder
	DDRE &= ~(1<<PORTE6);						// Set PE6 as input, right encoder XORed signal
	DDRF &= ~(1<<PORTF0);						// Set PF0 as input
	EICRB = (1<<ISC60) | ~(1<<ISC61);			// Trigger off the rising edge of INT6
	EIMSK = 1<<INT6;							// Enable INT6 interrupt
	//EIFR = 1<<INT6;								//Enables Flag

	// Enable pin-change interrupt on PB4 for left encoder, and disable other pin-change interrupts
	DDRB &= ~(1<<PINB4);						// Set PB4 as input, left encoder XORed signal
	DDRE &= ~(1<<PORTE2);						// Set PE2 as input
	PCICR |= 1<<PCIE0;							// Set PCIE0 to enable PCMSK0 scan
	PCMSK0 |= 1<<PCINT4;						// Set PCINT4 to trigger an interrupt on state change
	PCIFR = 1<<PCIF0;							// Clear its interrupt flag by writing a 1
}

/*
	* Distance traveled = Wheel rotations * circumference = 
	* (encoder ticks / counts per revolution) * circumference
	* diameter wheel = 39mm
*/
	
/* 
	* encoders provide a resolution of 12 counts per revolution of the motor shaft when counting both channels.
	* to compute the counts per revolution of the drive sprockets, multiply the gearboxes' gear ratio by 12.
	* 100:37:1 = 100.37 x 12 = 1204.44 CPR (counts per revolution)
*/ 
	
// encoder ticks = read from left and right encoder
// CPR = 1204.44 ~1204
// circumference = pi*3.9cm = 12.2522113490 ~12
// Distance = (encoder ticks / 1204.44) * 12

/*
	* Quadrature encoder transitions are often detected by monitoring both encoder channels directly. However, since
	* transitions on the Zumo’s encoders can occur at high frequencies (several thousand per second) when its motors
	* are running, it is necessary to use the AVR’s pin change interrupts or external interrupts to read the encoders.
*/
	
/*
	* PE6		Reads the right encoder XORed signal		external interrupt INT6				Digital pin 7
	* PB4		Reads the left encoder XOred signal			pin change interrupt PCINT4			Digital pin 8
	* PF0		Reads the right encoder channel B												Digital pin 23 (analog pin 5)
	* PE2		Reads the left encoder channel B
*/
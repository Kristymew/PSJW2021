#define F_CPU 16000000          				// 16MHz

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "motors_irq.h"
#include "USART1_irq.h"
#include "encoders_irq.h"
#include "i2c_irq.h"
#include "functies_irq.h"

void computeDistance();
void blinkYellowLed();
void printFunction();

static volatile char receivedData = ' ';     	// Create char to store input from keyboard

// Encoder variables
static volatile uint16_t ticksLeft;
static volatile uint16_t ticksRight;
static volatile float ticksTotal;
static volatile float distance;

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
	initI2C();
	magnetoMeter();
	
	sei();										// The sei() function converts the I bit in the SREG of the microcontroller set leaving the microcontroller oninterrupts can respond

	while(1) {
		computeDistance();
		blinkYellowLed();
		printFunction();
	}
}

void computeDistance() {
	ticksTotal = ticksLeft+ticksRight;		// Add the ticks of the left and right encoder
	distance = (ticksTotal/1204.44)*12.2522113490;	// (ticks/cpr)*(pi*diameter), pi*3.9cm = 12.2522113490, 100.37 x 12 = 1204.44 CPR (counts per revolution)
}

void blinkYellowLed() {						// User Story 1
	// Show data every second, and blink every second
	zetGeleLedAan();
	_delay_ms(1000);
	zetGeleLedUit();
}

void printFunction() {
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

	/*---------- I2C ----------*/
	writeString("Richting is: ");
	
	setRegister(OUT_X_L_M);
	uint8_t XL = readXL();
	setRegister(OUT_X_H_M);
	uint8_t XH = readXH();
	uint16_t X = (XH << 8 | XL);
	X = X - xOff;				// lees X waarde af met X - average waarde
	
	writeString("X: ");
	writeUnt(X);
	writeString(" ");
	
	setRegister(OUT_Y_L_M);
	uint8_t YL = readYL();
	setRegister(OUT_Y_H_M);
	uint8_t YH = readYH();
	uint16_t Y = (YH << 8 | YL);
	Y = Y - yOff;				// lees y waarde af met y - average waarde
	
	writeString("Y: ");
	writeUnt(Y);
	writeString(" ");
	
	setRegister(OUT_Z_L_M);
	uint8_t ZL = readZL();
	setRegister(OUT_Z_H_M);
	uint8_t ZH = readZH();
	uint16_t Z = (ZH << 8 | ZL);
	Z = Z - zOff;				// lees z waarde af met z - average waarde

	writeString("Z: ");
	writeUnt(Z);
	writeString("\n\r");
	writeString("\n\r");
}
#define F_CPU 16000000          				// 16MHz

#define SPEED1 100
#define SPEED2 50
#define SPEED3 0

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "motors_irq.h"

void initPWM() {
	TCCR1A = 0b10100000;            			// 160
	TCCR1B = 0b00010001;            			// 17
	ICR1 = 400;									// Input Capture Register
	OCR1A = 0;                      			// Snelheid van de rechtermotor
	OCR1B = 0;                      			// Snelheid van de linkermotor

	/* 
	 * Max speed OCR1A and OCR1B = 
	 * (LOW drives the motor forward, HIGH drives it in reverse)
	 * PORTB1 = Right Motor Direction
	 * PORTB2 = Left Motor Direction
	 * PORTB5 = Right Motor PWM; Timer1 PWM output A (OC1A)
	 * PORTB6 = Left Motor PWM; Timer1 PWM output B (OC1B)
	 * Set all ports as output
	*/
	DDRB |= (1<<PORTB1) | (1<<PORTB2) | (1<<PORTB5) | (1<<PORTB6);
}

/* Controlling the motors with PWM */
void forward(int speed) {
	PORTB = (0 << PORTB1) | (0 << PORTB2) | (1 << PORTB5) | (1 << PORTB6);		// Set left and right motors forward
	OCR1A = speed;   							// Set the speed of the left motor with PWM
	OCR1B = speed;   							// Set the speed of the right motor with PWM
}

void turnRight(int speed) {
	PORTB = (0 << PORTB2) | (1 << PORTB6);		// PORTB2 LOW = move forward, PORTB5 controls left motor PWM
	OCR1B = speed;
}

void turnLeft(int speed) {
	PORTB = (0 << PORTB1) | (1 << PORTB5);		// PORTB1 LOW = move forward, PORTB5 controls right motor PWM
	OCR1A = speed;
}

void backward(int speed) {
	PORTB = (1 << PORTB1) | (1 << PORTB2) | (1 << PORTB5) | (1 << PORTB6);		// PORTB1 + PORTB2 HIGH = move backward, PORTB5 = left + PORTB6 = right control motor PWM
	OCR1A = speed;   							// Set the speed of the left motor with PWM
	OCR1B = speed;   							// Set the speed of the right motor with PWM
}

void turnRightWide(int speed, int speed2) {		// Left motor PWM higher than right motor
	PORTB = (0 << PORTB1) | (0 << PORTB2) | (1 << PORTB5) | (1 << PORTB6);		// Set left and right motors forward
	OCR1A = speed;   							// Set the speed of the left motor with PWM
	OCR1B = speed2;   							// Set the speed of the right motor with PWM
}

void turnLeftWide(int speed, int speed2) {		// Right motor PWM higher than left motor
	PORTB = (0 << PORTB1) | (0 << PORTB2) | (1 << PORTB5) | (1 << PORTB6);		// Set left and right motors forward
	OCR1A = speed;   							// Set the speed of the left motor with PWM
	OCR1B = speed2;   							// Set the speed of the right motor with PWM
}

/* Function that calls the function of the PWM motor to give instructions depending on the input from the user */
void direction(char inputKeyboard) {
	switch(inputKeyboard) {
		case 'w':
			forward(SPEED1);
			break;
		case 's':
			backward(SPEED1);
			break;
		case 'a':
			turnLeft(SPEED1);
			turnRight(SPEED3);
			break;
		case 'd':
			turnRight(SPEED1);
			turnLeft(SPEED3);
			break;
		case 'q':
			turnLeftWide(SPEED1, SPEED2);
			break;
		case 'e':
			turnLeftWide(SPEED2, SPEED1);
			break;
		default:								// By no input, no actions
			forward(SPEED3);
			backward(SPEED3);
			turnLeft(SPEED3);
			turnRight(SPEED3);
			break;
	}
}
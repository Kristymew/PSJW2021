#include <avr/io.h>

#include "motors_irq.h"

static volatile int SPEED0 = 0;
static volatile int SPEED1 = 100;
static volatile int SPEED2 = 200;
static volatile int SPEED3 = 300;
static volatile int SPEED4 = 400;
static volatile int SET_SPEED;

void initPWM() {
	TCCR1A =	0b10100000;            			// 160
	TCCR1B =	0b00010001;            			// 170
	ICR1 =		400;							// Input Capture Register
	OCR1A =		0;                      		// Snelheid van de rechtermotor
	OCR1B =		0;                      		// Snelheid van de linkermotor

	DDRB |= (1<<PORTB1) | (1<<PORTB2) | (1<<PORTB5) | (1<<PORTB6);

	SET_SPEED = SPEED2;							// Default half SPEED of the max PWM (400) = (200)

	/* 
	 * Max speed OCR1A and OCR1B = 
	 * (LOW drives the motor forward, HIGH drives it in reverse)
	 * PORTB1 = Right Motor Direction
	 * PORTB2 = Left Motor Direction
	 * PORTB5 = Right Motor PWM; Timer1 PWM output A (OC1A)
	 * PORTB6 = Left Motor PWM; Timer1 PWM output B (OC1B)
	 * Set all ports as output
	*/
}

/* Controlling the motors with PWM */
void forward(int speed) {
	PORTB = (0<<PORTB1) | (0<<PORTB2) | (1<<PORTB5) | (1<<PORTB6);		// Set left and right motors forward
	OCR1A = speed;   							// Set the speed of the left motor with PWM
	OCR1B = speed;   							// Set the speed of the right motor with PWM
}

void turnRight(int speed) {
	PORTB = (0<<PORTB2) | (1<<PORTB6);			// PORTB2 LOW = move forward, PORTB5 controls left motor PWM
	OCR1B = speed;								// Set the speed of the right motor with PWM
}

void turnLeft(int speed) {
	PORTB = (0<<PORTB1) | (1<<PORTB5);			// PORTB1 LOW = move forward, PORTB5 controls right motor PWM
	OCR1A = speed;								// Set the speed of the left motor with PWM
}

void backward(int speed) {
	PORTB = (1<<PORTB1) | (1<<PORTB2) | (1<<PORTB5) | (1<<PORTB6);		// PORTB1 + PORTB2 HIGH = move backward, PORTB5 = left + PORTB6 = right control motor PWM
	OCR1A = speed;   							// Set the speed of the left motor with PWM
	OCR1B = speed;   							// Set the speed of the right motor with PWM
}

void turnRightWideForward(int speed, int speed2) {		// Left motor PWM higher than right motor
	PORTB = (0<<PORTB1) | (0<<PORTB2) | (1<<PORTB5) | (1<<PORTB6);		// Set left and right motors forward
	OCR1A = speed;   							// Set the speed of the left motor with PWM
	OCR1B = speed2;   							// Set the speed of the right motor with PWM
}

void turnLeftWideForward(int speed, int speed2) {		// Right motor PWM higher than left motor
	PORTB = (0<<PORTB1) | (0<<PORTB2) | (1<<PORTB5) | (1<<PORTB6);		// Set left and right motors forward
	OCR1A = speed;   							// Set the speed of the left motor with PWM
	OCR1B = speed2;   							// Set the speed of the right motor with PWM
}

void turnRightWideBackward(int speed, int speed2) {		// Left motor PWM higher than right motor
	PORTB = (1<<PORTB1) | (1<<PORTB2) | (1<<PORTB5) | (1<<PORTB6);		// Set left and right motors backward
	OCR1A = speed;   							// Set the speed of the left motor with PWM
	OCR1B = speed2;   							// Set the speed of the right motor with PWM
}

void turnLeftWideBackward(int speed, int speed2) {		// Right motor PWM higher than left motor
	PORTB = (1<<PORTB1) | (1<<PORTB2) | (1<<PORTB5) | (1<<PORTB6);		// Set left and right motors backward
	OCR1A = speed;   							// Set the speed of the left motor with PWM
	OCR1B = speed2;   							// Set the speed of the right motor with PWM
}

/* Function that calls the function of the PWM motor to give instructions depending on the input from the user */
void direction(char inputKeyboard) {
	switch(inputKeyboard) {
		case '1':
			SET_SPEED = SPEED1;					// PWM 100
			break;
		case '2':
			SET_SPEED = SPEED2;					// PWM 200
			break;
		case '3':
			SET_SPEED = SPEED3;					// PWM 300
			break;
		case '4':
			SET_SPEED = SPEED4;					// PWM 400
			break;
	}

	switch(inputKeyboard) {
		case 'w':
			forward(SET_SPEED);
			break;
		case 's':
			backward(SET_SPEED);
			break;
		case 'a':
			turnLeft(SET_SPEED);
			turnRight(SPEED0);
			break;
		case 'd':
			turnLeft(SPEED0);
			turnRight(SET_SPEED);
			break;
		case 'q':
			turnLeftWideForward(SET_SPEED, SET_SPEED/2);
			break;
		case 'e':
			turnLeftWideForward(SET_SPEED/2, SET_SPEED);
			break;
		case 'z':
			turnLeftWideBackward(SET_SPEED, SET_SPEED/2);
			break;
		case 'c':
			turnLeftWideBackward(SET_SPEED/2, SET_SPEED);
			break;
		default:								// By no input, no actions
			forward(SPEED0);
			backward(SPEED0);
			turnLeft(SPEED0);
			turnRight(SPEED0);
			break;
	}
}
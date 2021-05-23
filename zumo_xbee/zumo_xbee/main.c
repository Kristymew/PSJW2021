#define F_CPU 16000000          				// 16MHz

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <util/delay.h>

/* To write and read data to tx/rx */
void writeChar(char data);
void writeString(char st[]);
void writeInt(int16_t i);
unsigned char readChar();

/* Initalizations */
void initUsart1();
void initPWM();

/* Controls for the car */
void forward(int speed);
void turnRight(int speed);
void turnLeft(int speed);
void backward(int speed);
void direction(char inputKeyboard);				// Function to drive in a certain direction

int main(void) {
	initUsart1();								// Initialization for the registers
	initPWM();
	
	char receivedData = ' ';     				// Create char to store input from keyboard
	
	while(1) {
		//writeChar('\f');						// Clear screen
		writeString("input: \n");
		receivedData = readChar();				// Read the incoming byte (data from the keyboard)
		//writeChar(receivedData);				// Show received input from pc
		writeString("\n");
		
		direction(receivedData);				// Send the receivedData as parameter to the function direction
		
		
		
		// MUST BE INTERRUPT OR SOMETHING!!! EZ CHEESY FIX
		_delay_ms(200);							// Wait 200 ms
		receivedData = ' ';
		direction(receivedData);
	}
}

void initUsart1() {
	UCSR1A = 0;
	UCSR1B = (1 << RXEN1) | (1 << TXEN1);		// Enables the receiver and transmitter, TX=PD1 RX=PD0
	UCSR1C = (1 << UCSZ11) | (1 << UCSZ10);		// Use 8-bit character sizes, 1 stopbit, no parity

	/* Set the baudrate to 9600 */
	UBRR1H = 00;              					// Load lower 8-bits UBRR register
	UBRR1L = 103;             					// Load upper 8-bits of to high byte  UBRR register
}

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
	DDRB |= (1 << PORTB1) | (1 << PORTB2) | (1 << PORTB5) | (1 << PORTB6);
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

void turnRight(int speed) {
	PORTB = (0 << PORTB2) | (1 << PORTB6);		// PORTB2 LOW = move forward, PORTB5 controls left motor PWM
	OCR1B = speed;
}

void turnLeft(int speed) {
	PORTB = (0 << PORTB1) | (1 << PORTB5);		// PORTB1 LOW = move forward, PORTB5 controls right motor PWM
	OCR1A = speed;
}

/* Function that calls the function of the PWM motor to give instructions depending on the input from the user */
void direction(char inputKeyboard) {
	switch(inputKeyboard) {
		case 'w':
			forward(150);
			break;
		case 's':
			backward(150);
			break;
		case 'a':
			turnLeft(150);
			break;
		case 'd':
			turnRight(150);
			break;
		case 'q':
		
		case 'e':
		
		default:								// By no input, no actions
			forward(0);
			backward(0);
			turnLeft(0);
			turnRight(0);
	}
}

// Interrupt that checks for input every *ms, better than delay
#ifndef MOTORS_IRQ_H_
#define MOTORS_IRQ_H_

/* Initalizations */
void initPWM();

/* Controls for the car */
void forward(int speed);
void turnRight(int speed);
void turnLeft(int speed);
void backward(int speed);
void turnRightWide(int speed, int speed2);
void turnLeftWide(int speed, int speed2);
void direction(char inputKeyboard);				// Function to drive in a certain direction

#endif
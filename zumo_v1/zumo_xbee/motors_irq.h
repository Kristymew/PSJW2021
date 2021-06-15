#ifndef MOTORS_IRQ_H_
#define MOTORS_IRQ_H_

/* Initalizations */
void initPWM();

/* Controls for the car */
void forward(int speed);
void turnRight(int speed);
void turnLeft(int speed);
void backward(int speed);
void turnRightWideForward(int speed, int speed2);
void turnLeftWideForward(int speed, int speed2);
void turnRightWideBackward(int speed, int speed2);
void turnLeftWideBackward(int speed, int speed2);
void direction(char inputKeyboard);				// Function to drive in a certain direction

#endif
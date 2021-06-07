/*
 * IncFile1.h
 *
 * Created: 1/12/2019 2:06:50 PM
 *  Author: John
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void initUsart();
char readChar();
void writeChar(char c);
void writeInt(int16_t nr);
void writeUnt(uint16_t nr);
void writeString(char* s);
#endif /* INCFILE1_H_ */
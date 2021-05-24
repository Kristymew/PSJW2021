#ifndef USART1_IRQ_H_
#define USART1_IRQ_H_

/* Initalizations */
void initUsart1();

/* To write and read data to tx/rx */
void writeChar(char data);
void writeString(char st[]);
void writeInt(int16_t i);
unsigned char readChar();

#endif
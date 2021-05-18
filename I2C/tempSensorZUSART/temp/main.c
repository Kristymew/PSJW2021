/*
 * temp.c
 *
 * Created: 19/04/2021 19:09:07
 * Author : john
 */ 
#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>
#include "i2c.h"
#include "functies.h"

#define MCP9808Adres    0x18 

#define CONFIG_REG        1
#define TEMPERATUUR_REG   5
#define Fabriekant_ID_REG 6
#define DEVICE_ID_REG     7
#define RESOLUTIE_REG     8

void setConfigReg();
uint16_t readTemp();
void setResolutionReg();
void setRegister(uint8_t r);
uint16_t readReg();

int main(void)
{
	initUsart();
    initI2C();
    writeString("begin\n\r");
   
    while (1) 
    {
      writeString("Temperatuur is : ");
	  setRegister(TEMPERATUUR_REG);
	  uint16_t temp=readTemp();
	  writeUnt(temp);
	  writeString("\n\r");
	  _delay_ms(500);
    }
}


void setConfigReg() {
	i2cStart();
	i2cSend(MCP9808Adres<<1);   //i2c adres master schrijf
	i2cSend(CONFIG_REG);
	i2cSend(0);
	i2cSend(0);
	i2cStop();
}

void setResolutionReg(){
	i2cStart();
	i2cSend(MCP9808Adres<<1);   //i2c adres master schrijf
	i2cSend(RESOLUTIE_REG);
	i2cSend(3);
	i2cStop();
}

void setRegister(uint8_t r) {
	i2cStart();
	i2cSend(MCP9808Adres<<1);   //i2c adres master schrijf
	i2cSend(r);
	i2cStop();
}


uint16_t readReg() {
	i2cStart();
	i2cSend((MCP9808Adres<<1)+1);   //i2c adres master read
	uint8_t x =i2cReadAck();
	uint8_t y =i2cReadNoAck();
	i2cStop();
	return x*256+y;
}

uint16_t readTemp() {
	i2cStart();
	i2cSend((MCP9808Adres<<1)+1);   //i2c adres master read
	uint8_t x =i2cReadAck();
	uint8_t y =i2cReadNoAck();
	i2cStop();
	if ((x & 0x80) == 0x80){ //TA ³ TCRIT
	}
	if ((x & 0x40) == 0x40){ //TA > TUPPER
	}
	if ((x & 0x20) == 0x20){ //TA < TLOWER
	}
		x = x & 0x1F; //Clear flag bits
	if ((x & 0x10) == 0x10){ //TA < 0°C
		x = x & 0x0F; //Clear SIGN
		return 256 - (x * 16 + y / 16);
	}
	else { //TA ³ 0°C
		return (x * 16 + y / 16);
	}
}




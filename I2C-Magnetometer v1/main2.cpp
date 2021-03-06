#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include "mrBeen.h"

#include "i2c.h"
#include "functies.h"

#define LSM303DAdresWrite	0b0011010
#define LSM303DAdresRead	0b0011011

#define WHO_AM_I     	0x0F
#define CTRL5           0x24
#define OUT_X_L_M       0x08
#define OUT_X_H_M       0x09
#define OUT_Y_L_M       0x0A
#define OUT_Y_H_M       0x0B
#define OUT_Z_L_M       0x0C
#define OUT_Z_H_M       0x0D


void setRegister(uint8_t r);

uint8_t readXL();
uint8_t readXH();
uint8_t readYL();
uint8_t readYH();
uint8_t readZL();
uint8_t readZH();

int main()
{

	initUsart();
    initI2C();
	
	// *---------- Enable magnetometer --------*//
	// 0x64 = 0b01100100
	i2cStart(); // Begin Transmission
	i2cSend(LSM303DAdresWrite); // Master in Transmit mode
	i2cSend(CTRL5); // Access register CTRL5
	i2cSend(0x64); // Master stuurt deze waarde naar het CTRL1 register
	i2cStop(); // Stop transmission
	
    writeString("begin\n\r");  

   while(1)
   {
       
		writeString("Richting is: ");
		
		setRegister(OUT_X_L_M);
		uint8_t XL = readXL();
		setRegister(OUT_X_H_M);
		uint8_t XH = readXH();
		uint16_t X = (XH << 8 | XL);
		
		writeString("X: ");
		writeUnt(X);
		writeString(" ");
		
		setRegister(OUT_Y_L_M);
		uint8_t YL = readYL();
		setRegister(OUT_Y_H_M);
		uint8_t YH = readYH();
		uint16_t Y = (YH << 8 | YL);
		
		writeString("Y: ");
		writeUnt(Y);
		writeString(" ");
		
		setRegister(OUT_Z_L_M);
		uint8_t ZL = readZL();
		setRegister(OUT_Z_H_M);
		uint8_t ZH = readZH();
		uint16_t Z = (ZH << 8 | ZL);
		
		writeString("Z: ");
		writeUnt(Z);
		writeString("\n\r");
		_delay_ms(500);
		

  }

}


void setRegister(uint8_t r) {
	i2cStart();   
	i2cSend(LSM303DAdresWrite);//i2c adres master schrijf
	i2cSend(r);
	i2cStop();
}

uint8_t readXL() {
	i2cStart();
	i2cSend(LSM303DAdresRead);
	uint8_t xl = i2cReadNoAck();	
	i2cStop();
	return xl;
}
uint8_t readXH() {
	i2cStart();
	i2cSend(LSM303DAdresRead);
	uint8_t xh = i2cReadNoAck();	
	i2cStop();
	return xh;
}

uint8_t readYL() {
	i2cStart();
	i2cSend(LSM303DAdresRead);
	uint8_t yl = i2cReadNoAck();
	i2cStop();
	return yl;
}
uint8_t readYH() {
	i2cStart();
	i2cSend(LSM303DAdresRead);
	uint8_t yh = i2cReadNoAck();	
	i2cStop();
	return yh;
}
uint8_t readZL() {
	i2cStart();
	i2cSend(LSM303DAdresRead);
	uint8_t zl = i2cReadNoAck();
	i2cStop();
	return zl;
}
uint8_t readZH() {
	i2cStart();
	i2cSend(LSM303DAdresRead);
	uint8_t zh = i2cReadNoAck();	
	i2cStop();
	return zh;
}

void readAxes16bit(uint8_t addr, uint8_t firstReg){
	setRegister(addr); // Wire.beginTransmission
	i2cSend(firstReg); // MSB address, dat is L3GD20H_REG_OUT_X_L
	
	uint8_t xl = i2cReadAck(); // Wire.read();
	uint8_t xh = i2cReadAck();
	uint8_t yl = i2cReadAck();
	uint8_t yh = i2cReadAck();
	uint8_t zl = i2cReadAck();
	uint8_t zh = i2cReadAck();
	
	//combine high and low bytes
	int16_t vx = (xh << 8 | xl);
	int16_t vy = (yh << 8 | yl);
	int16_t vz = (zh << 8 | zl);

}

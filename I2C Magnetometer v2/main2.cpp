#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include "mrBeen.h"

#include "i2c.h"
#include "functies.h"

#define LSM303DAdresWrite	0b00111010
#define LSM303DAdresRead	0b00111011

#define WHO_AM_I     	0x0F
#define CTRL5           0x24
#define CTRL6			0x25
#define CTRL7			0x26
#define OUT_X_L_M       0x08
#define OUT_X_H_M       0x09
#define OUT_Y_L_M       0x0A
#define OUT_Y_H_M       0x0B
#define OUT_Z_L_M       0x0C
#define OUT_Z_H_M       0x0D


void setRegister(uint8_t r);
void calibratie();

uint8_t readXL();
uint8_t readXH();
uint8_t readYL();
uint8_t readYH();
uint8_t readZL();
uint8_t readZH();

int xOff;
int zOff;
int yOff;

int main()
{

	initUsart();
    initI2C();
	calibratie();
	
	// *---------- Enable magnetometer --------*//
	// 0x64 = 0b01100100
	i2cStart(); // Begin Transmission
	i2cSend(LSM303DAdresWrite); // Master in Transmit mode
	i2cSend(CTRL5); // Access register CTRL5
	i2cSend(0x64); // Master stuurt deze waarde naar het CTRL1 register
	i2cStop(); // Stop transmission
	
	// 0x20 
	i2cStart(); // Begin Transmission
	i2cSend(LSM303DAdresWrite); // Master in Transmit mode
	i2cSend(CTRL6); // Access register CTRL6
	i2cSend(0x20); // Master stuurt deze waarde naar het CTRL1 register
	i2cStop(); // Stop transmission
	
	// 0x00
	i2cStart(); // Begin Transmission
	i2cSend(LSM303DAdresWrite); // Master in Transmit mode
	i2cSend(CTRL7); // Access register CTRL7
	i2cSend(0x00); // Master stuurt deze waarde naar het CTRL1 register
	i2cStop(); // Stop transmission
	
    writeString("begin\n\r");  

   while(1)
   {
		writeString("Test");
       
		writeString("Richting is: ");
		
		setRegister(OUT_X_L_M);
		uint8_t XL = readXL();
		setRegister(OUT_X_H_M);
		uint8_t XH = readXH();
		uint16_t X = (XH << 8 | XL);
		X = X - xOff; // lees X waarde af met X - average waarde
		
		writeString("X: ");
		writeUnt(X);
		writeString(" ");
		
		setRegister(OUT_Y_L_M);
		uint8_t YL = readYL();
		setRegister(OUT_Y_H_M);
		uint8_t YH = readYH();
		uint16_t Y = (YH << 8 | YL);
		Y = Y - yOff; // lees y waarde af met y - average waarde
		
		writeString("Y: ");
		writeUnt(Y);
		writeString(" ");
		
		setRegister(OUT_Z_L_M);
		uint8_t ZL = readZL();
		setRegister(OUT_Z_H_M);
		uint8_t ZH = readZH();
		uint16_t Z = (ZH << 8 | ZL);
		Z = Z - zOff; // lees z waarde af met z - average waarde
		
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
	//i2cStop();
	return xl;
}
uint8_t readXH() {
	i2cStart();
	i2cSend(LSM303DAdresRead);
	uint8_t xh = i2cReadNoAck();	
	//i2cStop();
	return xh;
}

uint8_t readYL() {
	i2cStart();
	i2cSend(LSM303DAdresRead);
	uint8_t yl = i2cReadNoAck();
	//i2cStop();
	return yl;
}
uint8_t readYH() {
	i2cStart();
	i2cSend(LSM303DAdresRead);
	uint8_t yh = i2cReadNoAck();	
	//i2cStop();
	return yh;
}
uint8_t readZL() {
	i2cStart();
	i2cSend(LSM303DAdresRead);
	uint8_t zl = i2cReadNoAck();
	//i2cStop();
	return zl;
}
uint8_t readZH() {
	i2cStart();
	i2cSend(LSM303DAdresRead);
	uint8_t zh = i2cReadNoAck();	
	i2cStop();
	return zh;
}

void calibratie(){
	int xTotaal = 0;
	int yTotaal = 0;
	int zTotaal = 0;
	
	for(int i = 0; i < 1024; i++){
	 // readGyroVars
		setRegister(OUT_X_L_M);
		uint8_t XL = readXL();
		setRegister(OUT_X_H_M);
		uint8_t XH = readXH();
		uint16_t X = (XH << 8 | XL);
				
		setRegister(OUT_Y_L_M);
		uint8_t YL = readYL();
		setRegister(OUT_Y_H_M);
		uint8_t YH = readYH();
		uint16_t Y = (YH << 8 | YL);
		
		setRegister(OUT_Z_L_M);
		uint8_t ZL = readZL();
		setRegister(OUT_Z_H_M);
		uint8_t ZH = readZH();
		uint16_t Z = (ZH << 8 | ZL);
	 
		_delay_ms(2000);
		xTotaal = xTotaal + X;
		yTotaal = yTotaal + Y;
		zTotaal = zTotaal + Z;
	}
	
	xOff = xTotaal / 1024;
	yOff = yTotaal / 1024;
	zOff = zTotaal / 1024;

}
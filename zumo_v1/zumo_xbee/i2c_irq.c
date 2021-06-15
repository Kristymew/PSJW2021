#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>

#include "i2c_irq.h"

void initI2C(void) {
	/* set pullups for SDA, SCL lines */
	I2C_SDA_PORT |= ((1 << I2C_SDA) | (1 << I2C_SCL));			// Op output
	TWBR = 72;													// set I2C bit rate (p.242): 16MHz / (16+2*TWBR*1) ~= 100kHz
	TWCR |= (1 << TWEN);										// Enable
}

void i2cWaitForComplete(void) {
	while (!(TWCR & (1<<TWINT)));
}

void i2cStart(void) {
	TWCR = (1<<TWSTA)|(1<<TWEN)|(1<<TWINT);
	i2cWaitForComplete();
}

void i2cStop(void) {
	TWCR = (1<<TWSTO)|(1<<TWINT)|(1<<TWEN);						// Enable TWI, generate stop condition and clear interrupt flag
	while(TWCR & (1<<TWSTO));
}

uint8_t i2cReadAck(void) {
	TWCR = (1<<TWEN)|(1<<TWINT)|(1<<TWEA);
	i2cWaitForComplete();
	return (TWDR);
}

uint8_t i2cReadNoAck(void) {
	TWCR = (1<<TWEN)|(1<<TWINT);
	i2cWaitForComplete();
	return (TWDR);
}

void i2cSend(uint8_t data) {
	TWDR = data;
	TWCR = (1<<TWEN)|(1<<TWINT);
	i2cWaitForComplete();
}

void setRegister(uint8_t r) {
	i2cStart();
	i2cSend(LSM303DAdresWrite);									// I2C adres master schrijf
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

void calibratie() {
	int32_t xTotaal = 0;
	int32_t yTotaal = 0;
	int32_t zTotaal = 0;

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

		_delay_ms(2);
		xTotaal = xTotaal + X;
		yTotaal = yTotaal + Y;
		zTotaal = zTotaal + Z;
	}
	xOff = xTotaal / 1024;
	yOff = yTotaal / 1024;
	zOff = zTotaal / 1024;
}

void magnetoMeter() {
	/*---------- Enable magnetometer --------*/
	// 0x64 = 0b01100100
	i2cStart();									// Begin Transmission
	i2cSend(LSM303DAdresWrite);					// Master in Transmit mode
	i2cSend(CTRL5);								// Access register CTRL5
	i2cSend(0x64);								// Master stuurt deze waarde naar het CTRL1 register
	i2cStop();									// Stop transmission

	// 0x20
	i2cStart();									// Begin Transmission
	i2cSend(LSM303DAdresWrite);					// Master in Transmit mode
	i2cSend(CTRL6);								// Access register CTRL6
	i2cSend(0x20);								// Master stuurt deze waarde naar het CTRL1 register
	i2cStop();									// Stop transmission

	// 0x00
	i2cStart();									// Begin Transmission
	i2cSend(LSM303DAdresWrite);					// Master in Transmit mode
	i2cSend(CTRL7);								// Access register CTRL7
	i2cSend(0x00);								// Master stuurt deze waarde naar het CTRL1 register
	i2cStop();									// Stop transmission
	calibratie();
}
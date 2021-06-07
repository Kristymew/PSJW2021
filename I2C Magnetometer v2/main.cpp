#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include "mrBeen.h"

#include "i2c.h"
#include "functies.h"

#define L3GD20HAdresWrite    	0b11010110 
#define L3GD20HAdresRead    	0b11010111


#define LSM303D

#define WHO_AM_I     	0x0F
#define CTRL1           0x20 // D20H
#define CTRL_REG1       0x20 // D20, 4200D
#define CTRL2          	0x21 // D20H
#define CTRL_REG2       0x21 // D20, 4200D
#define CTRL3           0x22 // D20H
#define CTRL_REG3       0x22 // D20, 4200D
#define CTRL4           0x23 // D20H
#define CTRL_REG4       0x23 // D20, 4200D
#define CTRL5           0x24 // D20H
#define CTRL_REG5       0x24 // D20, 4200D
#define REFERENCE       0x25
#define OUT_TEMP        0x26
#define STATUS          0x27 // D20H
#define STATUS_REG      0x27 // D20, 4200D
#define OUT_X_L         0x28
#define OUT_X_H         0x29
#define OUT_Y_L         0x2A
#define OUT_Y_H         0x2B
#define OUT_Z_L         0x2C
#define OUT_Z_H         0x2D
#define FIFO_CTRL       0x2E // D20H
#define FIFO_CTRL_REG   0x2E // D20, 4200D
#define FIFO_SRC        0x2F // D20H
#define FIFO_SRC_REG    0x2F // D20, 4200D
#define IG_CFG          0x30 // D20H
#define INT1_CFG        0x30 // D20, 4200D
#define IG_SRC          0x31 // D20H
#define INT1_SRC        0x31 // D20, 4200D
#define IG_THS_XH       0x32 // D20H
#define INT1_THS_XH     0x32 // D20, 4200D
#define IG_THS_XL       0x33 // D20H
#define INT1_THS_XL     0x33 // D20, 4200D
#define IG_THS_YH       0x34 // D20H
#define INT1_THS_YH     0x34 // D20, 4200D
#define IG_THS_YL       0x35 // D20H
#define INT1_THS_YL     0x35 // D20, 4200D
#define IG_THS_ZH       0x36 // D20H
#define INT1_THS_ZH     0x36 // D20, 4200D
#define IG_THS_ZL       0x37 // D20H
#define INT1_THS_ZL     0x37 // D20, 4200D
#define IG_DURATION     0x38 // D20H
#define INT1_DURATION   0x38 // D20, 4200D
#define LOW_ODR         0x39  // D20H

/*
#define LSM6DS33AdresWrite    	0b11010100
#define LSM6DS33AdresRead    	0b11010100

#define FUNC_CFG_ACCESS   = 0x01

#define FIFO_CTRL1        = 0x06
#define FIFO_CTRL2        = 0x07
#define FIFO_CTRL3        = 0x08
#define FIFO_CTRL4        = 0x09
#define FIFO_CTRL5        = 0x0A
#define ORIENT_CFG_G      = 0x0B

#define INT1_CTRL         = 0x0D
#define INT2_CTRL         = 0x0E
#define WHO_AM_I          = 0x0F
#define CTRL1_XL          = 0x10
#define CTRL2_G           = 0x11
#define CTRL3_C           = 0x12
#define CTRL4_C           = 0x13
#define CTRL5_C           = 0x14
#define CTRL6_C           = 0x15
#define CTRL7_G           = 0x16
#define CTRL8_XL          = 0x17
#define CTRL9_XL          = 0x18
#define CTRL10_C          = 0x19

#define WAKE_UP_SRC       = 0x1B
#define TAP_SRC           = 0x1C
#define D6D_SRC           = 0x1D
#define STATUS_REG        = 0x1E

#define OUT_TEMP_L        = 0x20
#define OUT_TEMP_H        = 0x21
#define OUTX_L_G          = 0x22
#define OUTX_H_G          = 0x23
#define OUTY_L_G          = 0x24
#define OUTY_H_G          = 0x25
#define OUTZ_L_G          = 0x26
#define OUTZ_H_G          = 0x27
#define OUTX_L_XL         = 0x28
#define OUTX_H_XL         = 0x29
#define OUTY_L_XL         = 0x2A
#define OUTY_H_XL         = 0x2B
#define OUTZ_L_XL         = 0x2C
#define OUTZ_H_XL         = 0x2D

#define FIFO_STATUS1      = 0x3A
#define FIFO_STATUS2      = 0x3B
#define FIFO_STATUS3      = 0x3C
#define FIFO_STATUS4      = 0x3D
#define FIFO_DATA_OUT_L   = 0x3E
#define FIFO_DATA_OUT_H   = 0x3F
#define TIMESTAMP0_REG    = 0x40
#define TIMESTAMP1_REG    = 0x41
#define TIMESTAMP2_REG    = 0x42

#define STEP_TIMESTAMP_L  = 0x49
#define STEP_TIMESTAMP_H  = 0x4A
#define STEP_COUNTER_L    = 0x4B
#define STEP_COUNTER_H    = 0x4C

#define FUNC_SRC          = 0x53

#define TAP_CFG           = 0x58
#define TAP_THS_6D        = 0x59
#define INT_DUR2          = 0x5A
#define WAKE_UP_THS       = 0x5B
#define WAKE_UP_DUR       = 0x5C
#define FREE_FALL         = 0x5D
#define MD1_CFG           = 0x5E
#define MD2_CFG           = 0x5F
*/
//void setConfigReg();
//void setResolutionReg();
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
	
	// *---------- Enable X, Y, Z axis --------*//
	// 0x7F = 0b01111111
	i2cStart(); // Begin Transmission
	i2cSend(L3GD20HAdresWrite); // Master in Transmit mode
	i2cSend(CTRL1); // Access register CTRL1
	i2cSend(0x7F); // Master stuurt deze waarde naar het CTRL1 register
	i2cStop(); // Stop transmission
	
    writeString("begin\n\r");  

   while(1)
   {
       
		writeString("Positie is: ");
	
		
		setRegister(OUT_X_L);
		uint8_t XL = readXL();
		setRegister(OUT_X_H);
		uint8_t XH = readXH();
		uint16_t X = (XH << 8 | XL);
		
		writeString("X: ");
		writeUnt(X);
		writeString(" ");
		
		setRegister(OUT_Y_L);
		uint8_t YL = readYL();
		setRegister(OUT_Y_H);
		uint8_t YH = readYH();
		uint16_t Y = (YH << 8 | YL);
		
		writeString("Y: ");
		writeUnt(Y);
		writeString(" ");
		
		setRegister(OUT_Z_L);
		uint8_t ZL = readZL();
		setRegister(OUT_Z_H);
		uint8_t ZH = readZH();
		uint16_t Z = (ZH << 8 | ZL);
		
		writeString("Z: ");
		writeUnt(Z);
		writeString("\n\r");
		_delay_ms(500);
		
		
		
	
		

  }

}

/*void setConfigReg() {
	i2cStart();
	i2cSend(L3GD20HAdres<<1);   //i2c adres master schrijf
	i2cSend(CONFIG_REG);
	i2cSend(0);
	i2cSend(0);
	i2cStop();
}*/

/*void setResolutionReg(){
	i2cStart();
	i2cSend(L3GD20HAdres<<1);   //i2c adres master schrijf
	i2cSend(RESOLUTIE_REG);
	i2cSend(3);
	i2cStop();
}*/

void setRegister(uint8_t r) {
	i2cStart();   
	i2cSend(L3GD20HAdresWrite);//i2c adres master schrijf
	i2cSend(r);
	i2cStop();
}

uint8_t readXL() {
	i2cStart();
	i2cSend(L3GD20HAdresRead);
	uint8_t xl = i2cReadNoAck();	
	//i2cStop();
	return xl;
}
uint8_t readXH() {
	i2cStart();
	i2cSend(L3GD20HAdresRead);
	uint8_t xh = i2cReadNoAck();	
	//i2cStop();
	return xh;
}

uint8_t readYL() {
	i2cStart();
	i2cSend(L3GD20HAdresRead);
	uint8_t yl = i2cReadNoAck();
	//i2cStop();
	return yl;
}
uint8_t readYH() {
	i2cStart();
	i2cSend(L3GD20HAdresRead);
	uint8_t yh = i2cReadNoAck();	
	//i2cStop();
	return yh;
}
uint8_t readZL() {
	i2cStart();
	i2cSend(L3GD20HAdresRead);
	uint8_t zl = i2cReadNoAck();
	//i2cStop();
	return zl;
}
uint8_t readZH() {
	i2cStart();
	i2cSend(L3GD20HAdresRead);
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

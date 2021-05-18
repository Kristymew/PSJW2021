#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include "mrBeen.h"

#include "i2c.h"
#include "functies.h"

#define L3GD20HAdres    0b11010110 

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

	initialiseerGeleLed();   // 
	initUsart();
    initI2C();
    writeString("begin\n\r");  

   while(1)
   {
        //zetGeleLedAan();
        //_delay_ms(1250);
        //zetGeleLedUit();
        //_delay_ms(750);
		writeString("Positie is: ");
		
		setRegister(OUT_X_L);
		uint8_t XL=readXL();
		setRegister(OUT_X_H);
		uint8_t XH=readXH();
		uint16_t X = (XH << 8 | XL);
		writeUnt(X);
		
		setRegister(OUT_Y_L);
		uint8_t YL=readYL();
		setRegister(OUT_Y_H);
		uint8_t YH=readYH();
		uint16_t Y = (YH << 8 | YL);
		writeUnt(Y);
		
		setRegister(OUT_Z_L);
		uint8_t ZL=readZL();
		setRegister(OUT_Z_H);
		uint8_t ZH=readZH();
		uint16_t Z = (ZH << 8 | ZL);
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
	i2cSend(L3GD20HAdres<<1);   //i2c adres master schrijf
	i2cSend(r);
	i2cStop();
}

uint8_t readXL() {
	i2cStart();
	i2cSend((L3GD20HAdres<<1)+1);   //i2c adres master read
	uint8_t xlg = i2cReadAck();	
	i2cStop();
	return xlg;
}
uint8_t readXH() {
	i2cStart();
	i2cSend((L3GD20HAdres<<1)+1);   //i2c adres master read
	uint8_t xhg = i2cReadAck();	
	i2cStop();
	return xhg;
}

uint8_t readYL() {
	i2cStart();
	i2cSend((L3GD20HAdres<<1)+1);	 //i2c adres master read
	uint8_t ylg = i2cReadAck();
	i2cStop();
	return ylg;
}
uint8_t readYH() {
	i2cStart();
	i2cSend((L3GD20HAdres<<1)+1);   //i2c adres master read
	uint8_t yhg = i2cReadAck();	
	i2cStop();
	return yhg;
}
uint8_t readZL() {
	i2cStart();
	i2cSend((L3GD20HAdres<<1)+1);   //i2c adres master read
	uint8_t zlg = i2cReadAck();
	i2cStop();
	return zlg;
}
uint8_t readZH() {
	i2cStart();
	i2cSend((L3GD20HAdres<<1)+1);   //i2c adres master read
	uint8_t zhg = i2cReadAck();	
	i2cStop();
	return zhg;
}
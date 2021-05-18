#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include "mrBeen.h"

#include "i2c.h"
#include "functies.h"

#define L3GD20HAdres    0xD2 

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
uint16_t readX();
uint16_t readY();
uint16_t readZ();

int main()
{

	initialiseerGeleLed();   // 
	initUsart();
    initI2C();
    writeString("begin\n\r");  

   while(1)
   {
        zetGeleLedAan();
        _delay_ms(1250);
        zetGeleLedUit();
        _delay_ms(750);
		writeString("Positie is: ");
		setRegister(WHO_AM_I);
		uint16_t X=readX();
		writeUnt(X);
		uint16_t Y=readY();
		writeUnt(Y);
		uint16_t Z=readZ();
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


uint16_t readX() {
	i2cStart();
	i2cSend((L3GD20HAdres<<1)+1);   //i2c adres master read
	uint8_t xlg = i2cReadAck();
	uint8_t xhg = i2cReadNoAck();	
	i2cStop();
	int16_t gx = (xhg << 8 | xlg);
	return gx;
}

uint16_t readY() {
	i2cStart();
	i2cSend((L3GD20HAdres<<1)+1);
	uint8_t ylg = i2cReadAck();
	uint8_t yhg = i2cReadNoAck();
	i2cStop();
	int16_t gy = (yhg << 8 | ylg);
	return gy;
}
uint16_t readZ() {
	i2cStart();
	i2cSend((L3GD20HAdres<<1)+1);   //i2c adres master read
	uint8_t zlg = i2cReadAck();
	uint8_t zhg = i2cReadNoAck();
	i2cStop();
	int16_t gz = (zhg << 8 | zlg);
	return gz;
}
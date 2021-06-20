#ifndef I2C_IRQ_H_
#define I2C_IRQ_H_

#define I2C_SDA        PORTD1
#define I2C_SDA_PORT   PORTD
#define I2C_SCL        PORTD0

#define LSM303DAdresWrite	0b00111010
#define LSM303DAdresRead	0b00111011
#define L3GD20HAdresWrite   0b11010110	
#define L3GD20HAdresRead	0b11010111

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
#define	OUT_X_L			0x28
#define OUT_X_H			0x29
#define OUT_Y_L			0x2A
#define OUT_Y_H			0x2B
#define OUT_Z_L			0x2C
#define OUT_Z_H			0x2D

void initI2C(void);
void i2cWaitForComplete(void);
void i2cStart(void);
void i2cStop(void);
void i2cSend(uint8_t data);
uint8_t i2cReadAck(void);
uint8_t i2cReadNoAck(void);

void setRegister(uint8_t r);
void calibratie();
void magnetoMeter();

uint8_t readXL();
uint8_t readXH();
uint8_t readYL();
uint8_t readYH();
uint8_t readZL();
uint8_t readZH();

static volatile int xOff;
static volatile int yOff;
static volatile int zOff;

#endif
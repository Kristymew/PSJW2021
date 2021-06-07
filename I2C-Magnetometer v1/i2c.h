// Functions for i2c communication
#include <avr/io.h>



#define I2C_SDA        PD1
#define I2C_SDA_PORT   PORTD
#define I2C_SCL        PD0
     

void initI2C(void);
void i2cWaitForComplete(void);
void i2cStart(void);
void i2cStop(void);
void i2cSend(uint8_t data);
uint8_t i2cReadAck(void);
uint8_t i2cReadNoAck(void);

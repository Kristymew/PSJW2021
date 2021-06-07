#include "i2c.h"

void initI2C(void) {
                                     /* set pullups for SDA, SCL lines */
  I2C_SDA_PORT |= ((1 << I2C_SDA) | (1 << I2C_SCL)); // op output
  TWBR = 72;   /* set I2C bit rate (p.242): 16MHz / (16+2*TWBR*1) ~= 100kHz */
  TWCR |= (1 << TWEN);                                       /* enable */
}

void i2cWaitForComplete(void) {
	while (!(TWCR & (1<<TWINT)));	
}

void i2cStart(void) {
  TWCR = (1<<TWSTA)|(1<<TWEN)|(1<<TWINT);		
  i2cWaitForComplete();
}

void i2cStop(void) {
  	TWCR=(1<<TWSTO)|(1<<TWINT)|(1<<TWEN);					/* Enable TWI, generate stop condition and clear interrupt flag */
  	while(TWCR & (1<<TWSTO));
}

uint8_t i2cReadAck(void) {
  TWCR=(1<<TWEN)|(1<<TWINT)|(1<<TWEA);	
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

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include "mrBeen.h"

#include "i2c.h"
#include "functies.h"



#define line_sensor1 PF7 
#define line_sensor2 PF5
#define line_sensor3 PF4
#define line_sensor4 PD4
#define line_sensor5 PD6

// a dark line = high values 
// a white line = low values


int main()
{

	initUsart();


   while(1)
   {
       
	
		

  }

}



#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include "mrBeen.h"


int main()
{

  
   DDRB |= (1 << PB2) | (1 << PB6) | (1 << PB1) | (1 << PB5); // linker en rechter direction en speed op output
   
   _delay_ms(3000);
   

   while(1)
   {
		
		PORTB |= (1 << PB6) | (1 << PB5); // zet de motor links op volle kracht
		_delay_ms(1000); // 2 sec.
		PORTB &= ~(1 << PB6 | 1 << PB2); // zet de linker motor uit
		_delay_ms(1800); // 1 sec
		
		//PORTB |= (1 << PB6); // zet linker motor weer aan
  }

}

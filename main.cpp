#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include "mrBeen.h"


int main()
{

  /* DDRB = 1 << PORTB1 | 1 << PORTB2 | 1 << PORTB5 | 1 << PORTB6;
   PORTB = 1 << PORTB5;
   _delay_ms(1000);
   PORTB &= ~(1 << PORTB5);
   
   _delay_ms(1000);
   PORTB = 1 << PB1;
   PORTB |= 1 << PB5;
   _delay_ms(1000);
   PORTB &= ~(1 << PB5);
   
   while(1); */




	// *** PWM *** //
	//TCCR1A = 0b10100000; // 160
    //TCCR1B = 0b00010001; // 17
    //ICR1 = 400; 
   // OCR1A = 0; // snelheid van de rechtermotor
   // OCR1B = 0; // snelheid van de linkermotor
   initMotors();

  
   //DDRB |= (1 << PB2) | (1 << PB6) | (1 << PB1) | (1 << PB5); // linker en rechter direction en speed op output
   
   _delay_ms(2000);
   

   while(1)
   {
		//OCR1A = 150;
		//OCR1B = 150;
		
		//PORTB |= (1 << PB6) | (1 << PB5); // zet de motor links en rechts op volle kracht
		//_delay_ms(1000); // 
		//PORTB &= ~(1 << PB6 | 1 << PB2); // zet de linkermotor uit
		//OCR1B = 0; // zet de snelheid van linkermotor uit
		//zetSnelheidMotorLinks(0);
		
		//_delay_ms(500); //  
		
		zetSnelheidMotorsAchteruit(50);
		
		
		//PORTB |= (1 << PB6) | (1 << PB5 | 1 << PB2 | 1 << PB1); // zet de motors achteruit op volle kracht
		//_delay_ms(1800); // 2 sec.
		//PORTB &= ~(1 << PB6 | 1 << PB2); // zet de linker motor uit
		//_delay_ms(300); // 1 sec
		
		
  }
  

}

int main()
{

	// *** PWM *** //
	TCCR1A = 0b10100000; // 160
    TCCR1B = 0b00010001; // 17
    ICR1 = 400; 
    OCR1A = 0; // snelheid van de rechtermotor
    OCR1B = 0; // snelheid van de linkermotor
  
   DDRB |= (1 << PB2) | (1 << PB6) | (1 << PB1) | (1 << PB5); // linker en rechter direction en speed op output
   
   _delay_ms(4000);
   

   while(1)
   {
		
		//zetSnelheidMotorRechts();
			zetSnelheidMotorRechts(uint16_t a)
		gaVoorruit(150);
		
	  
		//PORTB |= (1 << PB6) | (1 << PB5); // zet de motor links en rechts op volle kracht
		//PORTB &= ~(1 << PB6 | 1 << PB2); // zet de linkermotor uit
		/*PORTB |= (1 << PB6) | (1 << PB5 | 1 << PB2 | 1 << PB1); // zet de motors achteruit op volle kracht
		_delay_ms(1800); // 2 sec.
		PORTB &= ~(1 << PB6 | 1 << PB2); // zet de linker motor uit
		_delay_ms(300); // 1 sec
		*/
		
  }
void zetSnelheidMotorRechts(uint16_t a) {
		
		
		OCR1A = a;
		
}

void gaVoorruit(uint16_t a) {
	OCR1A = a ; // snelheid van de rechtermotor
    OCR1B = a + 12; // snelheid van de linkermotor
  
}  

}
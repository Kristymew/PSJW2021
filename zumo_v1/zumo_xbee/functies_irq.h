#ifndef FUNCTIES_IRQ_H_
#define FUNCTIES_IRQ_H_

#define TOETS_C              (1<<PORTB0)
#define rodeLED              (1<<PORTB0)
#define DIR_MOTOR_Rechts     (1<<PORTB1)
#define DIR_MOTOR_Links      (1<<PORTB2)
#define TOETS_A              (1<<PORTB3)
#define PWM_MOTOR_Rechts     (1<<PORTB5)	// OC1A
#define PWM_MOTOR_Links      (1<<PORTB6)	// OC1B
#define geleLED              (1<<PORTC7)	// OC4A
#define TOETS_B              (1<<PORTD5)
#define PWM_BUZZER           (1<<PORTD7)	// OC4D

void initialiseerGeleLed();
void zetGeleLedAan();
void zetGeleLedUit();

#endif
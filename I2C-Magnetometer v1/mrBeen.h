
#include <avr/io.h>
#ifndef ZUMO_H 
#define ZUMO_H
#include "zumoAansluitingen.h"
void initialiseerGeleLed();
void zetGeleLedAan();
void zetGeleLedUit();
void zetSnelheidMotorLinks(uint16_t);

#endif

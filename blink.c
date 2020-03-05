/* CS484 Project 3 LCD Panel
   Bicky Manandhar
   Nirmal Panta */
#include <avr/io.h>
#include "delay.h"

void main( void ) {
  DDRB |= 1 << PB5; // Set pin PB5 as an output pin
  while( 1 ) {
    PORTB |= 1<<PB5; // Turn LED on
    delay1ms( 1000 ); // Delay 1 second

    PORTB &= ~(1<<PB5); // Turn LED off
    delay1ms( 1000 ); // Delay 1 second.
  }
}

/* CS484 Project 3 LCD Panel
   Main program to output "Hello, World!" on LCD
   Bicky Manandhar
   Nirmal Panta
*/
#include <avr/io.h>
#include "lcd.h"

void main( void ) {
  lcdInit();
  lcdPuts( "Hello, World!" );
  while( 1 );
}

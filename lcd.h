/* CS484 Project 3 LCD Panel
   Bicky Manandhar
   Nirmal Panta */
#include <avr/io.h>

void pulseENABLE( void );
void write4bits( uint8_t );
void command( unsigned char );
void lcdInit( void );
void data( unsigned char );
void lcdPuts( unsigned char *);

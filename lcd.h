/* CS484 Project 3 LCD Panel
   Bicky Manandhar
   Nirmal Panta */
#include <avr/io.h>

void pulseENABLE( void );
void write4bits( uint8_t );
void command( uint8_t );
void lcdInit( void );
void data( uint8_t );
void lcdPuts( unsigned char *);

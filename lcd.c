/* CS484 Project 3 LCD Panel
   Bicky Manandhar
   Nirmal Panta
   Modified from program written by Don Bindner and Jon Beck */
#include <avr/io.h>
#include "lcd.h"
#include "delay.h"
// Assumption -- both control wires are on the same port
#define CTRL_DDR DDRD
#define CTRL_PORT PORTD
#define RS (1<<PD6)
#define ENABLE (1<<PD7)
// Assumption -- the four data wires are on the same port
#define DATA_DDR DDRB
#define DATA_PORT PORTB
#define DB4 (1<<PB0)
#define DB5 (1<<PB1)
#define DB6 (1<<PB2)
#define DB7 (1<<PB3)

void pulseENABLE( void ) {
  delay1us( 1 );
  CTRL_PORT |= ENABLE; // set ENABLE pin high
  delay1us( 1 );
  CTRL_PORT &= ~ENABLE; // set ENABLE pin low
  delay1us( 100 );
}

void write4bits( uint8_t bits ) {
  if( bits & 1 ) {
    DATA_PORT |= DB4;
  }
  else {
    DATA_PORT &= ~DB4;
  }
  if( bits & 2 ) {
    DATA_PORT |= DB5;
  }
  else {
    DATA_PORT &= ~DB5;
  }
  if( bits & 4 ) {
    DATA_PORT |= DB6;
  }
  else {
    DATA_PORT &= DB6;
  }
  if( bits & 8 ) {
    DATA_PORT |= DB7;
  }
  else {
    DATA_PORT &= ~DB7;
  }
  pulseENABLE();
}

void command( uint8_t cmd ) {
  CTRL_PORT &= ~RS; // RS pin is low for commands
  write4bits( cmd>>4 );
  write4bits( cmd );
}

void lcdInit( void ) {
  // Set all pins as outputs
  CTRL_DDR |= RS+ENABLE;
  DATA_DDR |= DB4+DB5+DB6+DB7;

  CTRL_PORT &= ~(RS+ENABLE); // Set RS and ENABLE low

  delay1ms( 50 ); // Wait 50ms for power on
  write4bits( 0x03 ); // Init routine is to write 0x03 three times
  delay1ms( 5 );
  write4bits( 0x03 );
  delay1ms( 1 );
  write4bits( 0x03 );
  delay1ms( 1 );
  write4bits( 0x02 ); // Choose 4-bit interface
  command( 0x28 ); // 2 lines with 5x8 font
  command( 0x0c ); // Display on, cursor off
  command( 0x01 ); // Clear display
  delay1ms( 2 ); // Wait 2ms for clear
  command( 0x06 ); // Left-to-right text
}

void data( uint8_t c ) {
  CTRL_PORT |= RS; // RS pin is high for data
  write4bits( c>>4 );
  write4bits( c );
}

void lcdPuts( unsigned char * s ) {
  while( *s ) data( *s++ );
}

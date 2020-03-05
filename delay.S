	;; delay.S
	;; Bicky Manandhar
	;; Nirmal Panta
	;; implements delay in microseconds and milliseconds
	;; Modified from program written by Don Bindner and Jon Beck
	
	#define __SFR_OFFSET 0
	#include <avr/io.h>

.macro 	nop2
	rjmp .
.endm
	
.text

.global	delay1us		; void delay1us( uint16_t n ) 

	;; delay in units of 16 cycles (1us at 16MHz)
delay1us:
	nop
	nop2
	rjmp delay2

delay1:
	nop2
	nop2
	nop2
	nop2
	nop2
	nop2
delay2:
	sbiw r24, 1		; subtract 1 from r24/r25
	brne delay1		; branch if not zero to delay1

	ret

.global delay1ms		; void delay1ms( uint16_t n )
delay1ms:
	movw r26, r24		; save millisecond count
	rjmp delay4

delay3:
	nop2
	nop2
	nop2
	nop2
	nop2
delay4:
	ldi r24, 231		; r24/r25 contains 231+3*256
	ldi r25, 3		; = 999us
	call delay1us
	sbiw r26, 1		; subtract 1 from r26/r27
	brne delay3		; branch if not zero

	ret
	

# Nirmal Panta and Bicky Manandhar
delay.o: delay.h delay.S
	avr-gcc -mmcu=atmega328p -c delay.S -o delay.o

lcd.o: lcd.h lcd.c
	avr-gcc -mmcu=atmega328p -c lcd.c -o lcd.o

main.o: main.c
	avr-gcc -mmcu=atmega328p -c main.c -o main.o

blink.elf: blink.c delay.S
	avr-gcc -O -mmcu=atmega328p -o blink.elf blink.c delay.S

blink.hex: blink.elf
	avr-objcopy -j .text -j .data -O ihex blink.elf blink.hex

main.elf: delay.o lcd.o main.o
	avr-gcc -mmcu=atmega328p delay.o lcd.o main.o -o main.elf

main.hex: main.elf
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex

install-main: main.hex
	avrdude -p atmega328p -c usbtiny -U flash:w:main.hex:i

install-blink: blink.hex
	avrdude -p atmega328p -c usbtiny -U flash:w:blink.hex:i

erase:
	avrdude -p atmega328p -c usbtiny -e

clean:
	rm -f *.o *.elf *.hex *.lst

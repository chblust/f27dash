all: test.hex

clean:
	rm *.hex *.elf *.o *.d *.s

test.hex: test.elf
	avr-objcopy -O ihex -j .text -j .data test.elf test.hex

test.elf: *.o
	avr-gcc -mmcu=at90can128  *.o -o test.elf -I /usr/local/CrossPack-AVR-20131216/avr/include

*.o:*.c
	avr-gcc -funsigned-char -Os -Werror -Wall -mmcu=at90can128 -c -std=gnu99 *.c -I /usr/local/CrossPack-AVR-20131216/avr/include

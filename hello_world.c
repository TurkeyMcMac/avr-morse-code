#include <avr/io.h>
#include <avr/pgmspace.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <stdbool.h>
#include <stdint.h>

#define LED_PORT PORTB
#define LED_PIN ( _BV(5) )

bool morse_encode(char c);

void display(char c)
{
	morse_encode(c);
	_delay_ms(300);
}

__attribute__((constructor))
void main(void)
{
	DDRD = -1;

	while(1) {
		display('H');
		display('e');
		display('l');
		display('l');
		display('o');
		display(',');
		display(' ');
		display('w');
		display('o');
		display('r');
		display('l');
		display('d');
		display('!');
		_delay_ms(2000);
	}
}

bool morse_encode(char c)
{
#	define MORSE(ch, pattern) [ch] = 0b1##pattern
	static PROGMEM const char morse_table[128] = {
		MORSE('A', 01),
		MORSE('B', 1000),
		MORSE('C', 1010),
		MORSE('D', 100),
		MORSE('E', 0),
		MORSE('F', 0010),
		MORSE('G', 110),
		MORSE('H', 0000),
		MORSE('I', 00),
		MORSE('J', 0111),
		MORSE('K', 101),
		MORSE('L', 0100),
		MORSE('M', 11),
		MORSE('N', 10),
		MORSE('O', 111),
		MORSE('P', 0110),
		MORSE('Q', 1101),
		MORSE('R', 010),
		MORSE('S', 000),
		MORSE('T', 1),
		MORSE('U', 001),
		MORSE('V', 0001),
		MORSE('W', 011),
		MORSE('X', 1001),
		MORSE('Y', 1011),
		MORSE('Z', 1100),
		MORSE('a', 01),
		MORSE('b', 1000),
		MORSE('c', 1010),
		MORSE('d', 100),
		MORSE('e', 0),
		MORSE('f', 0010),
		MORSE('g', 110),
		MORSE('h', 0000),
		MORSE('i', 00),
		MORSE('j', 0111),
		MORSE('k', 101),
		MORSE('l', 0100),
		MORSE('m', 11),
		MORSE('n', 10),
		MORSE('o', 111),
		MORSE('p', 0110),
		MORSE('q', 1101),
		MORSE('r', 010),
		MORSE('s', 000),
		MORSE('t', 1),
		MORSE('u', 001),
		MORSE('v', 0001),
		MORSE('w', 011),
		MORSE('x', 1001),
		MORSE('y', 1011),
		MORSE('z', 1100),
		MORSE(',', 110011),
		MORSE('!', 101011),
	};
#	undef MORSE

	uint8_t morse, len;

	if (c == ' ') {
		_delay_ms(400);
		return true;
	}
	morse = pgm_read_byte(morse_table + c);
	if (!morse) {
		return false;
	}
	len = 7;
	while (!(morse & 0b10000000)) {
		morse <<= 1;
		--len;
	}
	morse >>= 7 - len;
	while (len--) {
		LED_PORT |= LED_PIN;
		if (morse & (1 << len)) {
			_delay_ms(300);
		} else {
			_delay_ms(100);
		}
		LED_PORT &= ~LED_PIN;
		_delay_ms(100);
	}
	_delay_ms(200);

	return true;
}


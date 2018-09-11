#include <avr/io.h>
#include <avr/pgmspace.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <stdbool.h>
#include <stdint.h>

#define LED_PORT PORTB
#define LED_PIN ( _BV(5) )

#define MORSE_DELAY_SCALE 100

void morse_encode_message_P(const char *msg);

__attribute__((constructor))
void main(void)
{
	static PROGMEM const char message[] = "Hello, world!";

	DDRD = -1;

	while(1) {
		morse_encode_message_P(message);
		_delay_ms(2000);
	}
}

bool morse_encode(char c);

void morse_encode_message_P(const char *msg)
{
	char c;

	while ((c = pgm_read_byte(msg)) != '\0') {
		morse_encode(c);
		++msg;
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
		_delay_ms(4 * MORSE_DELAY_SCALE);
		return true;
	}
	morse = pgm_read_byte(morse_table + c);
	if (!morse) {
		return false;
	}
	len = 7;
	while (!(morse & _BV(len))) {
		--len;
	}
	while (len--) {
		LED_PORT |= LED_PIN;
		if (morse & _BV(len)) {
			_delay_ms(3 * MORSE_DELAY_SCALE);
		} else {
			_delay_ms(1 * MORSE_DELAY_SCALE);
		}
		LED_PORT &= ~LED_PIN;
		_delay_ms(1 * MORSE_DELAY_SCALE);
	}
	_delay_ms(2 * MORSE_DELAY_SCALE);

	return true;
}


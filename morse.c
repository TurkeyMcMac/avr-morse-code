#include "morse.h"

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdint.h>

#define LED_PORT PORTB
#define LED_PIN ( _BV(5) )

#define MORSE_DELAY_SCALE 200

void morse_encode_message(const char *msg)
{
	char c;

	morse_encode('\x02');
	while ((c = *msg) != '\0') {
		morse_encode(c);
		++msg;
	}
	morse_encode('\x03');

}

void morse_encode_message_P(const char *msg)
{
	char c;

	morse_encode('\x02');
	while ((c = pgm_read_byte(msg)) != '\0') {
		morse_encode(c);
		++msg;
	}
	morse_encode('\x03');
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
		MORSE('1', 01111),
		MORSE('2', 00111),
		MORSE('3', 00011),
		MORSE('4', 00001),
		MORSE('5', 00000),
		MORSE('6', 10000),
		MORSE('7', 11000),
		MORSE('8', 11100),
		MORSE('9', 11110),
		MORSE('0', 11111),
		MORSE('.', 010101),
		MORSE(',', 110011),
		MORSE(':', 111000),
		MORSE('?', 001100),
		MORSE('\'', 011110),
		MORSE('-', 100001),
		MORSE('/', 10010),
		MORSE('(', 10110),
		MORSE(')', 101101),
		MORSE('"', 010010),
		MORSE('=', 10001),
		MORSE('+', 01010),
		MORSE('\x03', 000101), // End of Text character
		MORSE('\x02', 10101), // Start of Text character
		MORSE('*', 1001),
		MORSE('@', 011010),
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

#include "morse.h"
#include <util/delay.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

__attribute__((constructor))
void main(void)
{
	static PROGMEM const char message[] = "Hello, world.";

	DDRD = -1;

	while(1) {
		morse_encode_message_P(message);
		_delay_ms(2000);
	}
}

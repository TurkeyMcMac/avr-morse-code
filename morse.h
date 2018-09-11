#ifndef MORSE_H_
#define MORSE_H_

#include <stdbool.h>

void morse_encode_message(const char *msg);

void morse_encode_message_P(const char *msg);

bool morse_encode(char c);

#endif // Header guard

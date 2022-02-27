#ifndef __GUITAR_LEDS__H
#define __GUITAR_LEDS__H

#include <stdint.h>
#include <stddef.h>

#include "apa102.hpp"

class guitar_leds {
public:
	const size_t NUM_FRETS = 4;
	const size_t NUM_STRINGS = 6;

	guitar_leds(const float starting_frequency[NUM_STRINGS], const char starting_note[NUM_STRINGS]);

	apa102_led_t led[NUM_FRETS][NUM_STRINGS];
	float freq[NUM_FRETS][NUM_STRINGS];
	char* note[NUM_FRETS][NUM_STRINGS];
};

#endif

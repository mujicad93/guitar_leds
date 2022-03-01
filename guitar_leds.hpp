#ifndef __GUITAR_LEDS__H
#define __GUITAR_LEDS__H

#include <stdint.h>
#include <stddef.h>

#include "apa102.hpp"

class guitar_leds {
public:
	const static size_t NUM_FRETS = 4;
	const static size_t NUM_STRINGS = 6;
	const static uint8_t DEFAULT_BRIGHTNESS = 5;

	guitar_leds(const float starting_frequency[NUM_STRINGS], const char* const starting_note[NUM_STRINGS]);

	/*
	 * @brief Set all notes to value (with option to clear all other notes)
	 */
	void set_all_notes(const char* const note_in, const apa102_led_t value, const bool clear_others);

	apa102_led_t led[NUM_FRETS][NUM_STRINGS];
	float freq[NUM_FRETS][NUM_STRINGS];
	const char* note[NUM_FRETS][NUM_STRINGS];
};

#endif

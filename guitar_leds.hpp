#ifndef __GUITAR_LEDS__H
#define __GUITAR_LEDS__H

#include <stdint.h>
#include <stddef.h>

#include "apa102.hpp"

struct note_alias {
	const char* sharp;
	const char* flat;
};

class guitar_leds {
public:
	const static size_t NUM_FRETS = 4;
	const static size_t NUM_STRINGS = 6;
	const static uint8_t DEFAULT_BRIGHTNESS = 1;

	guitar_leds(const float starting_frequency[NUM_STRINGS], const char* const starting_note[NUM_STRINGS], apa102* p_apa_102_in);

	/*
	 * @brief Set all notes to value
	 * @input note_in - String representation of note to set
	 * @input value - Value to set LED to
	 * @input clear_others - Flag to clear all non-matching frets
	 */
	void set_all_notes(const char* const note_in, const apa102_led_t value, const bool clear_others);

	/*
	 * @brief Set fret matching frequency
	 * @input freq_in - Frequency of note to set
	 * @input value - Value to set LED to
	 * @input clear_others - Flag to clear all non-matching frets
	 */
	void set_freq(const float freq_in, const apa102_led_t value, const bool clear_others);

	/*
	 * @brief Set specific fret
	 * @input fret_idx - Which fret to set
	 * @input string_idx - Which string to set
	 * @input value - Value to set LED to
	 * @input clear_others - Flag to clear all non-matching frets
	 */
	void set_fret(const size_t fret_idx, const size_t string_idx, const apa102_led_t value, const bool clear_others);

	/*
	 * @brief Set chord
	 * @input fret_idx[NUM_STRINGS] - Fret to set on each string (set to NUM_FRETS if you want it blank)
	 * @input value - Value to set LED to
	 */
	void set_chord(const size_t fret[NUM_STRINGS], const apa102_led_t value);

	/*
	 * @brief Set leds once matrix has been filled
	 */
	void set_leds(void);

private:
	apa102* p_apa102;
	apa102_led_t led[NUM_FRETS][NUM_STRINGS];

	float freq[NUM_FRETS][NUM_STRINGS];
	const struct note_alias* note[NUM_FRETS][NUM_STRINGS];
};

#endif

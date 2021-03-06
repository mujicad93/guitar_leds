#include "guitar_leds.hpp"

#include <string.h>
#include <math.h>

const float EQUAL_TEMPERAMENT_RATIO = pow(2., (1. / 12.)); // 12√2
const float FUZZY_EQUAL_TEMPERAMENT_RATIO = EQUAL_TEMPERAMENT_RATIO - 0.001f;
const struct note_alias NOTES[] = {
	{"A", "A"},
	{"A#", "Bb"},
	{"B", "B"},
	{"C", "C"},
	{"C#", "Db"},
	{"D", "D"},
	{"D#", "Eb"},
	{"E", "E"},
	{"F", "F"},
	{"F#", "Gb"},
	{"G", "G"},
	{"G#", "Ab"},
};

const size_t NUM_NOTES = (sizeof(NOTES) / sizeof(NOTES[0]));

const struct note_alias* current_note(const char* const note)
{
	for (size_t note_idx = 0; note_idx < NUM_NOTES; note_idx++)
	{
		if (strcasecmp(note, NOTES[note_idx].sharp) == 0 || strcasecmp(note, NOTES[note_idx].flat) == 0)
			return &NOTES[note_idx];
	}
}

const struct note_alias* next_note(const char* const note)
{
	for (size_t note_idx = 0; note_idx < NUM_NOTES; note_idx++)
	{
		if (strcasecmp(note, NOTES[note_idx].sharp) == 0 || strcasecmp(note, NOTES[note_idx].flat) == 0)
			return &NOTES[(note_idx + 1) % NUM_NOTES];
	}
}

guitar_leds::guitar_leds(const float starting_frequency[NUM_STRINGS], const char* const starting_note[NUM_STRINGS], apa102* p_apa102_in)
{
	p_apa102 = p_apa102_in;

	for (size_t string_idx = 0; string_idx < NUM_STRINGS; string_idx++)
	{
		for (size_t fret_idx = 0; fret_idx < NUM_FRETS; fret_idx++)
		{
			if (fret_idx == 0)
			{
				freq[fret_idx][string_idx] = starting_frequency[string_idx];
				note[fret_idx][string_idx] = current_note(starting_note[string_idx]);
			}
			else
			{
				freq[fret_idx][string_idx] = freq[fret_idx - 1][string_idx] * EQUAL_TEMPERAMENT_RATIO;
				note[fret_idx][string_idx] = next_note(note[fret_idx - 1][string_idx]->flat);
			}

			led[fret_idx][string_idx] = (apa102_led_t){ .led = {.red = 0, .green = 0, .blue = 0, .brightness = DEFAULT_BRIGHTNESS } };
		}
	}
}

void guitar_leds::set_note(const char* const note_in, const apa102_led_t value, const bool clear_others)
{
	for (size_t string_idx = 0; string_idx < NUM_STRINGS; string_idx++)
	{
		for (size_t fret_idx = 0; fret_idx < NUM_FRETS; fret_idx++)
		{
			if (strcasecmp(note[fret_idx][string_idx]->flat, note_in) == 0 || strcasecmp(note[fret_idx][string_idx]->sharp, note_in) == 0)
				led[fret_idx][string_idx] = value;
			else
			{
				if (clear_others)
					led[fret_idx][string_idx] = (apa102_led_t){ .led = {.red = 0, .green = 0, .blue = 0, .brightness = DEFAULT_BRIGHTNESS } };
			}
		}
	}
}

void guitar_leds::set_freq(const float freq_in, const apa102_led_t value, const bool clear_others)
{
	for (size_t string_idx = 0; string_idx < NUM_STRINGS; string_idx++)
	{
		for (size_t fret_idx = 0; fret_idx < NUM_FRETS; fret_idx++)
		{
			if (freq[fret_idx][string_idx] > (freq_in / FUZZY_EQUAL_TEMPERAMENT_RATIO) && freq[fret_idx][string_idx] < (freq_in * FUZZY_EQUAL_TEMPERAMENT_RATIO))
				led[fret_idx][string_idx] = value;
			else
			{
				if (clear_others)
					led[fret_idx][string_idx] = (apa102_led_t){ .led = {.red = 0, .green = 0, .blue = 0, .brightness = DEFAULT_BRIGHTNESS } };
			}
		}
	}
}

void guitar_leds::set_fret(const size_t fret_idx, const size_t string_idx, const apa102_led_t value, const bool clear_others)
{
	if (clear_others)
	{
		for (size_t string_idx = 0; string_idx < NUM_STRINGS; string_idx++)
		{
			for (size_t fret_idx = 0; fret_idx < NUM_FRETS; fret_idx++)
			{
				led[fret_idx][string_idx] = (apa102_led_t){ .led = {.red = 0, .green = 0, .blue = 0, .brightness = DEFAULT_BRIGHTNESS } };
			}
		}
	}

	led[fret_idx][string_idx] = value;
}

void guitar_leds::set_chord(const size_t fret[NUM_STRINGS], const apa102_led_t value)
{
	for (size_t string_idx = 0; string_idx < NUM_STRINGS; string_idx++)
	{
		for (size_t fret_idx = 0; fret_idx < NUM_FRETS; fret_idx++)
		{
			if (fret[string_idx] == fret_idx)
				led[fret_idx][string_idx] = value;
			else
				led[fret_idx][string_idx] = (apa102_led_t){ .led = {.red = 0, .green = 0, .blue = 0, .brightness = DEFAULT_BRIGHTNESS } };
		}
	}
}

void guitar_leds::set_all(const apa102_led_t value)
{
	for (size_t string_idx = 0; string_idx < NUM_STRINGS; string_idx++)
	{
		for (size_t fret_idx = 0; fret_idx < NUM_FRETS; fret_idx++)
		{
			led[fret_idx][string_idx] = value;
		}
	}
}

void guitar_leds::clear_all(void)
{
	for (size_t string_idx = 0; string_idx < NUM_STRINGS; string_idx++)
	{
		for (size_t fret_idx = 0; fret_idx < NUM_FRETS; fret_idx++)
		{
			led[fret_idx][string_idx] = (apa102_led_t){ .led = {.red = 0, .green = 0, .blue = 0, .brightness = DEFAULT_BRIGHTNESS } };
		}
	}
}

void guitar_leds::update_leds(void)
{
	p_apa102->set_leds(&led[0][0], sizeof(led));
}

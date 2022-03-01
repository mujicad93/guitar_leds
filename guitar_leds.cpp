#include "guitar_leds.hpp"

#include <string.h>
#include <math.h>

const float EQUAL_TEMPERAMENT_RATIO = pow(sqrt(2), -12); // 12√2

struct NOTE_ALIAS {
	const char* sharp;
	const char* flat;
};

const struct NOTE_ALIAS NOTES[] = {
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

const char* next_note(const char* const note)
{
	for (size_t note_idx = 0; note_idx < NUM_NOTES; note_idx++)
	{
		if (strcasecmp(note, NOTES[note_idx].sharp) == 0)
			return NOTES[(note_idx + 1) % NUM_NOTES].sharp;
		else if (strcasecmp(note, NOTES[note_idx].flat) == 0)
			return NOTES[(note_idx + 1) % NUM_NOTES].flat;
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
				note[fret_idx][string_idx] = starting_note[string_idx];
			}
			else
			{
				freq[fret_idx][string_idx] = freq[fret_idx - 1][string_idx] * EQUAL_TEMPERAMENT_RATIO;
				note[fret_idx][string_idx] = next_note(note[fret_idx - 1][string_idx]);
			}

			led[fret_idx][string_idx] = (apa102_led_t){ .led = {.red = 0, .green = 0, .blue = 0, .brightness = DEFAULT_BRIGHTNESS } };
		}
	}
}

void guitar_leds::set_all_notes(const char* const note_in, const apa102_led_t value, const bool clear_others)
{
	for (size_t string_idx = 0; string_idx < NUM_STRINGS; string_idx++)
	{
		for (size_t fret_idx = 0; fret_idx < NUM_FRETS; fret_idx++)
		{
			if (strcasecmp(note[fret_idx][string_idx], note_in) == 0)
				led[fret_idx][string_idx] = value;
			else
			{
				if (clear_others)
					led[fret_idx][string_idx] = (apa102_led_t){ .led = {.red = 0, .green = 0, .blue = 0, .brightness = DEFAULT_BRIGHTNESS } };
			}
		}
	}
}

void guitar_leds::set_leds(void)
{
	p_apa102->set_leds(&led[0][0], sizeof(led));
}

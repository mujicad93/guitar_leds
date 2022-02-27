#include "guitar_leds.hpp"

#include <string.h>

struct NOTE_ALIAS {
	char* sharp;
	char* flat;
}

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

struct NOTE_ALIAS* next_note(char* note)
{
	for (size_t note_idx = 0; note_idx < NUM_NOTES; note_idx++)
	{
		if (strcasecmp(note, NOTES[note_idx][0]))
			return NOTES[(note_idx + 1) % NUM_NOTES][0];
		else if (strcasecmp(note, NOTES[note_idx][1]))
			return NOTES[(note_idx + 1) % NUM_NOTES][1];
	}
}

guitar_leds::guitar_leds(const float starting_frequency[NUM_STRINGS], const char* starting_note[NUM_STRINGS])
{
	for (size_t string_idx = 0; string_idx < this.NUM_STRINGS; string_idx++)
	{
		for (size_t fret_idx = 0; fret_idx < this.NUM_FRETS; fret_idx++)
		{
			if (fret_idx == 0)
			{
				this.freq[fret_idx][string_idx] = starting_frequency[string_idx];
				this.note[fret_idx][string_idx] = starting_note[string_idx];
			}
			else
			{
				this.freq[fret_idx][string_idx] = this.freq[fret_idx - 1][string_idx] * 1.0595f;
				this.note[fret_idx][string_idx] = next_note(this.note[fret_idx - 1][string_idx];
			}
		}
	}
}

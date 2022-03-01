#include <SPI.h>

#include "guitar_leds.hpp"
#include "guitar_chords.hpp"
#include "apa102_colors.hpp"

#define VERBOSE (false)
#define COLOR_TEST (true)

const char* STARTING_NOTES[] = { "E", "A", "D", "G", "B", "E" };
const float STARTING_FREQ[] = { 82.41f, 110.f, 146.83f, 196.f, 246.94f, 329.63f };

void init_apa102_comm(void)
{
	SPI.begin();
	SPI.beginTransaction(SPISettings(16000000, MSBFIRST, SPI_MODE0));
}

apa102 Apa102(init_apa102_comm, SPI.transfer);
guitar_leds Guitar_leds(STARTING_FREQ, STARTING_NOTES, &Apa102);

void setup() {
	// Delay for SPI startup
	delay(5000);
}

#define CLEAR_OTHER_LEDS (true)
#define DONT_CLEAR_OTHER_LEDS (false)

void loop() {
	Guitar_leds.set_note("E", RED(DIM), CLEAR_OTHER_LEDS);
	Guitar_leds.update_leds();
	delay(1000);

	Guitar_leds.set_note("A", RED(DIM), DONT_CLEAR_OTHER_LEDS);
	Guitar_leds.update_leds();
	delay(1000);

	Guitar_leds.set_note("D", RED(DIM), DONT_CLEAR_OTHER_LEDS);
	Guitar_leds.update_leds();
	delay(1000);

	Guitar_leds.set_note("G#", BLUE(DIM), CLEAR_OTHER_LEDS);
	Guitar_leds.update_leds();
	delay(1000);

	Guitar_leds.set_note("Bb", BLUE(DIM), CLEAR_OTHER_LEDS);
	Guitar_leds.update_leds();
	delay(1000);

	Guitar_leds.set_note("eb", BLUE(DIM), CLEAR_OTHER_LEDS);
	Guitar_leds.update_leds();
	delay(1000);

	Guitar_leds.set_freq(196.f, GREEN(DIM), CLEAR_OTHER_LEDS);
	Guitar_leds.update_leds();
	delay(1000);

	Guitar_leds.set_freq(220.f, GREEN(DIM), CLEAR_OTHER_LEDS);
	Guitar_leds.update_leds();
	delay(1000);

	Guitar_leds.set_fret(0, 0, WHITE(DIM), CLEAR_OTHER_LEDS);
	Guitar_leds.update_leds();
	delay(1000);

	Guitar_leds.set_fret(1, 1, WHITE(DIM), CLEAR_OTHER_LEDS);
	Guitar_leds.update_leds();
	delay(1000);

	Guitar_leds.set_fret(2, 2, WHITE(DIM), CLEAR_OTHER_LEDS);
	Guitar_leds.update_leds();
	delay(1000);

	Guitar_leds.set_fret(3, 3, WHITE(DIM), CLEAR_OTHER_LEDS);
	Guitar_leds.update_leds();
	delay(1000);

	Guitar_leds.set_chord(G_MAJ_CHORD, PURPLE(DIM));
	Guitar_leds.update_leds();
	delay(3000);

	Guitar_leds.set_chord(A_MIN_CHORD, TEAL(DIM));
	Guitar_leds.update_leds();
	delay(3000);

	Guitar_leds.set_chord(A_MAJ_CHORD, YELLOW(DIM));
	Guitar_leds.update_leds();
	delay(3000);

	Guitar_leds.set_chord(D_MAJ_CHORD, ORANGE(DIM));
	Guitar_leds.update_leds();
	delay(3000);

#if COLOR_TEST
	Guitar_leds.set_all(RED(DIM));
	Guitar_leds.update_leds();
	delay(1000);

	Guitar_leds.set_all(BLUE(DIM));
	Guitar_leds.update_leds();
	delay(1000);

	Guitar_leds.set_all(GREEN(DIM));
	Guitar_leds.update_leds();
	delay(1000);

	Guitar_leds.set_all(PURPLE(DIM));
	Guitar_leds.update_leds();
	delay(1000);

	Guitar_leds.set_all(TEAL(DIM));
	Guitar_leds.update_leds();
	delay(1000);

	Guitar_leds.set_all(YELLOW(DIM));
	Guitar_leds.update_leds();
	delay(1000);

	Guitar_leds.set_all(ORANGE(DIM));
	Guitar_leds.update_leds();
	delay(1000);

	Guitar_leds.set_all(WHITE(DIM));
	Guitar_leds.update_leds();
	delay(1000);

	Guitar_leds.clear_all();
	Guitar_leds.update_leds();
	delay(1000);
#endif
}

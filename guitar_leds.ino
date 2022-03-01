#include <SPI.h>

#include "guitar_leds.hpp"

apa102* p_apa102;
guitar_leds* p_guitar_leds;

const char* STARTING_NOTES[] = { "E", "A", "D", "G", "B", "E" };
const float STARTING_FREQ[] = { 82.41f, 110.f, 146.83f, 196.f, 246.94f, 329.63f };

void init_apa102_comm(void)
{
	SPI.begin();
	SPI.beginTransaction(SPISettings(16000000, MSBFIRST, SPI_MODE0));
}

void setup() {
	p_apa102 = new apa102(init_apa102_comm, SPI.transfer);
	p_guitar_leds = new guitar_leds(STARTING_FREQ, STARTING_NOTES);
	delay(5000);
}

void loop() {
	p_guitar_leds->set_all_notes("E", (apa102_led_t) { .led = { .red = 0xFF, .green = 0, .blue = 0, .brightness = 5 } }, true);
	delay(5000);

	p_guitar_leds->set_all_notes("A", (apa102_led_t) { .led = { .red = 0xFF, .green = 0, .blue = 0, .brightness = 5 } }, false);
	delay(5000);

	p_guitar_leds->set_all_notes("D", (apa102_led_t) { .led = { .red = 0xFF, .green = 0, .blue = 0, .brightness = 5 } }, false);
	delay(5000);

	p_guitar_leds->set_all_notes("E", (apa102_led_t) { .led = { .red = 0xFF, .green = 0, .blue = 0, .brightness = 5 } }, true);
	delay(5000);

	p_guitar_leds->set_all_notes("A", (apa102_led_t) { .led = { .red = 0xFF, .green = 0, .blue = 0, .brightness = 5 } }, true);
	delay(5000);

	p_guitar_leds->set_all_notes("D", (apa102_led_t) { .led = { .red = 0xFF, .green = 0, .blue = 0, .brightness = 5 } }, true);
	delay(5000);
}

#include <SPI.h>

#include "guitar_leds.hpp"

#define VERBOSE (false)

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

void loop() {
	Guitar_leds.set_all_notes("E", (apa102_led_t) { .led = { .red = 0xFF, .green = 0, .blue = 0, .brightness = guitar_leds::DEFAULT_BRIGHTNESS } }, true);
	Guitar_leds.set_leds();
#if VERBOSE
	Serial.println("Set All Es to red");
#endif
	delay(250);

	Guitar_leds.set_all_notes("A", (apa102_led_t) { .led = { .red = 0xFF, .green = 0, .blue = 0, .brightness = guitar_leds::DEFAULT_BRIGHTNESS } }, false);
	Guitar_leds.set_leds();
#if VERBOSE
	Serial.println("Set All As to red");
#endif
	delay(250);

	Guitar_leds.set_all_notes("D", (apa102_led_t) { .led = { .red = 0xFF, .green = 0, .blue = 0, .brightness = guitar_leds::DEFAULT_BRIGHTNESS } }, false);
	Guitar_leds.set_leds();
#if VERBOSE
	Serial.println("Set All Ds to red");
#endif
	delay(250);

	Guitar_leds.set_all_notes("G", (apa102_led_t) { .led = { .red = 0, .green = 0, .blue = 0xFF, .brightness = guitar_leds::DEFAULT_BRIGHTNESS } }, true);
	Guitar_leds.set_leds();
#if VERBOSE
	Serial.println("Set only Es to blue");
#endif
	delay(250);

	Guitar_leds.set_all_notes("B", (apa102_led_t) { .led = { .red = 0, .green = 0, .blue = 0xFF, .brightness = guitar_leds::DEFAULT_BRIGHTNESS } }, true);
	Guitar_leds.set_leds();
#if VERBOSE
	Serial.println("Set only As to blue");
#endif
	delay(250);

	Guitar_leds.set_all_notes("E", (apa102_led_t) { .led = { .red = 0, .green = 0, .blue = 0xFF, .brightness = guitar_leds::DEFAULT_BRIGHTNESS } }, true);
	Guitar_leds.set_leds();
#if VERBOSE
	Serial.println("Set only Ds to blue");
#endif
	delay(250);
}

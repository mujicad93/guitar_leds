#include <SPI.h>

#include "guitar_leds.hpp"

#define VERBOSE (false)

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
#if VERBOSE
	Serial.begin(115200);
	Serial.println("Start");
#endif

	p_apa102 = new apa102(init_apa102_comm, SPI.transfer);
	p_guitar_leds = new guitar_leds(STARTING_FREQ, STARTING_NOTES);

#if VERBOSE
	Serial.println("Initialized");
#endif

	delay(5000);

#if VERBOSE
	Serial.println("Entering Loop");
#endif
}

void loop() {
	p_guitar_leds->set_all_notes("E", (apa102_led_t) { .led = { .red = 0xFF, .green = 0, .blue = 0, .brightness = 5 } }, true);
	p_apa102->set_leds(&p_guitar_leds->led[0][0], sizeof(guitar_leds::led));
#if VERBOSE
	Serial.println("Set All Es to red");
#endif
	delay(1000);

	p_guitar_leds->set_all_notes("A", (apa102_led_t) { .led = { .red = 0xFF, .green = 0, .blue = 0, .brightness = 5 } }, false);
	p_apa102->set_leds(&p_guitar_leds->led[0][0], sizeof(guitar_leds::led));
#if VERBOSE
	Serial.println("Set All As to red");
#endif
	delay(1000);

	p_guitar_leds->set_all_notes("D", (apa102_led_t) { .led = { .red = 0xFF, .green = 0, .blue = 0, .brightness = 5 } }, false);
	p_apa102->set_leds(&p_guitar_leds->led[0][0], sizeof(guitar_leds::led));
#if VERBOSE
	Serial.println("Set All Ds to red");
#endif
	delay(1000);

	p_guitar_leds->set_all_notes("E", (apa102_led_t) { .led = { .red = 0, .green = 0, .blue = 0xFF, .brightness = 5 } }, true);
	p_apa102->set_leds(&p_guitar_leds->led[0][0], sizeof(guitar_leds::led));
#if VERBOSE
	Serial.println("Set only Es to blue");
#endif
	delay(1000);

	p_guitar_leds->set_all_notes("A", (apa102_led_t) { .led = { .red = 0, .green = 0, .blue = 0xFF, .brightness = 5 } }, true);
	p_apa102->set_leds(&p_guitar_leds->led[0][0], sizeof(guitar_leds::led));
#if VERBOSE
	Serial.println("Set only As to blue");
#endif
	delay(1000);

	p_guitar_leds->set_all_notes("D", (apa102_led_t) { .led = { .red = 0, .green = 0, .blue = 0xFF, .brightness = 5 } }, true);
	p_apa102->set_leds(&p_guitar_leds->led[0][0], sizeof(guitar_leds::led));
#if VERBOSE
	Serial.println("Set only Ds to blue");
#endif
	delay(1000);
}

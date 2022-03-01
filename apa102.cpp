#include "apa102.hpp"

apa102::apa102(void(*init_comm)(void), void(*send_bytes)(void* val, size_t len))
{
	init_comm();

	this->send_bytes = send_bytes;
}

void apa102::set_leds(apa102_led_t* const led_value, size_t num_leds)
{
	uint32_t word;
	word = START_FRAME;
	send_bytes((uint8_t*)&word, sizeof(START_FRAME));

	for (int led_idx = 0; led_idx < num_leds; led_idx++)
	{
		uint8_t brightness = (~BRIGHTNESS_MASK | (led_value[led_idx].led.brightness & BRIGHTNESS_MASK));
		send_bytes((uint8_t*)&brightness, 1);
		send_bytes((uint8_t*)&led_value[led_idx].led.blue, 1);
		send_bytes((uint8_t*)&led_value[led_idx].led.green, 1);
		send_bytes((uint8_t*)&led_value[led_idx].led.red, 1);
	}

	word = END_FRAME;
	send_bytes((uint8_t*)&word, sizeof(END_FRAME));

}
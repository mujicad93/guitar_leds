#include "apa102.hpp"

apa102::apa102(void(*init_comm)(void), void(*send_bytes)(void* val, size_t len))
{
	init_comm();

	this->send_bytes = send_bytes;
}

void apa102::set_leds(apa102_led_t* const led_value, size_t num_leds)
{
	send_bytes((uint8_t*)&apa102::START_FRAME, sizeof(apa102::START_FRAME));

	for (int led_idx = 0; led_idx < num_leds; led_idx++)
	{
		uint8_t brightness = (~apa102::BRIGHTNESS_MASK | (led_value[led_idx].led.brightness & apa102::BRIGHTNESS_MASK));
		send_bytes((uint8_t*)&brightness, 1);
		send_bytes((uint8_t*)&led_value[led_idx].led.blue, 1);
		send_bytes((uint8_t*)&led_value[led_idx].led.green, 1);
		send_bytes((uint8_t*)&led_value[led_idx].led.red, 1);
	}

	send_bytes((uint8_t*)&apa102::END_FRAME, sizeof(apa102::END_FRAME));

}
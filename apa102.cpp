#include "apa102.hpp"

apa102::apa102(void(*init_comm)(void), void(*send_bytes)(uint8_t* val, size_t len));
{
	init_comm();

	this.send_bytes = send_bytes;
}

void apa102::set_leds(apa102_led_t* const led_value, uint32_t num_leds)
{
	send_bytes((char*)&apa102::START_FRAME, sizeof(apa102::START_FRAME));

	for (int led_idx = 0; led_idx < num_leds; led_idx++)
	{
		send_bytes((~apa102::BRIGHTNESS_MASK | (led_value[led_idx].brighthness & apa102::BRIGHTNESS_MASK)), 1);
		send_bytes(led_value[led_idx].blue, 1);
		send_bytes(led_value[led_idx].green, 1);
		send_bytes(led_value[led_idx].red, 1);
	}

	send_bytes((char*)&apa102::END_FRAME, sizeof(apa102::END_FRAME));

}
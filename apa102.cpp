#include "apa102.hpp"

apa102::apa102(void(*send_bytes(uint8_t*, size_t len)))
{
	init_apa102_comm();
}

void apa102::set_leds(apa102_led_t* const led_value, uint32_t num_leds)
{
	this.send_bytes((char*)&apa102::START_FRAME, sizeof(apa102::START_FRAME));

	for (int led_idx = 0; led_idx < num_leds; led_idx++)
	{
		this.send_bytes(~apa102::BRIGHTNESS_MASK | (led_value[led_idx].brighthness & apa102::BRIGHTNESS_MASK));
		this.send_bytes(led_value[led_idx].blue);
		this.send_bytes(led_value[led_idx].green);
		this.send_bytes(led_value[led_idx].red);
	}

	this.send_bytes((char*)&apa102::END_FRAME, sizeof(apa102::END_FRAME));

}
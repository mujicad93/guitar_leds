#include "apa102.hpp"

void apa102::init(void(*init_comm)(void), void(*send_bytes_in)(void* val, size_t len))
{
	init_comm();
	send_bytes = send_bytes_in;
}

void apa102::set_leds(apa102_led_t* const led_value, size_t num_leds)
{
	uint32_t word;
	word = START_FRAME;
	send_bytes((uint8_t*)&word, sizeof(START_FRAME));

	for (int led_idx = 0; led_idx < num_leds; led_idx++)
	{
		uint8_t color = (~BRIGHTNESS_MASK | (led_value[led_idx].led.brightness & BRIGHTNESS_MASK));
		send_bytes((uint8_t*)&color, 1);
		color = led_value[led_idx].led.blue;
		send_bytes((uint8_t*)&color, 1);
		color = led_value[led_idx].led.green;
		send_bytes((uint8_t*)&color, 1);
		color = led_value[led_idx].led.red;
		send_bytes((uint8_t*)&color, 1);
	}

	word = END_FRAME;
	send_bytes((uint8_t*)&word, sizeof(END_FRAME));

}
#ifndef __APA102__H
#define __APA102__H

#include <stdint.h>
#include <stddef.h>

typedef union {
	uint32_t raw_value;
	char bytes[4];
	struct {
		uint8_t red;
		uint8_t green;
		uint8_t blue;
		uint8_t brightness;
	} led;
} apa102_led_t;

class apa102
{
public:
	const static uint32_t START_FRAME = 0x00000000;
	const static uint32_t END_FRAME = 0xFFFFFFFF;
	const static uint8_t  BRIGHTNESS_MASK = 0x1F;

	/*
	 * @brief Initialize APA102 communication (user must provide init function and send_bytes function)
	 */
	void init(void(*init_comm)(void), void(*send_bytes)(void* val, size_t len));

	/*
	* @brief Set LED values
	*/
	void set_leds(apa102_led_t* const rgb_value, size_t num_rgb_leds);

	/*
	 * @brief Send bytes through APA102 communication bus (implementation provided by user)
	 */
	void (*send_bytes)(void* val, size_t len);
};

#endif

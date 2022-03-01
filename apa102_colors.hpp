#ifndef __APA102_COLORS__H
#define __APA102_COLORS__H

#include "apa102.hpp"

#define MAX_BRIGHT (0xFF)
#define BRIGHT (5)
#define DIM (1)

#define RED(x) ((apa102_led_t)    {.led = {.red = 0xFF, .green = 0,    .blue = 0,    .brightness=(x)}})
#define BLUE(x) ((apa102_led_t)   {.led = {.red = 0,    .green = 0,    .blue = 0xFF, .brightness=(x)}})
#define GREEN(x) ((apa102_led_t)  {.led = {.red = 0,    .green = 0xFF, .blue = 0,    .brightness=(x)}})
#define PURPLE(x) ((apa102_led_t) {.led = {.red = 0xFF, .green = 0,    .blue = 0xFF, .brightness=(x)}})
#define TEAL(x) ((apa102_led_t)   {.led = {.red = 0,    .green = 0xFF, .blue = 0xFF, .brightness=(x)}})
#define YELLOW(x) ((apa102_led_t) {.led = {.red = 0xFF, .green = 0xFF, .blue = 0,    .brightness=(x)}})
#define WHITE(x) ((apa102_led_t)  {.led = {.red = 0xFF, .green = 0xFF, .blue = 0xFF, .brightness=(x)}})

#endif

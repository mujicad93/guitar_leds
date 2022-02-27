#include <SPI.h>

#define NUM_FRETS (4)
#define NUM_STRINGS (6)

enum rgb{
  RED_IDX = 0,
  GREEN_IDX,
  BLUE_IDX,
  NUM_COLORS
};



// Constants according to SK9822 datasheet
const uint32_t ONE_WIRE__START_FRAME = 0;
const uint32_t ONE_WIRE__END_FRAME = 0xFFFFFFFF;
const uint8_t BRIGHTNESS_MASK = 0x1F;

// 5 bit brightness setting
const uint8_t BRIGHTNESS = 0xF;

void setup() {
  SPI.begin();
  SPI.beginTransaction(SPISettings(16000000, MSBFIRST, SPI_MODE0));

  memset(led, 0, sizeof(led));
}

static uint8_t current_color = RED_IDX;
static uint8_t current_fret = 0;
static uint8_t current_string = 0;

void set_all_leds(void)
{
  SPI.transfer((char *) &ONE_WIRE__START_FRAME, sizeof(ONE_WIRE__START_FRAME));
  for(int fret_idx = 0; fret_idx < NUM_FRETS; fret_idx++)
  {
    for(int string_idx = 0; string_idx < NUM_STRINGS; string_idx++)
    {
      SPI.transfer(~BRIGHTNESS_MASK | (BRIGHTNESS & BRIGHTNESS_MASK));
      SPI.transfer(led[fret_idx][string_idx][BLUE_IDX]);
      SPI.transfer(led[fret_idx][string_idx][GREEN_IDX]);
      SPI.transfer(led[fret_idx][string_idx][RED_IDX]);
    }
  }
  SPI.transfer((char *) &ONE_WIRE__END_FRAME, sizeof(ONE_WIRE__END_FRAME));
}

void loop() {
  set_all_leds();

  for(int fret_idx = 0; fret_idx < NUM_FRETS; fret_idx++)
  {
    for(int string_idx = 0; string_idx < NUM_STRINGS; string_idx++)
    {
      led[fret_idx][string_idx][current_color]++;
    }
  }
//  led[current_fret][current_string][current_color]++;
  
  if(led[current_fret][current_string][current_color] == 0)
  {
    current_color++;
    if(current_color >= NUM_COLORS)
    {
      current_color = RED_IDX;
      current_string++;
      if(current_string >= NUM_STRINGS)
      {
        current_string = 0;
        current_fret++;

        if(current_fret >= NUM_FRETS)
        {
          current_fret = 0;
        }
      }
    }
  }
  
  //delayMicroseconds(1000);
}

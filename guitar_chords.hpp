#ifndef __GUITAR_CHORDS__H
#define __GUITAR_CHORDS__H

#include "guitar_leds.hpp"

size_t G_MAJ_CHORD[guitar_leds::NUM_STRINGS] = { 3, 2, 0, 0, 3, 3 };
size_t A_MAJ_CHORD[guitar_leds::NUM_STRINGS] = { guitar_leds::NUM_FRETS, guitar_leds::NUM_FRETS, 2, 2, 2, 0 };
size_t A_MIN_CHORD[guitar_leds::NUM_STRINGS] = { guitar_leds::NUM_FRETS, guitar_leds::NUM_FRETS, 2, 2, 1, 0 };
size_t D_MAJ_CHORD[guitar_leds::NUM_STRINGS] = { guitar_leds::NUM_FRETS, guitar_leds::NUM_FRETS, 0, 2, 3, 2 };

#endif

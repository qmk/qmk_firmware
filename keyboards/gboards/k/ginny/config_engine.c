#include "g/engine.h"
#include "config_engine.h"

// Ginni handling for Left/Right chords
C_SIZE process_engine_post(C_SIZE cur_chord, uint16_t keycode, keyrecord_t *record) { 
  if(!record->event.pressed) return cur_chord;
  // We only care about the first press for setting these bits
  if (bitpop_v(cur_chord) != 1) return cur_chord;

  // Left side chords
  if ((cur_chord & (AN | AI | AO | AP)) != 0)  return (cur_chord | RGT);
  return cur_chord;
}

C_SIZE process_chord_getnext(C_SIZE cur_chord) { 
  // Left side chords
  if ((cur_chord & RGT) == RGT) {
      return (cur_chord ^ RGT);
  }
  return 0;
}

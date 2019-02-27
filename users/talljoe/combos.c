#include "talljoe.h"

const uint16_t PROGMEM copypaste_combo[] = {KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM lock_combo[] = {KC_A, KC_S, KC_D, KC_F, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [CB_COPYPASTE] = COMBO_ACTION(copypaste_combo),
  [CB_LOCK] = COMBO_ACTION(lock_combo),
};

void process_combo_event(uint8_t combo_index, bool pressed) {
  switch(combo_index) {
    case CB_COPYPASTE:
      if (pressed) {
        macro_copy();
      } else {
        macro_paste();
      }
      break;
    case CB_LOCK:
    if(pressed) {
      macro_lock();
    }
  }
}

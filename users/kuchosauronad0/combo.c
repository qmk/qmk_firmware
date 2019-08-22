#include "combo.h"

void process_combo_event(uint8_t combo_index, bool pressed){
  switch(combo_index) {
    case CV_COPY:
      if (pressed) {
        tap_code16(LCTL(KC_C));
      }
      break;
    case XC_CUT:
      if (pressed) {
        tap_code16(LCTL(KC_X));
      }
      break;
    case ZV_PASTE:
      if (pressed) {
        tap_code16(LCTL(KC_V));
      }
      break;
    case QP_SLEEP:
      if (pressed) {
        tap_code16(KC_SLEP);
      }
      break;
  }
}

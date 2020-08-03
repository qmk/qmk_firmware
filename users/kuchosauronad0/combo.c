#include "combo.h"

void process_combo_event(uint8_t combo_index, bool pressed){
  switch(combo_index) {
    case ZV_COPY:
      if (pressed) {
        tap_code16(LCTL(KC_C));
      }
      break;
    case XV_CUT:
      if (pressed) {
        tap_code16(LCTL(KC_X));
      }
      break;

    case CV_PASTE:
      if (pressed) {
        tap_code16(LCTL(KC_V));
      }
      break;
    case QP_SLEEP:
      if (pressed) {
        tap_code16(KC_SYSTEM_SLEEP);
      }
      break;
  }
}

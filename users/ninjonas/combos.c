#include "ninjonas.h"

#ifdef COMBO_ENABLE
enum combo_events {
  EQ_QUIT,
  RW_CLOSE,
  QT_TAB,
  ZC_COPY,
  XV_PASTE
};

const uint16_t PROGMEM quit_combo[] = {KC_E, KC_Q, COMBO_END};
const uint16_t PROGMEM close_combo[] = {KC_R, KC_W, COMBO_END};
const uint16_t PROGMEM tab_combo[] = {KC_Q, KC_T, COMBO_END};
const uint16_t PROGMEM copy_combo[] = {KC_Z, KC_C, COMBO_END};
const uint16_t PROGMEM paste_combo[] = {KC_X, KC_V, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [EQ_QUIT] = COMBO_ACTION(quit_combo),
  [RW_CLOSE] = COMBO_ACTION(close_combo),
  [QT_TAB] = COMBO_ACTION(tab_combo),
  [ZC_COPY] = COMBO_ACTION(copy_combo),
  [XV_PASTE] = COMBO_ACTION(paste_combo),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
    case EQ_QUIT:
      if (pressed) {
        tap_code16(LGUI(KC_Q));
      }
      break;
    case RW_CLOSE:
      if (pressed) {
        tap_code16(LGUI(KC_W));
      }
      break;
    case QT_TAB:
      if (pressed) {
        tap_code16(LGUI(KC_T));
      }
      break;
    case ZC_COPY:
      if (pressed) {
        tap_code16(LGUI(KC_C));
      }
      break;
    case XV_PASTE:
      if (pressed) {
        tap_code16(LGUI(KC_V));
      }
      break;
  }
}
#endif
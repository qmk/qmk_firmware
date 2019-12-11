#include "issmirnov.h"

enum combo_events {
  JK_ESC,
  DF_CLN,
  SD_SLASH,
  XC_COPY,
  XV_PASTE
};


const uint16_t PROGMEM jk_combo[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM df_combo[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM sd_combo[] = {KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM copy_combo[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM paste_combo[] = {KC_X, KC_V, COMBO_END};


// BE SURE TO UPDATE THE CONFIG.H "COMBO_COUNT" value when you add elements here!
combo_t key_combos[COMBO_COUNT] = {
  COMBO(jk_combo, KC_ESC),
  COMBO(df_combo, KC_COLON),
  COMBO(sd_combo, KC_SLASH),
  [XC_COPY] = COMBO_ACTION(copy_combo),
  [XV_PASTE] = COMBO_ACTION(paste_combo),
};


void process_combo_event(uint8_t combo_index, bool pressed) {
  switch(combo_index) {
    case XC_COPY:
      if (pressed) {
        tap_code16(LCTL(KC_C));
      }
      break;

    case XV_PASTE:
      if (pressed) {
        tap_code16(LCTL(KC_V));
      }
      break;
  }
}

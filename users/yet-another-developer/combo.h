#pragma once
#include "quantum.h"
enum combo_events {
  ZV_COPY,
  XV_CUT,
  CV_PASTE,
  QP_SLEEP
};

const uint16_t PROGMEM copy_combo[] = {KC_Z, KC_V, COMBO_END};
const uint16_t PROGMEM cut_combo[] = {KC_X, KC_V, COMBO_END};
const uint16_t PROGMEM paste_combo[] = {KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM sleep_combo[] = {KC_Q, KC_P, COMBO_END};

combo_t key_combos[] = {
  [ZV_COPY] = COMBO_ACTION(copy_combo),
  [XV_CUT] = COMBO_ACTION(cut_combo),
  [CV_PASTE] = COMBO_ACTION(paste_combo),
  [QP_SLEEP] = COMBO_ACTION(sleep_combo),
};

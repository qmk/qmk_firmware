#pragma once
#include "quantum.h"

enum combo_events {
  CV_COPY,
  XC_CUT,
  ZV_PASTE,
  QP_SLEEP
};

const uint16_t PROGMEM copy_combo[] = {KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM cut_combo[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM paste_combo[] = {KC_Z, KC_V, COMBO_END};
const uint16_t PROGMEM sleep_combo[] = {KC_Q, KC_P, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [CV_COPY] = COMBO_ACTION(copy_combo),
  [XC_CUT] = COMBO_ACTION(cut_combo),
  [ZV_PASTE] = COMBO_ACTION(paste_combo),
  [QP_SLEEP] = COMBO_ACTION(sleep_combo),
};


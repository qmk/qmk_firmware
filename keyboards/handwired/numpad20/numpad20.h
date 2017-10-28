#ifndef NUMPAD20_H
#define NUMPAD20_H

#include "quantum.h"

#define COMPACT_KEYMAP( \
    K00, K01, K02, K03, \
    K10, K11, K12, K13, \
    K20, K21, K22, K23, \
    K30, K31, K32, K33, \
    K40, K41, K42, K43 \
    ) { \
  { KC_##K00, KC_##K01, KC_##K02, KC_##K03 },  \
  { KC_##K10, KC_##K11, KC_##K12, KC_##K13 },  \
  { KC_##K20, KC_##K21, KC_##K22, KC_##K23 },  \
  { KC_##K30, KC_##K31, KC_##K32, KC_##K33 },  \
  { KC_##K40, KC_##K41, KC_##K42, KC_##K43 }   \
}

#endif
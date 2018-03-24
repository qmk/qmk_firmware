#ifndef SIXBALL_H
#define SIXBALL_H

#include "quantum.h"

#define KEYMAP( \
      k01, k02, k03, \
      k04, k05, k06 \
) \
{ \
    { k02, k03, k06, k05, k04, k01 } \
} 

#define KC_KEYMAP(k01, k02, k03, k04, k05, k06) KEYMAP(KC_##k01, KC_##k02, KC_##k03, KC_##k04, KC_##k05, KC_##k06)

#endif

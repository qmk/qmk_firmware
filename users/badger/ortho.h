#ifndef BADGER_ORTHO_H
#define BADGER_ORTHO_H

#include "badger.h"

enum OrthoLayers {
  _RAISE = _CONFIG + 1,
  _LOWER
};

enum OrthoKeys {
  KC_MAC1 = SAFE_RANGE,
  KC_MAC2,
  KC_LYRC,
  KC_FIRST
};

#define P_ADJ LT(_ADJUST, KC_BSPC)
#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

#endif
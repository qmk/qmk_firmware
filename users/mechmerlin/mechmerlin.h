#pragma once

#include "quantum.h"

enum userspace_layers {
  _BL = 0, // Base Layer
  _FL,     // Function Layer
  _AL      // Arrow Layer
};

// Enum of custom keycodes defined in process_record_user
enum keycodes {
    KC_FNX, // Hold for FN layer, tap to toggle ARROWS layer. 
};

// Custom #defined keycodes
#define KC_CTCP MT(KC_LCTL, KC_CAPS)

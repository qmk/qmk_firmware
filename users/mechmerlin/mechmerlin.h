#pragma once

#include "quantum.h"

enum userspace_layers {
  _BL = 0, // Base Layer
  _FL,     // Function Layer
  _AL,     // Arrow Layer
  _CL      // Control Layer
};

// Enum of custom keycodes defined in process_record_user
enum keycodes {
    KC_FNX, // Hold for FN layer, tap to toggle ARROWS layer.
    KC_MAC, // Text macro.
};

// Custom #defined keycodes
#define KC_CTCP CTL_T(KC_CAPS)

#pragma once

#include "quantum.h"
#include "keymap_german.h"

enum userspace_layers {
  _DEADKEY = 14,            // Change if more than 16 layers are required
  _NAV
};

enum userspace_custom_keycodes {
  CU_GAME = SAFE_RANGE,     // Toggle game mode on/off
  CU_NAV,                   // NAV | ESC
  KC_P00,                   // Numpad double zero

  #ifdef GERMAN_ENABLE
  CU_LSFT,                  // LSFT | (
  CU_RSFT,                  // LSFT | )
  CU_COMM,                  // , | <
  CU_DOT,                   // . | >
  CU_SLSH,                  // / | ?
  CU_SCLN,                  // ; | :
  CU_QUOT,                  // ' | Enable deadkey layer
  CU_GRV,                   // ` | ~
  CU_CIRC,                  // ^
  CU_3,                     // 3 | #
  CU_6,                     // 6 | ^
  CU_7,                     // 7 | &
  CU_8,                     // 8 | *
  CU_9,                     // 9 | (
  CU_0,                     // 0 | )
  CU_EQL,                   // = | +
  CU_LBRC,                  // [ | {
  CU_RBRC,                  // ] | }
  CU_BSLS,                  // \ | |
  CU_Z,                     // Z | Y in conjunction with ctrl
  CU_Y,                     // Y | Z in conjunction wiht ctrl
  CU_ESCT,                  // Toggle escape of grv and circ on/off
  // Deadkey Layer
  CU_AE,                    // Ä
  CU_OE,                    // Ö
  CU_UE,                    // Ü
  CU_SS,                    // ß
  CU_DDQ,                   // "
  CU_ED,                    // Escape deadkey layer
  #endif

  #ifdef RGBLIGHT_ENABLE
  CU_RGBV,                  // Cycle through RGB brightness
  #endif

  NEW_SAFE_RANGE            // Use for keymap specific keycodes
};

#ifdef GERMAN_ENABLE
extern bool lshift;
extern bool rshift;
extern bool lshiftp;
extern bool rshiftp;
extern uint16_t lshift_timer;
extern uint16_t rshift_timer;

extern uint8_t prev_indx;
extern uint16_t prev_kcs[6];
void add_to_prev(uint16_t kc);
void unreg_prev(void);

extern bool esct;
#endif

extern bool navesc;
extern uint16_t navesc_timer;

extern bool game;

void timer_timeout(void);

bool process_record_keymap(uint16_t keycode, keyrecord_t *record);

#define CTRLX LCTL(KC_X)
#define CTRLC LCTL(KC_C)
#define CTRLV LCTL(KC_V)

#define GUIU LGUI(KC_UP)
#define GUID LGUI(KC_DOWN)
#define GUIL LGUI(KC_LEFT)
#define GUIR RGUI(KC_RIGHT)

/*
Templates for Keys, with custom shifted and non shifted Characters
*/

// Normal shift status
#define SHIFT_NORM(kc1, kc2) \
if (record->event.pressed) { \
  timer_timeout(); \
  if (lshift || rshift) { \
    register_code(KC_LSFT); \
    unregister_code(kc2); \
    register_code(kc2); \
    add_to_prev(kc2); \
  } else { \
    unregister_code(KC_LSFT); \
    unregister_code(kc1); \
    register_code(kc1); \
  } \
} else { \
  unregister_code(kc1); \
  unregister_code(kc2); \
} \
return false;

// Inverted shift status
#define SHIFT_SWITCH(kc1, kc2) \
if (record->event.pressed) { \
  timer_timeout(); \
  if (lshift || rshift) { \
    unregister_code(KC_LSFT); \
    unregister_code(kc2); \
    register_code(kc2); \
    add_to_prev(kc2); \
  } else { \
    register_code(KC_LSFT); \
    unregister_code(kc1); \
    register_code(kc1); \
    add_to_prev(kc1); \
  } \
} else { \
  unregister_code(kc1); \
  unregister_code(kc2); \
  unreg_prev(); \
  if (lshift || rshift) \
    register_code(KC_LSFT); \
  else \
    unregister_code(KC_LSFT); \
} \
return false;

// Always shifted
#define SHIFT_ALL(kc1, kc2) \
if (record->event.pressed) { \
  timer_timeout(); \
  register_code(KC_LSFT); \
  if (lshift || rshift) { \
    unregister_code(kc2); \
    register_code(kc2); \
    add_to_prev(kc2); \
  } else { \
    unregister_code(kc1); \
    register_code(kc1); \
    add_to_prev(kc1); \
  } \
} else { \
  unregister_code(kc1); \
  unregister_code(kc2); \
  unreg_prev(); \
  if (lshift || rshift) \
    register_code(KC_LSFT); \
  else \
    unregister_code(KC_LSFT); \
} \
return false;

// Never shifted
#define SHIFT_NO(kc1, kc2) \
if (record->event.pressed) { \
  timer_timeout(); \
  unregister_code(KC_LSFT); \
  if (lshift || rshift) { \
    unregister_code(kc2); \
    register_code(kc2); \
    add_to_prev(kc2); \
  } else { \
    unregister_code(kc1); \
    register_code(kc1); \
  } \
} else { \
  unregister_code(kc1); \
  unregister_code(kc2); \
  unreg_prev(); \
  if (lshift || rshift) \
    register_code(KC_LSFT); \
  else \
    unregister_code(KC_LSFT); \
} \
return false;

// Always AltGr
#define SHIFT_ALGR(kc1, kc2) \
if (record->event.pressed) { \
  timer_timeout(); \
  unregister_code(KC_LSFT); \
  register_code(DE_ALGR); \
  if (lshift || rshift) { \
    unregister_code(kc2); \
    register_code(kc2); \
    unregister_code(kc2); \
    register_code(KC_LSFT); \
  } else { \
    unregister_code(kc1); \
    register_code(kc1); \
    unregister_code(kc1); \
  } \
  unregister_code(DE_ALGR); \
} \
return false;

// Different keycode when Ctrl is pressed
#define CTRL(kc1, kc2) \
if(record->event.pressed) { \
  timer_timeout(); \
  if (lshift || rshift) \
    register_code(KC_LSFT); \
  else \
    unregister_code(KC_LSFT); \
  if (keyboard_report->mods & (MOD_BIT(KC_LCTL) | MOD_BIT(KC_RCTL))){ \
    register_code(kc2); \
  } else { \
    register_code(kc1); \
  } \
} else { \
    unregister_code(kc1); \
    unregister_code(kc2); \
} \
return false;

// Template for keys on deadkey layer (mostly Umlaute)
#define UML(kc) \
if(record->event.pressed) { \
  timer_timeout(); \
  if (lshift || rshift) \
    register_code(KC_LSFT); \
  else \
    unregister_code(KC_LSFT); \
  register_code(kc); \
  unregister_code(kc); \
  layer_off(_DEADKEY); \
} \
return false;

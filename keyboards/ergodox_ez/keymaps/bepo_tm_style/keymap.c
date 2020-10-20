// An Ergodox EZ keymap meant to be used with a bépo layout (FR ergonomic
// layout, dvorak style). The overall design is slightly inspired by the
// TypeMatrix keyboard. Switching between a TypeMatrix and an Ergodox with this
// layout should be relatively easy.
//
// See the README.md file for an image of this keymap.

#include QMK_KEYBOARD_H
#include "keymap_bepo.h"

// The layers that we are defining for this keyboards.
#define BASE 0
#define FN 1
#define MOUSE 2
#define NUMS 3
#define SWAP 4
#define SYSLEDS 5

// The Tap Dance identifiers, used in the TD keycode and tap_dance_actions array.
#define TAP_MACRO 0

// A 'transparent' key code (that falls back to the layers below it).
#define ___ KC_TRANSPARENT

// A 'blocking' key code. Does nothing but prevent falling back to another layer.
#define XXX KC_NO

// Some combined keys (one normal keycode when tapped and one modifier or layer
// toggle when held).
#define ESC_FN    LT(FN, KC_ESC)        // ESC key and FN layer toggle.
#define M_RSFT    MT(MOD_RSFT, BP_M)    // 'M' key and right shift modifier.
#define W_RCTL    MT(MOD_RCTL, BP_W)    // 'W' key and right control modifier.
#define SPC_RALT  MT(MOD_RALT, KC_SPC)  // SPACE key and right alt modifier.
#define PERC_FN    LT(FN, BP_PERC)      // '%' key and FN layer toggle.

// The most portable copy/paste keys (windows (mostly), linux, and some terminal emulators).
#define MK_CUT    LSFT(KC_DEL)  // shift + delete
#define MK_COPY   LCTL(KC_INS)  // ctrl + insert
#define MK_PASTE  LSFT(KC_INS)  // shift + insert

// The number of arrows that are sent by the fast arrow keys.
#define FAST_ARROW_TIME 10

// Custom keycodes
enum {
  // SAFE_RANGE must be used to tag the first element of the enum.
  COPY_ALL = SAFE_RANGE,  // CTRL + A and then ctrl + insert (copy)
  PASTE_LINK,  // CTRL + K (insert link) and then shift + insert (paste)
  FAST_UP,     // Send an up arrow FAST_ARROW_TIME times.
  FAST_DOWN,   // Send a down arrow FAST_ARROW_TIME times.
  CTRL_LEFT,   // Send Ctrl+left (move one word left).
  CTRL_RIGHT,  // Send Ctrl+right (move one word right).
  CTRL_B,      // Send Ctrl+B (bold).
  CTRL_U,      // Send Ctrl+B (underline).
  CTRL_I,      // Send Ctrl+B (italic).
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // Layer 0: basic keys.
  [BASE] = LAYOUT_ergodox(
    /* left hand */
    BP_DLR,   BP_DQUO, BP_LDAQ, BP_RDAQ, BP_LPRN, BP_RPRN, KC_DEL,
    KC_TAB,   BP_B,    BP_EACU, BP_P,    BP_O,    BP_EGRV, KC_BSPC,
    KC_LSFT,  BP_A,    BP_U,    BP_I,    BP_E,    BP_COMM,
    KC_LCTL,  BP_AGRV, BP_Y,    BP_X,    BP_DOT,  BP_K,    KC_ENT,
    ESC_FN,   BP_ECIR, KC_LGUI, KC_LALT, SPC_RALT,
                                                          TT(SWAP), KC_VOLU,
                                                                    KC_MUTE,
                                                  TT(FN), TT(NUMS), KC_VOLD,
    /* right hand */
        KC_DEL,  BP_AT,   BP_PLUS,  BP_MINS, BP_SLSH,     BP_ASTR, BP_EQL,
        KC_BSPC, BP_DCIR, BP_V,     BP_D,    BP_L,        BP_J,    BP_Z,
                 BP_C,    BP_T,     BP_S,    BP_R,        BP_N,    M_RSFT,
        KC_ENT,  BP_QUOT, BP_Q,     BP_G,    BP_H,        BP_F,    W_RCTL,
                          SPC_RALT, KC_LALT, TT(SYSLEDS), BP_CCED, PERC_FN,
    KC_LEFT, KC_RIGHT,
    KC_UP,
    KC_DOWN, TD(TAP_MACRO), TT(MOUSE)),

  // Layer 1: function and media keys.
  [FN] = LAYOUT_ergodox(
    /* left hand */
    KC_SLEP, KC_F1,      KC_F2,  KC_F3,   KC_F4,    KC_F5,    ___,
    ___,     CTRL_B,     ___,    ___,     ___,      ___,      ___,
    ___,     COPY_ALL,   CTRL_U, CTRL_I,  ___,      KC_LSFT,
    ___,     PASTE_LINK, MK_CUT, MK_COPY, MK_PASTE, KC_LCTL, ___,
    ___,     ___,        ___,    ___,     ___,
                                                         ___, KC_MPRV,
                                                              KC_MPLY,
                                                 ___,    ___, KC_MNXT,
    /* right hand */
        ___, KC_F6,     KC_F7,     KC_F8,   KC_F9,      KC_F10,  KC_F11,
        ___, FAST_UP,   KC_HOME,   KC_UP,   KC_END,     KC_PGUP, KC_F12,
             FAST_DOWN, KC_LEFT,   KC_DOWN, KC_RIGHT,   KC_PGDN, ___,
        ___, ___,       CTRL_LEFT, ___,     CTRL_RIGHT, ___,     ___,
                        ___,       ___,     ___,        ___,     ___,
    KC_HOME, KC_END,
    KC_PGUP,
    KC_PGDN, ___,       ___),
    // Note that any change to the FN layer above must be added to
    // the MOUSE layer below (except for the arrow keys).

  // Layer 2: Mouse control.
  [MOUSE] = LAYOUT_ergodox(
    /* left hand */
    KC_SLEP, KC_F1,      KC_F2,   KC_F3,   KC_F4,    KC_F5,    ___,
    ___,     ___,        KC_BTN4, KC_MS_U, KC_BTN5,  ___,      ___,
    ___,     COPY_ALL,   KC_MS_L, KC_MS_D, KC_MS_R,  KC_LSFT,
    ___,     PASTE_LINK, MK_CUT,  MK_COPY, MK_PASTE, KC_LCTL, ___,
    ___,     ___,        ___,     ___,     ___,
                                                       ___, KC_MPRV,
                                                            KC_MPLY,
                                                  ___, ___, KC_MNXT,
    /* right hand */
         ___, KC_F6, KC_F7,   KC_F8,   KC_F9,   KC_F10, KC_F11,
         ___, ___,   KC_WH_L, KC_WH_U, KC_WH_R, XXX,    KC_F12,
              ___,   KC_BTN1, KC_WH_D, KC_BTN2, KC_BTN3,    ___,
         ___, ___,   KC_ACL0, KC_ACL1, KC_ACL2, ___,    ___,
                     ___,     ___,     ___,     ___,    ___,
    ___, ___,
    ___,
    ___, ___, ___),

  // Layer 3: Numeric keypad and system keys.
  [NUMS] = LAYOUT_ergodox(
    /* left hand */
    KC_PSCR, KC_INS, KC_PAUS,    ___,     ___,      ___, ___,
    ___,     ___,    ___,        ___,     ___,      ___, ___,
    ___,     ___,    ___,        ___,     ___,      ___,
    ___,     ___,    MK_CUT,     MK_COPY, MK_PASTE, ___, ___,
    ___,     ___,    ___,        ___,     ___,
                                              ___, ___,
                                                   ___,
                                         ___, ___, ___,
    /* right hand */
         ___,     ___,     ___,   ___,   ___,     ___,     KC_NUM,
         ___,     KC_PEQL, KC_P7, KC_P8, KC_P9,   KC_PMNS, KC_SCRL,
                  KC_PCMM, KC_P4, KC_P5, KC_P6,   KC_PPLS, ___,
         KC_PENT, KC_P0,   KC_P1, KC_P2, KC_P3,   KC_PAST, ___,
                           ___,   ___,   ___,     KC_PSLS, ___,
    ___, ___,
    ___,
    ___, ___, ___),

  // Layer 4: hand swap, all keys are mirrored to the other side of the keyboard
  // except for the layer toggle itself (so there is no right arrow when this
  // layer is activated).
  [SWAP] = LAYOUT_ergodox(
    /* left hand */
    ___, ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___,
                             TT(SWAP), ___,
                                       ___,
                             ___, ___, ___,
    /* right hand */
         ___, ___, ___, ___, ___, ___, ___,
         ___, ___, ___, ___, ___, ___, ___,
              ___, ___, ___, ___, ___, ___,
         ___, ___, ___, ___, ___, ___, ___,
                   ___, ___, ___, ___, ___,
    ___, TT(SWAP),
    ___,
    ___, ___,      ___),

  // Layer 5: The LEDs are showing the "standard" caps/num/scroll lock indicator
  // instead of their default which shows the currently active layers (FN, NUMS,
  // and MOUSE in that order).
  [SYSLEDS] = LAYOUT_ergodox(
    /* left hand */
    ___, ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___,
                                  ___, ___,
                                       ___,
                             ___, ___, ___,
    /* right hand */
         ___, ___, ___, ___, ___,         ___, ___,
         ___, ___, ___, ___, ___,         ___, ___,
              ___, ___, ___, ___,         ___, ___,
         ___, ___, ___, ___, ___,         ___, ___,
                   ___, ___, TT(SYSLEDS), ___, ___,
    ___, ___,
    ___,
    ___, ___, ___),
};

// Whether the macro 1 is currently being recorded.
static bool is_macro1_recording = false;

// The current set of active layers (as a bitmask).
// There is a global 'layer_state' variable but it is set after the call
// to layer_state_set_user().
static layer_state_t current_layer_state = 0;
layer_state_t layer_state_set_user(layer_state_t state);

// Method called at the end of the tap dance on the TAP_MACRO key. That key is
// used to start recording a macro (double tap or more), to stop recording (any
// number of tap), or to play the recorded macro (1 tap).
void macro_tapdance_fn(tap_dance_state_t *state, void *user_data) {
  uint16_t keycode;
  keyrecord_t record;
  dprintf("macro_tap_dance_fn %d\n", state->count);
  if (is_macro1_recording) {
    keycode = DM_RSTP;
    is_macro1_recording = false;
    layer_state_set_user(current_layer_state);
  } else if (state->count == 1) {
    keycode = DM_PLY1;
  } else {
    keycode = DM_REC1;
    is_macro1_recording = true;
    layer_state_set_user(current_layer_state);
  }

  record.event.pressed = true;
  process_dynamic_macro(keycode, &record);
  record.event.pressed = false;
  process_dynamic_macro(keycode, &record);
}

// The definition of the tap dance actions:
tap_dance_action_t tap_dance_actions[] = {
  // This Tap dance plays the macro 1 on TAP and records it on double tap.
  [TAP_MACRO] = ACTION_TAP_DANCE_FN(macro_tapdance_fn),
};

// Runs for each key down or up event.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (keycode != TD(TAP_MACRO)) {
    // That key is processed by the macro_tapdance_fn. Not ignoring it here is
    // mostly a no-op except that it is recorded in the macros (and uses space).
    // We can't just return false when the key is a tap dance, because
    // process_record_user, is called before the tap dance processing (and
    // returning false would eat the tap dance).
    if (!process_dynamic_macro(keycode, record)) {
      return false;
    }
  }

  if (record->event.pressed) {
    switch(keycode) {
      case COPY_ALL:
        // A in QWERTY is also A in BÉPO (SEND_STRING assumes an QWERTY keymap)
        // There is no string representation of the insert key, so we need to use
        // the SS_UP/DOWN macro, instead of SS_LCTL(...).
        SEND_STRING(SS_LCTL("a") SS_DOWN(X_LCTL) SS_TAP(X_INSERT) SS_UP(X_LCTL) SS_TAP(X_RIGHT));
        return false;
      case PASTE_LINK:
        // B in QWERTY is K in BÉPO
        SEND_STRING(SS_LCTL("b") SS_DOWN(X_LSFT) SS_TAP(X_INSERT) SS_UP(X_LSFT) SS_TAP(X_ENTER));
        return false;
      case FAST_UP:
        for (int i = 0; i < FAST_ARROW_TIME; i++) {
          SEND_STRING(SS_TAP(X_UP));
        }
        return false;
      case FAST_DOWN:
        for (int i = 0; i < FAST_ARROW_TIME; i++) {
          SEND_STRING(SS_TAP(X_DOWN));
        }
        return false;
      case CTRL_B:
        SEND_STRING(SS_LCTL("q"));  // Ctrl+q (== Ctrl+b in bépo)
        return false;
      case CTRL_U:
        SEND_STRING(SS_LCTL("s"));  // Ctrl+s (== Ctrl+u in bépo)
        return false;
      case CTRL_I:
        SEND_STRING(SS_LCTL("d"));  // Ctrl+d (== Ctrl+i in bépo)
        return false;
      case CTRL_LEFT:
        register_code(KC_LCTL);
        register_code(KC_LEFT);
        return false;
      case CTRL_RIGHT:
        register_code(KC_LCTL);
        register_code(KC_RIGHT);
        return false;
    }
  } else {
    switch(keycode) {
      case CTRL_LEFT:
        unregister_code(KC_LEFT);
        unregister_code(KC_LCTL);
        return false;
      case CTRL_RIGHT:
        unregister_code(KC_RIGHT);
        unregister_code(KC_LCTL);
        return false;
    }
  }

  return true; // Let QMK send the enter press/release events
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

};

// The state of the LEDs requested by the system, as a bitmask.
static led_t sys_led_state = {0};

// Value to use to switch LEDs on. The default value of 255 is far too bright.
static const uint8_t max_led_value = 20;

// Whether the given layer (one of the constant defined at the top) is active.
#define LAYER_ON(layer) (current_layer_state & (1<<layer))

void led_1_on(void) {
  ergodox_right_led_1_on();
  ergodox_right_led_1_set(max_led_value);
}

void led_2_on(void) {
  ergodox_right_led_2_on();
  ergodox_right_led_2_set(max_led_value);
}

void led_3_on(void) {
  ergodox_right_led_3_on();
  ergodox_right_led_3_set(max_led_value);
}

void led_1_off(void) {
  ergodox_right_led_1_off();
}

void led_2_off(void) {
  ergodox_right_led_2_off();
}

void led_3_off(void) {
  ergodox_right_led_3_off();
}

// Called when the computer wants to change the state of the keyboard LEDs.
bool led_update_user(led_t led_state) {
  sys_led_state = led_state;
  if (LAYER_ON(SYSLEDS)) {
    if (sys_led_state.caps_lock) {
      led_1_on();
    } else {
      led_1_off();
    }
    if (sys_led_state.num_lock) {
      led_2_on();
    } else {
      led_2_off();
    }
    if (sys_led_state.scroll_lock) {
      led_3_on();
    } else {
      led_3_off();
    }
  }
  return false;
}

layer_state_t layer_state_set_user(layer_state_t state) {
  current_layer_state = state;
  swap_hands = LAYER_ON(SWAP);

  if (is_macro1_recording) {
    led_1_on();
    led_2_on();
    led_3_on();
    return state;
  }

  if (LAYER_ON(SYSLEDS)) {
    led_update_user(sys_led_state);
    return state;
  }

  if (LAYER_ON(FN)) {
    led_3_on();
  } else {
    led_3_off();
  }

  if (LAYER_ON(NUMS)) {
    led_2_on();
  } else {
    led_2_off();
  }

  if (LAYER_ON(MOUSE)) {
    led_1_on();
  } else {
    led_1_off();
  }

  return state;
};

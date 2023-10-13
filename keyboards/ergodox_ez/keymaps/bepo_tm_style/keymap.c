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
#define SYSLEDS 4
#define SWAP 5  // Should always be last (probably).

// The Tap Dance identifiers, used in the TD keycode and tap_dance_actions array.
#define TAP_MACRO 0
#define TAP_SWAP  1

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
#define PERC_FN   LT(FN, BP_PERC)      // '%' key and FN layer toggle.

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
  SWAP_CHARS,  // Swap the last two chars.
  COPY_WORD,   // Copy the current word
  CTRL_B,      // Send Ctrl+B (bold).
  CTRL_U,      // Send Ctrl+B (underline).
  CTRL_I,      // Send Ctrl+B (italic).
  DOUBLE_0,    // Send 00
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
                                                      TD(TAP_SWAP), KC_VOLU,
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
                                                         ___, KC_MNXT,
                                                              KC_MPLY,
                                                 ___,    ___, KC_MPRV,
    /* right hand */
        ___, KC_F6,     KC_F7,     KC_F8,   KC_F9,      KC_F10,     KC_F11,
        ___, FAST_UP,   KC_HOME,   KC_UP,   KC_END,     KC_PGUP,    KC_F12,
             FAST_DOWN, KC_LEFT,   KC_DOWN, KC_RIGHT,   KC_PGDN,    CW_TOGG,
        ___, ___,       CTRL_LEFT, ___,     CTRL_RIGHT, SWAP_CHARS, COPY_WORD,
                        ___,       ___,     ___,        ___,        ___,
    KC_HOME, KC_END,
    KC_PGUP,
    KC_PGDN, ___,       ___),
    // Note that any change to the FN layer above must be added to
    // the MOUSE layer below (except for the arrow keys).

  // Layer 2: Mouse control.
  [MOUSE] = LAYOUT_ergodox(
    /* left hand */
    KC_SLEP, KC_F1,      KC_F2,   KC_F3,   KC_F4,    KC_F5,    ___,
    ___,     ___,        KC_BTN1, KC_MS_U, KC_BTN2,  ___,      ___,
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
  // Note: we don’t have the copy/cut/paste keys on this layer so that the '.'
  // is easily accessible (conflict with paste).
  // Also, we don’t use the KC_KP_DOT and KC_KP_EQUAL keys as they are not
  // recognised by all OSs.
  [NUMS] = LAYOUT_ergodox(
    /* left hand */
    KC_PSCR, KC_INS, KC_PAUS, ___, ___, ___, ___,
    ___,     ___,    ___,     ___, ___, ___, ___,
    ___,     ___,    ___,     ___, ___, ___,
    ___,     ___,    ___,     ___, ___, ___, ___,
    ___,     ___,    ___,     ___,     ___,
                                              ___, ___,
                                                   ___,
                                         ___, ___, ___,
    /* right hand */
         ___,     ___,      ___,   ___,   ___,     ___,     KC_NUM,
         ___,     ___,      KC_P7, KC_P8, KC_P9,   KC_PMNS, KC_SCRL,
                  DOUBLE_0, KC_P4, KC_P5, KC_P6,   KC_PPLS, ___,
         KC_PENT, KC_P0,    KC_P1, KC_P2, KC_P3,   KC_PAST, ___,
                           ___,   ___,   ___,     KC_PSLS, ___,
    ___, ___,
    ___,
    ___, ___, ___),

  // Layer 4: The LEDs are showing the "standard" caps/num/scroll lock indicator
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

  // Layer 5: hand swap mode, the primary FN/MOUSE thumb keys are now activating
  // and swap. The second thumb key become the FN mode/toggle (on both sides).
  [SWAP] = LAYOUT_ergodox(
    /* left hand */
    ___, ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___,
                                  ___,    ___,
                                          ___,
                          SH_TT, TT(FN), ___,
    /* right hand */
         ___, ___, ___, ___, ___, ___, ___,
         ___, ___, ___, ___, ___, ___, ___,
              ___, ___, ___, ___, ___, ___,
         ___, ___, ___, ___, ___, ___, ___,
                   ___, ___, ___, ___, ___,
    ___, ___,
    ___,
    ___, TT(FN),  SH_TT),
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

// For the Swap-hand tap-dance we define a small state machine as the pre-
// defined macros don’t allow for a "hold" action.
typedef enum {
    TD_UNKNOWN,
    TD_SINGLE_TAP, // One key-press
    TD_SINGLE_HOLD, // One key-hold
    TD_MULTI_TAP_NO_TOGGLE, // Several key-press, less than TAPPING_TOGGLE
    TD_MULTI_HOLD_NO_TOGGLE, // Several key-press, the last is hold
    TD_TOGGLED_TAP, // At least TAPPING_TOGGLE key-press
    TD_TOGGLED_HOLD, // At least TAPPING_TOGGLE key-press, the last is held.
} td_state_t;

td_state_t parse_dance_state(tap_dance_state_t *state) {
  _Static_assert(TAPPING_TOGGLE > 1, "TAPPING_TOGGLE must be larger than 1");
  // We ignore the state->interrupted value and assume that when we’re
  // interrupted, we have a HOLD. In some circumstance it might be preferable to
  // handle an interrupted key press as a TAP.
  if (state->pressed) {
    if (state->count == 1) {
      return TD_SINGLE_HOLD;
    } else if (state->count < TAPPING_TOGGLE) {
      return TD_MULTI_HOLD_NO_TOGGLE;
    } else {
      return TD_TOGGLED_HOLD;
    }
  } else {
    if (state->count == 1) {
      return TD_SINGLE_TAP;
    } else if (state->count < TAPPING_TOGGLE) {
      return TD_MULTI_TAP_NO_TOGGLE;
    } else {
      return TD_TOGGLED_TAP;
    }
  }
}

td_state_t swap_hand_state = TD_UNKNOWN;

void swap_hand_tapdance_finished(tap_dance_state_t *state, void *user_data) {
  swap_hand_state = parse_dance_state(state);
  switch (swap_hand_state) {
    case TD_SINGLE_HOLD:
    case TD_MULTI_HOLD_NO_TOGGLE:
      swap_hands_on();
      break;
    case TD_TOGGLED_TAP:
    case TD_TOGGLED_HOLD:
      if (layer_state_is(SWAP)) {
        layer_off(SWAP);
      } else {
        layer_on(SWAP);
      }
      break;
    default:
      break;
  }
}

void swap_hand_tapdance_reset(tap_dance_state_t *state, void *user_data) {
  switch (swap_hand_state) {
    case TD_SINGLE_HOLD:
    case TD_MULTI_HOLD_NO_TOGGLE:
      swap_hands_off();
      break;
    default:
      break;
  }
  swap_hand_state = TD_UNKNOWN;
}

// The definition of the tap dance actions:
tap_dance_action_t tap_dance_actions[] = {
  // This Tap dance plays the macro 1 on TAP and records it on double tap.
  [TAP_MACRO] = ACTION_TAP_DANCE_FN(macro_tapdance_fn),
  [TAP_SWAP]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, swap_hand_tapdance_finished, swap_hand_tapdance_reset),
};

// When in hand-swapped mode, we invert some lateralized keys for conveniance.
// However, we must release the right key in case hand-swapping is released
// before the key. This macro handles that behavior.
// `key` is the key being handled (e.g. KC_LEFT) and `opposite` is the key that
// it is replaced with.
// This macro is main to appear in the main switch of the process_record_user
// method.
#define HANDLE_LATERALIZED_KEY(key, opposite) \
  case key:                 \
    { \
      static bool has_pressed_ ## key = false;                \
      if (is_swap_hands_on() && record->event.pressed) { \
        register_code(opposite); \
        has_pressed_ ## key = true; \
        return false; \
      } else if ((is_swap_hands_on() || has_pressed_ ## key) && !record->event.pressed) { \
          unregister_code(opposite); \
          has_pressed_ ## key = false; \
          return false; \
      } \
    } \
    break;

#define HANDLE_LATERALIZED_KEY_PAIR(key, opposite) \
  HANDLE_LATERALIZED_KEY(key, opposite); \
  HANDLE_LATERALIZED_KEY(opposite, key);

// When using "caps word" we have to manually distinguish between '_' and other
// uses of the SPC_RALT key. This variable keeps track of whether the last key
// press was an underscore.
bool last_press_is_underscore = false;

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

  // Make sure that '_' key press don’t deactivate the caps word mode but that
  // other use of the SPC_RALT key will turn it off.
  // This is not trivial because we have no easy way to know what use of
  // SPC_RALT will be sent. So this is probably just an approximation.
  bool set_last_press_is_underscore = false;
  if (keycode == SPC_RALT && is_caps_word_on()) {
    if (get_mods() == MOD_BIT(KC_RALT)) {
      if (record->event.pressed) {
        // This is necessarily a '_' being entered.
        set_last_press_is_underscore = true;
      }
    } else if (!record->event.pressed) {
      if (!last_press_is_underscore) {
        caps_word_off();
      }
    }
  }
  last_press_is_underscore = set_last_press_is_underscore;

  #define SEND_STRING_IF_PRESSED(x) if (record->event.pressed) { SEND_STRING(x); } else {}

  switch(keycode) {
    case COPY_ALL:
      // A in QWERTY is also A in BÉPO (SEND_STRING assumes a QWERTY keymap)
      // There is no string representation of the insert key, so we need to use
      // the SS_UP/DOWN macro, instead of SS_LCTL(...).
      SEND_STRING_IF_PRESSED(SS_LCTL("a") SS_DOWN(X_LCTL) SS_TAP(X_INSERT) SS_UP(X_LCTL) SS_TAP(X_RIGHT));
      return false;
    case PASTE_LINK:
      // B in QWERTY is K in BÉPO
      SEND_STRING_IF_PRESSED(SS_LCTL("b") SS_DOWN(X_LSFT) SS_TAP(X_INSERT) SS_UP(X_LSFT) SS_TAP(X_ENTER));
      return false;
    case FAST_UP:
      if (record->event.pressed) {
        for (int i = 0; i < FAST_ARROW_TIME; i++) {
          SEND_STRING(SS_TAP(X_UP));
        }
        return false;
      }
    case FAST_DOWN:
      if (record->event.pressed) {
        for (int i = 0; i < FAST_ARROW_TIME; i++) {
          SEND_STRING(SS_TAP(X_DOWN));
        }
        return false;
      }
    case CTRL_B:
      SEND_STRING_IF_PRESSED(SS_LCTL("q"));  // Ctrl+q (== Ctrl+b in bépo)
      return false;
    case CTRL_U:
      SEND_STRING_IF_PRESSED(SS_LCTL("s"));  // Ctrl+s (== Ctrl+u in bépo)
      return false;
    case CTRL_I:
      SEND_STRING_IF_PRESSED(SS_LCTL("d"));  // Ctrl+d (== Ctrl+i in bépo)
      return false;
    case DOUBLE_0:
      if (record->event.pressed) {
        tap_code(KC_P0);
        tap_code(KC_P0);
      }
      return false;
    case SWAP_CHARS:
      SEND_STRING_IF_PRESSED(
          SS_DOWN(X_LSFT) SS_TAP(X_LEFT) SS_UP(X_LSFT)  // Select char to the left
          SS_DOWN(X_LSFT) SS_TAP(X_DEL) SS_UP(X_LSFT)  // Shift + Del == cut
          SS_TAP(X_LEFT)
          SS_DOWN(X_LSFT) SS_TAP(X_INSERT) SS_UP(X_LSFT)  // Shift + Insert == paste
          SS_TAP(X_RIGHT)
        );
      return false;
    case COPY_WORD:
      SEND_STRING_IF_PRESSED(
          SS_DOWN(X_LCTL) SS_TAP(X_LEFT) SS_UP(X_LCTL)  // Ctrl + Left
          SS_DOWN(X_LCTL) SS_DOWN(X_LSFT) SS_TAP(X_RIGHT) SS_UP(X_LSFT) SS_UP(X_LCTL)  // Ctrl + Shift + Right
          SS_DOWN(X_LCTL) SS_TAP(X_INSERT) SS_UP(X_LCTL)  // Ctrl + Insert == copy
          SS_DOWN(X_RIGHT)
        );
      return false;
    case CTRL_LEFT:
      if (record->event.pressed) {
        register_code(KC_LCTL);
        register_code(KC_LEFT);
      } else {
        unregister_code(KC_LEFT);
        unregister_code(KC_LCTL);
      }
      return false;
    case CTRL_RIGHT:
      if (record->event.pressed) {
        register_code(KC_LCTL);
        register_code(KC_RIGHT);
      } else {
        unregister_code(KC_RIGHT);
        unregister_code(KC_LCTL);
      }       
      return false;
    HANDLE_LATERALIZED_KEY_PAIR(KC_LEFT, KC_RIGHT);
    HANDLE_LATERALIZED_KEY_PAIR(KC_MS_L, KC_MS_R);
    HANDLE_LATERALIZED_KEY_PAIR(KC_WH_L, KC_WH_R);
    HANDLE_LATERALIZED_KEY_PAIR(KC_BTN1, KC_BTN2);
    HANDLE_LATERALIZED_KEY_PAIR(KC_ACL0, KC_ACL2);
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

  if ((bool)LAYER_ON(FN) ^ (bool)LAYER_ON(SWAP)) {
    led_3_on();
  } else {
    led_3_off();
  }

  if ((bool)LAYER_ON(NUMS) ^ (bool)LAYER_ON(SWAP)) {
    led_2_on();
  } else {
    led_2_off();
  }

  if ((bool)LAYER_ON(MOUSE) ^ (bool)LAYER_ON(SWAP)) {
    led_1_on();
  } else {
    led_1_off();
  }

  return state;
};

// Called while "caps word" is active (when CW_TOGG was pressed) to determine
// which keys are word breaking.
bool caps_word_press_user(uint16_t keycode) {
  switch (keycode) {
    // Keycodes that continue Caps Word, with shift applied.
    case KC_A ... KC_X:
    case KC_Z:
    case KC_LBRC:  // Z
    case KC_RBRC:  // W
    case KC_SCLN:  // N
    case KC_QUOT:  // M
    case KC_BSLS:  // Ç
    case KC_NUBS:  // Ê
    case KC_COMM:  // G
    case KC_DOT:   // H
    case KC_SLSH:  // F
      add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
      return true;

    // Keycodes that continue Caps Word, without shifting.
    case KC_Y:  // ^
    case KC_ALGR:  // alt-gr
    case KC_BSPC:
    case KC_DEL:
    case KC_UNDS:
    case KC_8:  // '-'
      return true;
    // When using the SPC_RALT key, the caps word is interrupted unless we fully
    // allow KC_SPC here (this might be considered to be a bug in the
    // process_caps_word function which looks at the tap function of keys only*).
    // So we fully allow the KC_SPC key and then, in process_record_user, we
    // handle the cases where a space is entered and manually interrupt the
    // caps word.
    // *This bug, is due to the same reason why the handling in
    // process_record_user is complex: it’s because during this whole processing
    // there is no way yet to know which function of a key will be sent.
    // Maybe this would be simpler if SPC_RALT was implemented with a tap-dance
    // but it’s not as configurable wrt interruption.
    case KC_SPC:
      return true;

    default:
      return false;  // Deactivate Caps Word.
  }
}

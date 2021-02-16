/* 2021 hydrx
 */
#include QMK_KEYBOARD_H

// layers:
#define _CK 0
#define _FN 1

enum custom_keycodes {
  CK = SAFE_RANGE,
  FN,
};

// tap dance declarations
enum {
  C_Z = 0,
  C_X,
  C_V,
  C_S,
  S_C,
};

// define a type containing as many tapdance states as you need
typedef enum {
  SINGLE_TAP,
  SINGLE_HOLD,
  DOUBLE_SINGLE_TAP
} td_state_t;

// create a global instance of the tapdance state type
static td_state_t td_state_sft;
static bool caps_lock = false;

// declare your tapdance functions:

// function to determine the current tapdance state
int cur_dance (qk_tap_dance_state_t *state);

// `finished` and `reset` functions for each tapdance keycode
void sft_finished (qk_tap_dance_state_t *state, void *user_data);
void sft_reset (qk_tap_dance_state_t *state, void *user_data);


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* COLEMAK
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | ESC    | 1      | 2      | 3      | 4      | 5      | -      | =      | \      | 6      | 7      | 8      | 9      | 0      | `      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * | TAB    | Q      | W      | F      | P      | G      | P7     | P8     | P9     | J      | L      | U      | Y      | ;      | '      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * | FN     | A      | R      | S      | T      | D      | P4     | P5     | P6     | H      | N      | E      | I      | O      | ENTER  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * | SHIFT  | Z      | X      | C      | V      | B      | P1     | P2     | P3     | K      | M      | ,      | .      |  /     | SFL    |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * | LCTRL  | LGUI   | LALT   | CTRL+S | [      | SPACE  | BKSP   | P0     | ENTER  | SPACE  | ]      |  LEFT  |  UP    |  DOWN  | RIGHT  |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

  [_CK] = { /* COLEMAK */
   { KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_MINS, KC_EQL,  KC_BSLS, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV   },
   { KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_P7,   KC_P8,   KC_P9,   KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_QUOT  },
   { TT(_FN), KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_P4,   KC_P5,   KC_P6,   KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_ENT   },
   { KC_LSFT, TD(C_Z), TD(C_X), KC_C,    TD(C_V), KC_B,    KC_P1,   KC_P2,   KC_P3,   KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, TD(S_C)  },
   { KC_LCTL, KC_LGUI, KC_LALT, TD(C_S), KC_LBRC, KC_SPC,  KC_BSPC, KC_P0,   KC_ENT,  KC_SPC,  KC_RBRC, KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT  },
  },

/* FUNCTION LAYER - arrows, fn keys, media keys
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        | F1     | F2     | F3     | F4     | F5     | F11    | F12    |        | F6     | F7     | F8     | F9     | F10    | `      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * |        |        |   UP   |        |        |        | RESET  |RGB_TOG |RGB_MOD |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * |        |  LEFT  |  DOWN  | RIGHT  |        |        |  ASUP  |  ASTG  |  ASRP  |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * |        |        |        |        |        |        |  ASDN  |   UP   |  DEL   |        |        |        |        |        | PLAY   |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * |        |        |        |        |        |        |  LEFT  |  DOWN  | RIGHT  |        |        | RW     | VOLU   | VOLD   | FW     |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

  [_FN] = { /* FUNCTION */
   { KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F11,  KC_F12,  KC_TRNS, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_TRNS  },
   { KC_TRNS, KC_TRNS, KC_UP,   KC_TRNS, KC_TRNS, KC_TRNS, RESET,   RGB_TOG, RGB_MOD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS  },
   { KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS, KC_ASUP, KC_ASTG, KC_ASRP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS  },
   { KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_ASDN, KC_UP,   KC_DEL,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY  },
   { KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS, KC_MPRV, KC_VOLU, KC_VOLD, KC_MNXT  },
  }
 };

// determine the tapdance state to return
int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed) { return SINGLE_TAP; }
    else { return SINGLE_HOLD; }
  }
  if (state->count == 2) { return DOUBLE_SINGLE_TAP; }
  else { return 3; } // any number higher than the maximum state value you return above
}

#define DEBOUNCE_CAPS_DELAY 100

// handle the possible states for each tapdance keycode you define:

void sft_finished (qk_tap_dance_state_t *state, void *user_data) {
  td_state_sft = cur_dance(state);
    if (td_state_sft == DOUBLE_SINGLE_TAP) {
        if (!caps_lock) {
            register_code(KC_CAPSLOCK);
            return;
        }
    }
   
    if (caps_lock) {
        register_code(KC_CAPSLOCK);
    } else {
        register_code(KC_LSFT);
    }
}

void sft_reset (qk_tap_dance_state_t *state, void *user_data) {
     if (td_state_sft == DOUBLE_SINGLE_TAP) {
        if (!caps_lock) {
            caps_lock = true;
            wait_ms(DEBOUNCE_CAPS_DELAY);
            unregister_code(KC_CAPSLOCK);
            return;
        }
    }

    if (caps_lock) {
        caps_lock = false;
        wait_ms(DEBOUNCE_CAPS_DELAY);
        unregister_code(KC_CAPSLOCK);
    } else {
        unregister_code(KC_LSFT);
    }
}

// tap dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  [C_Z]  = ACTION_TAP_DANCE_DOUBLE(KC_Z, LCTL(KC_Z)),
  [C_X]  = ACTION_TAP_DANCE_DOUBLE(KC_X, LCTL(KC_X)),
  [C_V]  = ACTION_TAP_DANCE_DOUBLE(KC_V, LCTL(KC_V)),
  [C_S]  = ACTION_TAP_DANCE_DOUBLE(LCTL(KC_S), LCTL(KC_C)),
  [S_C] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sft_finished, sft_reset)
};

  // Set numlock to always on when keyboard starts
  void matrix_init_user (void) {
    if (!(host_keyboard_leds() & (1<<USB_LED_NUM_LOCK))) {
        register_code(KC_NUMLOCK);
        unregister_code(KC_NUMLOCK);
    }
  }
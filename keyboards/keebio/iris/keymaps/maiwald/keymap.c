#include QMK_KEYBOARD_H
#include "keymap_german_osx.h"

enum layers {
  _COLEMAK = 0,
  _EXTEND,
  _SYMBOLS,
  _GERMAN,
};

enum custom_keycodes {
  MY_SLSH = SAFE_RANGE,
};

enum {
  TD_GUI_ALT,
  TD_GER_ALT,
};

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD,
};

int cur_dance(qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->pressed) return SINGLE_HOLD;
    else return SINGLE_TAP;
  }

  return 8;
}

// Create an instance of 'tap' for the 'x' tap dance.
static uint8_t gertap_state = 0;

void gertap_finished(qk_tap_dance_state_t *state, void *user_data) {
  gertap_state = cur_dance(state);
  switch (gertap_state) {
    case SINGLE_TAP:
      set_oneshot_layer(_GERMAN, ONESHOT_START);
      clear_oneshot_layer_state(ONESHOT_PRESSED);
      break;
    case SINGLE_HOLD:
      register_code(KC_RALT);
      break;
  }
}

void gertap_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (gertap_state) {
    case SINGLE_TAP:
      break;
    case SINGLE_HOLD:
      unregister_code(KC_RALT);
      break;
  }
  gertap_state = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_GUI_ALT] = ACTION_TAP_DANCE_DOUBLE(KC_LGUI, KC_LALT),
  [TD_GER_ALT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, gertap_finished, gertap_reset),
};

#define MY_A LCTL_T(DE_A)
#define MY_O RCTL_T(DE_O)
#define MY_R LSFT_T(DE_R)
#define MY_I RSFT_T(DE_I)

#define VIM_ALT C(DE_6)
#define KC_EUR  S(A(KC_2))
#define MY_GUI  TD(TD_GUI_ALT)
#define MY_ALT  TD(TD_GER_ALT)
#define MY_SCSH G(S(KC_4))

#define EXT_SPC  LT(_EXTEND, KC_SPC)
#define SFT_ZERO MT(MOD_LSFT, DE_0)

bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case EXT_SPC:
      return true;
    default:
      return false;
  }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_COLEMAK] = LAYOUT(
      DE_GRV,  DE_1, DE_2, DE_3, DE_4,   DE_5,                                        DE_6,    DE_7,   DE_8,    DE_9,   DE_0,    MY_SCSH,
      KC_TAB,  DE_Q, DE_W, DE_F, DE_P,   DE_B,                                        DE_J,    DE_L,   DE_U,    DE_Y,   DE_QUOT, KC_BSPC,
      KC_ESC,  MY_A, MY_R, DE_S, DE_T,   DE_G,                                        DE_M,    DE_N,   DE_E,    MY_I,   MY_O,    KC_ENT,
      KC_LSFT, DE_Z, DE_X, DE_C, DE_D,   DE_V,          KC_BSPC,       KC_ENT,        DE_K,    DE_H,   DE_COMM, DE_DOT, MY_SLSH, KC_RSFT,
                                 MY_GUI, OSM(MOD_LSFT), OSL(_SYMBOLS), OSL(_SYMBOLS), EXT_SPC, MY_ALT
      ),

  [_EXTEND] = LAYOUT(
      XXXXXXX, KC_BRID, KC_BRIU, RGB_TOG, RGB_VAD, RGB_VAI,                       KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLD, KC_VOLU, XXXXXXX,
      _______, XXXXXXX, DE_7,    DE_8,    DE_9,    DE_PLUS,                       KC_HOME, KC_PGUP, VIM_ALT, XXXXXXX, KC_DEL,  XXXXXXX,
      _______, XXXXXXX, DE_4,    DE_5,    DE_6,    DE_MINS,                       KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_BSPC, XXXXXXX,
      _______, XXXXXXX, DE_1,    DE_2,    DE_3,    XXXXXXX,  A(KC_BSPC), RESET,   KC_END,  KC_PGDN, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                          _______, SFT_ZERO, KC_LALT,    _______, _______, _______
      ),

  [_SYMBOLS] = LAYOUT(
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      XXXXXXX, DE_EXLM, DE_LABK, DE_AT,   DE_RABK, DE_PLUS,                   DE_CIRC, DE_LBRC, DE_UNDS, DE_RBRC, DE_EURO, XXXXXXX,
      XXXXXXX, DE_BSLS, DE_LPRN, DE_DQUO, DE_RPRN, DE_MINS,                   DE_PERC, DE_LCBR, DE_EQL,  DE_RCBR, DE_PIPE, XXXXXXX,
      XXXXXXX, XXXXXXX, DE_TILD, DE_QUOT, DE_HASH, DE_DLR,  _______, _______, DE_GRV,  DE_AMPR, DE_ASTR, DE_COLN, DE_QUES, XXXXXXX,
                                          _______, KC_SPC,  _______, _______, _______, _______
      ),

  [_GERMAN] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______,                   _______, _______, DE_UDIA, _______, _______, _______,
      _______, DE_ADIA, _______, DE_SS,   _______, _______,                   _______, _______, _______, _______, DE_ODIA, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                          _______, _______, _______, _______, _______, _______
      ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  uint16_t one_shot_mod_state = get_oneshot_mods();

  switch (keycode) {
    case KC_TRNS:
    case KC_NO:
      /* Always cancel one-shot layer when another key gets pressed */
      if (record->event.pressed && is_oneshot_layer_active())
      clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
      return true;
    case MY_SLSH:
      if (record->event.pressed) {
        if ((get_mods() | one_shot_mod_state) & MOD_MASK_SHIFT) {
          tap_code16(DE_QUES);
        } else {
          tap_code16(DE_SLSH);
        }
      }
      return false;
    case KC_ESC:
      if (one_shot_mod_state) {
        clear_oneshot_mods();
        return false;
      } else {
        return true;
      }
    default:
      return true;
  }
}

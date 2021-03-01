#include QMK_KEYBOARD_H

enum layers {
  _COLEMAK = 0,
  _EXTEND,
  _SYMBOLS
};

enum custom_keycodes {
  MY_COMM = SAFE_RANGE,
  MY_DOT,
};

enum {
  TD_GUI_ALT,
};

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_GUI_ALT] = ACTION_TAP_DANCE_DOUBLE(KC_LGUI, KC_LALT),
};

#define MY_A LCTL_T(KC_A)
#define MY_O RCTL_T(KC_O)
#define MY_R LSFT_T(KC_R)
#define MY_I RSFT_T(KC_I)

#define VIM_ALT S(C(KC_CIRC))
#define KC_EUR  S(A(KC_2))
#define MY_GUI  TD(TD_GUI_ALT)

#define EXT_SPC  LT(_EXTEND, KC_SPC)
#define SFT_ZERO MT(MOD_LSFT, KC_0)

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
      KC_GRV,  KC_1, KC_2, KC_3, KC_4,   KC_5,                                        KC_6,    KC_7,   KC_8,    KC_9,   KC_0,    KC_MINS,
      KC_TAB,  KC_Q, KC_W, KC_F, KC_P,   KC_B,                                        KC_J,    KC_L,   KC_U,    KC_Y,   KC_QUOT, KC_BSPC,
      KC_ESC,  MY_A, MY_R, KC_S, KC_T,   KC_G,                                        KC_M,    KC_N,   KC_E,    MY_I,   MY_O,    KC_ENT,
      KC_LSFT, KC_Z, KC_X, KC_C, KC_D,   KC_V,          KC_BSPC,       KC_ENT,        KC_K,    KC_H,   MY_COMM, MY_DOT, KC_SLSH, KC_RSFT,
                                 MY_GUI, OSM(MOD_LSFT), OSL(_SYMBOLS), OSL(_SYMBOLS), EXT_SPC, KC_RALT
      ),

  [_EXTEND] = LAYOUT(
      XXXXXXX, KC_BRID, KC_BRIU, RGB_TOG, RGB_VAD, RGB_VAI,                       KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLD, KC_VOLU, XXXXXXX,
      _______, XXXXXXX, KC_7,    KC_8,    KC_9,    KC_PLUS,                       KC_HOME, KC_PGUP, VIM_ALT, XXXXXXX, KC_DEL,  XXXXXXX,
      _______, XXXXXXX, KC_4,    KC_5,    KC_6,    KC_MINS,                       KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_BSPC, XXXXXXX,
      _______, XXXXXXX, KC_1,    KC_2,    KC_3,    XXXXXXX,  A(KC_BSPC), RESET,   KC_END,  KC_PGDN, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                          _______, SFT_ZERO, KC_LALT,    _______, _______, _______
      ),

  [_SYMBOLS] = LAYOUT(
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      XXXXXXX, KC_EXLM, KC_LT,   KC_AT,   KC_GT,   KC_PLUS,                   KC_CIRC, KC_LBRC, KC_UNDS, KC_RBRC, KC_EUR,  XXXXXXX,
      XXXXXXX, KC_BSLS, KC_LPRN, KC_DQUO, KC_RPRN, KC_MINS,                   KC_PERC, KC_LCBR, KC_PEQL, KC_RCBR, KC_PIPE, XXXXXXX,
      XXXXXXX, XXXXXXX, KC_TILD, KC_QUOT, KC_HASH, KC_DLR,  _______, _______, KC_GRV,  KC_AMPR, KC_ASTR, KC_COLN, KC_QUES, XXXXXXX,
                                          _______, KC_SPC,  _______, _______, _______, _______
      ),
};

void handle_umlaut(uint16_t base_key, keyrecord_t *record, uint16_t mod_state, uint16_t one_shot_mod_state) {
  if (record->event.pressed) {
    clear_mods();
    clear_oneshot_mods();
    tap_code16(LALT(KC_U));
    set_mods(mod_state & MOD_MASK_SHIFT);
    set_oneshot_mods(one_shot_mod_state & MOD_MASK_SHIFT);
    tap_code(base_key);
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  uint16_t mod_state = get_mods();
  uint16_t one_shot_mod_state = get_oneshot_mods();

  switch (keycode) {
    case KC_ESC:
      if (one_shot_mod_state) {
        clear_oneshot_mods();
        return false;
      } else {
        return true;
      }
    case MY_COMM:
      if (record->event.pressed) {
        if ((mod_state | one_shot_mod_state) & MOD_MASK_SHIFT) {
          set_mods(mod_state & ~MOD_MASK_SHIFT);
          set_oneshot_mods(one_shot_mod_state & ~MOD_MASK_SHIFT);
          tap_code(KC_SCLN);
          set_mods(mod_state);
        } else {
          tap_code(KC_COMM);
        }
      }
      return false;
    case MY_DOT:
      if (record->event.pressed) {
        if ((mod_state | one_shot_mod_state) & MOD_MASK_SHIFT) {
          // this is with a shift mod active, so KC_SCLN becomes S(KC_SCLN)
          tap_code(KC_SCLN);
        } else {
          tap_code(KC_DOT);
        }
      }
      return false;
    default:
      return true;
  }
}

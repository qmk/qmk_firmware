// Copyright 2021 Tomasz Wawer (@sq5rix)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
    _BEAKL15,
    _LOWER,
    _RAISE,
    _MOUSE
};

enum custom_keycodes {
   LT_DAT = SAFE_RANGE,
   LT_COM,
   LT_QUOT
};

#define LOWER  LT(_LOWER, KC_ENT)
#define LOWER2 LT(_LOWER, KC_T)
#define RAISE  LT(_RAISE, KC_SPC)
#define RAISE2 LT(_RAISE, KC_BSPC)
#define MOUSE  LT(_MOUSE, KC_A)

#define SH_ESC MT(MOD_LSFT, KC_ESC)
#define SH_CWD MT(MOD_LALT, KC_BSPC)
#define SH_LTAB MT(MOD_LALT, KC_TAB)
#define SH_UND MT(MOD_LCTL, KC_UNDS)
#define SH_Z MT(MOD_LCTL, KC_Z)

#define SH_LGS MT(MOD_LGUI, KC_B)
#define AL_I ALGR_T(KC_I)
#define AL_N ALGR_T(KC_N)

// Tap Dance definitions
enum {
    TD_S
};
tap_dance_action_t tap_dance_actions[] = {
    [TD_S] = ACTION_TAP_DANCE_DOUBLE(KC_S, KC_Z),
};

bool sh_key(keyrecord_t *record, uint8_t sk, uint8_t nk);
bool sh_key8(keyrecord_t *record, uint8_t sk, uint8_t nk);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 [_BEAKL15] = LAYOUT(
  TG(_RAISE),  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_DEL,
     SH_LTAB,  KC_Q,    KC_H,    KC_O,    KC_U,    KC_X,                               KC_G,    KC_C,    KC_R,    KC_F,    KC_Z,    KC_LGUI,
     SH_UND,   KC_Y,    AL_I,    KC_E,    MOUSE,   LT_DAT,                             KC_D,    TD(TD_S),LOWER2,  AL_N,    KC_B,    KC_SCLN,
     KC_LSFT,  KC_J,    KC_SLSH, LT_COM,  KC_K,    LT_QUOT, RGB_TOG,          BL_TOGG, KC_W,    KC_M,    KC_L,    KC_P,    KC_V,    KC_RSFT,
                                       SH_Z, LOWER, RAISE,                      SH_ESC,  RAISE2, SH_LTAB
  ),

  [_LOWER] = LAYOUT(
     _______, _______, _______, _______, _______, _______,                             _______, _______, _______, _______, _______, _______,
     _______, _______, KC_LT,   KC_DLR,  KC_GT,   KC_EXLM,                             _______, KC_LBRC, KC_UNDS, KC_RBRC, KC_EXLM, _______,
     _______, KC_BSLS, KC_LPRN, KC_DQUO, KC_RPRN, KC_HASH,                             KC_PERC, KC_LCBR, KC_EQL,  KC_RCBR, KC_PIPE, _______,
     _______, KC_SCLN, KC_SLSH, KC_ASTR, KC_PLUS,  _______, _______,          _______, _______, KC_AMPR, KC_CIRC, KC_TILD, KC_SCLN, _______,
                                    _______, _______, _______,                    _______, _______, _______

  ),

  [_RAISE] = LAYOUT(
     _______,  KC_VOLD, KC_VOLU, KC_MUTE, KC_BRIGHTNESS_DOWN, KC_BRIGHTNESS_UP,    KC_PSCR,    _______, _______, _______, _______, QK_BOOT,
     _______,  KC_SLSH, KC_6,    KC_5,    KC_4,    KC_EQL,                            KC_CIRC, KC_PGUP, KC_UP,   KC_PGDN, _______, RGB_VAI,
     _______,  KC_3,    KC_2,    KC_1,    KC_0,    KC_DOT,                            KC_EQL,  KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,
     _______,  KC_ASTR, KC_9,    KC_8,    KC_7,    KC_PLUS,  _______,        _______, KC_PLUS, KC_HOME, KC_COLN, KC_END,  _______, RGB_MOD,
                                    _______, _______, _______,                    _______, _______, _______
  ),

  [_MOUSE] = LAYOUT(
     _______, _______, _______, _______, _______, _______,                             _______, _______, _______, _______, _______, _______,
     _______, _______, _______, _______, _______, _______,                             _______, KC_BTN1, KC_MS_U, KC_BTN2, _______, _______,
     _______, _______, _______, KC_BTN1, _______, _______,                             _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______,
     _______, _______, _______, _______, _______, _______, _______,           _______, _______, _______, KC_BTN3, _______, _______, _______,
                                    _______, _______, _______,                    _______, _______, _______
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LT_DAT:
      return sh_key8(record, KC_2, KC_DOT);
    case LT_COM:
      return sh_key8(record, KC_1, KC_COMM);
    case LT_QUOT:
      return sh_key(record, KC_GRV, KC_QUOT);
    default:
      return true;
  }
}

bool sh_key(keyrecord_t *record, uint8_t sk, uint8_t nk){
      if (record->event.pressed) {
        if (get_mods() & MOD_BIT(KC_LSFT) || get_mods() & MOD_BIT(KC_RSFT)){
           unregister_code(KC_LSFT);
           unregister_code(KC_RSFT);
           register_code(sk);
        } else {
           register_code(nk);
        }
      }
      else {
           unregister_code16(sk);
           unregister_code(nk);
      }
      return false;
}

bool sh_key8(keyrecord_t *record, uint8_t sk, uint8_t nk){
      if (record->event.pressed) {
        if (get_mods() & MOD_BIT(KC_LSFT) || get_mods() & MOD_BIT(KC_RSFT)){
           register_code(sk);
        } else {
           register_code(nk);
        }
      }
      else {
           unregister_code(sk);
           unregister_code(nk);
      }
      return false;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code16(C(G(KC_LEFT)));
        } else {
            tap_code16(C(G(KC_RGHT)));
        }
    }
    // tmux screen
    else if (index == 1) {
        switch(get_highest_layer(layer_state)){
             case 0:
                if (clockwise) {
                    send_string(SS_LCTL("B")"p");
                } else {
                    send_string(SS_LCTL("B")"n");
                }
                break;
             case _RAISE:
                if (clockwise) {
                    tap_code16(C(G(KC_PGUP)));
                } else {
                    tap_code16(C(G(KC_PGDN)));
                }
                break;
        }
    }
    return true;
}

const rgblight_segment_t PROGMEM raise_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 12, HSV_RED}
);
const rgblight_segment_t PROGMEM lower_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 12, HSV_BLUE}
);
const rgblight_segment_t PROGMEM mouse_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 12, HSV_GREEN}
);

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    lower_layer,
    raise_layer,
    mouse_layer
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, 2));
    rgblight_set_layer_state(1, layer_state_cmp(state, 3));
    rgblight_set_layer_state(2, layer_state_cmp(state, 4));
    return state;
}

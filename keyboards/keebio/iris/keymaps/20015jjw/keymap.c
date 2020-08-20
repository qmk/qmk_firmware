#include QMK_KEYBOARD_H
#include <rgblight.h>
#include <report.h>
#include <config.h>
#include <quantum.h>

extern keymap_config_t keymap_config;

// #define _QWERTY 0
// #define _LOWER 1
// #define _RAISE 2
// #define _MOUSE 3
// #define _ADJUST 4
// #define _HWCT 5

// enum custom_keycodes {
//   QWERTY = SAFE_RANGE,
//   FN,
//   MOUSE,
//   ADJUST,
//   HWCT,
// };

enum my_layers {
  _QWERTY,
  _FN,
  _MOUSE,
  _ADJUST,
  _HWCT,
};

#define LCTL_ESC LCTL_T(KC_ESC)
#define LGUI_MINS LGUI_T(KC_MINUS)
#define HYPR_ENT HYPR_T(KC_ENT)

#define FN_SPC LT(_FN, KC_SPACE)
#define FN_ENT LT(_FN, KC_ENT)

#define SLEEP LALT(LGUI(KC_MEDIA_EJECT))

#define NXT_SCR LALT(LSFT(KC_P))

#define KC_MOUS TT(_MOUSE) // double tab toggle mouse layer
// #define KC_HWCT TT(_HWCT) // double tab toggle hardware control layer

#define MS_L KC_MS_LEFT
#define MS_R KC_MS_RIGHT
#define MS_U KC_MS_UP
#define MS_D KC_MS_DOWN
#define MS_B1 KC_MS_BTN1
#define MS_B2 KC_MS_BTN2
#define MW_U KC_MS_WH_UP
#define MW_D KC_MS_WH_DOWN
#define MW_L KC_MS_WH_LEFT
#define MW_R KC_MS_WH_RIGHT

//// only uncomment the below line when you enable leader key in rules.mk
//LEADER_EXTERNS();

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_EQL,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     LCTL_ESC,KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSPO, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_MUTE,          NXT_SCR, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    KC_LALT, LGUI_MINS,FN_SPC,                   FN_SPC,  KC_BSPC, HYPR_ENT
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_FN] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_GESC, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_MINUS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     RESET,   EEP_RST, _______, _______, _______, _______,                            _______, _______, _______, _______, KC_LBRC, KC_RBRC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     RGB_TOG, RGB_MOD, _______, _______, _______, _______,                            KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, RGB_HUI, RGB_SAI, RGB_VAI, _______, _______, KC_MPLY,           KC_F12,  _______, _______, _______, _______, _______, SLEEP,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, KC_DEL,  _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_MOUSE] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, MS_B1,   MS_U,    MS_B2,   MW_U,    _______,                            _______, MS_B1,   MS_B2,   _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, MS_L,    MS_D,    MS_R,    MW_D,    _______,                            MS_L,    MS_D   , MS_U,    MS_R    ,_______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, MW_L,    MW_R,    _______, _______,          _______, KC_BRID, KC_BRIU, KC_VOLD, KC_VOLU, KC_MUTE, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_ADJUST] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     BL_BRTG, _______, _______, _______, DEBUG,   RESET,                              RESET,   DEBUG,   _______, RGB_HUI, RGB_SAI, RGB_VAI,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      BL_INC, _______, _______, _______, _______, EEP_RST,                            EEP_RST, _______, _______, RGB_HUD, RGB_SAD, RGB_VAD,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      BL_DEC, KC_MPRV, KC_MNXT, KC_MFFD, KC_MRWD, KC_MPLY,                            KC_MPRV, KC_MNXT, KC_MFFD, KC_MRWD, KC_MPLY, RGB_MOD,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     BL_TOGG, _______, _______, _______, _______, _______, _______,          _______, KC_BRID, KC_BRIU, KC_VOLD, KC_VOLU, KC_MUTE, RGB_TOG,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_HWCT] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     BL_BRTG, _______, _______, _______, _______,   RESET,                              RESET, _______, _______, RGB_HUI, RGB_SAI, RGB_VAI,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      BL_INC, _______, _______, _______, _______, _______,                            _______, _______, _______, RGB_HUD, RGB_SAD, RGB_VAD,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
      BL_DEC, KC_MPRV, KC_MNXT, KC_MFFD, KC_MRWD, KC_MPLY,                            KC_MPRV, KC_MNXT, KC_MFFD, KC_MRWD, KC_MPLY, RGB_MOD,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     BL_TOGG, _______, _______, _______, _______, _______, KC_EJCT,          _______, KC_BRID, KC_BRIU, KC_VOLD, KC_VOLU, KC_MUTE, RGB_TOG,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  )

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  //   case QWERTY:
  //     if (record->event.pressed) {
  //       set_single_persistent_default_layer(_QWERTY);
  //     }
  //     return false;
  //     break;
  //   case FN:
  //     if (record->event.pressed) {
  //       layer_on(_FN);
  //       dprintf("Got on layer %s ", FN);
  //       update_tri_layer(_LOWER, _RAISE, _MOUSE);
  //     } else {
  //       layer_off(_RAISE);
  //       dprintf("Got off layer %s ", RAISE);
  //       update_tri_layer(_LOWER, _RAISE, _MOUSE);
  //     }
  //     return false;
  //     break;
  //   case MOUSE:
  //     if (record->event.pressed) {
  //       layer_on(_MOUSE);
  //       dprintf("Got on layer %s ", MOUSE);
  //       update_tri_layer(_LOWER, _RAISE, _MOUSE);
  //     } else {
  //       layer_off(_MOUSE);
  //       dprintf("Got off layer %s ", MOUSE);
  //       update_tri_layer(_LOWER, _RAISE, _MOUSE);
  //     }
  //     return false;
  //     break;
  //   case HWCT:
  //     if (record->event.pressed) {
  //       layer_on(_HWCT);
  //       dprintf("Got on layer %s ", HWCT);
  //       update_tri_layer(_LOWER, _RAISE, _MOUSE);
  //     } else {
  //       layer_off(_HWCT);
  //       dprintf("Got off layer %s ", HWCT);
  //       update_tri_layer(_LOWER, _RAISE, _MOUSE);
  //     }
  //     return false;
  //     break;

  //   case ADJUST:
  //     if (record->event.pressed) {
  //       layer_on(_ADJUST);
  //     } else {
  //       layer_off(_ADJUST);
  //     }
  //     return false;
  //     break;
  }

  return true;
}

void keyboard_post_init_user(void) {
  rgblight_enable_noeeprom();
  rgblight_mode_noeeprom(RGBLIGHT_MODE_REACTIVE + 3);
}

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        switch (biton32(layer_state)) {
            case _FN:
                clockwise ? tap_code(KC_MEDIA_NEXT_TRACK) : tap_code(KC_MEDIA_PREV_TRACK);
                break;
            default:
                clockwise ? tap_code(KC_AUDIO_VOL_UP) : tap_code(KC_AUDIO_VOL_DOWN);
                break;
        }
    } else if (index == 1) {
        switch (biton32(layer_state)) {
            case _FN:
                clockwise ? SEND_STRING(SS_LALT(SS_LSFT("h"))) : SEND_STRING(SS_LALT(SS_LSFT("l")));
                break;
            default:
                clockwise ? SEND_STRING(SS_LCTL(SS_TAP(X_RIGHT))) : SEND_STRING(SS_LCTL(SS_TAP(X_LEFT)));
                break;
        }
    }
}

const int led_map[MATRIX_ROWS][MATRIX_COLS] = LAYOUT(

  //┌───┬───┬───┬───┬───┬───┐                 ┌───┬───┬───┬───┬───┬───┐
     2,  2,  1,  1,  0,  0,                    11, 11, 10, 10, 9,  9,
  //├───┼───┼───┼───┼───┼───┤                 ├───┼───┼───┼───┼───┼───┤
     2,  2,  1,  1,  0,  0,                    11, 11, 10, 10, 9,  9,
  //├───┼───┼───┼───┼───┼───┤                 ├───┼───┼───┼───┼───┼───┤
     3,  3,  4,  4,  0,  0,                    11, 11, 7,  7,  8,  8,
  //├───┼───┼───┼───┼───┼───┼───┐         ┌───┼───┼───┼───┼───┼───┼───┤
     3,  3,  4,  4,  5,  5,  5,            6,  6,  6,  7,  7,  8,  8,
  //└───┴───┴───┴──┬┴──┬┴──┬┴──┬┘         └┬──┴┬──┴┬──┴┬──┴───┴───┴───┘
                    4,  5,  5,              6,  6,  7
                 //└───┴───┴───┘           └───┴───┴───┘
);


#ifdef RGBLIGHT_EFFECT_REACTIVE
void pre_process_action_quantum(keyevent_t event) {
    int index = led_map[event.key.row][event.key.col];
    update_reactive_led_map(index, event.pressed);
}
#endif

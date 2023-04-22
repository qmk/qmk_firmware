// Copyright 2018 Wez Furlong
// SPDX-License-Identifier: GPL-2.0-or-later
#include "halfdeck.h"
#include "action_layer.h"
#include "os_detection.h"
#ifdef MOUSEKEY_ENABLE
#include "mousekey.h"
#if TOUCHPAD_IS_CIRQUE
#include "pinnacle.h"
#endif
#endif

// Each layer gets a name for readability, which is then used in the keymap matrix below.
enum layer_id {
  BASE = 0,
  RAISE,
};

// Macro ids for use with M(n)
enum custom_keycodes {
  MCOPY = SAFE_RANGE,
  MCUT,
  MPASTE,
  FNCOPYCUT,
  FNOSTOGGLE,
  FNPANNING,
};

// Whether to come up in "mac mode", which affects the copy/paste macros.
// You can use the FNOSTOGGLE function to toggle this at runtime.
static bool is_mac = false;

static inline bool is_mac_host(void) {
  switch (detected_host_os()) {
    case OS_MACOS:
    case OS_IOS:
      return true;
    default:
      return is_mac;
  }
}

#define ___ KC_TRNS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[BASE]=
  KEYMAP(
    // LEFT
    KC_GRV,        KC_1,     KC_2,         KC_3,     KC_4,      KC_5,     FNCOPYCUT,
    KC_TAB,        KC_Q,     KC_W,         KC_E,     KC_R,      KC_T,     KC_LBRC,
    CTL_T(KC_ESC), KC_A,     KC_S,         KC_D,     KC_F,      KC_G,     KC_MINS,
    KC_LSFT,       KC_Z,     KC_X,         KC_C,     KC_V,      KC_B,
                                                                          KC_LGUI,
                   KC_VOLU,                                     KC_LCTL, KC_LALT,
    MO(RAISE),     KC_VOLD,  KC_PSCR,                           MO(RAISE),KC_BSPC,

    // RIGHT
    MPASTE,     KC_6,     KC_7,     KC_8,      KC_9,       KC_0,    MO(RAISE),
    KC_RBRC,    KC_Y,     KC_U,     KC_I,      KC_O,       KC_P,    KC_BSLS,
    KC_EQL,     KC_H,     KC_J,     KC_K,      KC_L,       KC_SCLN, KC_QUOT,
                KC_N,     KC_M,     KC_COMM,   KC_DOT,     KC_SLSH, KC_RSFT,
    KC_RGUI,
    KC_RCTL,   KC_ENT,                                    KC_UP,
    KC_RALT,   KC_SPC,                         KC_LEFT,   KC_DOWN, KC_RIGHT
    ),

[RAISE]=
  KEYMAP(
    // LEFT
    FNOSTOGGLE, KC_F1,   KC_F2,  KC_F3,         KC_F4,        KC_F5, ___,
    ___,           ___,     ___,    ___,           ___,          ___,   ___,
    ___,           ___,     ___,    KC_MS_BTN2,    FNPANNING, ___,   ___,
    ___,           QK_REBOOT,   ___,    ___,           ___,   ___,
                                                   ___,
                   KC_F15,                         ___,   ___,
    ___,           KC_F14,  ___,                   ___,   ___,

    // RIGHT
    ___,   KC_F6, KC_F7,   KC_F8,   KC_F9,    KC_F10,   ___,
    ___,   ___,   ___,     ___,     ___,      ___,      ___,
    ___,   ___,   ___,     ___,     ___,      ___,      ___,
           ___,   ___,     KC_MPRV, KC_MNXT,  KC_MPLY,  ___,
    ___,
    ___,   ___,                               KC_PGUP,
    ___,   ___,                      KC_HOME, KC_PGDN,  KC_END
),

};

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // Hold down shift while pressing to cut rather than copy
    case FNCOPYCUT:
      if (record->event.pressed) {
          int8_t shifted = get_mods() & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));

          // Implicitly release the shift key so that it doesn't
          // mess with the macro that we play back
          unregister_mods(shifted);

          return process_record_user(shifted ? MCUT: MCOPY, record);
      }
      return false;

    case FNPANNING:
      if (record->event.pressed) {
#ifdef MOUSEKEY_ENABLE
#if TOUCHPAD_IS_CIRQUE
        if (IS_RELEASED(record->event)) {
          trackpad_set_mode(MovePointer);
        } else {
          trackpad_set_mode(Panning);
        }
#endif
#endif
      }
      return false;

    case FNOSTOGGLE:
      if (record->event.pressed) {
        is_mac = !is_mac;
        halfdeck_blink_led(is_mac ? 3 : 1);
      }
      return false;

    case MCOPY:
      if (record->event.pressed) {
        if (is_mac_host()) {
          SEND_STRING(SS_LGUI("c"));
        } else {
          SEND_STRING(SS_DOWN(X_LCTL) SS_TAP(X_INSERT) SS_UP(X_LCTL));
        }
      }
      return false;

    case MCUT:
      if (record->event.pressed) {
        if (is_mac_host()) {
          SEND_STRING(SS_LGUI("x"));
        } else {
          SEND_STRING(SS_DOWN(X_LSFT) SS_TAP(X_DEL) SS_UP(X_LSFT));
        }
      }
      return false;

    case MPASTE:
      if (record->event.pressed) {
        if (is_mac_host()) {
          SEND_STRING(SS_LGUI("v"));
        } else {
          SEND_STRING(SS_DOWN(X_LSFT) SS_TAP(X_INSERT) SS_UP(X_LSFT));
        }
      }
      return false;
  }
  return true;
}


void led_set_user(uint8_t usb_led) {
}

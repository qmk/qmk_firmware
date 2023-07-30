/* Copyright 2022 Nathan Kessler <nathant93@gmail.com> */

#include QMK_KEYBOARD_H
#include "action_layer.h"
#include "version.h"
#include "keymap_dvorak.h"
#include <sendstring_dvorak.h>

#define _BASE 0
#define _SYM 1
#define _NAV 2
#define _UTIL 3

// Shift keys on the home row
#define SH_DV_U SFT_T(DV_U)
#define SH_DV_H SFT_T(DV_H)

// Symbol layer access
#define SYM_I LT(_SYM, DV_I)
#define SYM_D LT(_SYM, DV_D)
#define SYM_DOWN LT(_SYM, KC_DOWN)
#define MO_SYM MO(_SYM)

#define MO_UTIL MO(_UTIL)

// Navigation layer / arrow keys
#define NAV_E LT(_NAV, DV_E)

// Ctrl+Shift+C and Ctrl+Shift+V
#define SH_CT_C LCTL(LSFT(DV_C))
#define SH_CT_V LCTL(LSFT(DV_V))

// Ctrl tap/hold
#define CT_BSPC CTL_T(KC_BSPC)
#define CT_SPC  CTL_T(KC_SPC)

// Alt tap/hold
#define ALT_DEL ALT_T(KC_DEL)
#define ALT_ENT ALT_T(KC_ENT)

// Shift+Enter tap/hold
#define SFT_ENT SFT_T(KC_ENT)

// GUI tap/hold
#define WIN_UP  GUI_T(KC_UP)
#define WINRGHT GUI_T(KC_RIGHT)

enum custom_keycodes {
    EQLRBRC = SAFE_RANGE, // can always be here
    L_FLASH,
    R_FLASH,
};

// Tap Dance declarations
enum {
    MR1,
};

void macro1(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count > 3) return;

    keyrecord_t kr;
    kr.event.pressed = false;
    uint16_t action  = DYN_REC_STOP;

    if (state->count == 1) {
        action = DYN_MACRO_PLAY1;
        kr.event.pressed = false;
    } else if (state->count == 2) {
        action = DYN_REC_STOP;
        kr.event.pressed = true;
    } else if (state->count == 3) {
        action = DYN_REC_START1;
        kr.event.pressed = false;
    }

    process_dynamic_macro(action, &kr);
}

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    [MR1] = ACTION_TAP_DANCE_FN(macro1),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_BASE] = LAYOUT_5x6(
//  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,          KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_ESC ,
    KC_TILD, DV_QUOT, DV_COMM, DV_DOT , DV_P   , DV_Y   ,          DV_F   , DV_G   , DV_C   , DV_R   , DV_L   , DV_SLSH,
    KC_TAB , DV_A   , DV_O   , NAV_E  , SH_DV_U, SYM_I  ,          SYM_D  , SH_DV_H, DV_T   , DV_N   , DV_S   , DV_MINS,
    KC_LSFT, DV_SCLN, DV_Q   , DV_J   , DV_K   , DV_X   ,          DV_B   , DV_M   , DV_W   , DV_V   , DV_Z   , KC_RSFT,
                                        KC_F13 , KC_F14 ,          KC_F13 , KC_F14 ,
                                        CT_BSPC, ALT_DEL,          SFT_ENT,  CT_SPC ,
                                        KC_DOWN, WIN_UP ,          WINRGHT, KC_LEFT,
                                        MO_UTIL, TD(MR1),          XXXXXXX, MO_UTIL
  ),

  [_SYM] = LAYOUT_5x6(

//  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    KC_ESC , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,          KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 ,
    _______, _______, _______, KC_EXLM, KC_AT  , KC_HASH,          EQLRBRC, KC_LPRN, KC_RPRN, DV_SLSH, _______, KC_F12 ,
    _______, _______, _______, KC_DLR , KC_PERC, _______,          DV_EQL , DV_LCBR, DV_RCBR, KC_BSLS, KC_PIPE, _______,
    _______, _______, _______, KC_CIRC, KC_AMPR, KC_ASTR,          DV_PLUS, DV_LBRC, DV_RBRC, DV_QUES, _______, _______,
                                        _______, _______,          _______, _______,
                                        _______, _______,          _______, _______,
                                        _______, _______,          _______, _______,
                                        _______, _______,          _______, _______

  ),

  [_NAV] = LAYOUT_5x6(
//  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______,
    _______, _______, KC_MRWD, KC_MPLY, KC_MFFD, _______,          KC_PGUP, KC_HOME, KC_UP  , KC_END , _______, _______,
    _______, _______, _______, _______, _______, _______,          KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,
    _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______,
                                        _______, _______,          _______, _______,
                                        _______, _______,          _______, _______,
                                        _______, _______,          _______, _______,
                                        _______, _______,          _______, _______
  ),
  [_UTIL] = LAYOUT_5x6(
//  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    QK_BOOT, _______, _______, _______, _______, L_FLASH,          R_FLASH, _______, _______, _______, _______, QK_BOOT,
    _______, _______, KC_MRWD, KC_MPLY, KC_MFFD, KC_VOLU,          _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, KC_VOLD,          _______, _______, _______, _______, _______, _______,
                                        _______, _______,          _______, _______,
                                        _______, _______,          _______, _______,
                                        _______, _______,          _______, _______,
                                        _______, _______,          _______, _______
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
   switch (keycode) {
    case EQLRBRC:
      if (record->event.pressed) {
        SEND_STRING("=> ");
      }
      break;
   case L_FLASH:
      if (record->event.pressed) {
        SEND_STRING("make handwired/dactyl_manuform/5x6:kesslern:avrdude-split-left"SS_TAP(X_ENTER));
        reset_keyboard();
      }
      break;
   case R_FLASH:
      if (record->event.pressed) {
        SEND_STRING("make handwired/dactyl_manuform/5x6:kesslern:avrdude-split-right"SS_TAP(X_ENTER));
        reset_keyboard();
      }
      break;
   }

  return true;
}

// Copyright 2022 Viatly Volkov (@vlkv)
// SPDX-License-Identifier: GPL-2.0-or-later

/*
qmk compile -kb avalanche/v4 -km default
qmk flash -kb avalanche/v4 -km default
*/

#include QMK_KEYBOARD_H

enum layer {
    _QWERTY,
    _LOWER,
    _RAISE,
};

#define FN_1 MO(_LOWER)
#define FN_2 MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
                 KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                                           KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_DEL ,
                 KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,                                           KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSPC,
        KC_ESC , KC_LCTL, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,                                           KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT, KC_UNDS,
                 KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_DEL , KC_LGUI, /**/  KC_INS , KC_BSPC, KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,
                                            KC_LGUI, KC_LALT, KC_LGUI, FN_1   , KC_ENT , /**/  FN_2   , KC_SPC , KC_BSPC, KC_RALT, KC_RGUI
    ),
    [_LOWER] = LAYOUT(
                 _______, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,                                           KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 ,
                 KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                                           KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_DEL ,
       _______ , KC_TILD, KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC,                                           KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE, _______,
                 _______, KC_EQL , KC_MINS, KC_PLUS, KC_LCBR, KC_RCBR, _______, _______, /**/  _______, _______, KC_LBRC, KC_RBRC, KC_SCLN, KC_COLN, KC_BSLS, _______,
                                            _______, _______, _______, _______, _______, /**/  _______, _______, _______, _______, _______
    ),
    [_RAISE] = LAYOUT(
                 _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                           KC_VOLD, KC_VOLU, KC_MUTE, XXXXXXX, XXXXXXX, XXXXXXX,
                 _______, KC_0,    KC_1,    KC_2,    KC_3,    KC_BSPC,                                           KC_PGUP, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        _______, _______, KC_0,    KC_4,    KC_5,    KC_6,    KC_DEL,                                            KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, XXXXXXX, XXXXXXX, XXXXXXX,
                 _______, KC_0,    KC_7,    KC_8,    KC_9,    KC_DOT,  _______, _______, /**/  _______, _______, KC_PGDN, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
                                            _______, _______, _______, _______, _______, /**/  _______, _______, _______, _______, _______
    ),
};

#ifdef OLED_ENABLE

#include "images.h"

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_0;
}

void shiftright(char* buf, int size, int num) {
  for (int i = size-1; i > 0; i--) {
    buf[i] >>= 1;
    if (buf[i-1] & 0x01) {
      buf[i] |= 0x80;
    }
  }
  buf[0] >>= 1;
}

// right to left, 8 bit vertical strips.
void mask(char* enable) {
  char rowenable[3];
  const char* data = display;
  int i = 0;
  char blockmask[2] = { 0x00, 0x00 };

  while (i < sizeof(display)) {
    if (i % 128 == 0) {
      // shift enable-mask right 1 at each row, reinitialize row copy
      if (i != 0) {
        shiftright(enable, 3, 2);
      }
      rowenable[0] = enable[0];
      rowenable[1] = enable[1];
      rowenable[2] = enable[2];
    }

    if (i % 8 == 0) {
      if (rowenable[2] & 0x01) {
        blockmask[1] = 0xff;
      } else {
        blockmask[1] = 0x00;
      }

      if (rowenable[2] & 0x02) {
        blockmask[0] = 0xff;
      } else {
        blockmask[0] = 0x00;
      }
      shiftright(rowenable, 3, 2);
    }

    uint8_t c = pgm_read_byte(data++);
    oled_write_raw_byte(c & blockmask[1], i++);
    shiftright(blockmask, 2, 1);
  }
}

void setmask(char* mask) {
  mask[0] = 0x00;
  mask[1] = 0x00;
  mask[2] = 0x00;

  uint8_t mod = get_mods() | get_oneshot_mods();
  if (mod & MOD_MASK_CTRL) {
    mask[1] |= 0xf0;
  }
  if (mod & MOD_MASK_ALT) {
    mask[1] |= 0x0f;
  }
  if (mod & MOD_MASK_GUI) {
    mask[0] |= 0xf0;
  }

  switch (get_highest_layer(layer_state)) {
    case _LOWER:
      mask[2] |= 0xf0;
      break;
    case _RAISE:
      mask[0] |= 0x0f;
      break;
  }
}

bool oled_task_user(void) {
    char m[3];
    setmask(m);
    mask(m);
    return false;
}

#endif


/*
Copyright 2016 Priyadi Iman Nurcahyo <priyadi@priyadi.net>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

enum layers {
  QWE, // qwerty
  COL, // colemak
  WOR, // workman
  DVO, // dvorak

  MOU, // mouse keys
  EMO, // emoji
  SYS, // system
};

enum keycodes {
  // default layout switcher
  LAY_QWE = SAFE_RANGE,
  LAY_COL,
  LAY_WOR,
  LAY_DVO,

  // layer switchers
  LYR_SYS,
  LYR_EMO,

  // os switchers
  OS_LIN,
  OS_WIN,
  OS_MAC,
};

// unicode map

enum unicode_name {
  GRIN, // grinning face 😊
  TJOY, // tears of joy 😂
  SMILE, // grining face with smiling eyes 😁
  HEART, // heart ❤
  EYERT, // smiling face with heart shaped eyes 😍
  CRY, // crying face 😭
  SMEYE, // smiling face with smiling eyes 😊
  UNAMU, // unamused 😒
  KISS, // kiss 😘
  HART2, // two hearts 💕
  WEARY, // weary 😩
  OKHND, // ok hand sign 👌
  PENSV, // pensive 😔
  SMIRK, // smirk 😏
  RECYC, // recycle ♻
  WINK, // wink 😉
  THMUP, // thumb up 👍
  THMDN, // thumb down 👎
  PRAY, // pray 🙏
  PHEW, // relieved 😌
  MUSIC, // musical notes
  FLUSH, // flushed 😳
  CELEB, // celebration 🙌
  CRY2, // crying face 😢
  COOL, // smile with sunglasses 😎
  NOEVS, // see no evil
  NOEVH, // hear no evil
  NOEVK, // speak no evil
  POO, // pile of poo
  EYES, // eyes
  VIC, // victory hand
  BHART, // broken heart
  SLEEP, // sleeping face
  SMIL2, // smiling face with open mouth & sweat
  HUNRD, // 100
  CONFU, // confused
  TONGU, // face with tongue & winking eye
  DISAP, // disappointed
  YUMMY, // face savoring delicious food
  CLAP, // hand clapping
  FEAR, // face screaming in fear
  HORNS, // smiling face with horns
  HALO, // smiling face with halo
  BYE, // waving hand
  SUN, // sun
  MOON, // moon
  SKULL, // skull
};

const uint32_t PROGMEM unicode_map[] = {
  [GRIN] = 0x1F600,
  [TJOY] = 0x1F602,
  [SMILE] = 0x1F601,
  [HEART] = 0x2764,
  [EYERT] = 0x1f60d,
  [CRY] = 0x1f62d,
  [SMEYE] = 0x1F60A,
  [UNAMU] = 0x1F612,
  [KISS] = 0x1F618,
  [HART2] = 0x1F495,
  [WEARY] = 0x1F629,
  [OKHND] = 0x1F44C,
  [PENSV] = 0x1F614,
  [SMIRK] = 0x1F60F,
  [RECYC] = 0x267B,
  [WINK] = 0x1F609,
  [THMUP] = 0x1F44D,
  [THMDN] = 0x1F44E,
  [PRAY] = 0x1F64F,
  [PHEW] = 0x1F60C,
  [MUSIC] = 0x1F3B6,
  [FLUSH] = 0x1F633,
  [CELEB] = 0x1F64C,
  [CRY2] = 0x1F622,
  [COOL] = 0x1F60E,
  [NOEVS] = 0x1F648,
  [NOEVH] = 0x1F649,
  [NOEVK] = 0x1F64A,
  [POO] = 0x1F4A9,
  [EYES] = 0x1F440,
  [VIC] = 0x270C,
  [BHART] = 0x1F494,
  [SLEEP] = 0x1F634,
  [SMIL2] = 0x1F605,
  [HUNRD] = 0x1F4AF,
  [CONFU] = 0x1F615,
  [TONGU] = 0x1F61C,
  [DISAP] = 0x1F61E,
  [YUMMY] = 0x1F60B,
  [CLAP] = 0x1F44F,
  [FEAR] = 0x1F631,
  [HORNS] = 0x1F608,
  [HALO] = 0x1F607,
  [BYE] = 0x1F44B,
  [SUN] = 0x2600,
  [MOON] = 0x1F314,
  [SKULL] = 0x1F480,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* qwerty */
    [QWE] = LAYOUT(
                                   KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_F21,  KC_PSCR, KC_SLCK, KC_PAUS,
                                   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,

    MO(EMO), MO(SYS),     KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  XXXXXXX, KC_BSPC,     KC_INS,  KC_HOME, KC_PGUP,     KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,
    KC_MNXT, KC_VOLU,     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,          XXXXXXX,     KC_DEL,  KC_END,  KC_PGDN,     KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
    KC_MPLY, KC_MUTE,     KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_BSLS, KC_ENT,               KC_UP,                KC_P4,   KC_P5,   KC_P6,   KC_PCMM,
    KC_MPRV, KC_VOLD,     KC_LSFT, KC_GRV,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          XXXXXXX, KC_RSFT,     KC_LEFT, TG(MOU), KC_RGHT,     KC_P1,   KC_P2,   KC_P3,   KC_PENT,
    KC_LGUI, KC_APP,      KC_LCTL,          KC_LALT,                            KC_SPC,                                               KC_RALT,          KC_RCTL,              KC_DOWN,              XXXXXXX, KC_P0,   KC_PDOT, XXXXXXX
    ),

    /* colemak */
    [COL] = LAYOUT(
                                   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,

    _______, _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MINS, KC_EQL,  _______, _______,     _______, _______, _______,     _______, _______, _______, _______,
    _______, _______,     _______, KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_LBRC, KC_RBRC,          _______,     _______, _______, _______,     _______, _______, _______, _______,
    _______, _______,     _______, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,          _______, _______,              _______,              _______, _______, _______, _______,
    _______, _______,     _______, _______, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          _______, _______,     _______, _______, _______,     _______, _______, _______, _______,
    _______, _______,     _______,          _______,                            _______,                                              _______,          _______,              _______,              _______, _______, _______, _______
    ),

    /* workman */
    [WOR] = LAYOUT(
                                   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,

    _______, _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MINS, KC_EQL,  _______, _______,     _______, _______, _______,     _______, _______, _______, _______,
    _______, _______,     _______, KC_Q,    KC_D,    KC_R,    KC_W,    KC_B,    KC_J,    KC_F,    KC_U,    KC_P,    KC_SCLN, KC_LBRC, KC_RBRC,          _______,     _______, _______, _______,     _______, _______, _______, _______,
    _______, _______,     _______, KC_A,    KC_S,    KC_H,    KC_T,    KC_G,    KC_Y,    KC_N,    KC_E,    KC_O,    KC_I,    KC_QUOT,          _______, _______,              _______,              _______, _______, _______, _______,
    _______, _______,     _______, _______, KC_Z,    KC_X,    KC_M,    KC_C,    KC_V,    KC_K,    KC_L,    KC_COMM, KC_DOT,  KC_SLSH,          _______, _______,     _______, _______, _______,     _______, _______, _______, _______,
    _______, _______,     _______,          _______,                            _______,                                              _______,          _______,              _______,              _______, _______, _______, _______
    ),

    /* dvorak */
    [DVO] = LAYOUT(
                                   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,

    _______, _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_LBRC, KC_RBRC, _______, _______,     _______, _______, _______,     _______, _______, _______, _______,
    _______, _______,     _______, KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH, KC_EQL,           _______,     _______, _______, _______,     _______, _______, _______, _______,
    _______, _______,     _______, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS,          _______, _______,              _______,              _______, _______, _______, _______,
    _______, _______,     _______, _______, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,             _______, _______,     _______, _______, _______,     _______, _______, _______, _______,
    _______, _______,     _______,          _______,                            _______,                                              _______,          _______,              _______,              _______, _______, _______, _______
    ),

    /* system */
    [SYS] = LAYOUT(
                                   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,

    _______, _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______,     _______, _______, _______, _______,
    _______, _______,     _______, LAY_QWE, OS_WIN,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,     _______, _______, _______,     _______, _______, _______, _______,
    _______, _______,     _______, _______, _______, LAY_DVO, _______, _______, _______, _______, LAY_WOR, OS_LIN,  _______, _______,          _______, _______,              _______,              _______, _______, _______, _______,
    _______, _______,     _______, _______, _______, _______, LAY_COL, _______, _______, _______, OS_MAC,  _______, _______, _______,          _______, _______,     _______, _______, _______,     _______, _______, _______, _______,
    _______, _______,     _______,          _______,                            _______,                                              _______,          _______,              _______,              _______, _______, _______, _______
    ),

    /* mouse keys */
    [MOU] = LAYOUT(
                                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,

    XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, KC_BTN4,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX,              KC_MS_U,              XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, KC_BTN5,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX,     KC_MS_L, _______, KC_MS_R,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    KC_BTN1, KC_BTN3,     KC_BTN2,          XXXXXXX,                            XXXXXXX,                                              XXXXXXX,          XXXXXXX,              KC_MS_D,              XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),

    /* emoji */
    [EMO] = LAYOUT(
                                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,

    XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX,     XXXXXXX, X(CRY2),X(WEARY),X(EYERT),X(SMIRK), X(TJOY), X(RECYC),X(UNAMU),X(MUSIC),X(OKHND),X(PENSV),XXXXXXX, XXXXXXX,          XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX,     XXXXXXX, X(PRAY),X(SMILE),X(SMIL2),X(FLUSH), X(GRIN), X(HEART),X(BYE),  X(KISS), X(CELEB),X(COOL), XXXXXXX,          XXXXXXX, XXXXXXX,              XXXXXXX,              XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX,X(SLEEP),X(CLAP), X(CRY),   X(VIC),  X(BHART),X(SUN),  X(SMEYE),X(WINK), X(MOON), X(CONFU),         XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX,     XXXXXXX,          XXXXXXX,                            XXXXXXX,                                              XXXXXXX,          XXXXXXX,              XXXXXXX,              XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),

    /*
    [XXX] = LAYOUT(
                                   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,

    _______, _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______,     _______, _______, _______, _______,
    _______, _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,     _______, _______, _______,     _______, _______, _______, _______,
    _______, _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,              _______,              _______, _______, _______, _______,
    _______, _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,     _______, _______, _______,     _______, _______, _______, _______,
    _______, _______,     _______,          _______,                            _______,                                              _______,          _______,              _______,              _______, _______, _______, _______
    ),
    */
};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    /* layout switcher */
    case LAY_QWE:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<QWE);
      }
      return false;
      break;
    case LAY_COL:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<COL);
      }
      return false;
      break;
    case LAY_WOR:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<WOR);
      }
      return false;
      break;
    case LAY_DVO:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<DVO);
      }
      return false;
      break;

    /* os switcher */
    case OS_LIN:
      set_unicode_input_mode(UC_LNX);
      return false;
      break;
    case OS_WIN:
      set_unicode_input_mode(UC_WINC);
      return false;
      break;
    case OS_MAC:
      set_unicode_input_mode(UC_OSX);
      return false;
      break;

  }
  return true;
}

void matrix_init_user() {
  set_unicode_input_mode(UC_LNX);
}

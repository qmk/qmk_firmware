#include QMK_KEYBOARD_H
#include "keymap_jp.h"
#include <stdio.h>

// レイヤーの定義
enum layers {
  _EUCALYN = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
  _MINECRAFT,
};

// マクロキーの定義
enum custom_keycodes {
  RAISE = SAFE_RANGE,
  LOWER,
  ESC_MHEN,
  SFT_I,
  SFT_T,
  CTL_E,
  CTL_N
};

// 複合キーを8文字までの変数に
// MINECRAFTレイヤーのみ
#define CAPTURE LGUI(KC_PSCR)
#define TO_MC TO(_MINECRAFT)
#define TO_EU TO(_EUCALYN)

// レイヤーごとにキーマップを定義
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_EUCALYN] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     ESC_MHEN,    KC_Q,    KC_W, JP_COMM,  JP_DOT, JP_SCLN,                         KC_M,    KC_R,    KC_D,    KC_Y,    KC_P, JP_MINS,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_TAB,    KC_A,    KC_O,   CTL_E,   SFT_I,    KC_U,                         KC_G,   SFT_T,   CTL_N,    KC_S,    KC_B, JP_QUOT,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LALT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_F,                         KC_H,    KC_J,    KC_K,    KC_L, JP_SLSH,  KC_DEL,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   LOWER,  KC_SPC,     KC_ENT,   RAISE, KC_BSPC\
                                      //`--------------------------'  `--------------------------'
  ),

  [_LOWER] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        KC_NO,   KC_P1,   KC_P2,   KC_P3,   KC_P4,   KC_P5,                        KC_P6,   KC_P7,   KC_P8,   KC_P9,   KC_P0,   KC_NO,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                      KC_HOME, KC_PGDN, KC_PGUP,  KC_END,   KC_NO,   KC_NO,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                      KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,   KC_NO,   KC_NO,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            KC_NO,   LOWER,   KC_NO,      KC_NO,   RAISE,   KC_NO\
                                      //`--------------------------'  `--------------------------'
    ),

  [_RAISE] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       JP_GRV, JP_TILD,   KC_NO,   JP_LT,   JP_GT, JP_COLN,                        KC_NO, JP_LPRN, JP_RPRN,   KC_NO,   KC_NO, JP_UNDS,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_NO, JP_AMPR,   JP_AT, JP_PLUS,  JP_EQL,   KC_NO,                      JP_CIRC, JP_LCBR, JP_RCBR,  JP_DLR, JP_EXLM, JP_DQUO,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_NO, JP_PIPE, JP_HASH, JP_ASTR, JP_PERC,   KC_NO,                        KC_NO, JP_LBRC, JP_RBRC, JP_BSLS, JP_QUES,   KC_NO,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            KC_NO,   LOWER,   KC_NO,      KC_NO,   RAISE,   KC_NO\
                                      //`--------------------------'  `--------------------------'
  ),

  [_ADJUST] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        KC_NO,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,   KC_NO,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_NO,  KC_F11,  KC_F12,   KC_NO,   KC_NO,   KC_NO,                        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   TO_MC,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            KC_NO,   LOWER,   KC_NO,      KC_NO,   RAISE,   KC_NO\
                                      //`--------------------------'  `--------------------------'
  ),

  [_MINECRAFT] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,   KC_NO,    KC_Q,    KC_W,    KC_E,    KC_T,                        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_TAB,   KC_NO,    KC_A,    KC_S,    KC_D,    KC_F,                        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      JP_SLSH,   KC_F1,   KC_F5,  KC_F11,   KC_NO,  CAPTURE,                        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  TO_EU,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LCTL, KC_LSFT,  KC_SPC,      KC_NO,   KC_NO,   KC_NO\
                                      //`--------------------------'  `--------------------------'
  ),

};

// OLEDの設定
#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (layer_state) {
        case _EUCALYN:
            oled_write_ln_P(PSTR("Eucalyn"), false);
            break;
        case _LOWER:
            oled_write_ln_P(PSTR("Lower"), false);
            break;
        case _RAISE:
            oled_write_ln_P(PSTR("Raise"), false);
            break;
        case _ADJUST:
            oled_write_ln_P(PSTR("Adjust"), false);
            break;
        case _MINECRAFT:
            oled_write_ln_P(PSTR("Minecraft"), false);
            break;
    }
}


char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);
}

void oled_render_keylog(void) {
    oled_write(keylog_str, false);
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
        oled_render_keylog();
    } else {
        oled_render_logo();
    }
    return false;
}

static bool lower_pressed = false;
static bool raise_pressed = false;


static bool sft_i_pressed = false;
static uint16_t sft_i_pressed_time = 0;

static bool sft_t_pressed = false;
static uint16_t sft_t_pressed_time = 0;

static bool ctl_e_pressed = false;
static uint16_t ctl_e_pressed_time = 0;

static bool ctl_n_pressed = false;
static uint16_t ctl_n_pressed_time = 0;

// マウス用に長押しで通常の修飾キーに
// 逆にスペース、エンターの押しっぱなしができなくなるのか
void matrix_scan_user(void) {
  if (sft_i_pressed && timer_elapsed(sft_i_pressed_time) > TAPPING_TERM) {
    register_code(KC_LSFT);
    sft_i_pressed = false;
  }
  if (sft_t_pressed && timer_elapsed(sft_t_pressed_time) > TAPPING_TERM) {
    register_code(KC_LSFT);
    sft_t_pressed = false;
  }
  if (ctl_e_pressed && timer_elapsed(ctl_e_pressed_time) > TAPPING_TERM) {
    register_code(KC_LCTL);
    ctl_e_pressed = false;
  }
  if (ctl_n_pressed && timer_elapsed(ctl_n_pressed_time) > TAPPING_TERM) {
    register_code(KC_LCTL);
    ctl_n_pressed = false;
  }
};

static void user_mt(keyrecord_t *record, uint16_t modcode, uint16_t keycode, bool *modifier_pressed, uint16_t *modifier_pressed_time, bool tapping_term_disable) {
  if (record->event.pressed) {
    *modifier_pressed = true;
    *modifier_pressed_time = record->event.time;
  } else {
    if (!*modifier_pressed) unregister_code(modcode);
    if (*modifier_pressed && (tapping_term_disable || (timer_elapsed(*modifier_pressed_time) < TAPPING_TERM))) {
      register_code(keycode);
      unregister_code(keycode);
    }
    *modifier_pressed = false;
  }
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case SFT_I:
      user_mt(record, KC_LSFT, KC_I, &sft_i_pressed, &sft_i_pressed_time, true);
      return false;
      break;
    case SFT_T:
      user_mt(record, KC_LSFT, KC_T, &sft_t_pressed, &sft_t_pressed_time, true);
      return false;
      break;
    case CTL_E:
      user_mt(record, KC_LCTL,  KC_E, &ctl_e_pressed, &ctl_e_pressed_time, true);
      return false;
      break;
    case CTL_N:
      user_mt(record, KC_LCTL,  KC_N, &ctl_n_pressed, &ctl_n_pressed_time, true);
      return false;
      break;
    case ESC_MHEN:
      if (record->event.pressed){
        tap_code(KC_ESC);
        tap_code(KC_MHEN);
        tap_code(KC_LANG2);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        lower_pressed = true;
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
        if (lower_pressed) {
          tap_code(KC_MHEN);
          tap_code(KC_LANG2);
        }
        lower_pressed = false;
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        raise_pressed = true;
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
        if (raise_pressed) {
          tap_code(KC_HENK);
          tap_code(KC_LANG1);
        }
        raise_pressed = false;
      }
      return false;
      break;
    default:  // case: defaultではない.。マクロキーでない他のすべてのキー
      if (record->event.pressed) {
        lower_pressed = false;
        raise_pressed = false;
        if (ctl_e_pressed || ctl_n_pressed) {
          register_code(KC_LCTL);
        }
        if (sft_i_pressed || sft_t_pressed) {
          register_code(KC_LSFT);
        }
        sft_i_pressed = false;
        sft_t_pressed = false;
        ctl_e_pressed = false;
        ctl_n_pressed = false;
      }
      break;
  }
  return true;
};

#endif // OLED_ENABLE

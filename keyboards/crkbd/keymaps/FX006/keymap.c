/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>
*/

#include QMK_KEYBOARD_H
#include <stdio.h>
#include <keymap_german.h>
#include <keymap_HomeRowMod.h>

/* Define the layer names */
enum layers {
  NEO_BASE,
  _NAVL,
  _NAVR,
  _FL_Mouse,
  _SYM,
  _NUM,
  _RGB,
  QWERZ_BASE //not linked in jet
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [QWERZ_BASE] = LAYOUT_split_3x6_3(
  //|--------|--------|--------|--------|--------|--------|                    |--------|--------|--------|--------|--------|--------|
    KC_ESC,  DE_Q,    DE_W,    DE_E,    DE_R,    DE_T,                         DE_Z,    DE_U,    DE_I,    DE_O,    DE_P,    DE_UDIA,
    KC_TAB,  HRQ_L1,  HRQ_L2,  HRQ_L3,  HRQ_L4,  DE_G,                         DE_H,    HRQ_R1,  HRQ_R2,  HRQ_R3,  HRQ_R4,  DE_ADIA,
    KC_LGUI, DE_Y,    DE_X,    DE_C,    DE_V,    DE_B,                         DE_N,    DE_M,    DE_COMM, DE_DOT,  DE_MINS, DE_SS,
  //Left Thumb
    LT(_NUM,KC_TAB),
    LT(_NAVL,KC_DEL),
    LT(_SYM,KC_BSPC),
  //Right Thumb
    LT(_SYM,KC_SPC),
    LT(_NAVR,KC_ENT),
    LT(_FL_Mouse,KC_ENT)
  ),

  [NEO_BASE] = LAYOUT_split_3x6_3(
  //|--------|--------|--------|--------|--------|--------|                    |--------|--------|--------|--------|--------|--------|
    KC_ESC,  DE_X,    DE_V,    DE_L,    DE_C,    DE_W,                         DE_K,    DE_H,    DE_G,    DE_F,    DE_Q,    DE_SS,
    KC_TAB,  HRN_L1,  HRN_L2,  HRN_L3,  HRN_L4,  DE_O,                         DE_S,    HRN_R1,  HRN_R2,  HRN_R3,  HRN_R4,  DE_Y,
    KC_LGUI, DE_UDIA, DE_ODIA, DE_ADIA, DE_P,    DE_Z,                         DE_B,    DE_M,    DE_COMM, DE_DOT,  DE_J,    XXXXXXX,
  //Left Thumb
  //Left Thumb
    LT(_NUM,KC_TAB),
    LT(_NAVL,KC_DEL),
    LT(_SYM,KC_BSPC),
  //Right Thumb
    LT(_SYM,KC_SPC),
    LT(_NAVR,KC_ENT),
    LT(_FL_Mouse,KC_ENT)
    ),

  [_NAVR] = LAYOUT_split_3x6_3(
  //|--------|--------|--------|--------|--------|--------|                    |--------|--------|--------|--------|--------|--------|
    _______,  DE_ASTR, DE_7,    DE_8,    DE_9,    DE_PLUS,                      KC_PGUP, KC_HOME, KC_UP,   KC_END,  _______, _______,
    _______,  DE_SLSH, DE_4,    DE_5,    DE_6,    DE_MINS,                      KC_PGDN, KC_LEFT, KC_DOWN, KC_RIGHT,_______, _______,
    _______,  DE_0,    DE_1,    DE_2,    DE_3,    DE_EQL,                       _______, _______, _______, _______, _______, _______,
  //Left Thumb
    DE_COMM,
    DE_DOT,
    _______,
  //Right Thumb
    _______,
    _______,
    _______
  ),

  [_NAVL] = LAYOUT_split_3x6_3(
  //|--------|--------|--------|--------|--------|--------|                    |--------|--------|--------|--------|--------|--------|
    _______,  _______, KC_END,  KC_UP,   KC_HOME, KC_PGUP,                      DE_ASTR, DE_7,    DE_8,    DE_9,    DE_PLUS, _______,
    _______,  _______, KC_RIGHT,KC_DOWN, KC_LEFT, KC_PGDN,                      DE_SLSH, DE_4,    DE_5,    DE_6,    DE_MINS, _______,
    _______,  _______, _______, _______, _______, _______,                      DE_0,    DE_1,    DE_2,    DE_3,    DE_EQL,  _______,
  //Left Thumb
    _______,
    _______,
    _______,
  //Right Thumb
    _______,
    DE_COMM,
    DE_DOT
  ),

  [_FL_Mouse] = LAYOUT_split_3x6_3(
  //|--------|--------|--------|--------|--------|--------|                    |--------|--------|--------|--------|--------|--------|
    KC_ESC,  XXXXXXX, DE_7,    DE_8,    DE_9,    XXXXXXX,                      KC_MS_WH_UP, KC_MS_BTN1, KC_MS_UP, KC_MS_BTN2, XXXXXXX, XXXXXXX,
    KC_TAB,  XXXXXXX, DE_4,    DE_5,    DE_6,    XXXXXXX,                      KC_MS_WH_DOWN, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT,XXXXXXX, XXXXXXX,
    KC_LGUI, DE_0,    DE_1,    DE_2,    DE_3,    XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //Left Thumb
    _______,
    _______,
    _______,
  //Right Thumb
    _______,
    _______,
    _______
  ),

  [_SYM] = LAYOUT_split_3x6_3(
  //|--------|--------|--------|--------|--------|--------|                    |--------|--------|--------|--------|--------|--------|
    KC_ESC,  XXXXXXX, DE_UNDS, DE_LBRC, DE_RBRC, DE_CIRC,                      DE_EXLM, DE_LABK, DE_RABK, DE_EQL,  DE_AMPR, XXXXXXX,
    KC_TAB,  DE_BSLS, DE_SLSH, DE_LCBR, DE_RCBR, DE_ASTR,                      DE_QUES, DE_LPRN, DE_RPRN, DE_MINS, DE_COLN, DE_AT,
    KC_LGUI, DE_HASH, DE_DLR,  DE_PIPE, DE_TILD, DE_GRV,                       DE_PLUS, DE_PERC, DE_DQUO, DE_QUOT, XXXXXXX, XXXXXXX,
  //Left Thumb
    _______,
    _______,
    _______,
  //Right Thumb
    _______,
    _______,
    _______
  ),

  [_NUM] = LAYOUT_split_3x6_3(
  //|--------|--------|--------|--------|--------|--------|                    |--------|--------|--------|--------|--------|--------|
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        KC_F6,   KC_F6,   KC_F6,   KC_F6,   KC_F10,  KC_F11,
    _______, DE_1,    DE_2,    DE_3,    DE_4,    DE_5,                         DE_6,    DE_7,    DE_8,    DE_9,    DE_0,    KC_F12,
    _______, XXXXXXX, XXXXXXX, DE_COMM, DE_DOT,  XXXXXXX,                      DE_EQL,  DE_PLUS, DE_MINS, DE_ASTR, DE_SLSH, XXXXXXX,
  //Left Thumb
    _______,
    _______,
    _______,
  //Right Thumb  
    _______,
    _______,
    _______
  ),

  [_RGB] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  )
};


#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

#define L_BASE 0
#define L_LOWER 2
#define L_RAISE 4
#define L_ADJUST 8

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (layer_state) {
        case L_BASE:
            oled_write_ln_P(PSTR("Default"), false);
            break;
        case L_LOWER:
            oled_write_ln_P(PSTR("Lower"), false);
            break;
        case L_RAISE:
            oled_write_ln_P(PSTR("Raise"), false);
            break;
        case L_ADJUST:
        case L_ADJUST|L_LOWER:
        case L_ADJUST|L_RAISE:
        case L_ADJUST|L_LOWER|L_RAISE:
            oled_write_ln_P(PSTR("Adjust"), false);
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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    set_keylog(keycode, record);
  }
  return true;
}
#endif // OLED_ENABLE

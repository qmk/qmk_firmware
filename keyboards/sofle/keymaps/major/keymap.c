#include QMK_KEYBOARD_H

#include <stdio.h>
#include "quantum.h"

/* layers */
enum sofle_layers {
    _QWERTY = 0,
    _UPPER  = 1,
    _LOWER  = 2,
    _ADJUST = 3,
    // MIRYOKU
    _MIRYOKU_BASE  = 4,
    _MIRYOKU_NUM   = 5,
    _MIRYOKU_NAV   = 6,
    _MIRYOKU_FUN   = 7,
    _MIRYOKU_MEDIA = 8,
    _MIRYOKU_MOUSE = 9,
    _MIRYOKU_SYM   = 10,
    _TRANSPARENT   = 11,
};

enum custom_keycodes {
    KC_QWERTY = SAFE_RANGE,
    KC_LOWER,
    KC_UPPER,
    KC_ADJUST,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


/*
 * QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |MRYOKU|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | ESC  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  | Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Space  /       \Enter \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */

[_QWERTY] = LAYOUT(
  KC_GRV,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                                KC_6,     KC_7,    KC_8,    KC_9,     KC_0,   DF(_MIRYOKU_BASE),
  KC_ESC,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                                KC_Y,     KC_U,    KC_I,    KC_O,     KC_P,       KC_BSPC,
  KC_TAB,   KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                                KC_H,     KC_J,    KC_K,    KC_L,    KC_SCLN,     KC_QUOT,
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_MUTE,           KC_NO,      KC_N,     KC_M,   KC_COMM, KC_DOT,   KC_SLSH,     KC_RSFT,
                  KC_LGUI,  KC_LALT, KC_LCTL,   MO(_LOWER), KC_SPC,      KC_ENT,  MO(_UPPER),   KC_RCTL, KC_RALT, KC_RGUI
),


[_UPPER] = LAYOUT(
  _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,                              KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11, 
  KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,                               KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_F12, 
  _______,  KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,                            KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  KC_PIPE, 
  _______,  KC_EQL,   KC_MINS,  KC_PLUS,  KC_LCBR,  KC_RCBR, _______,        _______,   KC_LBRC,  KC_RBRC,  KC_SCLN,  KC_COLN,  KC_NUHS,  _______, 
                      _______,  _______,  _______,   _______, _______,      _______,  _______,      _______, _______, _______
),

[_LOWER] = LAYOUT(
  _______,  _______,     _______,     _______,    _______,    _______,                             _______,    _______,      _______,     _______,      _______,     _______, 
  _______,  KC_INS,      KC_PSCR,     KC_APP,      KC_NO,     KC_NO,                               KC_PGUP,  LCTL(KC_LEFT),  KC_UP,    LCTL(KC_RGHT), LCTL(KC_BSPC), KC_BSPC, 
  _______,  KC_NO,       KC_LALT,     KC_LCTL,    KC_LSFT,    KC_CAPS,                             KC_PGDN,    KC_LEFT,      KC_DOWN,     KC_RGHT,      KC_DEL,      KC_BSPC, 
  _______,  LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V),   KC_NO,    _______,         _______,  KC_NO,      KC_HOME,      KC_NO,       KC_END,        KC_NO,      _______, 
                         _______,     _______,    _______,     _______,  _______,       _______,  _______,     _______,      _______,     _______
),

[_ADJUST] = LAYOUT(
  KC_NO,    KC_NO,  KC_NO,    KC_NO, KC_NO,  KC_NO,                      KC_NO, KC_NO,   KC_NO,    KC_NO,  KC_NO, KC_NO, 
  QK_BOOT,  KC_NO,  DF(4),   CG_TOGG,KC_NO,  KC_NO,                      KC_NO, KC_NO,   KC_NO,    KC_NO,  KC_NO, KC_NO,
  KC_NO,    KC_NO,  CG_TOGG,  KC_NO, KC_NO,  KC_NO,                      KC_NO, KC_VOLD, KC_MUTE, KC_VOLU, KC_NO, KC_NO, 
  KC_NO,    KC_NO,  KC_NO,    KC_NO, KC_NO,  KC_NO,  KC_NO,      KC_NO,  KC_NO, KC_MPRV, KC_MPLY, KC_MNXT, KC_NO, KC_NO, 
                _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______
),

/*
 * MIRYOKU_BASE/ColemakDH - customised to make use of all available keys (for better or worse?)
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |QWERTY|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  `¬  |   Q  |   W  |   F  |   P  |   B  |                    |   J  |   L  |   U  |   Y  |  '"  | Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  \|  | g(A) | a(R) | c(S) | s(T) |   G  |-------.    ,-------|   M  | s(N) | c(E) | a(I) | g(O) |  #~  |
 * |------+------+------+------+------+------|  PLAY |    |  PLAY |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   D  |   V  |-------|    |-------|   K  |   H  |  ,<  |  .>  |  /?  |  ;:  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | Esc  |Space | /  Tab  /       \Enter \  | Bspc | Del  | RAlt | RGUI |
 *            |      |      |MEDIA | NAV  |/ MOUSE /         \ SYM  \ |  NUM | FUN  |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */

[_MIRYOKU_BASE] = LAYOUT(
  KC_ESC,       KC_1,         KC_2,         KC_3,         KC_4,     KC_5,                                                         KC_6,     KC_7,       KC_8,           KC_9,        KC_0,    DF(_QWERTY), 
  KC_GRV,       KC_Q,         KC_W,         KC_F,         KC_P,     KC_B,                                                         KC_J,     KC_L,       KC_U,           KC_Y,       KC_QUOT,    KC_BSPC, 
  KC_NUBS,  LGUI_T(KC_A), LALT_T(KC_R), LCTL_T(KC_S), LSFT_T(KC_T), KC_G,                                                         KC_M, LSFT_T(KC_N), LCTL_T(KC_E), LALT_T(KC_I), RGUI_T(KC_O), KC_NUHS, 
  KC_LSFT,      KC_Z,         KC_X,         KC_C,         KC_D,     KC_V,   KC_MPLY,                                    KC_MPLY,  KC_K,     KC_H,      KC_COMM,        KC_DOT,     KC_SLSH,    KC_SCLN, 
                            KC_LGUI,      KC_LALT,    LT(8, KC_ESC), LT(6, KC_SPC), LT(9, KC_TAB),      LT(10, KC_ENT), LT(5, KC_BSPC), LT(7, KC_DEL), KC_RALT,        KC_RGUI
),

/* 
*  NB: ALL OTHER _MIRYOKU_* LAYERS SHOULD BE 1:1 with https://github.com/manna-harbour/miryoku/tree/master/docs/reference
*  EXCEPT FOR PRESERVING LAYER TOGGLE 
*  AND MISSING SOME BLUETOOTH/EXT POWER ONES AND REDO
*  ALSO DID NOT IMPLEMENT EXTRAS (ADDITIONAL FEATURES, BUTTON LAYER)
*/

[_MIRYOKU_NAV] = LAYOUT(
  _______, _______, _______, _______, _______,  _______,                            _______, _______, _______, _______, _______,  DF(0),
  _______, _______, _______, _______, _______,  _______,                            _______, KC_PSTE, KC_COPY, KC_CUT,  KC_UNDO, _______,
  _______, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT,  _______,                            KC_CAPS, KC_LEFT, KC_DOWN, KC_UP,  KC_RIGHT, _______,
  _______, _______, _______, _______, _______,  _______, _______,         _______,  KC_INS,  KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______,
                    _______, _______, _______,   _______, _______,       KC_ENTER, KC_BSPC,  KC_DEL, _______, _______
),

[_MIRYOKU_MOUSE] = LAYOUT(
  _______, _______, _______, _______, _______,  _______,                             _______, _______, _______, _______, _______,  DF(0),
  _______, _______, _______, _______, _______,  _______,                             _______, KC_PSTE, KC_COPY, KC_CUT,  KC_UNDO, _______,
  _______, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT,  _______,                             _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, _______,
  _______, _______, _______, _______, _______,  _______, _______,          _______,  _______, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, _______,
                    _______, _______, _______,   _______, _______,        KC_BTN2, KC_BTN1,   KC_BTN3, _______, _______
),

[_MIRYOKU_MEDIA] = LAYOUT(
  _______, _______, _______, _______, _______,  _______,                            _______, _______, _______, _______, _______,  DF(0),
  _______, _______, _______, _______, _______,  _______,                            RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, _______,
  _______, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT,  _______,                            _______, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, _______,
  _______, _______, _______, _______, _______,  _______, _______,         _______,  _______, _______, _______, _______, _______, _______,
                    _______, _______, _______,   _______, _______,       KC_MSTP, KC_MPLY,   KC_MUTE, _______, _______
),

[_MIRYOKU_SYM] = LAYOUT(
  _______, _______, _______, _______, _______,  _______,                          _______, _______, _______, _______, _______,  DF(0),
  _______, KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN,  KC_RCBR,                          _______, _______, _______, _______, _______, _______,
  _______, KC_COLN, KC_DLR,  KC_PERC, KC_CIRC,  KC_PLUS,                          _______, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, _______,
  _______, KC_TILD, KC_EXLM,  KC_AT,  KC_HASH,  KC_PIPE, _______,       _______,  _______, _______, _______, _______, _______, _______,
                    _______, _______, KC_LPRN,   KC_RPRN, KC_UNDS,     _______, _______,   _______, _______, _______
),

[_MIRYOKU_NUM] = LAYOUT(
  _______, _______, _______, _______, _______,  _______,                              _______, _______, _______, _______, _______,  DF(0),
  _______, KC_LBRC,   KC_7,    KC_8,    KC_9,   KC_RBRC,                              _______,   KC_7,    KC_8,    KC_9,  _______, _______,
  _______, KC_SCLN,   KC_4,    KC_5,    KC_6,   KC_EQL,                               _______,   KC_4,    KC_5,    KC_6,  KC_LGUI, _______,
  _______, KC_GRV,    KC_1,    KC_2,    KC_3,   KC_NUBS, _______,           _______,  _______,   KC_1,    KC_2,    KC_3,  _______, _______,
                     KC_DOT,   KC_0,  KC_MINS,   _______, _______,         _______, _______,   _______,   KC_0,   _______
),


[_MIRYOKU_FUN] = LAYOUT(
  _______, _______, _______, _______, _______,  _______,                        EE_CLR, _______, _______, _______, _______,  DF(0),
  _______,  KC_F12,   KC_F7,   KC_F8,   KC_F9,  KC_PSCR,                        _______, _______, _______, _______, _______, _______,
  _______,  KC_F11,   KC_F4,   KC_F5,   KC_F6,  KC_SCRL,                        _______, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, _______,
  _______,  KC_F10,   KC_F1,   KC_F2,   KC_F3,  KC_PAUS, _______,     _______,  _______, _______, _______, _______, _______, _______,
                    _______, _______, _______,   KC_SPC,   KC_TAB,   _______, _______,   _______, _______, _______
),

[_TRANSPARENT] = LAYOUT(
  _______, _______, _______, _______, _______,  _______,                            _______, _______, _______, _______, _______,  DF(0),
  _______, _______, _______, _______, _______,  _______,                            _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______,  _______,                            _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______,  _______, _______,         _______,  _______, _______, _______, _______, _______, _______,
                    _______, _______, _______,   _______, _______,       _______, _______,   _______, _______, _______
),
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _UPPER, _ADJUST);
}
/* end layers */

/* encoder */
#if defined(ENCODER_ENABLE)
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_RIGHT);
        } else {
            tap_code(KC_LEFT);
        }
    } else if (index == 1) {
        if (clockwise) {
            tap_code(KC_DOWN);
        } else {
            tap_code(KC_UP);
        }
    }
    // stop processing after this - avoids default volume behaviours from running simultaneously
    return false;
};

#endif // defined(ENCODER_ENABLE)
/* end encoder */

/* OLED/luna */
#ifdef OLED_ENABLE

/* settings */
#    define MIN_WALK_SPEED 10
#    define MIN_RUN_SPEED 40

/* advanced settings */
#    define ANIM_FRAME_DURATION 200 // how long each frame lasts in ms
#    define ANIM_SIZE 96            // number of bytes in array. If you change sprites, minimize for adequate firmware size. max is 1024

/* timers */
uint32_t anim_timer = 0;

/* current frame */
uint8_t current_frame = 0;

/* status variables */
int   current_wpm = 0;
led_t led_usb_state;

bool isSneaking = false;
bool isJumping  = false;
bool showedJump = true;

/* logic */
static void render_luna(int LUNA_X, int LUNA_Y) {
    /* Sit */
    static const char PROGMEM sit[2][ANIM_SIZE] = {/* 'sit1', 32x22px */
                                                   {
                                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1c, 0x02, 0x05, 0x02, 0x24, 0x04, 0x04, 0x02, 0xa9, 0x1e, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x08, 0x68, 0x10, 0x08, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x06, 0x82, 0x7c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x0c, 0x10, 0x10, 0x20, 0x20, 0x20, 0x28, 0x3e, 0x1c, 0x20, 0x20, 0x3e, 0x0f, 0x11, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                   },

                                                   /* 'sit2', 32x22px */
                                                   {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1c, 0x02, 0x05, 0x02, 0x24, 0x04, 0x04, 0x02, 0xa9, 0x1e, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x90, 0x08, 0x18, 0x60, 0x10, 0x08, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x0e, 0x82, 0x7c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x0c, 0x10, 0x10, 0x20, 0x20, 0x20, 0x28, 0x3e, 0x1c, 0x20, 0x20, 0x3e, 0x0f, 0x11, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};

    /* Walk */
    static const char PROGMEM walk[2][ANIM_SIZE] = {/* 'walk1', 32x22px */
                                                    {
                                                        0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x10, 0x90, 0x90, 0x90, 0xa0, 0xc0, 0x80, 0x80, 0x80, 0x70, 0x08, 0x14, 0x08, 0x90, 0x10, 0x10, 0x08, 0xa4, 0x78, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x08, 0xfc, 0x01, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x18, 0xea, 0x10, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1c, 0x20, 0x20, 0x3c, 0x0f, 0x11, 0x1f, 0x03, 0x06, 0x18, 0x20, 0x20, 0x3c, 0x0c, 0x12, 0x1e, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                    },

                                                    /* 'walk2', 32x22px */
                                                    {
                                                        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x20, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x28, 0x10, 0x20, 0x20, 0x20, 0x10, 0x48, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x20, 0xf8, 0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x10, 0x30, 0xd5, 0x20, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x20, 0x30, 0x0c, 0x02, 0x05, 0x09, 0x12, 0x1e, 0x02, 0x1c, 0x14, 0x08, 0x10, 0x20, 0x2c, 0x32, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                    }};

    /* Run */
    static const char PROGMEM run[2][ANIM_SIZE] = {/* 'run1', 32x22px */
                                                   {
                                                       0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x08, 0x08, 0xc8, 0xb0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x40, 0x40, 0x3c, 0x14, 0x04, 0x08, 0x90, 0x18, 0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0xc4, 0xa4, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc8, 0x58, 0x28, 0x2a, 0x10, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x09, 0x04, 0x04, 0x04, 0x04, 0x02, 0x03, 0x02, 0x01, 0x01, 0x02, 0x02, 0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                   },

                                                   /* 'run2', 32x22px */
                                                   {
                                                       0x00, 0x00, 0x00, 0xe0, 0x10, 0x10, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x78, 0x28, 0x08, 0x10, 0x20, 0x30, 0x08, 0x10, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x10, 0xb0, 0x50, 0x55, 0x20, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28, 0x37, 0x02, 0x1e, 0x20, 0x20, 0x18, 0x0c, 0x14, 0x1e, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                   }};

    /* Bark */
    static const char PROGMEM bark[2][ANIM_SIZE] = {/* 'bark1', 32x22px */
                                                    {
                                                        0x00, 0xc0, 0x20, 0x10, 0xd0, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x40, 0x3c, 0x14, 0x04, 0x08, 0x90, 0x18, 0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc8, 0x48, 0x28, 0x2a, 0x10, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28, 0x37, 0x02, 0x02, 0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                    },

                                                    /* 'bark2', 32x22px */
                                                    {
                                                        0x00, 0xe0, 0x10, 0x10, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x40, 0x40, 0x2c, 0x14, 0x04, 0x08, 0x90, 0x18, 0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x48, 0x28, 0x2a, 0x10, 0x0f, 0x20, 0x4a, 0x09, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28, 0x37, 0x02, 0x02, 0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                    }};

    /* Sneak */
    static const char PROGMEM sneak[2][ANIM_SIZE] = {/* 'sneak1', 32x22px */
                                                     {
                                                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x40, 0x40, 0x80, 0x00, 0x80, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x21, 0xf0, 0x04, 0x02, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x04, 0x04, 0x04, 0x03, 0x01, 0x00, 0x00, 0x09, 0x01, 0x80, 0x80, 0xab, 0x04, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1c, 0x20, 0x20, 0x3c, 0x0f, 0x11, 0x1f, 0x02, 0x06, 0x18, 0x20, 0x20, 0x38, 0x08, 0x10, 0x18, 0x04, 0x04, 0x02, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00,
                                                     },

                                                     /* 'sneak2', 32x22px */
                                                     {
                                                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xa0, 0x20, 0x40, 0x80, 0xc0, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x41, 0xf0, 0x04, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x02, 0x04, 0x04, 0x02, 0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x40, 0x40, 0x55, 0x82, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x20, 0x30, 0x0c, 0x02, 0x05, 0x09, 0x12, 0x1e, 0x04, 0x18, 0x10, 0x08, 0x10, 0x20, 0x28, 0x34, 0x06, 0x02, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                     }};

    /* animation */
    void animate_luna(void) {
        /* jump */
        if (isJumping || !showedJump) {
            /* clear */
            oled_set_cursor(LUNA_X, LUNA_Y + 2);
            oled_write("     ", false);

            oled_set_cursor(LUNA_X, LUNA_Y - 1);

            showedJump = true;
        } else {
            /* clear */
            oled_set_cursor(LUNA_X, LUNA_Y - 1);
            oled_write("     ", false);

            oled_set_cursor(LUNA_X, LUNA_Y);
        }

        /* switch frame */
        current_frame = (current_frame + 1) % 2;

        /* current status */
        if (led_usb_state.caps_lock) {
            oled_write_raw_P(bark[current_frame], ANIM_SIZE);

        } else if (isSneaking) {
            oled_write_raw_P(sneak[current_frame], ANIM_SIZE);

        } else if (current_wpm <= MIN_WALK_SPEED) {
            oled_write_raw_P(sit[current_frame], ANIM_SIZE);

        } else if (current_wpm <= MIN_RUN_SPEED) {
            oled_write_raw_P(walk[current_frame], ANIM_SIZE);

        } else {
            oled_write_raw_P(run[current_frame], ANIM_SIZE);
        }
    }

#    if OLED_TIMEOUT > 0
    /* the animation prevents the normal timeout from occuring */
    if (last_input_activity_elapsed() > OLED_TIMEOUT && last_led_activity_elapsed() > OLED_TIMEOUT) {
        oled_off();
        return;
    } else {
        oled_on();
    }
#    endif

    /* animation timer */
    if (timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
        anim_timer = timer_read32();
        animate_luna();
    }
}

/* KEYBOARD PET END */

/* KEYBOARD XOMT START */
static void render_xomt(int XOMT_X, int XOMT_Y) {
    static const char PROGMEM xomt[] = {
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    };

    oled_set_cursor(XOMT_X, XOMT_Y);
    oled_write_raw_P(xomt, 8);
}
/* KEYBOARD XOMT END */

static void print_status_narrow(void) {
    oled_set_cursor(0, 0);
    oled_write("M4J0R", false);

    oled_set_cursor(0, 2);

    switch (get_highest_layer(default_layer_state)) {
        case _QWERTY:
            oled_write("QWRTY", false);
            break;
        case _MIRYOKU_BASE:
            oled_write("MRYKU", false);
            break;
        default:
            oled_write("UNDEF", false);
    }

    oled_set_cursor(0, 4);

    /* Print current layer */
    oled_write("LAYER", false);

    oled_set_cursor(0, 5);

    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
        case _MIRYOKU_BASE:
            oled_write("Base ", false);
            break;
        case _UPPER:
            oled_write("Upper", false);
            break;
        case _LOWER:
            oled_write("Lower", false);
            break;
        case _ADJUST:
            oled_write("Adjst", false);
            break;
        case _MIRYOKU_NAV:
            oled_write("MKNav", false);
            break;
        case _MIRYOKU_SYM:
            oled_write("MKSym", false);
            break;
        case _MIRYOKU_NUM:
            oled_write("MKNum", false);
            break;
        case _MIRYOKU_MOUSE:
            oled_write("MKMse", false);
            break;
        case _MIRYOKU_MEDIA:
            oled_write("MKMda", false);
            break;
        case _MIRYOKU_FUN:
            oled_write("MKFun", false);
            break;
        default:
            oled_write("Undef", false);
    }

    oled_set_cursor(0, 7);
    /* wpm counter */
    oled_write(get_u8_str(get_current_wpm(), ' '), false);
    oled_set_cursor(0, 8);
    oled_write(" wpm", false);

    /* KEYBOARD XOMT RENDER START */

    render_xomt(0, 10);

    /* KEYBOARD XOMT RENDER ENDER */

    /* KEYBOARD PET RENDER START */

    render_luna(0, 13);

    /* KEYBOARD PET RENDER END */
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

bool oled_task_user(void) {
    /* KEYBOARD PET VARIABLES START */

    current_wpm   = get_current_wpm();
    led_usb_state = host_keyboard_led_state();

    /* KEYBOARD PET VARIABLES END */

    print_status_narrow();
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        /* KEYBOARD PET STATUS START */
        case KC_LCTL:
        case KC_RCTL:
            if (record->event.pressed) {
                isSneaking = true;
            } else {
                isSneaking = false;
            }
            break;
        case KC_SPC:
            if (record->event.pressed) {
                isJumping  = true;
                showedJump = false;
            } else {
                isJumping = false;
            }
            break;
            /* KEYBOARD PET STATUS END */
    }
    return true;
}

#endif
/* end OLED/luna */

/* RGB lighting */
// forks rgb_default, using corrected LED addresses for 1 (ind) + 6 (und) + 29(per) = 36 lights per side
#ifdef RGBLIGHT_ENABLE

#    define INDICATOR_BRIGHTNESS 30

#    define HSV_OVERRIDE_HELP(h, s, v, Override) h, s, Override
#    define HSV_OVERRIDE(hsv, Override) HSV_OVERRIDE_HELP(hsv, Override)

#    define SET_INDICATORS(hsv)                                     \
        {0, 1, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}, {     \
            36 + 0, 6, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS) \
        }

#    define SET_UNDERGLOW(hsv) \
        {1, 6, hsv}, {         \
            36 + 1, 6, hsv     \
        }

#    define SET_NUMROW(hsv)                                                               \
        {12, 1, hsv}, {21, 2, hsv}, {31, 2, hsv}, {36 + 12, 1, hsv}, {36 + 21, 2, hsv}, { \
            36 + 31, 2, hsv                                                               \
        }

#    define SET_THUMBCLUSTER(hsv)                                                       \
        {7, 1, hsv}, {16, 2, hsv}, {26, 2, hsv}, {36 + 7, 1, hsv}, {36 + 16, 2, hsv}, { \
            36 + 26, 2, hsv                                                             \
        }

#    define SET_LAYER_ID(hsv)                                                                                                           \
        {0, 1, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}, {36 + 0, 6, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}, {1, 6, hsv}, { \
            36 + 1, 6, hsv                                                                                                              \
        }

// build our "layer" array
char layer_state_str[72];

// qwerty = teal
const rgblight_segment_t PROGMEM layer_qwerty_lights[] = RGBLIGHT_LAYER_SEGMENTS(SET_LAYER_ID(HSV_TEAL));

// colemakdh = pink
const rgblight_segment_t PROGMEM layer_colemakdh_lights[] = RGBLIGHT_LAYER_SEGMENTS(SET_LAYER_ID(HSV_PINK));

// upper = purple
const rgblight_segment_t PROGMEM layer_upper_lights[] = RGBLIGHT_LAYER_SEGMENTS(SET_LAYER_ID(HSV_PURPLE));

// lower = white
const rgblight_segment_t PROGMEM layer_lower_lights[] = RGBLIGHT_LAYER_SEGMENTS(SET_LAYER_ID(HSV_WHITE));

// adj = orange
const rgblight_segment_t PROGMEM layer_adjust_lights[] = RGBLIGHT_LAYER_SEGMENTS(SET_LAYER_ID(HSV_ORANGE));

// miryoku-fun  =
const rgblight_segment_t PROGMEM layer_mkfun_lights[] = RGBLIGHT_LAYER_SEGMENTS(SET_LAYER_ID(HSV_RED));

// miryoku-sym  =
const rgblight_segment_t PROGMEM layer_mksym_lights[] = RGBLIGHT_LAYER_SEGMENTS(SET_LAYER_ID(HSV_ORANGE));

// miryoku-num  =
const rgblight_segment_t PROGMEM layer_mknum_lights[] = RGBLIGHT_LAYER_SEGMENTS(SET_LAYER_ID(HSV_YELLOW));

// miryoku-nav  =
const rgblight_segment_t PROGMEM layer_mknav_lights[] = RGBLIGHT_LAYER_SEGMENTS(SET_LAYER_ID(HSV_GREEN));

// miryoku-mda  =
const rgblight_segment_t PROGMEM layer_mkmda_lights[] = RGBLIGHT_LAYER_SEGMENTS(SET_LAYER_ID(HSV_BLUE));

// miryoku-mse  =
const rgblight_segment_t PROGMEM layer_mkmse_lights[] = RGBLIGHT_LAYER_SEGMENTS(SET_LAYER_ID(HSV_VIOLET));

// configure layers
const rgblight_segment_t *const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(layer_qwerty_lights, layer_colemakdh_lights, layer_upper_lights, layer_lower_lights, layer_adjust_lights, layer_mkfun_lights, layer_mksym_lights, layer_mknum_lights, layer_mknav_lights, layer_mkmda_lights, layer_mkmse_lights, );

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _QWERTY));
    rgblight_set_layer_state(1, layer_state_cmp(state, _MIRYOKU_BASE));
    rgblight_set_layer_state(2, layer_state_cmp(state, _LOWER));
    rgblight_set_layer_state(3, layer_state_cmp(state, _UPPER));
    rgblight_set_layer_state(4, layer_state_cmp(state, _ADJUST));
    rgblight_set_layer_state(5, layer_state_cmp(state, _MIRYOKU_FUN));
    rgblight_set_layer_state(6, layer_state_cmp(state, _MIRYOKU_SYM));
    rgblight_set_layer_state(7, layer_state_cmp(state, _MIRYOKU_NUM));
    rgblight_set_layer_state(8, layer_state_cmp(state, _MIRYOKU_NAV));
    rgblight_set_layer_state(9, layer_state_cmp(state, _MIRYOKU_MDA));
    rgblight_set_layer_state(10, layer_state_cmp(state, _MIRYOKU_MSE));
    return update_tri_layer_state(state, _LOWER, _UPPER, _ADJUST);
};

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;

    rgblight_mode(10);
};

#endif

/* RGB matrix */
#ifdef RGB_MATRIX_ENABLE

#    define min(a, b)               \
        ({                          \
            __typeof__(a) _a = (a); \
            __typeof__(b) _b = (b); \
            _a < _b ? _a : _b;      \
        })

void set_indicator_underglow_layer(uint8_t hue, uint8_t sat, uint8_t val) {
    HSV hsv = {.h = hue, .s = sat, .v = min(RGB_MATRIX_MAXIMUM_BRIGHTNESS, val)};
    RGB rgb = hsv_to_rgb(hsv);
    // for the indicator, we actually want to fix the value to e.g. 50 for reduced brightness of "naked" LED
    HSV hsv_indicator = {.h = hue, .s = sat, .v = RGB_MATRIX_MAXIMUM_BRIGHTNESS_INDICATOR};
    RGB rgb_indicator = hsv_to_rgb(hsv_indicator);

    // first 7 LEDs are 1xindicator + 6xunderglow
    // also add 36 to ensure we modify appropriately on nonmaster side
    rgb_matrix_set_color(0, rgb_indicator.r, rgb_indicator.g, rgb_indicator.b);
    rgb_matrix_set_color(36, rgb_indicator.r, rgb_indicator.g, rgb_indicator.b);
    for (uint8_t i = 1; i < 7; i++) {
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        rgb_matrix_set_color(36 + i, rgb.r, rgb.g, rgb.b);
    };
};

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
        case _MIRYOKU_BASE:
            set_indicator_underglow_layer(HSV_TEAL);
            break;
        case _LOWER:
        case _MIRYOKU_NAV:
            set_indicator_underglow_layer(HSV_WHITE);
            break;
        case _UPPER:
        case _MIRYOKU_SYM:
            set_indicator_underglow_layer(HSV_PURPLE);
            break;
        case _ADJUST:
        case _MIRYOKU_NUM:
            set_indicator_underglow_layer(HSV_GOLD);
            break;
        default:
            set_indicator_underglow_layer(HSV_GREEN);
    }
    return true;
};

// not quite sure why i need to give this function a nudge - but this allows RGBMatrix
// to _actually_ do its bootstrapping on init
void keyboard_post_init_user(void) {
    eeconfig_update_rgb_matrix_default();
};

#endif
/* END RGB matrix*/

 /* Copyright 2021 HellSingCoder
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 2 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  */

#include QMK_KEYBOARD_H

#ifdef JOYSTICK_ENABLE
#   include "analog.h"
#endif

enum lime_layers {
    /* _M_XYZ = Mac Os, _W_XYZ = Win/Linux */
    _QWERTY,
    _COLEMAK,
    _LOWER,
    _RAISE,
    _ADJUST,
};

enum custom_keycodes {
    KC_QWERTY = SAFE_RANGE,
    KC_COLEMAK,
    KC_LOWER,
    KC_RAISE,
    KC_ADJUST,
    KC_PRVWD,
    KC_NXTWD,
    KC_LSTRT,
    KC_LEND,
    KC_DLINE,
    KC_BSPC_DEL,
    KC_THUMB_SWAP,
    KC_THUMB_LEFT,
    KC_THUMB_RIGHT,
    KC_JOYSTICK_DEBUG,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | Esc  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  BS  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Caps |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|       |    |  Mute |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |  \   |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *     |Lower | LGUI | LAlt | DEL  | LCTR | /Enter  /       \Space \  |Raise |  [   |  ]   |  -   |  =   |
 *     |      |      |      |      |      |/       /         \      \ |      |      |      |      |      |
 *      `----------------------------------------'            '------''----------------------------------'
 */

[_QWERTY] = LAYOUT(
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                            KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_BSPC_DEL,
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                            KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_GRV,
  KC_CAPS,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                            KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,  XXXXXXX,        KC_MUTE,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_BSLS,
        KC_LOWER, KC_LGUI,KC_LALT,KC_DEL, KC_LCTL,  KC_THUMB_LEFT,       KC_THUMB_RIGHT,  KC_RAISE, KC_LBRC, KC_RBRC, KC_MINS, KC_EQL
),

/*
 * COLEMAK
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | Esc  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  BS  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |                    |   J  |   L  |   U  |   Y  |   ;  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Caps |   A  |   R  |   S  |   T  |   D  |-------.    ,-------|   H  |   N  |   E  |   I  |   O  |  '   |
 * |------+------+------+------+------+------|       |    |  Mute |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   K  |   M  |   ,  |   .  |   /  |  \   |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *     |Lower | LGUI | LAlt | DEL  | LCTR | /Enter  /       \Space \  |Raise |  [   |  ]   |  -   |  =   |
 *     |      |      |      |      |      |/       /         \      \ |      |      |      |      |      |
 *      `----------------------------------------'            '------''----------------------------------'
 */

[_COLEMAK] = LAYOUT(
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                            KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_BSPC_DEL,
  KC_TAB,   KC_Q,   KC_W,    KC_F,    KC_P,    KC_G,                            KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN,  KC_GRV,
  KC_CAPS,  KC_A,   KC_R,    KC_S,    KC_T,    KC_D,                            KC_H,    KC_N,    KC_E,    KC_I,    KC_O,     KC_QUOT,
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,  XXXXXXX,        KC_MUTE,  KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_BSLS,
        KC_LOWER, KC_LGUI,KC_LALT,KC_DEL, KC_LCTL,  KC_THUMB_LEFT,       KC_THUMB_RIGHT,  KC_RAISE, KC_LBRC, KC_RBRC, KC_MINS, KC_EQL
),

/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | Esc  |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  | Ins  | Pscr | Menu |      |      |                    |      | PWrd |  Up  | NWrd |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Caps | LAt  | LCtl |LShift|      |      |-------.    ,-------|      | Left | Down | Rigth|      |      |
 * |------+------+------+------+------+------|       |    |  Mute |------+------+------+------+------+------|
 * |LShift|      |      |      |      |      |-------|    |-------|      | LStr | DLine| LEnd |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *     |Lower | LGUI | LAlt | DEL  | LCTR | /Enter  /       \Space \  |Raise |      |      |      |      |
 *     |      |      |      |      |      |/       /         \      \ |      |      |      |      |      |
 *      `----------------------------------------'            '------''----------------------------------'
 */
[_RAISE] = LAYOUT(
  _______, _______ , _______ , _______ , _______ , _______,                        _______,  _______ ,  _______ ,  _______ ,  _______ , _______,
  _______, KC_INS,   KC_PSCR,  KC_APP,   XXXXXXX,  XXXXXXX,                        KC_PGUP,  KC_PRVWD,  KC_UP,     KC_NXTWD,  XXXXXXX, XXXXXXX,
  _______, KC_LALT,  KC_LCTL,  KC_LSFT,  XXXXXXX,  XXXXXXX,                        KC_PGDN,  KC_LEFT,   KC_DOWN,   KC_RGHT,   XXXXXXX,   XXXXXXX,
  _______, XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  _______,    _______,  XXXXXXX,  KC_LSTRT,  KC_DLINE,   KC_LEND,   XXXXXXX,  XXXXXXX,
         _______, _______, _______, _______, _______, _______,                  _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),

/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | Esc  |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Caps |   !  |   @  |   #  |   $  |   %  |-------.    ,-------|   ^  |   &  |   *  |   (  |   )  |   |  |
 * |------+------+------+------+------+------|       |    |  Mute |------+------+------+------+------+------|
 * |LShift|  =   |  -   |  +   |   {  |   }  |-------|    |-------|   [  |   ]  |   ;  |   :  |   \  |  `   |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *     |Lower | LGUI | LAlt | DEL  | LCTR | /Enter  /       \Space \  |Raise |      |      |      |      |
 *     |      |      |      |      |      |/       /         \      \ |      |      |      |      |      |
 *      `----------------------------------------'            '------''----------------------------------'
 */
[_LOWER] = LAYOUT(
  _______,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                           KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  _______,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                            KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_F12,
  _______,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                         KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE,
  _______,  KC_EQL,  KC_MINS, KC_PLUS, KC_LCBR, KC_RCBR, _______,       _______, KC_LBRC, KC_RBRC, KC_SCLN, KC_COLN, KC_BSLS, KC_GRV,
         _______, _______, _______, _______, _______, _______,              _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),

/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | QK_BOOT|      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |QWERTY|      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |JDEBUG|      |      |-------.    ,-------|      | VOLDO| MUTE | VOLUP|      |      |
 * |------+------+------+------+------+------|       |    |  Mute |------+------+------+------+------+------|
 * |      |      |      |COLEMA|      |      |-------|    |-------|      | PREV | PLAY | NEXT |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *     |Lower |MACWIN|      |      |      | / Swap  /       \      \  |Raise |      |      |      |      |
 *     |      |      |      |      |      |/       /         \      \ |      |      |      |      |      |
 *      `----------------------------------------'            '------''----------------------------------'
 */
  [_ADJUST] = LAYOUT(
  QK_BOOT, XXXXXXX,    XXXXXXX,   XXXXXXX,          XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, KC_QWERTY,  XXXXXXX,   XXXXXXX,          CG_TOGG, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX,    XXXXXXX,   KC_JOYSTICK_DEBUG,XXXXXXX, XXXXXXX,                       XXXXXXX, KC_VOLD, KC_MUTE, KC_VOLU, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX,    XXXXXXX,   KC_COLEMAK,       XXXXXXX, XXXXXXX, XXXXXXX,     _______, XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX,
         _______, CG_TOGG, XXXXXXX, XXXXXXX,    XXXXXXX, KC_THUMB_SWAP,                  XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  )
};

#ifdef JOYSTICK_ENABLE
    /* Joystick pins */
#   ifndef JOYSTICK_X_PIN
#       define JOYSTICK_X_PIN F5
#       define JOYSTICK_Y_PIN F4
#   endif

    /* Joystick + Encoder fix */
    void keyboard_post_init_kb(void) {
        if (is_keyboard_master()) {
            gpio_write_pin_low(JOYSTICK_X_PIN);
            gpio_write_pin_low(JOYSTICK_Y_PIN);
        }
    }

    /* Joystick axes settings */
    joystick_config_t joystick_axes[JOYSTICK_AXIS_COUNT] = {
        [0] = JOYSTICK_AXIS_IN(JOYSTICK_X_PIN, 268, 514, 813),
        [1] = JOYSTICK_AXIS_IN(JOYSTICK_Y_PIN, 865, 519, 260)
    };
#endif

/* Joystick Debug */
bool joystick_debug = false;

/* Space Enter swap */
bool swap_space_enter = false;

/* Smart Backspace Delete */
bool shift_held = false;
static uint16_t held_shift = 0;

/* keyboard pet jump status variables */
bool isJumping = false;
bool showedJump = true;

#ifdef OLED_ENABLE
    /* Keyboard logo (from gdlcfont.c) */
    static void render_logo(void) {
        static const char PROGMEM lime_logo[] = {
            0x80, 0x81, 0x82, 0x83, 0x84,
            0xA0, 0xA1, 0xA2, 0xA3, 0xA4,
            0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0
        };

        oled_write_P(lime_logo, false);
    }

    /* Keyboard Pet settings */
    #define MIN_WALK_SPEED 10
    #define MIN_RUN_SPEED 50
    #define ANIM_FRAME_DURATION 200 // how long each frame lasts in ms
    #define ANIM_SIZE 96 // number of bytes per image

    /* Keyboard Pet status variables */
    led_t led_usb_state;
    uint8_t current_wpm = 0;
    uint8_t current_frame = 0;
    uint32_t anim_timer = 0;
    uint32_t anim_sleep = 0;

    /* Keyboard Pet logic */
    static void render_keyboard_pet(int KEYBOARD_PET_X, int KEYBOARD_PET_Y) {

        /* Sit */
        static const char PROGMEM sit[2][ANIM_SIZE] = {
            {
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1c,
                0x02, 0x05, 0x02, 0x24, 0x04, 0x04, 0x02, 0xa9, 0x1e, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x08, 0x68, 0x10, 0x08, 0x04, 0x03, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x06, 0x82, 0x7c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x0c, 0x10, 0x10, 0x20, 0x20, 0x20, 0x28,
                0x3e, 0x1c, 0x20, 0x20, 0x3e, 0x0f, 0x11, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
            },
            {
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1c,
                0x02, 0x05, 0x02, 0x24, 0x04, 0x04, 0x02, 0xa9, 0x1e, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x90, 0x08, 0x18, 0x60, 0x10, 0x08, 0x04, 0x03, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x0e, 0x82, 0x7c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x0c, 0x10, 0x10, 0x20, 0x20, 0x20, 0x28,
                0x3e, 0x1c, 0x20, 0x20, 0x3e, 0x0f, 0x11, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
            }
        };

        /* Walk */
        static const char PROGMEM walk[2][ANIM_SIZE] = {
            {
                0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x10, 0x90, 0x90, 0x90, 0xa0, 0xc0, 0x80, 0x80,
                0x80, 0x70, 0x08, 0x14, 0x08, 0x90, 0x10, 0x10, 0x08, 0xa4, 0x78, 0x80, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x08, 0xfc, 0x01, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00,
                0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x18, 0xea, 0x10, 0x0f, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1c, 0x20, 0x20, 0x3c, 0x0f, 0x11, 0x1f, 0x03,
                0x06, 0x18, 0x20, 0x20, 0x3c, 0x0c, 0x12, 0x1e, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
            },
            {
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x20, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00,
                0x00, 0xe0, 0x10, 0x28, 0x10, 0x20, 0x20, 0x20, 0x10, 0x48, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x20, 0xf8, 0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
                0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x10, 0x30, 0xd5, 0x20, 0x1f, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x20, 0x30, 0x0c, 0x02, 0x05, 0x09, 0x12, 0x1e,
                0x02, 0x1c, 0x14, 0x08, 0x10, 0x20, 0x2c, 0x32, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
            }
        };

        /* Run */
        static const char PROGMEM run[2][ANIM_SIZE] = {
            {
                0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x08, 0x08, 0xc8, 0xb0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
                0x80, 0x40, 0x40, 0x3c, 0x14, 0x04, 0x08, 0x90, 0x18, 0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0xc4, 0xa4, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc8, 0x58, 0x28, 0x2a, 0x10, 0x0f, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x09, 0x04, 0x04, 0x04, 0x04, 0x02, 0x03, 0x02, 0x01, 0x01,
                0x02, 0x02, 0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00
            },
            {
                0x00, 0x00, 0x00, 0xe0, 0x10, 0x10, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
                0x80, 0x80, 0x78, 0x28, 0x08, 0x10, 0x20, 0x30, 0x08, 0x10, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00,
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x10, 0xb0, 0x50, 0x55, 0x20, 0x1f, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28, 0x37,
                0x02, 0x1e, 0x20, 0x20, 0x18, 0x0c, 0x14, 0x1e, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
            }
        };

        /* Bark */
        static const char PROGMEM bark[2][ANIM_SIZE] = {
            {
                0x00, 0xc0, 0x20, 0x10, 0xd0, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x40,
                0x3c, 0x14, 0x04, 0x08, 0x90, 0x18, 0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00, 0x80, 0xc8, 0x48, 0x28, 0x2a, 0x10, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28, 0x37, 0x02, 0x02,
                0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
            },
            {
                0x00, 0xe0, 0x10, 0x10, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x40,
                0x40, 0x2c, 0x14, 0x04, 0x08, 0x90, 0x18, 0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x48, 0x28, 0x2a, 0x10, 0x0f, 0x20, 0x4a, 0x09, 0x10,
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28, 0x37, 0x02, 0x02,
                0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
            }
        };

        /* animation */
        void animate_keyboard_pet(void) {

            /* jump */
            if (isJumping || !showedJump) {
                oled_set_cursor(KEYBOARD_PET_X,KEYBOARD_PET_Y +2);
                oled_write_P(PSTR("     "), false);
                oled_set_cursor(KEYBOARD_PET_X,KEYBOARD_PET_Y -1);
                showedJump = true;
            } else {
                oled_set_cursor(KEYBOARD_PET_X,KEYBOARD_PET_Y -1);
                oled_write_P(PSTR("     "), false);
                oled_set_cursor(KEYBOARD_PET_X,KEYBOARD_PET_Y);
            }

            /* switch frame */
            current_frame = (current_frame + 1) % 2;

            /* current animation status */
            if(led_usb_state.caps_lock) {
                oled_write_raw_P(bark[abs(1 - current_frame)], ANIM_SIZE);
            } else if(current_wpm <= MIN_WALK_SPEED) {
                oled_write_raw_P(sit[abs(1 - current_frame)], ANIM_SIZE);
            } else if(current_wpm <= MIN_RUN_SPEED) {
                oled_write_raw_P(walk[abs(1 - current_frame)], ANIM_SIZE);
            } else {
                oled_write_raw_P(run[abs(1 - current_frame)], ANIM_SIZE);
            }
        }

        /* animation timer */
        if(timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
            anim_timer = timer_read32();
            if(timer_elapsed32(anim_sleep) < OLED_TIMEOUT) {
                animate_keyboard_pet();
            }
        }

        if (current_wpm > 0) {
            anim_sleep = timer_read32();
        } else if(timer_elapsed32(anim_sleep) > OLED_TIMEOUT) {
            oled_off();
        }

    }

    static void print_logo_narrow(void) {

        /* Keyboard logo */
        render_logo();

        /* wpm counter */
        char wpm_str[5];
        wpm_str[4] = '\0';
        wpm_str[3] = '0' + current_wpm % 10;
        wpm_str[2] = '0' + ( current_wpm /= 10) % 10;
        wpm_str[1] = '0' + current_wpm / 10;
        wpm_str[0] = ' ';
        oled_set_cursor(0,14);
        oled_write(wpm_str, false);
        oled_write_P(PSTR("  wpm"), false);
    }

    static void print_status_narrow(void) {

        /* Print current OS */
        oled_set_cursor(2,0);
        if (keymap_config.swap_lctl_lgui) {
            oled_write_P(PSTR("\x9E"), false);
        } else {
            oled_write_P(PSTR("\x9F"), false);
        }

        /* Print current layout */
        oled_set_cursor(0,2);
        switch (get_highest_layer(default_layer_state)) {
            case _QWERTY:
                oled_write_P(PSTR("QWRTY"), false);
                break;
            case _COLEMAK:
                oled_write_P(PSTR("COLMK"), false);
                break;
            default:
                oled_write_P(PSTR("UNDEF"), false);
        }

        /* Print current layer */
        oled_set_cursor(0,4);
        oled_write_P(PSTR("LAYER"), false);
        oled_set_cursor(0,5);
        switch (get_highest_layer(layer_state)) {
            case _QWERTY:
                oled_write_P(PSTR("Base "), false);
                break;
            case _RAISE:
                oled_write_P(PSTR("Raise"), false);
                break;
            case _LOWER:
                oled_write_P(PSTR("Lower"), false);
                break;
            case _ADJUST:
                oled_write_P(PSTR("Adj  "), false);
                break;
            default:
                oled_write_P(PSTR("Undef"), false);
        }

        /* caps lock */
        oled_set_cursor(0,7);
        oled_write_P(PSTR("CAPS"), false);
        if (led_usb_state.caps_lock) {
            oled_write_P(PSTR("\x9A"), false);
        } else {
            oled_write_P(PSTR("\x99"), false);
        }

        /* Space Enter swap */
        oled_set_cursor(0,9);
        oled_write_P(PSTR("\x9B"), false);
        oled_set_cursor(2,9);
        oled_write_P(PSTR("\x9C"), !swap_space_enter);
        oled_set_cursor(4,9);
        oled_write_P(PSTR("\x9D"), swap_space_enter);

       /* Joystick debugging */
#      ifdef JOYSTICK_ENABLE
            if (joystick_debug) {
                oled_set_cursor(0,10);
                oled_write_P(PSTR("X:"), false);
                uint16_t val = analogReadPin(JOYSTICK_X_PIN);
                char val_str[3];
                itoa(val, val_str, 10);
                oled_write(val_str, false);
                oled_set_cursor(0,11);
                oled_write_P(PSTR("Y:"), false);
                val = analogReadPin(JOYSTICK_Y_PIN);
                itoa(val, val_str, 10);
                oled_write(val_str, false);
            } else {
                oled_set_cursor(0,10);
                oled_write_P(PSTR("     "), false);
                oled_set_cursor(0,11);
                oled_write_P(PSTR("     "), false);
            }
#       endif

        /* Keyboard Pet Render */
        render_keyboard_pet(0,13);
    }

    /* vertical screens orientation fix */
    oled_rotation_t oled_init_user(oled_rotation_t rotation) {
        return OLED_ROTATION_270;
    }

    bool oled_task_user(void) {

        /* Keyboard Pet Variables */
        current_wpm = get_current_wpm();
        led_usb_state = host_keyboard_led_state();

        if (is_keyboard_master()) {
            print_status_narrow();
        } else {
            print_logo_narrow();
        }
        return false;
    }

#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
        case KC_COLEMAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_COLEMAK);
            }
            return false;
        case KC_LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
        case KC_RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
        case KC_ADJUST:
            if (record->event.pressed) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            return false;
        case KC_PRVWD:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    register_mods(mod_config(MOD_LALT));
                    register_code(KC_LEFT);
                } else {
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_LEFT);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LALT));
                    unregister_code(KC_LEFT);
                } else {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_LEFT);
                }
            }
            break;
        case KC_NXTWD:
             if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    register_mods(mod_config(MOD_LALT));
                    register_code(KC_RIGHT);
                } else {
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_RIGHT);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LALT));
                    unregister_code(KC_RIGHT);
                } else {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_RIGHT);
                }
            }
            break;
        case KC_LSTRT:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                     /* CMD-arrow on Mac, but we have CTL and GUI swapped */
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_LEFT);
                } else {
                    register_code(KC_HOME);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_LEFT);
                } else {
                    unregister_code(KC_HOME);
                }
            }
            break;
        case KC_LEND:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    /* CMD-arrow on Mac, but we have CTL and GUI swapped */
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_RIGHT);
                } else {
                    register_code(KC_END);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_RIGHT);
                } else {
                    unregister_code(KC_END);
                }
            }
            break;
        case KC_DLINE:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_BSPC);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_BSPC);
            }
            break;

        case KC_JOYSTICK_DEBUG:
            if (record->event.pressed) {
                joystick_debug = !joystick_debug;
            }
            return false;
            break;

        /* Space Enter swap */
        case KC_THUMB_SWAP:
            if (record->event.pressed) {
                swap_space_enter = !swap_space_enter;
            }
            return false;
            break;
        case KC_THUMB_LEFT:
            if (record->event.pressed) {
                if (swap_space_enter) {
                    register_code(KC_SPC);

                    /*Keyboard Pet jump*/
                    isJumping = true;
                    showedJump = false;
                } else {
                    register_code(KC_ENT);
                }
            } else {
                if (swap_space_enter) {
                    unregister_code(KC_SPC);

                    /*Keyboard Pet jump reset*/
                    isJumping = false;
                } else {
                    unregister_code(KC_ENT);
                }
            }
            return false;
        case KC_THUMB_RIGHT:
            if (record->event.pressed) {
                if (swap_space_enter) {
                    register_code(KC_ENT);
                } else {
                    register_code(KC_SPC);
                    isJumping = true;
                    showedJump = false;
                }
            } else {
                if (swap_space_enter) {
                    unregister_code(KC_ENT);
                } else {
                    unregister_code(KC_SPC);
                    isJumping = false;
                }
            }
            return false;

        /* Smart Backspace Delete */
        case KC_RSFT:
        case KC_LSFT:
            shift_held = record->event.pressed;
            held_shift = keycode;
            break;
        case KC_BSPC_DEL:
            if (record->event.pressed) {
                if (shift_held) {
                    unregister_code(held_shift);
                    register_code(KC_DEL);
                } else {
                    register_code(KC_BSPC);
                }
            } else {
                unregister_code(KC_DEL);
                unregister_code(KC_BSPC);
                if (shift_held) {
                    register_code(held_shift);
                }
            }
            return false;
    }
    return true;
}

/* The default rotary encoder code can be found at the bottom of qmk_firmware/keyboards/lime/rev1/rev1.c
 * These default settings can be overriden by your own settings in your keymap.c
 * For your convenience, here's a copy of those settings so that you can uncomment them if you wish to apply your own modifications.
 * DO NOT edit the rev1.c file; instead override the weakly defined default functions by your own.
 */

/* DELETE THIS LINE TO UNCOMMENT (1/2)

// Encoders
#ifdef ENCODER_ENABLE
    bool encoder_update_user(uint8_t index, bool clockwise) {

        if (index == 0) {
            if (clockwise) {
                tap_code(KC_MNXT);
            } else {
                tap_code(KC_MPRV);
            }
        } else if (index == 1) {
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
        }
        return false;
    }
#endif

#endif
DELETE THIS LINE TO UNCOMMENT (2/2) */

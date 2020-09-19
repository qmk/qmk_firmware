/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
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
#include "raw_hid.h"

enum layers {
    _QWERTY = 0,
    _LOWER,
    _RAISE,
    _ADJUST
};

// shortcuts for certain keys to use LAYOUT_kc()
#define KC_RAISE TT(_RAISE)
#define KC_LOWER TT(_LOWER)
#define KC_KITTY S(KC_LCTL)
#define KC_I3 S(KC_LGUI)
#define KC_CTLESC MT(MOD_LCTL, KC_ESC)
#define KC_GUIBS MT(MOD_LGUI, KC_BSPC)
#define KC_ALTCLN MT(MOD_LALT, KC_COLON)
#define KC_RTOG RGB_TOG
#define KC_RSAI RGB_SAI
#define KC_RHUI RGB_HUI
#define KC_RVAI RGB_VAI
#define KC_RMOD RGB_MOD
#define KC_RSAD RGB_SAD
#define KC_RHUD RGB_HUD
#define KC_RVAD RGB_VAD
#define KC_RRMD RGB_RMOD


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: QWERTY
 */
    [_QWERTY] = LAYOUT_kc(
 // ,-------------------------------------------.                              ,-------------------------------------------.
      GRV,      Q,     W,     E,     R,    T,                                     Y,     U,     I,     O,     P,    BSLS,
 // |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
      TAB,      A,     S,     D,     F,    G,                                     H,     J,     K,     L,    SCLN,  QUOT,
 // |--------+------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------+--------|
      LSPO,     Z,     X,     C,     V,    B,     LSPO, ALTCLN,    RALT,  RSPC,   N,     M,    COMM,  DOT,   SLSH,  MINS,
 // `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
                              I3,  KITTY, RAISE,  SPC,  CTLESC,   GUIBS,  ENT,  LOWER,  SPC,   PSCR
 //                        `----------------------------------'  `----------------------------------'
    ),
/*
 * Lower Layer: Symbols
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  !   |  @   |  |   |  [   |  ]   |                              |      |      |      |      |      |  | \   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  #   |  $   |  `   |  {   |  }   |                              |   +  |  -   |  /   |  *   |  %   |  ' "   |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  %   |  ^   |  ~   |  (   |  )   |      |      |  |      |      |   &  |  =   |  ,   |  .   |  / ? | - _    |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_LOWER] = LAYOUT_kc(
 // ,-------------------------------------------.                              ,-------------------------------------------.
       TRNS,   EXLM,   AT,   PIPE,  LBRC,  RBRC,                                 TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  BSLS,
 // |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
       TRNS,   HASH,  DLR,   GRV,   LCBR,  RCBR,                                 PLUS,  MINS,  SLSH,  ASTR,  PERC,  QUOT,
 // |--------+------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------+--------|
       TRNS,   PERC,  CIRC,  TILD,  LPRN,  RPRN,  TRNS,  TRNS,     TRNS,  TRNS,  AMPR,  EQL,   COMM,   DOT,  SLSH,  MINS,
 // `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
                             TRNS,  TRNS,  TRNS,  TRNS,  TRNS,     TRNS,  TRNS,  TRNS,  TRNS,  TRNS
 //                        `----------------------------------'  `----------------------------------'
    ),
/*
 * Raise Layer: Number keys, media, navigation
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |   1  |  2   |  3   |  4   |  5   |                              |  6   |  7   |  8   |  9   |  0   |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      | Prev | Play | Next | VolUp|                              | Left | Down | Up   | Right|      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      | Mute | VolDn|      |      |  |      |      | MLeft| Mdown| MUp  |MRight|      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_RAISE] = LAYOUT_kc(
 // ,-------------------------------------------.                              ,-------------------------------------------.
       TRNS,    1,     2,     3,     4,     5,                                    6,     7,     8,     9,     0,    TRNS,
 // |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
       TRNS,   TRNS,  MPRV,  MPLY,  MNXT,  VOLU,                                 LEFT,  DOWN,   UP,   RGHT,  TRNS,  TRNS,
 // |--------+------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------+--------|
       TRNS,   TRNS,  TRNS,  TRNS,  MUTE,  VOLD,  TRNS,  TRNS,     TRNS,  TRNS,  MS_L,  MS_D,  MS_U,  MS_R,  TRNS,  TRNS,
 // `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
                             TRNS,  TRNS,  TRNS,  TRNS,  TRNS,     TRNS,  TRNS,  TRNS,  TRNS,  TRNS
 //                        `----------------------------------'  `----------------------------------'
      ),
/*
 * Adjust Layer: Function keys, RGB
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        | F1   |  F2  | F3   | F4   | F5   |                              | F6   | F7   |  F8  | F9   | F10  |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        | TOG  | SAI  | HUI  | VAI  | MOD  |                              |      |      |      | F11  | F12  |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      | SAD  | HUD  | VAD  | RMOD |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_ADJUST] = LAYOUT_kc(
 // ,-------------------------------------------.                              ,-------------------------------------------.
       TRNS,    F1,    F2,    F3,    F4,    F5,                                   F6,    F7,    F8,    F9,   F10,   TRNS,
 // |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
       TRNS,   RTOG,  RSAI,  RHUI,  RVAI,  RMOD,                                 TRNS,  TRNS,  TRNS,   F11,  F12,   TRNS,
 // |--------+------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------+--------|
       TRNS,   TRNS,  RSAD,  RHUD,  RVAD,  RRMD,  TRNS,  TRNS,     TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,
 // `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
                             TRNS,  TRNS,  TRNS,  TRNS,  TRNS,     TRNS,  TRNS,  TRNS,  TRNS,  TRNS
 //                        `----------------------------------'  `----------------------------------'
      ),
 //
 //  * Layer template
 //
 //    [_LAYERINDEX] = LAYOUT_kc(
 // ,-------------------------------------------.                              ,-------------------------------------------.
 //    TRNS,   TRNS,  TRNS,  TRNS,  TRNS,  TRNS,                                 TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,
 // |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 //    TRNS,   TRNS,  TRNS,  TRNS,  TRNS,  TRNS,                                 TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,
 // |--------+------+------+------+------+------+------+------.  ,------+------+------+------+------+------+------+--------|
 //    TRNS,   TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,     TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,  TRNS,
 // `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 //                          TRNS,  TRNS,  TRNS,  TRNS,  TRNS,     TRNS,  TRNS,  TRNS,  TRNS,  TRNS
 //                        `----------------------------------'  `----------------------------------'
 //    ),
};

static void send_layer_via_hid(char *layer) {
    //raw_hid_send((uint8_t*)layer, sizeof(layer));
    return;
}

/* RGB LIGHT LAYERS
const rgblight_segment_t PROGMEM my_qwerty_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 10, HSV_AZURE}
);

const rgblight_segment_t PROGMEM my_raise_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 10, HSV_RED}
);

const rgblight_segment_t PROGMEM my_lower_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 10, HSV_TURQUOISE}
);

const rgblight_segment_t PROGMEM my_adjust_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 10, HSV_PURPLE}
);
*/

void keyboard_post_init_user(void) {
    rgblight_sethsv_noeeprom(HSV_BLUE);
}


layer_state_t layer_state_set_user(layer_state_t state) {
    layer_state_t new_state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);

    switch (get_highest_layer(new_state)) {
        case _QWERTY:
            send_layer_via_hid("Default");
            rgblight_sethsv_noeeprom(HSV_BLUE);
            break;
        case _LOWER:
            send_layer_via_hid("Lower");
            rgblight_sethsv_noeeprom(HSV_RED);
            break;
        case _RAISE:
            send_layer_via_hid("Raise");
            rgblight_sethsv_noeeprom(HSV_TURQUOISE);
            break;
        case _ADJUST:
            send_layer_via_hid("Adjust");
            rgblight_sethsv_noeeprom(HSV_PURPLE);
            break;
        default:
            send_layer_via_hid("Undefined");
    }
    return new_state;
}

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
	return OLED_ROTATION_180;
}

static void render_logo(void) {
    static const char PROGMEM logo[] = {
        // canvas is 128x64.  need 16 padding
        // 80x32
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x20, 0x60, 0xe0, 0xf0, 0xfe, 0xfe, 0xf0, 0x60, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x0c, 0x1c, 0x3c, 0x7c, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0x7c, 0xf8, 0xe0, 0x60, 0x20, 0x10, 0x10, 0x0c, 0x0f, 0x09, 0x08, 0x00, 0x09, 0x9b, 0x5c, 0x50, 0x10, 0x20, 0x40, 0xe0, 0xf8, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x78, 0x38, 0x38, 0x10, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x1f, 0x1f, 0x1f, 0x1f, 0x17, 0x15, 0x3d, 0xef, 0xaf, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x10, 0x00, 0x02, 0x02, 0x01, 0x01, 0x00, 0x00, 0x10, 0x00, 0x00, 0x40, 0xa0, 0xbf, 0xff, 0x3f, 0x3f, 0x3f, 0x1f, 0x1f, 0x1f, 0x1f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    oled_write_raw_P(logo, sizeof(logo));
}

static void render_qmk_logo(void) {
  static const char PROGMEM qmk_logo[] = {
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};

  oled_write_P(qmk_logo, false);
}

static void render_status(void) {
    // QMK Logo and version information
    render_qmk_logo();
    oled_write_P(PSTR("Kyria rev1.3\n\n"), false);

    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("Lower / Symbols\n"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("Raise / Numbers\n"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("Adjust\n"), false);
            break;
        default:
            oled_write_P(PSTR("Undefined\n"), false);
    }

    // Host Keyboard LED Status
    uint8_t led_usb_state = host_keyboard_leds();
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_NUM_LOCK) ? PSTR("NUMLCK ") : PSTR("       "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_CAPS_LOCK) ? PSTR("CAPLCK ") : PSTR("       "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_SCROLL_LOCK) ? PSTR("SCRLCK ") : PSTR("       "), false);
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status(); // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_logo();
    }
}
#endif


#ifdef RAW_ENABLE
void raw_hid_receive(uint8_t *data, uint8_t length) {
    // messages from host
    // add ability to set color
    raw_hid_send(data, length);
}
#endif

#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        // Volume control
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    else if (index == 1) {
        // Page up/Page down
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
}
#endif

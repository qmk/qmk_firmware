/* Copyright 2020-2021 Fredrik Salomonsson <plattfot@gmail.com>
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
#include "version.h"

enum custom_keycodes {
    PLACEHOLDER = SAFE_RANGE,  // can always be here
    // New keys
    CLO_TAP,  // Close the next key press
};

// Close tap feature based on a post from drashna
// https://www.reddit.com/r/olkb/comments/citkbx/double_key_press_modifier_qmkwould_work_like/ev9cue8/
// Will insert the closing equivalent key and move the cursor inside.
// For example clo_tap and then ( will result in (|), where | is the
// cursor. For " it will be "|" as the close equivalent key is the
// same key.
enum close_tap_modes {
  CLO_DISABLED = 0b000,
  CLO_PRESSED  = 0b001, // Close tap key is pressed
  CLO_ACTIVE   = 0b010, // Close tap next keypress
  CLO_USED     = 0b100, // Turn off when close tap key is released
};

#define CLO_RELEASE(flag) flag & ~CLO_PRESSED

static enum close_tap_modes close_tap_it = CLO_DISABLED;

enum layers {
    _DEFAULT,
    _LOWER,
    _RAISE,
    _NAV,
    _ADJUST,
};

#define MO_ADJT MO(_ADJUST)
#define L_RAISE OSL(_RAISE)
#define L_LOWER OSL(_LOWER)
#define L_NAV   MO(_NAV)
#define EU_TDOT RSA(KC_SLSH)
#define EU_CDOT RALT(KC_EQUAL)
#define EU_DEG  RALT(KC_SCLN)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: Default
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  Esc   |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |  Del   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |  Tab   |   A  |   S  |  D   |   F  |   G  |                              |   H  |   J  |   K  |   L  |   ;  |   '    |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  | Lead | RAISE|  | LOWER|BSpace|   N  |   M  |   ,  |   .  |   /  | RShift |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        | MPlay| GUI  | LCtrl| Space| LALT |  | RCtrl| Enter| NAV  | RALT |Scroll|
 *                        |      |      |      |      |      |  |      |      |      |      | Lock |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_DEFAULT] = LAYOUT(
      KC_ESC,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,
      KC_TAB,  KC_A,   KC_S,   KC_D,   KC_F,   KC_G,                                         KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
      KC_LSFT, KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,    QK_LEAD,  L_RAISE, L_LOWER, KC_BSPC, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                               KC_MPLY,KC_LGUI,KC_LCTL, KC_SPACE, KC_LALT, KC_RCTL,  KC_ENT, L_NAV,   KC_RALT, KC_SCRL
    ),

/*
 * Lower Layer: Left symbols
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  !   |  @   |  #   |  $   |  %   |                              |  F6  |  F7  |  F8  |  F9  | F10  |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  |   |  _   |  \   |  -   |  +   |                              | F12  |      |      |      |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  °   |  :   |  (   |  )   |  ×   |      |ADJUST|  |      |      |CLOTAP|      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_LOWER] = LAYOUT(
      _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
      _______, KC_PIPE, KC_UNDS, KC_BSLS, KC_MINS, KC_PLUS,                                     KC_F12,  _______, _______, _______, _______, _______,
      _______, EU_DEG,  KC_COLN, KC_LPRN, KC_RPRN, EU_CDOT, _______, MO_ADJT, _______, _______, CLO_TAP, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
/*
 * Raise Layer: Right symbols + state
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |                              |   ^  |  &   |  *   |  ~   |  ?   |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |      |      | F11  |                              |   =  |  {   |  }   |  [   |  ]   |   `    |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |CLOTAP|      |      |  |ADJUST|      |   …  |  "   |  <   |  >   |  /   |CapsLock|
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        | Mute |      |      |      |      |  |      |      |      |      |Insert|
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_RAISE] = LAYOUT(
      _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                       KC_CIRC, KC_AMPR, KC_ASTR, KC_TILDE,KC_QUES, _______,
      _______, _______, _______, _______, _______, KC_F11,                                      KC_EQUAL,KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, KC_GRV,
      _______, _______, _______, _______, _______, CLO_TAP, _______, _______, MO_ADJT, _______, EU_TDOT, KC_DQUO, KC_LT,   KC_GT,   _______, KC_CAPS,
                                 KC_MUTE, _______, _______, _______, _______, _______, _______, _______, _______, KC_INS

    ),
/*
 * Navigation Layer: Number/Function keys, navigation
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |   1  |  2   |  3   |  4   |  5   |                              |  6   |  7   |  8   |  9   |  0   |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |                              |      | Left | Up   | Down | Right|        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NAV] = LAYOUT(
      _______, KC_1, 	KC_2,    KC_3,    KC_4,    KC_5,                                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
      _______, _______, _______, _______, _______, _______,                                     _______, KC_LEFT, KC_UP, KC_DOWN,   KC_RGHT, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
/*
 * Adjust Layer: RGB
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        | TOG  | SAI  | HUI  | VAI  | MOD  |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      | SAD  | HUD  | VAD  | RMOD |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_ADJUST] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
      _______, RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI, RGB_MOD,                                     _______, _______, _______, _______, _______, _______,
      _______, _______, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD,_______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
// /*
//  * Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     ),
};
// clang-format on

/* void keyboard_post_init_user(void) { */
/*   rgblight_setrgb(51, 135, 204); */
/* } */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case CLO_TAP:
                close_tap_it = close_tap_it & CLO_ACTIVE?
                    CLO_USED:
                    CLO_ACTIVE|CLO_PRESSED;
                return false;
            case QK_LEADER:
                close_tap_it = CLO_DISABLED;
                return true;
        }
    } else if (close_tap_it & CLO_ACTIVE &&
               keycode != CLO_TAP &&
               keycode != OSL(_RAISE) &&
               keycode != OSL(_LOWER) &&
               keycode != MO(_NAV)) {

        close_tap_it = close_tap_it & CLO_PRESSED?
            close_tap_it | CLO_USED:
            CLO_DISABLED;
        switch(keycode)
        {
        case KC_LPRN:
          tap_code16(KC_RPRN);
          tap_code16(KC_LEFT);
          break;
        case KC_RPRN:
          tap_code16(KC_LEFT);
          tap_code16(KC_LPRN);
          break;
        case KC_LCBR:
          tap_code16(KC_RCBR);
          tap_code16(KC_LEFT);
          break;
        case KC_RCBR:
          tap_code16(KC_LEFT);
          tap_code16(KC_LCBR);
          break;
        case KC_LBRC:
          tap_code16(KC_RBRC);
          tap_code16(KC_LEFT);
          break;
        case KC_RBRC:
          tap_code16(KC_LEFT);
          tap_code16(KC_LBRC);
          break;
        case KC_LT:
          tap_code16(KC_GT);
          tap_code16(KC_LEFT);
          break;
        case KC_GT:
          tap_code16(KC_LEFT);
          tap_code16(KC_LT);
          break;
        default:
          tap_code16(keycode);
          tap_code16(KC_LEFT);
          break;
        }
    } else {
        switch (keycode) {
            case CLO_TAP:
                close_tap_it = close_tap_it & CLO_USED?
                    CLO_DISABLED:
                    CLO_RELEASE(close_tap_it);
        }
    }

    return true;
}

//layer_state_t layer_state_set_user(layer_state_t state) { return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST); }

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_180; }

// clang-format off
static void render_qmk_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
        0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
        0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};

    oled_write_P(qmk_logo, false);
}
// clang-format on
static void render_static_info(void) {
    render_qmk_logo();
    oled_write_P(PSTR("Kyria rev1.0\n"), false);
    oled_write_P(PSTR("Keymap: plattfot v2\n"), false);
}

static void render_status(void) {
    // QMK Logo and version information
    render_qmk_logo();
    oled_write_P(PSTR("Kyria rev1.0\n"), false);
    oled_write_P(PSTR("v" QMK_VERSION "\n"), false);

    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case _DEFAULT:
            oled_write_P(PSTR("base\n"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("<-sym/fun->\n"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("<-fun/sym->\n"), false);
            break;
        case _NAV:
            oled_write_P(PSTR("num/nav\n"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("adjust\n"), false);
            break;
        default:
            oled_write_P(PSTR("undefined\n"), false);
    }

    // Host Keyboard LED Status and Double tap
    led_t led_state = host_keyboard_led_state();
    if (led_state.num_lock) {
        oled_write_P(PSTR("NUMLCK "), false);
    } else if (close_tap_it) {
        oled_write_P(PSTR("Close  "), false);
    } else {
        oled_write_P(PSTR("       "), false);
    }

    if (led_state.caps_lock) {
        oled_write_P(PSTR("CAPLCK "), false);
    } else if (close_tap_it) {
        oled_write_P(PSTR("Tap    "), false);
    } else {
        oled_write_P(PSTR("       "), false);
    }

    oled_write_P(led_state.scroll_lock ? PSTR("SCRLCK ") : PSTR("       "), false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_static_info();
    }
    return false;
}
#endif

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        switch (get_highest_layer(layer_state)) {
            case _LOWER:
                // Skip/Prev song
                if (clockwise) {
                    tap_code(KC_MNXT);
                    clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
                } else {
                    tap_code(KC_MPRV);
                    clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
                }
                break;
            case _NAV:
                // Brightness control
                if (clockwise) {
                    tap_code(KC_BRIU);
                    clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
                } else {
                    tap_code(KC_BRID);
                    clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
                }
                break;
            default:
                // Volume control
                if (clockwise) {
                    tap_code(KC_VOLU);
                    clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
                } else {
                    tap_code(KC_VOLD);
                    clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
                }
                break;
        }
    } else if (index == 1) {
        switch (get_highest_layer(layer_state)) {
            case _RAISE:
                // Scroll through the workspaces
                if (clockwise) {
                    tap_code16(G(KC_GT));
                    clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
                } else {
                    tap_code16(G(KC_LT));
                    clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
                }
                break;
            default:
                // Scrolling
                if (clockwise) {
                    tap_code(KC_PGDN);
                    clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
                } else {
                    tap_code(KC_PGUP);
                    clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
                }
                break;
        }
    }
    return true;
}
#endif

LEADER_EXTERNS();

void matrix_scan_user(void) {
    LEADER_DICTIONARY() {
        leading = false;
        leader_end();
        // Sway navigation
        SEQ_ONE_KEY(KC_Q) {  // Jump to workspace 1
            SEND_STRING(SS_LGUI("1"));
        }
        SEQ_ONE_KEY(KC_W) {  // Jump to workspace 2
            SEND_STRING(SS_LGUI("2"));
        }
        SEQ_ONE_KEY(KC_E) {  // Jump to workspace 3
            SEND_STRING(SS_LGUI("3"));
        }
        SEQ_ONE_KEY(KC_R) {  // Jump to workspace 4
            SEND_STRING(SS_LGUI("4"));
        }
        SEQ_ONE_KEY(KC_T) {  // Jump to workspace 5
            SEND_STRING(SS_LGUI("5"));
        }

        SEQ_ONE_KEY(KC_Y) {  // Jump to workspace 6
            SEND_STRING(SS_LGUI("6"));
        }
        SEQ_ONE_KEY(KC_U) {  // Jump to workspace 7
            SEND_STRING(SS_LGUI("7"));
        }
        SEQ_ONE_KEY(KC_I) {  // Jump to workspace 8
            SEND_STRING(SS_LGUI("8"));
        }
        SEQ_ONE_KEY(KC_O) {  // Jump to workspace 9
            SEND_STRING(SS_LGUI("9"));
        }
        SEQ_ONE_KEY(KC_P) {  // Jump to workspace 0
            SEND_STRING(SS_LGUI("0"));
        }
        SEQ_ONE_KEY(KC_G) {  // View scratch pad
            SEND_STRING(SS_LGUI("-"));
        }

        // Sway move window
        SEQ_TWO_KEYS(KC_M, KC_Q) {  // Move to workspace 1
            SEND_STRING(SS_LSFT(SS_LGUI("1")));
        }
        SEQ_TWO_KEYS(KC_M, KC_W) {  // Move to workspace 2
            SEND_STRING(SS_LSFT(SS_LGUI("2")));
        }
        SEQ_TWO_KEYS(KC_M, KC_E) {  // Move to workspace 3
            SEND_STRING(SS_LSFT(SS_LGUI("3")));
        }
        SEQ_TWO_KEYS(KC_M, KC_R) {  // Move to workspace 4
            SEND_STRING(SS_LSFT(SS_LGUI("4")));
        }
        SEQ_TWO_KEYS(KC_M, KC_T) {  // Move to workspace 5
            SEND_STRING(SS_LSFT(SS_LGUI("5")));
        }

        SEQ_TWO_KEYS(KC_M, KC_Y) {  // Move to workspace 6
            SEND_STRING(SS_LSFT(SS_LGUI("6")));
        }
        SEQ_TWO_KEYS(KC_M, KC_U) {  // Move to workspace 7
            SEND_STRING(SS_LSFT(SS_LGUI("7")));
        }
        SEQ_TWO_KEYS(KC_M, KC_I) {  // Move to workspace 8
            SEND_STRING(SS_LSFT(SS_LGUI("8")));
        }
        SEQ_TWO_KEYS(KC_M, KC_O) {  // Move to workspace 9
            SEND_STRING(SS_LSFT(SS_LGUI("9")));
        }
        SEQ_TWO_KEYS(KC_M, KC_P) {  // Move to workspace 0
            SEND_STRING(SS_LSFT(SS_LGUI("0")));
        }
        SEQ_TWO_KEYS(KC_M, KC_G) {  // Move to scratch pad
            SEND_STRING(SS_LSFT(SS_LGUI("-")));
        }
    }
}

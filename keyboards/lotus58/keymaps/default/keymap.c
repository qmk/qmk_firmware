/* Copyright 2021 TweetyDaBird
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

enum layers {
    _QWERTY,
    _NUM,
    _FUNC,
    _SYSTEM,
};

enum custom_keycodes {
    KC_QWERTY = SAFE_RANGE,
    KC_NUM,
    KC_FUNC,
};

// Tap Dance declarations
enum {
    MEDIA_SCROLL,
    PG_UP,
    PG_DN,
    DEL_INS,
    ESC_PIPE,
};

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    [MEDIA_SCROLL] = ACTION_TAP_DANCE_DOUBLE(KC_MPLY, KC_MUTE),
    [PG_DN] = ACTION_TAP_DANCE_DOUBLE(KC_DOWN, KC_PGDN),
    [PG_UP] = ACTION_TAP_DANCE_DOUBLE(KC_UP, KC_PGUP),
    [DEL_INS] = ACTION_TAP_DANCE_DOUBLE(KC_DEL, KC_INS),
    [ESC_PIPE] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_NUBS),
};

#define CK_ESC TD(ESC_PIPE)
#define CK_LCTRL MT(MOD_LCTL, KC_LEFT)
#define CK_LALT MT(MOD_LALT, KC_RGUI)
#define CK_LSPC MT(MOD_LSFT, KC_SPC)
#define CK_DELINS TD(DEL_INS)
#define CK_RENT MT(MOD_RSFT, KC_ENT)
#define CK_RALT MT(MOD_RALT, KC_APP)
#define CK_RCTRL MT(MOD_RCTL, KC_RIGHT)

/* Keymap for reference
 * ,-----------------------------------------.                    ,------------------------------------------.
 * | Esc  |   1  |   2  |   3  |   4  |   5  |   ___        ___   |   6  |   7  |   8  |   9  |   0  |   +   |
 * |------+------+------+------+------+------|  /   \      /   \  |------+------+------+------+------+-------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  | ( ENC )    ( ENC ) |   Y  |   U  |   I  |   O  |   P  |   Å   |
 * |------+------+------+------+------+------|  \___/      \___/  |------+------+------+------+------+-------|
 * |   '  |   A  |   S  |   D  |   F  |   G  |                    |   H  |   J  |   K  |   L  |   Ö  |   Ä   |
 * |------+------+------+------+------+------|-------.    ,-------|------+------+------+------+------+-------|
 * | Left |   Z  |   X  |   C  |   V  |   B  |  Down |    |  Up   |   N  |   M  |   ,  |   .  |   -  | Right |
 * `-----------------------------------------|-------/    \-------|------------------------------------------'
 *                    | Del  | Lower| Alt | / Space /      \ Enter \ |  Alt |Raise | Bksp |
 *                    | Ins  |      | Win |/ Shift /        \ Shift \| Menu |      |      |
 *                    `-------------------'-------'          '-------'--------------------'
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = LAYOUT(

    CK_ESC, KC_1, KC_2,   KC_3,     KC_4,    KC_5,                             KC_6, KC_7,      KC_8,    KC_9,   KC_0,    KC_MINS,
    KC_TAB, KC_Q, KC_W,   KC_E,     KC_R,    KC_T,                             KC_Y, KC_U,      KC_I,    KC_O,   KC_P,    KC_LBRC,
   KC_NUHS, KC_A, KC_S,   KC_D,     KC_F,    KC_G,                             KC_H, KC_J,      KC_K,    KC_L,   KC_SCLN, KC_QUOT,
  CK_LCTRL, KC_Z, KC_X,   KC_C,     KC_V,    KC_B, TD(PG_DN),      TD(PG_UP),  KC_N, KC_M,      KC_COMM, KC_DOT, KC_SLSH, CK_RCTRL,
            KC_LGUI, CK_DELINS, TT(_NUM), CK_LALT,   CK_LSPC,      CK_RENT, CK_RALT, TT(_FUNC), KC_BSPC, TD(MEDIA_SCROLL)
),

[_NUM] = LAYOUT(
  _______,   KC_F1,   KC_F2,    KC_F3,   KC_F4,   KC_F5,                         KC_CIRC,    KC_7,    KC_8,    KC_9, XXXXXXX, XXXXXXX,
  _______, XXXXXXX,   KC_UP,  XXXXXXX, XXXXXXX, XXXXXXX,                         KC_HASH,    KC_4,    KC_5,    KC_6, XXXXXXX, XXXXXXX,
  XXXXXXX, KC_LEFT, KC_DOWN, KC_RIGHT, KC_LBRC, KC_RBRC,                         KC_AMPR,    KC_1,    KC_2,    KC_3, XXXXXXX, XXXXXXX,
  _______, XXXXXXX, KC_PAST,  KC_PPLS, KC_PSLS,  KC_EQL, _______,       _______,  KC_DLR,    KC_0, KC_SCLN, KC_COLN, KC_PMNS, _______,
                    _______,  _______, _______, _______, _______,       _______, _______, _______, _______, _______
),

[_FUNC] = LAYOUT(
  _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                           KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, _______,
  _______, _______, _______, _______, _______, _______,                         _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                         _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______, _______,
                    _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______
),

  [_SYSTEM] = LAYOUT(
  XXXXXXX , XXXXXXX,  XXXXXXX ,  XXXXXXX , XXXXXXX, XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  RESET  , XXXXXXX,KC_QWERTY,XXXXXXX,XXXXXXX,KC_ASTG,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX , XXXXXXX,XXXXXXX, XXXXXXX,    XXXXXXX,  XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX , XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,  XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                   _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______ \
  )
};

#ifdef OLED_ENABLE

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
        0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
        0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0
    };

    oled_write_P(qmk_logo, false);
}

static void print_status_narrow(void) {
    // Print current mode
    oled_write_P(PSTR("\n"), false);
  oled_write_P(PSTR(""), false);
    oled_write_P(PSTR("Lotus -58-"), false);
  oled_write_P(PSTR("\n"), false);

    switch (get_highest_layer(default_layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("Qwrty"), false);
            break;
        default:
            oled_write_P(PSTR("Undef"), false);
    }
    oled_write_P(PSTR("\n"), false);
    // Print current layer
    oled_write_P(PSTR("Layer"), false);
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("-Base\n"), false);
            break;
        case _FUNC:
            oled_write_P(PSTR("-Func\n"), false);
            break;
        case _NUM:
            oled_write_P(PSTR("-Num \n"), false);
            break;
        case _SYSTEM:
            oled_write_P(PSTR("-Sys \n"), false);
            break;
        default:
            oled_write_P(PSTR("Undef"), false);
    }
    oled_write_P(PSTR("\n"), false);
    led_t led_usb_state = host_keyboard_led_state();
    oled_write_ln_P(PSTR("CPSLK"), led_usb_state.caps_lock);
    oled_write_P(PSTR("\n"), false);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    }
    return rotation;
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        render_logo();
    }
}

#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
    }
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
   return update_tri_layer_state(state, _NUM, _FUNC, _SYSTEM);
}

#ifdef ENCODER_ENABLE

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    } else if (index == 1) {
        if (clockwise) {
            if (get_mods() & MOD_MASK_CTRL) {
                tap_code(KC_MPRV);
            } else {
                tap_code(KC_VOLD);
            }

        } else {
            if (get_mods() & MOD_MASK_CTRL) {
                tap_code(KC_MNXT);
            } else {
                tap_code(KC_VOLU);
            }
        }
    }
    return true;
}

#endif

/* Copyright 2020 Adam Naldal <adamnaldal@gmail.com>
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
    _QWERTY = 0,
    _NN,
    _MS,
    _SP
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: QWERTY
 *
 *     ,-------------------------------------------.                            ,-------------------------------------------.
 *     |   TAB  |   Q  |   W  |   E  |   R  |   T  |                            |   Y  |   U  |   I  |   O  |   P  |  ESC   |
 *     |--------+------+------+------+------+------|                            |------+------+------+------+------+--------|
 *     |   CTRL |   A  |   S  |   D  |   F  |   G  |                            |   H  |   J  |   K  |   L  | ;  : |  ' "   |
 *     |--------+------+------+------+------+------|                            |------+------+------+------+------+--------|
 *     | LShift |   Z  |   X  |   C  |   V  |   B  |                            |   N  |   M  | ,  < | . >  | /  ? |  SHIFT |
 *     `------------------------⫟------⫟------⫟------⫟------.         ,-----⫟------⫟------⫟------⫟-------------------------'
 *                              | GUI  | Caps | Space| Nav +|         |Media+| Bksp | Enter| AltGr|
 *                              |      |      |      |Number|         |symbol|      |      |      |
 *                              `---------------------------'         `---------------------------'
 */
    [_QWERTY] = LAYOUT_split_3x6_4(
      //,-----------------------------------------------------.                            ,-----------------------------------------------------.
           KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                 KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_ESC,
      //|--------+--------+--------+--------+--------+--------|                            |--------+--------+--------+--------+--------+--------|
          KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                                 KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
      //|--------+--------+--------+--------+--------+--------|                            |--------+--------+--------+--------+--------+--------|
          KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                                 KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
      //|--------+--------+-----------⫟--------⫟--------⫟--------⫟--------.   .--------⫟--------⫟--------⫟--------⫟-----------+--------+--------|
                                        KC_LGUI,  KC_CAPS,   KC_SPC, MO(_NN),     MO(_MS), KC_BSPC,  KC_ENT, KC_RALT
                                    //`------------------------------------'  '------------------------------------'
    ),
  /*
   * Navigation and Numbers: _NN
   *
   *     ,-------------------------------------------.                            ,-------------------------------------------.
   *     |   TAB  |   1  |   2  |   3  |   4  |   5  |                            |   6  |   7  |   8  |   9  |   0  |  ESC   |
   *     |--------+------+------+------+------+------|                            |------+------+------+------+------+--------|
   *     |   CTRL |  F1  |  F2  |  F3  |  F4  |  F5  |                            | left | down |  up  | right|      |        |
   *     |--------+------+------+------+------+------|                            |------+------+------+------+------+--------|
   *     | LShift |  F6  |  F7  |  F8  |  F9  | F10  |                            | home | pgdn | pgup |  end |      |  SHIFT |
   *     `------------------------⫟------⫟------⫟------⫟------.         ,-----⫟------⫟------⫟------⫟-------------------------'
   *                              | GUI  | Del  | Space| Nav +|         |Media+|Back- | Enter| AltGr|
   *                              |      |      |      |Number|         |symbol|space |      |      |
   *                              `---------------------------'         `---------------------------'
   */
   [_NN] = LAYOUT_split_3x6_4(
     //,-----------------------------------------------------.                            ,-----------------------------------------------------.
          KC_TAB,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                 KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_ESC,
     //|--------+--------+--------+--------+--------+--------|                            |--------+--------+--------+--------+--------+--------|
         KC_LCTL,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, XXXXXXX, XXXXXXX,
     //|--------+--------+--------+--------+--------+--------|                            |--------+--------+--------+--------+--------+--------|
         KC_LSFT,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,                              KC_HOME, KC_PGDN, KC_PGUP,  KC_END, XXXXXXX, KC_RSFT,
     //|--------+--------+-----------⫟--------⫟--------⫟--------⫟--------.   .--------⫟--------⫟--------⫟--------⫟-----------+--------+--------|
                                       KC_LGUI,  KC_DEL,   KC_SPC, _______,     _______, KC_BSPC,  KC_ENT, KC_RALT
                                   //`------------------------------------'  '------------------------------------'
   ),
 /*
  * Media and Symbols: _MS
  *
  *     ,-------------------------------------------.                            ,-------------------------------------------.
  *     |   TAB  |   !  |   @  |   #  |   $  |   %  |                            |   ^  |   &  |   *  |   (  |   )  |  ESC   |
  *     |--------+------+------+------+------+------|                            |------+------+------+------+------+--------|
  *     |   CTRL |      | prev | play | next | vol+ |                            |   -  |   =  |   {  |   }  |  |   |   ´    |
  *     |--------+------+------+------+------+------|                            |------+------+------+------+------+--------|
  *     | LShift |      |brght-|brght+| mute | vol- |                            |   _  |   +  |   [  |   ]  |  \  |   ~    |
  *     `------------------------⫟------⫟------⫟------⫟------.         ,-----⫟------⫟------⫟------⫟-------------------------'
  *                              | GUI  | Del  | Space| Nav +|         |Media+| Bksp | Enter| AltGr|
  *                              |      |      |      |Number|         |symbol|      |      |      |
  *                              `---------------------------'         `---------------------------'
  */
  [_MS] = LAYOUT_split_3x6_4(
    //,-----------------------------------------------------.                            ,-----------------------------------------------------.
         KC_TAB, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                              KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,  KC_ESC,
    //|--------+--------+--------+--------+--------+--------|                            |--------+--------+--------+--------+--------+--------|
        KC_LCTL, XXXXXXX, KC_MRWD, KC_MPLY, KC_MFFD, KC_VOLU,                              KC_MINS,  KC_EQL, KC_LCBR, KC_RCBR, KC_PIPE,  KC_GRV,
    //|--------+--------+--------+--------+--------+--------|                            |--------+--------+--------+--------+--------+--------|
        KC_LSFT, XXXXXXX, KC_BRID, KC_BRIU, KC_MUTE, KC_VOLD,                              KC_UNDS, KC_PLUS, KC_LBRC, KC_RBRC, KC_BSLS, KC_TILD,
    //|--------+--------+-----------⫟--------⫟--------⫟--------⫟--------.   .--------⫟--------⫟--------⫟--------⫟-----------+--------+--------|
                                      KC_LGUI,  KC_DEL,   KC_SPC, _______,     _______, KC_BSPC,  KC_ENT, KC_RALT
                                  //`------------------------------------'  '------------------------------------'
  ),
/*
 * Special functions: _SP
 *
 *     ,-------------------------------------------.                            ,-------------------------------------------.
 *     |   TAB  |      |      |      | RESET|      |                            |      |      |      |      |      |  ESC   |
 *     |--------+------+------+------+------+------|                            |------+------+------+------+------+--------|
 *     |   CTRL |      |      | DEBUG|      |      |                            |      |      |      |      |      |        |
 *     |--------+------+------+------+------+------|                            |------+------+------+------+------+--------|
 *     | LShift |      |      |      |      |      |                            |      |      |      |      |      |  SHIFT |
 *     `------------------------⫟------⫟------⫟------⫟------.         ,-----⫟------⫟------⫟------⫟-------------------------'
 *                              | GUI  | Del  | Space| Nav +|         |Media+| Bksp | Enter| AltGr|
 *                              |      |      |      |Number|         |symbol|      |      |      |
 *                              `---------------------------'         `---------------------------'
 */
 [_SP] = LAYOUT_split_3x6_4(
   //,-----------------------------------------------------.                            ,-----------------------------------------------------.
        KC_TAB, XXXXXXX, XXXXXXX, XXXXXXX,   RESET, XXXXXXX,                              XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_ESC,
   //|--------+--------+--------+--------+--------+--------|                            |--------+--------+--------+--------+--------+--------|
       KC_LCTL, XXXXXXX, XXXXXXX,   DEBUG, XXXXXXX, XXXXXXX,                              XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|                            |--------+--------+--------+--------+--------+--------|
       KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                              XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_RSFT,
   //|--------+--------+-----------⫟--------⫟--------⫟--------⫟--------.   .--------⫟--------⫟--------⫟--------⫟-----------+--------+--------|
                                     KC_LGUI,  KC_DEL,   KC_SPC, _______,     _______, KC_BSPC,  KC_ENT, KC_RALT
                                 //`------------------------------------'  '------------------------------------'
 ),

};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _NN, _MS, _SP);
}

#ifdef OLED_ENABLE

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };

    oled_write_P(qmk_logo, false);
}

static void print_status_narrow(void) {
    // Print current mode
    oled_write_P(PSTR("\n"), false);
    oled_write_ln_P(PSTR("MODE"), false);
    oled_write_ln_P(PSTR(""), false);

    oled_write_P(PSTR("\n\n"), false);
    // Print current layer
    oled_write_ln_P(PSTR("LAYER"), false);
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("Base\n"), false);
            break;
        case _NN:
            oled_write_P(PSTR("Nums\n"), false);
            break;
        case _MS:
            oled_write_P(PSTR("Sym\n"), false);
            break;
        case _SP:
            oled_write_P(PSTR("Spec\n"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef\n"), false);
    }
    oled_write_P(PSTR("\n\n"), false);
    led_t led_usb_state = host_keyboard_led_state();
    oled_write_ln_P(PSTR("CPSLK"), led_usb_state.caps_lock);
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

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        // master side thumb encoder
        // Volume control
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    else if (index == 1) {
        // master side pinky encoder
        // Page down / Page up
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
    else if (index == 2) {
        // minion side thumb encoder
        // Next track / Previous track
        if (clockwise) {
            tap_code(KC_MFFD);
        } else {
            tap_code(KC_MRWD);
        }
    }
    else if (index == 3) {
        // minion side pinky encoder
        // Page end / Page home
        if (clockwise) {
            tap_code(KC_END);
        } else {
            tap_code(KC_HOME);
        }
    }
    return true;
}
#endif

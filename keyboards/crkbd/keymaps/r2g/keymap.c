/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

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

static bool mo1_active = false;
static bool mo2_active = false;
static bool mo3_active = false;
static bool mo4_active = false;

enum layers {
  _QWERTY,
  _SIMBOLS,
  _NAVIGATE,
  _ADJUST,
  _DVORAK
};

enum custom_keycodes {
  QWERTY, //= SAFE_RANGE,
  SIMBOLS,
  NAVIGATE,
  ADJUST,
  DVORAK
};

// Tap Dance declarations
enum {
    TD_ESC_CAPS,
    TD_RALT_LALT,
    TD_HOME_END,
};

//Action press for each the layers
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MO(1):
            if (record->event.pressed) {
                mo1_active = !mo1_active;
                if (mo1_active) {
                    layer_on(1);
                } else {
                    layer_off(1);
                }
            }
            return false;
        case MO(2):
            if (record->event.pressed) {
                mo2_active = !mo2_active;
                if (mo2_active) {
                    layer_on(2);
                } else {
                    layer_off(2);
                }
            }
            return false;
        case MO(3):
            if (record->event.pressed) {
                mo3_active = !mo3_active;
                if (mo3_active) {
                    layer_on(3);
                } else {
                    layer_off(3);
                }
            }
            return false;
            case MO(4):
            if (record->event.pressed) {
                mo4_active = !mo4_active;
                if (mo4_active) {
                    layer_on(4);
                    register_code(KC_A);  // Ejemplo de mensaje de depuración
                } else {
                    layer_off(4);
                    unregister_code(KC_A);  // Ejemplo de mensaje de depuración
                }
            }
            return false;
        default:
            return true;
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
TD(TD_ESC_CAPS),  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,  KC_ENT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_TAB, 
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   MO(1),  KC_SPC,     KC_SPC,   MO(2), TD(TD_RALT_LALT)
                                      //`--------------------------'  `--------------------------'

  ),

   [_SIMBOLS] = LAYOUT( 
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, KC_PGUP,   KC_UP, KC_PGDN,  KC_GRV, KC_BSLS,                      KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,  KC_ENT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, KC_LEFT, KC_DOWN, KC_RIGHT,KC_TILD, KC_SLSH,                      KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,  KC_TAB,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_SPC,   MO(3), KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),
  
    [_NAVIGATE] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_LCTL, KC_PGUP,   KC_UP, KC_PGDN,   KC_F4, KC_PSCR,                      KC_PSLS,    KC_1,    KC_2,    KC_3, KC_PPLS, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, KC_LEFT, KC_DOWN, KC_RIGHT,  KC_F5, TD(TD_HOME_END),              KC_PAST,    KC_4,    KC_5,    KC_6, KC_PMNS, KC_PEQL,  
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
TD(TD_RALT_LALT), KC_CALC, XXXXXXX, KC_MUTE, KC_VOLD, KC_VOLU,                   KC_PCMM,    KC_7,    KC_8,    KC_9,    KC_0,  KC_ESC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   MO(4),  KC_SPC,     KC_ENT, _______, KC_DEL
                                      //`--------------------------'  `--------------------------'
  ),

    [_ADJUST] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, XXXXXXX,                      RGB_M_P, RGB_M_B, RGB_M_R,RGB_M_SW,RGB_M_SN, RGB_M_K,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, RGB_TOG,                      RGB_M_X, RGB_M_G, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_ENT, _______, KC_LCTL
                                      //`--------------------------'  `--------------------------'
  ),

    [_DVORAK] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
TD(TD_ESC_CAPS), KC_QUOT, KC_COMM, KC_DOT,   KC_P,    KC_Y,                         KC_F,    KC_G,    KC_C,    KC_R,    KC_L, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_A,    KC_O,    KC_E,    KC_U,    KC_I,                         KC_D,    KC_H,    KC_T,    KC_N,    KC_S,  KC_ENT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, KC_SCLN,    KC_Q,    KC_J,    KC_K,    KC_X,                         KC_B,    KC_M,    KC_W,    KC_V,   KC_Z,   KC_TAB,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_SPC, _______, TD(TD_RALT_LALT)
                                      //`--------------------------'  `--------------------------'

  ),

};

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {

    // Tap once for Escape, twice for Caps Lock
    [TD_ESC_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS),
    [TD_RALT_LALT] = ACTION_TAP_DANCE_DOUBLE(KC_RALT, KC_LALT),
    [TD_HOME_END] = ACTION_TAP_DANCE_DOUBLE(KC_HOME, KC_END),
};

#ifdef RGB_MATRIX_ENABLE

void suspend_power_down_user(void) {
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_user(void) {
    rgb_matrix_set_suspend_state(false);
}

#endif

// RGB_MODE_PLAIN	RGB_M_P 	Modo estático (sin animación)
// RGB_MODE_BREATHE	RGB_M_B	    Modo de animación de respiración
// RGB_MODE_RAINBOW	RGB_M_R	    Modo de animación arcoíris
// RGB_MODE_SWIRL	RGB_M_SW	Modo de animación de remolino
// RGB_MODE_SNAKE	RGB_M_SN	Modo de animación de serpiente
// RGB_MODE_KNIGHT	RGB_M_K	    Modo de animación "Knight Rider"
// RGB_MODE_XMAS	RGB_M_X	    Modo de animación navideña
// RGB_MODE_GRADIENT RGB_M_G	Modo de animación de degradado estático
// RGB_MODE_RGBTEST	RGB_M_T	    Modo de animación de prueba rojo, verde y azul   


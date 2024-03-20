/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert
Copyright 2021 Franco Rosi <fraanrosi@gmail.com>

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

// Following line allows macro to read current RGB settings
#ifdef RGBLIGHT_ENABLE
uint8_t                  RGB_current_mode;
HSV                      CURRENT_COLOR;
bool                     caps_is_active = false;
/*Here I set the first rgb mode*/
void keyboard_post_init_user(void) {
    rgblight_enable();  // Enables RGB, without saving settings
    rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL + 3);
    RGB_current_mode = rgblight_get_mode();
    rgblight_sethsv(HSV_RED);
    CURRENT_COLOR = rgblight_get_hsv();
}
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
    _QWERTY = 0,
    _LOWER,
    _RAISE
};

enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    LOWER,
    RAISE,
    RGBRST,
    RGB_1,
    RGB_2,
    RGB_3,
    RGB_4,
    RGB_5,
    RGB_6,
    RGB_7,
    RGB_8,
    RGB_9
};

#define LOWER MO(1)
#define RAISE MO(2)


// HELIX_ROWS == 5
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Qwerty
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |   |  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  | Del  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  | Bksp |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | CAPS |   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |   Ñ  |Enter |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |Shift |   Z  |   X  |   C  |   V  |   B  |   {  |   }  |   N  |   M  |   ,  |   .  |   -  |Shift |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Ctrl | Esc  | Win  | Alt  |Raise |Lower |Space |Space |Alt Gr| Left |  Up  | Down |Right | Ctrl |
   * `-------------------------------------------------------------------------------------------------'
   */
    [_QWERTY] = LAYOUT(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   KC_QUOT,  KC_NUHS, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
        KC_LCTL, KC_ESC,  KC_LGUI, KC_LALT, MO(2),   MO(1),  KC_SPC,   KC_SPC,  KC_RALT, KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT, KC_RCTL
        ),

    /*Lower
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |             |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      | Mute | Play |Mouse1|Mouse2|      |             |Print |      |Insert|' ? \ | ¿  ¡ |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |Shine+|Shine-| Vol -| Vol +|      |             |      |Mouse↑|      | ´  ¨ |+ * ~ |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      | <  > |      |      |      |      |      |      |Mouse←|Mouse↓|Mouse→|      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      | Home |PageUp|PageDn| End  |      |
   * `-------------------------------------------------------------------------------------------------'
   */
    [_LOWER] = LAYOUT(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
        KC_TRNS, KC_MUTE, KC_MPLY, KC_BTN1, KC_BTN2, KC_TRNS,                   KC_PSCR, KC_TRNS, KC_INS,  KC_MINS, KC_EQL,  KC_TRNS,
        KC_NO,   KC_BRID, KC_BRIU, KC_VOLD, KC_VOLU, KC_TRNS,                   KC_TRNS, KC_MS_U, KC_TRNS, KC_LBRC, KC_RBRC, KC_TRNS,
        KC_TRNS, KC_NUBS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS,  KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS,  KC_TRNS, KC_TRNS, KC_HOME, KC_PGUP, KC_PGDN, KC_END,  KC_TRNS
        ),

    /* Raise
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |      |      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | RGB1 | RGB2 | RGB3 | RGB4 |RGB ON|      |             |      | MODE+| MODE-|      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | RGB5 | RGB6 | RGB7 | RGB8 | RGB9 |      |             |      | HUE+ | HUE- |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      | MODE+| MODE-| HUE+ | HUE- |      | Reset|      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
    [_RAISE] = LAYOUT(
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        RGB_1,   RGB_2,   RGB_3,   RGB_4,   RGB_TOG, KC_NO,                     KC_NO,   RGB_MOD, RGB_RMOD,KC_NO,   KC_NO,   KC_NO,
        RGB_5,   RGB_6,   RGB_7,   RGB_8,   RGB_9,   KC_NO,                     KC_NO,   RGB_HUI, RGB_HUD, KC_NO,   KC_NO,   KC_NO,
        KC_NO,   RGB_MOD, RGB_RMOD,RGB_HUI, RGB_HUD, KC_NO,  QK_BOOT,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_TRNS, KC_NO,  KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO
        )
};

// define variables for reactive RGB
bool TOG_STATUS = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LOWER:
            if (record->event.pressed) {
                // not sure how to have keyboard check mode and set it to a variable, so my work around
                // uses another variable that would be set to true after the first time a reactive key is pressed.
                if (TOG_STATUS) {  // TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
                } else {
                    TOG_STATUS = !TOG_STATUS;
                    #ifdef RGBLIGHT_ENABLE
                        if (!caps_is_active) {
                            RGB_current_mode = rgblight_get_mode();
                            CURRENT_COLOR    = rgblight_get_hsv();
                        }
                        rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
                        rgblight_sethsv(HSV_BLUE);
                    #endif
                }
                layer_on(_LOWER);
            } else {
                #ifdef RGBLIGHT_ENABLE
                    if (!caps_is_active) {
                        rgblight_mode(RGB_current_mode);
                        rgblight_sethsv(CURRENT_COLOR.h, CURRENT_COLOR.s, CURRENT_COLOR.v);
                    } else {
                        rgblight_mode(RGBLIGHT_MODE_ALTERNATING);
                        rgblight_sethsv(HSV_WHITE);
                    }
                #endif
                TOG_STATUS = false;
                layer_off(_LOWER);
            }
            return false;
            break;
        case RAISE:
            if (record->event.pressed) {
                // not sure how to have keyboard check mode and set it to a variable, so my work around
                // uses another variable that would be set to true after the first time a reactive key is pressed.
                if (TOG_STATUS) {  // TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
                } else {
                    TOG_STATUS = !TOG_STATUS;
                    #ifdef RGBLIGHT_ENABLE
                        if (!caps_is_active) {
                            RGB_current_mode = rgblight_get_mode();
                            CURRENT_COLOR    = rgblight_get_hsv();
                        }
                        rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
                        rgblight_sethsv(HSV_RED);
                    #endif
                }
                layer_on(_RAISE);
            } else {
                #ifdef RGBLIGHT_ENABLE
                    if (!caps_is_active) {
                        rgblight_mode(RGB_current_mode);
                        rgblight_sethsv(CURRENT_COLOR.h, CURRENT_COLOR.s, CURRENT_COLOR.v);
                    } else {
                        rgblight_mode(RGBLIGHT_MODE_ALTERNATING);
                        rgblight_sethsv(HSV_WHITE);
                    }
                #endif
                layer_off(_RAISE);
                TOG_STATUS = false;
            }
            return false;
            break;
            //led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
        case RGB_1 ... RGB_9:
            if (record->event.pressed) {
                rgblight_sethsv(CURRENT_COLOR.h, CURRENT_COLOR.s, CURRENT_COLOR.v);
                //this to have each custom mode separately, but sharing logic
                switch(keycode){
                    case RGB_1:
                        rgblight_mode(RGBLIGHT_MODE_RAINBOW_MOOD + 1);
                        break;
                    case RGB_2:
                        rgblight_mode(RGBLIGHT_MODE_KNIGHT);
                        break;
                    case RGB_3:
                        rgblight_mode(RGBLIGHT_MODE_SNAKE);
                        break;
                    case RGB_4:
                        rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL + 3);
                        break;
                    case RGB_5:
                        rgblight_mode(RGBLIGHT_MODE_TWINKLE + 5);
                        break;
                    case RGB_6:
                        rgblight_mode(RGBLIGHT_MODE_BREATHING + 3);
                        break;
                    case RGB_7:
                        rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
                        break;
                    case RGB_8:
                        rgblight_mode(RGBLIGHT_MODE_STATIC_GRADIENT + 5);
                        break;
                    case RGB_9:
                        rgblight_mode(RGBLIGHT_MODE_CHRISTMAS);
                        break;
                }
                RGB_current_mode = rgblight_get_mode();
                CURRENT_COLOR = rgblight_get_hsv();
            }
            return false;
            break;
        case RGB_TOG ... RGB_HUD:
            if (record->event.pressed) {
                rgblight_sethsv(CURRENT_COLOR.h, CURRENT_COLOR.s, CURRENT_COLOR.v);
                rgblight_mode(RGB_current_mode);
                process_rgb(keycode, record);
                RGB_current_mode = rgblight_get_mode();
                CURRENT_COLOR = rgblight_get_hsv();
            }
            return false;
            break;
        case KC_CAPS:
            if (record->event.pressed) {
                register_code(KC_CAPS);
                caps_is_active = !caps_is_active;
                if (caps_is_active) {
                    CURRENT_COLOR    = rgblight_get_hsv();
                    rgblight_mode(RGBLIGHT_MODE_ALTERNATING);
                    rgblight_sethsv(HSV_WHITE);
                } else if (!caps_is_active) {
                    unregister_code(KC_CAPS);
                    rgblight_mode(RGB_current_mode);
                    rgblight_sethsv(CURRENT_COLOR.h, CURRENT_COLOR.s, CURRENT_COLOR.v);
                }
            }
            return false;
            break;
        case RGBRST:
            #ifdef RGBLIGHT_ENABLE
                if (record->event.pressed) {
                    eeconfig_update_rgblight_default();
                    rgblight_enable();
                    RGB_current_mode = rgblight_get_mode();
                }
            #endif
            break;
    }
    return true;
}

void matrix_init_user(void) {
#ifdef RGBLIGHT_ENABLE
    RGB_current_mode = rgblight_get_mode();
    CURRENT_COLOR    = rgblight_get_hsv();
#endif
}

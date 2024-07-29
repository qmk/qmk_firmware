 /*
 Copyright 2020 Garret Gartner

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

enum avenue_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _FUNCTION
};



//Tap Dance Declarations:
enum avenue_tapcodes {
  TD_RST,
  TD_DBQT,
};

void dance_rst_reset (tap_dance_state_t *state, void *user_data) { // *Line_Note.001
  if (state->count >= 2) {
    reset_keyboard();
    reset_tap_dance(state);
  }
}

//Tap Dance Functions:
tap_dance_action_t tap_dance_actions[] = {
 [TD_RST] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, NULL, dance_rst_reset), // References "dance_rst_reset" (*Line_Note.001)
 [TD_DBQT] = ACTION_TAP_DANCE_DOUBLE (KC_QUOTE, KC_DQT)
};



// Keymap Customization:
#define LOWR  MO(_LOWER)
#define RISE  MO(_RAISE)
#define FN    MO(_FUNCTION)
#define GUI   KC_LGUI
#define ALT   KC_LALT
#define SPACE KC_SPACE

    /*
    *   ┌────┐
    *   │    │ = "TRANSPARENT" KEY LOCATION
    *   └────┘
    */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* _QWERTY (Base)
    *
    * ┌────┐ ┌────┐                                       ┌────┬────┬────┐
    * │MUTE│ │Esc │                                       │ \  │ -  │ =  │
    * └────┘ └────┘                                       └────┴────┴────┘
    * ┌────┐ ┌────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┐
    * │Home│ │Tab │ Q  │ W  │ E  │ R  │ T  │ Y  │ U  │ I  │ O  │ P  │BkSp│
    * ├────┤ ├────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┤
    * │PgUp│ │CAPS│ A  │ S  │ D  │ F  │ G  │ H  │ J  │ K  │ L  │ ;  │ '  │
    * ├────┤ ├────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┤
    * │PgDn│ │Shft│ Z  │ X  │ C  │ V  │ B  │ N  │ M  │ ,  │ .  │ /  │Entr│
    * ├────┤ ├────┼────┼────┼────┼────┼────┴────┼────┼────┼────┼────┼────┤
    * │End │ │CTL │GUI │ALT │FUNC│LOWR│    │    │RISE│Left│Down│ Up │Rght│
    * └────┘ └────┴────┴────┴────┴────┴─────────┴────┴────┴────┴────┴────┘
    */
    [_QWERTY] = LAYOUT_all(
        KC_MUTE,      KC_ESC,                                                                       KC_BSLS,   KC_MINUS,   KC_EQUAL,
        KC_HOME,      KC_TAB,    KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,      KC_O,      KC_P,       KC_BSPC,
        KC_PGUP,      KC_LCTL,   KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,      KC_L,      KC_SCLN,    KC_QUOT,
        KC_PGDN,      KC_LSFT,   KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,   KC_DOT,    KC_SLSH,    KC_ENT,
        KC_END,       KC_DEL,    GUI,    ALT,    FN,     LOWR,   SPACE,  SPACE,  RISE,   KC_LEFT,   KC_DOWN,   KC_UP,      KC_RIGHT
    ),

    /* _LOWER (Media / Symbols / Punctuation)
    *
    * ┌────┐ ┌────┐                                       ┌────┬────┬────┐
    * │ // │ │PRNT│                                       │ [  │ ]  │ `  │
    * └────┘ └────┘                                       └────┴────┴────┘
    * ┌────┐ ┌────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┐
    * │PLAY│ │    │ 1  │ 2  │ 3  │ 4  │ 5  │ 6  │ 7  │ 8  │ 9  │ 0  │    │
    * ├────┤ ├────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┤
    * │NEXT│ │    │ !  │ @  │ #  │ $  │ %  │ ^  │ &  │ *  │ (  │ )  │ "  │
    * ├────┤ ├────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┤
    * │PREV│ │    │    │    │    │    │    │    │    │    │    │    │    │
    * ├────┤ ├────┼────┼────┼────┼────┼────┴────┼────┼────┼────┼────┼────┤
    * │STOP│ │    │    │    │    │    │    │    │    │    │    │    │    │
    * └────┘ └────┴────┴────┴────┴────┴─────────┴────┴────┴────┴────┴────┘
    */
    [_LOWER] = LAYOUT_all(
        _______,      _______,                                                                                           KC_LBRC,   KC_RBRC,   KC_GRAVE,
        KC_MPLY,      _______,   KC_1,      KC_2,      KC_3,      KC_4,      KC_5,      KC_6,      KC_7,      KC_8,      KC_9,      KC_0,      _______,
        KC_MNXT,      _______,   KC_EXLM,   KC_AT,     KC_HASH,   KC_DLR,    KC_PERC,   KC_CIRC,   KC_AMPR,   KC_ASTR,   KC_LPRN,   KC_RPRN,   KC_DQT,
        KC_MPRV,      _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,
        KC_MSTP,      _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______
    ),

    /* _RAISE (Misc Modifiers / Extended Punctuation)
    *
    * ┌────┐ ┌────┐                                       ┌────┬────┬────┐
    * │PRNT│ │    │                                       │ {  │ }  │ ~  │
    * └────┘ └────┘                                       └────┴────┴────┘
    * ┌────┐ ┌────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┐
    * │    │ │    │    │    │    │    │    │    │    │    │    │    │    │
    * ├────┤ ├────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┤
    * │    │ │CAPS│    │    │    │    │    │    │    │    │    │    │    │
    * ├────┤ ├────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┤
    * │    │ │    │    │    │    │    │    │    │    │    │    │    │    │
    * ├────┤ ├────┼────┼────┼────┼────┼────┴────┼────┼────┼────┼────┼────┤
    * │    │ │    │    │    │    │    │    │    │    │    │    │    │    │
    * └────┘ └────┴────┴────┴────┴────┴─────────┴────┴────┴────┴────┴────┘
    */
    [_RAISE] = LAYOUT_all(
        KC_PSCR,      _______,                                                                                           KC_LCBR,   KC_RCBR,   KC_TILD,
        _______,      _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,
        _______,      KC_CAPS,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,
        _______,      _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,
        _______,      _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______
    ),

    /* _FUNCTION (F-Row / DFU Reset / RGB Toggle)
    *
    * ┌────┐ ┌────┐                                       ┌────┬────┬────┐
    * │RSET│ │RGB │                                       │F11 │F12 │F13 │
    * └────┘ └────┘                                       └────┴────┴────┘
    * ┌────┐ ┌────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┐
    * │    │ │    │ F1 │ F2 │ F3 │ F4 │ F5 │ F6 │ F7 │ F8 │ F9 │F10 │    │
    * ├────┤ ├────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┤
    * │    │ │    │    │    │    │    │    │    │    │    │    │    │    │
    * ├────┤ ├────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┤
    * │    │ │    │    │    │    │    │    │    │    │    │    │    │    │
    * ├────┤ ├────┼────┼────┼────┼────┼────┴────┼────┼────┼────┼────┼────┤
    * │    │ │    │    │    │    │    │    │    │    │    │    │    │    │
    * └────┘ └────┴────┴────┴────┴────┴─────────┴────┴────┴────┴────┴────┘
    */
    [_FUNCTION] = LAYOUT_all(
        TD(TD_RST),   RGB_TOG,                                                                                           KC_F11,    KC_F12,    KC_F13,
        _______,      _______,   KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5,     KC_F6,     KC_F7,     KC_F8,     KC_F9,     KC_F10,    _______,
        _______,      _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,
        _______,      _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,
        _______,      _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______
    )
};



//  KEYMAP TEMPLATE:
//
//  /* <_LAYER>:
//  *
//  * ┌────┐ ┌────┐                                       ┌────┬────┬────┐
//  * │    │ │    │                                       │    │    │    │
//  * └────┘ └────┘                                       └────┴────┴────┘
//  * ┌────┐ ┌────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┐
//  * │    │ │    │    │    │    │    │    │    │    │    │    │    │    │
//  * ├────┤ ├────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┤
//  * │    │ │    │    │    │    │    │    │    │    │    │    │    │    │
//  * ├────┤ ├────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┤
//  * │    │ │    │    │    │    │    │    │    │    │    │    │    │    │
//  * ├────┤ ├────┼────┼────┼────┼────┼────┴────┼────┼────┼────┼────┼────┤
//  * │    │ │    │    │    │    │    │    │    │    │    │    │    │    │
//  * └────┘ └────┴────┴────┴────┴────┴─────────┴────┴────┴────┴────┴────┘
//  */
//  [<LAYER>] = LAYOUT_all(
//      _______,      _______,                                                                                           _______,   _______,   _______,
//      _______,      _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,
//      _______,      _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,
//      _______,      _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,
//      _______,      _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______
//  )


// Per-Key Tapping Term Definitions:
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TD(TD_DBQT):
            return 235;
        default:
            return TAPPING_TERM;
    }
}

// Encoder Customization: (*Order-of-Keycode Specific)
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    return true;
}



// RGB Indicator Customization: (100% stolen from Jetpacktuxedo)
void keyboard_post_init_user(void) {
  #ifdef RGBLIGHT_ENABLE
// Set up RGB effects on _only_ the first LED (index 0):
        rgblight_set_effect_range(0, 1);
// Set LED effects to breathing mode in a "terminal-green" type color:
        rgblight_sethsv_noeeprom(50, 255, 100);
        rgblight_mode_noeeprom(RGBLIGHT_EFFECT_BREATHING + 2);
// Init the second LED to a static color:
        rgblight_setrgb_at(225, 185, 0, 1);
  #endif // RGBLIGHT_ENABLE
}

// RGB Indicator Customization: (cont.)
layer_state_t layer_state_set_user(layer_state_t state){
    #ifdef RGBLIGHT_ENABLE
        uint8_t led1r = 0;
        uint8_t led1g = 0;
        uint8_t led1b = 0;
        if (layer_state_cmp(state, 1)) {
            led1b = 255;
        }
        if (layer_state_cmp(state, 3)) {
            led1r = 200;
        }
        rgblight_setrgb_at(led1r, led1g, led1b, 1);
    #endif //RGBLIGHT_ENABLE
  return state;
}

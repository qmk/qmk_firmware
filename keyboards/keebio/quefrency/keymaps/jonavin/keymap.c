/* Copyright 2021 Jonavin Eng
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

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum custom_layers {
    _BASE,
    _FN1,
    _MO2,
    _MO3,
};

enum custom_keycodes {
  DOUBLEZERO = SAFE_RANGE,
  KC_WINLCK,   //Toggles Win key on and off
};

// Tap Dance Definitions
enum custom_tapdance {
  TD_LSFT_CAPSLOCK,
};

qk_tap_dance_action_t tap_dance_actions[] = {
  // Tap once for shift, twice for Caps Lock
  [TD_LSFT_CAPSLOCK] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
};

#define KC_LSFTCAPS TD(TD_LSFT_CAPSLOCK)

bool _isWinKeyDisabled = false;

#ifdef RGBLIGHT_ENABLE
    // Custom RGB Colours
    #define RGB_GODSPEED 0x00, 0xE4, 0xFF // colour for matching keycaps
#endif // RGBLIGHT_ENABLE

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_65(
      KC_GESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSLS, KC_INS,
      KC_PSCR, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSPC, KC_DEL,
      TT(_MO2), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_PGUP,
      KC_LSFTCAPS, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, KC_PGDN,
      KC_LCTL, KC_LGUI, KC_LALT, LT(_FN1, KC_SPC), KC_SPC, KC_SPC, KC_SPC, KC_RALT, MO(_FN1), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT),
    [_FN1] = LAYOUT_65(
      KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_F13, KC_CALC, KC_NO,
      RGB_TOG, RGB_MOD, RGB_VAI, KC_NO, KC_NO, KC_NO, KC_NO, KC_PSCR, KC_SLCK, KC_PAUS, KC_NO, KC_NO, KC_NO, KC_NO, KC_DEL,
      KC_CAPS, KC_NO, RGB_VAD, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_HOME,
      KC_TRNS, KC_NO, RGB_HUI, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, RGB_MOD, KC_END,
      KC_TRNS, KC_WINLCK, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_APP, RGB_SPD, RGB_RMOD, RGB_SPI),
    [_MO2] = LAYOUT_65(
      KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_P7, KC_P8, KC_P9, KC_P0, KC_PMNS, KC_PPLS, KC_PSLS, KC_PEQL, KC_TRNS,
      KC_TAB, KC_HOME, KC_UP, KC_END, KC_PGUP, KC_NO, KC_NO, KC_P4, KC_P5, KC_P6, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_NO, KC_TAB, KC_P1, KC_P2, KC_P3, KC_NO, KC_PAST, KC_PENT, KC_HOME,
      KC_TRNS, KC_NO, KC_DEL, KC_INS, KC_NO, KC_NO, KC_NLCK, KC_P0, DOUBLEZERO, KC_PDOT, KC_PSLS, KC_TRNS, RCTL(KC_PGUP), KC_END,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BSPC, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RCTL(KC_LEFT), RCTL(KC_PGDN), RCTL(KC_RIGHT)),
    [_MO3] = LAYOUT_65(
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_DOWN, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case DOUBLEZERO:
        if (record->event.pressed) {
            // when keycode DOUBLEZERO is pressed
            SEND_STRING("00");
        } else {
            // when keycode DOUBLEZERO is released
        }
        break;
    case KC_WINLCK:
        if (record->event.pressed) {
            _isWinKeyDisabled = !_isWinKeyDisabled; //toggle status
            if(_isWinKeyDisabled) {
                process_magic(GUI_OFF, record);
            } else {
                process_magic(GUI_ON, record);
            }
        } else  unregister_code16(keycode);
        break;
    }
    return true;
};

#ifdef ENCODER_ENABLE       // Encoder Functionality
bool encoder_update_user(uint8_t index, bool clockwise) {
    switch (index)
    {
    case 0:  // first encoder (Left Macro set)
            if (clockwise) {
            tap_code(KC_PGDN);
        }  else {
            tap_code(KC_PGUP);
        }

    default: // other encoder (Top right)
        if ( clockwise ) {
            if (keyboard_report->mods & MOD_BIT(KC_LSFT) ) { // If you are holding L shift, Page up
                unregister_mods(MOD_BIT(KC_LSFT));
                register_code(KC_PGDN);
                register_mods(MOD_BIT(KC_LSFT));
            } else if (keyboard_report->mods & MOD_BIT(KC_LCTL)) {  // if holding Left Ctrl, navigate next word
                    tap_code16(LCTL(KC_RGHT));
            } else if (keyboard_report->mods & MOD_BIT(KC_LALT)) {  // if holding Left Alt, change media next track
                tap_code(KC_MEDIA_NEXT_TRACK);
            } else  {
                tap_code(KC_VOLU);                                                   // Otherwise it just changes volume
            }
        } else {
            if (keyboard_report->mods & MOD_BIT(KC_LSFT) ) {
                unregister_mods(MOD_BIT(KC_LSFT));
                register_code(KC_PGUP);
                register_mods(MOD_BIT(KC_LSFT));
            } else if (keyboard_report->mods & MOD_BIT(KC_LCTL)) {  // if holding Left Ctrl, navigate previous word
                tap_code16(LCTL(KC_LEFT));
            } else if (keyboard_report->mods & MOD_BIT(KC_LALT)) {  // if holding Left Alt, change media previous track
                tap_code(KC_MEDIA_PREV_TRACK);
            } else {
                tap_code(KC_VOLD);
            }
        }
        break;
    }
    return true;
}
#endif

#ifdef RGBLIGHT_ENABLE

    enum custom_rgblight_layers
    {
        _rgbCAPS,
        _rgbWINLOCK,
        _rgbFN,
        _rgbNUMPAD,
    };

    // RGB map LEFT 1, 2, 3, 12, 13, 14, 15, 0  RIGHT 7, 6, 5, 4, 11, 10, 9, 8
    const rgblight_segment_t PROGMEM _rgb_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
        {14, 1, HSV_RED}       // Light 4 LEDs, starting with LED 6
    );
    const rgblight_segment_t PROGMEM _rgb_winlock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
        {13, 1, HSV_PURPLE}       // Light 4 LEDs, starting with LED 6
    );
    const rgblight_segment_t PROGMEM _rgb_fn_layer[] = RGBLIGHT_LAYER_SEGMENTS(
        {9, 2, HSV_ORANGE},
        {12, 2, HSV_ORANGE}
    );
    // Light LEDs 9 & 10 in cyan when keyboard layer 1 is active
    const rgblight_segment_t PROGMEM _rgb_numpad_layer[] = RGBLIGHT_LAYER_SEGMENTS(
        {4, 3, HSV_PURPLE},
        {9, 3, HSV_PURPLE}
    );

    const rgblight_segment_t* const PROGMEM _rgb_layers[] = RGBLIGHT_LAYERS_LIST(
        _rgb_capslock_layer,
        _rgb_winlock_layer,
        _rgb_fn_layer,
        _rgb_numpad_layer
    );

    bool led_update_user(led_t led_state) {
        rgblight_set_layer_state(_rgbCAPS, led_state.caps_lock);
        rgblight_set_layer_state(_rgbWINLOCK, _isWinKeyDisabled);
        return true;
    }

    layer_state_t layer_state_set_user(layer_state_t state) {
        rgblight_set_layer_state(_rgbFN, layer_state_cmp(state, _FN1));
        rgblight_set_layer_state(_rgbNUMPAD, layer_state_cmp(state, _MO2));
        return state;
    }
#endif // RGBLIGHT_ENABLE

void keyboard_post_init_user(void) {

    if (IS_HOST_LED_ON(USB_LED_NUM_LOCK)) { // turn on Num lock by defautl so that the numpad layer always has predictable results
        tap_code(KC_NUMLOCK);
    }
    #ifdef RGBLIGHT_ENABLE
        rgblight_mode(1); // single colour mode
        rgblight_setrgb(RGB_GODSPEED); // Default startup colour
        rgblight_layers = _rgb_layers;
    #endif
}

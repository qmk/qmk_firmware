/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>

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
#include "rgb_matrix_ledmaps.h"

#define RGB_BRIGHT_PINK 245, 37, 60
#define HSV_BRIGHT_PINK 250, 84.9, 96.1

enum gmmk_pro_layers {
    _QWERTY,
    _GAME,
    _UTIL
};

enum combo_events {
  BASE_LAYER,
  UTIL_LAYER,
  GAMES_LAYER
};

enum custom_keycodes {
  KC_00 = SAFE_RANGE,
  KC_WINLCK,    //Toggles Win key on and off
};

const uint16_t PROGMEM base_layer_combo[] = {KC_PGDOWN, KC_HOME, COMBO_END};
const uint16_t PROGMEM util_layer_combo[] = {KC_PGDOWN, KC_END, COMBO_END};
const uint16_t PROGMEM game_layer_combo[] = {KC_PGDOWN, KC_PGUP, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [BASE_LAYER] = COMBO_ACTION(base_layer_combo),
  [UTIL_LAYER] = COMBO_ACTION(util_layer_combo),
  [GAMES_LAYER] = COMBO_ACTION(game_layer_combo),
};



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//      ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	     Del           Rotary(Mute)
//      ~        1        2        3        4        5        6        7        8        9        0         -       (=)	     BackSpc           Home
//      Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]        \                 End
//      Caps     A        S        D        F        G        H        J        K        L        ;        "                 Enter             PgUp
//      Sh_L              Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       PgDn
//      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right


    // The FN key by default maps to a momentary toggle to layer 1 to provide access to the RESET key (to put the board into bootloader mode). Without
    // this mapping, you have to open the case to hit the button on the bottom of the PCB (near the USB cable attachment) while plugging in the USB
    // cable to get the board into bootloader mode - definitely not fun when you're working on your QMK builds. Remove this and put it back to KC_RGUI
    // if that's your preference.
    //
    // To put the keyboard in bootloader mode, use FN+backslash. If you accidentally put it into bootloader, you can just unplug the USB cable and
    // it'll be back to normal when you plug it back in.
    [_QWERTY] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,          KC_MPLY,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_HOME,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_END,
        LT(_UTIL, KC_CAPS), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_PGUP,
        KC_LSPO,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSPC, KC_UP,   KC_PGDOWN,
        LCTL_T(KC_LBRACKET), KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, TT(_UTIL),   RCTL_T(KC_RBRACKET), KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_UTIL] = LAYOUT(
         KC_ESC, KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_F21,   KC_F22,      KC_F23,  KC_F24,  KC_INS,            KC_MPLY,
         KC_GRV, _______, _______, _______, _______, _______, _______, KC_P7,    KC_P8,   KC_P9,    KC_P0,     KC_PMNS, KC_PPLS, _______,            KC_HOME,
         KC_TAB, _______,   KC_UP, _______, _______, _______,  KC_TAB, KC_P4,    KC_P5,   KC_P6,  KC_PDOT,     _______, EEP_RST,   RESET,             KC_END,
        _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, KC_P1,    KC_P2,   KC_P3,    KC_NO,     KC_PAST,          KC_PENT,            KC_PGUP,
        _______,          XXXXXXX, KC_DEL,  KC_INS, XXXXXXX, _______, KC_NO,    KC_P0,   KC_00,  KC_PDOT,     KC_PSLS,          _______, KC_MFFD, KC_PGDOWN,
        _______, KC_WINLCK, _______,                            KC_BSPC,                          _______, TO(_QWERTY), _______, KC_MPRV, KC_MRWD,   KC_MNXT
    ),

    [_GAME] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,           KC_MPLY,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_HOME,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_END,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_PGUP,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_PGDN,
        KC_LCTL, XXXXXXX, KC_LALT,                            KC_SPC,                             KC_RALT, XXXXXXX, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

};

#ifdef ENCODER_ENABLE       // Encoder Functionality

    bool encoder_update_user(uint8_t index, bool clockwise) {

        if ( clockwise ) {
            if (keyboard_report->mods & MOD_BIT(KC_LSFT) ) { // If you are holding L shift, Page up
                unregister_mods(MOD_BIT(KC_LSFT));
                tap_code16(RCTL(KC_PGDN));
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
                tap_code16(RCTL(KC_PGUP));
                register_mods(MOD_BIT(KC_LSFT));
            } else if (keyboard_report->mods & MOD_BIT(KC_LCTL)) {  // if holding Left Ctrl, navigate previous word
                tap_code16(LCTL(KC_LEFT));
            } else if (keyboard_report->mods & MOD_BIT(KC_LALT)) {  // if holding Left Alt, change media previous track
                tap_code(KC_MEDIA_PREV_TRACK);
            } else {
                tap_code(KC_VOLD);
            }
        }
        return true;
    }
#endif

void keyboard_post_init_user(void){
    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom(HSV_SPRINGGREEN);
    rgb_matrix_mode(RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE);
}

bool _isWinKeyDisabled = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case KC_00:
        if (record->event.pressed) {
            // when keycode KC_00 is pressed
            SEND_STRING("00");
        } else {
            // when keycode KC_00 is released
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
}

void process_combo_event(uint16_t combo_index, bool pressed) {
    switch (combo_index) {
        case GAMES_LAYER:
            if (pressed) {
                layer_on(_GAME);
                layer_off(_QWERTY);
                layer_off(_UTIL);
            }
            break;
        case UTIL_LAYER:
            if (pressed) {
                layer_on(_UTIL);
                layer_off(_QWERTY);
                layer_off(_GAME);
            }
            break;
        case BASE_LAYER:
            if (pressed) { 
                layer_on(_QWERTY);
                layer_off(_UTIL);
                layer_off(_GAME);
            }
            break;
    }
}

void suspend_power_down_user(void) {
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_set_suspend_state(true);
#endif  // RGB_MATRIX_ENABLE
}

void suspend_wakeup_init_user(void) {
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_set_suspend_state(false);
#endif  // RGB_MATRIX_ENABLE
}

#ifdef RGB_MATRIX_LEDMAPS_ENABLED

#define ______ {0, 0, 0}

const ledmap PROGMEM ledmaps[] = {
         //  LU = Left Underglow, RU = Right Underglow
         //  LU_1    ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	     Prt           Rotary(Mute)  RU_1
         //  LU_2    ~        1        2        3        4        5        6        7        8        9        0         -       (=)	     BackSpc           Del       RU_2
         //  LU_3    Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]        \                 PgUp         RU_3
         //  LU_4    Caps     A        S        D        F        G        H        J        K        L        ;        "                 Enter             PgDn         RU_4
         //  LU_5    Sh_L              Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       End          RU_5
         //  LU_6    Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right        RU_6
    [_QWERTY] = RGB_MATRIX_LAYOUT_LEDMAP(
          ______,    SPRING, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,         ______,    ______,
          ______,    ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,         ______,    ______,
          ______,    ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,         ______,    ______,
          ______,    ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,         ______,         ______,    ______,
          ______,    ______,         ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,         ______, ______, ______,    ______,
          ______,    ______, ______, ______,                         ______,                         ______, ______, ______, ______, ______, ______,    ______
    ),
    [_UTIL] = RGB_MATRIX_LAYOUT_LEDMAP(
          SPRING,    ______, SPRING, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,         ______,    ______,
          SPRING,    ______, SPRING, ______, ______, ______, ______, ______, SPRING, SPRING, SPRING, ______, ______, ______, ______,         SPRING,    SPRING,
          SPRING,    ______, ______, ______, ______, ______, ______, ______, SPRING, SPRING, SPRING, ______, ______, ______, ______,         ______,    ______,
          SPRING,    ______, ______, ______, ______, ______, ______, ______, SPRING, SPRING, SPRING, ______, ______,         ______,         ______,    ______,
          SPRING,    ______,         ______, ______, ______, ______, ______, ______, SPRING, SPRING, ______, ______,         ______, ______, ______,    ______,
          SPRING,    ______, ______, ______,                         ______,                         ______, SPRING, ______, ______, ______, ______,    ______
    ),
    [_GAME] = RGB_MATRIX_LAYOUT_LEDMAP(
          MAGENT,    ______, ______, MAGENT, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,         ______,    ______,
          MAGENT,    ______, ______, MAGENT, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,         MAGENT,    MAGENT,
          MAGENT,    ______, ______, MAGENT, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,         MAGENT,    MAGENT,
          MAGENT,    ______, MAGENT, MAGENT, MAGENT, ______, ______, ______, ______, ______, ______, ______, ______,         ______,         ______,    ______,
          MAGENT,    ______,         ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,         ______, ______, ______,    ______,
          MAGENT,    ______, ______, ______,                         ______,                         ______, ______, ______, ______, ______, ______,    ______
    ),
};

#endif // RGB_MATRIX_LEDMAPS_ENABLED

/* Copyright 2015-2017 Jack Humbert
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
#include "drashna.h"

#ifdef RGBLIGHT_ENABLE
extern rgblight_config_t rgblight_config;
#endif


#ifdef BACKLIGHT_ENABLE
enum planck_keycodes {
  BACKLIT = NEW_SAFE_RANGE,
};
#else
  #define BACKLIT OSM(MOD_LSFT)
#endif

#ifdef KEYBOARD_planck_ez
#   define PLNK_1 BK_LWER
#   define PLNK_2 SP_LWER
#   define PLNK_3 KC_NO
#   define PLNK_4 ET_RAIS
#else
#   define PLNK_1 SP_LWER
#   define PLNK_2 BK_LWER
#   define PLNK_3 DL_RAIS
#   define PLNK_4 ET_RAIS
#endif

#define LAYOUT_ortho_4x12_base( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A  \
  ) \
  LAYOUT_ortho_4x12_wrapper( \
    KC_ESC,  K01,    K02,     K03,      K04,     K05,     K06,     K07,     K08,     K09,     K0A,     KC_BSPC, \
    KC_TAB,  K11,    K12,     K13,      K14,     K15,     K16,     K17,     K18,     K19,     K1A,     KC_QUOT, \
    KC_MLSF, CTL_T(K21), K22, K23,      K24,     K25,     K26,     K27,     K28,     K29, RCTL_T(K2A), KC_ENT,  \
    BACKLIT, OS_LCTL, OS_LALT, OS_LGUI, PLNK_1,  PLNK_2,  PLNK_3,  PLNK_4,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT  \
  )
#define LAYOUT_ortho_4x12_base_wrapper(...)       LAYOUT_ortho_4x12_base(__VA_ARGS__)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_ortho_4x12_base_wrapper(
    _________________QWERTY_L1_________________, _________________QWERTY_R1_________________,
    _________________QWERTY_L2_________________, _________________QWERTY_R2_________________,
    _________________QWERTY_L3_________________, _________________QWERTY_R3_________________
  ),

  [_COLEMAK] = LAYOUT_ortho_4x12_base_wrapper(
    _________________COLEMAK_L1________________, _________________COLEMAK_R1________________,
    _________________COLEMAK_L2________________, _________________COLEMAK_R2________________,
    _________________COLEMAK_L3________________, _________________COLEMAK_R3________________
  ),

  [_DVORAK] = LAYOUT_ortho_4x12_base_wrapper(
    _________________DVORAK_L1_________________, _________________DVORAK_R1_________________,
    _________________DVORAK_L2_________________, _________________DVORAK_R2_________________,
    _________________DVORAK_L3_________________, _________________DVORAK_R3_________________
  ),

  [_WORKMAN] = LAYOUT_ortho_4x12_base_wrapper(
    _________________WORKMAN_L1________________, _________________WORKMAN_R1________________,
    _________________WORKMAN_L2________________, _________________WORKMAN_R2________________,
    _________________WORKMAN_L3________________, _________________WORKMAN_R3________________
  ),

  [_NORMAN] = LAYOUT_ortho_4x12_base_wrapper(
    _________________NORMAN_L1_________________, _________________NORMAN_L1_________________,
    _________________NORMAN_L2_________________, _________________NORMAN_R2_________________,
    _________________NORMAN_L3_________________, _________________NORMAN_R3_________________
  ),

  [_MALTRON] = LAYOUT_ortho_4x12_base_wrapper(
    _________________MALTRON_L1________________, _________________MALTRON_R1________________,
    _________________MALTRON_L2________________, _________________MALTRON_R2________________,
    _________________MALTRON_L3________________, _________________MALTRON_R3________________
  ),

  [_EUCALYN] = LAYOUT_ortho_4x12_base_wrapper(
    _________________EUCALYN_L1________________, _________________EUCALYN_R1________________,
    _________________EUCALYN_L2________________, _________________EUCALYN_R2________________,
    _________________EUCALYN_L3________________, _________________EUCALYN_R3________________
  ),

  [_CARPLAX] = LAYOUT_ortho_4x12_base_wrapper(
    _____________CARPLAX_QFMLWY_L1_____________, _____________CARPLAX_QFMLWY_R1_____________,
    _____________CARPLAX_QFMLWY_L2_____________, _____________CARPLAX_QFMLWY_R2_____________,
    _____________CARPLAX_QFMLWY_L3_____________, _____________CARPLAX_QFMLWY_R3_____________
  ),

  [_MODS] = LAYOUT_ortho_4x12_wrapper(
    _______, ___________________BLANK___________________, ___________________BLANK___________________, _______,
    _______, ___________________BLANK___________________, ___________________BLANK___________________, _______,
    KC_LSFT, ___________________BLANK___________________, ___________________BLANK___________________, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

  [_LOWER] = LAYOUT_ortho_4x12_wrapper(
    KC_TILD, _________________LOWER_L1__________________, _________________LOWER_R1__________________, KC_BSPC,
    KC_DEL,  _________________LOWER_L2__________________, _________________LOWER_R2__________________, KC_PIPE,
    _______, _________________LOWER_L3__________________, _________________LOWER_R3__________________, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
  ),

  [_RAISE] = LAYOUT_ortho_4x12_wrapper(
    KC_GRV,  _________________RAISE_L1__________________, _________________RAISE_R1__________________, KC_BSPC,
    KC_DEL,  _________________RAISE_L2__________________, _________________RAISE_R2__________________, KC_BSLS,
    _______, _________________RAISE_L3__________________, _________________RAISE_R3__________________, _______,
    _______, _______, _______, _______, _______, _______, _______, _________________RAISE_R3__________________
  ),

  [_ADJUST] = LAYOUT_ortho_4x12_wrapper(
    KC_MAKE, _________________ADJUST_L1_________________, _________________ADJUST_R1_________________, KC_RST,
    VRSN,    _________________ADJUST_L2_________________, _________________ADJUST_R2_________________, EEP_RST,
    _______, _________________ADJUST_L3_________________, _________________ADJUST_R3_________________, TG_MODS,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_NUKE
  )

};


bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
 #ifdef BACKLIGHT_ENABLE
        case BACKLIT:
            if (record->event.pressed) {
                register_code(KC_RSFT);
                #ifdef BACKLIGHT_ENABLE
                backlight_step();
                #endif
            } else {
                unregister_code(KC_RSFT);
            }
            return false;
            break;
#endif
    }
    return true;
}

bool music_mask_user(uint16_t keycode) {
    switch (keycode) {
        case RAISE:
        case LOWER:
        case BK_LWER:
        case SP_LWER:
        case DL_RAIS:
        case ET_RAIS:
            return false;
        default:
            return true;
    }
}

#ifdef RGB_MATRIX_ENABLE

void suspend_power_down_keymap(void) {
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_keymap(void) {
    rgb_matrix_set_suspend_state(false);
}

void rgb_matrix_layer_helper (uint8_t red, uint8_t green, uint8_t blue) {
    for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
        if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_MODIFIER)) {
            rgb_matrix_set_color( i, red, green, blue );
        }
    }
}

void rgb_matrix_indicators_user(void) {
    uint8_t this_mod = get_mods();
    uint8_t this_led = host_keyboard_leds();
    uint8_t this_osm = get_oneshot_mods();
    bool is_ez;
    #ifdef KEYBOARD_planck_ez
    is_ez = true;
    #endif

    if ( userspace_config.rgb_layer_change &&
#ifdef RGB_DISABLE_WHEN_USB_SUSPENDED
        !g_suspend_state &&
#endif
#if defined(RGBLIGHT_ENABLE)
            (!rgblight_config.enable && rgb_matrix_config.enable)
#else
            rgb_matrix_config.enable
#endif
        ) {
        switch (biton32(layer_state)) {
            case _RAISE:
                rgb_matrix_layer_helper(0xFF, 0xFF, 0x00); break;
            case _LOWER:
                rgb_matrix_layer_helper(0x00, 0xFF, 0x00); break;
            case _ADJUST:
                rgb_matrix_layer_helper(0xFF, 0x00, 0x00); break;
            default:
                switch (biton32(default_layer_state)) {
                case _QWERTY:
                    rgb_matrix_layer_helper(0x00, 0xFF, 0xFF); break;
                case _COLEMAK:
                    rgb_matrix_layer_helper(0xFF, 0x00, 0xFF); break;
                case _DVORAK:
                    rgb_matrix_layer_helper(0x00, 0xFF, 0x00); break;
                case _WORKMAN:
                    rgb_matrix_layer_helper(0xD9, 0xA5, 0x21); break;
                case _NORMAN:
                    rgb_matrix_layer_helper(0xFF, 0x7C, 0x4D); break;
                case _MALTRON:
                    rgb_matrix_layer_helper(0xFF, 0xFF, 0x00); break;
                case _EUCALYN:
                    rgb_matrix_layer_helper(0xFF, 0x80, 0xBF); break;
                case _CARPLAX:
                    rgb_matrix_layer_helper(0x00, 0x00, 0xFF); break;
                }
        }
    }

    switch (biton32(default_layer_state)) {
        case _QWERTY:
            rgb_matrix_set_color(is_ez ? 41 : 42, 0x00, 0xFF, 0xFF); break;
        case _COLEMAK:
            rgb_matrix_set_color(is_ez ? 41 : 42, 0xFF, 0x00, 0xFF); break;
        case _DVORAK:
            rgb_matrix_set_color(is_ez ? 41 : 42, 0x00, 0xFF, 0x00); break;
        case _WORKMAN:
            rgb_matrix_set_color(is_ez ? 41 : 42, 0xD9, 0xA5, 0x21); break;
    }
    if ( (this_mod | this_osm) & MOD_MASK_SHIFT || this_led & (1<<USB_LED_CAPS_LOCK)) {
        rgb_matrix_set_color(24, 0x00, 0xFF, 0x00);
        rgb_matrix_set_color(36, 0x00, 0xFF, 0x00);
    }
    if ( (this_mod | this_osm) & MOD_MASK_CTRL) {
        rgb_matrix_set_color(25, 0xFF, 0x00, 0x00);
        rgb_matrix_set_color(34, 0xFF, 0x00, 0x00);
        rgb_matrix_set_color(37, 0xFF, 0x00, 0x00);

    }
    if ( (this_mod | this_osm) & MOD_MASK_GUI) {
        rgb_matrix_set_color(39, 0xFF, 0xD9, 0x00);
    }
    if ( (this_mod | this_osm) & MOD_MASK_ALT) {
        rgb_matrix_set_color(38, 0x00, 0x00, 0xFF);
    }
}

void matrix_init_keymap(void) {
  // rgblight_mode(RGB_MATRIX_MULTISPLASH);
}
#else //RGB_MATRIX_INIT

void matrix_init_keymap(void) {
#if !defined(CONVERT_TO_PROTON_C) && !defined(KEYBOARD_planck)
    setPinOutput(D5);
    writePinHigh(D5);

    setPinOutput(B0);
    writePinHigh(B0);
#endif
}
#endif //RGB_MATRIX_INIT

#ifdef ENCODER_ENABLE
void encoder_update(bool clockwise) {
    switch (biton32(layer_state)) {
        case _RAISE:
            clockwise ? tap_code(KC_VOLD) : tap_code(KC_VOLU);
            break;
        case _LOWER:
#ifdef RGB_MATRIX_ENABLE
            clockwise ? rgb_matrix_step() : rgblight_step_reverse();
#else
            clockwise ? tap_code(KC_PGDN) : tap_code(KC_PGUP);
#endif
            break;
        case _ADJUST:
#ifdef AUDIO_CLICKY
            clockwise ? clicky_freq_up() : clicky_freq_down();
#endif
            break;
        default:
            clockwise ? tap_code(KC_DOWN) : tap_code(KC_UP);
    }
#ifdef AUDIO_CLICKY
    clicky_play();
#endif
}
#endif // ENCODER_ENABLE

#ifdef KEYBOARD_planck_rev6
void dip_update(uint8_t index, bool active) {
    switch (index) {
        case 0:
            if(active) { audio_on(); } else { audio_off(); }
            break;
        case 1:
            if(active) { clicky_on(); } else { clicky_off(); }
            break;
        case 2:
            keymap_config.swap_lalt_lgui = keymap_config.swap_ralt_rgui = active;
            break;
        case 3:
            userspace_config.nuke_switch = active;
            break;
    }
}
#endif // KEYBOARD_planck_rev6

#ifdef KEYBOARD_planck_ez
uint32_t layer_state_set_keymap(uint32_t state) {

    palClearPad(GPIOB, 8);
    palClearPad(GPIOB, 9);
    switch (biton32(state)) {
        case _LOWER:
            palSetPad(GPIOB, 9);
            break;
        case _RAISE:
            palSetPad(GPIOB, 8);
            break;
        case _ADJUST:
            palSetPad(GPIOB, 9);
            palSetPad(GPIOB, 8);
            break;
        default:
            break;
    }
    return state;
}
#endif

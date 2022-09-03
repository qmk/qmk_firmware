/* Copyright 2021 Sets3n/Сэцэн
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
    _BASE = 0,
    _FUNC,
    _NUM
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// 0:Base Layer
    [_BASE] = LAYOUT(
        KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,  KC_5,  KC_6,   KC_7,  KC_8,    KC_9,    KC_0,    KC_GRV,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,  KC_T,  KC_Y,   KC_U,  KC_I,    KC_O,    KC_P,    KC_LBRC,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,  KC_G,  KC_H,   KC_J,  KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,  KC_B,  KC_N,   KC_M,  KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
        KC_LCTL, KC_LGUI, KC_LALT, KC_LGUI, MO(2), TO(1), KC_SPC, MO(1), KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT),
 
// 1:fn Layer    
    [_FUNC] = LAYOUT(
		KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_0,    KC_BSPC, 
		KC_TAB,  KC_VOLD, KC_VOLU, KC_MUTE, KC_EJCT, KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, 
		KC_CAPS, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_L,    KC_SCLN, KC_QUOT, 
		KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT, 
		KC_LCTL, KC_LGUI, KC_LALT, KC_NO,   KC_TRNS, TO(2),   KC_SPC,  KC_TRNS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT),
// 2:Num Layer    
    [_NUM] = LAYOUT(
		KC_TRNS, KC_F1,   KC_F2,   KC_F3,    KC_F4,   KC_F5,   KC_F6,   KC_BSPC,  KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS, 
		KC_TAB,  KC_Q,    KC_UP,   KC_E,     KC_R,    KC_T,    KC_Y,    KC_LBRC,  KC_P7,   KC_P8,   KC_P9,   KC_PPLS, 
		KC_CAPS, KC_LEFT, KC_DOWN, KC_RIGHT, RGB_HUD, RGB_SAI, RGB_SAD, KC_QUOT,  KC_P4,   KC_P5,   KC_P6,   KC_PEQL, 
		KC_LSFT, KC_Z,    KC_X,    KC_C,     KC_V,    KC_B,    KC_N,    KC_ENT,   KC_P1,   KC_P2,   KC_P3,   KC_PCMM, 
		KC_LCTL, KC_LGUI, KC_LALT, KC_NO,    KC_TRNS, TO(0),   KC_SPC,  KC_TRNS,  KC_P0,   KC_P0,   KC_PDOT, KC_PENT) 
};


// Define RGB Location
const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
        {0, 1, HSV_MAGENTA}
);

const rgblight_segment_t PROGMEM my_numlocak_layer[] = RGBLIGHT_LAYER_SEGMENTS(
        {1, 1, HSV_GREEN}
);

const rgblight_segment_t PROGMEM my_scroll_layer[] = RGBLIGHT_LAYER_SEGMENTS(
        {2, 1, HSV_CYAN}
);

const rgblight_segment_t PROGMEM my_num_layer[] = RGBLIGHT_LAYER_SEGMENTS(
        {11, 1, HSV_AZURE},
        {12, 3, HSV_TEAL},
        {17, 1, HSV_PINK},
        {23, 3, HSV_GOLDENROD},
        {26, 1, HSV_TEAL},
        {28, 3, HSV_PINK},
        {35, 3, HSV_GOLDENROD},
        {38, 1, HSV_TEAL},
        {47, 3, HSV_GOLDENROD},
        {50, 1, HSV_TEAL},
        {58, 3, HSV_GOLDENROD},
        {61, 1, HSV_TEAL}
);
// Define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
        my_capslock_layer,
        my_numlocak_layer,
        my_scroll_layer,
        my_num_layer
);

void keyboard_post_init_user(void){
        //Enable the LED layers
        rgblight_layers = my_rgb_layers;
}

// Enabling and disabling lighting layers
layer_state_t layer_state_set_user(layer_state_t state) {
    // Both layers will light up if both kb layers are active
    rgblight_set_layer_state(0, layer_state_cmp(state, 0));
    rgblight_set_layer_state(1, layer_state_cmp(state, 1));
    rgblight_set_layer_state(2, layer_state_cmp(state, 2));
    rgblight_set_layer_state(3, layer_state_cmp(state, _NUM));


    return state;
}
bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(0, led_state.caps_lock);
    rgblight_set_layer_state(1, led_state.num_lock);
    rgblight_set_layer_state(2, led_state.scroll_lock);

    return true;
}


#ifdef WPM_ENABLE
char wpm_str[10];
uint16_t wpm_graph_timer = 0;
#endif

static char current_alpha_oled = '\0';

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode){
        case KC_A:
            if (record->event.pressed) {
                current_alpha_oled = 'A';
            }
            break;
        case KC_B:
            if (record->event.pressed) {
                current_alpha_oled = 'B';
            }
            break;
        case KC_C:
            if (record->event.pressed) {
                current_alpha_oled = 'C';
            }
            break;
        case KC_D:
            if (record->event.pressed) {
                current_alpha_oled = 'D';
            }
            break;
        case KC_E:
            if (record->event.pressed) {
                current_alpha_oled = 'E';
            }
            break;
        case KC_F:
            if (record->event.pressed) {
                current_alpha_oled = 'F';
            }
            break;
        case KC_G:
            if (record->event.pressed) {
                current_alpha_oled = 'G';
            }
            break;
        case KC_H:
            if (record->event.pressed) {
                current_alpha_oled = 'H';
            }
            break;
        case KC_I:
            if (record->event.pressed) {
                current_alpha_oled = 'I';
            }
            break;
        case KC_J:
            if (record->event.pressed) {
                current_alpha_oled = 'J';
            }
            break;
        case KC_K:
            if (record->event.pressed) {
                current_alpha_oled = 'K';
            }
            break;
        case KC_L:
            if (record->event.pressed) {
                current_alpha_oled = 'L';
            }
            break;
        case KC_M:
            if (record->event.pressed) {
                current_alpha_oled = 'M';
            }
            break;
        case KC_N:
            if (record->event.pressed) {
                current_alpha_oled = 'N';
            }
            break;
        case KC_O:
            if (record->event.pressed) {
                current_alpha_oled = 'O';
            }
            break;
        case KC_P:
            if (record->event.pressed) {
                current_alpha_oled = 'P';
            }
            break;
        case KC_Q:
            if (record->event.pressed) {
                current_alpha_oled = 'Q';
            }
            break;
        case KC_R:
            if (record->event.pressed) {
                current_alpha_oled = 'R';
            }
            break;
        case KC_S:
            if (record->event.pressed) {
                current_alpha_oled = 'S';
            }
            break;
        case KC_T:
            if (record->event.pressed) {
                current_alpha_oled = 'T';
            }
            break;
        case KC_U:
            if (record->event.pressed) {
                current_alpha_oled = 'U';
            }
            break;
        case KC_V:
            if (record->event.pressed) {
                current_alpha_oled = 'V';
            }
            break;
        case KC_W:
            if (record->event.pressed) {
                current_alpha_oled = 'W';
            }
            break;
        case KC_X:
            if (record->event.pressed) {
                current_alpha_oled = 'X';
            }
            break;
        case KC_Y:
            if (record->event.pressed) {
                current_alpha_oled = 'Y';
            }
            break;
        case KC_Z:
            if (record->event.pressed) {
                current_alpha_oled = 'Z';
            }
            break;
#ifdef EMAIL_ENABLE
        case KC_2:
            if (record->event.pressed) {
                if (get_mods() & MOD_BIT(KC_LSHIFT)) {
                    register_code16(LSFT(KC_2));
                } else if (get_mods() & MOD_BIT(KC_RSHIFT)) {
                    del_mods(MOD_BIT(KC_RSHIFT));
                    SEND_STRING(EMAIL_ADDRESS);
                } else {
                    register_code(KC_2);
                }
                if (get_mods() & MOD_BIT(KC_LSHIFT)) {
                    unregister_code16(LSFT(KC_2));
                } else if (get_mods() & MOD_BIT(KC_RSHIFT)) {
                } else {
                    unregister_code(KC_2);
                }
                return false;
            }
            break;
#endif
        default:
            break;
    }
    return true;
}

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
        return OLED_ROTATION_0;
}

bool oled_task_user(void) {
    static const char PROGMEM image[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4};
    oled_write_P(image, false);
    oled_write_P(PSTR("    Zx50 by Sets3n\n"), false);
    oled_write_P(PSTR("    Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case _BASE:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case _FUNC:
            oled_write_P(PSTR("Function\n"), false);
            break;
        case _NUM:
            oled_write_P(PSTR("Number\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined\n"), false);
    }

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.caps_lock ? PSTR("}~CAP") : PSTR("{|   "), false);
    oled_write_P(led_state.num_lock ? PSTR("  NUM") : PSTR("     "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("  SCR  ") : PSTR("       "), false);
    // Write Keys Status
    oled_write_P(PSTR("["), false);
    if (current_alpha_oled == '\0') {
        oled_write_char('*', false);
    } else {
        oled_write_char(current_alpha_oled, false);
    }
    oled_write_P(PSTR("]\n"), false);
    // Write Word Per Minute (WPM) Calculcation
    oled_write_P(PSTR("WPM: "), false);
    oled_write(get_u8_str(get_current_wpm(), '0'), false);
    oled_write(wpm_str, false);
    uint8_t mods = get_mods() | get_weak_mods();
    oled_write_P((mods & MOD_MASK_ALT) ? PSTR("ALT ") : PSTR("    "), false);
    oled_write_P((mods & MOD_MASK_CTRL) ? PSTR("CTL ") : PSTR("    "), false);
    oled_write_P((mods & MOD_MASK_SHIFT) ? PSTR("SFT ") : PSTR("    "), false);

    return false;
}
#endif

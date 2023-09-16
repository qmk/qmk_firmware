/* Copyright 2020 elijahblake81
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

#define MILLISECONDS_IN_SECOND 1000

// These are just to make it neater to use builtin HSV values in the keymap
#define RED {HSV_RED}
#define CORAL {HSV_CORAL}
#define ORANGE {HSV_ORANGE}
#define GOLDEN {HSV_GOLDENROD}
#define GOLD {HSV_GOLD}
#define YELLOW {HSV_YELLOW}
#define CHART {HSV_CHARTREUSE}
#define GREEN {HSV_GREEN}
#define SPRING {HSV_SPRINGGREEN}
#define TURQ {HSV_TURQUOISE}
#define TEAL {HSV_TEAL}
#define CYAN {HSV_CYAN}
#define AZURE {HSV_AZURE}
#define BLUE {HSV_BLUE}
#define PURPLE {HSV_PURPLE}
#define MAGENT {HSV_MAGENTA}
#define PINK {HSV_PINK}



//========================================================== CONFIGURABLE DEFAULTS ==========================================================
extern bool g_suspend_state;
extern rgb_config_t rgb_matrix_config;
bool disable_layer_color;

enum alt_keycodes {
    U_T_AUTO = SAFE_RANGE, // USB Extra Port Toggle Auto Detect / Always Active
    U_T_AGCR,              // USB Toggle Automatic GCR control
    DBG_TOG,               // DEBUG Toggle On / Off
    DBG_MTRX,              // DEBUG Toggle Matrix Prints
    DBG_KBD,               // DEBUG Toggle Keyboard Prints
    DBG_MOU,               // DEBUG Toggle Mouse Prints
    MD_BOOT,               // Restart into bootloader after hold timeout
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /*
    [DEFAULT] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGUP,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,     KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_PGDN,
        KC_LCTL, KC_LGUI, KC_LALT,                             KC_SPC,                             KC_RALT, MO(1),   KC_LEFT, KC_DOWN, KC_RGHT
    ),
    */
   [0] = LAYOUT_65_ansi_blocker(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,   KC_EQL,    KC_BSPC,   KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,  KC_BSLS,   KC_HOME,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,           KC_ENT,    KC_PGUP,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,             KC_UP,   KC_PGDN,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(1),     KC_LEFT,  KC_DOWN, KC_RGHT
        ),
    [1] = LAYOUT_65_ansi_blocker(
        KC_GRV,  KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_F13,   KC_CALC,
        RGB_M_P, RGB_SPD,  RGB_HUI, RGB_SPI, RGB_SAI, RGB_VAI, _______, U_T_AUTO, _______, _______, KC_PSCR, KC_SCRL, KC_PAUS, _______, KC_MYCM,
        RGB_TOG, RGB_RMOD, RGB_HUD, RGB_MOD, RGB_SAD, RGB_VAD, _______, _______, _______, _______, _______, _______,          KC_MUTE,  KC_VOLU,
        _______, _______,  _______, _______, _______, MD_BOOT, NK_TOGG, DBG_TOG, _______, _______, _______, _______,          KC_VOLU,  KC_VOLD,
        _______, _______,  _______,                            KC_MPLY,                            _______, _______, KC_HOME, KC_VOLD,  KC_END
    ),
    /*
    [X] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______, _______, _______, _______, TG_NKRO, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______
    ),
    [RGB] = LAYOUT(
        ESC: 0,    1: 1,      2: 2,      3: 3,    4: 4,    5: 5,    6: 6,    7: 7,    8: 8,      9: 9,      0: 10,      MINS: 11,   EQL: 12,   BSPC: 13,  DEL: 14,
        TAB: 15,   Q: 16,     W: 17,     E: 18,   R: 19,   T: 20,   Y: 21,   U: 22,   I: 23,     O: 24,     P: 25,      LBRC: 26,   RBRC: 27,  BSLS: 28,  HOME: 29,
        CAPS: 30,  A: 31,     S: 32,     D: 33,   F: 34,   G: 35,   H: 36,   J: 37,   K: 38,     L: 39,     SCLN: 40,   QUOT: 41,              ENT: 42,   PGUP: 43,
        LSFT: 44,  Z: 45,     X: 46,     C: 47,   V: 48,   B: 49,   N: 50,   M: 51,   COMM: 52,  DOT: 53,   SLSH: 54,   RSFT: 55,              UP: 56,    PGDN: 57,
        LCTL: 58,  LGUI: 59,  LALT: 60,                    SPC: 61,                              RALT: 62,  FN: 63,                  LEFT: 64, DOWN: 65,  RGHT: 66
        //UnderGlow
        :67, :68, :69, :70, :71, :72, :73, :74, :75, :76, :77, :78, :79, :80, :81,
        :82, :83, :84, :85,
        :86, :87, :88, :89,
        :90, :91, :92, :93, :94, :95, :96, :97, :98, :99, :100, :101, :102, :103, :104, :105,
    ),
    [MATRIX] = LAYOUT(
        0,      1,      2,      3,      4,      5,      6,      7,      8,      9,      10,     11,         12,     13,     14,
        15,     16,     17,     18,     19,     20,     21,     22,     23,     24,     25,     26,         27,     28,     29,
        30,     31,     32,     33,     34,     35,     36,     37,     38,     39,     40,     41,         42,             43,
        44,     45,     46,     47,     48,     49,     50,     51,     52,     53,     54,     55,                 56,     57,
        58,     59,     60,                             61,                         62,     63,         64,     65,     66,
        //UnderGlow
        90,     91,     92,     93,     94,     95,     96,     97,     98,     99,     100,    101,    102,    103,        104,        105,
        88,                                                                                                                             89,
        86,                                                                                                                             87,
        84,                                                                                                                             85,
        67,     68,     69,     70,     71,     72,     73,     74,     75,     76,     77,     78,     79,     80,     81,     82,     83
    ),
    */
};

#ifdef _______
#undef _______
#define _______ {0, 0, 0}

const uint8_t PROGMEM ledmap[][RGB_MATRIX_LED_COUNT][3] = {
    [0] = {
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, CHART,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, CHART,   CHART,   CHART,   _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          CHART,   _______,
        _______, _______, _______,                            _______,                            _______, _______, CHART,   CHART,   CHART,
        //UnderGlow
        CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,
        CHART,                                                                                                                        CHART,
        CHART,                                                                                                                        CHART,
        CHART,                                                                                                                        CHART,
        CHART,                                                                                                                        CHART,
        CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART
        },
    [1] = {
        CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,    CHART,   CHART,   CHART,   CHART,     CHART,    BLUE,
        GOLD,    PINK,    AZURE,   PINK,    TURQ,    TEAL,    _______, RED,     _______,  _______, GREEN,   BLUE,    GOLD,      _______,  BLUE,
        TEAL,    MAGENT,  AZURE,   MAGENT,  TURQ,    TEAL,    _______, _______, _______,  _______, _______, _______,                GOLD, BLUE,
        _______, _______, _______, _______, _______, RED,     RED,     RED,     _______,  _______, _______, _______,                GOLD, BLUE,
        _______, _______, _______,                            GOLD,                                _______, _______,       PURPLE,  GOLD, PURPLE,
        //UnderGlow
        CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,
        CHART,                                                                                                                        CHART,
        CHART,                                                                                                                        CHART,
        CHART,                                                                                                                        CHART,
        CHART,                                                                                                                        CHART,
        CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART,   CHART
    },
};

#undef _______
#define _______ KC_TRNS
#endif

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
    // Enable or disable debugging
    debug_enable=false;
    debug_matrix=false;
    debug_keyboard=false;
    //rgb_enabled_flag = true;          // Initially, keyboard RGB is enabled. Change to false config.h initializes RGB disabled.
};

void keyboard_post_init_user(void) {
    rgb_matrix_enable();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint32_t key_timer;

    switch (keycode) {
        case U_T_AUTO:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_extra_manual, "USB extra port manual mode");
            }
            return false;
        case U_T_AGCR:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_gcr_auto, "USB GCR auto mode");
            }
            return false;
        case MD_BOOT:
            if (record->event.pressed) {
                key_timer = timer_read32();
            } else {
                if (timer_elapsed32(key_timer) >= 500) {
                    reset_keyboard();
                }
            }
            return false;
        case RGB_TOG:
            if (record->event.pressed) {
                switch (rgb_matrix_get_flags()) {
                    case LED_FLAG_ALL: {
                        rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER);
                        rgb_matrix_set_color_all(0, 0, 0);
                    }
                    break;
                    case LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER: {
                        rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                        rgb_matrix_set_color_all(0, 0, 0);
                    }
                    break;
                    case LED_FLAG_UNDERGLOW: {
                        rgb_matrix_set_flags(LED_FLAG_NONE);
                        rgb_matrix_disable_noeeprom();
                    }
                    break;
                    default: {
                        rgb_matrix_set_flags(LED_FLAG_ALL);
                        rgb_matrix_enable_noeeprom();
                    }
                    break;
                }
                return false;
        }
    }
    return true;
}
void set_layer_color(int layer) {
    for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        HSV hsv = {
            .h = pgm_read_byte(&ledmap[layer][i][0]),
            .s = pgm_read_byte(&ledmap[layer][i][1]),
            .v = pgm_read_byte(&ledmap[layer][i][2]),
        };
        if (hsv.h || hsv.s || hsv.v) {
            RGB rgb = hsv_to_rgb(hsv);
            float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
            rgb_matrix_set_color(i, f * rgb.r, f * rgb.g, f * rgb.b);
        } else if (layer == 1) {
            // Only deactivate non-defined key LEDs at layers other than FN. Because at FN we have RGB adjustments and need to see them live.
            // If the values are all false then it's a transparent key and deactivate LED at this layer
            rgb_matrix_set_color(i, 0, 0, 0);
        }
    }
}
bool rgb_matrix_indicators_user(void) {
    if (g_suspend_state || disable_layer_color ||
        rgb_matrix_get_flags() == LED_FLAG_NONE ||
        rgb_matrix_get_flags() == LED_FLAG_UNDERGLOW) {
            return;
        }
    set_layer_color(get_highest_layer(layer_state));
    return false;
}

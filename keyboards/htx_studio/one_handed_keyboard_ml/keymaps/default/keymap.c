/* Copyright 2025 htx-studio (@https://github.com/htx-studio)
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

#define TRACKBALL_DPI_MIN 1000
#define TRACKBALL_DPI_MAX 8000
#define TRACKBALL_DPI_DEFAULT 3000
#define TRACKBALL_DPI_STEP 1000

enum my_keycodes {
    DPI_UP = SAFE_RANGE,
    DPI_DOWN
};

typedef union {
    uint16_t TrackballDPI;
} user_config_t;
user_config_t user_config;


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//       ┏━━━━━━━┳━━━━━━━┳━━━━━━━┳━━━━━━━┳━━━━━━━┳━━━━━━━┳━━━━━━━┳━━━━━━━┳━━━━━━━┳━━━━━━━┳━━━━━━━┳━━━━━━━┳━━━━━━━┳━━━━━━━┓
//       ┃  ESC  ┃   1   ┃   2   ┃   3   ┃   4   ┃   5   ┃   6   ┃   7   ┃   8   ┃   9   ┃   0   ┃  -_   ┃  +=   ┃   `~  ┃
//       ┣━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━┫
//       ┃  TAB  ┃   Q   ┃   W   ┃   E   ┃   R   ┃   T   ┃   Y   ┃   U   ┃   I   ┃   O   ┃   P   ┃  [{   ┃  ]}   ┃  :;   ┃
//       ┗━━━┳━━━┻━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━┻━━━┳━━━┛
//           ┃  CAPSLOCK ┃   A   ┃   S   ┃   D   ┃   F   ┃   G   ┃   H   ┃   J   ┃   K   ┃   L   ┃   '"  ┃   ENTER   ┃ 
//           ┗━━━┳━━━━━━━┻━━━┳━━━┻━━━┳━━━┻━━━┳━━━┻━━━┳━━━┻━━━┳━━━┻━━━┳━━━┻━━━┳━━━┻━━━┳━━━┻━━━━━━━┻━┳━━━━━┻━━━━━━━┳━━━┛
//               ┃   SHIFT   ┃   Z   ┃   X   ┃   C   ┃   V   ┃   B   ┃   N   ┃   M   ┃   MOUSE1    ┃   MOUSE2    ┃
//               ┗━━━┳━━━━━━━┻┳━━━━━━┻━┳━━━━━┻━━┳━━━━┻━━━┳━━━┻━━━━┳━━┻━━━━━┳━┻━━━━━━┳┻━━━━━━━━━━━━━┻┳━━━━━━━━┳━━━┛
//                   ┃  CTRL  ┃  LGUI  ┃  LALT  ┃   ,<   ┃   .>   ┃   /?   ┃   Fn   ┃      SPC      ┃  BACK  ┃
//                   ┗━━━━━━━━┻━━━━━━━━┻━━━━━━━━┻━━━━━━━━┻━━━━━━━━┻━━━━━━━━┻━━━━━━━━┻━━━━━━━━━━━━━━━┻━━━━━━━━┛
//                                     ┏━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┓
//                                     ┃  MOUSE3 ┃    →    ┃    ↓    ┃    ←    ┃    ↑    ┃
//                                     ┗━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┛

    [0] = LAYOUT(
        KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINUS,           KC_EQUAL,            KC_GRAVE,
        KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LEFT_BRACKET,    KC_RIGHT_BRACKET,    KC_SEMICOLON,
               KC_CAPS_LOCK,       KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOTE,       KC_ENTER,
                  KC_LEFT_SHIFT,      KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    QK_MOUSE_BUTTON_1,      QK_MOUSE_BUTTON_2,
                    KC_LEFT_CTRL,    KC_LEFT_GUI,    KC_LEFT_ALT,    KC_COMMA,    KC_DOT,    KC_SLASH,    MO(1),    KC_SPC,    KC_BACKSPACE,
        
        QK_MOUSE_BUTTON_3,    KC_RIGHT,    KC_DOWN,    KC_LEFT,    KC_UP
    ),

//       ┏━━━━━━━┳━━━━━━━┳━━━━━━━┳━━━━━━━┳━━━━━━━┳━━━━━━━┳━━━━━━━┳━━━━━━━┳━━━━━━━┳━━━━━━━┳━━━━━━━┳━━━━━━━┳━━━━━━━┳━━━━━━━┓
//       ┃       ┃   F1  ┃   F2  ┃   F3  ┃   F4  ┃   F5  ┃   F6  ┃   F7  ┃   F8  ┃   F9  ┃  F10  ┃  F11  ┃  F12  ┃       ┃
//       ┣━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━┫
//       ┃       ┃       ┃       ┃       ┃       ┃       ┃       ┃       ┃RM_HUED┃RM_HUEU┃       ┃ DPI_DO┃ DPI_UP┃       ┃
//       ┗━━━┳━━━┻━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━┻━━━┳━━━┛
//           ┃           ┃       ┃       ┃       ┃       ┃       ┃       ┃RM_SATD┃RM_SATU┃       ┃       ┃           ┃ 
//           ┗━━━┳━━━━━━━┻━━━┳━━━┻━━━┳━━━┻━━━┳━━━┻━━━┳━━━┻━━━┳━━━┻━━━┳━━━┻━━━┳━━━┻━━━┳━━━┻━━━━━━━┻━┳━━━━━┻━━━━━━━┳━━━┛
//               ┃           ┃       ┃       ┃       ┃       ┃       ┃RM_SPDD┃RM_SPDU┃   MOUSE1    ┃   MOUSE2    ┃
//               ┗━━━┳━━━━━━━┻┳━━━━━━┻━┳━━━━━┻━━┳━━━━┻━━━┳━━━┻━━━━┳━━┻━━━━━┳━┻━━━━━━┳┻━━━━━━━━━━━━━┻┳━━━━━━━━┳━━━┛
//                   ┃        ┃        ┃        ┃        ┃        ┃   \|   ┃        ┃    RM_TOGG    ┃   DEL  ┃
//                   ┗━━━━━━━━┻━━━━━━━━┻━━━━━━━━┻━━━━━━━━┻━━━━━━━━┻━━━━━━━━┻━━━━━━━━┻━━━━━━━━━━━━━━━┻━━━━━━━━┛
//                                     ┏━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┓
//                                     ┃  MOUSE3 ┃ RM_PREV ┃ RM_VALD ┃ RM_NEXT ┃ RM_VALU ┃
//                                     ┗━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┛


    [1] = LAYOUT(
        _______,    KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_F11,     KC_F12,     _______,
        _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    RM_HUED,    RM_HUEU,    _______,    DPI_DOWN,    DPI_UP,    _______,
                    _______,    _______,    _______,    _______,    _______,    _______,    _______,    RM_SATD,    RM_SATU,    _______,    _______,    _______,
                      _______,    _______,    _______,    _______,    _______,    _______,    RM_SPDD,    RM_SPDU,    QK_MOUSE_BUTTON_1,    QK_MOUSE_BUTTON_2,
                             _______,    _______,    _______,    _______,    _______,    KC_BSLS,    _______,    RM_TOGG,    KC_DEL,
        
                             QK_MOUSE_BUTTON_3, RM_PREV, RM_VALD, RM_NEXT, RM_VALU
    ),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = {ENCODER_CCW_CW(MS_WHLU, MS_WHLD)},
    [1] = {ENCODER_CCW_CW(MS_WHLD, MS_WHLU)}
};
#endif

void pointing_device_init_kb(void) {
    wait_ms(10);
    user_config.TrackballDPI = eeconfig_read_user();
    wait_ms(10);
    adns9800_init();
    wait_ms(10);
    pointing_device_set_cpi(user_config.TrackballDPI);
}

// ADNS9800. The CPI range is 800-8200, in increments of 200.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case DPI_UP: {
        if (record->event.pressed) {
            user_config.TrackballDPI += TRACKBALL_DPI_STEP;
            if(user_config.TrackballDPI > TRACKBALL_DPI_MAX) {
                user_config.TrackballDPI = TRACKBALL_DPI_MAX;
            }
            eeconfig_update_user(user_config.TrackballDPI);
            pointing_device_set_cpi(user_config.TrackballDPI);
            return false;
        }
    }
    case DPI_DOWN: {
        if (record->event.pressed) {
            user_config.TrackballDPI -= TRACKBALL_DPI_STEP;
            if(user_config.TrackballDPI < TRACKBALL_DPI_MIN) {
                user_config.TrackballDPI = TRACKBALL_DPI_MIN;
            }
            eeconfig_update_user(user_config.TrackballDPI);
            pointing_device_set_cpi(user_config.TrackballDPI);
            return false;
        }
    }
    default:
    return true;
    
    }
}

void eeconfig_init_user(void) {
    user_config.TrackballDPI = TRACKBALL_DPI_DEFAULT;
    wait_ms(10);
    pointing_device_set_cpi(user_config.TrackballDPI);
    eeconfig_update_user(user_config.TrackballDPI);
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (host_keyboard_led_state().caps_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(28, 255, 255, 255); // assuming caps lock is at led #5
    } else {
        RGB_MATRIX_INDICATOR_SET_COLOR(28, 0, 0, 0);
    }
    return false;
}

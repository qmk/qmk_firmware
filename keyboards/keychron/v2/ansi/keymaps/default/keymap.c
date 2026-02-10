/* Copyright 2021 @ Keychron (https://www.keychron.com)
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
#include "unicode.h"
#include "timer.h"

static struct { bool on; bool first; } w_i_d_e_t_e_x_t = {false,false};
static struct { bool on; bool upper; } tAuNtTeXt = {false,false};

// clang-format off
enum layers {
    MAC_BASE,
    WIN_BASE,
    _FUNCTION,
    _GAMING,
    _GAMING2,
    _GAMING3,
    _FN5,
    _FN6,
    _FN7,
    _FN8
};

enum prilik_keycodes {
    _DUMMY = SAFE_RANGE,
    WIDETXT,
    TAUNTXT,
    UC_SHRG
};

#define KC_TASK LGUI(KC_TAB)
#define KC_FLXP LGUI(KC_E)

// --- Timer for auto-off ---
static uint32_t mode_last_activity = 0; // last keypress timestamp in ms
#define MODE_TIMEOUT 5000             // 5000 ms = 5 seconds

// Blink control
static uint32_t blink_timer = 0;         // tracks blinking
#define BLINK_INTERVAL 500               // 500 ms per blink
static bool blink_state = false;         // current on/off

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_ansi_67(
        QK_GESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC,
        KC_INS, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
        KC_DEL, KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
        KC_HOME, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP,
        KC_LCTL, KC_LALT, KC_LGUI, KC_SPC, KC_RGUI, MO(2), MO(4), KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [WIN_BASE] = LAYOUT_ansi_67(KC_TRNS, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_INS, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL, KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_HOME, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, MO(2), TG(3), TG(4), KC_LEFT, KC_DOWN, KC_RGHT),
    [_FUNCTION] = LAYOUT_ansi_67(KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS, UC_SHRG, RM_TOGG, RM_NEXT, RM_VALU, RM_HUEU, RM_SATU, RM_SPDU, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, WIDETXT, KC_TRNS, RM_PREV, RM_VALD, RM_HUED, RM_SATD, RM_SPDD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, TAUNTXT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, NK_TOGG, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
    [_GAMING] = LAYOUT_ansi_67(KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)
};

// --- RGB setup ---
void keyboard_post_init_user(void) {
    rgb_matrix_enable();
    rgb_matrix_mode(RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE);
}

// --- Gaming brightness boost ---
static uint8_t saved_hue = 0;
static uint8_t saved_sat = 0;
static uint8_t saved_val = 0;
static bool brightness_boosted = false;

layer_state_t layer_state_set_user(layer_state_t state) {
    bool gaming = layer_state_cmp(state, _GAMING) ||
                  layer_state_cmp(state, _GAMING2) ||
                  layer_state_cmp(state, _GAMING3);

    if (gaming && !brightness_boosted) {
        saved_hue = rgb_matrix_get_hue();
        saved_sat = rgb_matrix_get_sat();
        saved_val = rgb_matrix_get_val();

        rgb_matrix_sethsv_noeeprom(saved_hue, saved_sat, 255);
        brightness_boosted = true;
    } else if (!gaming && brightness_boosted) {
        rgb_matrix_sethsv_noeeprom(saved_hue, saved_sat, saved_val);
        brightness_boosted = false;
    }

    return state;
}

// --- RGB Layer and Key Highlights ---
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t layer = get_highest_layer(layer_state);

    uint32_t now = timer_read32();

    // Disable modes if timeout reached
    if ((w_i_d_e_t_e_x_t.on || tAuNtTeXt.on) && (now - mode_last_activity > MODE_TIMEOUT)) {
        w_i_d_e_t_e_x_t.on = false;
        tAuNtTeXt.on = false;
    }

    // Caps Lock indicator (white)
    if (host_keyboard_led_state().caps_lock) {
        uint8_t index = g_led_config.matrix_co[2][0]; // adjust if necessary
        if (index != NO_LED && index >= led_min && index < led_max) {
            rgb_matrix_set_color(index, 255, 255, 255);
        }
    }

    // FUNCTION layer → highlight active keys in BLUE
    if (layer == _FUNCTION) {
        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t index = g_led_config.matrix_co[row][col];
                if (index == NO_LED || index < led_min || index >= led_max) continue;

                uint16_t kc = keymap_key_to_keycode(layer, (keypos_t){col, row});
                if (kc > KC_TRNS) rgb_matrix_set_color(index, 0, 0, 255);
            }
        }
    }

    // --- Number keys highlighted based on active gaming layers ---
    uint8_t active_layers[] = {_GAMING, _GAMING2, _GAMING3};
    uint8_t highlight_colors[][3] = {
        {255, 0, 0},   // _GAMING → 1 → RED
        {0, 255, 255}, // _GAMING2 → 2 → CYAN
        {255, 165, 0}  // _GAMING3 → 3 → ORANGE
    };

    for (uint8_t l = 0; l < sizeof(active_layers)/sizeof(active_layers[0]); l++) {
        if (layer_state_cmp(layer_state, active_layers[l])) {
            uint8_t row = 0;
            uint8_t col = l + 1; // map to number row 1,2,3
            uint8_t index = g_led_config.matrix_co[row][col];
            if (index != NO_LED && index >= led_min && index < led_max) {
                rgb_matrix_set_color(index,
                    highlight_colors[l][0],
                    highlight_colors[l][1],
                    highlight_colors[l][2]
                );
            }
        }
    }

    // --- WASD highlight on gaming layers ---
    if (layer == _GAMING || layer == _GAMING2 || layer == _GAMING3) {
        const uint8_t wasd[][2] = {{1,2},{2,1},{2,2},{2,3}}; // W,A,S,D
        for (uint8_t i = 0; i < 4; i++) {
            uint8_t row = wasd[i][0];
            uint8_t col = wasd[i][1];
            uint8_t index = g_led_config.matrix_co[row][col];
            if (index != NO_LED && index >= led_min && index < led_max)
                rgb_matrix_set_color(index, 0, 255, 0); // GREEN
        }
    }

    // --- Always highlight ESC, SPACE, ENTER in ORANGE ---
    const uint8_t always_leds[] = {
        g_led_config.matrix_co[0][0],   // ESC
        g_led_config.matrix_co[4][6],   // SPACE
        g_led_config.matrix_co[2][13],  // ENTER
    };
    for (uint8_t i = 0; i < sizeof(always_leds); i++) {
        uint8_t index = always_leds[i];
        if (index != NO_LED && index >= led_min && index < led_max)
            rgb_matrix_set_color(index, 255, 165, 0); // ORANGE
    }

    // --- Optional: gaming pulsing column ---
    if (layer == _GAMING || layer == _GAMING2 || layer == _GAMING3) {
        static uint8_t val = 0;
        static int8_t dir = 8;
        val += dir;
        if (val > 255 || val < 80) dir = -dir;

        uint8_t rows[] = {0,1,2};
        uint8_t col = 14;
        for (uint8_t i = 0; i < 3; i++) {
            uint8_t index = g_led_config.matrix_co[rows[i]][col];
            if (index != NO_LED && index >= led_min && index < led_max)
                rgb_matrix_set_color(index, 0,0,val);
        }
    }

    // --- Blink logic ---
    if (now - blink_timer >= BLINK_INTERVAL) {
        blink_state = !blink_state;   // toggle blink
        blink_timer = now;
    }

    // --- Highlight Wide Text key ---
    if (w_i_d_e_t_e_x_t.on && blink_state) {
        uint8_t row = 1;
        uint8_t col = 14;
        uint8_t index = g_led_config.matrix_co[row][col];
        if (index != NO_LED) rgb_matrix_set_color(index, 255, 165, 0); // ORANGE
    }

    // --- Highlight Taunt Text key ---
    if (tAuNtTeXt.on && blink_state) {
        uint8_t row = 2;
        uint8_t col = 14;
        uint8_t index = g_led_config.matrix_co[row][col];
        if (index != NO_LED) rgb_matrix_set_color(index, 255, 165, 0); // ORANGE
    }

    return false;
}

// --- Process Record User ---
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Debug
    if (record->event.pressed) {
        uprintf("KC: %u | row: %u col: %u\n",
            keycode,
            record->event.key.row,
            record->event.key.col
        );
    }
    if (record->event.pressed) {
        mode_last_activity = timer_read32();  // reset the inactivity timer
    }
    // --- Wide Text ---
    if (w_i_d_e_t_e_x_t.on && record->event.pressed) {
        switch(keycode) {
            case KC_A...KC_0:
            case KC_MINUS...KC_SLASH:
            case KC_SPC:
                if (!w_i_d_e_t_e_x_t.first) tap_code(KC_SPC);
                w_i_d_e_t_e_x_t.first = false;
                break;
            case KC_ENT: w_i_d_e_t_e_x_t.first = true; break;
            case KC_BSPC: tap_code(KC_BSPC); break;
        }
    }

    if (tAuNtTeXt.on && record->event.pressed) {
        // Only modify alphabetical keys
        if ((keycode >= KC_A) && (keycode <= KC_Z)) {
            if (tAuNtTeXt.upper) {
                register_code(KC_LSFT);  // hold shift
                register_code(keycode);
                unregister_code(keycode);
                unregister_code(KC_LSFT);
            } else {
                register_code(keycode);  // normal
                unregister_code(keycode);
            }
            tAuNtTeXt.upper = !tAuNtTeXt.upper; // toggle next case
            return false; // already handled key
        }
    }

    // --- Custom Keycodes ---
    switch(keycode) {
        case WIDETXT:
            if (record->event.pressed) { w_i_d_e_t_e_x_t.on = !w_i_d_e_t_e_x_t.on; w_i_d_e_t_e_x_t.first=true; }
            return false;

        case TAUNTXT:
            if (record->event.pressed) {
                tAuNtTeXt.on = !tAuNtTeXt.on;
                tAuNtTeXt.upper = false; // reset case sequence
            }
            return false;

        case UC_SHRG:
            if (record->event.pressed) {
                send_unicode_string("¯\\_(ツ)_/¯");
            }
            return false;

        default: return true; // Let QMK handle everything else (Shift, Caps Word, etc.)
    }
}
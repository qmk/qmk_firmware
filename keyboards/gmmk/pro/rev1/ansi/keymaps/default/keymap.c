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

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//      ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12      Prt           Rotary(Mute)
//      ~        1        2        3        4        5        6        7        8        9        0         -       (=)      BackSpc           Del
//      Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]        \                 PgUp
//      CapsWrd  A        S        D        F        G        H        J        K        L        ;        "                 Enter             PgDn
//      Sh_L              Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       End
//      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right

    [0] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR,          KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_PGUP,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGDN,
        CW_TOGG, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_END,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_DEL,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(1),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

//      ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12      Prt           Rotary(RGB Bright)
//      ~        RGBTogg  ---      ---      ---      ---      ---      ---      ---      ---      ---      ---      ---      ---               ---
//      Tab      ---      RGBValU  ---      ---      ---      ---      ---      ---      ---      ---      ---      ---      ---               ---
//      ---      ---      RGBValD  ---      ---      ---      ---      ---      ---      ---      ---      ---               ---               ---
//      ---               ---      RGBHueU  ---      ---      ---      NKROtog  ---      ---      ---      ---               Rep    RGBNext    ---
//      ---      ---      ---                                 ---                                 ---      ---      ---      RGBSpd-  RGBPrev  RGBSpd+
//      Macro:   Rec1     Stop     Play1    Rec2     Stop     Play2
    [1] = LAYOUT(
        _______, KC_MYCM, KC_WHOM, KC_CALC, KC_MSEL, KC_MPRV, KC_MNXT, KC_MPLY, KC_MSTP, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______,          QK_BOOT,
        _______, RM_TOGG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, DM_REC1, RM_VALU, DM_REC2, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, DM_PLY1, RM_VALD, DM_PLY2, _______, _______, _______, _______, _______, _______, _______, _______,          DM_RSTP,          _______,
        _______,          _______, RM_HUEU, _______, _______, _______, NK_TOGG, _______, _______, _______, _______,          QK_REP,  RM_NEXT, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, RM_SPDD, RM_PREV, RM_SPDU
    ),

};
// clang-format on

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },  // volume
    [1] = { ENCODER_CCW_CW(RM_VALD, RM_VALU) }   // RGB brightness on FN
};
#endif

// -----------------------------------------------------------------------------
// Key overrides
// Shift + Backspace = Delete
const key_override_t bspc_del_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);

const key_override_t *key_overrides[] = {
    &bspc_del_override,
    NULL
};

// -----------------------------------------------------------------------------
// OS detection — swap Alt/GUI for macOS
bool process_detected_host_os_kb(os_variant_t detected_os) {
    if (detected_os == OS_MACOS || detected_os == OS_IOS) {
        keymap_config.swap_lalt_lgui = true;
        keymap_config.swap_ralt_rgui = true;
    } else {
        keymap_config.swap_lalt_lgui = false;
        keymap_config.swap_ralt_rgui = false;
    }
    return true;
}

// -----------------------------------------------------------------------------
// WPM — drive RGB animation speed with typing speed (throttled to ~4Hz)
void housekeeping_task_user(void) {
    static uint32_t last_wpm_update = 0;
    if (timer_elapsed32(last_wpm_update) < 250) return;
    last_wpm_update = timer_read32();

    uint8_t wpm = get_current_wpm();
    if (wpm > 0) {
        uint8_t spd = (uint8_t)MIN(255, MAX(30, (uint16_t)wpm * 2));
        rgb_matrix_set_speed_noeeprom(spd);
    }
}

// -----------------------------------------------------------------------------
// Force solid red on every boot, bypassing stale EEPROM values
void keyboard_post_init_user(void) {
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv_noeeprom(HSV_RED);
}

// -----------------------------------------------------------------------------
// Dynamic macro recording state — tracked via callbacks
static bool is_macro_recording = false;

bool dynamic_macro_record_start_user(int8_t direction) {
    is_macro_recording = true;
    return true;
}

bool dynamic_macro_record_end_user(int8_t direction) {
    is_macro_recording = false;
    return true;
}

// -----------------------------------------------------------------------------
// RGB indicators
#ifdef RGB_MATRIX_ENABLE

// Scale indicator colors to RGB_MATRIX_MAXIMUM_BRIGHTNESS
#define INDICATOR_AMBER RGB_MATRIX_MAXIMUM_BRIGHTNESS, (RGB_MATRIX_MAXIMUM_BRIGHTNESS * 160 / 255), 0
#define INDICATOR_RED   RGB_MATRIX_MAXIMUM_BRIGHTNESS, 0, 0
#define INDICATOR_CYAN  0, RGB_MATRIX_MAXIMUM_BRIGHTNESS, RGB_MATRIX_MAXIMUM_BRIGHTNESS
#define INDICATOR_GREEN 0, RGB_MATRIX_MAXIMUM_BRIGHTNESS, 0

// Side LEDs: left column l01-l08, right column l11-l18
static const uint8_t PROGMEM side_leds[] = {
    67, 70, 73, 76, 80, 83, 87, 91,  // left side
    68, 71, 74, 77, 81, 84, 88, 92   // right side
};

static void set_side_leds(uint8_t r, uint8_t g, uint8_t b) {
    for (uint8_t i = 0; i < sizeof(side_leds); i++) {
        rgb_matrix_set_color(pgm_read_byte(&side_leds[i]), r, g, b);
    }
}

// Defined in quantum/rgb_matrix/overlay.c — LampArray overlay
void rgb_matrix_overlay_apply(uint8_t led_min, uint8_t led_max);
bool rgb_matrix_overlay_is_enabled(void);

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    // Apply LampArray overlay (Windows Dynamic Lighting)
    rgb_matrix_overlay_apply(led_min, led_max);

    if (is_caps_word_on()) {
        // Caps Word: amber on Caps Lock key + sides
        rgb_matrix_set_color(3, INDICATOR_AMBER);
        set_side_leds(INDICATOR_AMBER);
    } else if (host_keyboard_led_state().caps_lock) {
        // Caps Lock: red on Caps Lock key + sides
        rgb_matrix_set_color(3, INDICATOR_RED);
        set_side_leds(INDICATOR_RED);
    }

    // Dynamic macro recording: green sides
    if (is_macro_recording) {
        set_side_leds(INDICATOR_GREEN);
    }

    // FN layer: cyan on FN key + sides (overrides above)
    if (get_highest_layer(layer_state) > 0) {
        rgb_matrix_set_color(55, INDICATOR_CYAN);
        set_side_leds(INDICATOR_CYAN);
    }

    return false;
}
#endif

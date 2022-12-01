/* Copyright 2022 Daniel Weeks (@xanimos)
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

#include "keymap.h"

static uint16_t idle_timer;             // Idle LED timeout timer
static uint8_t idle_second_counter;     // Idle LED seconds counter, counts seconds not milliseconds
static uint8_t key_event_counter;       // This counter is used to check if any keys are being held

static const char * sendstring_commands[] = {
    "git init",
    "git clone ",
    "git add ",
    "git diff ",
    "git reset --soft ",
    "git branch --list",
    "git checkout ",
    "git remote add ",
    "git fetch ",
    "git pull",
    "git pull upstream ",
    "git push",
    "git push -u origin ",
    "git push --force-with-lease",
    "git commit ",
    "git commit -m \": [TFS-]\"",
    "git status",
    "git log",
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_KL] = LAYOUT(
    //    ESC       F1       F2       F3       F4       F5       F6       F7       F8       F9       F10     F11      F12              PRINT    SCLCK    PAUSE
        KC_ESC ,  KC_F1 ,  KC_F2 ,  KC_F3 ,  KC_F4 ,  KC_F5 ,  KC_F6 ,  KC_F7 ,  KC_F8 ,  KC_F9 ,  KC_F10,  KC_F11,  KC_F12,          KC_PSCR, KC_SCRL,RCS(KC_M),
    //     ~        1        2        3        4        5        6        7        8        9        0        -        =      BCKSP     INS      HOME     PGUP
        KC_GRV ,  KC_1  ,  KC_2  ,  KC_3  ,  KC_4  ,  KC_5  ,  KC_6  ,  KC_7  ,  KC_8  ,  KC_9  ,  KC_0  , KC_MINS,  KC_EQL, KC_BSPC, KC_INS , KC_HOME, KC_PGUP,
    //    TAB       Q        W        E        R        T        Y        U        I        O        P        [        ]        \       DEL      END      PGDN
        KC_TAB ,  KC_Q  ,  KC_W  ,  KC_E  ,  KC_R  ,  KC_T  ,  KC_Y  ,  KC_U  ,  KC_I  ,  KC_O  ,  KC_P  , KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL , KC_END , KC_PGDN,
    //   CAPS       A        S        D        F        G        H        J        K        L        ;        '      ENTER
        KC_CAPS,  KC_A  ,  KC_S  ,  KC_D  ,  KC_F  ,  KC_G  ,  KC_H  ,  KC_J  ,  KC_K  ,  KC_L  , KC_SCLN, KC_QUOT, KC_ENT ,
    //   SHIFT      Z        X        C        V        B        N        M        ,        .        /      RSHIFT                               UP
        SC_LSPO,  KC_Z  ,  KC_X  ,  KC_C  ,  KC_V  ,  KC_B  ,  KC_N  ,  KC_M  , KC_COMM, KC_DOT , KC_SLSH, SC_RSPC,                             KC_UP ,
    //   CTRL      GUI      ALT                       SPACE                               RALT     MENU     RGUI     RCTRL             LEFT     DOWN     RIGHT
       KC_LCTL,  KC_LGUI, KC_LALT,                    KC_SPC,                   TD(TD_FN_SWITCH), KC_RALT, KC_RGUI, KC_RCTL,          KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_FL] = LAYOUT(
    //    ESC       F1       F2       F3       F4       F5       F6       F7       F8       F9       F10     F11      F12              PRINT    SCLCK    PAUSE
        _______, ROUT_TG, ROUT_FM, ROUT_VD, ROUT_VI, _______, _______, _______, _______, _______, _______, KC_WAKE, KC_SLEP,          KC_PAUS, _______, KC_MUTE,
    //     ~        1        2        3        4        5        6        7        8        9        0        -        =      BCKSP     INS      HOME     PGUP
        RGB_TOG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MSTP, KC_MPLY, KC_VOLU,
    //    TAB       Q        W        E        R        T        Y        U        I        O        P        [        ]        \       DEL      END      PGDN
        _______, RGB_MOD, RGB_SPI, RGB_VAI, RGB_HUI, RGB_SAI, _______, _______, _______, _______, _______, _______, _______, _______, KC_MPRV, KC_MNXT, KC_VOLD,
    //   CAPS       A        S        D        F        G        H        J        K        L        ;        '      ENTER
        _______,RGB_RMOD, RGB_SPD, RGB_VAD, RGB_HUD, RGB_SAD, _______, _______, _______, _______, _______, _______, _______,
    //   SHIFT      Z        X        C        V        B        N        M        ,        .        /      RSHIFT                               UP
        _______, _______, _______,COPY_ALL, _______, MD_BOOT, NK_TOGG, _______, _______, _______, _______, TOG_NPD,                            KC_BRIU,
    //   CTRL      GUI      ALT                       SPACE                               RALT     MENU     RGUI     RCTRL             LEFT     DOWN     RIGHT
        _______, _______, _______,                   _______,                            _______, _______, _______, _______,          _______, KC_BRID, _______
    ),
    [_GL] = LAYOUT(
    //    ESC       F1       F2       F3       F4       F5       F6       F7       F8       F9       F10     F11      F12              PRINT    SCLCK    PAUSE
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
    //     ~        1        2        3        4        5        6        7        8        9        0        -        =      BCKSP     INS      HOME     PGUP
         G_INIT, G_CLONE, G_REMTE, G_RESET, G_PSFWL, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    //    TAB       Q        W        E        R        T        Y        U        I        O        P        [        ]        \       DEL      END      PGDN
        _______, G_PUPST,  G_PULL, G_PSORG,  G_PUSH, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    //   CAPS       A        S        D        F        G        H        J        K        L        ;        '      ENTER
        _______,   G_ADD,  G_STAT,  G_DIFF, G_FETCH, _______, _______, _______, _______, _______, _______, _______, _______,
    //   SHIFT      Z        X        C        V        B        N        M        ,        .        /      RSHIFT                               UP
        _______,   G_LOG, G_CHECK,  G_COMM, G_COMSG, G_BRANH, _______, _______, _______, _______, _______, _______,                            _______,
    //   CTRL      GUI      ALT                       SPACE                               RALT     MENU     RGUI     RCTRL             LEFT     DOWN     RIGHT
        _______, _______, _______,                   _______,                            _______, _______, _______, _______,          _______, _______, _______
    ),
    [_NUMPAD] = LAYOUT(
    //    ESC       F1       F2       F3       F4       F5       F6       F7       F8       F9       F10     F11      F12              PRINT    SCLCK    PAUSE
        TOG_NPD, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
    //     ~        1        2        3        4        5        6        7        8        9        0        -        =      BCKSP     INS      HOME     PGUP
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    //    TAB       Q        W        E        R        T        Y        U        I        O        P        [        ]        \       DEL      END      PGDN
        _______, _______, _______, _______, _______, _______,   KC_P7,   KC_P8,   KC_P9, _______, _______, _______, _______, _______, _______, _______, _______,
    //   CAPS       A        S        D        F        G        H        J        K        L        ;        '      ENTER
        _______, _______, _______, _______, _______, _______,   KC_P4,   KC_P5,   KC_P6, _______, _______, _______, _______,
    //   SHIFT      Z        X        C        V        B        N        M        ,        .        /      RSHIFT                               UP
        _______, _______, _______, _______, _______,   KC_P1,   KC_P2,   KC_P3, KC_PDOT, _______, _______, _______,                            _______,
    //   CTRL      GUI      ALT                       SPACE                               RALT     MENU     RGUI     RCTRL             LEFT     DOWN     RIGHT
        _______, _______, _______,                     KC_P0,                            _______, _______, _______, _______,          _______, _______, _______
    ),
    /*
    [X] = LAYOUT(
    //    ESC       F1       F2       F3       F4       F5       F6       F7       F8       F9       F10     F11      F12              PRINT    SCLCK    PAUSE
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
    //     ~        1        2        3        4        5        6        7        8        9        0        -        =      BCKSP     INS      HOME     PGUP
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    //    TAB       Q        W        E        R        T        Y        U        I        O        P        [        ]        \       DEL      END      PGDN
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    //   CAPS       A        S        D        F        G        H        J        K        L        ;        '      ENTER
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    //   SHIFT      Z        X        C        V        B        N        M        ,        .        /      RSHIFT                               UP
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                            _______,
    //   CTRL      GUI      ALT                       SPACE                               RALT     MENU     RGUI     RCTRL             LEFT     DOWN     RIGHT
        _______, _______, _______,                   _______,                            _______, _______, _______, _______,          _______, _______, _______
    ),
    */
};

#define __OFF__ {0, 0, 0}

const uint8_t PROGMEM ledmap[][RGB_MATRIX_LED_COUNT][3] = {
    [_FL] = {
        //  These remain on base layer rgb to see adjustments ;)
        //       |----------------------------------|
    //  _______, ROUT_TG, ROUT_FM, ROUT_VD, ROUT_VI, _______, _______, _______, _______, _______, _______, KC_WAKE, KC_SLEP,          KC_PAUS, _______, KC_MUTE,
        __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__,  YELLOW,  YELLOW,           ORANGE, __OFF__,    GOLD,
    //  RGB_TOG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MSTP, KC_MPLY, KC_VOLU,
           GOLD, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__,     RED,  SPRING,  ORANGE,
    //  _______, RGB_MOD, RGB_SPI, RGB_VAI, RGB_HUI, RGB_SAI, _______, _______, _______, _______, _______, _______, _______, _______, KC_MPRV, KC_MNXT, KC_VOLD,
        __OFF__,  ORANGE,   GREEN,   AZURE,  GOLDEN,  MAGENT, __OFF__,   AZURE,   AZURE, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__,    TEAL,    TEAL,  ORANGE,
    //  _______,RGB_RMOD, RGB_SPD, RGB_VAD, RGB_HUD, RGB_SAD, _______, _______, _______, _______, _______, _______, _______,
        __OFF__,  ORANGE,   GREEN,   AZURE,  GOLDEN,  MAGENT, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__,
    //  _______, _______, _______,COPY_ALL, _______, MD_BOOT, NK_TOGG, _______, _______, _______, _______, TO(_NUMPAD),                        KC_BRIU,
        __OFF__, __OFF__, __OFF__,   CORAL, __OFF__,     RED,    TURQ, __OFF__, __OFF__, __OFF__, __OFF__,    CYAN,                             SPRING,
    //  _______, _______, _______,                   _______,                            _______, _______, _______, _______,          _______, KC_BRID, _______
        __OFF__, __OFF__, __OFF__,                   __OFF__,                            __OFF__, __OFF__, __OFF__, __OFF__,          __OFF__,  SPRING, __OFF__
    },
    [_GL] = {
    //  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__,          __OFF__, __OFF__, __OFF__,
    //   G_INIT, G_CLONE, G_REMTE, G_RESET, G_PSFWL, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
          AZURE,   CHART,   CHART,     RED,   CORAL, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__,
    //  _______, G_PUPST,  G_PULL, G_PSORG,  G_PUSH, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        __OFF__,    BLUE,  PURPLE,  MAGENT,    PINK, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__,
    //  _______,   G_ADD,  G_STAT,  G_DIFF, G_FETCH, _______, _______, _______, _______, _______, _______, _______, _______,
        __OFF__,  SPRING,   GREEN,    TURQ,    TEAL, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__,
    //  _______,   G_LOG, G_CHECK,  G_COMM, G_COMSG, G_BRANH, _______, _______, _______, _______, _______, _______,                            _______,
        __OFF__,    CYAN,  GOLDEN,  YELLOW,    GOLD,   CHART, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__,                            __OFF__,
    //  _______, _______, _______,                   _______,                            _______, _______, _______, _______,          _______, _______, _______
        __OFF__, __OFF__, __OFF__,                   __OFF__,                            __OFF__, __OFF__, __OFF__, __OFF__,          __OFF__, __OFF__, __OFF__
    },
    [_NUMPAD] = {
    //  TO(_KL), _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
            RED, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__,          __OFF__, __OFF__, __OFF__,
    //  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__,
    //  _______, _______, _______, _______, _______, _______,   KC_P7,   KC_P8,   KC_P9, _______, _______, _______, _______, _______, _______, _______, _______,
        __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__,   GREEN,   GREEN,   GREEN, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__,
    //  _______, _______, _______, _______, _______, _______,   KC_P4,   KC_P5,   KC_P6, _______, _______, _______, _______,
        __OFF__, __OFF__, __OFF__, __OFF__, __OFF__, __OFF__,    TURQ,    TURQ,    TURQ, __OFF__, __OFF__, __OFF__, __OFF__,
    //  _______, _______, _______, _______, _______, _______,   KC_P1,   KC_P2,   KC_P3, KC_PDOT, _______, _______,                            _______,
        __OFF__, __OFF__, __OFF__, __OFF__, __OFF__,    CYAN,    CYAN,    CYAN,   AZURE, __OFF__, __OFF__, __OFF__,                            __OFF__,
    //  _______, _______, _______,                     KC_P0,                            _______, _______, _______, _______,          _______, _______, _______
        __OFF__, __OFF__, __OFF__,                      CYAN,                            __OFF__, __OFF__, __OFF__, __OFF__,          __OFF__, __OFF__, __OFF__
    },
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
    // Enable or disable debugging
    debug_enable = false;
    debug_matrix = false;
    debug_keyboard = false;
    debug_mouse = false;

    idle_second_counter = 0;                            // Counter for number of seconds keyboard has been idle.
    key_event_counter = 0;                              // Counter to determine if keys are being held, neutral at 0.
    rgb_time_out_seconds = RGB_DEFAULT_TIME_OUT;        // RGB timeout initialized to its default configure in keymap.h
    rgb_time_out_enable = false;                        // Disable RGB timeout by default. Enable using toggle key.
    rgb_time_out_user_value = false;                    // Has to have the same initial value as rgb_time_out_enable.
    rgb_enabled_flag = true;                            // Initially, keyboard RGB is enabled. Change to false config.h initializes RGB disabled.
    rgb_time_out_fast_mode_enabled = false;             // RGB timeout fast mode disabled initially.
    rgb_time_out_saved_flag = rgb_matrix_get_flags();   // Save RGB matrix state for when keyboard comes back from ide.
};

void keyboard_post_init_user(void) {
    rgb_matrix_enable();
}

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
    if(rgb_time_out_enable && rgb_enabled_flag) {
        // If the key event counter is not zero then some key was pressed down but not released, thus reset the timeout counter.
        if (key_event_counter) {
            idle_second_counter = 0;
        } else if (timer_elapsed(idle_timer) > MILLISECONDS_IN_SECOND) {
            idle_second_counter++;
            idle_timer = timer_read();
        }

        if (idle_second_counter >= rgb_time_out_seconds) {
            rgb_time_out_saved_flag = rgb_matrix_get_flags();
            rgb_matrix_set_flags(LED_FLAG_NONE);
            rgb_matrix_disable_noeeprom();
            rgb_enabled_flag = false;
            idle_second_counter = 0;
        }
    }
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint32_t key_timer;

    // Increment key event counter for every press and decrement for every release.
    if (record->event.pressed) {
        key_event_counter++;

    } else {
        key_event_counter--;
    }

    if (rgb_time_out_enable) {
        idle_timer = timer_read();
        // Reset the seconds counter. Without this, something like press> leave x seconds> press, would be x seconds on the effective counter not 0 as it should.
        idle_second_counter = 0;
        if (!rgb_enabled_flag) {
            rgb_matrix_enable_noeeprom();
            rgb_matrix_set_flags(rgb_time_out_saved_flag);
            rgb_enabled_flag = true;
        }
    }

    switch (keycode) {
        case MD_BOOT:
            if (record->event.pressed) {
                key_timer = timer_read32();
            } else {
                if (timer_elapsed32(key_timer) >= 500) {
                    reset_keyboard();
                }
            }
            return false;
    }

    if (record->event.pressed) {
        switch (keycode) {
            case RGB_TOG:
                rgb_time_out_enable = rgb_time_out_user_value;
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
                        // This line is for LED idle timer. It disables the toggle so you can turn off LED completely if you like
                        rgb_time_out_enable = false;
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
            // ======================================================== CUSTOM KEYCOADS BELOW ========================================================
            case COPY_ALL:
                // Selects all and text and copy
                SEND_STRING(SS_LCTL("ac"));
                return false;
            case ROUT_TG:
                // Toggle idle LED timeout on or off
                rgb_time_out_enable = !rgb_time_out_enable;
                rgb_time_out_user_value = rgb_time_out_enable;
                return false;
            case ROUT_VI:
                // Increase idle LED timeout value in seconds
                // Only increase if current value is lower than RGB_TIME_OUT_MAX. Don't care what value the result will be
                // Modity RGB_TIME_OUT_STEP for bigger or smaller increments
                if (!rgb_time_out_fast_mode_enabled && rgb_time_out_seconds <= RGB_TIME_OUT_MAX) {
                    rgb_time_out_seconds += RGB_TIME_OUT_STEP;
                }
                return false;
            case ROUT_VD:
                // Decrease idle LED timeout value in seconds
                // Only decrease if current value is higher than minimum value and the result is larger than zero
                // Modity RGB_TIME_OUT_STEP for bigger or smaller decrements
                if (!rgb_time_out_fast_mode_enabled && rgb_time_out_seconds > RGB_TIME_OUT_MIN) {
                    rgb_time_out_seconds -= RGB_TIME_OUT_STEP;
                }
                return false;
            case ROUT_FM:
                if (rgb_time_out_fast_mode_enabled) {
                    rgb_time_out_seconds = rgb_time_out_saved_seconds;
                } else {
                    rgb_time_out_saved_seconds = rgb_time_out_seconds;
                    rgb_time_out_seconds = RGB_FAST_MODE_TIME_OUT;
                }
                rgb_time_out_fast_mode_enabled = !rgb_time_out_fast_mode_enabled;
                return false;
            case G_INIT ... G_LOG:
                send_string_with_delay(sendstring_commands[keycode - G_INIT], 5);
                return false;
            case TOG_NPD:
                if (get_highest_layer(layer_state) != _NUMPAD) {
                    layer_move(_NUMPAD);
                } else {
                    layer_move(_KL);
                }
                return false;
        }
    }
    return true;
}

void set_layer_color(int layer) {
    if (layer == 0) { return; }
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
            continue;
        }
        if(layer == _FL && i <= 4 && i >= 1) {
            continue; // Leave RGB for F1-F4 of function layer to adjust RGB settings
        }

        rgb_matrix_set_color(i, 0, 0, 0);
    }
}

bool rgb_matrix_indicators_user(void) {
    if (disable_layer_color ||
        rgb_matrix_get_flags() == LED_FLAG_NONE ||
        rgb_matrix_get_flags() == LED_FLAG_UNDERGLOW) {
            return;
        }
    set_layer_color(get_highest_layer(layer_state));
    return false;
}



td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->pressed && !state->interrupted) {
        if (state->count == 1) { return TD_SINGLE_HOLD; }
        return TD_DOUBLE_HOLD;
    }
    return TD_UNKNOWN;
}

static td_tap_t fn_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void fn_tap_finished(qk_tap_dance_state_t *state, void *user_data) {
    fn_tap_state.state = cur_dance(state);
    switch (fn_tap_state.state) {
        case TD_SINGLE_HOLD:
            // set function layer
            layer_move(_FL);
            break;
        case TD_DOUBLE_HOLD:
            // set git layer
            layer_move(_GL);
            break;
        case TD_UNKNOWN:
            register_code(KC_APP);
            break;
        default:
            break;
    }
}

void fn_tap_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (fn_tap_state.state) {
        case TD_UNKNOWN:
            unregister_code(KC_APP);
            break;
        case TD_DOUBLE_HOLD:
        case TD_SINGLE_HOLD:
            // Set default layer if we didn't activate numpad layer in function
            if (get_highest_layer(layer_state) != _NUMPAD) {
                layer_move(_KL);
            }
            break;
        break;
        default:
        break;
    }
    fn_tap_state.state = TD_NONE;
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_FN_SWITCH] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, fn_tap_finished, fn_tap_reset)
};

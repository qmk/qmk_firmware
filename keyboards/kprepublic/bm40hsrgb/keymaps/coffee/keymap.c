// Copyright 2022 Fae Fankhauser (@CoffeeIsLife87)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum custom_keycodes {
    MCR_PLY = QK_USER, // Macro play
    MCR_REC,           // Macro record
    MCR_SWT,           // Swap active macro
    MS_ACL_U,          // Mouse speed up
    MS_ACL_D,          // Mouse speed down
};

enum layout_names {
    _MAIN = 0,       // Keys Layout: The main keyboard layout that has all the characters
    _SUB,            // Extension to Main
    _CTR,            // Macros, RGB, Audio controls, layer access. More or less the control center of my keyboard
    #ifdef MOUSEKEY_ENABLE
    _MSE,
    #endif // MOUSEKEY_ENABLE
    _END,
};

#ifdef MOUSEKEY_ENABLE
#include "action.h"
#define TOG_MSE TG(_MSE)
static int current_accel = 0;
#else
#define TOG_MSE XXXXXXX
#endif // MOUSEKEY_ENABLE

#ifdef DYNAMIC_MACRO_ENABLE
// Macro 1 is = 1, Macro 2 = -1, No macro = 0
static bool MACRO1 = true; // Determines whether or not we're using 1 or 2
static bool RECORDING = false;
static uint16_t REC = DM_REC1; // Record either macro 1 or 2. Or stop recording
static uint16_t PLY = DM_PLY1; // Play either macro 1 or macro 2

void dynamic_macro_record_start_user(int8_t direction) {
    REC = DM_RSTP;
    RECORDING = true;
}

void dynamic_macro_record_end_user(int8_t direction) {
    RECORDING = false;
}
#else
#define MCR_PLY KC_NO
#define MCR_REC KC_NO
#define MCR_SWT KC_NO
#endif // DYNAMIC_MACRO_ENABLE

#ifdef TURBO_ENABLE
static bool turbo_active = false; // Only changed by TRBO_ST
static uint16_t turbo_keycode = KC_NO; // turbo_active can't be true if this is KC_NO
static bool turbo_key_pressed = false;
static bool turbo_keycode_selecting = false; // Determine new keycode or delay mode switch
static bool turbo_ms_delay_direction = true; // True is raise the delay, false is lower it
static uint16_t turbo_ms_delay_direction_indicator = 0;
static uint16_t turbo_ms_delay = 100; // Start at sending keycodes 10 times a second
static uint16_t turbo_timer; // Changed semi automatically
/*
 * Because the KC's are wrapped in `LT()` they won't be interpreted as KC_NO or KC_TRNS
 * Instead they'll just be like any other custom KC which will let me use them how I want 
*/
#define TRBO_ST LT(_CTR, KC_NO  )
#define TRBO_TI LT(_CTR, KC_TRNS)
#else
#define TRBO_ST KC_NO
#define TRBO_TI KC_NO
#endif

const uint16_t PROGMEM keymaps[_END][MATRIX_ROWS][MATRIX_COLS] = {
    [_MAIN] = LAYOUT_planck_mit(
        KC_ESC , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSPC,
        KC_TAB , KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_ENT ,
        KC_LCTL, KC_LGUI, XXXXXXX,KC_LALT ,MO(_SUB),      KC_SPC     ,MO(_CTR), KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT
    ),
    [_SUB] = LAYOUT_planck_mit(
        KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_DEL,
        XXXXXXX, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_MINS, KC_EQL , KC_LBRC, KC_RBRC, KC_PGUP,
        _______, KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , XXXXXXX, KC_HOME, KC_END , KC_BSLS, KC_PGDN,
        _______, _______, XXXXXXX, _______, _______,      _______    , _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),
    [_CTR] = LAYOUT_planck_mit(
        XXXXXXX, RGB_SPD, RGB_VAI, RGB_SPI, RGB_HUI, RGB_SAI, XXXXXXX, XXXXXXX, KC_VOLU, XXXXXXX, XXXXXXX, MCR_REC,
        XXXXXXX, RGB_RMOD,RGB_VAD, RGB_MOD, RGB_HUD, RGB_SAD, XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, MCR_PLY,
        XXXXXXX, XXXXXXX, RGB_TOG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLD, XXXXXXX, XXXXXXX, MCR_SWT,
        XXXXXXX, XXXXXXX, XXXXXXX, TRBO_TI, TRBO_ST,      TOG_MSE,     _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    )
    #ifdef MOUSEKEY_ENABLE
    ,[_MSE] = LAYOUT_planck_mit(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, XXXXXXX, XXXXXXX, KC_BTN1, KC_WH_D, KC_WH_U, KC_BTN2, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, MS_ACL_D,      TOG_MSE,    MS_ACL_U,XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    )
    #endif // MOUSEKEY_ENABLE
};

#ifdef RGB_MATRIX_ENABLE

#define LAYER (get_highest_layer(layer_state))
#define LAYER_SIZE (MATRIX_ROWS * MATRIX_COLS)
#define BRIGHTNESS rgb_matrix_get_val()

#ifdef UNDERGLOW_DISABLE
void keyboard_pre_init_user(void) {
    for (int key_id = 0; key_id < RGB_MATRIX_LED_COUNT; key_id++ ) {
        if (g_led_config.flags[key_id] == LED_FLAG_UNDERGLOW) {
            g_led_config.flags[key_id] = LED_FLAG_NONE;
        }
    }
}
#endif // UNDERGLOW_DISABLE

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (LAYER == _MAIN) {return false;}

    for (uint8_t i = led_min; i <= led_max; i++) {
        uint8_t pos = ((uint8_t*)g_led_config.matrix_co)[i];
        if (!HAS_ANY_FLAGS(g_led_config.flags[pos], (LED_FLAG_MODIFIER | LED_FLAG_KEYLIGHT))) {continue;}
        uint16_t KC = pgm_read_word(&((uint16_t*)keymaps)[(LAYER_SIZE * LAYER) + i]);

        switch (KC) {
            case KC_NO:
                RGB_MATRIX_INDICATOR_SET_COLOR(pos, 0, 0, 0 );
                break;

            #ifdef DYNAMIC_MACRO_ENABLE
            case MCR_SWT:
                if (!MACRO1) { RGB_MATRIX_INDICATOR_SET_COLOR(pos, 0, BRIGHTNESS, BRIGHTNESS); }
                break;

            case MCR_REC:
                if (RECORDING) { RGB_MATRIX_INDICATOR_SET_COLOR(pos, BRIGHTNESS, 0, 0); }
                break;
            #endif // DYNAMIC_MACRO_ENABLE

            #ifdef TURBO_ENABLE
            case TRBO_ST:
                if (turbo_keycode_selecting) {
                    RGB_MATRIX_INDICATOR_SET_COLOR(pos, BRIGHTNESS, BRIGHTNESS, BRIGHTNESS);
                } else {
                    if (turbo_active) {
                        if (turbo_key_pressed) {
                            RGB_MATRIX_INDICATOR_SET_COLOR(pos, BRIGHTNESS, BRIGHTNESS, BRIGHTNESS);
                        } else {
                            RGB_MATRIX_INDICATOR_SET_COLOR(pos, 0, 0, 0);
                        }
                    }
                }
                break;

            case TRBO_TI:
                if (turbo_ms_delay_direction_indicator != 0) {
                    uint8_t time = timer_elapsed(turbo_ms_delay_direction_indicator) / 200;
                    if (time > 0) {
                        if ((time % 2) == 1) {
                            if (turbo_ms_delay_direction) {
                                RGB_MATRIX_INDICATOR_SET_COLOR(pos, 0, BRIGHTNESS, 0);
                            } else {
                                RGB_MATRIX_INDICATOR_SET_COLOR(pos, BRIGHTNESS, 0, 0);
                            }
                        } else {
                            RGB_MATRIX_INDICATOR_SET_COLOR(pos, 0, 0, 0);
                        }
                        if (time >= 6) {
                            turbo_ms_delay_direction_indicator = 0;
                        }
                    }
                }
                break;
            #endif

        }
    }
    return false;
}
#endif

#ifdef TURBO_ENABLE
void housekeeping_task_user(void) {
    if (turbo_active) {
        if (turbo_key_pressed) {
            if (timer_elapsed(turbo_timer) > turbo_ms_delay) {
                unregister_code(turbo_keycode);
                turbo_key_pressed = false;
                turbo_timer = timer_read();
            }
        } else {
            if (timer_elapsed(turbo_timer) > (turbo_ms_delay / 2)) {
                register_code(turbo_keycode);
                turbo_key_pressed = true;
            }
        }
    }
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    #ifdef DYNAMIC_MACRO_ENABLE
    if (keycode == MCR_REC) {keycode = REC;}
    if (keycode == MCR_PLY) {keycode = PLY;}
    if (!process_dynamic_macro(keycode, record)) {
        REC = (MACRO1 ? DM_REC1 : DM_REC2);
        return false;
    }
    #endif // DYNAMIC_MACRO_ENABLE

    #ifdef MOUSEKEY_ENABLE
    if ((keycode == MS_ACL_U) || (keycode == MS_ACL_D)) {
        if (record->event.pressed) {
            if ( (keycode == MS_ACL_U) && (current_accel < 2) ) { current_accel += 1; }
            if ( (keycode == MS_ACL_D) && (current_accel > 0) ) { current_accel -= 1; }
        }
        keycode = KC_ACL0 + current_accel;
        action_t mousekey_action = action_for_keycode(keycode);
        process_action(record, mousekey_action);
    }
    #endif // MOUSEKEY_ENABLE

    #ifdef TURBO_ENABLE
    if (record->event.pressed) {
        if (turbo_keycode_selecting) {
            if (IS_BASIC_KEYCODE(keycode)    || 
                IS_MODIFIER_KEYCODE(keycode) ||
                IS_JOYSTICK_KEYCODE(keycode) ||
                IS_MOUSE_KEYCODE(keycode))
            {
                unregister_code(turbo_keycode);
                turbo_key_pressed = false;
                turbo_keycode = keycode;
                turbo_keycode_selecting = false;
            }
        }
    }
    #endif

    switch (keycode) {
        #ifdef DYNAMIC_MACRO_ENABLE
        case MCR_SWT:
            if (!RECORDING && record->event.pressed) {
                // if the button is pressed and we're not recording
                MACRO1 = !MACRO1;
                if (MACRO1) {
                    REC = DM_REC1;
                    PLY = DM_PLY1;
                } else {
                    REC = DM_REC2;
                    PLY = DM_PLY2;
                }
            }
            return false;
        #endif // DYNAMIC_MACRO_ENABLE

        #ifdef TURBO_ENABLE
        case TRBO_ST:
            if (record->event.pressed) {
                if (!record->tap.count) {
                    turbo_keycode_selecting = !turbo_keycode_selecting;
                } else {
                    if (turbo_keycode != KC_NO) {
                        if (!turbo_active) {
                            turbo_keycode_selecting = false;
                            turbo_active = true;
                        } else {
                            unregister_code(turbo_keycode);
                            turbo_key_pressed = false;
                            turbo_active = false;
                        }
                    }
                }
            }
            return false;

        case TRBO_TI:
            if (record->event.pressed) {
                if (!record->tap.count) {
                    turbo_ms_delay_direction = !turbo_ms_delay_direction;
                    turbo_ms_delay_direction_indicator = timer_read();
                } else {
                    if (turbo_ms_delay_direction)
                        turbo_ms_delay += 20;
                    else
                        turbo_ms_delay -= 20;

                    if (turbo_ms_delay > 500) // half a second
                        turbo_ms_delay = 500;
                    if (turbo_ms_delay < 60) // Around 16 times a second
                        turbo_ms_delay = 60;
                }
            }
            return false;
        #endif

        default:
            return true; //Process all other keycodes normally
    }
}

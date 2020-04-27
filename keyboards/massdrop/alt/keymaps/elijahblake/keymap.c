#include "keymap.h"

static uint16_t idle_timer;             // Idle LED timeout timer
static uint8_t idle_second_counter;     // Idle LED seconds counter, counts seconds not milliseconds
static uint8_t key_event_counter;       // This counter is used to check if any keys are being held

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
    [DEFAULT] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL, 
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGUP,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_PGDN,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(1),   KC_LEFT, KC_DOWN, KC_RGHT 
    ),
    */
   [_KL] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,              KC_BSPC, KC_DEL,  
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,             KC_BSLS, KC_HOME, 
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,                      KC_ENT,  KC_PGUP, 
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,                      KC_UP,   KC_PGDN, 
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(_FL), KC_LEFT, KC_DOWN, KC_RGHT  
        ),
    [_FL] = LAYOUT(
        KC_GRV,  KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,    KC_F13,    KC_CALC, 
        RGB_M_P, RGB_SPD,  RGB_HUI, RGB_SPI, RGB_SAI, RGB_VAI, _______, _______, _______, _______, KC_PSCR, KC_SLCK, KC_PAUS,   _______,   KC_MYCM, 
        RGB_TOG, RGB_RMOD, RGB_HUD, RGB_MOD, RGB_SAD, RGB_VAD, _______, _______, _______, _______, _______, _______,            KC_MUTE,   KC_VOLU, 
        _______, _______,  ROUT_FM, _______, _______, MD_BOOT, NK_TOGG, DBG_TOG, _______, _______, _______, _______,            KC_VOLU,   KC_VOLD, 
        ROUT_TG, ROUT_VI,  ROUT_VD,                            KC_MPLY,                            _______, _______, KC_HOME,   KC_VOLD,   KC_END  
    ),
    /*
    [X] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______ 
    ),
    [RGB] = LAYOUT(
        ESC: 0,   1: 1,     2: 2,     3: 3,   4: 4,   5: 5,   6: 6,   7: 7,   8: 8,     9: 9,     0: 10,     MINS: 11,  EQL: 12,  BSPC:13,   DEL:14,
        TAB: 15,  Q: 16,    W: 17,    E: 18,  R: 19,  T: 20,  Y: 21,  U: 22,  I: 23,    O: 24,    P: 25,     LBRC: 26,  RBRC: 27, BSLS:28,   HOME:29,
        CAPS: 30, A: 31,    S: 32,    D: 33,  F: 34,  G: 35,  H: 36,  J: 37,  K: 38,    L: 39,    SCLN: 40,  QUOT:41,             ENT:42,    PGUP: 43,
        LSFT: 44, Z: 45,    X: 46,    C: 47,  V: 48,  B: 49,  N: 50,  M: 51,  COMM: 52, DOT: 53,  SLSH: 54,  RSFT: 55,            UP: 56,    PGDN: 57,
        LCTL: 58, LGUI: 59, LALT: 60,               SPC: 61,                            RALT: 62, FN: 63,               LEFT: 64, DOWN: 65,  RGHT: 66
    ),
    [MATRIX] = LAYOUT(
        0,      1,      2,      3,      4,      5,      6,   7,     8,      9,      10,     11,         12,     13,     14,
        15,     16,     17,     18,     19,     20,     21,  22,    23,     24,     25,     26,         27,     28,     29,
        30,     31,     32,     33,     34,     35,     36,  37,    38,     39,     40,     41,         42,             43,
        44,     45,     46,     47,     48,     49,     50,  51,    52,     53,     54,     55,                 56,     57,
        58,     59,     60,                             61,                         62,     63,         64,     65,     66
    ),
    */
};

#ifdef _______
#undef _______
#define _______ {0, 0, 0}

const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {
    [_KL] = {
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, GREEN,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, GREEN,   GREEN,   GREEN,   _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          GREEN,   _______,
        _______, _______, _______,                            _______,                            _______, _______, GREEN,   GREEN,   GREEN 
    },
    [_FL] = {
        PURPLE,  PURPLE,  PURPLE,  PURPLE,  PURPLE,  PURPLE,  PURPLE,  PURPLE,  PURPLE,   PURPLE,  PURPLE,  PURPLE,  PURPLE,    PURPLE,  BLUE, 
        GOLD,    PINK,    AZURE,   PINK,    TURQ,    TEAL,    _______, _______, _______,  _______, RED,     RED,     GOLD,               _______,   BLUE, 
        TEAL,    MAGENT,  AZURE,   MAGENT,  TURQ,    TEAL,    _______, _______, _______,  _______, _______, _______,                     GOLD,      BLUE, 
        _______, _______, _______, _______, _______, RED,     RED,     RED,     _______,  _______, _______, _______,                     GOLD,      BLUE, 
        _______, _______, _______,                            GOLD,                                _______, _______,            BLUE,    GOLD,      RED   
    },
};

#undef _______
#define _______ KC_TRNS
#endif

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
    // Enable or disable debugging
    debug_enable=true;
    debug_matrix=true;
    debug_keyboard=true;
    debug_mouse=false;

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
        switch (keycode) {
            case DBG_TOG:
                TOGGLE_FLAG_AND_PRINT(debug_enable, "Debug mode");
                return false;
            case DBG_MTRX:
                TOGGLE_FLAG_AND_PRINT(debug_matrix, "Debug matrix");
                return false;
            case DBG_KBD:
                TOGGLE_FLAG_AND_PRINT(debug_keyboard, "Debug keyboard");
                return false;
            case DBG_MOU:
                TOGGLE_FLAG_AND_PRINT(debug_mouse, "Debug mouse");
                return false;
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
            // ======================================================== CUSTOM KEYCODES BELOW ========================================================
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
        }
    }
    return true;
}
void set_layer_color(int layer) {
    if (layer == 0) { return; }
    for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
        HSV hsv = {
            .h = pgm_read_byte(&ledmap[layer][i][0]),
            .s = pgm_read_byte(&ledmap[layer][i][1]),
            .v = pgm_read_byte(&ledmap[layer][i][2]),
        };
        if (hsv.h || hsv.s || hsv.v) {
            RGB rgb = hsv_to_rgb(hsv);
            float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
            rgb_matrix_set_color(i, f * rgb.r, f * rgb.g, f * rgb.b);
        } else if (layer != 1) {
            // Only deactivate non-defined key LEDs at layers other than FN. Because at FN we have RGB adjustments and need to see them live.
            // If the values are all false then it's a transparent key and deactivate LED at this layer
            rgb_matrix_set_color(i, 0, 0, 0);
        }
    }
}

void rgb_matrix_indicators_user(void) {
    if (g_suspend_state || disable_layer_color ||
        rgb_matrix_get_flags() == LED_FLAG_NONE ||
        rgb_matrix_get_flags() == LED_FLAG_UNDERGLOW) {
            return;
        }
    //Escape Key:RED
    rgb_matrix_set_color(0, 255, 0, 0); 
    //WASD GREEN
    rgb_matrix_set_color(17, 0, 255, 0);
    rgb_matrix_set_color(31, 0, 255, 0);
    rgb_matrix_set_color(32, 0, 255, 0);
    rgb_matrix_set_color(33, 0, 255, 0);
    //ARROWS GREEN
    rgb_matrix_set_color(56, 0, 255, 0);  
    rgb_matrix_set_color(64, 0, 255, 0);  
    rgb_matrix_set_color(65, 0, 255, 0);  
    rgb_matrix_set_color(66, 0, 255, 0); 
    set_layer_color(get_highest_layer(layer_state));
}
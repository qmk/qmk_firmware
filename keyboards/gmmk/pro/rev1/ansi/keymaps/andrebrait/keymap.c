/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>
   Copyright 2022 Andre Brait <andrebrait@gmail.com>

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

enum layers { WIN_BASE = 0, WIN_FN, MAC_BASE, MAC_FN };

enum custom_keycodes {
    CMDQ_TOG = QK_KB_2 // TECH DEBT: Starts at QK_KB_2 to maintain ordering with VIA definitions. See #19884. Revert to QK_KB_0 when VIA catches up with QMK.
};

#define KC_TASK LWIN(KC_TAB) // Open Task Manager
#define KC_FLXP LWIN(KC_E)   // Open File Explorer
#define DF_WINB DF(WIN_BASE) // Switch to WIN_BASE layer
#define MO_WINF MO(WIN_FN)   // Toggle to WIN_FN layer
#define DF_MACB DF(MAC_BASE) // Switch to MAX_BASE layer
#define MO_MACF MO(MAC_FN)   // Toggle to MAC_FN layer

// clang-format off
uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// The GMMK Pro default layout is:
//
//      ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	     Del          Rotary(Play/Pause)
//      ~        1        2        3        4        5        6        7        8        9        0         -       (=)	     BackSpc           Home
//      Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]        \                 PgUp
//      Caps     A        S        D        F        G        H        J        K        L        ;        "                 Enter             PgDn
//      Sh_L              Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       End
//      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right


    // The FN key by default maps to a momentary toggle to layer 1 to provide access to the QK_BOOT key (to put the board into bootloader mode). Without
    // this mapping, you have to open the case to hit the button on the bottom of the PCB (near the USB cable attachment) while plugging in the USB
    // cable to get the board into bootloader mode - definitely not fun when you're working on your QMK builds. Remove this and put it back to KC_RGUI
    // if that's your preference.
    //
    // To put the keyboard in bootloader mode, use FN+backslash. If you accidentally put it into bootloader, you can just unplug the USB cable and
    // it'll be back to normal when you plug it back in.
    //
    // This keyboard defaults to 6KRO instead of NKRO for compatibility reasons (some KVMs and BIOSes are incompatible with NKRO).
    // Since this is, among other things, a "gaming" keyboard, a key combination to enable NKRO on the fly is provided for convenience.
    // Press Fn+N to toggle between 6KRO and NKRO. This setting is persisted to the EEPROM and thus persists between restarts.
    //
    // RGB and function keys are inspired by the Keychron Q1 layouts instead of using the default keys.
    // To clean the EEPROM, hold the ESC key while connecting the keyboard.

    [WIN_BASE] = LAYOUT(
        KC_ESC,  KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR,          KC_MUTE,
        KC_GRV,  KC_1,     KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_INS,
        KC_TAB,  KC_Q,     KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_DEL,
        KC_CAPS, KC_A,     KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_HOME,
        KC_LSFT,           KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LWIN,  KC_LALT,                            KC_SPC,                             KC_RALT, MO_WINF, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [WIN_FN] = LAYOUT(
        EE_CLR,  KC_BRID,  KC_BRIU, KC_TASK, KC_FLXP, RGB_VAD, RGB_VAI, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, XXXXXXX,          XXXXXXX,
        XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          KC_PAUS,
        RGB_TOG, RGB_MOD,  RGB_HUI, RGB_SAI, RGB_SPI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,          KC_SCRL,
        DF_MACB, RGB_RMOD, RGB_HUD, RGB_SAD, RGB_SPD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,          KC_PGUP,
        XXXXXXX,           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, NK_TOGG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, KC_PGDN,
        XXXXXXX, XXXXXXX,  XXXXXXX,                            XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),

    [MAC_BASE] = LAYOUT(
        KC_ESC,  KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR,          KC_MUTE,
        KC_GRV,  KC_1,     KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_INS,
        KC_TAB,  KC_Q,     KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_DEL,
        KC_CAPS, KC_A,     KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_HOME,
        KC_LSFT,           KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LOPT,  KC_LCMD,                            KC_SPC,                             KC_RCMD, MO_MACF, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [MAC_FN] = LAYOUT(
        EE_CLR,  KC_BRID,  KC_BRIU, KC_MCTL, KC_LPAD, RGB_VAD, RGB_VAI, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, XXXXXXX,          XXXXXXX,
        XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          KC_BRMU,
        RGB_TOG, RGB_MOD,  RGB_HUI, RGB_SAI, RGB_SPI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,          KC_BRMD,
        DF_WINB, RGB_RMOD, RGB_HUD, RGB_SAD, RGB_SPD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,          KC_PGUP,
        XXXXXXX,           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, NK_TOGG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, KC_PGDN,
        XXXXXXX, XXXXXXX,  CMDQ_TOG,                           XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    )
};
// clang-format on

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [WIN_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [WIN_FN]   = {ENCODER_CCW_CW(XXXXXXX, XXXXXXX)},
    [MAC_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [MAC_FN]   = {ENCODER_CCW_CW(XXXXXXX, XXXXXXX)},
};
#endif

/* To record user preferences */
typedef union {
    uint32_t raw; // set to 32-bit of size
    struct {
        bool rgb_enabled : 1;         // Artificial RGB ON/OFF flag (1 bit)
        bool cmd_q_delay_enabled : 1; // Toggle CMD+Q delay (1 bit)
    };
} user_config_t;
user_config_t user_config;

/* Delayed keypresses variables and functions */
static fast_timer_t delayed_press_delay        = 0;
static uint16_t     delayed_press_keycode      = KC_NO;
static fast_timer_t delayed_press_start_time   = 0;
static uint16_t     delayed_press_sent_keycode = KC_NO;
static void         start_delayed_press(fast_timer_t delay, uint16_t keycode);
static void         mark_delayed_press_sent(void);
static void         mark_delayed_release_sent(void);
static void         cancel_delayed_press(void);

#define IS_ANY_DELAYED_PRESS_PENDING() (delayed_press_start_time > 0 && delayed_press_keycode != KC_NO)
#define IS_DELAYED_PRESS_PENDING(keycode) (delayed_press_start_time > 0 && delayed_press_keycode == (keycode))
#define IS_DELAYED_PRESS_SENT(keycode) (delayed_press_sent_keycode != KC_NO && delayed_press_sent_keycode == (keycode))

/* CMD+Q delay */
#ifndef CMD_Q_DELAY
#    define CMD_Q_DELAY 1000
#endif
#if CMD_Q_DELAY <= 0 || CMD_Q_DELAY >= UINT16_MAX / 2
#    error "CMD_Q_DELAY must be a positive integer smaller than UINT16_MAX / 2"
#endif

#ifdef RGB_MATRIX_ENABLE

#    define CAPS_LOCK_COLOR RGB_RED
#    define WIN_BASE_COLOR RGB_BLUE
#    define WIN_FN_COLOR RGB_BLUE
#    define MAC_BASE_COLOR RGB_WHITE
#    define MAC_FN_COLOR RGB_WHITE
#    define UNKNOWN_LAYER_COLOR RGB_PINK

/* The maximum effects duration */
#    ifndef EFFECTS_DURATION
#        define EFFECTS_DURATION 2000
#    endif
#    if EFFECTS_DURATION <= 0 || EFFECTS_DURATION >= UINT16_MAX / 2
#        error "EFFECTS_DURATION must be a positive integer smaller than UINT16_MAX / 2"
#    endif
/* The interval for the flashing effect */
#    ifndef FLASHING_EFFECT_INTERVAL
#        define FLASHING_EFFECT_INTERVAL 250
#    endif
#    if FLASHING_EFFECT_INTERVAL <= 0 || FLASHING_EFFECT_INTERVAL >= UINT16_MAX / 2
#        error "FLASHING_EFFECT_INTERVAL must be a positive integer smaller than UINT16_MAX / 2"
#    endif

static void set_rgb_layer_winfn(void);
static void set_rgb_layer_macfn(void);

/* Effects functions */
static float flashing_effect(fast_timer_t delta_time);
static float static_effect(fast_timer_t delta_time);
static float increasing_effect(fast_timer_t delta_time);

/* Effect variables and functions */
static fast_timer_t effect_started_time = 0;
static fast_timer_t effect_max_duration = EFFECTS_DURATION;
static uint8_t      effect_r = 0x0, effect_g = 0x0, effect_b = 0x0;
static float (*effect_multiplier)(fast_timer_t) = static_effect;
static void start_effects(fast_timer_t max_duration, uint8_t r_color, uint8_t g_color, uint8_t b_color, float (*multiplier)(fast_timer_t));
static void stop_effects(void);

/* Delayed keypresses variables with RGB variant */
static void start_delayed_press_with_effects(fast_timer_t delay, uint16_t keycode, uint8_t r_color, uint8_t g_color, uint8_t b_color);

#endif // RGB_MATRIX_ENABLE

void eeconfig_init_user(void) { // EEPROM is getting reset!
    user_config.raw                 = 0;
    user_config.rgb_enabled         = true; // We want this enabled by default
    user_config.cmd_q_delay_enabled = true; // We want this enabled by default
    eeconfig_update_user(user_config.raw);  // Write default value to EEPROM now
}

void keyboard_post_init_user(void) {
#ifdef RGB_MATRIX_ENABLE
    // Enable the RGB matrix, if not enabled
    if (!rgb_matrix_is_enabled()) {
        rgb_matrix_enable();
    }
    // Set the flags to ALL, if not already set
    if (rgb_matrix_get_flags() != LED_FLAG_ALL) {
        rgb_matrix_set_flags(LED_FLAG_ALL);
    }
#endif

    // Read the user config from EEPROM
    user_config.raw = eeconfig_read_user();
}

void matrix_scan_user(void) {
    if (IS_ANY_DELAYED_PRESS_PENDING()) {
        if (timer_elapsed_fast(delayed_press_start_time) > delayed_press_delay) {
            register_code(delayed_press_keycode);
            mark_delayed_press_sent();
        }
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (IS_DELAYED_PRESS_SENT(keycode)) {
        if (!record->event.pressed) {
            /* Send key-up event and clear the keycode and stop processing */
            unregister_code(keycode);
            mark_delayed_release_sent();
            return false;
        }
    } else if (IS_DELAYED_PRESS_PENDING(keycode)) {
        if (!record->event.pressed) {
            /* Cancel the pending press and stop processing */
            cancel_delayed_press();
            return false;
        }
    } else if (IS_ANY_DELAYED_PRESS_PENDING()) {
        /* Cancel the pending press and resume processing */
        cancel_delayed_press();
    }
    switch (keycode) {
        case QK_DEF_LAYER ... QK_DEF_LAYER_MAX:
            if (record->event.pressed) {
                /* Set the default layout on the EEPROM, let the default layer change callback handle the rest */
                set_single_persistent_default_layer(QK_DEF_LAYER_GET_LAYER(keycode));
            }
            return false;
        case CMDQ_TOG:
            if (record->event.pressed) {
#ifdef RGB_MATRIX_ENABLE
                if (user_config.cmd_q_delay_enabled) {
                    /* Turning delay OFF */
                    start_effects(EFFECTS_DURATION, RGB_RED, flashing_effect);
                } else {
                    /* Turning delay ON */
                    start_effects(EFFECTS_DURATION, RGB_GREEN, flashing_effect);
                }
#endif
                user_config.cmd_q_delay_enabled = !user_config.cmd_q_delay_enabled;
                eeconfig_update_user(user_config.raw);
            }
            return false;
        case KC_Q:
            if (user_config.cmd_q_delay_enabled) {
                if (layer_state_is(MAC_BASE)) {
                    uint8_t mods = get_mods();
                    if (mods == MOD_BIT(KC_LCMD) || mods == MOD_BIT(KC_RCMD)) {
                        if (record->event.pressed) {
#ifdef RGB_MATRIX_ENABLE
                            start_delayed_press_with_effects(CMD_Q_DELAY, KC_Q, RGB_ORANGE);
#else
                            start_delayed_press(CMD_Q_DELAY, KC_Q);
#endif
                        }
                        return false;
                    }
                }
            }
            break;
#ifdef RGB_MATRIX_ENABLE
#    ifdef NKRO_ENABLE
        case NK_TOGG:
            if (record->event.pressed) {
                if (keymap_config.nkro) {
                    /* Turning NKRO OFF */
                    start_effects(EFFECTS_DURATION, RGB_RED, flashing_effect);
                } else {
                    /* Turning NKRO ON */
                    start_effects(EFFECTS_DURATION, RGB_GREEN, flashing_effect);
                }
            }
            break;
#    endif // NKRO_ENABLE
        case RGB_TOG:
            if (record->event.pressed) {
                user_config.rgb_enabled = !user_config.rgb_enabled;
                eeconfig_update_user(user_config.raw);
            }
            return false;
        case RGB_MODE_FORWARD ... RGB_MODE_TWINKLE:
            if (!user_config.rgb_enabled) {
                /* Ignore changes to RGB settings while only it's supposed to be OFF */
                return false; // Skip all further processing of this key
            }
            break;
#endif // RGB_MATRIX_ENABLE
    }
    return true;
}

static void start_delayed_press(fast_timer_t delay, uint16_t keycode) {
    delayed_press_delay        = delay;
    delayed_press_keycode      = keycode;
    delayed_press_start_time   = timer_read_fast();
    delayed_press_sent_keycode = KC_NO;
}

static void mark_delayed_press_sent(void) {
    delayed_press_sent_keycode = delayed_press_keycode;
    cancel_delayed_press();
}

static void mark_delayed_release_sent(void) {
    delayed_press_sent_keycode = KC_NO;
}

static void cancel_delayed_press(void) {
    delayed_press_delay      = 0;
    delayed_press_keycode    = KC_NO;
    delayed_press_start_time = 0;
#ifdef RGB_MATRIX_ENABLE
    stop_effects();
#endif
}

#ifdef RGB_MATRIX_ENABLE

static void start_delayed_press_with_effects(fast_timer_t delay, uint16_t keycode, uint8_t r_color, uint8_t g_color, uint8_t b_color) {
    start_delayed_press(delay, keycode);
    start_effects(delay, r_color, g_color, b_color, increasing_effect);
}

/*
Effects when switching layers
*/

static uint8_t previous_layer = UINT8_MAX;

layer_state_t default_layer_state_set_user(layer_state_t state) {
    uint8_t current_layer = get_highest_layer(state);
    if (previous_layer != current_layer) {
        // For some reason, setting the default layer alone doesn't change it fully
        layer_move(current_layer);
        switch (current_layer) {
            case WIN_BASE:
                start_effects(EFFECTS_DURATION, WIN_BASE_COLOR, flashing_effect);
                break;
            case MAC_BASE:
                start_effects(EFFECTS_DURATION, MAC_BASE_COLOR, flashing_effect);
                break;
            default:
                // This should not ever happen, but let's display something if it does!
                start_effects(EFFECTS_DURATION, UNKNOWN_LAYER_COLOR, static_effect);
                break;
        }
        previous_layer = current_layer;
    }
    return state;
}

static void start_effects(fast_timer_t max_duration, uint8_t r_color, uint8_t g_color, uint8_t b_color, float (*multiplier)(fast_timer_t)) {
    effect_r            = r_color;
    effect_g            = g_color;
    effect_b            = b_color;
    effect_multiplier   = multiplier;
    effect_max_duration = max_duration;
    effect_started_time = timer_read_fast();
}

static void stop_effects(void) {
    effect_r            = 0x0;
    effect_g            = 0x0;
    effect_b            = 0x0;
    effect_multiplier   = static_effect;
    effect_max_duration = EFFECTS_DURATION;
    effect_started_time = 0;
}

static float flashing_effect(fast_timer_t delta_time) {
    return ((delta_time / FLASHING_EFFECT_INTERVAL) + 1) & 0x01;
}

static float static_effect(fast_timer_t delta_time) {
    return 1.0;
}

static float increasing_effect(fast_timer_t delta_time) {
    return ((float)delta_time) / effect_max_duration;
}

bool rgb_matrix_indicators_user(void) {
    if (effect_started_time > 0) {
        fast_timer_t delta_time = timer_elapsed_fast(effect_started_time);
        if (delta_time <= effect_max_duration) {
            /* Render effect */
            float   multiplier = effect_multiplier(delta_time);
            uint8_t val_r      = multiplier * effect_r;
            uint8_t val_g      = multiplier * effect_g;
            uint8_t val_b      = multiplier * effect_b;
            rgb_matrix_set_color_all(val_r, val_g, val_b);
            return false;
        } else {
            /* Effect duration is finished */
            stop_effects();
        }
    }
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color_all(CAPS_LOCK_COLOR);
    } else if (!user_config.rgb_enabled) {
        rgb_matrix_set_color_all(RGB_OFF);
    }
    switch (get_highest_layer(layer_state)) {
        case WIN_BASE:
        case MAC_BASE:
            break;
        case WIN_FN:
            set_rgb_layer_winfn();
            return false;
        case MAC_FN:
            set_rgb_layer_macfn();
            return false;
        default:
            // This should never happen, but if it does, let's display something!
            rgb_matrix_set_color_all(UNKNOWN_LAYER_COLOR);
            return false;
    }
    return true;
}

// RGB led number layout, function of the key

//  67, led 01   0, ESC    6, F1      12, F2      18, F3   23, F4   28, F5      34, F6   39, F7   44, F8      50, F9   56, F10   61, F11    66, F12    69, Prt       Rotary(Mute)   68, led 12
//  70, led 02   1, ~      7, 1       13, 2       19, 3    24, 4    29, 5       35, 6    40, 7    45, 8       51, 9    57, 0     62, -_     78, (=+)   85, BackSpc   72, Home       71, led 13
//  73, led 03   2, Tab    8, Q       14, W       20. E    25, R    30, T       36, Y    41, U    46, I       52, O    58, P     63, [{     89, ]}     93, \|        75, PgUp       74, led 14
//  76, led 04   3, Caps   9, A       15, S       21, D    26, F    31, G       37, H    42, J    47, K       53, L    59, ;:    64, '"                96, Enter     86, PgDn       77, led 15
//  80, led 05   4, Sh_L   10, Z      16, X       22, C    27, V    32, B       38, N    43, M    48, ,<      54, .<   60, /?               90, Sh_R   94, Up        82, End        81, led 16
//  83, led 06   5, Ct_L   11,Win_L   17, Alt_L                     33, SPACE                     49, Alt_R   55, FN             65, Ct_R   95, Left   97, Down      79, Right      84, led 17
//  87, led 07                                                                                                                                                                      88, led 18
//  91, led 08                                                                                                                                                                      92, led 19

static void set_rgb_layer_winfn(void) {
    rgb_matrix_set_color(0, WIN_FN_COLOR);
    rgb_matrix_set_color(6, WIN_FN_COLOR);
    rgb_matrix_set_color(12, WIN_FN_COLOR);
    rgb_matrix_set_color(18, WIN_FN_COLOR);
    rgb_matrix_set_color(23, WIN_FN_COLOR);
    rgb_matrix_set_color(28, WIN_FN_COLOR);
    rgb_matrix_set_color(34, WIN_FN_COLOR);
    rgb_matrix_set_color(39, WIN_FN_COLOR);
    rgb_matrix_set_color(44, WIN_FN_COLOR);
    rgb_matrix_set_color(50, WIN_FN_COLOR);
    rgb_matrix_set_color(56, WIN_FN_COLOR);
    rgb_matrix_set_color(61, WIN_FN_COLOR);
    rgb_matrix_set_color(66, WIN_FN_COLOR);
    rgb_matrix_set_color(2, WIN_FN_COLOR);
    rgb_matrix_set_color(3, WIN_FN_COLOR);
    rgb_matrix_set_color(8, WIN_FN_COLOR);
    rgb_matrix_set_color(9, WIN_FN_COLOR);
    rgb_matrix_set_color(14, WIN_FN_COLOR);
    rgb_matrix_set_color(15, WIN_FN_COLOR);
    rgb_matrix_set_color(20, WIN_FN_COLOR);
    rgb_matrix_set_color(21, WIN_FN_COLOR);
    rgb_matrix_set_color(25, WIN_FN_COLOR);
    rgb_matrix_set_color(26, WIN_FN_COLOR);
    rgb_matrix_set_color(38, WIN_FN_COLOR);
    rgb_matrix_set_color(93, WIN_FN_COLOR);
    rgb_matrix_set_color(72, WIN_FN_COLOR);
    rgb_matrix_set_color(75, WIN_FN_COLOR);
    rgb_matrix_set_color(86, WIN_FN_COLOR);
    rgb_matrix_set_color(82, WIN_FN_COLOR);
}

static void set_rgb_layer_macfn(void) {
    rgb_matrix_set_color(0, MAC_FN_COLOR);
    rgb_matrix_set_color(6, MAC_FN_COLOR);
    rgb_matrix_set_color(12, MAC_FN_COLOR);
    rgb_matrix_set_color(18, MAC_FN_COLOR);
    rgb_matrix_set_color(23, MAC_FN_COLOR);
    rgb_matrix_set_color(28, MAC_FN_COLOR);
    rgb_matrix_set_color(34, MAC_FN_COLOR);
    rgb_matrix_set_color(39, MAC_FN_COLOR);
    rgb_matrix_set_color(44, MAC_FN_COLOR);
    rgb_matrix_set_color(50, MAC_FN_COLOR);
    rgb_matrix_set_color(56, MAC_FN_COLOR);
    rgb_matrix_set_color(61, MAC_FN_COLOR);
    rgb_matrix_set_color(66, MAC_FN_COLOR);
    rgb_matrix_set_color(2, MAC_FN_COLOR);
    rgb_matrix_set_color(3, MAC_FN_COLOR);
    rgb_matrix_set_color(8, MAC_FN_COLOR);
    rgb_matrix_set_color(9, MAC_FN_COLOR);
    rgb_matrix_set_color(14, MAC_FN_COLOR);
    rgb_matrix_set_color(15, MAC_FN_COLOR);
    rgb_matrix_set_color(20, MAC_FN_COLOR);
    rgb_matrix_set_color(21, MAC_FN_COLOR);
    rgb_matrix_set_color(25, MAC_FN_COLOR);
    rgb_matrix_set_color(26, MAC_FN_COLOR);
    rgb_matrix_set_color(38, MAC_FN_COLOR);
    rgb_matrix_set_color(93, MAC_FN_COLOR);
    rgb_matrix_set_color(72, MAC_FN_COLOR);
    rgb_matrix_set_color(75, MAC_FN_COLOR);
    rgb_matrix_set_color(86, MAC_FN_COLOR);
    rgb_matrix_set_color(82, MAC_FN_COLOR);
    rgb_matrix_set_color(17, MAC_FN_COLOR);
}

#endif // RGB_MATRIX_ENABLE

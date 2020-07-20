#include QMK_KEYBOARD_H
#include "taphold.h"
#include "seq.h"
#include "ds1307.h"
#include "lightmode.h"
#include <stdio.h>

/* Note: don't forget there's some more code in qmk_firmware/users/anderson dir */

#define _MAIN 0
#define _ALPHA 1
#define _BETA 2

enum custom_keycodes {
    KC_MAIN = SAFE_RANGE,
    KC_ALPHA,
    KC_BETA,
#ifdef LIGHTMODE_ENABLE
    KC_LIGHT_MODE,
#endif
    KC_SEQ,
    KC_SET_TIME,
};
#ifdef LIGHTMODE_ENABLE
#endif

/* TapHold is my own implementation of the `LT` macro. It's processed in `process_record_user()`. */
#define TAPHOLD_CONFIG_SIZE 3
taphold_t taphold_config[TAPHOLD_CONFIG_SIZE] = {
    {.key=KC_ALPHA, .mode=TAPHOLD_LAYER, .shortAction=KC_ESC, .longAction=_ALPHA},
    {.key=KC_BETA, .mode=TAPHOLD_LAYER, .shortAction=KC_EQL, .longAction=_BETA},
    {.key=KC_RCTRL, .mode=TAPHOLD_MOD, .shortAction=KC_MINS, .longAction=KC_LCTRL},
};
uint16_t taphold_config_size = TAPHOLD_CONFIG_SIZE;
uint32_t taphold_timeout = 90;

/* Seq is implementation of unicode macros similar to UCIS, but with unicode strings. */
#define SEQ_CONFIG_SIZE 3
seq_t seq_config[SEQ_CONFIG_SIZE] = {
    {.sequence="temp", .result="42°C"},
    {.sequence="table", .result="┳━━┳"},
    {.sequence="shrug", .result="¯\\_(ツ)_/¯"}
};
uint16_t seq_config_size = SEQ_CONFIG_SIZE;

/* Colors */
uint32_t layer_colors[3] = {
    [_MAIN] = 0xFF0010,
    [_ALPHA] = 0x4020FF,
    [_BETA] = 0x20FF00,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Main layer
                                                       │MUTE │           │L_MOD│
       ┏━━━━━┳━━━━━┯━━━━━┯━━━━━┯━━━━━┯━━━━━┳━━━━━┯━━━━━┯━━━━━┯━━━━━┯━━━━━┳━━━━━┓
       ┃ TAB ┃  Q  │  W  │  E  │  R  │  T  ┃  Y  │  U  │  I  │  O  │  P  ┃ BSP ┃
       ┣━━━━━╉─────┼─────┼─────┼─────┼─────╂─────┼─────┼─────┼─────┼─────╊━━━━━┫
       ┃𝛼/ESC┃  A  │  S  │  D  │  F  │  G  ┃  H  │  J  │  K  │  L  │  ;  ┃ RET ┃
       ┣━━━━━╉─────┼─────┼─────┼─────┼─────╂─────┼─────┼─────┼─────┼─────╊━━━━━┫
       ┃SHIFT┃  Z  │  X  │  C  │  V  │  B  ┃  N  │  M  │  ,  │  .  │  /  ┃CTL/-┃
       ┣━━━━━╉─────┼─────┼─────┼─────┼─────╂─────┼─────┼─────┼─────┼─────╊━━━━━┫
       ┃LCTRL┃     │     │ ALT │ GUI │SPACE┃SPACE│ 𝛽/= │  '  │     │     ┃  \  ┃
       ┗━━━━━┻━━━━━┷━━━━━┷━━━━━┷━━━━━┷━━━━━┻━━━━━┷━━━━━┷━━━━━┷━━━━━┷━━━━━┻━━━━━┛
       */
    [_MAIN] = LAYOUT( \
                                                                                KC_MUTE,                   LCTL(KC_D),
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
        KC_ALPHA,KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,  \
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RCTRL,\
        KC_LCTRL,_______, _______, KC_LALT, KC_LGUI, KC_SPC,  KC_SPC,  KC_BETA, KC_QUOT, _______, _______, KC_BSLS  \
    ),

    /* Alpha layer (𝛼)
                                                       │     │           │     │
       ┏━━━━━┳━━━━━┯━━━━━┯━━━━━┯━━━━━┯━━━━━┳━━━━━┯━━━━━┯━━━━━┯━━━━━┯━━━━━┳━━━━━┓
       ┃     ┃PREV │PLAY │NEXT │     │NUMLK┃  -  │ ^^^ │  ^  │ vvv │  ~  ┃ DEL ┃
       ┣━━━━━╉─────┼─────┼─────┼─────┼─────╂─────┼─────┼─────┼─────┼─────╊━━━━━┫
       ┃     ┃     │VOL -│VOL +│     │CPSLK┃HOME │ <-- │  v  │ --> │  `  ┃  \  ┃
       ┣━━━━━╉─────┼─────┼─────┼─────┼─────╂─────┼─────┼─────┼─────┼─────╊━━━━━┫
       ┃     ┃     │     │     │     │SCRLK┃ END │  =  │  [  │  ]  │  (  ┃  )  ┃
       ┣━━━━━╉─────┼─────┼─────┼─────┼─────╂─────┼─────┼─────┼─────┼─────╊━━━━━┫
       ┃     ┃     │     │     │     │     ┃     │     │     │     │     ┃     ┃
       ┗━━━━━┻━━━━━┷━━━━━┷━━━━━┷━━━━━┷━━━━━┻━━━━━┷━━━━━┷━━━━━┷━━━━━┷━━━━━┻━━━━━┛
       */
    [_ALPHA] = LAYOUT( \
                                                                                _______,                   _______, \
        _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, KC_NLCK, KC_MINS, KC_PGUP, KC_UP,   KC_PGDN, KC_TILD, KC_DEL,  \
        _______, _______, KC_VOLD, KC_VOLU, _______, KC_CAPS, KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT,KC_GRV,  KC_BSLS, \
        _______, _______, _______, _______, _______, KC_SLCK, KC_END,  KC_EQL,  KC_LBRC, KC_RBRC, KC_LPRN ,KC_RPRN, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
    ),

    /* Beta layer (𝛽)
                                                       │     │           │     │
       ┏━━━━━┳━━━━━┯━━━━━┯━━━━━┯━━━━━┯━━━━━┳━━━━━┯━━━━━┯━━━━━┯━━━━━┯━━━━━┳━━━━━┓
       ┃ RGB ┃  1  │  2  │  3  │  4  │  5  ┃  6  │  7  │  8  │  9  │  0  ┃ F12 ┃
       ┣━━━━━╉─────┼─────┼─────┼─────┼─────╂─────┼─────┼─────┼─────┼─────╊━━━━━┫
       ┃L_MOD┃ F1  │ F2  │ F3  │ F4  │ F5  ┃ F6  │ F7  │ F8  │ F9  │ F10 ┃ F11 ┃
       ┣━━━━━╉─────┼─────┼─────┼─────┼─────╂─────┼─────┼─────┼─────┼─────╊━━━━━┫
       ┃     ┃RESET│DEBUG│     │     │TIME ┃SLEEP│ SEQ │  {  │  }  │PTSCR┃     ┃
       ┣━━━━━╉─────┼─────┼─────┼─────┼─────╂─────┼─────┼─────┼─────┼─────╊━━━━━┫
       ┃     ┃     │     │     │     │     ┃     │     │     │     │     ┃     ┃
       ┗━━━━━┻━━━━━┷━━━━━┷━━━━━┷━━━━━┷━━━━━┻━━━━━┷━━━━━┷━━━━━┷━━━━━┷━━━━━┻━━━━━┛
       */
    [_BETA] = LAYOUT( \
                                                                                _______,                   _______, \
        RGB_TOG, KC_1,  KC_2,    KC_3,   KC_4,    KC_5,     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_F12,
#ifdef LIGHTMODE_ENABLE
        KC_LIGHT_MODE,
#else
        _______,
#endif
                 KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  \
        _______, RESET,   DEBUG,   _______, _______, KC_SET_TIME,KC_SLEP,KC_SEQ,KC_LCBR, KC_RCBR, KC_PSCR, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
    )
};

static bool alpha_pressed = false;
static bool beta_pressed = false;

static bool ctrl_pressed = false;
static bool alt_pressed = false;
static bool shift_pressed = false;
static bool gui_pressed = false;

static bool is_in_seq = false;

void keyboard_post_init_user(void) {
    /* debug_enable = true; */
    /* debug_matrix = true; */
}

void eeconfig_init_user(void) {
    set_unicode_input_mode(UC_LNX);
}

void matrix_init_user(void) {
#ifdef LIGHTMODE_ENABLE
    set_light_mode(SMOOTHLED, layer_colors[_MAIN]);
#endif
}

static uint32_t last_update = 0;
static uint8_t hours, minutes, seconds;

void matrix_scan_user(void) {
    uint32_t now = timer_read32();
    if (now - last_update > 500) {
        ds1307_get_time(&hours, &minutes, &seconds);
        last_update = now;
    }
}

static bool is_in_set_time = false;
static char new_time[6];
static uint8_t new_time_index = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == KC_SEQ && record->event.pressed) {
        seq_start();
        layer_off(_BETA);
        is_in_seq = true;
        return false;
    } else if (is_in_seq) {
        if (record->event.pressed) {
            if (!seq_feed(keycode)) {
                is_in_seq = false;
            }
        }
        return false;
    }
    if (keycode == KC_SET_TIME && record->event.pressed) {
        is_in_set_time = true;
        new_time_index = 0;
    } else if (is_in_set_time) {
        if (!record->event.pressed && keycode >= KC_1 && keycode <= KC_0) {
            new_time[new_time_index++] = (keycode == KC_0) ? 0 : keycode - KC_1 + 1;
            if (new_time_index == 6) {
                is_in_set_time = false;
                ds1307_set_time(
                        (new_time[0]) * 10 + (new_time[1]),
                        (new_time[2]) * 10 + (new_time[3]),
                        (new_time[4]) * 10 + (new_time[5])
                );
                for (int i = 0; i < 6; i++) {
                    tap_code(KC_BSPACE);
                }
            }
        }
    }

    if (keycode == KC_LCTRL || keycode == KC_RCTRL) {
        ctrl_pressed = record->event.pressed;
    } else if (keycode == KC_LALT) {
        alt_pressed = record->event.pressed;
    } else if (keycode == KC_LSFT) {
        shift_pressed = record->event.pressed;
    } else if (keycode == KC_LGUI) {
        gui_pressed = record->event.pressed;
    } else if (keycode == KC_ALPHA) {
        alpha_pressed = record->event.pressed;
    } else if (keycode == KC_BETA) {
        beta_pressed = record->event.pressed;
    }

    if (keycode == RESET) {
        rgblight_setrgb(255, 255, 0);
    }
#ifdef LIGHTMODE_ENABLE
    if (record->event.pressed && keycode == KC_LIGHT_MODE) {
        next_light_mode(layer_colors[_MAIN]);
    }
#endif
    if (keycode == KC_LCTRL) {
        /* Some Overlay1_Enable fuckery! */
        (record->event.pressed ? register_code : unregister_code)(KC_LCTRL);
        return false;
    }
    return taphold_process(keycode, record);
}

layer_state_t layer_state_set_user(layer_state_t state) {
#ifdef LIGHTMODE_ENABLE
    uint8_t layer = get_highest_layer(state);
    update_light_mode(layer_colors[layer]);
#endif
    return state;
}

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (!alpha_pressed) {
            tap_code(clockwise ? KC_VOLD : KC_VOLU);
        } else {
            tap_code(clockwise ? KC_MPRV : KC_MNXT);
        }
    } else if (index == 1) {
        if (!alpha_pressed) {
            tap_code(clockwise ? KC_UP : KC_DOWN);
        } else {
            tap_code(clockwise ? KC_PGUP : KC_PGDN);
        }
    }
}

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_0;
}

void oled_task_user(void) {
    /* Host Keyboard Layer Status */
    uint8_t current_layer = get_highest_layer(layer_state);

    /* Layer */
    static const char PROGMEM icons[4][3][6] = {
        {
            { 0x80, 0x81, 0x82, 0x83, 0x84, 0 },
            { 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0 },
            { 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0 }
        },
        {
            { 0x85, 0x86, 0x87, 0x88, 0x89, 0 },
            { 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0 },
            { 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0 }
        },
        {
            { 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0 },
            { 0xaa, 0xab, 0xac, 0xad, 0xae, 0 },
            { 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0 }
        },
        {
            { 0x8f, 0x90, 0x91, 0x92, 0x93, 0 },
            { 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0 },
            { 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0 }
        }
    };

    uint8_t icon_index = current_layer == _MAIN ? 3 : current_layer == _ALPHA ? 1 : 2;
    for (int i = 0; i < 3; i++) {
        oled_set_cursor(0, i + 1);
        oled_write_P(icons[icon_index][i], false);
    }

    /* Time */
    oled_set_cursor(6, 0);
    // oled_write_P(PSTR("-D48 Custom-\n"), false);
    char buf[16];
    sprintf(
            buf,
            "%02d:%02d:%02d", hours, minutes, seconds
    );
    oled_write(buf, false);

    /* Modifiers */
    static const char PROGMEM mods[][2] = {
        {0x94, 0x95}, // CTL
        {0x96, 0x97}, // ALT
        {0x98, 0x99}, // GUI
        {0x9a, 0x9b},  // SFT
        /* {0x9c, 0x9d},  // EMPTY */
    };

    char mod_data[13] = "\x9c\x9d\x9c\x9d\x9c\x9d\x9c\x9d \x07\x07\x07\0";
    if (ctrl_pressed) strncpy(mod_data, mods[0], 2);
    if (alt_pressed) strncpy(mod_data + 2, mods[1], 2);
    if (gui_pressed) strncpy(mod_data + 4, mods[2], 2);
    if (shift_pressed) strncpy(mod_data + 6, mods[3], 2);
    led_t led_usb_state = host_keyboard_led_state();
    if (led_usb_state.num_lock) mod_data[9] = 'N';
    if (led_usb_state.caps_lock) mod_data[10] = 'C';
    if (led_usb_state.scroll_lock) mod_data[11] = 'S';

    oled_set_cursor(6, 1);
    oled_write(mod_data, false);

    /* Matrix */
    static const char PROGMEM matrix_chars[] = {
        0xb4, // None
        0xb5, // Upper
        0xb6, // Lower
        0xb7  // Both
    };

    for (uint8_t row = 1; row < MATRIX_ROWS; row += 2) {
        // Skip first row because it's used by the encoders.
        uint16_t bits1 = matrix_get_row(row);
        uint16_t bits2 = matrix_get_row(row + 1);

        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            uint8_t matrix_char = matrix_chars[((bits1 & (1 << col)) ? 1 : 0) | ((bits2 & (1 << col)) ? 2 : 0)];
            oled_set_cursor(6 + col, 2 + (row - 1) / 2);
            oled_write_char(matrix_char, false);
        }
    }

}
#endif

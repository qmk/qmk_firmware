// Copyright 2022 Guilherme Bermêo (bermeo.dev)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H


// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layers { 
    _QWERTY, 
    _LOWER, 
    _RAISE, 
    _NUMP,
};

uint8_t mod_state;

bool isBarking  = false;
bool isJumping  = false;
bool showedJump = true;
bool isSneaking = false;

enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    LOWER,
    RAISE,
    ADJUST,
    CEDILHA,            // ç direct key
    AO,                 // ã direct key
    ASPAS,              // " direct key

};
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {[_QWERTY] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
    LCTL_T(KC_F3), KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,  KC_GRAVE,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    LALT_T(KC_TAB), KC_A,  KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L,  KC_SCLN, KC_ENTER,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    LSFT_T(KC_LEFT), KC_Z, KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M,   KC_COMM, KC_DOT, KC_SLSH, RGUI_T(KC_RIGHT),
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                      LGUI_T(KC_DOWN), MO(1), KC_SPC,    KC_BSPC,  MO(2),  RSFT_T(KC_UP)
    //                                    `--------------------------'  `--------------------------'
    ),

[_LOWER] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
    LCTL_T(KC_F5), KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                         KC_6, KC_7, KC_8, KC_9, KC_0, KC_ESCAPE,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    LCTL(LGUI(KC_SPC)), KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_ENT,                  KC_LBRC, KC_RBRC, KC_BSLS, KC_QUOT, KC_COLON, KC_ENT,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    LALT(KC_LEFT), KC_F1, KC_F2,    KC_C,    KC_V,   KC_BSPC,                      KC_MINS, KC_EQL,   KC_LT,   KC_GT, KC_QUESTION, LALT(KC_RIGHT),
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                               LGUI_T(KC_PAGE_DOWN), _______, KC_SPC,    LALT(KC_BSPC), TG(3), RSFT_T(KC_PAGE_UP)
    //                                    `--------------------------'  `--------------------------'
    ),

[_RAISE] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
    LCTL_T(KC_F4), KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TILDE,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    LALT_T(KC_TAB), AO,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_LCBR, KC_RCBR, KC_PIPE,  ASPAS,  KC_COLON, KC_ENT,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    LALT(KC_LEFT), XXXXXXX, XXXXXXX, CEDILHA, XXXXXXX, XXXXXXX,                   KC_UNDS, KC_PLUS,  KC_LT,    KC_GT, KC_QUESTION, LALT(KC_RIGHT),
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                       LGUI_T(KC_END), TG(3), KC_SPC,     KC_DEL,  _______, RSFT_T(KC_HOME)
    //                                    `--------------------------'  `--------------------------'
    ),

[_NUMP] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       RGB_TOG,  _______, _______, _______, _______, _______,                      _______,  KC_P7,   KC_P8,  KC_P9,  KC_PAST, KC_PSLS,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        _______, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, _______,                      _______,  KC_P4,   KC_P5,  KC_P6,  KC_PMNS,  KC_ENT,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       _______, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, _______,                       KC_PDOT,  KC_P1,   KC_P2,  KC_P3,  KC_PPLS,   KC_NO,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                             TG(3),    TG(3),   TG(3),     KC_BSPC,  TG(3),   KC_P0
    //                                    `--------------------------'  `--------------------------'
    )};

//Per key lights
void rgb_matrix_indicators_user(void) {
#ifdef RGB_MATRIX_ENABLE
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            isSneaking = false;
            mod_state  = get_mods();
            for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
                if (mod_state & MOD_MASK_SHIFT) {
                    isBarking = true;
                    rgb_matrix_set_color(52, 255, 255, 255);
                    rgb_matrix_set_color(i, 255, 150, 0);
                } else if (mod_state & MOD_MASK_GUI || mod_state & MOD_MASK_CTRL) {
                    isBarking = true;
                    rgb_matrix_set_color(15, 255, 0, 0);
                    switch (i) {
                        case 0 ... 5:                            // underglow left side
                        case 9:                                  // cmd + T white (new tab)
                        case 11:                                 // cmd + F white (find)
                        case 18:                                 // cmd + W white (close tab)
                        case 19:                                 // cmd + S white (save)
                        case 21:                                 // cmd + Z white (undo)
                        case 22:                                 // cmd + A white (select all)
                        case 27 ... 32:                          // underglow right side
                        case 43:                                 // cmd + K white (comment for desktop remote)
                        case 48:                                 // cmd + / white (comment line)
                            rgb_matrix_set_color(i, 255, 255, 255); // white
                            break;
                        case 6:                                  // space bar off
                        case 24 ... 26:                          // left column off
                        case 33:                                 // backspace off
                        case 41:                                 // shift off
                        case 51 ... 53:                          // right column off
                            rgb_matrix_set_color(i, 0, 0, 0);    //off
                            break;
                    }
                    if (mod_state & MOD_MASK_GUI) {
                        rgb_matrix_set_color(12, 255, 255, 255); // white V key
                        rgb_matrix_set_color(15, 255, 255, 255); // white C key
                        rgb_matrix_set_color(20, 255, 255, 255); // white X key
                    } else {
                    }
                } else if (mod_state & MOD_MASK_ALT) {
                    isBarking = true;
                } else {
                    isBarking = false;
                    rgb_matrix_set_color(14, 0, 0, 0);          // command key off
                }
            }
            rgb_matrix_set_color(13, 23, 181, 255);             // cyan layer
            rgb_matrix_set_color(40, 255, 33, 0);               // orange layer
            break;

        case _RAISE:
            isSneaking = true;
            for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
                switch (i) {
                    case 7:                                     // B key off
                    case 8:                                     // G key off
                    case 11:                                    // F key off
                    case 12:                                    // V key off
                    case 16:                                    // D key off
                    case 19 ... 21:                             // S, X, Z keys off
                    case 25:                                    // tab key off
                    case 26:                                    // shift key off
                    case 52 ... 53:                             // right column off
                        rgb_matrix_set_color(i, 0, 0, 0);       // off
                        break;
                    case 15:                                    // Ç key
                    case 22:                                    // Ã key
                    case 24:                                    // Launch (F4)
                    case 40:                                    // Active layer
                        rgb_matrix_set_color(i, 255, 255, 255); // white
                        break;
                    case 13:                                    // active layer
                        rgb_matrix_set_color(i, 0, 255, 0);     // green
                        break;
                    case 42:                                    // , shifted key
                    case 47 ... 49:                             // . / ; shifted keys
                        rgb_matrix_set_color(i, 255, 214, 0);   // yellow
                        break;
                    default:
                        rgb_matrix_set_color(i, 255, 33, 0);    // orange
                }
            }
            break;

        case _LOWER:
            isSneaking = true;
            for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
                switch (i) {
                    case 7:                                     // Delete key
                    case 51:                                    // ESC key
                        rgb_matrix_set_color(i, 255, 0, 0);     // red
                        break;
                    case 12:                                    // V key off
                    case 15:                                    // C key off
                    case 20:                                    // X key off
                    case 21:                                    // Z key off
                    
                    case 26:                                    // shift key off
                    case 52 ... 53:                             // right column off
                        rgb_matrix_set_color(i, 0, 0, 0);       // off
                        break;
                    case 11:                                    // Right arrow key
                    case 13:                                    // Active layer
                    case 16:                                    // Up arrow key
                    case 19:                                    // Down arrow key
                    case 22:                                    // Left arrow key
                    case 24:                                    // Print
                        rgb_matrix_set_color(i, 255, 255, 255); // white
                        break;
                    case 8:                                     // Enter key
                    case 40:                                    // Activate Numpad
                        rgb_matrix_set_color(i, 0, 255, 0);     // green
                        break;
                    case 42:                                    // , shifted key
                    case 47 ... 49:                             // . / ; shifted keys
                    case 25:                                    // opens emoji dialog (on macOS)
                        rgb_matrix_set_color(i, 255, 214, 0);   // yellow
                        break;
                    default:
                        rgb_matrix_set_color(i, 23, 181, 255);  // cyan
                }
            }

            break;

        case _NUMP:
            isSneaking = true;
            for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
                switch (i) {
                    case 12:                                    // RGB speed-
                    case 15:                                    // RGB brigthness-
                    case 20:                                    // RGB saturation-
                    case 21:                                    // RGB hue-
                    case 49:                                    // Numpad -
                    case 51:                                    // Numpad /
                        rgb_matrix_set_color(i, 255, 0, 0);     // red
                        break;
                    case 8 ... 10:                              // G T R off
                    case 17:                                    // E off
                    case 18:                                    // W off
                    case 23:                                    // Q off
                    case 25:                                    // Tab off
                    case 26:                                    // LShift off
                    case 33:                                    // Backspace off
                    case 35:                                    // H off
                    case 36:                                    // Y off
                    case 53:                                    // RShift off
                        rgb_matrix_set_color(i, 0, 0, 0);       // off
                        break;
                    case 6:                                     // Space bar off
                    case 13:                                    // Return to default layer
                    case 16:                                    // RGB brigthness+
                    case 24:                                    // RGB toggle
                    case 37 ... 47:                             // Numpad numbers
                    case 52:                                    // Enter key
                        rgb_matrix_set_color(i, 255, 255, 255); // white
                        break;
                    case 11:                                    // RGB speed+
                    case 19:                                    // RGB saturation+
                    case 22:                                    // RGB hue+
                    case 48:                                    // Numpad +
                        rgb_matrix_set_color(i, 0, 255, 0);     // green
                        break;
                    case 34:                                    // . numpad key
                        rgb_matrix_set_color(i, 255, 214, 0);   // yellow
                        break;
                }
                rgb_matrix_set_color(13, 23, 181, 255);         // Activate cyan layer
                rgb_matrix_set_color(40, 255, 33, 0);           // Activate orange layer
                rgb_matrix_set_color(50, 0, 33, 255);           // Numpad *
                rgb_matrix_set_color(14, 0, 255, 0);            // Green layer active
            }
    }
};
#endif

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

/* KEYBOARD PET START */
/* settings */
#    define MIN_WALK_SPEED 10
#    define MIN_RUN_SPEED 60
/* advanced settings */
#    define ANIM_FRAME_DURATION 100 // how long each frame lasts in ms
#    define ANIM_SIZE 96            // number of bytes in array. If you change sprites, minimize for adequate firmware size. max is 1024
/* timers */
uint32_t anim_timer = 0;
uint32_t anim_sleep = 0;
/* current frame */
uint8_t current_frame = 0;
/* status variables */
int current_wpm = 0;
// led_t led_usb_state;
/* logic */
static void render_luna(int LUNA_X, int LUNA_Y) {
    /* Sit */
    static const char PROGMEM sit[2][ANIM_SIZE] = {/* 'sit1', 32x22px */
        {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1c, 0x02, 0x05, 0x02, 0x24, 0x04, 0x04, 0x02, 0xa9, 0x1e, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x08, 0x68, 0x10, 0x08, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x06, 0x82, 0x7c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x0c, 0x10, 0x10, 0x20, 0x20, 0x20, 0x28, 0x3e, 0x1c, 0x20, 0x20, 0x3e, 0x0f, 0x11, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        },
        /* 'sit2', 32x22px */
        {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1c, 0x02, 0x05, 0x02, 0x24, 0x04, 0x04, 0x02, 0xa9, 0x1e, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x90, 0x08, 0x18, 0x60, 0x10, 0x08, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x0e, 0x82, 0x7c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x0c, 0x10, 0x10, 0x20, 0x20, 0x20, 0x28, 0x3e, 0x1c, 0x20, 0x20, 0x3e, 0x0f, 0x11, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};

    /* Walk */
    static const char PROGMEM walk[2][ANIM_SIZE] = {/* 'walk1', 32x22px */
        {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x10, 0x90, 0x90, 0x90, 0xa0, 0xc0, 0x80, 0x80, 0x80, 0x70, 0x08, 0x14, 0x08, 0x90, 0x10, 0x10, 0x08, 0xa4, 0x78, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x08, 0xfc, 0x01, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x18, 0xea, 0x10, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1c, 0x20, 0x20, 0x3c, 0x0f, 0x11, 0x1f, 0x03, 0x06, 0x18, 0x20, 0x20, 0x3c, 0x0c, 0x12, 0x1e, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        },
        /* 'walk2', 32x22px */
        {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x20, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x28, 0x10, 0x20, 0x20, 0x20, 0x10, 0x48, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x20, 0xf8, 0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x10, 0x30, 0xd5, 0x20, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x20, 0x30, 0x0c, 0x02, 0x05, 0x09, 0x12, 0x1e, 0x02, 0x1c, 0x14, 0x08, 0x10, 0x20, 0x2c, 0x32, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        }};

    /* Run */
    static const char PROGMEM run[2][ANIM_SIZE] = {/* 'run1', 32x22px */
        {
            0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x08, 0x08, 0xc8, 0xb0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x40, 0x40, 0x3c, 0x14, 0x04, 0x08, 0x90, 0x18, 0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0xc4, 0xa4, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc8, 0x58, 0x28, 0x2a, 0x10, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x09, 0x04, 0x04, 0x04, 0x04, 0x02, 0x03, 0x02, 0x01, 0x01, 0x02, 0x02, 0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00,
        },

        /* 'run2', 32x22px */
        {
            0x00, 0x00, 0x00, 0xe0, 0x10, 0x10, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x78, 0x28, 0x08, 0x10, 0x20, 0x30, 0x08, 0x10, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x10, 0xb0, 0x50, 0x55, 0x20, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28, 0x37, 0x02, 0x1e, 0x20, 0x20, 0x18, 0x0c, 0x14, 0x1e, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        }};

    // /* Bark */
    static const char PROGMEM bark[2][ANIM_SIZE] = {/* 'bark1', 32x22px */
        {
            0x00, 0xc0, 0x20, 0x10, 0xd0, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x40, 0x3c, 0x14, 0x04, 0x08, 0x90, 0x18, 0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc8, 0x48, 0x28, 0x2a, 0x10, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28, 0x37, 0x02, 0x02, 0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        },

        /* 'bark2', 32x22px */
        {
            0x00, 0xe0, 0x10, 0x10, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x40, 0x40, 0x2c, 0x14, 0x04, 0x08, 0x90, 0x18, 0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x48, 0x28, 0x2a, 0x10, 0x0f, 0x20, 0x4a, 0x09, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28, 0x37, 0x02, 0x02, 0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        }};

    /* Sneak */
    static const char PROGMEM sneak[2][ANIM_SIZE] = {/* 'sneak1', 32x22px */
            {
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x40, 0x40, 0x80, 0x00, 0x80, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x21, 0xf0, 0x04, 0x02, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x04, 0x04, 0x04, 0x03, 0x01, 0x00, 0x00, 0x09, 0x01, 0x80, 0x80, 0xab, 0x04, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1c, 0x20, 0x20, 0x3c, 0x0f, 0x11, 0x1f, 0x02, 0x06, 0x18, 0x20, 0x20, 0x38, 0x08, 0x10, 0x18, 0x04, 0x04, 0x02, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00,
            },

            /* 'sneak2', 32x22px */
            {
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xa0, 0x20, 0x40, 0x80, 0xc0, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x41, 0xf0, 0x04, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x02, 0x04, 0x04, 0x02, 0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x40, 0x40, 0x55, 0x82, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x20, 0x30, 0x0c, 0x02, 0x05, 0x09, 0x12, 0x1e, 0x04, 0x18, 0x10, 0x08, 0x10, 0x20, 0x28, 0x34, 0x06, 0x02, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
            }};

    /* animation */
    void animate_luna(void) {
        /* jump */
        if (isJumping || !showedJump) {
            /* clear */
            oled_set_cursor(LUNA_X, LUNA_Y + 2);
            oled_write("     ", false);
            oled_set_cursor(LUNA_X, LUNA_Y - 1);
            showedJump = true;
        } else {
            /* clear */
            oled_set_cursor(LUNA_X, LUNA_Y - 1);
            oled_write("     ", false);
            oled_set_cursor(LUNA_X, LUNA_Y);
        }
        /* switch frame */
        current_frame = (current_frame + 1) % 2;
        /* draw */
        if (isBarking) {
            oled_write_raw_P(bark[abs(1 - current_frame)], ANIM_SIZE);

        } else if (isSneaking) {
            oled_write_raw_P(sneak[abs(1 - current_frame)], ANIM_SIZE);

        } else if (current_wpm <= MIN_WALK_SPEED) {
            oled_write_raw_P(sit[abs(1 - current_frame)], ANIM_SIZE);

        } else if (current_wpm <= MIN_RUN_SPEED) {
            oled_write_raw_P(walk[abs(1 - current_frame)], ANIM_SIZE);

        } else {
            oled_write_raw_P(run[abs(1 - current_frame)], ANIM_SIZE);
        }
    }
    /* animation timer */
    if (timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
        anim_timer = timer_read32();
        animate_luna();
    }
}

void render_mod_status_gui_alt(uint8_t modifiers) {
    static const char PROGMEM gui_off_1[] = {0x85, 0x86, 0};
    static const char PROGMEM gui_off_2[] = {0xa5, 0xa6, 0};
    static const char PROGMEM gui_on_1[]  = {0x8d, 0x8e, 0};
    static const char PROGMEM gui_on_2[]  = {0xad, 0xae, 0};
    static const char PROGMEM alt_off_1[] = {0x87, 0x88, 0};
    static const char PROGMEM alt_off_2[] = {0xa7, 0xa8, 0};
    static const char PROGMEM alt_on_1[]  = {0x8f, 0x90, 0};
    static const char PROGMEM alt_on_2[]  = {0xaf, 0xb0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[]  = {0xc7, 0};
    static const char PROGMEM on_off_2[]  = {0xc8, 0};
    static const char PROGMEM off_on_1[]  = {0xc9, 0};
    static const char PROGMEM off_on_2[]  = {0xca, 0};
    static const char PROGMEM on_on_1[]   = {0xcb, 0};
    static const char PROGMEM on_on_2[]   = {0xcc, 0};

    if (modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_1, false);
    } else {
        oled_write_P(gui_off_1, false);
    }
    if ((modifiers & MOD_MASK_GUI) && (modifiers & MOD_MASK_ALT)) {
        oled_write_P(on_on_1, false);
    } else if (modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_1, false);
    } else if (modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }
    if (modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_1, false);
    } else {
        oled_write_P(alt_off_1, false);
    }
    if (modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_2, false);
    } else {
        oled_write_P(gui_off_2, false);
    }
    if (modifiers & MOD_MASK_GUI & MOD_MASK_ALT) {
        oled_write_P(on_on_2, false);
    } else if (modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_2, false);
    } else if (modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }
    if (modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_2, false);
    } else {
        oled_write_P(alt_off_2, false);
    }
}

void render_mod_status_ctrl_shift(uint8_t modifiers) {
    static const char PROGMEM ctrl_off_1[]  = {0x89, 0x8a, 0};
    static const char PROGMEM ctrl_off_2[]  = {0xa9, 0xaa, 0};
    static const char PROGMEM ctrl_on_1[]   = {0x91, 0x92, 0};
    static const char PROGMEM ctrl_on_2[]   = {0xb1, 0xb2, 0};
    static const char PROGMEM shift_off_1[] = {0x8b, 0x8c, 0};
    static const char PROGMEM shift_off_2[] = {0xab, 0xac, 0};
    static const char PROGMEM shift_on_1[]  = {0xcd, 0xce, 0};
    static const char PROGMEM shift_on_2[]  = {0xcf, 0xd0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[]  = {0xc7, 0};
    static const char PROGMEM on_off_2[]  = {0xc8, 0};
    static const char PROGMEM off_on_1[]  = {0xc9, 0};
    static const char PROGMEM off_on_2[]  = {0xca, 0};
    static const char PROGMEM on_on_1[]   = {0xcb, 0};
    static const char PROGMEM on_on_2[]   = {0xcc, 0};

    if (modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_1, false);
    } else {
        oled_write_P(ctrl_off_1, false);
    }
    if ((modifiers & MOD_MASK_CTRL) && (modifiers & MOD_MASK_SHIFT)) {
        oled_write_P(on_on_1, false);
    } else if (modifiers & MOD_MASK_CTRL) {
        oled_write_P(on_off_1, false);
    } else if (modifiers & MOD_MASK_SHIFT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }
    if (modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_1, false);
    } else {
        oled_write_P(shift_off_1, false);
    }
    if (modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_2, false);
    } else {
        oled_write_P(ctrl_off_2, false);
    }
    if (modifiers & MOD_MASK_CTRL & MOD_MASK_SHIFT) {
        oled_write_P(on_on_2, false);
    } else if (modifiers & MOD_MASK_CTRL) {
        oled_write_P(on_off_2, false);
    } else if (modifiers & MOD_MASK_SHIFT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }
    if (modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_2, false);
    } else {
        oled_write_P(shift_off_2, false);
    }
}

void render_layer_state(void) {
    static const char PROGMEM default_layer[] = {0x20, 0x94, 0x95, 0x96, 0x20, 0x20, 0xb4, 0xb5, 0xb6, 0x20, 0x20, 0xd4, 0xd5, 0xd6, 0x20, 0};
    static const char PROGMEM raise_layer[]   = {0x20, 0x97, 0x98, 0x99, 0x20, 0x20, 0xb7, 0xb8, 0xb9, 0x20, 0x20, 0xd7, 0xd8, 0xd9, 0x20, 0};
    static const char PROGMEM lower_layer[]   = {0x20, 0x9a, 0x9b, 0x9c, 0x20, 0x20, 0xba, 0xbb, 0xbc, 0x20, 0x20, 0xda, 0xdb, 0xdc, 0x20, 0};
    static const char PROGMEM nump_layer[]    = {0x20, 0x9d, 0x9e, 0x9f, 0x20, 0x20, 0xbd, 0xbe, 0xbf, 0x20, 0x20, 0xdd, 0xde, 0xdf, 0x20, 0};
    if (layer_state_is(_NUMP)) {
        oled_write_P(nump_layer, false);
    } else if (layer_state_is(_LOWER)) {
        oled_write_P(lower_layer, false);
    } else if (layer_state_is(_RAISE)) {
        oled_write_P(raise_layer, false);
    } else {
        oled_write_P(default_layer, false);
    }
}

// renders on oled
bool oled_task_user(void) {
    current_wpm = get_current_wpm();
    // led_usb_state = host_keyboard_led_state();

    if (is_keyboard_left()) {
        oled_set_cursor(0, 2);
        if (isSneaking) {
            render_layer_state();
        } else {
            for (size_t i = 0; i < 7; i++) {
                oled_write("     ", false);
            }
        }
        render_luna(0, 12);
    } else {
        oled_set_cursor(0, 6);
        render_layer_state();
        oled_set_cursor(0, 11);
        if (mod_state) {
            render_mod_status_gui_alt(get_mods());
            render_mod_status_ctrl_shift(get_mods());
        } else {
            for (size_t i = 0; i < 5; i++) {
                oled_write("     ", false);
            }
        }
    }
    return false;
}

#endif

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        // ç key
        case CEDILHA:
            if (record->event.pressed) {
                register_code(KC_QUOT);
                unregister_code(KC_QUOT);
                register_code(KC_C);
                unregister_code(KC_C);
            }
            break;
            return false;

        // ã key
        case AO:
            if (record->event.pressed) {
                register_code(KC_LSFT);
                register_code(KC_GRV);
                unregister_code(KC_LSFT);
                unregister_code(KC_GRV);
                register_code(KC_A);
                unregister_code(KC_A);
            }
            break;
            return false;

        // direct " key
        case ASPAS:
            if (record->event.pressed) {
                register_code(KC_LSFT);
                register_code(KC_QUOT);
                register_code(KC_SPC);
                unregister_code(KC_SPC);
                unregister_code(KC_QUOT);
                unregister_code(KC_LSFT);
            }
            break;
            return false;

        // Luna jumping on space
        case KC_SPC:
            if (record->event.pressed) {
                isJumping  = true;
                showedJump = false;
            } else {
                isJumping = false;
            }
            break;
            return false;
    }
    return true;
}

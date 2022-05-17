// Copyright 2022 Andrew Dunai (@and3rson)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "endgame48.h"
#include "config.h"
#include "taphold.h"
#include "rgblight.h"
#include "oled/oled_driver.h"
#include "smoothled.h"
#include "stdio.h"
#include "string.h"
#include "symbols.h"

#define ________ KC_TRNS

#define _MAIN 0
#define _ALPHA 1
#define _BETA 2
#define _SIGMA 3

#define F_DASH "\x9c\x9d"

uint32_t layer_colors[4] = {
    0x4020FF,
    0xFF0010,
    0x20FF00,
    0x40FFFF
};

enum custom_keycodes {
  KC_MAIN = EG_SAFE_RANGE,
  KC_ALPHA,
  KC_BETA,
};

/* TapHold is my own implementation of the `LT` macro. It's processed in `process_record_user()`. */
uint16_t taphold_config_size = 3;
taphold_t taphold_config[] = {
    {.key=KC_ALPHA, .mode=TAPHOLD_LAYER, .shortAction=KC_ESC, .longAction=_ALPHA},
    {.key=KC_BETA, .mode=TAPHOLD_LAYER, .shortAction=KC_EQL, .longAction=_BETA},
    {.key=KC_LCTRL, .mode=TAPHOLD_MOD, .shortAction=KC_MINS, .longAction=KC_LCTRL},
};
uint32_t taphold_timeout = 100;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Main layer
       ┏━━━━━┳━━━━━┯━━━━━┯━━━━━┯━━━━━┯━━━━━┓┏┳━┳┓┏━━━━━┯━━━━━┯━━━━━┯━━━━━┯━━━━━┳━━━━━┓
       ┃ TAB ┃  Q  │  W  │  E  │  R  │  T  ┃┃┃ ┃┃┃  Y  │  U  │  I  │  O  │  P  ┃ BSP ┃
       ┣━━━━━╉─────┼─────┼─────┼─────┼─────┨┃┃ ┃┃┣─────┼─────┼─────┼─────┼─────╊━━━━━┫
       ┃𝛼/ESC┃  A  │  S  │  D  │  F  │  G  ┃┃┃ ┃┃┃  H  │  J  │  K  │  L  │  ;  ┃ RET ┃
       ┣━━━━━╉─────┼─────┼─────┼─────┼─────┨┗┻━┻┛┣─────┼─────┼─────┼─────┼─────╊━━━━━┫
       ┃SHIFT┃  Z  │  X  │  C  │  V  │  B  ┃     ┃  N  │  M  │  ,  │  .  │  /  ┃LCTRL┃
       ┣━━━━━╉─────┼─────┼─────┼─────┼─────┨     ┣─────┼─────┼─────┼─────┼─────╊━━━━━┫
       ┃CTRL ┃     │     │ ALT │ GUI │SPACE┃ (o) ┃SPACE│ 𝛽/= │  '  │     │     ┃     ┃
       ┗━━━━━┻━━━━━┷━━━━━┷━━━━━┷━━━━━┷━━━━━┛     ┗━━━━━┷━━━━━┷━━━━━┷━━━━━┷━━━━━┻━━━━━┛
       */
    [_MAIN] = LAYOUT( \
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,             KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
        KC_ALPHA,KC_A,    KC_S,    KC_D,    KC_F,    KC_G,             KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,  \
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,             KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_LCTRL,\
        KC_LCTRL,________,________,KC_LALT, KC_LGUI, KC_SPC,  KC_EGMENU,KC_SPC, KC_BETA, KC_QUOT, ________,________,________\
    ),

    /* 𝛼 layer
       ┏━━━━━┳━━━━━┯━━━━━┯━━━━━┯━━━━━┯━━━━━┓┏┳━┳┓┏━━━━━┯━━━━━┯━━━━━┯━━━━━┯━━━━━┳━━━━━┓
       ┃     ┃PREV │PLAY │NEXT │     │     ┃┃┃ ┃┃┃  -  │ ^^^ │  ^  │ vvv │  ~  ┃ DEL ┃
       ┣━━━━━╉─────┼─────┼─────┼─────┼─────┨┃┃ ┃┃┣─────┼─────┼─────┼─────┼─────╊━━━━━┫
       ┃     ┃     │VOL -│VOL +│     │     ┃┃┃ ┃┃┃HOME │ <-- │  v  │ --> │  `  ┃  \  ┃
       ┣━━━━━╉─────┼─────┼─────┼─────┼─────┨┗┻━┻┛┣─────┼─────┼─────┼─────┼─────╊━━━━━┫
       ┃     ┃     │     │     │     │     ┃     ┃ END │  =  │  [  │  ]  │  (  ┃  )  ┃
       ┣━━━━━╉─────┼─────┼─────┼─────┼─────┨     ┣─────┼─────┼─────┼─────┼─────╊━━━━━┫
       ┃     ┃     │     │     │     │     ┃ (o) ┃     │     │     │     │     ┃     ┃
       ┗━━━━━┻━━━━━┷━━━━━┷━━━━━┷━━━━━┷━━━━━┛     ┗━━━━━┷━━━━━┷━━━━━┷━━━━━┷━━━━━┻━━━━━┛
       */
    [_ALPHA] = LAYOUT( \
        ________,KC_MPRV, KC_MPLY, KC_MNXT, ________,________,         KC_MINS, KC_PGUP, KC_UP,   KC_PGDN, KC_TILD, KC_DEL,  \
        ________,________,KC_VOLD, KC_VOLU, ________,________,         KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT,KC_GRV,  KC_BSLS, \
        ________,________,________,________,________,________,         KC_END,  KC_EQL,  KC_LBRC, KC_RBRC, LSFT(KC_9),LSFT(KC_0),\
        ________,________,________,________,________,________,________,________,________,________,________,________,________\
    ),

    /* 𝛽 layer
       ┏━━━━━┳━━━━━┯━━━━━┯━━━━━┯━━━━━┯━━━━━┓┏┳━┳┓┏━━━━━┯━━━━━┯━━━━━┯━━━━━┯━━━━━┳━━━━━┓
       ┃ RGB ┃  1  │  2  │  3  │  4  │  5  ┃┃┃ ┃┃┃  6  │  7  │  8  │  9  │  0  ┃ F12 ┃
       ┣━━━━━╉─────┼─────┼─────┼─────┼─────┨┃┃ ┃┃┣─────┼─────┼─────┼─────┼─────╊━━━━━┫
       ┃     ┃ F1  │ F2  │ F3  │ F4  │ F5  ┃┃┃ ┃┃┃ F6  │ F7  │ F8  │ F9  │ F10 ┃ F11 ┃
       ┣━━━━━╉─────┼─────┼─────┼─────┼─────┨┗┻━┻┛┣─────┼─────┼─────┼─────┼─────╊━━━━━┫
       ┃     ┃RESET│DEBUG│SLEEP│WAKE │EGMNU ┃     ┃     │     │  {  │  }  │     ┃     ┃
       ┣━━━━━╉─────┼─────┼─────┼─────┼─────┨     ┣─────┼─────┼─────┼─────┼─────╊━━━━━┫
       ┃     ┃     │     │     │     │     ┃ (o) ┃PTSCR│     │     │     │     ┃     ┃
       ┗━━━━━┻━━━━━┷━━━━━┷━━━━━┷━━━━━┷━━━━━┛     ┗━━━━━┷━━━━━┷━━━━━┷━━━━━┷━━━━━┻━━━━━┛
       */
    [_BETA] = LAYOUT( \
        RGB_TOG, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,             KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_F12,  \
        ________,KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,            KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  \
        ________,RESET,   DEBUG,   KC_PWR,  KC_WAKE, KC_EGMENU,        ________,________,KC_LCBR, KC_RCBR, ________,________,\
        ________,________,________,________,________,KC_MUTE, ________,KC_PSCR, ________,________,________,________,________\
    ),
    /* Σ layer
       ┏━━━━━┳━━━━━┯━━━━━┯━━━━━┯━━━━━┯━━━━━┓┏┳━┳┓┏━━━━━┯━━━━━┯━━━━━┯━━━━━┯━━━━━┳━━━━━┓
       ┃     ┃     │     │     │     │     ┃┃┃ ┃┃┃     │     │     │     │     ┃     ┃
       ┣━━━━━╉─────┼─────┼─────┼─────┼─────┨┃┃ ┃┃┣─────┼─────┼─────┼─────┼─────╊━━━━━┫
       ┃     ┃     │     │     │     │     ┃┃┃ ┃┃┃     │     │     │     │     ┃     ┃
       ┣━━━━━╉─────┼─────┼─────┼─────┼─────┨┗┻━┻┛┣─────┼─────┼─────┼─────┼─────╊━━━━━┫
       ┃     ┃     │     │     │     │     ┃     ┃     │     │     │     │     ┃     ┃
       ┣━━━━━╉─────┼─────┼─────┼─────┼─────┨     ┣─────┼─────┼─────┼─────┼─────╊━━━━━┫
       ┃     ┃     │     │     │     │     ┃ (o) ┃     │     │     │     │     ┃     ┃
       ┗━━━━━┻━━━━━┷━━━━━┷━━━━━┷━━━━━┷━━━━━┛     ┗━━━━━┷━━━━━┷━━━━━┷━━━━━┷━━━━━┻━━━━━┛
       */
    [_SIGMA] = LAYOUT( \
        ________,________,________,________,________,________,         ________,________,________,________,________,________,\
        ________,________,________,________,________,________,         ________,________,________,________,________,________,\
        ________,________,________,________,________,________,         ________,________,________,________,________,________,\
        ________,________,________,________,________,________,________,________,________,________,________,________,________\
    ),
};

static bool alpha_pressed = false;
static bool beta_pressed = false;

static bool ctrl_pressed = false;
static bool alt_pressed = false;
static bool shift_pressed = false;
static bool gui_pressed = false;

static volatile uint32_t last_scan;
static volatile uint32_t scan_interval;

void matrix_init_user(void) {
    smoothled_set(layer_colors[0], 1500, swimOut);
}

void matrix_scan_user(void) {
    uint32_t now = timer_read32();
    scan_interval = now - last_scan;
    last_scan = now;
    smoothled_process();
}

void suspend_power_down_user(void) {
    smoothled_set(0, 0, swimIn);
}

void suspend_wakeup_init_user(void) {
    smoothled_set(layer_colors[_MAIN], 1500, swimOut);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    layer_state_t prevState = update_tri_layer_state(layer_state, _ALPHA, _BETA, _SIGMA);
    state = update_tri_layer_state(state, _ALPHA, _BETA, _SIGMA);
    uint8_t prevLayer = biton32(prevState);
    uint8_t layer = biton32(state);
    smoothled_set(layer_colors[layer], 250, prevLayer < layer ? swimOut : swimIn);
    return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == KC_LCTRL) ctrl_pressed = record->event.pressed;
    if (keycode == KC_LALT) alt_pressed = record->event.pressed;
    if (keycode == KC_LSFT) shift_pressed = record->event.pressed;
    if (keycode == KC_LGUI) gui_pressed = record->event.pressed;

    if (keycode == RESET) {
        request_reset();
        return false;
    }

    if (keycode == KC_ALPHA) alpha_pressed = record->event.pressed;
    if (keycode == KC_BETA) beta_pressed = record->event.pressed;

    return taphold_process(keycode, record);
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (alpha_pressed) {
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
        } else if (beta_pressed) {
            if (clockwise) {
                tap_code(KC_PGDN);
            } else {
                tap_code(KC_PGUP);
            }
        } else {
            if (clockwise) {
                tap_code(KC_MS_WH_DOWN);
            } else {
                tap_code(KC_MS_WH_UP);
            }
        }
    }
    return false;
}

bool oled_task_user(void) {
    oled_write_P(logo, false);

    uint8_t current_layer = biton32(layer_state);

    oled_write_P(layerIcons[current_layer], current_layer != _MAIN);

    oled_write_P(PSTR("\n\n"), false);

    char mod_data[12] = F_DASH " " F_DASH F_DASH " " F_DASH "\n\0";
    if (ctrl_pressed) memcpy(mod_data, mods[0], 2);
    if (alt_pressed) memcpy(mod_data +3, mods[1], 2);
    if (shift_pressed) memcpy(mod_data + 5, mods[2], 2);
    if (gui_pressed) memcpy(mod_data + 8, mods[3], 2);
    oled_write(mod_data, false);

    char buf[10] = "     ";
    buf[sprintf(buf, "%2lums", scan_interval ? scan_interval : 1L)] = ' ';
    buf[5] = 0;
    oled_write(buf, false);

    return false;
}

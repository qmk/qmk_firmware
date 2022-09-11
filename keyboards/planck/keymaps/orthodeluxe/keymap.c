/* Copyright 2020 Erik Bakker
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
#include "muse.h"

enum planck_layers {
    _BASELAYER_MACOS,
    _BASELAYER_WINDOWS,
    _LEFTYLAYER,
    _NUMLAYER_MACOS,
    _NUMLAYER_WINDOWS,
    _NAVLAYER_MACOS,
    _NAVLAYER_WINDOWS,
    _SYMLAYER_MACOS,
    _SYMLAYER_WINDOWS,
    _UTILSLAYER
};

enum planck_keycodes {
    MACOS = SAFE_RANGE, 
    WINDOWS,
    RCMDCTRL, 
    LEFTYCUT, LEFTYCOPY, LEFTYPASTE,
    PLUSCOLON,
    APPSWITCH, TASKVIEW, PREVDESK, NEXTDESK,
    QUOTES, DQUOTES,
    POINTYBR, SQUAREBR, CURLYBR, ROUNDBR
};

enum appswitch_mode {
    APPSWITCH_OFF, 
    APPSWITCH_FIRST_TIME,
    APPSWITCH_ON,
    APPSWITCH_TASK_VIEW
};

enum quote_shapes {
    SINGLE_QUOTE, DOUBLE_QUOTE
};

enum bracket_shapes {
    POINTY, SQUARE, CURLY, ROUND
};

uint8_t windowsmode = 0;

#define L_NUM_M MO(_NUMLAYER_MACOS)
#define L_NUM_W MO(_NUMLAYER_WINDOWS)
#define L_NAV_M MO(_NAVLAYER_MACOS)
#define L_NAV_W MO(_NAVLAYER_WINDOWS)
#define L_SYM_M MO(_SYMLAYER_MACOS)
#define L_SYM_W MO(_SYMLAYER_WINDOWS)
#define UTILSLAYER MO(_UTILSLAYER)

static void set_keycodes_for_os(int os);
static bool handle_app_switch(bool pressed);
static bool app_switch_valid_keycode(uint16_t keycode);
static bool handle_right_command_or_control(bool pressed);
static bool handle_pluscolon(bool pressed);
static bool type_quotes(uint8_t quote_shape, bool pressed);
static bool type_brackets(uint8_t bracket_shape, bool pressed);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Base layer:
 * ,-----------------------------------------------------------------------------------.
 * |BckSpc|   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  Del |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  Esc |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  | ;  : | Enter|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab- |   Z  |   X  |   C  |   V  |   B  |   N  |   M  | ,  < | .  > | /  ? |  Tab |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Shift|      |      |      |NumLyr|    Space    |NavLyr|      |      |      | Shift|
 * `-----------------------------------------------------------------------------------'    
 *
 * Bottom row for MacOS:
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Shift| Ctrl |Option|  Cmd |NumLyr|    Space    |NavLyr|  Cmd |Option| Ctrl | Shift|
 * `-----------------------------------------------------------------------------------'
 *
 * Bottom row for Windows: 
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Shift|  Win |  Alt | Ctrl |NumLyr|    Space    |NavLyr| Ctrl |  Alt | Menu | Shift|
 * `-----------------------------------------------------------------------------------'
 */
[_BASELAYER_MACOS] = LAYOUT_planck_grid(
    KC_BSPC, KC_Q,     KC_W,    KC_E,     KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,     KC_O,    KC_P,     KC_DEL,
    KC_ESC,  KC_A,     KC_S,    KC_D,     KC_F,    KC_G,    KC_H,    KC_J,    KC_K,     KC_L,    KC_SCLN,  KC_ENT,
    _______, KC_Z,     KC_X,    KC_C,     KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM,  KC_DOT,  KC_SLSH,  KC_TAB,
    KC_LSFT, KC_LCTRL, KC_LALT, KC_LGUI,  L_NUM_M, KC_SPC,  KC_SPC,  L_NAV_M, RCMDCTRL, KC_RALT, KC_RCTRL, KC_RSFT
),
[_BASELAYER_WINDOWS] = LAYOUT_planck_grid(
    KC_BSPC, KC_Q,     KC_W,    KC_E,     KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,     KC_O,    KC_P,     KC_DEL,
    KC_ESC,  KC_A,     KC_S,    KC_D,     KC_F,    KC_G,    KC_H,    KC_J,    KC_K,     KC_L,    KC_SCLN,  KC_ENT,
    _______, KC_Z,     KC_X,    KC_C,     KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM,  KC_DOT,  KC_SLSH,  KC_TAB,
    KC_LSFT, KC_LGUI,  KC_LALT, KC_LCTRL, L_NUM_W, KC_SPC,  KC_SPC,  L_NAV_W, RCMDCTRL, KC_RALT, KC_APP,   KC_RSFT
),

/* Lefty layer:
 * This layer enables lefties (who mouse with their left hand) to easily cut, copy and paste using their right hand.
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |  Cut | Copy | Paste|      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |(hold)|      |      |      |
 * '-----------------------------------------------------------------------------------'
 */
 
 [_LEFTYLAYER] = LAYOUT_planck_grid(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, KC_X,    KC_C,    KC_V,    _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Numpad layer:
 * ,-----------------------------------------------------------------------------------.
 * |      |   &  |   |  |   !  |   +  |   =  |   %  |   7  |   8  |   9  |   *  |   =  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   @  | '  ' | "  " |   -  |   _  |   €  |   4  |   5  |   6  | +  : | Enter|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | <  > | [  ] | {  } | (  ) |   \  |   $  |   1  |   2  |   3  |   /  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |(hold)|             |SymLyr|   0  |   .  |   -  |      |
 * `-----------------------------------------------------------------------------------'
 */
[_NUMLAYER_MACOS] = LAYOUT_planck_grid(
    _______, KC_AMPR,  KC_PIPE,  KC_EXLM, KC_PPLS, KC_EQL,  KC_PERC,    KC_7,    KC_8,    KC_9,    KC_PAST,   KC_EQL,
    _______, KC_AT,    QUOTES,   DQUOTES, KC_MINS, KC_UNDS, RALT(KC_2), KC_4,    KC_5,    KC_6,    PLUSCOLON, KC_PENT,
    _______, POINTYBR, SQUAREBR, CURLYBR, ROUNDBR, KC_BSLS, KC_DLR,     KC_1,    KC_2,    KC_3,    KC_PSLS,   _______,
    _______, _______,  _______,  _______, _______, _______, _______,    L_SYM_M, KC_0,    KC_PDOT, KC_PMNS,   _______
),
[_NUMLAYER_WINDOWS] = LAYOUT_planck_grid(
    _______, KC_AMPR,  KC_PIPE,  KC_EXLM, KC_PPLS, KC_EQL,  KC_PERC,    KC_7,    KC_8,    KC_9,    KC_PAST,   KC_EQL,
    _______, KC_AT,    QUOTES,   DQUOTES, KC_MINS, KC_UNDS, RALT(KC_5), KC_4,    KC_5,    KC_6,    PLUSCOLON, KC_PENT,
    _______, POINTYBR, SQUAREBR, CURLYBR, ROUNDBR, KC_BSLS, KC_DLR,     KC_1,    KC_2,    KC_3,    KC_PSLS,   _______,
    _______, _______,  _______,  _______, _______, _______, _______,    L_SYM_W, KC_0,    KC_PDOT, KC_PMNS,   _______
),

/* Symbol layer:
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |   €  |      |   ~  |      |   _  |   ^  |      |   %  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   @  |   $  |   $  |      |   `  |   #  |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |   !  |      |      |   \  |   ~  |   &  |      |      |   !  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |(hold)|  UtilsLayer |(hold)|      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_SYMLAYER_MACOS] = LAYOUT_planck_grid(
    _______, XXXXXXX, XXXXXXX, RALT(KC_2), XXXXXXX, KC_TILD,    XXXXXXX,    KC_UNDS, KC_CIRC, XXXXXXX, KC_PERC, _______,
    _______, KC_AT,   KC_DLR,  KC_DLR,     XXXXXXX, KC_GRV,     KC_HASH,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
    _______, XXXXXXX, KC_EXLM, XXXXXXX,    XXXXXXX, KC_BSLS,    KC_TILD,    KC_AMPR, XXXXXXX, XXXXXXX, KC_EXLM, _______,
    _______, _______, _______, _______,    _______, UTILSLAYER, UTILSLAYER, _______, _______, _______, _______, _______
),
[_SYMLAYER_WINDOWS] = LAYOUT_planck_grid(
    _______, XXXXXXX, XXXXXXX, RALT(KC_5), XXXXXXX, KC_TILD,    XXXXXXX,    KC_UNDS, KC_CIRC, XXXXXXX, KC_PERC, _______,
    _______, KC_AT,   KC_DLR,  KC_DLR,     XXXXXXX, KC_GRV,     KC_HASH,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
    _______, XXXXXXX, KC_EXLM, XXXXXXX,    XXXXXXX, KC_BSLS,    KC_TILD,    KC_AMPR, XXXXXXX, XXXXXXX, KC_EXLM, _______,
    _______, _______, _______, _______,    _______, UTILSLAYER, UTILSLAYER, _______, _______, _______, _______, _______
),

/* Navigation layer:
 * ,-----------------------------------------------------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |      | PgUp | Home |  Up  |  End |PrtScr| Lock |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F5  |  F6  |  F7  |  F8  |      | PgDn | Left | Down | Right| AppSw|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F9  |  F10 |  F11 |  F12 |      |      |PrDesk| Down |NxDesk|TaskVw|      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |SymLyr|             |(hold)|      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_NAVLAYER_MACOS] = LAYOUT_planck_grid(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   XXXXXXX, KC_PGUP, G(KC_LEFT), KC_UP,   G(KC_RGHT), SGUI(KC_4), C(G(KC_Q)),
    _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   XXXXXXX, KC_PGDN, KC_LEFT,    KC_DOWN, KC_RGHT,    APPSWITCH,  _______,
    _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  XXXXXXX, XXXXXXX, C(KC_LEFT), KC_DOWN, C(KC_RGHT), C(KC_UP),   _______,
    _______, _______, _______, _______, L_SYM_M, _______, _______, _______,    _______, _______,    _______,    _______
),
[_NAVLAYER_WINDOWS] = LAYOUT_planck_grid(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   XXXXXXX, KC_PGUP, KC_HOME,       KC_UP,   KC_END,        KC_PSCR,   G(KC_L),
    _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   XXXXXXX, KC_PGDN, KC_LEFT,       KC_DOWN, KC_RGHT,       APPSWITCH, _______,
    _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  XXXXXXX, XXXXXXX, C(G(KC_LEFT)), KC_DOWN, C(G(KC_RGHT)), G(KC_TAB), _______,
    _______, _______, _______, _______, L_SYM_W, _______, _______, _______,       _______, _______,       _______,   _______
),

/* Utilities layer:
 * ,-----------------------------------------------------------------------------------.
 * |      |      |  Win |      | Reset|      |      |      |  Ins |      | Pause|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |ScrlLk| Debug|      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |CapsLk|      |      | NumLk|  Mac |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |(hold)|    (hold)   |(hold)|      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_UTILSLAYER] = LAYOUT_planck_grid(
    _______, XXXXXXX, WINDOWS, XXXXXXX, QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, KC_INS,  XXXXXXX, KC_PAUS, _______,
    _______, XXXXXXX, KC_SLCK, DEBUG,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
    _______, XXXXXXX, XXXXXXX, KC_CAPS, XXXXXXX, XXXXXXX, KC_NLCK, MACOS,   XXXXXXX, XXXXXXX, XXXXXXX, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)
};

/* Bootmagic keys (hold when plugging in the USB cable):
 * ,-----------------------------------------------------------------------------------.
 * |BootLd|      |  Win |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |  Mac |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

bool app_switch_active = false;
static uint16_t timer;
static uint16_t duration = 0;
static bool double_tap = false;
uint8_t active_modifiers = 0;
bool shift_modifier_active = false;
uint8_t keycode_rightcommand;
uint8_t keycode_appswitch;

/* main loop */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    /* Store modifiers in booleans for easy access in underlying methods. */
    active_modifiers = get_mods();
    shift_modifier_active = active_modifiers & ((1<<((KC_LSFT) & 0x07)) | (1<<((KC_RSFT) & 0x07)));

    /* Switch off timer when double click time is exceeded. */
    if (timer > 0) {
        duration = timer_elapsed(timer);
        if (duration > TAPPING_TERM) { timer = 0; }
    }
        
    /* Keep app_switch_active true, while a valid key is pressed. */
    if (app_switch_active) {
        if ((keycode == L_NAV_M || keycode == L_NAV_W) && record->event.pressed == false) {
            unregister_code(keycode_appswitch);
            app_switch_active = false;
        }
        if (app_switch_valid_keycode(keycode) == false) {
            unregister_code(keycode_appswitch);
            app_switch_active = false;
        }
    }

    switch (keycode) {
        case MACOS:
            #ifdef AUDIO_ENABLE
                stop_all_notes();
                PLAY_SONG(plover_song);
            #endif
            set_keycodes_for_os(MACOS);
            default_layer_set(_BASELAYER_MACOS);
            layer_on(_BASELAYER_MACOS);
            layer_off(_BASELAYER_WINDOWS);
            return false;
            break;
        case WINDOWS:
            #ifdef AUDIO_ENABLE
                stop_all_notes();
                PLAY_SONG(plover_gb_song);
            #endif
            set_keycodes_for_os(WINDOWS);
            default_layer_set(_BASELAYER_WINDOWS);
            layer_on(_BASELAYER_WINDOWS);
            layer_off(_BASELAYER_MACOS);
            return false;
            break;
        case RCMDCTRL:
            return handle_right_command_or_control(record->event.pressed);
            break;
        case APPSWITCH:
            return handle_app_switch(record->event.pressed);
            break;
        case QUOTES:
            return type_quotes(SINGLE_QUOTE, record->event.pressed);
            break;
        case DQUOTES:
            return type_quotes(DOUBLE_QUOTE, record->event.pressed);
            break;
        case POINTYBR:
            return type_brackets(POINTY, record->event.pressed);
            break;
        case SQUAREBR:
            return type_brackets(SQUARE, record->event.pressed);
            break;
        case CURLYBR:
            return type_brackets(CURLY, record->event.pressed);
            break;
        case ROUNDBR:
            return type_brackets(ROUND, record->event.pressed);
            break;
        case PLUSCOLON:
            return handle_pluscolon(record->event.pressed);
            break;
    }
    return true;
}

void set_keycodes_for_os(int os) {
    if (os == MACOS) {
        keycode_rightcommand = KC_RGUI;
        keycode_appswitch = KC_LGUI;
    } else {
        keycode_rightcommand = KC_RCTRL;
        keycode_appswitch = KC_LALT;
    }
}

/* While lefties use their mouse with their left hand, it is handy to use their right hand for Cut, Copy and Paste. */
bool handle_right_command_or_control(bool pressed) {
    if (pressed) {
        register_code(keycode_rightcommand);
        layer_on(_LEFTYLAYER);
    } else {
        layer_off(_LEFTYLAYER);
        unregister_code(keycode_rightcommand);
    }
    return false;
}

/* Key combo to easily switch applications. Press and hold Command or Alt, press and release Tab. Command or Alt is released when an invalid key is pressed in main loop. */
bool handle_app_switch(bool pressed) {
    if (pressed) {
        if (app_switch_active == false) {
          app_switch_active = true;
          register_code(keycode_appswitch);
        }
        register_code(KC_TAB);
    } else {
        unregister_code(KC_TAB);
    }
    return false;
}

/* Defines valid keys for app_switch function. */
bool app_switch_valid_keycode(uint16_t keycode) {
    if (keycode == APPSWITCH || KC_UP || KC_LEFT || KC_DOWN || KC_RIGHT) {
        return true;
    }
    return false;
}

/* Type 1 or 2 quotation marks, either single or double quotation marks.
 *  - Press once: type 1 quote and start timer. 
 *  - Quickly press twice: type pair of quotes and put cursor in between. 
 */
bool type_quotes(uint8_t quote_shape, bool pressed) {
    clear_mods();
    bool use_shift = quote_shape == DOUBLE_QUOTE ? true : false;

    duration = timer_elapsed(timer);

    if (pressed) {
        if ((timer == 0) || (duration == 0) || (duration > TAPPING_TERM)) {
            if (use_shift) { register_code(KC_LSFT); }
            register_code(KC_QUOT);
            double_tap = false;
        } else {
            if (duration < TAPPING_TERM) {
                if (use_shift) { 
                    tap_code16(S(KC_QUOT));
                } else {
                    tap_code(KC_QUOT);
                }
                double_tap = true;
            }
        }
    } else {
        if (double_tap) {
            tap_code(KC_LEFT);
            timer = 0;
            double_tap = false;
        } else {
            unregister_code(KC_QUOT);
            if (use_shift) { unregister_code(KC_LSFT); }
            timer = timer_read();
            double_tap = false;
        }
    }

    set_mods(active_modifiers);
    return false;
}

/* Type a bracket or a pair of brackets
 *  - Press once: type opening bracket.
 *  - Press while holding shift: type closing bracket.
 *  - Quickly press twice: type pair of brackets and put cursor in between.
 */
bool type_brackets(uint8_t bracket_shape, bool pressed) {
    clear_mods();

    uint8_t opening_bracket;
    uint8_t closing_bracket;
    bool use_shift;
    switch (bracket_shape) {
        case POINTY:
            opening_bracket = KC_COMM;
            closing_bracket = KC_DOT;
            use_shift = true;
            break;
        case SQUARE:
            opening_bracket = KC_LBRC;
            closing_bracket = KC_RBRC;
            use_shift = false;
            break;
        case CURLY:
            opening_bracket = KC_LBRC;
            closing_bracket = KC_RBRC;
            use_shift = true;
            break;
        case ROUND:
            opening_bracket = KC_9;
            closing_bracket = KC_0;
            use_shift = true;
            break;
    }
    duration = timer_elapsed(timer);

    if (pressed) {
        if ((timer == 0) || (duration == 0) || (duration > TAPPING_TERM) || (shift_modifier_active)) {
            if (use_shift) { register_code(KC_LSFT); }
            register_code(shift_modifier_active ? closing_bracket : opening_bracket);
            double_tap = false;
        } else {
            if (duration < TAPPING_TERM) {
                if (use_shift) { 
                    tap_code16(S(closing_bracket));
                } else {
                    tap_code(closing_bracket);
                }
                double_tap = true;
            }
        }
    } else {
        if (double_tap) {
            tap_code(KC_LEFT);
            timer = 0;
            double_tap = false;
        } else {
            unregister_code(shift_modifier_active ? closing_bracket : opening_bracket);
            if (use_shift) { unregister_code(KC_LSFT); }
            timer = timer_read();
            double_tap = false;
        }
    }

    set_mods(active_modifiers);
    return false;
}

/* On the Numpad-layer, the semicolon key produces a Plus ('+'). But to help entering time values, we like to have a colon (':') when shift is held. */
bool handle_pluscolon(bool pressed) {
    if (pressed) {
        register_code(shift_modifier_active ? KC_SCLN : KC_PPLS);
    } else {
        unregister_code(shift_modifier_active ? KC_SCLN : KC_PPLS);
    }
    return false;
}

// Bootmagic configures the keyboard when initializing (starting up after connecting the USB cable)
void bootmagic_lite(void) {
    matrix_scan();
    wait_ms(DEBOUNCE * 2);
    matrix_scan();
    int os;

    // hold key in upper left corner while plugging in the USB cable to enter the Bootloader for flashing.
    if (matrix_get_row(BOOTMAGIC_LITE_ROW) & (1 << BOOTMAGIC_LITE_COLUMN)) {
        bootloader_jump();
    }

    // hold M key while plugging in the USB cable to use the keyboard in MacOs mode.
    if (matrix_get_row(BOOTMAGIC_LITE_MACOS_ROW) & (1 << BOOTMAGIC_LITE_MACOS_COLUMN)) {
        os = MACOS;
    }

    // hold W key while plugging in the USB cable to use the keyboard in Windows mode.
    if (matrix_get_row(BOOTMAGIC_LITE_WIN_ROW) & (1 << BOOTMAGIC_LITE_WIN_COLUMN)) {
        os = WINDOWS;
    }

    switch (os){
        case MACOS:
            default_layer_set(_BASELAYER_MACOS);
            layer_on(_BASELAYER_MACOS);
            layer_off(_BASELAYER_WINDOWS);
            break;
        case WINDOWS:
            default_layer_set(_BASELAYER_WINDOWS);
            layer_on(_BASELAYER_WINDOWS);
            layer_off(_BASELAYER_MACOS);
            break;
        default:
            os = MACOS;
            default_layer_set(_BASELAYER_MACOS);
            layer_on(_BASELAYER_MACOS);
            layer_off(_BASELAYER_WINDOWS);
            break;
    }
    set_keycodes_for_os(os);
}

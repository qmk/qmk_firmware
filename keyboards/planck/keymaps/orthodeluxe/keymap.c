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
    _BASELAYER,
    _LEFTYLAYER,
    _NUMLAYER,
    _SYMLAYER,
    _NAVLAYER,
    _UTILSLAYER
};

enum planck_keycodes {
    MACOS = SAFE_RANGE, 
    WINDOWS,
    NUMLAYER, NAVLAYER, SYMLAYER, 
    LCMDCTRL, RCMDCTRL, LCTRLWIN, RCTRLMENU, 
    LEFTYCUT, LEFTYCOPY, LEFTYPASTE,
    PRTSCR, EUROSIGN, HOMEKEY, ENDKEY, LOCKSCREEN, PLUSCOLON,
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

#define NUMLAYER MO(_NUMLAYER)
#define NAVLAYER MO(_NAVLAYER)
#define SYMLAYER MO(_SYMLAYER)
#define UTILSLAYER MO(_UTILSLAYER)

static bool handle_mac_or_win_key(uint16_t mac_keycode, uint16_t win_keycode, bool pressed);
static bool type_eurosign(bool pressed);
static bool handle_print_screen(bool pressed);
static bool handle_lock_screen(bool pressed);
static bool handle_home_key(bool pressed);
static bool handle_end_key(bool pressed);
static bool handle_show_task_view(bool pressed);
static bool handle_switch_desktop(bool previous, bool pressed);
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
[_BASELAYER] = LAYOUT_planck_grid(
    KC_BSPC,   KC_Q,     KC_W,    KC_E,     KC_R,     KC_T,    KC_Y,    KC_U,     KC_I,     KC_O,    KC_P,      KC_DEL,
    KC_ESC,    KC_A,     KC_S,    KC_D,     KC_F,     KC_G,    KC_H,    KC_J,     KC_K,     KC_L,    KC_SCLN,   KC_ENT,
    S(KC_TAB), KC_Z,     KC_X,    KC_C,     KC_V,     KC_B,    KC_N,    KC_M,     KC_COMM,  KC_DOT,  KC_SLSH,   KC_TAB,
    KC_LSFT,   LCTRLWIN, KC_RALT, LCMDCTRL, NUMLAYER, KC_SPC,  KC_SPC,  NAVLAYER, RCMDCTRL, KC_RALT, RCTRLMENU, KC_RSFT
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
[_NUMLAYER] = LAYOUT_planck_grid(
    _______, KC_AMPR,  KC_PIPE,  KC_EXLM, KC_PPLS, KC_EQL,  KC_PERC,  KC_7,     KC_8,    KC_9,    KC_PAST,   KC_EQL,
    _______, KC_AT,    QUOTES,   DQUOTES, KC_MINS, KC_UNDS, EUROSIGN, KC_4,     KC_5,    KC_6,    PLUSCOLON, KC_PENT,
    _______, POINTYBR, SQUAREBR, CURLYBR, ROUNDBR, KC_BSLS, KC_DLR,   KC_1,     KC_2,    KC_3,    KC_PSLS,   _______,
    _______, _______,  _______,  _______, _______, _______, _______,  SYMLAYER, KC_0,    KC_PDOT, KC_PMNS,   _______
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
[_SYMLAYER] = LAYOUT_planck_grid(
    _______, _______, _______, EUROSIGN, _______, KC_TILD,    _______,    KC_UNDS, KC_CIRC, _______, KC_PERC, _______,
    _______, KC_AT,   KC_DLR,  KC_DLR,   _______, KC_GRV,     KC_HASH,    _______, _______, _______, _______, _______,
    _______, _______, KC_EXLM, _______,  _______, KC_BSLS,    KC_TILD,    KC_AMPR, _______, _______, KC_EXLM, _______,
    _______, _______, _______, _______,  _______, UTILSLAYER, UTILSLAYER, _______, _______, _______, _______, _______
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
[_NAVLAYER] = LAYOUT_planck_grid(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,    XXXXXXX, KC_PGUP, HOMEKEY,  KC_UP,   ENDKEY,   PRTSCR,    LOCKSCREEN,
    _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,    XXXXXXX, KC_PGDN, KC_LEFT,  KC_DOWN, KC_RGHT,  APPSWITCH, _______,
    _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,   XXXXXXX, XXXXXXX, PREVDESK, KC_DOWN, NEXTDESK, TASKVIEW,  _______,
    _______, _______, _______, _______, SYMLAYER, _______, _______, _______,  _______, _______,  _______,   _______
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
    _______, XXXXXXX, WINDOWS, XXXXXXX, RESET,   XXXXXXX, XXXXXXX, XXXXXXX, KC_INS,  XXXXXXX, KC_PAUS, _______,
    _______, XXXXXXX, KC_SLCK, DEBUG,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
    _______, XXXXXXX, XXXXXXX, KC_CAPS, XXXXXXX, XXXXXXX, KC_NLCK, MACOS,   XXXXXXX, XXXXXXX, XXXXXXX, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)
};

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

bool macos_mode = true;
bool app_switch_active = false;
static uint16_t timer;
static uint16_t duration = 0;
static bool double_tap = false;
uint8_t active_modifiers = 0;
bool shift_modifier_active = false;

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
        if (keycode == NAVLAYER && record->event.pressed == false) {
            unregister_code(macos_mode ? KC_LGUI : KC_LALT);
            app_switch_active = false;
        }
        if (app_switch_valid_keycode(keycode) == false) {
          unregister_code(macos_mode ? KC_LGUI : KC_LALT);
          app_switch_active = false;
        }
    }

    switch (keycode) {
        case MACOS:
            #ifdef AUDIO_ENABLE
                stop_all_notes();
                PLAY_SONG(plover_song);
            #endif
            macos_mode = true;
            return false;
            break;
        case WINDOWS:
            #ifdef AUDIO_ENABLE
                stop_all_notes();
                PLAY_SONG(plover_gb_song);
            #endif
            macos_mode = false;
            return false;
            break;
        case LCMDCTRL:
            return handle_mac_or_win_key(KC_LGUI, KC_LCTRL, record->event.pressed);
            break;
        case RCMDCTRL:
            return handle_right_command_or_control(record->event.pressed);
            break;
        case LCTRLWIN:
            return handle_mac_or_win_key(KC_LCTRL, KC_LGUI, record->event.pressed);
            break;
        case RCTRLMENU:
            return handle_mac_or_win_key(KC_RCTRL, KC_APP, record->event.pressed);
            break;
        case EUROSIGN:
            return type_eurosign(record->event.pressed);
            break;
        case PRTSCR:
            return handle_print_screen(record->event.pressed);
            break;
        case LOCKSCREEN:
            return handle_lock_screen(record->event.pressed);
            break;
        case HOMEKEY:
            return handle_home_key(record->event.pressed);
            break;
        case ENDKEY:
            return handle_end_key(record->event.pressed);
            break;
        case APPSWITCH:
            return handle_app_switch(record->event.pressed);
            break;
        case PREVDESK:
            return handle_switch_desktop(true, record->event.pressed);
            break;
        case NEXTDESK:
            return handle_switch_desktop(false, record->event.pressed);
            break;
        case TASKVIEW:
            return handle_show_task_view(record->event.pressed);
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

/* Type 1 of 2 keycodes, depending on OS mode (MacOs or Windows) */
bool handle_mac_or_win_key(uint16_t mac_keycode, uint16_t win_keycode, bool pressed) {
    if (pressed) {
        register_code(macos_mode ? mac_keycode : win_keycode); 
    } else {
        unregister_code(macos_mode ? mac_keycode : win_keycode); 
    }
    return false;
}

/* While lefties use their mouse with their left hand, it is handy to use their right hand for Cut, Copy and Paste. */
bool handle_right_command_or_control(bool pressed) {
    if (pressed) {
        register_code(macos_mode ? KC_RGUI : KC_RCTL);
        layer_on(_LEFTYLAYER);
    } else {
        layer_off(_LEFTYLAYER);
        unregister_code(macos_mode ? KC_RGUI : KC_RCTL);
    }
    return false;
}

/* Key combo to type a euro sign. */
bool type_eurosign(bool pressed) {
    /* Register_code16 does not seem to work here. */
    if (pressed) {
        register_code(KC_RALT); 
        register_code(macos_mode ? KC_2 : KC_5); 
    } else {
        unregister_code(macos_mode ? KC_2 : KC_5); 
        unregister_code(KC_RALT); 
    }
    return false;
}

/* Key combo for the print screen function */
bool handle_print_screen(bool pressed) {
    if (macos_mode) {
        if (pressed) {
            register_code16(SGUI(KC_4)); 
        } else {
            unregister_code16(SGUI(KC_4)); 
        }
    } else {
        if (pressed) {
            register_code(KC_PSCR); 
        } else {
            unregister_code(KC_PSCR); 
        }
    }
    return false;
}

/* Key combo that locks the desktop */
bool handle_lock_screen(bool pressed) {
    if (macos_mode) {
        if (pressed){
            register_code(KC_LCTRL);
            register_code(KC_LGUI);
            register_code(KC_Q);
        } else {
            unregister_code(KC_Q);
            unregister_code(KC_LGUI);
            unregister_code(KC_LCTRL);
        }
    } else {
        if (pressed) {
            register_code16(G(KC_L));
        } else {
            unregister_code16(G(KC_L));
        }
    }
    return false;
}

/* Handle Home key in Windows, simulate Home key in MacOs. */
bool handle_home_key(bool pressed) {
    if (macos_mode) {
        if (pressed) {
            register_code16(G(KC_LEFT));
        } else {
            unregister_code16(G(KC_LEFT));
        }
    } else {
        if (pressed) {
            register_code(KC_HOME);
        } else {
            unregister_code(KC_HOME);
        }
    }
    return false;
}

/* Handle End key in Windows, simulate End key in MacOs. */
bool handle_end_key(bool pressed) {
    if (macos_mode) {
        if (pressed) {
            register_code16(G(KC_RGHT));
        } else {
            unregister_code16(G(KC_RGHT));
        }
    } else {
        if (pressed) {
            register_code(KC_END);
        } else {
            unregister_code(KC_END);
        }
    }
    return false;
}

/* Key combo to show TaskView (Windows) or Mission Control (MacOs). */
bool handle_show_task_view(bool pressed) {
    if (macos_mode) {
        if (pressed) {
            register_code16(C(KC_UP));
        } else {
            unregister_code16(C(KC_UP));
        }
    } else {
        if (pressed) {
            register_code16(G(KC_TAB));
        } else {
            unregister_code16(G(KC_TAB));
        }
    }
    return false;
}

 /* Key combo to easily switch virtual desktops ('Spaces' in MacOs). */
bool handle_switch_desktop(bool previous, bool pressed) {
    if (pressed) {
        if (macos_mode == false) {
            register_code(KC_LGUI);
        }
        register_code16(C(previous ? KC_LEFT : KC_RGHT));
    } else {
        unregister_code16(C(previous ? KC_LEFT : KC_RGHT));
        if (macos_mode == false) {
            unregister_code(KC_LGUI);
        }
    }
    return false;
}

/* Key combo to easily switch applications. Press and hold Command or Alt, press and release Tab. Command or Alt is released when an invalid key is pressed in main loop. */
bool handle_app_switch(bool pressed) {
    if (pressed) {
        if (app_switch_active == false) {
          app_switch_active = true;
          register_code(macos_mode ? KC_LGUI : KC_LALT);
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

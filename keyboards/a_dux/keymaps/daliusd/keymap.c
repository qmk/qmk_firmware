/* Copyright 2021 @daliusd
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

#include "oneshot.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layers {
    _QWERTY,
    _SYM,
    _NAV,
    _NUMB,
    _TMUX,
    _MOUSE,
    _MISC,
    _FUNC,
};

enum custom_keycodes {
  TM_NEXT = SAFE_RANGE,
  TM_PREV,
  TM_LEFT,
  TM_RIGHT,
  TM_NEW,
  TM_SLCT,
  TM_SRCH,
  TM_URL,
  OS_CTRL,
  OS_ALT,
  OS_GUI,
  OS_TMUX,
  OS_MISC,
  OS_FUNC,
};

// Shortcut to make keymap more readable

#define L_NAV       MO(_NAV)
#define L_SYM       MO(_SYM)
#define L_MOUSE     TG(_MOUSE)

#define K_PRINT     (QK_LCTL | QK_LSFT | QK_LGUI | KC_4)

enum unicode_names {
    SNEK,
    EURO,
    LT_S_A,
    LT_L_A,
    LT_S_C,
    LT_L_C,
    LT_S_E1,
    LT_L_E1,
    LT_S_E2,
    LT_L_E2,
    LT_S_I,
    LT_L_I,
    LT_S_S,
    LT_L_S,
    LT_S_U1,
    LT_L_U1,
    LT_S_U2,
    LT_L_U2,
    LT_S_Z,
    LT_L_Z,
    LT_OB,
    LT_CB,
};

const uint32_t PROGMEM unicode_map[] = {
    [SNEK]  = 0x1F40D, // 🐍
    [EURO]  = 0x20ac, // €
    [LT_S_A] = 0x105, // ą
    [LT_L_A] = 0x104, // Ą
    [LT_S_C] = 0x10d, // č
    [LT_L_C] = 0x10c, // Č
    [LT_S_E1] = 0x119, // ę
    [LT_L_E1] = 0x118, // Ę
    [LT_S_E2] = 0x117, // ė
    [LT_L_E2] = 0x116, // Ė
    [LT_S_I] = 0x12f, // į
    [LT_L_I] = 0x12e, // Į
    [LT_S_S] = 0x161, // š
    [LT_L_S] = 0x160, // Š'
    [LT_S_U1] = 0x173, // ų
    [LT_L_U1] = 0x172, // Ų
    [LT_S_U2] = 0x16b, // ū
    [LT_L_U2] = 0x16a, // Ū
    [LT_S_Z] = 0x17e, // ž
    [LT_L_Z] = 0x17d, // Ž
    [LT_OB] = 0x201e, // „
    [LT_CB] = 0x201c, // “
};

#define K_SNEK      X(SNEK)
#define K_EURO      X(EURO)
#define K_LT_A      XP(LT_S_A, LT_L_A)
#define K_LT_C      XP(LT_S_C, LT_L_C)
#define K_LT_E1     XP(LT_S_E1, LT_L_E1)
#define K_LT_E2     XP(LT_S_E2, LT_L_E2)
#define K_LT_I      XP(LT_S_I, LT_L_I)
#define K_LT_S      XP(LT_S_S, LT_L_S)
#define K_LT_U1     XP(LT_S_U1, LT_L_U1)
#define K_LT_U2     XP(LT_S_U2, LT_L_U2)
#define K_LT_Z      XP(LT_S_Z, LT_L_Z)
#define K_LT_OB     X(LT_OB)
#define K_LT_CB     X(LT_CB)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┐                         ┌────────┬────────┬────────┬────────┬────────┐
     KC_Q    ,KC_W    ,KC_E    ,KC_R    ,KC_T,                              KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,
  //├────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┤
     KC_A    ,KC_S    ,KC_D    ,KC_F    ,KC_G    ,                          KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_SCLN ,
  //├────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┤
     KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B    ,                          KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH,
  //└────────┴────────┴────────┴────┬───┴────┬───┼────────┐       ┌────────┼───┬────┴───┬────┴────────┴────────┴────────┘
                                     L_NAV   ,    KC_SPC  ,        KC_LSFT ,    L_SYM
  //                                └────────┘   └────────┘       └────────┘   └────────┘
  ),

  [_SYM] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┐                         ┌────────┬────────┬────────┬────────┬────────┐
     KC_EXLM ,KC_AT   ,KC_HASH ,KC_DLR  ,KC_PERC ,                          KC_CIRC ,KC_AMPR ,KC_ASTR ,KC_LPRN ,KC_RPRN ,
  //├────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┤
     KC_GRV  ,KC_PLUS ,KC_LBRC ,KC_RBRC ,K_LT_OB ,                          KC_MINS ,OS_ALT  ,OS_CTRL ,OS_GUI  ,KC_PIPE ,
  //├────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┤
     K_SNEK  ,KC_EQL  ,KC_LCBR ,KC_RCBR ,K_LT_CB ,                          KC_UNDS ,KC_QUOT ,KC_DQT  ,K_EURO  ,KC_BSLS ,
  //└────────┴────────┴────────┴────┬───┴────┬───┼────────┐       ┌────────┼───┬────┴───┬────┴────────┴────────┴────────┘
                                     _______ ,    _______ ,        _______ ,    _______
  //                                └────────┘   └────────┘       └────────┘   └────────┘
  ),

  [_NAV] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┐                         ┌────────┬────────┬────────┬────────┬────────┐
     KC_TILDE,L_MOUSE ,OS_FUNC ,OS_MISC ,OS_TMUX ,                          K_LT_A  ,K_LT_C  ,K_LT_E1 ,K_LT_E2 ,K_LT_I  ,
  //├────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┤
     KC_TAB  ,OS_GUI  ,OS_CTRL ,OS_ALT  ,KC_ENT  ,                          KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RIGHT,KC_END  ,
  //├────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┤
     KC_DELT ,KC_BSPC ,KC_ESC  ,KC_PGDN ,KC_PGUP ,                          KC_HOME ,K_LT_S  ,K_LT_U1 ,K_LT_U2 ,K_LT_Z  ,
  //└────────┴────────┴────────┴────┬───┴────┬───┼────────┐       ┌────────┼───┬────┴───┬────┴────────┴────────┴────────┘
                                     _______ ,    _______ ,        _______ ,    _______
  //                                └────────┘   └────────┘       └────────┘   └────────┘
  ),

  [_NUMB] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┐                         ┌────────┬────────┬────────┬────────┬────────┐
     KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,                          XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┤
     KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,                          XXXXXXX ,OS_ALT  ,OS_CTRL ,OS_GUI  ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┤
     KC_DELT ,KC_BSPC ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                          XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //└────────┴────────┴────────┴────┬───┴────┬───┼────────┐       ┌────────┼───┬────┴───┬────┴────────┴────────┴────────┘
                                     _______ ,    _______ ,        _______ ,    _______
  //                                └────────┘   └────────┘       └────────┘   └────────┘
  ),

  [_TMUX] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┐                         ┌────────┬────────┬────────┬────────┬────────┐
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                          XXXXXXX ,TM_URL  ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                          TM_LEFT ,TM_NEXT ,TM_PREV ,TM_RIGHT,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                          TM_NEW  ,TM_SLCT ,XXXXXXX ,XXXXXXX ,TM_SRCH ,
  //└────────┴────────┴────────┴────┬───┴────┬───┼────────┐       ┌────────┼───┬────┴───┬────┴────────┴────────┴────────┘
                                     XXXXXXX ,    XXXXXXX ,        XXXXXXX ,    XXXXXXX
  //                                └────────┘   └────────┘       └────────┘   └────────┘
  ),

  [_MOUSE] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┐                         ┌────────┬────────┬────────┬────────┬────────┐
     XXXXXXX ,L_MOUSE ,KC_MS_U ,KC_BTN3 ,KC_WH_U ,                          XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,KC_MS_L ,KC_MS_D ,KC_MS_R ,KC_WH_D ,                          XXXXXXX ,KC_LALT ,KC_LCTL ,KC_LGUI ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,KC_ESC  ,XXXXXXX ,XXXXXXX ,                          XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //└────────┴────────┴────────┴────┬───┴────┬───┼────────┐       ┌────────┼───┬────┴───┬────┴────────┴────────┴────────┘
                                     KC_BTN1 ,    KC_BTN2 ,        XXXXXXX ,    XXXXXXX
  //                                └────────┘   └────────┘       └────────┘   └────────┘
  ),

  [_MISC] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┐                         ┌────────┬────────┬────────┬────────┬────────┐
     RESET   ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                          KC_BRID ,KC_BRIU ,XXXXXXX ,KC_PSCR ,K_PRINT ,
  //├────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,DEBUG   ,XXXXXXX ,XXXXXXX ,                          KC_MPRV ,KC_MPLY ,XXXXXXX ,KC_MNXT ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                          KC_VOLD ,KC_VOLU ,XXXXXXX ,XXXXXXX ,UC_MOD  ,
  //└────────┴────────┴────────┴────┬───┴────┬───┼────────┐       ┌────────┼───┬────┴───┬────┴────────┴────────┴────────┘
                                     XXXXXXX ,    XXXXXXX ,        XXXXXXX ,    XXXXXXX
  //                                └────────┘   └────────┘       └────────┘   └────────┘
  ),

  [_FUNC] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┐                         ┌────────┬────────┬────────┬────────┬────────┐
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                          KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,
  //├────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                          KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,
  //├────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                          KC_F11  ,KC_F12  ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //└────────┴────────┴────────┴────┬───┴────┬───┼────────┐       ┌────────┼───┬────┴───┬────┴────────┴────────┴────────┘
                                     XXXXXXX ,    XXXXXXX ,        XXXXXXX ,    XXXXXXX
  //                                └────────┘   └────────┘       └────────┘   └────────┘
  ),
};

#define TMUX_PREFIX SS_DOWN(X_LCTL) "b" SS_UP(X_LCTL)

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case L_SYM:
    case L_NAV:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_layer_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case L_SYM:
    case L_NAV:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case L_SYM:
    case L_NAV:
    case OS_CTRL:
    case OS_ALT:
    case OS_GUI:
    case OS_TMUX:
    case OS_MISC:
    case KC_LSFT:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_mod_key(uint16_t keycode) {
    switch (keycode) {
    case OS_CTRL:
    case OS_ALT:
    case OS_GUI:
        return true;
    default:
        return false;
    }
}

oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;
oneshot_state os_tmux_state = os_up_unqueued;
oneshot_state os_misc_state = os_up_unqueued;
oneshot_state os_func_state = os_up_unqueued;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    update_oneshot(
        &os_ctrl_state, KC_LCTL, OS_CTRL,
        keycode, record
    );
    update_oneshot(
        &os_alt_state, KC_LALT, OS_ALT,
        keycode, record
    );
    update_oneshot(
        &os_cmd_state, KC_LGUI, OS_GUI,
        keycode, record
    );

    bool handled = true;
    handled = update_oneshot_layer(
        &os_tmux_state, _TMUX, OS_TMUX,
        keycode, record
    ) & handled;

    handled = update_oneshot_layer(
        &os_misc_state, _MISC, OS_MISC,
        keycode, record
    ) & handled;

    handled = update_oneshot_layer(
        &os_func_state, _FUNC, OS_FUNC,
        keycode, record
    ) & handled;
    if (!handled) return false;

    switch (keycode) {
        case TM_LEFT:
            if (!record->event.pressed) return true;
            SEND_STRING(TMUX_PREFIX "<");
            return false;
        case TM_RIGHT:
            if (!record->event.pressed) return true;
            SEND_STRING(TMUX_PREFIX ">");
            return false;
        case TM_NEXT:
            if (!record->event.pressed) return true;
            SEND_STRING(TMUX_PREFIX "n");
            return false;
        case TM_PREV:
            if (!record->event.pressed) return true;
            SEND_STRING(TMUX_PREFIX "p");
            return false;
        case TM_NEW:
            if (!record->event.pressed) return true;
            SEND_STRING(TMUX_PREFIX "c");
            return false;
        case TM_SLCT:
            if (!record->event.pressed) return true;
            SEND_STRING(TMUX_PREFIX "[");
            return false;
        case TM_SRCH:
            if (!record->event.pressed) return true;
            SEND_STRING(TMUX_PREFIX "\t");
            return false;
        case TM_URL:
            if (!record->event.pressed) return true;
            SEND_STRING(TMUX_PREFIX SS_LCTL("u"));
            return false;
    }
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _SYM, _NAV, _NUMB);
}

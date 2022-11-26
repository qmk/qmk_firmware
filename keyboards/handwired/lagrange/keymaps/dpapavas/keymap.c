/* Copyright 2020 Dimitris Papavasiliou <dpapavas@protonmail.ch>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

#define CAPS_SFT MT(MOD_LSFT, KC_CAPS)
#define QUOT_SFT MT(MOD_RSFT, KC_QUOT)
#define PSCR_SFT MT(MOD_LSFT, KC_PSCR)
#define PAUSE_SFT MT(MOD_RSFT, KC_PAUSE)
#define F_SFT MT(MOD_LSFT, KC_F)
#define J_SFT MT(MOD_RSFT, KC_J)
#define PGUP_GUI MT(MOD_LGUI, KC_PGUP)
#define END_GUI MT(MOD_LGUI, KC_END)
#define UP_GUI MT(MOD_RGUI, KC_UP)
#define LEFT_GUI MT(MOD_RGUI, KC_LEFT)
#define EQL_CTL MT(MOD_RCTL, KC_EQL)
#define MINS_CTL MT(MOD_LCTL, KC_MINS)
#define BSPC_ALT LALT_T(KC_BSPC)
#define ENT_ALT LALT_T(KC_ENT)
#define SPC_ALT RALT_T(KC_SPC)
#define DEL_ALT RALT_T(KC_DEL)

enum tapdance_keycodes {
    TD_LEFT,
    TD_RGHT,
    TD_C_X
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
                           /* Left hand */                                                                                       /* Right hand */

        KC_GRV,   KC_1,    KC_2,    KC_3,     KC_4,     KC_5,                                                   KC_6,    KC_7,    KC_8,     KC_9,     KC_0,    KC_ESC,
        KC_TAB,   KC_Q,    KC_W,    KC_E,     KC_R,     KC_T,                                                   KC_Y,    KC_U,    KC_I,     KC_O,     KC_P,    KC_BSLS,
        CAPS_SFT, KC_A,    KC_S,    KC_D,     F_SFT,    KC_G,                                                   KC_H,    J_SFT,   KC_K,     KC_L,     KC_SCLN, QUOT_SFT,
        PSCR_SFT, KC_Z,    KC_X,    KC_C,     KC_V,     KC_B,                                                   KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_SLSH, PAUSE_SFT,

        TD(TD_LEFT),       KC_INS,  KC_LBRC, MINS_CTL, BSPC_ALT, DEL_ALT, TD(TD_C_X),   TD(TD_C_X), ENT_ALT,  SPC_ALT,  EQL_CTL, KC_RBRC, KC_DEL,          TD(TD_RGHT),
                                             KC_HOME,  PGUP_GUI, END_GUI,                           LEFT_GUI, UP_GUI,   KC_RGHT,
                                                       KC_PGDN,                                               KC_DOWN
        ),

  [1] = LAYOUT(
                          /* Left hand */                                                                        /* Right hand */

        KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_F11,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_F12,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

        KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, QK_BOOT, QK_BOOT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
                                            KC_TRNS, KC_TRNS, KC_TRNS,                 KC_TRNS, KC_TRNS, KC_TRNS,
                                                     KC_TRNS,                                   KC_TRNS
        ),
};

/* The following helper macros define tap dances that support
 * separated press, release, tap and double-tap functions. */

#define STEPS(DANCE) [DANCE] = ACTION_TAP_DANCE_FN_ADVANCED(            \
        NULL,                                                           \
        dance_ ## DANCE ## _finished,                                   \
        dance_ ## DANCE ## _reset)

#define CHOREOGRAPH(DANCE, PRESS, RELEASE, TAP, DOUBLETAP)              \
    static bool dance_ ## DANCE ## _pressed;                            \
                                                                        \
    void dance_ ## DANCE ## _finished(qk_tap_dance_state_t *state, void *user_data) { \
        if (state->count == 1) {                                        \
            if (state->pressed) {                                       \
                dance_ ## DANCE ## _pressed = true;                     \
                PRESS;                                                  \
            } else {                                                    \
                TAP;                                                    \
            }                                                           \
        } else if (state->count == 2) {                                 \
            if (!state->pressed) {                                      \
                DOUBLETAP;                                              \
            }                                                           \
        }                                                               \
    }                                                                   \
                                                                        \
    void dance_ ## DANCE ## _reset(qk_tap_dance_state_t *state, void *user_data) { \
        if (state->count == 1) {                                        \
            if (dance_ ## DANCE ## _pressed) {                          \
                RELEASE;                                                \
                dance_ ## DANCE ## _pressed = false;                    \
            }                                                           \
        }                                                               \
    }

/* Define dance for left palm key. */

CHOREOGRAPH(TD_LEFT,
            layer_invert(1),    /* Temporarily toggle layer when held. */
            layer_invert(1),

            /* Press and release both shifts on tap, to change
             * keyboard layout (i.e. language). */

            SEND_STRING(SS_DOWN(X_LSFT) SS_DOWN(X_RSFT)
                        SS_UP(X_LSFT) SS_UP(X_RSFT)),

            layer_invert(1));   /* Toggle layer (permanently) on
                                 * double-tap. */

/* Define dance for right palm key. */

CHOREOGRAPH(TD_RGHT,
            layer_invert(1),    /* Same as above */
            layer_invert(1),
            /* Send a complex macro: C-x C-s Mod-t up.  (Save in
             * Emacs, switch to terminal and recall previous command,
             * hopefully a compile command.) */
            SEND_STRING(SS_DOWN(X_LCTRL) SS_TAP(X_X) SS_TAP(X_S) SS_UP(X_LCTRL)
                        SS_DOWN(X_LGUI) SS_TAP(X_T) SS_UP(X_LGUI) SS_TAP(X_UP)),
            layer_invert(1));

/* This facilitates C-x chords in Emacs.  Used as a modifier along
 * with, say, the s-key, it saves, by sending C-x C-s.  When tapped it
 * just sends C-x. */

CHOREOGRAPH(TD_C_X,
            SEND_STRING(SS_DOWN(X_LCTRL) SS_TAP(X_X)),
            SEND_STRING(SS_UP(X_LCTRL)),
            SEND_STRING(SS_DOWN(X_LCTRL) SS_TAP(X_X) SS_UP(X_LCTRL)),);

qk_tap_dance_action_t tap_dance_actions[] = {
    STEPS(TD_LEFT), STEPS(TD_RGHT), STEPS(TD_C_X)
};

/* Set a longer tapping term for palm keys to allow comfortable
 * permanent layer toggle.  Also set an essentially infinite tapping
 * term for certain mod-tap keys one tends to keep pressed (such as
 * space, backspace, etc.).  This prevents sending the modifier
 * keycode by accident (allowing re-tap to get repeated key-press)
 * and, in combination with permissive hold, they can still be used
 * fine as modifiers. */

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TD(TD_LEFT):
        case TD(TD_RGHT):
             return 250;
        case BSPC_ALT:
        case UP_GUI:
        case LEFT_GUI:
            return 5000;
        default:
            return TAPPING_TERM;
    }
}

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TD(TD_LEFT):
        case TD(TD_RGHT):
        case BSPC_ALT:
        case UP_GUI:
        case LEFT_GUI:
            return true;
        default:
            return false;
    }
}

/* Use the first LED to indicate the active layer. */

layer_state_t layer_state_set_user(layer_state_t state) {
    writePin(D0, (get_highest_layer(state) > 0));

    return state;
}

/* Cycle through the LEDs after initialization. */

void keyboard_post_init_user(void) {
    const pin_t pins[] = {D0, D1, D2};
    uint8_t i, j;

    for (i = 0 ; i < sizeof(pins) / sizeof(pins[0]) + 2 ; i += 1) {
        for (j = 0 ; j < sizeof(pins) / sizeof(pins[0]) ; j += 1) {
            setPinOutput(pins[j]);
            writePin(pins[j], (j == i || j == i - 1));
        }

        wait_ms(100);
    }
}

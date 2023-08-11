/* Copyright 2021 rookiebwoy
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

// Layers declarations
enum layers {
    _BL
};

// Tap Dance declarations
enum {
    TD_PNCT,
    TD_ABC,
    TD_DEF,
    TD_GHI,
    TD_JKL,
    TD_MNO,
    TD_PQRS,
    TD_TUV,
    TD_WXYZ,
    TD_SPACE,
    TD_UPRCS,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap _BL: Base Layer
 * ,-----------------------.
 * |ENTER  | ↑     | BSPC  |
 * |       |       |       |
 * |-------|-------|-------|
 * | <-    | ↓     | ->    |
 * |       |       |       |
 * |-------|-------|-------|
 * | 1 .,' | 2     | 3     |
 * |?!-:;/ | abc   | def   |
 * |-------|-------|-------|
 * | 4     | 5     | 6     |
 * | ghi   | jkl   | mno   |
 * |-------|-------|-------|
 * | 7     | 8     | 9     |
 * | pqrs  | tuv   | wxyz  |
 * |-------|-------|-------|
 * | *     | 0     | CAPS  |
 * |       | space |       |
 * `-----------------------'
 */
  [_BL] = LAYOUT(
    KC_ENT,       KC_UP,        KC_BSPC,
    KC_LEFT,      KC_DOWN,      KC_RIGHT,
    TD(TD_PNCT),  TD(TD_ABC),   TD(TD_DEF),
    TD(TD_GHI),   TD(TD_JKL),   TD(TD_MNO),
    TD(TD_PQRS),  TD(TD_TUV),   TD(TD_WXYZ),
    KC_PAST,      TD(TD_SPACE), TD(TD_UPRCS)
  ),
};

// Tap Dance cycles
void dance_1 (tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return tap_code(KC_DOT);
        else return tap_code(KC_1);
    } else if (state->count == 2) {
        tap_code (KC_COMM);
    } else if (state->count == 3) {
        tap_code(KC_QUOT);
    } else if (state->count == 4) {
        tap_code16(KC_QUES);
    } else if (state->count == 5) {
        tap_code16(KC_EXLM);
    } else if (state->count == 6) {
        tap_code(KC_MINS);
    } else if (state->count == 7) {
        tap_code16(KC_COLN);
    } else if (state->count == 8) {
        tap_code(KC_SCLN);
    } else if (state->count == 9) {
        tap_code(KC_SLSH);
    } else {
        reset_tap_dance (state);
    }
}

void dance_2 (tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return tap_code(KC_A);
        else return tap_code(KC_2);
    } else if (state->count == 2) {
        tap_code (KC_B);
    } else if (state->count == 3) {
        tap_code(KC_C);
    } else {
        reset_tap_dance (state);
    }
}

void dance_3 (tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return tap_code(KC_D);
        else return tap_code(KC_3);
    } else if (state->count == 2) {
        tap_code (KC_E);
    } else if (state->count == 3) {
        tap_code(KC_F);
    } else {
        reset_tap_dance (state);
    }
}

void dance_4 (tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return tap_code(KC_G);
        else return tap_code(KC_4);
    } else if (state->count == 2) {
        tap_code (KC_H);
    } else if (state->count == 3) {
        tap_code(KC_I);
    } else {
        reset_tap_dance (state);
    }
}

void dance_5 (tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return tap_code(KC_J);
        else return tap_code(KC_5);
    } else if (state->count == 2) {
        tap_code (KC_K);
    } else if (state->count == 3) {
        tap_code(KC_L);
    } else {
        reset_tap_dance (state);
    }
}

void dance_6 (tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return tap_code(KC_M);
        else return tap_code(KC_6);
    } else if (state->count == 2) {
        tap_code (KC_N);
    } else if (state->count == 3) {
        tap_code(KC_O);
    } else {
        reset_tap_dance (state);
    }
}

void dance_7 (tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return tap_code(KC_P);
        else return tap_code(KC_7);
    } else if (state->count == 2) {
        tap_code (KC_Q);
    } else if (state->count == 3) {
        tap_code(KC_R);
    } else if (state->count == 4) {
        tap_code(KC_S);
    } else {
        reset_tap_dance (state);
    }
}

void dance_8 (tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return tap_code(KC_T);
        else return tap_code(KC_8);
    } else if (state->count == 2) {
        tap_code (KC_U);
    } else if (state->count == 3) {
        tap_code(KC_V);
    } else {
        reset_tap_dance (state);
    }
}

void dance_9 (tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return tap_code(KC_W);
        else return tap_code(KC_9);
    } else if (state->count == 2) {
        tap_code (KC_X);
    } else if (state->count == 3) {
        tap_code(KC_Y);
    } else if (state->count == 4) {
        tap_code(KC_Z);
    } else {
        reset_tap_dance (state);
    }
}

void dance_0 (tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return tap_code(KC_SPACE);
        else return tap_code(KC_0);
    } else {
        reset_tap_dance (state);
    }
}

void dance_maiusc (tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return set_oneshot_mods(MOD_BIT(KC_LSFT)); 
        else return tap_code(KC_CAPS);
    } else {
        reset_tap_dance (state);
    }
}

// Tap Dance actions
tap_dance_action_t tap_dance_actions[] = {
    [TD_PNCT] = ACTION_TAP_DANCE_FN (dance_1),
    [TD_ABC] = ACTION_TAP_DANCE_FN (dance_2),
    [TD_DEF] = ACTION_TAP_DANCE_FN (dance_3),
    [TD_GHI] = ACTION_TAP_DANCE_FN (dance_4),
    [TD_JKL] = ACTION_TAP_DANCE_FN (dance_5),
    [TD_MNO] = ACTION_TAP_DANCE_FN (dance_6),
    [TD_PQRS] = ACTION_TAP_DANCE_FN (dance_7),
    [TD_TUV] = ACTION_TAP_DANCE_FN (dance_8),
    [TD_WXYZ] = ACTION_TAP_DANCE_FN (dance_9),
    [TD_SPACE] = ACTION_TAP_DANCE_FN (dance_0),
    [TD_UPRCS] = ACTION_TAP_DANCE_FN (dance_maiusc),
};

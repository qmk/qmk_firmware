/* Copyright 2021 @ Victor-Gabriel Savu
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

enum layers{
  MAC_BASE,
  MAC_FN,
  WIN_BASE,
  WIN_FN
};

#define KC_TASK LGUI(KC_TAB)
#define KC_FLXP LGUI(KC_E)

enum unicode_names {
    GRIN,
    SAD,
};

const uint32_t unicode_map[] PROGMEM = {
    [GRIN]  = 0x1F600,  // 😀
    [SAD]   = 0x1F61E,  // 😞
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[MAC_BASE] = LAYOUT_iso_83(
     KC_ESC,             KC_BRID,  KC_BRIU,  KC_F3,    KC_F4,    RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_DEL,   KC_INS,
     KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_PGUP,
     KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,                      KC_PGDN,
     KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_NUHS,  KC_ENT,             KC_HOME,
     KC_LSFT,  KC_NUBS,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,  KC_UP,
     KC_LCTL,  KC_LALT,  KC_LGUI,                                KC_SPC,                                 KC_RGUI, MO(MAC_FN),KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

[MAC_FN] = LAYOUT_iso_83(
     KC_TRNS,            KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_TRNS,  KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
     RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,                      KC_TRNS,
     KC_TRNS,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,  KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_TRNS,                                KC_TRNS,                                KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS),

[WIN_BASE] = LAYOUT_iso_83(
     KC_ESC,             KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_DEL,   UM(SAD),
     KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            UM(GRIN),
     KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,                      KC_PGUP,
     QK_LEAD,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_NUHS,  KC_ENT,             KC_PGDN,
     KC_LSFT,  KC_NUBS,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,  KC_UP,
     KC_LCTL,  KC_LGUI,  KC_LALT,                                KC_SPC,                                 KC_RALT, MO(WIN_FN),KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

[WIN_FN] = LAYOUT_iso_83(
     KC_TRNS,            KC_BRID,  KC_BRIU,  KC_CALC,  KC_FLXP,  RGB_VAD,  RGB_VAI,  KC_TRNS,  KC_PSCR,  KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_MPLY,  KC_TRNS,  KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
     RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,                      KC_TRNS,
     KC_CAPS,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,  KC_PGUP,
     KC_TRNS,  KC_TRNS,  KC_TRNS,                                KC_TRNS,                                KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_HOME,  KC_PGDN,  KC_END)

};

static bool wiggle_mouse;
static uint16_t wiggle_timer;
static uint16_t next_wiggle;

void leader_end_user(void) {
    if (leader_sequence_one_key(QK_LEAD)) {
        tap_code(KC_CAPS);
    }

    if (leader_sequence_four_keys(KC_I, KC_D, KC_L, KC_E)) {
        wiggle_mouse = !wiggle_mouse;
        wiggle_timer = timer_read();
    }

    if (leader_sequence_two_keys(KC_O, KC_K)) {
        send_unicode_string("👍");
    }

    if (leader_sequence_three_keys(KC_S, KC_A, KC_D)) {
        send_unicode_string("😞");
    }

    if (leader_sequence_five_keys(KC_C, KC_H, KC_E, KC_C, KC_K)) {
        send_unicode_string("✅");
    }

    if (leader_sequence_five_keys(KC_C, KC_R, KC_O, KC_S, KC_S)) {
        send_unicode_string("❎");
    }

    if (leader_sequence_five_keys(KC_T, KC_H, KC_A, KC_N, KC_K)) {
        send_unicode_string("🙏");
    }

    if (leader_sequence_five_keys(KC_S, KC_M, KC_I, KC_L, KC_E)) {
        send_unicode_string("😊");
    }

    if (leader_sequence_five_keys(KC_P, KC_A, KC_R, KC_T, KC_Y)) {
        send_unicode_string("🎉");
    }

    if (leader_sequence_four_keys(KC_E, KC_Y, KC_E, KC_S)) {
        send_unicode_string("(ಠ_ಠ)");
    }

    if (leader_sequence_five_keys(KC_M, KC_A, KC_G, KC_I, KC_C)) {
        send_unicode_string("(ಠ_ಠ) 🪄 ⠁⭒*.✫.*⭒⠁");
    }

    if (leader_sequence_five_keys(KC_T, KC_A, KC_B, KC_L, KC_E)) {
        send_unicode_string("(ノಠ痊ಠ)ノ彡┻━┻");
    }

    if (leader_sequence_five_keys(KC_S, KC_H, KC_R, KC_U, KC_G)) {
        send_unicode_string("¯\\_(ツ)_/¯");
    }
}

void matrix_scan_user(void) {
    if (wiggle_mouse && timer_elapsed(wiggle_timer) > next_wiggle) {
        wiggle_timer = timer_read();

        uint8_t rval = TCNT0 + TCNT1 + TCNT3 + TCNT4;
        next_wiggle = rval % 1000;

        if (rval & 1) tap_code(KC_MS_UP);
        if (rval & 2) tap_code(KC_MS_DOWN);
        if (rval & 4) tap_code(KC_MS_LEFT);
        if (rval & 8) tap_code(KC_MS_RIGHT);
    }
}

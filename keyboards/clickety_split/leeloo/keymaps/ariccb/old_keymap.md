/* Copyright 2022 Clickety Split Ltd.
 *                https://clicketysplit.ca
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

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _COLEMAK 0
#define _QWERTY 1
#define _LOWER 2
#define _RAISE 3
#define _FN 4
#define _ADJUST 5

#define MICMUTE LALT(KC_M)
#define DESKTR LGUI(LCTL(KC_RGHT))  // move one virtual desktop to the right
#define DESKTL LGUI(LCTL(KC_LEFT))  // move one virtual desktop to the left
#define LOWF24 LT(_LOWER, KC_F24)
#define HYPER  S(C(A(KC_LGUI)))
#define MTLCTL_F9 MT(MOD_LCTL, KC_9)
#define MTLSFT_F10 MT(MOD_LSFT, KC_F10)
#define MTLALT_F11 MT(MOD_LALT, KC_F11)
#define MTLALT_PDOT MT(MOD_LALT, KC_PDOT)
#define MTLGUI_Z MT(MOD_LGUI, KC_Z)
#define MTLGUI_X MT(MOD_LGUI, KC_X)
#define MTALT_APP MT(MOD_LALT, KC_APP)
#define MTLALT_PL MT(MOD_LALT, KC_MPLY)
#define MTLALT_NXT MT(MOD_LALT, KC_MNXT)
#define MTENTER MT(MOD_LCTL, KC_ENT)
#define MTRSFTBSLS MT(MOD_RSFT, KC_BSLS)
#define MTRCTLQUO MT(MOD_RCTL, KC_QUOT)
#define MTTAB MT(MOD_LCTL | MOD_LGUI | MOD_LALT, KC_TAB)
#define FNESC LT(_FN, KC_ESC)
#define MTPLAY MT(MOD_RALT, KC_MPLY)
#define KC_COPY LCTL(KC_C)
#define KC_CUT LCTL(KC_X)
#define KC_PASTE LCTL(KC_V)
#define KC_WINPASTE LGUI(KC_V)
#define KC_PTXT LCTL(LSFT(KC_V))
#define KC_UNDO LCTL(KC_Z)
#define KC_REDO LCTL(KC_Y)

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  HANDSDOWN,
  COLEMAK,
  LOWER,
  RAISE,
  FN,
  ADJUST,
  NUMPAD,
  GAMING,
  EXT_NUM,
  EXT_GAMING,
  SELWORD,
  BRACES,
  BRACES2,
  ARROW,
  ALT_TAB
};


const uint16_t PROGMEM F1_combo[] = {KC_F2, KC_F9, COMBO_END};
combo_t key_combos[COMBO_COUNT] = {
    COMBO(F1_combo, KC_F1),
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* MIT Layout (COLEMAK-DH)
 * .-----------------------------------------.                                 .-----------------------------------------.
 * |      |      |      |      |      |      |                                 |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                                 |------+------+------+------+------+------|
 * | ESC  |  Q   |  W   |  F   |  P   |  B   |                                 |  J   |  L   |  U   |  Y   |  ;   | BSPC |
 * |------+------+------+------+------+------|                                 |------+------+------+------+------+------|
 * | TAB  |  A   |  R   |  S   |  T   |  G   |--------.               .--------|  M   |  N   |  E   |  I   |  O   |   '  |
 * |------+------+------+------+------+------|        |               |        |------+------+------+------+------+------|
 * | LSFT |  Z   |  X   |  C   |  D   |  V   |--------|               |--------|  K   |  H   |  ,   |  .   |  /   |   \  |
 * .-----------------------------------------/       /                 \       \-----------------------------------------'
 *                |  GUI  |  ENT  |  F24  | /       /                   \       \  |       |  ALT  |       |
 *                |       |       |  LOW  |/  SPC  /                     \  SPC  \ | RAISE |  PLAY |       |
 *                `-------------------------------'                       '--------------------------------'
 */
  [_COLEMAK] = LAYOUT(
  HYPER,   KC_F2,    KC_F9,    KC_F10,  KC_F11,  KC_F12,                       KC_F3,   KC_F4,  KC_F5,     KC_F6,    KC_F7,   KC_F8,
  FNESC,   KC_Q,     KC_W,     KC_F,    KC_P,    KC_B,                         KC_J,    KC_L,   KC_U,    KC_Y,     KC_SCLN, KC_BSPC,
  MTTAB,   KC_A,     KC_R,     KC_S,    KC_T,    KC_G,                         KC_M,    KC_N,   KC_E,    KC_I,     KC_O,    MTRCTLQUO,
  KC_LSFT, KC_Z,     KC_X,     KC_C,    KC_D,    KC_V,   KC_NO,     KC_MPLY,   KC_K,    KC_H,   KC_COMM, KC_DOT,   KC_SLSH, MTRSFTBSLS,
                               KC_LGUI, MTENTER, LOWF24, KC_SPC,    MTALT_APP, KC_SPC,  MO(3),  KC_NO
),


/* MIT Layout (QWERTY)
 * .-----------------------------------------.                                 .-----------------------------------------.
 * |      |      |      |      |      |      |                                 |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                                 |------+------+------+------+------+------|
 * | ESC  |  Q   |  W   |  E   |  R   |  T   |                                 |  Y   |  U   |  I   |  O   |  P   | BSPC |
 * |------+------+------+------+------+------|                                 |------+------+------+------+------+------|
 * | TAB  |  A   |  S   |  D   |  F   |  G   |--------.               .--------|  H   |  J   |  K   |  L   |  ;   |   '  |
 * |------+------+------+------+------+------|        |               |        |------+------+------+------+------+------|
 * | LSFT |  Z   |  X   |  C   |  V   |  B   |--------|               |--------|  N   |  M   |  ,   |  .   |  /   |   \  |
 * .-----------------------------------------/       /                 \       \-----------------------------------------'
 *                |  GUI  |  ENT  |  F24  | /       /                   \       \  |       |  ALT  |       |
 *                |       |       |  LOW  |/  SPC  /                     \  SPC  \ | RAISE |  PLAY |       |
 *                `-------------------------------'                       '--------------------------------'
 */
  [_QWERTY] = LAYOUT(
  KC_NO,   KC_NO,    KC_NO,    KC_NO,   KC_NO,   KC_NO,                        KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,   KC_NO,
  FNESC,   KC_Q,     KC_W,     KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,     KC_P,    KC_BSPC,
  MTTAB,   KC_A,     KC_S,     KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L,     KC_SCLN, MTRCTLQUO,
  KC_LSFT, KC_Z,     KC_X,     KC_C,    KC_V,    KC_B,    KC_NO,      KC_NO,   KC_N,    KC_M,    KC_COMM, KC_DOT,   KC_SLSH, MTRSFTBSLS,
                               _______, _______, _______, _______,    _______, _______, _______, _______
),

/* MIT Layout (LOWER)
 * .-----------------------------------------.                                 .-----------------------------------------.
 * |      |      |      |      |      |      |                                 |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                                 |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                                 |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                                 |------+------+------+------+------+------|
 * |      |      |      |      |      |      |--------.               .--------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|        |               |        |------+------+------+------+------+------|
 * |      |      |      |      |      |      |--------|               |--------|      |      |      |      |      |      |
 * .-----------------------------------------/       /                 \       \-----------------------------------------'
 *                |       |       |       | /       /                   \       \  |       |       |       |
 *                |       |       |       |/       /                     \       \ |       |       |       |
 *                `-------------------------------'                       '--------------------------------'
 */
  [_LOWER] = LAYOUT(
  KC_NO,     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                            KC_NO,   KC_NO,       KC_NO,   KC_NO,    KC_NO,   KC_NO,
  KC_GRV,    KC_EXLM, KC_HASH, KC_DLR,  KC_LBRC, KC_RBRC,                          KC_COLN, KC_P7,       KC_P8,   KC_P9,    KC_EQL,  KC_BSPC,
  S(KC_TAB), KC_TILD, KC_CIRC, KC_PERC, KC_LPRN, KC_RPRN,                          KC_M,    KC_P4,       KC_P5,   KC_P6,    KC_PMNS, KC_PPLS,
  KC_TRNS,   KC_PIPE, KC_AMPR, KC_DQUO, KC_LCBR, KC_RCBR, KC_NO,      KC_NO,       KC_AT,   KC_P1,       KC_P2,   KC_P3,    KC_PSLS, KC_PAST,
                               _______, _______, _______, _______,    MTLALT_PDOT, KC_P0,   MTLALT_PDOT, KC_NO
),

/* MIT Layout (RAISE)
 * .-----------------------------------------.                                 .-----------------------------------------.
 * |      |      |      |      |      |      |                                 |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                                 |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                                 |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                                 |------+------+------+------+------+------|
 * |      |      |      |      |      |      |--------.               .--------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|        |               |        |------+------+------+------+------+------|
 * |      |      |      |      |      |      |--------|               |--------|      |      |      |      |      |      |
 * .-----------------------------------------/       /                 \       \-----------------------------------------'
 *                |       |       |       | /       /                   \       \  |       |       |       |
 *                |       |       |       |/       /                     \       \ |       |       |       |
 *                `-------------------------------'                       '--------------------------------'
 */
  [_RAISE] = LAYOUT(
  KC_NO,   KC_NO,    KC_NO,    KC_NO,   KC_NO,   KC_NO,                        KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,       KC_NO,
  KC_TRNS, KC_EXLM,  KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,                      KC_TRNS, KC_CUT,  KC_UNDO, KC_REDO,  KC_EQL,      KC_BSPC,
  KC_TRNS, KC_NO,    KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,                      ARROW,   SELWORD, KC_COPY, KC_PASTE, KC_WINPASTE, KC_DQUO,
  KC_TRNS, KC_VOLD,  KC_VOLU, KC_MUTE,  KC_TRNS, KC_TRNS, KC_NO,      KC_NO,   BRACES,  BRACES2, KC_LABK, KC_RABK,  KC_QUES,     KC_PIPE,
                              _______,  _______, MO(5),   _______,    _______, _______, _______, _______
),

/* MIT Layout (FN)
 * .-----------------------------------------.                                 .-----------------------------------------.
 * |      |      |      |      |      |      |                                 |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                                 |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                                 |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                                 |------+------+------+------+------+------|
 * |      |      |      |      |      |      |--------.               .--------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|        |               |        |------+------+------+------+------+------|
 * |      |      |      |      |      |      |--------|               |--------|      |      |      |      |      |      |
 * .-----------------------------------------/       /                 \       \-----------------------------------------'
 *                |       |       |       | /       /                   \       \  |       |       |       |
 *                |       |       |       |/       /                     \       \ |       |       |       |
 *                `-------------------------------'                       '--------------------------------'
 */
  [_FN] = LAYOUT(
  KC_NO,   DESKTL,    DESKTR,     KC_NO,      KC_NO,   KC_NO,                           KC_NO,   KC_NO,   KC_NO,        KC_NO,   KC_NO,    KC_NO,
  KC_TRNS, MTLCTL_F9, MTLSFT_F10, MTLALT_F11, KC_F12,  KC_MYCM,                         KC_CALC, KC_HOME, KC_UP,        KC_END,  KC_PSCR,  KC_DEL,
  KC_TRNS, KC_F5,     KC_F6,      KC_F7,      KC_F8,   DESKTL,                          DESKTR,  KC_LEFT, KC_DOWN,      KC_RGHT, KC_SLCK,  KC_CAPS,
  KC_TRNS, KC_F1,     KC_F2,      KC_F3,      KC_F4,   ALT_TAB, KC_NO,      MTLALT_NXT, MICMUTE, KC_PGUP, LCA(KC_DOWN), KC_PGDN, KC_PAUSE, KC_INS,
                                  _______,    _______, _______, _______,    _______,    _______, _______, _______
),

/* MIT Layout (ADJUST)
 * .-----------------------------------------.                                 .-----------------------------------------.
 * |      |      |      |      |      |      |                                 |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                                 |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                                 |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                                 |------+------+------+------+------+------|
 * |      |      |      |      |      |      |--------.               .--------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|        |               |        |------+------+------+------+------+------|
 * |      |      |      |      |      |      |--------|               |--------|      |      |      |      |      |      |
 * .-----------------------------------------/       /                 \       \-----------------------------------------'
 *                |       |       |       | /       /                   \       \  |       |       |       |
 *                |       |       |       |/       /                     \       \ |       |       |       |
 *                `-------------------------------'                       '--------------------------------'
 */
  [_ADJUST] = LAYOUT(
  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                        KC_NO,     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  FNESC,   KC_BTN3, KC_BTN2, KC_MS_U, KC_BTN1, RGB_HUI,                      RGB_HUD,   AU_ON,   AU_OFF,  KC_TRNS, KC_TRNS, RESET,
  KC_TRNS, KC_NO,   KC_MS_L, KC_MS_D, KC_MS_R, GAMING,                       HANDSDOWN, KC_BTN1, KC_BTN2, KC_BTN3, KC_TRNS, RGB_TOG,
  KC_TRNS, KC_WH_L, KC_WH_U, KC_WH_D, KC_WH_R, QWERTY,  KC_NO,      KC_NO,   COLEMAK,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, DEBUG,
                             _______, _______, _______, _______,    _______, _______,   _______, KC_NUM
)
};

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {

    if (index == 0) {
        switch (biton32(layer_state)) {
            case _QWERTY:
                // Volume Up / Volume Down
                if (clockwise) {
                    tap_code(KC_VOLD);
                } else {
                    tap_code(KC_VOLU);
                }
                break;
            case _LOWER:
                // Zoom In / Zoom Out
                if (clockwise) {
                    tap_code16(C(KC_MINS));
                } else {
                    tap_code16(C(KC_EQL));
                }
                break;
            case _RAISE:
                // Volume control
                if (clockwise) {
                    tap_code(KC_LBRC);
                } else {
                    tap_code(KC_RBRC);
                }
                break;
            case _ADJUST:
                // Volume Up / Volume Down
                if (clockwise) {
                    tap_code(KC_VOLD);
                } else {
                    tap_code(KC_VOLU);
                }
                break;
            default:
                // Volume Up / Volume Down
                if (clockwise) {
                    tap_code(KC_VOLD);
                } else {
                    tap_code(KC_VOLU);
                }
                break;
        }

    } else if (index == 1) {
        switch (biton32(layer_state)) {
            case _QWERTY:
                // Down / Up
                if (clockwise) {
                    tap_code(KC_DOWN);
                } else {
                    tap_code(KC_UP);
                }
                break;
            case _LOWER:
                // Right / Left
                if (clockwise) {
                    tap_code(KC_RIGHT);
                } else {
                    tap_code(KC_LEFT);
                }
                break;
            case _RAISE:
                // Page Down/Page Up
                if (clockwise) {
                    tap_code(KC_PGDN);
                } else {
                    tap_code(KC_PGUP);
                }
                break;
            case _ADJUST:
                // Page up/Page down
                if (clockwise) {
                    tap_code(KC_PGDN);
                } else {
                    tap_code(KC_PGUP);
                }
                break;
            default:
                // Page up/Page down
                if (clockwise) {
                    tap_code(KC_PGDN);
                } else {
                    tap_code(KC_PGUP);
                }
                break;
        }
    }

    return false;

}
#endif

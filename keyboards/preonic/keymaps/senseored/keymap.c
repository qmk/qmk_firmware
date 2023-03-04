/* Copyright 2015-2017 Jack Humbert
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

enum preonic_layers {
  _QWERTY,
  _FNL1,
  _LOWER,
  _RAISE,
  _FNL2,
  _ADJUST,
  _GAMEMODE,
  _FNL3,
  _LOWER2,
  _RAISE2
};

enum preonic_keycodes {
  TBMACRO = SAFE_RANGE,
  DGRMCRO,
  WRKMOD,
  BACKLIT,
  RAISE,
  LOWER
};

bool bnumlock = false;
bool numlock_changed = false;
bool workmode = true;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  Tab |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |   [  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | FNL1 |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |   "  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  | Alt  | Bksp |Lower |    Space    |Raise | Bksp | AltGr|   *  | Esc  |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_preonic_grid(
  KC_GRV,     KC_1,    KC_2,    KC_3,       KC_4,   KC_5,   KC_6,       KC_7,    KC_8,   KC_9,     KC_0,  KC_BSPC,
  KC_TAB,     KC_Q,    KC_W,    KC_E,       KC_R,   KC_T,   KC_Y,       KC_U,    KC_I,   KC_O,     KC_P,  KC_LBRC,
  TT(_FNL1),  KC_A,    KC_S,    KC_D,       KC_F,   KC_G,   KC_H,       KC_J,    KC_K,   KC_L,  KC_SCLN,  KC_QUOT,
  KC_LSFT,    KC_Z,    KC_X,    KC_C,       KC_V,   KC_B,   KC_N,       KC_M, KC_COMM, KC_DOT,  KC_SLSH,  KC_ENT,
  KC_LCTL, KC_LGUI, KC_LALT,  KC_DEL, TT(_LOWER), KC_SPC, KC_SPC, TT(_RAISE), KC_BSPC, KC_RALT, KC_NUHS,  KC_ESC
),

/* FNL1
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |TbMacr| Prev | Play | Next | AltF4| CapsL| Esc  | PgUp |  Up  | PgDn |PrScrn| Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      | Vol- | Vol+ | Mute | NumL | Home | Left | Down | Right|      |  Del |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      | End  |      |      |      |   ?  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |   !  |      |
 * `-----------------------------------------------------------------------------------'
 */
[_FNL1] = LAYOUT_preonic_grid(
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  TBMACRO, KC_MPRV, KC_MPLY, KC_MNXT,  ALT_F4, KC_CAPS,  KC_ESC, KC_PGUP,   KC_UP, KC_PGDN, KC_PSCR, KC_BSPC,
  TT(_FNL1), _______, KC_VOLD, KC_VOLU, KC_MUTE, KC_NUM, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, _______,  KC_DEL,
  KC_LSFT,    CTLZ,    CTLX,    CTLC,    CTLV, _______,  KC_END, _______, _______, _______, LSFT(KC_MINS), _______,
  _______, _______, CTALDEL, _______, _______, _______, _______, _______, _______, _______, LSFT(KC_1), _______
),


/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   §  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |   +  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |   ´  |   `  |   @  |   £  |   $  |   €  |   ¨  |   {  |   [  |   ]  |   }  |   \  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   <  |   |  |   >  |   °  |      |      |   µ  |   ¨  |   ^  |   ~  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      | AltGr|      |      |             |      |      |      |      | BAIL |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_preonic_grid(
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_GRV,    KC_1,          KC_2,       KC_3,    KC_4,      KC_5,  KC_6,         KC_7,      KC_8,        KC_9,          KC_0,       KC_MINS,
  KC_EQL, S(KC_EQL),   RALT(KC_2), RALT(KC_3), RALT(KC_4), RALT(KC_E), KC_RBRC, RALT(KC_7), RALT(KC_8), RALT(KC_9),    RALT(KC_0), RALT(KC_MINS),
  KC_LSFT, KC_NUBS, RALT(KC_NUBS), S(KC_NUBS), DGRMCRO, XXXXXXX, XXXXXXX,   RALT(KC_M),   KC_RBRC,  S(KC_RBRC), RALT(KC_RBRC),       _______,
  _______, _______,       KC_RALT,    _______,TO(_ADJUST), _______, _______,      _______,   _______,     _______,       _______, TO(_QWERTY)
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |  Tab |  F1  |  F2  |  F3  |  F4  |  Esc | Bksp |   /  |   7  |   8  |   9  |   -  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | FNL2 |  F5  |  F6  |  F7  |  F8  |Insert| Home | PgUp |   4  |   5  |   6  |   +  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F9  |  F10 |  F11 |  F12 |  Del | End  | PgDn |   1  |   2  |   3  | Enter|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |  Alt |      |      |             |   *  |   0  |   ,  |   .  | BAIL |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_preonic_grid(
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  KC_TAB,    KC_F1,   KC_F2,   KC_F3,   KC_F4,  KC_ESC, KC_BSPC, KC_PSLS,  KC_P7,  KC_P8,  KC_P9, KC_PMNS,
  TT(_FNL2), KC_F5,   KC_F6,   KC_F7,   KC_F8,  KC_INS, KC_HOME, KC_PGUP,  KC_P4,  KC_P5,  KC_P6, KC_PPLS,
  KC_LSFT,   KC_F9,  KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_END, KC_PGDN,  KC_P1,  KC_P2,  KC_P3, KC_PENT,
  _______, _______, KC_LALT, _______, TO(_QWERTY), _______, _______, KC_PAST,  KC_P0,  KC_PDOT, KC_DOT, TO(_QWERTY)
),

/* FNL2
 * ,-----------------------------------------------------------------------------------.
 * |TbMacr| Prev | Play | Next | AltF4| CapsL|      |PrScrn|Insert| Home | PgUp |ScrLck|
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      | Vol- | Vol+ | Mute | NumL |      |      |  Del | End  | PgDn | Pause|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |  Up  |      | Enter|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Left | Down | Right| BAIL |
 * `-----------------------------------------------------------------------------------'
 */
[_FNL2] = LAYOUT_preonic_grid(
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  TBMACRO, KC_MPRV, KC_MPLY, KC_MNXT,  ALT_F4, KC_CAPS, _______, KC_PSCR,  KC_INS, KC_HOME, KC_PGUP, KC_SCRL,
  _______, _______, KC_VOLD, KC_VOLU, KC_MUTE, KC_NUM,  _______, _______,  KC_DEL,  KC_END, KC_PGDN, KC_PAUS,
  _______,    CTLZ,    CTLX,    CTLC,    CTLV, _______, _______, _______, _______,   KC_UP, _______, KC_ENT,
  _______, _______, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, TO(_QWERTY)
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | GAME | Reset|      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|AudOff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|MusOff|MidiOn|MidOff|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      | BAIL |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_preonic_grid(
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  TO(_GAMEMODE), QK_BOOT, DB_TOGG, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL,
  _______, _______, MU_NEXT, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, _______, _______, _______, _______, _______,
  _______, AU_PREV, AU_NEXT, MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, TO(_QWERTY)
),


/* Game mode
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  Tab |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |   [  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | FNL1 |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |   "  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |   1  | Lower| Bksp | Alt  |    Space    | Raise| Bksp | BAIL |   *  | Esc  |
 * `-----------------------------------------------------------------------------------'
 */
[_GAMEMODE] = LAYOUT_preonic_grid(
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_TAB,     KC_Q,    KC_W,    KC_E,       KC_R,   KC_T,   KC_Y,       KC_U,    KC_I,   KC_O,     KC_P,  KC_LBRC,
  TT(_FNL3),  KC_A,    KC_S,    KC_D,       KC_F,   KC_G,   KC_H,       KC_J,    KC_K,   KC_L,  KC_SCLN,  KC_QUOT,
  KC_LSFT,    KC_Z,    KC_X,    KC_C,       KC_V,   KC_B,   KC_N,       KC_M, KC_COMM, KC_DOT,  KC_SLSH,  KC_ENT,
  KC_LCTL, KC_1, MO(_LOWER2),  KC_DEL, KC_LALT, KC_SPC, KC_SPC, MO(_RAISE2), KC_BSPC, TO(_QWERTY), KC_NUHS, KC_ESC
),
/* FNL3
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |TbMacr| Prev | Play | Next | AltF4| CapsL| Esc  | PgUp |  Up  | PgDn |PrScrn| Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      | Vol- | Vol+ | Mute | NumL | Home | Left | Down | Right|      |  Del |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      | End  |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      | BAIL |
 * `-----------------------------------------------------------------------------------'
 */
[_FNL3] = LAYOUT_preonic_grid(
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  TBMACRO, KC_MPRV, KC_MPLY, KC_MNXT,  ALT_F4, KC_CAPS,  KC_ESC, KC_PGUP,   KC_UP, KC_PGDN, KC_PSCR, KC_BSPC,
  _______, _______, KC_VOLD, KC_VOLU, KC_MUTE, KC_NUM,  KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, _______,  KC_DEL,
  KC_LSFT, _______, _______, _______, _______, _______,  KC_END, _______, _______, _______, LSFT(KC_MINS), _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, LSFT(KC_1), _______
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  Tab |  F1  |  F2  |  F3  |  F4  |  Esc | Bksp |   /  |   7  |   8  |   9  |   -  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | FNL2 |  F5  |  F6  |  F7  |  F8  |Insert| Home | PgUp |   4  |   5  |   6  |   +  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F9  |  F10 |  F11 |  F12 |  Del | End  | PgDn |   1  |   2  |   3  | Enter|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |  Alt |      |      |             |   *  |   0  |   ,  |   .  | BAIL |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER2] = LAYOUT_preonic_grid(
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_TAB,    KC_F1,   KC_F2,   KC_F3,   KC_F4,  KC_ESC, KC_BSPC, KC_PSLS,  KC_P7,  KC_P8,  KC_P9, KC_PMNS,
  TT(_FNL2), KC_F5,   KC_F6,   KC_F7,   KC_F8,  KC_INS, KC_HOME, KC_PGUP,  KC_P4,  KC_P5,  KC_P6, KC_PPLS,
  KC_LSFT,   KC_F9,  KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_END, KC_PGDN,  KC_P1,  KC_P2,  KC_P3, KC_PENT,
  _______, _______, _______, _______, _______, _______, _______, KC_PAST,  KC_P0,  KC_PDOT, KC_DOT, TO(_GAMEMODE)
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   §  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |   +  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |   ´  |   `  |   @  |   £  |   $  |   €  |   ¨  |   {  |   [  |   ]  |   }  |   \  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   <  |   |  |   >  |   °  |      |      |   µ  |   ¨  |   ^  |   ~  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      | AltGr|      |      |             |      |      |      |      | BAIL |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE2] = LAYOUT_preonic_grid(
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_GRV,    KC_1,          KC_2,       KC_3,    KC_4,      KC_5,  KC_6,         KC_7,      KC_8,        KC_9,          KC_0,       KC_MINS,
  KC_EQL, S(KC_EQL),   RALT(KC_2), RALT(KC_3), RALT(KC_4), RALT(KC_E), KC_RBRC, RALT(KC_7), RALT(KC_8), RALT(KC_9),    RALT(KC_0), RALT(KC_MINS),
  KC_LSFT, KC_NUBS, RALT(KC_NUBS), S(KC_NUBS), DGRMCRO, XXXXXXX, XXXXXXX,   RALT(KC_M),   KC_RBRC,  S(KC_RBRC), RALT(KC_RBRC),       _______,
  _______, _______,       KC_RALT,    _______, _______, _______, _______,      _______,   _______,     _______,       _______, TO(_GAMEMODE)
)


};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch(keycode) {
            case TBMACRO:
                SEND_STRING(SS_TAP(X_TAB) SS_DOWN(X_LSFT) SS_TAP(X_HOME) SS_UP(X_LSFT) SS_TAP(X_DELETE));
                return false;
            case DGRMCRO:
                if(!bnumlock) {
                    tap_code(KC_NUM_LOCK);
                    bnumlock = true;
                }
                //SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_P0) SS_TAP(X_P1) SS_TAP(X_P7) SS_TAP(X_P6) SS_UP(X_LALT));
                SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_KP_0) SS_TAP(X_KP_1) SS_TAP(X_KP_7) SS_TAP(X_KP_6) SS_UP(X_LALT) );
                return false;

            if(bnumlock) {
                tap_code(KC_NUM_LOCK);
                bnumlock = false;
                }
            case WRKMOD:
                if(!workmode) {
                    workmode = true;
                    return false;
                }
                else {
                    workmode = false;
                    return false;
                }
        }

    }
    return true;
  switch (keycode) {

        case BACKLIT:
          if (record->event.pressed) {
            register_code(KC_RSFT);
            #ifdef BACKLIGHT_ENABLE
              backlight_step();
            #endif
            #ifdef __AVR__
            PORTE &= ~(1<<6);
            #endif
          } else {
            unregister_code(KC_RSFT);
            #ifdef __AVR__
            PORTE |= (1<<6);
            #endif
          }
          return false;
          break;
      }
    return true;
};

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

bool encoder_update_user(uint8_t index, bool clockwise) {
  if (muse_mode) {
    if (IS_LAYER_ON(_RAISE)) {
      if (clockwise) {
        muse_offset++;
      } else {
        muse_offset--;
      }
    } else {
      if (clockwise) {
        muse_tempo+=1;
      } else {
        muse_tempo-=1;
      }
    }
  } else {
    if (clockwise) {
      register_code(KC_PGDN);
      unregister_code(KC_PGDN);
    } else {
      register_code(KC_PGUP);
      unregister_code(KC_PGUP);
    }
  }
    return true;
}

bool dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0:
            if (active) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            break;
        case 1:
            if (active) {
                muse_mode = true;
            } else {
                muse_mode = false;
            }
    }
    return true;
}


layer_state_t layer_state_set_user(layer_state_t state) {
//  if(rgblight_get_mode() == 1) {
    switch (get_highest_layer(state)) {
    case _QWERTY:
        if(bnumlock) {
            tap_code(KC_NUM_LOCK);
        }
        break;
    case _LOWER:
        if(!bnumlock) {
            tap_code(KC_NUM_LOCK);
        }

        break;
    case _ADJUST:
        if(bnumlock) {
                tap_code(KC_NUM_LOCK);
        }
        break;
    case _RAISE:
        if(bnumlock) {
                tap_code(KC_NUM_LOCK);
        }
        break;
    case _FNL1:
        if(bnumlock) {
                tap_code(KC_NUM_LOCK);
        }
        break;
    case _GAMEMODE:
        break;
    default: //  for any other layers, or the default layer
        if(bnumlock) {
                tap_code(KC_NUM_LOCK);
        }

        break;
    }
 // }
  return state;
}

void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    } else {
        if (muse_counter) {
            stop_all_notes();
            muse_counter = 0;
        }
    }
#endif
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    default:
      return true;
  }
}

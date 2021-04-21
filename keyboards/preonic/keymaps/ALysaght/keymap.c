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
 *
 * qmk compile -kb preonic/rev3
 * qmk flash -kb preonic/rev3
 */

#include QMK_KEYBOARD_H
#include "ALysaght.h"
//#include "muse.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |   1  |   2  |   3  |   4  |   5  |  NO  |  NO  |   6  |   7  |   8  |   9  |   0  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |   Q  |   W  |   E  |   R  |   T  |  NO  |  NO  |   Y  |   U  |   I  |   O  |   P  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |A-Shft|S-Ctrl|D-Alt |F-GUI |   G  |  NO  |  NO  |   H  |J-GUI |K-Alt |L-Ctrl|'-Shft|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |   Z  |   X  |   C  |   V  |   B  |  NO  |  NO  |   N  |   M  |   ,  |   .  |   /  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |  NO  |  NO  |LTEsc |LTBksp|LTTab |  NO  |  NO  |LTEnt |LTSpc |LTDel |  NO  |  NO  |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_preonic_grid(
  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,      XXXXXXX, XXXXXXX,   KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
  _________________QWERTY_L1_________________,   XXXXXXX, XXXXXXX,   _________________QWERTY_R1_________________,
  _________________QWERTY_L2_________________,   XXXXXXX, XXXXXXX,   _________________QWERTY_R1_________________,
  _________________QWERTY_L3_________________,   XXXXXXX, XXXXXXX,   _________________QWERTY_R1_________________,
  _________________BASE_LT___________________,   XXXXXXX, XXXXXXX,   _________________BASE_RT___________________
),

/* Final Fantasy XIV
* ,-----------------------------------------------------------------------------------.
* |   1  |   2  |   3  |   4  | LT5  |  NO  |  NO  |   6  |   7  |   8  |   9  |   0  |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |   Q  |   W  |   E  |   R  |   T  |  NO  |  NO  |   Y  |   U  |   I  |   O  |   P  |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |   A  |   S  |   D  |   F  |   G  |  NO  |  NO  |   H  |   J  |   K  |   L  |   '  |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |   Z  |   X  |   C  |   V  |   B  |  NO  |  NO  |   N  |   M  |   ,  |   .  |   /  |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |  NO  |  NO  | Alt  |Shift | GUI  |  NO  |  NO  |Enter |Space | Bksp |  NO  |  NO  |
* `-----------------------------------------------------------------------------------'
 */
[_FFXIV] = LAYOUT_preonic_grid(
  _________________FFXIV_L0__________________, XXXXXXX, XXXXXXX,   _________________FFXIV_R0__________________,
  _________________FFXIV_L1__________________, XXXXXXX, XXXXXXX,   _________________FFXIV_R1__________________,
  _________________FFXIV_L2__________________, XXXXXXX, XXXXXXX,   _________________FFXIV_R2__________________,
  _________________FFXIV_L3__________________, XXXXXXX, XXXXXXX,   _________________FFXIV_R3__________________,
  _________________FFXIV_LT__________________, XXXXXXX, XXXXXXX,   _________________FFXIV_RT__________________
),




/* Navigation layer
* ,-----------------------------------------------------------------------------------.
* |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |NX_HOM|NX_WB |NX_WF |NX_END|
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |Shift | Ctrl | Alt  | GUI  |  NO  |  NO  |  NO  | CAPS | Left | Down |  Up  |Right |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* | Undo | Cut  | Copy |Paste |  NO  |  NO  |  NO  | Ins  | Home | PgDn | PgUp | End  |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |  NO  |  NO  |  NO  |      |  NO  |  NO  |  NO  |Enter |Space |  NO  |  NO  |  NO  |
* `-----------------------------------------------------------------------------------'
*/

[_NAVR] = LAYOUT_preonic_grid(
  _________________BLANK_5___________________, XXXXXXX, XXXXXXX, _________________BLANK_5___________________,
  _________________NAV_L1____________________, XXXXXXX, XXXXXXX, _________________NAV_R1____________________,
  _________________NAV_L2____________________, XXXXXXX, XXXXXXX, _________________NAV_R1____________________,
  _________________NAV_L3____________________, XXXXXXX, XXXXXXX, _________________NAV_R1____________________,
  _________________NAV_LT____________________, XXXXXXX, XXXXXXX, _________________NAV_RT____________________
),

/* SHIFTED Number and Symbol layer
* ,-----------------------------------------------------------------------------------.
* |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |  &   |  *   |  |   |  (   |  )   |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |  $   |  %   |  ^   |  [   |  ]   |  NO  |  NO  |  NO  | GUI  | Alt  | Ctrl |Shift |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |  !   |  @   |  #   |  {   |  }   |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |  NO  |  NO  |  .   |  ;   |  ~   |  NO  |  NO  |      |  NO  |  NO  |  NO  |  NO  |
* `-----------------------------------------------------------------------------------'
*/

[_NSSL] = LAYOUT_preonic_grid(
  _________________BLANK_5___________________, XXXXXXX, XXXXXXX, _________________BLANK_5___________________,
  _________________NSSL_L1___________________, XXXXXXX, XXXXXXX, _________________NSSL_R1___________________,
  _________________NSSL_L2___________________, XXXXXXX, XXXXXXX, _________________NSSL_R2___________________,
  _________________NSSL_L3___________________, XXXXXXX, XXXXXXX, _________________NSSL_R3___________________,
  _________________NSSL_LT___________________, XXXXXXX, XXXXXXX, _________________NSSL_RT___________________
),


/* Number and Symbol layer
* ,-----------------------------------------------------------------------------------.
* |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |  7   |  8   |  9   |  0   |  \   |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |  4   |  5   |  6   |  -   |  =   |  NO  |  NO  |  NO  | GUI  | Alt  | Ctrl |Shift |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |  1   |  2   |  3   |  _   |  +   |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |  NO  |  NO  |  .   |  :   |  `   |  NO  |  NO  |  NO  |      |  NO  |  NO  |  NO  |
* `-----------------------------------------------------------------------------------'
*/
[_NSL] = LAYOUT_preonic_grid(
  _________________BLANK_5___________________, XXXXXXX, XXXXXXX, _________________BLANK_5___________________,
  _________________NSL_L1____________________, XXXXXXX, XXXXXXX, _________________NSL_R1____________________,
  _________________NSL_L2____________________, XXXXXXX, XXXXXXX, _________________NSL_R1____________________,
  _________________NSL_L3____________________, XXXXXXX, XXXXXXX, _________________NSL_R1____________________,
  _________________NSL_LT____________________, XXXXXXX, XXXXXXX, _________________NSL_RT____________________
),


/* MOUSE layer
* ,-----------------------------------------------------------------------------------.
* |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |Shift | Ctrl | Alt  | GUI  |  NO  |  NO  |  NO  |  NO  | MS_L | MS_D | MS_U | MS_R |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  | WH_L | WH_D | WH_U | WH_R |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |  NO  |  NO  |ADJUST|  NO  |      |  NO  |  NO  | BTN1 | BTN2 | BTN3 |  NO  |  NO  |
* `-----------------------------------------------------------------------------------'
*/

[_MOUSE] = LAYOUT_preonic_grid(
  _________________BLANK_5___________________, XXXXXXX, XXXXXXX, _________________BLANK_5___________________,
  _________________MOUSE_L1__________________, XXXXXXX, XXXXXXX, _________________MOUSE_R1__________________,
  _________________MOUSE_L2__________________, XXXXXXX, XXXXXXX, _________________MOUSE_R2__________________,
  _________________MOUSE_L3__________________, XXXXXXX, XXXXXXX, _________________MOUSE_R3__________________,
  _________________MOUSE_LT__________________, XXXXXXX, XXXXXXX, _________________MOUSE_RT__________________
),



/* MEDIA layer
* ,-----------------------------------------------------------------------------------.
* |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |RGBTOG|RGBMOD|RGBHUI|RGBSAI|RGBVAI|
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |Shift | Ctrl | Alt  | GUI  |  NO  |  NO  |  NO  |  NO  | Prev |VolUp |VolDn | Next |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  ??  |  NO  |RGBHUD|RGBSAD|RGBVAD|
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |  NO  |  NO  |      |  NO  |ADJUST|  NO  |  NO  | Stop | Play | Mute |  NO  |  NO  |
* `-----------------------------------------------------------------------------------'
*/

[_MEDIA] = LAYOUT_preonic_grid(
  _________________BLANK_5___________________, XXXXXXX, XXXXXXX, _________________BLANK_5___________________,
  _________________MEDIA_L1__________________, XXXXXXX, XXXXXXX, _________________MEDIA_R1__________________,
  _________________MEDIA_L2__________________, XXXXXXX, XXXXXXX, _________________MEDIA_R2__________________,
  _________________MEDIA_L3__________________, XXXXXXX, XXXXXXX, _________________MEDIA_R3__________________,
  _________________MEDIA_LT__________________, XXXXXXX, XXXXXXX, _________________MEDIA_RT__________________
),


/* FUNCTION layer
* ,-----------------------------------------------------------------------------------.
* |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |
* |------+------+------+------+------+-------------+------+------+------+------+------|
* |GITFET|GITPUL|      |GITREB|      |  NO  |  NO  |      |  F9  | F10  | F11  | F12  |
* |------+------+------+------+------+-------------+------+------+------+------+------|
* |GITADD|GITSTA|GITCOM|GITPUI|GITPUO|  NO  |  NO  |      |  F5  |  F6  |  F7  |  F8  |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |GITBDE|GITBRC|GITCOU|GITCOB|GITBRC|  NO  |  NO  |      |  F1  |  F2  |  F3  |  F4  |
* |------+------+------+------+------+------+------+------+------+------+------+------|
* |  NO  |  NO  |ScrGrb| <-\s |%>%\n |  NO  |  NO  |  NO  |  NO  |      |  NO  |  NO  |
* `-----------------------------------------------------------------------------------'
*/
[_FUNL] = LAYOUT_preonic_grid(
  _________________BLANK_5___________________,   XXXXXXX, XXXXXXX,   _________________BLANK_5___________________,
  _________________FUNC_L1___________________,   XXXXXXX, XXXXXXX,   _________________FUNC_R1___________________,
  _________________FUNC_L2___________________,   XXXXXXX, XXXXXXX,   _________________FUNC_R2___________________,
  _________________FUNC_L3___________________,   XXXXXXX, XXXXXXX,   _________________FUNC_R3___________________,
  _________________FUNC_LT___________________,   XXXXXXX, XXXXXXX,   _________________FUNC_RT___________________
),




/* Adjust (_MOUSE + _MEDIA)
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Reset |Debug |      |      |      |      |      |TermOf|TermOn|      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |FFXIV |Qwerty|      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_preonic_grid(
  _________________BLANK_5___________________,   XXXXXXX, XXXXXXX,   _________________BLANK_5___________________,
  _________________DRAGO_L1__________________,   XXXXXXX, XXXXXXX,   _________________DRAGO_R1__________________,
  _________________DRAGO_L2__________________,   XXXXXXX, XXXXXXX,   _________________DRAGO_R2__________________,
  _________________DRAGO_L3__________________,   XXXXXXX, XXXXXXX,   _________________DRAGO_R3__________________,
  _________________DRAGO_LT__________________,   XXXXXXX, XXXXXXX,   _________________DRAGO_RT__________________
  /*
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, _______,
  RESET,   DEBUG,   XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX,   TERM_ON, TERM_OFF, XXXXXXX, AG_NORM, AG_SWAP,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX,   FFXIV,   QWERTY,   MUV_DE,  MUV_IN,  MU_MOD,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX,   MI_ON,   MU_ON,    AU_ON,   XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, _______, XXXXXXX, _______,   XXXXXXX, XXXXXXX,   MI_OFF,  MU_OFF,   AU_OFF,  XXXXXXX, XXXXXXX
  */
)


};


/*
bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void encoder_update_user(uint8_t index, bool clockwise) {
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
}

void dip_switch_update_user(uint8_t index, bool active) {
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

*/

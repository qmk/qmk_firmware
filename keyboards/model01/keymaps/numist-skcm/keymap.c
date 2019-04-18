/* Copyright 2018 James Laird-Wah
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
#include "keymap_steno.h"

#define DYNAMIC_MACRO_SIZE 256
#define DYNAMIC_MACRO_RANGE SAFE_RANGE
#include "dynamic_macro.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return process_record_dynamic_macro(keycode, record);
}

void matrix_init_user() {
  steno_set_mode(STENO_MODE_GEMINI); // or STENO_MODE_BOLT
}

enum {
  KC_M_FIND,
  KC_M_AGAIN,
  KC_M_UNDO,
  KC_M_CUT,
  KC_M_COPY,
  KC_M_PASTE,
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch (id) {
      case KC_M_FIND:
        return MACRODOWN( D(LGUI), T(F), END );
      case KC_M_AGAIN:
        return MACRODOWN( D(LGUI), T(G), END );
      case KC_M_UNDO:
        return MACRODOWN( D(LGUI), T(Z), END );
      case KC_M_CUT:
        return MACRODOWN( D(LGUI), T(X), END );
      case KC_M_COPY:
        return MACRODOWN( D(LGUI), T(C), END );
      case KC_M_PASTE:
        return MACRODOWN( D(LGUI), T(V), END );
    }

    return MACRO_NONE;
}

/* Keymap */

enum {
  DEF = 0,
  NUM,
  FUN,
  PLV,
};

#define CAG_ESC MT(MOD_LCTL | MOD_LALT | MOD_LGUI, KC_ESC)

#define M_FIND  M(KC_M_FIND)
#define M_AGAIN M(KC_M_AGAIN)
#define M_UNDO  M(KC_M_UNDO)
#define M_CUT   M(KC_M_CUT)
#define M_COPY  M(KC_M_COPY)
#define M_PSTE  M(KC_M_PASTE)

#define M_RECD1 DYN_REC_START1
#define M_STOP1 DYN_REC_STOP
#define M_PLAY1 DYN_MACRO_PLAY1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[DEF] = LAYOUT(
  TG(PLV), KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                      KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , MO(NUM),
  KC_GRV , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_LBRC,    KC_RBRC, KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_EQL ,
  KC_PGUP, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_TAB ,    KC_ENT , KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,
  KC_PGDN, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , CAG_ESC,    KC_BSLS, KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_MINS,
                                         KC_LCTL,                                 KC_RCTL,
                                            KC_LALT,                           KC_SPC ,
                                               KC_LGUI,                     KC_RSFT,
                                                  KC_LSFT,               KC_BSPC,
                                      MO(FUN),                                        MO(FUN)
  ),
[NUM] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                      _______, KC_7   , KC_8   , KC_9   , KC_PMNS, _______,
  _______, _______, _______, _______, _______, _______, _______,    _______, _______, KC_4   , KC_5   , KC_6   , KC_PPLS, _______,
  _______, _______, _______, _______, _______, _______, _______,    _______, _______, KC_1   , KC_2   , KC_3   , KC_PEQL, _______,
  _______, _______, _______, _______, _______, _______, _______,    _______, _______, KC_0   , KC_DOT , KC_PAST, KC_PSLS, KC_PENT,
                                         _______,                                 _______,
                                            _______,                           _______,
                                               _______,                     _______,
                                                  _______,               _______,
                                      _______,                                        _______
  ),
[FUN] = LAYOUT(
  RESET  , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,                      KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 ,
  _______, M_RECD1, M_STOP1, M_PLAY1, _______, _______, _______,    KC_MPRV, KC_MNXT, KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, KC_F12 ,
  KC_HOME, M_CUT  , M_COPY , M_PSTE , M_FIND , M_AGAIN, M_UNDO ,    KC_MPLY, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, _______, _______,
  KC_END , _______, _______, _______, _______, _______, CAG_ESC,    _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, KC_BSLS, KC_PIPE,
                                         _______,                                 _______,
                                            _______,                           _______,
                                               _______,                     _______,
                                                  _______,               KC_DEL ,
                                      _______,                                        _______
  ),
[PLV] = LAYOUT(
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  STN_N1 , STN_N2 , STN_N3 , STN_N4 , STN_N5 , STN_N6 , XXXXXXX,    XXXXXXX, STN_N7 , STN_N8 , STN_N9 , STN_NA , STN_NB , STN_NC ,
  XXXXXXX, STN_S1 , STN_TL , STN_PL , STN_HL , STN_ST1, XXXXXXX,    XXXXXXX, STN_ST3, STN_FR , STN_PR , STN_LR , STN_TR , STN_DR ,
  XXXXXXX, STN_S2 , STN_KL , STN_WL , STN_RL , STN_ST2, XXXXXXX,    XXXXXXX, STN_ST4, STN_RR , STN_BR , STN_GR , STN_SR , STN_ZR,
                                         XXXXXXX,                                 XXXXXXX,
                                            STN_A  ,                           STN_U  ,
                                               STN_O  ,                     STN_E  ,
                                                  XXXXXXX,               XXXXXXX,
                                      XXXXXXX,                                        XXXXXXX
  )
};

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
#include "keymap_steno.h"

// Custom Keycodes and Combinations Used
#define DEL_SHF SFT_T(KC_DEL)
#define QUAKE LCTL(KC_GRV)

#define WKSP_L LALT(LCTL(KC_LEFT))
#define WKSP_D LALT(LCTL(KC_DOWN))
#define WKSP_U LALT(LCTL(KC_UP))
#define WKSP_R LALT(LCTL(KC_RGHT))

#define AM_CYC A(S(KC_SPC))
#define AM_SHR A(S(KC_COMM))
#define AM_GRW A(S(KC_DOT))
#define AM_REL A(S(KC_Z))
#define AM_LFT A(S(KC_H))
#define AM_RGH A(S(KC_L))
#define AM_CW A(S(KC_K))
#define AM_CCW A(S(KC_J))
#define AM_TLL A(S(KC_1))
#define AM_TLW A(S(KC_2))
#define AM_BSP A(S(KC_3))
#define AM_FUL A(S(KC_4))


extern keymap_config_t keymap_config;

enum planck_layers {
  _BASE,
  _LOWER,
  _RAISE,
  _FUNC,
  _PLOVER,
  _GAME,
  _LNUM,
  _LFUN,
  _ADJUST,
  _MOUSE
};

enum planck_keycodes {
  BASE = SAFE_RANGE,
  PLOVER,
  GAME,
  LNUM,
  LFUN,
  LOWER,
  RAISE,
  FUNC,
  MOUSE,
  ADJUST,
  EXT_PLV,
  EXT_GM
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Base
 * ,-----------------------------------------------------------------------------------.
 * | Tab  | " '  | < ,  | > .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  | ? /  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  | _ -  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |Del/Sf|  : ; |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  | Bspc |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Game | GUI  | Alt  |Lower |Shift |Space |Raise | Alt  | GUI  |  Fn  |Enter |
 * `-----------------------------------------------------------------------------------'
 */
[_BASE] = LAYOUT_planck_grid(
    KC_TAB, KC_QUOT, KC_COMM,  KC_DOT,    KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L, KC_SLSH,
    KC_ESC,    KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S, KC_MINS,
   DEL_SHF, KC_SCLN,    KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z, KC_BSPC,
   KC_LCTL,    GAME, KC_LGUI, KC_LALT,   LOWER,  KC_LSFT,  KC_SPC,  RAISE, KC_RALT, KC_RGUI,    FUNC,  KC_ENT
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |      |AmCycl|AmShrk|AmGrow|AmReld|      |      | Home |PgDwn | PgUp | End  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |AmLeft|AmCcw |AmCw  |AmRght|      |      | Left | Down |  Up  |Right |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |AmTall|AmTllW|AmBsp |AmFull|      |      |WkLeft|WkDown| WkUp |WkRigh|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |Raise |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
   XXXXXXX,  AM_CYC,  AM_SHR,  AM_GRW,  AM_REL, XXXXXXX, XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP,  KC_END, XXXXXXX,
   XXXXXXX,  AM_LFT,  AM_CCW,   AM_CW,  AM_RGH, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, XXXXXXX,
   XXXXXXX,  AM_TLL,  AM_TLW,  AM_BSP,  AM_FUL, XXXXXXX, XXXXXXX,  WKSP_L,  WKSP_D,  WKSP_U,  WKSP_R, XXXXXXX,
   _______, XXXXXXX, _______, _______, _______, _______, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |Quake |   `  |   ~  |   \  |   |  |   (  |   )  |   7  |   8  |   9  |   /  |  =   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   !  |   @  |   #  |   $  |   {  |   }  |   4  |   5  |   6  |   *  |  +   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   %  |   ^  |   &  |   *  |   [  |   ]  |   1  |   2  |   3  |   -  |Bkspc |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |Lower |   <  |   >  |      |   0  |   .  |   ,  |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(
     QUAKE,  KC_GRV, KC_TILD, KC_BSLS, KC_PIPE, KC_LPRN, KC_RPRN,    KC_7,    KC_8,    KC_9, KC_SLSH,  KC_EQL,
   XXXXXXX, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_LCBR, KC_RCBR,    KC_4,    KC_5,    KC_6, KC_ASTR, KC_PLUS,
   XXXXXXX, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LBRC, KC_RBRC,    KC_1,    KC_2,    KC_3, KC_MINS, KC_BSPC,
   _______, XXXXXXX, _______, _______, _______, KC_LABK, KC_RABK, _______,    KC_0,  KC_DOT, KC_COMM, XXXXXXX
),

/* Func
 * ,-----------------------------------------------------------------------------------.
 * |      |Sleep |Prev-W|Ply/Ps|Next-W|      |      |  F9  | F10  | F11  | F12  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      | Wake | Mute | Vol- | Vol+ |      |      |  F5  |  F6  |  F7  |  F8  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Power |Prev-M|Ply/Ps|Next-M|      |      |  F1  |  F2  |  F3  |  F4  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_FUNC] = LAYOUT_planck_grid(
   XXXXXXX, KC_SLEP, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX,   KC_F9,  KC_F10,  KC_F11,  KC_F12, XXXXXXX,
   XXXXXXX, KC_WAKE, KC_MUTE, KC_VOLD, KC_VOLU, XXXXXXX, XXXXXXX,   KC_F5,   KC_F6,   KC_F7,   KC_F8, XXXXXXX,
   XXXXXXX,  KC_PWR, KC_MRWD, KC_MPLY, KC_MFFD, XXXXXXX, XXXXXXX,   KC_F1,   KC_F2,   KC_F3,   KC_F4, XXXXXXX,
   _______, _______, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX
),

/* Game
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |  Q   |  W   |  E   |  H   |  Z   |  I   |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |Shift |  A   |  S   |  D   |  U   |  X   |  P   |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Ctrl |  F   |  G   |  R   |  M   |  C   |  O   |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |  ~   | Alt  |Space |Shift | LNUM | LFUN |      |      |      |      | Exit |
 * `-----------------------------------------------------------------------------------'
 */
[_GAME] = LAYOUT_planck_grid(
    KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_H,    KC_Z,    KC_I, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   KC_LSFT,    KC_A,    KC_S,    KC_D,    KC_U,    KC_X,    KC_P, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   KC_LCTL,    KC_F,    KC_G,    KC_R,    KC_M,    KC_C,    KC_O, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    KC_ESC, KC_TILD, KC_LALT,  KC_SPC, KC_LSFT,    LNUM,    LFUN, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  EXT_GM
),

/* LNum
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |  1   |  2   |  3   |  4   |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |Shift |  5   |  6   |  7   |  8   |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Ctrl |  9   |  10  |  ,   |  .   |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |      | Alt  |Space |Shift |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LNUM] = LAYOUT_planck_grid(
   _______,    KC_1,    KC_2,    KC_3,    KC_4, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   _______,    KC_5,    KC_6,    KC_7,    KC_8, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   _______,    KC_9,    KC_0, KC_COMM,  KC_DOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   _______, XXXXXXX, _______, _______, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),

/* LFun
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |  F1  |  F2  |  F3  |  F4  |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |Shift |  F5  |  F6  |  F7  |  F8  |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Ctrl |  F9  |  F10 |  F11 |  F12 |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |      | Alt  |Space |Shift |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LFUN] = LAYOUT_planck_grid(
   _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   _______,   KC_F5,   KC_F6,   KC_F7,   KC_F8, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   _______,   KC_F9,  KC_F10,  KC_F11,  KC_F12, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   _______, XXXXXXX, _______, _______, _______, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),


/* Mouse (Not Reachable on Planck)
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |Click1|Click3|Click2|      |      |MouseL|MouseD|MouseU|MouseR|      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |Accel0|Accel1|Accel2|      |      |ScrllL|ScrllD|ScrllU|ScrllR|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_MOUSE] = LAYOUT_planck_grid(
   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   XXXXXXX, XXXXXXX, KC_BTN1, KC_BTN3, KC_BTN2, XXXXXXX, XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, XXXXXXX,
   XXXXXXX, XXXXXXX, KC_ACL0, KC_ACL1, KC_ACL2, XXXXXXX, XXXXXXX, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, XXXXXXX,
   _______, _______, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX
),

/* Plover layer (http://opensteno.org)
 * ,-----------------------------------------------------------------------------------.
 * |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |  FN  |   S  |   T  |   P  |   H  |   *  |   *  |   F  |   P  |   L  |   T  |   D  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   S  |   K  |   W  |   R  |   *  |   *  |   R  |   B  |   G  |   S  |   Z  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Exit |      |      |   A  |   O  |      |      |   E  |   U  |  PWR | RES1 | RES2 |
 * `-----------------------------------------------------------------------------------'
 */

[_PLOVER] = LAYOUT_planck_grid(
  STN_N1,  STN_N2,  STN_N3,  STN_N4,  STN_N5,  STN_N6,  STN_N7,  STN_N8,  STN_N9,  STN_NA,  STN_NB,  STN_NC ,
  STN_FN,  STN_S1,  STN_TL,  STN_PL,  STN_HL,  STN_ST1, STN_ST3, STN_FR,  STN_PR,  STN_LR,  STN_TR,  STN_DR ,
  XXXXXXX, STN_S2,  STN_KL,  STN_WL,  STN_RL,  STN_ST2, STN_ST4, STN_RR,  STN_BR,  STN_GR,  STN_SR,  STN_ZR ,
  EXT_PLV, XXXXXXX, XXXXXXX, STN_A,   STN_O,   XXXXXXX, XXXXXXX, STN_E,   STN_U,   STN_PWR, STN_RE1, STN_RE2
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|RGBTog|RGBMod|      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|Light-|Light+|      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
   _______, QK_BOOT, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL ,
   _______, _______, _______,   AU_ON,  AU_OFF, AG_NORM, AG_SWAP, RGB_TOG, RGB_MOD, _______, _______, _______,
   _______, AU_PREV, AU_NEXT,   MU_ON,  MU_OFF,   MI_ON,  MI_OFF, RGB_VAD, RGB_VAI, _______, _______, _______,
   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)

};

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case FUNC:
      if (record->event.pressed) {
        layer_on(_FUNC);
      } else {
        layer_off(_FUNC);
      }
      return false;
      break;
    case PLOVER:
      if (!record->event.pressed) {
        #ifdef AUDIO_ENABLE
          stop_all_notes();
          PLAY_SONG(plover_song);
        #endif
        layer_on(_PLOVER);
      }
      return false;
      break;
    case EXT_PLV:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(plover_gb_song);
        #endif
        layer_off(_PLOVER);
      }
      return false;
      break;
    case GAME:
      if (!record->event.pressed) {
        #ifdef AUDIO_ENABLE
          stop_all_notes();
          PLAY_SONG(plover_song);
        #endif
        layer_on(_GAME);
      }
      return false;
      break;
    case EXT_GM:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(plover_gb_song);
        #endif
        layer_off(_GAME);
      }
      return false;
      break;
    case LNUM:
      if (record->event.pressed) {
        layer_on(_LNUM);
      } else {
        layer_off(_LNUM);
      }
      return false;
      break;
    case LFUN:
      if (record->event.pressed) {
        layer_on(_LFUN);
      } else {
        layer_off(_LFUN);
      }
      return false;
      break;
    case MOUSE:
      if (record->event.pressed) {
        layer_on(_MOUSE);
      } else {
        layer_off(_MOUSE);
      }
      return false;
      break;
  }
  return true;
}

void matrix_init_user() {
  steno_set_mode(STENO_MODE_GEMINI);
}

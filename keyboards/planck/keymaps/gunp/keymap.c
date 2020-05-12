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

/* modified by Gun Pinyo */

#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

enum planck_layers {
  LY_0000, LY_0001, LY_0010, LY_0011,
  LY_0100, LY_0101, LY_0110, LY_0111,
  LY_1000, LY_1001, LY_1010, LY_1011,
  LY_1100, LY_1101, LY_1110, LY_1111,
};

enum planck_keycodes {
  FN_A = SAFE_RANGE,
  FN_B,
  FN_C,
  FN_D,
  DYNAMIC_MACRO_RANGE,
};

#include "dynamic_macro.h"

#define MFN_R1 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define MFN_R2 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define MFN_R3 XXXXXXX, FN_A,    FN_B,    FN_C,    XXXXXXX, XXXXXXX
#define MFN_R4 XXXXXXX, KC_LCTL, KC_LSFT, KC_LALT, FN_D,    XXXXXXX
#define UNUSED_LAYER {\
  {XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, MFN_R1},\
  {XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, MFN_R2},\
  {XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, MFN_R3},\
  {XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, MFN_R4}},
#define MC(kc) LCTL(kc)
#define MA(kc) LALT(kc)
#define MG(kc) LGUI(kc)          // ModGui, for i3 shortcuts
#define MSC(kc) LSFT(LCTL(kc))
#define MSA(kc) LSFT(LALT(kc))
#define MCA(kc) LCTL(LALT(kc))
#define XX XXXXXXX

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[LY_0000] = LAYOUT_planck_grid(
 KC_DEL,  KC_Q, KC_W, KC_F, KC_P, KC_G, KC_J, KC_L, KC_U, KC_Y, KC_K, KC_TAB,
 KC_BSPC, KC_A, KC_R, KC_S, KC_T, KC_D, KC_H, KC_N, KC_E, KC_I, KC_O, KC_ENT,
 KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_M, FN_A, FN_B, FN_C, XX,  KC_LSFT,
 XX,KC_F21,KC_F22,KC_ESC,KC_SPC,KC_F23,KC_F24,KC_LCTL,KC_LSFT,KC_LALT,FN_D,XX
),
[LY_1000] = LAYOUT_planck_grid(
  UC(L'∃'), KC_SLSH,  KC_RCBR,  KC_RPRN,  KC_RBRC,  KC_GT,    MFN_R1,
  UC(L'∀'), KC_BSLS,  KC_LCBR,  KC_LPRN,  KC_LBRC,  KC_LT,    MFN_R2,
  KC_AMPR,  KC_PIPE,  KC_AT,    KC_TILD,  KC_DLR,   KC_CIRC,  MFN_R3,
  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    MFN_R4,
),
[LY_0010] = LAYOUT_planck_grid(
  UC(L'×'), KC_ASTR,  KC_QUES,  KC_EXLM,  KC_GRV,   KC_HASH,  MFN_R1,
  UC(L'→'), KC_MINS,  KC_COMM,  KC_DOT,   KC_QUOT,  KC_EQL,   MFN_R2,
  UC(L'∘'), KC_PLUS,  KC_SCLN,  KC_COLN,  KC_DQUO,  KC_UNDS,  MFN_R3,
  KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   MFN_R4,
),
[LY_1010] = LAYOUT_planck_grid(
  UC(L'⊗'), UC(L'⊕'), KC_7,     KC_8,     KC_9,     UC(L'┻'), MFN_R1,
  UC(L'⊚'), KC_0,     KC_1,     KC_2,     KC_3,     UC(L'┃'), MFN_R2,
  UC(L'┏'), UC(L'┓'), KC_4,     KC_5,     KC_6,     UC(L'┳'), MFN_R3,
  UC(L'┗'), UC(L'┛'), UC(L'┫'), UC(L'━'), UC(L'┣'), UC(L'╋'), MFN_R4
),
[LY_0100] = LAYOUT_planck_grid(
 KC_F13, KC_WSCH,     KC_HOME,     KC_UP,     KC_END,     KC_PGUP,     MFN_R1,
 KC_F14, XXXXXXX,     KC_LEFT,     KC_DOWN,   KC_RGHT,    KC_PGDN,     MFN_R2,
 KC_F15, KC_WBAK,     KC_WFWD,     MC(KC_A),  MC(KC_Z),   MSC(KC_Z),   MFN_R3,
 KC_F16, MA(KC_LEFT), MC(KC_LEFT), MC(KC_F),  MC(KC_RGHT),MA(KC_RGHT), MFN_R4,
),
[LY_1100] = LAYOUT_planck_grid(
 KC_F17, MC(KC_WSCH), S(KC_HOME),  S(KC_UP),  S(KC_END),  MC(KC_PGUP), MFN_R1,
 KC_F18, XXXXXXX,     S(KC_LEFT),  S(KC_DOWN),S(KC_RGHT), MC(KC_PGDN), MFN_R2,
 KC_F19, MC(KC_S),    MC(KC_X),    MC(KC_C),  MC(KC_V),   MC(KC_L),    MFN_R3,
 KC_F20, MCA(KC_LEFT),MSC(KC_LEFT),MCA(KC_F),MSC(KC_RGHT),MCA(KC_RGHT),MFN_R4,
),
[LY_0110] = LAYOUT_planck_grid(
  MC(KC_F1) ,MC(KC_F2) ,MC(KC_F3) ,MC(KC_F4) ,MC(KC_F5) ,MC(KC_F6) , MFN_R1,
  MC(KC_F7) ,MC(KC_F8) ,MC(KC_F9) ,MC(KC_F10),MC(KC_F11),MC(KC_F12), MFN_R2,
  MC(KC_F13),MC(KC_F14),MC(KC_F15),MC(KC_F16),MC(KC_F17),MC(KC_F18), MFN_R3,
  MC(KC_F19),MC(KC_F20),MC(KC_F21),MC(KC_F22),MC(KC_F23),MC(KC_F24), MFN_R4
),
[LY_1110] = LAYOUT_planck_grid(
  MG(KC_F1) ,MG(KC_F2) ,MG(KC_F3) ,MG(KC_F4) ,MG(KC_F5) ,MG(KC_F6) , MFN_R1,
  MG(KC_F7) ,MG(KC_F8) ,MG(KC_F9) ,MG(KC_F10),MG(KC_F11),MG(KC_F12), MFN_R2,
  MG(KC_F13),MG(KC_F14),MG(KC_F15),MG(KC_F16),MG(KC_F17),MG(KC_F18), MFN_R3,
  MG(KC_F19),MG(KC_F20),MG(KC_F21),MG(KC_F22),MG(KC_F23),MG(KC_F24), MFN_R4
),
[LY_1111] = LAYOUT_planck_grid(
 KC_MPRV, DYN_REC_STOP,    KC_WH_L,         KC_MS_U, KC_WH_R, KC_WH_U, MFN_R1,
 KC_CAPS, XXXXXXX,         KC_MS_L,         KC_MS_D, KC_MS_R, KC_WH_D, MFN_R2,
 KC_MNXT, DYN_MACRO_PLAY2, DYN_MACRO_PLAY1, KC_MPLY, KC_MRWD, KC_MFFD, MFN_R3,
 KC_MSTP, DYN_REC_START2,  DYN_REC_START1,  KC_BTN2, KC_BTN1, KC_BTN3, MFN_R4,
),
[LY_1101] = LAYOUT_planck_grid(
  XXXXXXX, MU_ON,   MU_OFF,      PRINT_ON, PRINT_OFF,   DEBUG,   MFN_R1,
  XXXXXXX, KC_APP,  KC_VOLD,     KC_MUTE,  KC_VOLU,     XXXXXXX, MFN_R2,
  XXXXXXX, KC_MAIL, S(KC_VOLD),  KC_INS,   S(KC_VOLU),  KC_PSCR, MFN_R3,
  XXXXXXX, MUV_DE,  MUV_IN,      AU_ON,    AU_OFF,      RESET,   MFN_R4,
),
[LY_0011] = LAYOUT_planck_grid(
  UC(L'็'),  UC(L'์'),  UC(L'่'),  UC(L'้'),  UC(L'๊'),  UC(L'๋'), MFN_R1,
  UC(L'โ'),  UC(L'แ'),  UC(L'เ'),  UC(L'า'),  UC(L'ั'),  UC(L'ะ'), MFN_R2,
  UC(L'ไ'),  UC(L'ใ'),  UC(L'ิ'),  UC(L'ี'),  UC(L'ึ'),  UC(L'ื'), MFN_R3,
  UC(L'ๅ'),  UC(L'ฺ'),  UC(L'ํ'),  UC(L'ุ'),  UC(L'ู'),  UC(L'ำ'), MFN_R4,
),
[LY_1011] = LAYOUT_planck_grid(
  UC(L'ฐ'),  UC(L'ฎ'),  UC(L'ฏ'),  UC(L'ฮ'),  UC(L'ข'),  UC(L'ฃ'), MFN_R1,
  UC(L'ถ'),  UC(L'ด'),  UC(L'ต'),  UC(L'อ'),  UC(L'ก'),  UC(L'จ'), MFN_R2,
  UC(L'ภ'),  UC(L'บ'),  UC(L'ป'),  UC(L'ส'),  UC(L'ห'),  UC(L'ฉ'), MFN_R3,
  UC(L'ฯ'),  UC(L'ผ'),  UC(L'ฝ'),  UC(L'ศ'),  UC(L'ษ'),  UC(L'ๆ'), MFN_R4,
),
[LY_0111] = LAYOUT_planck_grid(
  UC(L'ฒ'),  UC(L'ฤ'),  UC(L'ฦ'),  UC(L'ม'),  UC(L'ค'),  UC(L'ฅ'), MFN_R1,
  UC(L'ณ'),  UC(L'ร'),  UC(L'ล'),  UC(L'น'),  UC(L'ว'),  UC(L'ง'), MFN_R2,
  UC(L'ญ'),  UC(L'ช'),  UC(L'ซ'),  UC(L'ย'),  UC(L'ท'),  UC(L'ฑ'), MFN_R3,
  UC(L'ฌ'),  UC(L'ฬ'),  UC(L'ฟ'),  UC(L'พ'),  UC(L'ธ'),  UC(L'ฆ'), MFN_R4,
),
[LY_0001] = UNUSED_LAYER
[LY_0101] = UNUSED_LAYER
[LY_1001] = UNUSED_LAYER
};

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

uint16_t cur_layer_code = 0;

#ifdef AUDIO_ENABLE

float tone_startup[][2]    = SONG(STARTUP_SOUND);
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
float tone_plover[][2]     = SONG(PLOVER_SOUND);
float tone_plover_gb[][2]  = SONG(PLOVER_GOODBYE_SOUND);
float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);
float tone_goodbye[][2]    = SONG(GOODBYE_SOUND);
#endif

void startup_user() {
  _delay_ms(20); // gets rid of tick
  set_unicode_input_mode(UC_LNX);
#ifdef AUDIO_ENABLE
  PLAY_SONG(tone_startup);
#endif
}

void shutdown_user() {
#ifdef AUDIO_ENABLE
  PLAY_SONG(tone_goodbye);
  _delay_ms(150);
  stop_all_notes();
#endif
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  uint16_t mask = 1 << (3 - (keycode - FN_A));
  if (!process_record_dynamic_macro(keycode, record))
    return false;
  if(FN_A <= keycode && keycode <= FN_D) {
    if(!(cur_layer_code & mask) == record->event.pressed) {
      layer_off(cur_layer_code + LY_0000);
      cur_layer_code ^= mask;
      layer_on(cur_layer_code + LY_0000);
    }
    return false;
  }
  return true;
}

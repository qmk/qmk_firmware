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
//#include "muse.h"

enum preonic_layers {
  _QWERTY,
  _FFXIV,
  _MEDIA,
  _NAVR,
  _MOUSE,
  _NSSL,
  _NSL,
  _FUNL,
  _ADJUST
};

enum preonic_keycodes {
  QWERTY = SAFE_RANGE,
  FFXIV,
  BACKLIT,
  R_ASIGN,
  R_PIPE,
  GITFETC,
  GITPULL,
  GITPUSI,
  GITPUSO,
  GITREBA,
  GITADD,
  GITCOMM,
  GITBRCH,
  GITCOUT,
  GITCOBR,
  GITSTAT,
  GITBDEL
};

// modifier keys
#define HOME_A  LSFT_T(KC_A)
#define HOME_S  LCTL_T(KC_S)
#define HOME_D  LALT_T(KC_D)
#define HOME_F  LGUI_T(KC_F)

#define HOME_J  LGUI_T(KC_J)
#define HOME_K  LALT_T(KC_K)
#define HOME_L  LCTL_T(KC_L)
#define HOME_SCLN  LSFT_T(KC_SCLN)

#define LT_ESC  LT(_MEDIA, KC_ESC)
#define LT_BSPC LT(_NAVR, KC_BSPC)
#define LT_TAB  LT(_MOUSE, KC_TAB)
#define LT_ENT  LT(_NSSL, KC_ENT)
#define LT_SPC  LT(_NSL, KC_SPC)
#define LT_DEL  LT(_FUNL, KC_DEL)

#define UNDO  LGUI(KC_Z)
#define CUT   LGUI(KC_X)
#define COPY  LGUI(KC_C)
#define PASTE LGUI(KC_V)

#define NX_HOME LCTL(KC_A)
#define NX_END  LCTL(KC_E)
#define NX_WB   LALT(KC_B)
#define NX_WF   LALT(KC_F)

#define SCR_GRB SGUI(C(KC_4))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |   1  |   2  |   3  |   4  |   5  |  NO  |  NO  |   6  |   7  |   8  |   9  |   0  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |   Q  |   W  |   E  |   R  |   T  |  NO  |  NO  |   Y  |   U  |   I  |   O  |   P  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |A-Shft|S-Ctrl|D-Alt |F-GUI |   G  |  NO  |  NO  |   H  |J-GUI |K-Alt |L-Ctrl|;-Shft|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |   Z  |   X  |   C  |   V  |   B  |  NO  |  NO  |   N  |   M  |   ,  |   .  |   /  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |  NO  |  NO  |LTEsc |LTBksp|LTTab |  NO  |  NO  |LTEnt |LTSpc |LTDel |  NO  |  NO  |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_preonic_grid(
  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   XXXXXXX, XXXXXXX, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,   XXXXXXX, XXXXXXX, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
  HOME_A,  HOME_S,  HOME_D,  HOME_F,  KC_G,   XXXXXXX, XXXXXXX, KC_H,    HOME_J,  HOME_K,  HOME_L,  HOME_SCLN,
  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   XXXXXXX, XXXXXXX, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
  XXXXXXX, XXXXXXX, LT_ESC,  LT_BSPC, LT_TAB, XXXXXXX, XXXXXXX, LT_ENT,  LT_SPC,  LT_DEL,  XXXXXXX, XXXXXXX
),

/* Final Fantasy XIV
* ,-----------------------------------------------------------------------------------.
* |   1  |   2  |   3  |   4  |   5  |  NO  |  NO  | LT6  |   7  |   8  |   9  |   0  |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |   Q  |   W  |   E  |   R  |   T  |  NO  |  NO  |   Y  |   U  |   I  |   O  |   P  |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |   A  |   S  |   D  |   F  |   G  |  NO  |  NO  |   H  |   J  |   K  |   L  |   ;  |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |   Z  |   X  |   C  |   V  |   B  |  NO  |  NO  |   N  |   M  |   ,  |   .  |   /  |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |  NO  |  NO  | Alt  |Shift | GUI  |  NO  |  NO  |Enter |Space | Bksp |  NO  |  NO  |
* `-----------------------------------------------------------------------------------'
 */
[_FFXIV] = LAYOUT_preonic_grid(
  KC_ESC,  KC_GRV,  KC_TAB,  KC_4,    LT(_ADJUST, KC_5), XXXXXXX, XXXXXXX,   KC_6,    KC_7,   KC_8,    KC_9,    KC_0,
  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,              XXXXXXX, XXXXXXX,   KC_Y,    KC_U,   KC_I,    KC_O,    KC_P,
  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,              XXXXXXX, XXXXXXX,   KC_H,    KC_J,   KC_K,    KC_L,    KC_SCLN,
  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,              XXXXXXX, XXXXXXX,   KC_N,    KC_M,   KC_COMM, KC_DOT,  KC_SLSH,
  XXXXXXX, XXXXXXX, KC_LALT, KC_LSFT, KC_LGUI,           XXXXXXX, XXXXXXX,   LT_ENT,  LT_SPC, KC_BSPC, XXXXXXX, XXXXXXX
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
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, NX_HOME, NX_WB,   NX_WF,   NX_END,
  KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, XXXXXXX, XXXXXXX, XXXXXXX, KC_CAPS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,
  UNDO,    CUT,     COPY,    PASTE,   XXXXXXX, XXXXXXX, XXXXXXX, KC_INS,  KC_HOME, KC_PGDN, KC_PGUP, KC_END,
  XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, KC_ENT,  KC_SPC,  KC_DEL,  XXXXXXX, XXXXXXX
),

/* SHIFTED Number and Symbol layer
* ,-----------------------------------------------------------------------------------.
* |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |  &   |  *   |  (   |  )   |  ~   |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |  $   |  %   |  ^   |  _   |  +   |  NO  |  NO  |  NO  | GUI  | Alt  | Ctrl |Shift |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |  !   |  @   |  #   |  {   |  }   |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |  NO  |  NO  |  .   |  "   |  |   |  NO  |  NO  |      |  NO  |  NO  |  NO  |  NO  |
* `-----------------------------------------------------------------------------------'
*/

[_NSSL] = LAYOUT_preonic_grid(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TILD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  KC_DLR,  KC_PERC, KC_CIRC, KC_UNDS, KC_PLUS, XXXXXXX, XXXXXXX, XXXXXXX, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT,
  KC_EXLM, KC_AT,   KC_HASH, KC_LCBR, KC_RCBR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, KC_DOT,  KC_DQUO, KC_PIPE, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),


/* Number and Symbol layer
* ,-----------------------------------------------------------------------------------.
* |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |  7   |  8   |  9   |  0   |  `   |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |  4   |  5   |  6   |  -   |  =   |  NO  |  NO  |  NO  | GUI  | Alt  | Ctrl |Shift |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |  1   |  2   |  3   |  [   |  ]   |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |  NO  |  NO  |  .   |  '   |  \   |  NO  |  NO  |  NO  |      |  NO  |  NO  |  NO  |
* `-----------------------------------------------------------------------------------'
*/
[_NSL] = LAYOUT_preonic_grid(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  KC_4,    KC_5,    KC_6,    KC_MINS, KC_EQL,  XXXXXXX, XXXXXXX, XXXXXXX, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT,
  KC_1,    KC_2,    KC_3,    KC_LBRC, KC_RBRC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, KC_DOT,  KC_QUOT, KC_BSLS, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX
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
* |  NO  |  NO  |  NO  |  NO  |      |  NO  |  NO  | BTN1 | BTN2 | BTN3 |  NO  |  NO  |
* `-----------------------------------------------------------------------------------'
*/

[_MOUSE] = LAYOUT_preonic_grid(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_WH_L, KC_WH_U, KC_WH_D, KC_WH_R,
  XXXXXXX, XXXXXXX, MO(_ADJUST), XXXXXXX, _______, XXXXXXX, XXXXXXX, KC_BTN1, KC_BTN2, KC_BTN3, XXXXXXX, XXXXXXX
),



/* MEDIA layer
* ,-----------------------------------------------------------------------------------.
* |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |Shift | Ctrl | Alt  | GUI  |  NO  |  NO  |  NO  |  NO  | MS_L | MS_D	| MS_U | MS_R |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  | WH_L | WH_U	| WH_D | WH_R |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |  NO  |  NO  |      |  NO  |  NO  |  NO  |  NO  | BTN1 | BTN2 | BTN3 |  NO  |  NO  |
* `-----------------------------------------------------------------------------------'
*/

[_MEDIA] = LAYOUT_preonic_grid(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI,
  KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, BACKLIT, XXXXXXX, RGB_HUD, RGB_SAD, RGB_VAD,
  XXXXXXX, XXXXXXX, _______, XXXXXXX, MO(_ADJUST), XXXXXXX, XXXXXXX, KC_MSTP, KC_MPLY, KC_MUTE, XXXXXXX, XXXXXXX
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
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  GITFETC, GITPULL, XXXXXXX, GITREBA, XXXXXXX,   XXXXXXX, XXXXXXX,   XXXXXXX, KC_F9,   KC_F10,  KC_F11,  KC_F12,
  GITADD,  GITSTAT, GITCOMM, GITPUSO, GITPUSI,   XXXXXXX, XXXXXXX,   XXXXXXX, KC_F5,   KC_F6,   KC_F7,   KC_F8,
  GITBDEL, XXXXXXX, GITCOUT, GITCOBR, GITBRCH,   XXXXXXX, XXXXXXX,   XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F4,
  XXXXXXX, XXXXXXX, SCR_GRB, R_ASIGN, R_PIPE,    XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX
),




/* Adjust (_MOUSE + _MEDIA)
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Reset |Debug |      |      |      |      |      |TermOf|TermOn|      |AGnorm|AGswap|
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |FFXIV |Qwerty|Voice-|Voice+|Aud cy|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |MidiOn|MusOn |Aud on|      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |MidOff|MusOff|AudOff|      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_preonic_grid(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, _______,
  RESET,   DEBUG,   XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX,   TERM_ON, TERM_OFF, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX,   FFXIV,   QWERTY,   XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX,   XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, _______, XXXXXXX, _______,   XXXXXXX, XXXXXXX,   XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  /*
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, _______,
  RESET,   DEBUG,   XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX,   TERM_ON, TERM_OFF, XXXXXXX, AG_NORM, AG_SWAP,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX,   FFXIV,   QWERTY,   MUV_DE,  MUV_IN,  MU_MOD,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX,   MI_ON,   MU_ON,    AU_ON,   XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, _______, XXXXXXX, _______,   XXXXXXX, XXXXXXX,   MI_OFF,  MU_OFF,   AU_OFF,  XXXXXXX, XXXXXXX
  */
)


};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
        case QWERTY:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_QWERTY);
          }
          return false;
          break;
        case FFXIV:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_FFXIV);
          }
          return false;
          break;
        case R_ASIGN:
          if (record->event.pressed) {
            // when keycode R_ASIGN is pressed
            SEND_STRING("<- ");
          }
          // return false;
          break;
        case R_PIPE:
          if (record->event.pressed) {
            SEND_STRING(" %>%\n");
          }
          break;
        case GITFETC:
          if (record->event.pressed) {
            SEND_STRING("git fetch ");
          }
          break;
        case GITPULL:
          if (record->event.pressed) {
            SEND_STRING("git pull ");
          }
          break;
        case GITPUSI:
          if (record->event.pressed) {
            SEND_STRING("git push imm ");
          }
          break;
        case GITPUSO:
          if (record->event.pressed) {
            SEND_STRING("git push origin ");
          }
          break;
        case GITREBA:
          if (record->event.pressed) {
            SEND_STRING("git pull --rebase ");
          }
          break;
        case GITADD:
          if (record->event.pressed) {
            SEND_STRING("git add ");
          }
          break;
        case GITCOMM:
          if (record->event.pressed) {
            SEND_STRING("git commit -m ");
          }
          break;
        case GITBRCH:
          if (record->event.pressed) {
            SEND_STRING("git branch ");
          }
          break;
        case GITCOUT:
          if (record->event.pressed) {
            SEND_STRING("git checkout ");
          }
          break;
        case GITCOBR:
          if (record->event.pressed) {
            SEND_STRING("git checkout -b ");
          }
          break;
        case GITSTAT:
          if (record->event.pressed) {
            SEND_STRING("git status ");
          }
          break;
        case GITBDEL:
          if (record->event.pressed) {
            SEND_STRING("git branch -d ");
          }
          break;
        case BACKLIT:
          if (record->event.pressed) {
            register_code(KC_RSFT);
            #ifdef BACKLIGHT_ENABLE
              backlight_step();
            #endif
            #ifdef __AVR__
            writePinLow(E6);
            #endif
          } else {
            unregister_code(KC_RSFT);
            #ifdef __AVR__
            writePinHigh(E6);
            #endif
          }
          return false;
          break;
      }
    return true;
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

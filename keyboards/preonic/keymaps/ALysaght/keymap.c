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
#include "muse.h"

enum preonic_layers {
  _QWERTY,
  _FFXIV,
  //_MEDR,
  _NAVR,
  //_MOUR,
  _NSSL,
  _NSL,
  //_FUNL,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum preonic_keycodes {
  QWERTY = SAFE_RANGE,
  FFXIV,
  LOWER,
  RAISE,
  BACKLIT,
  R_ASIGN,
  R_PIPE,
  GITFETC,
  GITPULL,
  GITPUSH,
  GITREBA,
  GITADD,
  GITCOMM,
  GITBRCH,
  GITCOUT,
  GITWTAD,
  GITWTPR,
  GITSTAT,
  GITBDEL,
  GITMAIN,
  GITORIG
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

#define LT_ESC  KC_ESC //LT(_MEDR, KC_ESC)
#define LT_BSPC  LT(_NAVR, KC_BSPC)
#define LT_TAB  KC_TAB //LT(_MOUR, KC_TAB)
#define LT_ENT  LT(_NSSL, KC_ENT)
#define LT_SPC  LT(_NSL, KC_SPC)
#define LT_DEL  KC_DEL //LT(_FUNL, KC_DEL)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |  `   |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  [   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Tab  |A-Shft|S-Ctrl|D-Alt |F-GUI |   G  |   H  |J-GUI |K-Alt |L-Ctrl|;-Shft|  '   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |Lower |Raise |      | Esc  | Bksp | Tab  |Enter |Space | Del  |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_preonic_grid(
  KC_ESC,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,      KC_BSLS,
  KC_GRV,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,      KC_LBRC,
  KC_TAB,   HOME_A,  HOME_S,  HOME_D,  HOME_F,  KC_G,    KC_H,    HOME_J,  HOME_K,  HOME_L,  HOME_SCLN, KC_QUOT,
  KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,   KC_ENT,
  LOWER,    RAISE,   XXXXXXX, LT_ESC,  LT_BSPC, LT_TAB,  LT_ENT,  LT_SPC,  LT_DEL,  XXXXXXX, XXXXXXX,   XXXXXXX
),

/* Final Fantasy XIV
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |  `   |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  [   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | F11  |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |LOWER |RAISE | Alt  | GUI  |Shift | Bksp |Space | F12  | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_FFXIV] = LAYOUT_preonic_grid(
  KC_ESC,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS,
  KC_GRV,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
  KC_TAB,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_F11,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
  LOWER,    RAISE,   KC_LALT, KC_LGUI, KC_LSFT, KC_BSPC, KC_SPC,  KC_F12,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),




/* Navigation layer
* ,-----------------------------------------------------------------------------------.
* |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |  NO  |Shift | Ctrl | Alt  | GUI  |  NO  | CAPS | Left | Down |  Up  |Right |  NO  |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  | Ins  | Home | PgDn | PgUp | End  |  NO  |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |Enter |Space |  NO  |  NO  |  NO  |  NO  |
* `-----------------------------------------------------------------------------------'
*/

[_NAVR] = LAYOUT_preonic_grid(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, XXXXXXX, KC_CAPS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_INS,  KC_HOME, KC_PGDN, KC_PGUP, KC_END,  XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_ENT,  KC_SPC,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),

/* SHIFTED Number and Symbol layer
* ,-----------------------------------------------------------------------------------.
* |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |  NO  |  &   |  *   |  (   |  )   |  ~   |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |  NO  |  $   |  %   |  ^   |  _   |  +   |  NO  | GUI  | Alt  | Ctrl |Shift |  NO  |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |  NO  |  !   |  @   |  #   |  {   |  }   |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |  NO  |  NO  |  NO  |  .   |  "   |  |   |      |  NO  |  NO  |  NO  |  NO  |  NO  |
* `-----------------------------------------------------------------------------------'
*/

[_NSSL] = LAYOUT_preonic_grid(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TILD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, KC_DLR,  KC_PERC, KC_CIRC, KC_UNDS, KC_PLUS, XXXXXXX, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,
  XXXXXXX, KC_EXLM, KC_AT,   KC_HASH, KC_LCBR, KC_RCBR, XXXXXXX, XXXXXXX, XXXXXXX, KC_ALGR, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, KC_DOT,  KC_DQUO, KC_PIPE, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),


/* Number and Symbol layer
* ,-----------------------------------------------------------------------------------.
* |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |  NO  |  7   |  8   |  9   |  0   |  `   |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |  NO  |  4   |  5   |  6   |  -   |  =   |  NO  | GUI  | Alt  | Ctrl |Shift |  NO  |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |  NO  |  1   |  2   |  3   |  [   |  ]   |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |  NO  |  NO  |  NO  |  .   |  '   |  \   |  NO  |      |  NO  |  NO  |  NO  |  NO  |
* `-----------------------------------------------------------------------------------'
*/
[_NSL] = LAYOUT_preonic_grid(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, KC_4,    KC_5,    KC_6,    KC_MINS, KC_EQL,  XXXXXXX, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,
  XXXXXXX, KC_1,    KC_2,    KC_3,    KC_LBRC, KC_RBRC, XXXXXXX, XXXXXXX, XXXXXXX, KC_ALGR, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, KC_DOT,  KC_QUOT, KC_BSLS, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),





/* xxxx layer
* ,-----------------------------------------------------------------------------------.
* |      |      |      |      |      |      |      |      |      |      |      |      |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |      |      |      |      |      |      |      |      |      |      |      |      |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |      |      |      |      |      |      |      |      |      |      |      |      |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |      |      |      |      |      |      |      |      |      |      |      |      |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |      |      |      |      |      |      |      |      |      |      |      |      |
* `-----------------------------------------------------------------------------------'
*/

/*
[_xxxx] = LAYOUT_preonic_grid(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, RESET,   U_NA,    U_NA,    U_NA,    U_NA,    U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND, XXXXXXX,
  XXXXXXX, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, U_NA,    KC_CAPS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX,
  XXXXXXX, U_NA,    KC_ALGR, U_NA,    U_NA,    U_NA,    KC_INS,  KC_HOME, KC_PGDN, KC_PGUP, KC_END, XXXXXXX,
  XXXXXXX, U_NP,    U_NP,    U_NA,    U_NA,    U_NA,    KC_ENT,  KC_BSPC, KC_DEL,  U_NP,    U_NP, XXXXXXX
),
*/

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * | F11  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 | F12  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |  ]   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |  <-  |  %>% |   -  |   =  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |ScrSht|      | Del  |  Ins |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_preonic_grid(
  KC_F11,  KC_F1,   KC_F2,   KC_F3,         KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12,
  _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______, _______, KC_RBRC,
  _______, _______, _______, _______,       _______, _______, _______, R_ASIGN, R_PIPE,  KC_MINS, KC_EQL,  _______,
  _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, SGUI(C(KC_4)), _______, KC_DEL,   KC_INS, _______, KC_MUTE, KC_VOLD, KC_VOLU, KC_MPLY
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |  |   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |GITCOU|GITFET|GITPUL|GITREB|      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |GITADD|GITSTA|GITCOM|GITPUS|      |      |Origin|      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |GITBRC|GITBDE|GITWTA|GITWTP|      |      | Main |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      | Home | PgDn | PgUp | End  |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_preonic_grid(
  KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE,
  _______, GITCOUT, GITFETC, GITPULL, GITREBA, _______, _______, _______, _______, _______, _______, _______,
  _______,  GITADD, GITSTAT, GITCOMM, GITPUSH, _______, _______, GITORIG, _______, _______, _______, _______,
  _______, GITBRCH, GITBDEL, GITWTAD, GITWTPR, _______, _______, GITMAIN, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP,  KC_END
),



/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Reset| Debug|      |      |      |      |TermOf|TermOn|      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |Aud cy|Aud on|AudOff|AGnorm|AGswap|Qwerty|      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|MusOff|MidiOn|MidOff|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite|      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_preonic_grid(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, RESET,   DEBUG,   _______, _______, _______, _______, TERM_ON, TERM_OFF,_______, _______, _______,
  _______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,    FFXIV, _______, _______, _______,
  _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______, _______, _______, _______,
  BACKLIT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
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
        case GITPUSH:
          if (record->event.pressed) {
            SEND_STRING("git push ");
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
        case GITWTAD:
          if (record->event.pressed) {
            SEND_STRING("git worktree add ");
          }
          break;
        case GITWTPR:
          if (record->event.pressed) {
            SEND_STRING("git git worktree prune ");
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
          break;;
        case GITMAIN:
          if (record->event.pressed) {
            SEND_STRING("main ");
          }
          break;
        case GITORIG:
          if (record->event.pressed) {
            SEND_STRING("origin ");
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

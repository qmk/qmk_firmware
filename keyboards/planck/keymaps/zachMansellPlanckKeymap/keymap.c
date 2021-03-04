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


enum planck_layers {
  _QWERTY,
  _CMK_DHM,
  _SYM,
  _NUM,
  _ERG_NUM,
  _NAV,
  _SYS,
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  CMK_DHM,
  BACKLIT,
  SYM,
  NUM,
  ERG_NUM,
  NAV,
};

//Tap Dance Declarations
enum {
  TD_ESC_CAPS = 0,
  ALT_LP,
  CTL_RCB,
  GUI_RP,
  SFT_LCB,
  SFT_PLS
};

typedef enum {
  SINGLE_TAP,
  SINGLE_HOLD,
  DOUBLE_SINGLE_TAP
} td_state_t;

static td_state_t td_state;
int cur_dance (qk_tap_dance_state_t *state);
void altlp_finished (qk_tap_dance_state_t *state, void *user_data);
void altlp_reset (qk_tap_dance_state_t *state, void *user_data);
void ctlrcb_finished (qk_tap_dance_state_t *state, void *user_data);
void ctlrcb_reset (qk_tap_dance_state_t *state, void *user_data);
void guirp_finished (qk_tap_dance_state_t *state, void *user_data);
void guirp_reset (qk_tap_dance_state_t *state, void *user_data);
void sftlcb_finished (qk_tap_dance_state_t *state, void *user_data);
void sftlcb_reset (qk_tap_dance_state_t *state, void *user_data);
void sftpls_finished (qk_tap_dance_state_t *state, void *user_data);
void sftpls_reset (qk_tap_dance_state_t *state, void *user_data);

#define ALT_3 LALT_T(KC_3)
#define ALT_2 LALT_T(KC_2)
#define ALT_8 LALT_T(KC_8)
#define ALT_D LALT_T(KC_D)
#define ALT_K LALT_T(KC_K)
#define ALT_LB LALT_T(KC_LBRC)
#define ALT_S LALT_T(KC_S)
#define ALT_E LALT_T(KC_E)
#define CTRL_2 LCTL_T(KC_2)
#define CTRL_4 LCTL_T(KC_4)
#define CTRL_5 LCTL_T(KC_5)
#define CTRL_9 LCTL_T(KC_9)
#define CTRL_EQ LCTL_T(KC_EQL)
#define CTRL_L LCTL_T(KC_L)
#define CTRL_S LCTL_T(KC_S)
#define CTRL_R LCTL_T(KC_R)
#define CTRL_I LCTL_T(KC_I)
#define GUI_4 LGUI_T(KC_4)
#define GUI_1 LGUI_T(KC_1)
#define GUI_0 LGUI_T(KC_0)
#define GUI_7 LGUI_T(KC_7)
#define GUI_RB LGUI_T(KC_RBRC)
#define GUI_F LGUI_T(KC_F)
#define GUI_J LGUI_T(KC_J)
#define GUI_TEA LGUI_T(KC_T)
#define GUI_N LGUI_T(KC_N)
#define MAC_EM S(LALT(KC_MINS))
#define MAC_EN LALT(KC_MINS)
#define NAV_BK LT(_NAV, KC_BSPC)
#define NAV_SPC LT(_NAV, KC_SPC)
#define NAV_LK TG(_NAV)
#define NUMLK TG(_NUM)
#define NUM_SPC LT(_NUM, KC_SPC)
#define ERG_NUM_SPC LT(_ERG_NUM, KC_SPC)
#define SFT_0 LSFT_T(KC_0)
#define SFT_6 LSFT_T(KC_6)
#define SFT_7 LSFT_T(KC_7)
#define SFT_1 LSFT_T(KC_1)
#define SFT_A LSFT_T(KC_A)
#define SFT_O LSFT_T(KC_O)
#define SFT_CLN LSFT_T(KC_SCOLON)
#define SFT_OS OSM(MOD_LSFT)
#define SYM_OS LT(_SYM, KC_SPC)
#define SYM_BK LT(_SYM, KC_BSPC)
#define SYS_Z LT(_SYS, KC_Z)
#define VOL_DN S(LALT(KC__VOLDOWN))
#define VOL_UP S(LALT(KC__VOLUP))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |      |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |sftA  |  ctlS|  altD|guiF  |   G  |   H  |guiJ  |altK  |ctkL  |  sft;|  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |SYSZ  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   ?  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      | sftos|navbak|symspc|spcNUM|   SYM|sft/os| Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_grid(
    _______,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    _______,  SFT_A,    CTRL_S,    ALT_D,    GUI_F,    KC_G,    KC_H,    GUI_J,    ALT_K,    CTRL_L,    SFT_CLN, KC_QUOT,
    _______, SYS_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_QUES, _______,
    _______, _______, _______, SFT_OS, NAV_BK, SYM_OS,  NUM_SPC, SYM_OS,   SFT_OS, KC_DOWN, KC_UP,   KC_RGHT
),

/* Colemak DHm
 * ,-----------------------------------------------------------------------------------.
 * |      |   Q  |   W  |   F  |   P  |   B  |   J  |   L  |  U   |   Y  |   '  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |sftA  |  ctlR|  altS|guiT  |   G  |   M  |guiN  |altE  |ctkI  |  sftO|  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   Z  |   X  |   C  |   D  |   V  |   K  |   H  |   ,  |   .  |   ?  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      | sftos|nav,bak|sym/os|spc  |NUM   |sft/os| Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_CMK_DHM] = LAYOUT_planck_grid(
    _______,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT,    KC_BSPC,
    _______,  SFT_A,    CTRL_R,    ALT_S,    GUI_TEA,    KC_G,    KC_M,    GUI_N,    ALT_E,    CTRL_I,    SFT_O, KC_QUOT,
    _______, SYS_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SCLN, _______,
    _______, _______, _______, SFT_OS, SYM_BK, NAV_SPC,  ERG_NUM_SPC, SYM_OS,   SFT_OS, KC_DOWN, KC_UP,   KC_RGHT
),

/* Ergonomic Number
 * ,-----------------------------------------------------------------------------------.
 * |      |   f1 |  f2  |  f3  |  f4  |  f5  |  f6  |  f7  |  f8  |  f9  |  f10 |Bksp  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  sft1| ctrl2|alt3  |gui4  |    5 |  6   |gui7  |alt8  |ctrl9 |sft0  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |  -   |SPACE |BSPC  |DEL   |NUM LK|      |      |  /   |      |
 * |------+------+------+------+------------+------+------+------+------+------+-------|
 * |      |      |      |      | Tab  | esc |       |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ERG_NUM] = LAYOUT_planck_grid(
    _______,  KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10,    _______,
    _______,  SFT_7, CTRL_5,   ALT_3,   GUI_1,   KC_9,   KC_8,   GUI_0, ALT_2,  CTRL_4, SFT_6, _______,
    _______, KC_F11, KC_F12, KC_MINS, KC_SPC, KC_BSPC, KC_DEL,  NUMLK, _______, _______, KC_SLSH, _______,
    _______, _______, _______, _______, KC_ESC, KC_TAB, _______, _______, _______, _______, _______, _______
),

/* SYM
 * ,-----------------------------------------------------------------------------------.
 * |      |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   ?  |   '  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | SFT/+| CTL/=| ALT/(| GUI/)|  "   |  :   | GUI/]| ALT/[| CTL/}|SFT/{ |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  <   |  |   |  -   |  >   |  \   |  `   |_     |/     | ~    | ;    |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |emdash|      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_SYM] = LAYOUT_planck_grid(
    _______, KC_EXLM,    KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,    KC_ASTR,    KC_QUES, KC_QUOT, KC_BSPC,
    _______,  TD(SFT_PLS),CTRL_EQ, TD(ALT_LP),   TD(GUI_RP),   KC_DQT,   KC_COLN,   GUI_RB,    ALT_LB,    TD(CTL_RCB), TD(SFT_LCB), _______,
    _______, KC_LT,      KC_PIPE, KC_MINS,   KC_GT,   KC_BSLS,  KC_GRV,  KC_UNDS,  KC_SLSH, KC_TILD, KC_SCLN, _______,
    _______, _______, _______, _______, _______, _______, _______, MAC_EM,    _______,    _______, _______, _______
),

/* Number
 * ,-----------------------------------------------------------------------------------.
 * |      |   f1 |  f2  |  f3  |  f4  |  f5  |  f6  |  f7  |  f8  |  f9  |  f10 |Bksp  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  sft1| ctrl2|alt3  |gui4  |    5 |  6   |gui7  |alt8  |ctrl9 |sft0  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |  -   |SPACE |BSPC  |DEL   |NUM LK|      |      |  /   |      |
 * |------+------+------+------+------------+------+------+------+------+------+-------|
 * |      |      |      |      | Tab  | esc |       |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_NUM] = LAYOUT_planck_grid(
    _______,  KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10,    _______,
    _______,  SFT_1, CTRL_2,   ALT_3,   GUI_4,   KC_5,   KC_6,   GUI_7, ALT_8,  CTRL_9, SFT_0, _______,
    _______, _______, _______, KC_MINS, KC_SPC, KC_BSPC, KC_DEL,  NUMLK, _______, _______, KC_SLSH, _______,
    _______, _______, _______, _______, KC_ESC, KC_TAB, _______, _______, _______, _______, _______, _______
),

/* Navigation + mouse keys
 *
 * ,-----------------------------------------------------------------------------------.
 * |      | PSCR |      |whlup |whldwn|      | bksp | pgdn | pgup |home  |end   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |shft  |cntrl |  alt |gui   |nav lk|caps  |left  |down  |up    |right |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |acl0  |acl1  |acl2  |btn2  |btn1  |ms l  |ms d  |ms u  |ms r  |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |esc   | del  | enter|      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_NAV] = LAYOUT_planck_grid(
  _______, KC_PSCR, _______, KC_WH_U, KC_WH_D, _______, KC_BSPC, KC_PGDN, KC_PGUP, KC_HOME, KC_END, _______,
  _______,KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, NAV_LK, KC_CAPS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______,
  _______,_______, KC_ACL0, KC_ACL1, KC_ACL2, KC_BTN2, KC_BTN1, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, _______,
  _______,_______,_______,_______,_______,KC_ESC, KC_DEL, KC_ENT, _______, _______, _______,  _______
),

/* System, media and layer lock keys
 *
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|Debug |QWERT |CMKDHM|      |      |VOL-- | VOL++|BRGTH-|BRGTH+|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |SHIFT |CTRl  |ALT   |GUI   |NAV LK|POWER |VOL-  | VOL+ | MUTE | MPLY |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |AU OFF|AU On |      |      |NUM LK|MRWD  | MFFD |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_SYS] = LAYOUT_planck_grid(
    _______, RESET,   DEBUG,   QWERTY, CMK_DHM, _______, _______, KC_VOLD, KC_VOLU,  KC_BRID, KC_BRIU, _______,
    _______, KC_LSFT, KC_LCTL,  KC_LALT,   KC_LGUI,  NAV_LK, KC_POWER, VOL_DN,  VOL_UP,  KC__MUTE,  KC_MPLY,  _______,
    _______, _______,  _______,  AU_OFF,   AU_ON,  _______,   _______,  NUMLK, KC_MRWD, KC_MFFD, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______
)

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case CMK_DHM:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_CMK_DHM);
      }
      return false;
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
    default:
      return true;
  }
};

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_ESC_CAPS]  = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS),//Tap once for Esc, twice for Caps Lock
  [ALT_LP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, altlp_finished, altlp_reset),
  [CTL_RCB] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ctlrcb_finished, ctlrcb_reset),
  [GUI_RP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, guirp_finished, guirp_reset),
  [SFT_LCB] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sftlcb_finished, sftlcb_reset),
  [SFT_PLS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sftpls_finished, sftpls_reset)
// Other declarations would go here, separated by commas, if you have them
};
//In Layer declaration, add tap dance item in place of a key code

// #ifdef AUDIO_ENABLE
//   float caps_lock_off_sound[][2] = SONG(CAPS_LOCK_OFF_SOUND);
//   float caps_lock_on_sound[][2] = SONG(CAPS_LOCK_ON_SOUND);
//   float num_lock_on_sound[][2] = SONG(NUM_LOCK_ON_SOUND);
//   float ag_norm_sound[][2] = SONG(AG_NORM_SOUND);
// #endif

// layer_state_t layer_state_set_user(layer_state_t state) {
//   switch (get_highest_layer(state)) {
//     case _NUM:
//         #ifdef AUDIO_ENABLE
//           stop_all_notes();
//           PLAY_SONG(caps_lock_on_sound);
//         #endif
//         break;
//     case _SYM:
//         #ifdef AUDIO_ENABLE
//           stop_all_notes();
//           PLAY_SONG(caps_lock_off_sound);
//         #endif
//         break;
//     case _NAV:
//         #ifdef AUDIO_ENABLE
//           stop_all_notes();
//           PLAY_SONG(num_lock_on_sound);
//         #endif
//         break;
//     }
//   return state;
// }

int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed) return SINGLE_TAP;
    else return SINGLE_HOLD;
  }
  if (state->count == 2) return DOUBLE_SINGLE_TAP;
  else return 3;
}

void altlp_finished (qk_tap_dance_state_t *state, void *user_data) {
  td_state = cur_dance(state);
  switch (td_state) {
    case SINGLE_TAP:
      register_code16(KC_LPRN);
      break;
    case SINGLE_HOLD:
      register_mods(MOD_BIT(KC_LALT));
      break;
    case DOUBLE_SINGLE_TAP:
      tap_code16(KC_LPRN);
      register_code16(KC_LPRN);
  }
}

void altlp_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (td_state) {
    case SINGLE_TAP:
      unregister_code16(KC_LPRN);
      break;
    case SINGLE_HOLD:
      unregister_mods(MOD_BIT(KC_LALT));
      break;
    case DOUBLE_SINGLE_TAP:
      unregister_code16(KC_LPRN);
  }
}

void ctlrcb_finished (qk_tap_dance_state_t *state, void *user_data) {
  td_state = cur_dance(state);
  switch (td_state) {
    case SINGLE_TAP:
      register_code16(KC_RCBR);
      break;
    case SINGLE_HOLD:
      register_mods(MOD_BIT(KC_LCTL));
      break;
    case DOUBLE_SINGLE_TAP:
      tap_code16(KC_RCBR);
      register_code16(KC_RCBR);
  }
}

void ctlrcb_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (td_state) {
    case SINGLE_TAP:
      unregister_code16(KC_RCBR);
      break;
    case SINGLE_HOLD:
      unregister_mods(MOD_BIT(KC_LCTL));
      break;
    case DOUBLE_SINGLE_TAP:
      unregister_code16(KC_RCBR);
  }
}

void guirp_finished (qk_tap_dance_state_t *state, void *user_data) {
  td_state = cur_dance(state);
  switch (td_state) {
    case SINGLE_TAP:
      register_code16(KC_RPRN);
      break;
    case SINGLE_HOLD:
      register_mods(MOD_BIT(KC_LGUI));
      break;
    case DOUBLE_SINGLE_TAP:
      tap_code16(KC_RPRN);
      register_code16(KC_RPRN);
  }
}

void guirp_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (td_state) {
    case SINGLE_TAP:
      unregister_code16(KC_RPRN);
      break;
    case SINGLE_HOLD:
      unregister_mods(MOD_BIT(KC_LGUI));
      break;
    case DOUBLE_SINGLE_TAP:
      unregister_code16(KC_RPRN);
  }
}

void sftlcb_finished (qk_tap_dance_state_t *state, void *user_data) {
  td_state = cur_dance(state);
  switch (td_state) {
    case SINGLE_TAP:
      register_code16(KC_LCBR);
      break;
    case SINGLE_HOLD:
      register_mods(MOD_BIT(KC_LSFT));
      break;
    case DOUBLE_SINGLE_TAP:
      tap_code16(KC_LCBR);
      register_code16(KC_LCBR);
  }
}

void sftlcb_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (td_state) {
    case SINGLE_TAP:
      unregister_code16(KC_LCBR);
      break;
    case SINGLE_HOLD:
      unregister_mods(MOD_BIT(KC_LSFT));
      break;
    case DOUBLE_SINGLE_TAP:
      unregister_code16(KC_LCBR);
  }
}

void sftpls_finished (qk_tap_dance_state_t *state, void *user_data) {
  td_state = cur_dance(state);
  switch (td_state) {
    case SINGLE_TAP:
      register_code16(KC_PLUS);
      break;
    case SINGLE_HOLD:
      register_mods(MOD_BIT(KC_LSFT));
      break;
    case DOUBLE_SINGLE_TAP:
      tap_code16(KC_PLUS);
      register_code16(KC_PLUS);
  }
}

void sftpls_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (td_state) {
    case SINGLE_TAP:
      unregister_code16(KC_PLUS);
      break;
    case SINGLE_HOLD:
      unregister_mods(MOD_BIT(KC_LSFT));
      break;
    case DOUBLE_SINGLE_TAP:
      unregister_code16(KC_PLUS);
  }
}

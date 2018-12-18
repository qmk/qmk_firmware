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

extern keymap_config_t keymap_config;

enum planck_layers {
  _QWERTY,
  _NUMBER,
  _SYMBOL,
  _FUNC,
  _ADJUST
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE
};

#define SPC_SHF MT(MOD_LSFT, KC_SPC)

#define ENT_FUN LT(_FUNC, KC_ENT)
#define ESC_FUN LT(_FUNC, KC_ESC)
#define TAB_NUM LT(_NUMBER, KC_TAB)
#define BSP_SYM LT(_SYMBOL, KC_BSPC)
#define DEL_ADJ LT(_ADJUST, KC_DEL)

#define SYMLOCK TG(_SYMBOL)
#define NUMLOCK TG(_NUMBER)

#define ONE_CTL OSM(MOD_LCTL)
#define ONE_ALT OSM(MOD_LALT)
#define ONE_GUI OSM(MOD_LGUI)
#define ONE_HYP OSM(MOD_HYPR)
#define ONE_MEH OSM(MOD_MEH)
#define ONE_WRP OSM(MOD_LCTL | MOD_LALT | MOD_LGUI)

#define A_CTRL MT(MOD_LCTL, KC_A)
#define S_ALT  MT(MOD_LALT, KC_S)
#define D_GUI  MT(MOD_LGUI, KC_D)
#define F_SHFT MT(MOD_LSFT, KC_F)
#define G_NUM  LT(_NUMBER, KC_G)
#define H_NAV  LT(_SYMBOL, KC_H)
#define J_SHFT MT(MOD_RSFT, KC_J)
#define K_GUI  MT(MOD_RGUI, KC_K)
#define L_ALT  MT(MOD_RALT, KC_L)
#define MINSCTL MT(MOD_RCTL, KC_MINS)
#define SCL_CTL MT(MOD_RCTL, KC_SCLN)

#define BWORD LALT(KC_LEFT)
#define FWORD LALT(KC_RIGHT)

#define NWIN LGUI(KC_GRV)
#define PWIN LGUI(LSFT(KC_GRV))
#define NTAB LGUI(LSFT(KC_RBRC))
#define PTAB LGUI(LSFT(KC_LBRC))

#define XMSNCTL HYPR(KC_F14)
#define XDSKTOP HYPR(KC_F15)
#define XNXTSPC HYPR(KC_F16)
#define XPRVSPC HYPR(KC_F17)
#define XNOTIFY HYPR(KC_F18)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Querty
  |   #  |   q  |   w  |   e  |   r  |   t  |   y  |   u  |   i  |   o  |   p  |   -  |
  |      |      |      |      |      |      |      |      |      |      |      |      |
  |------|------|------|------|------|------|------|------|------|------|------|------|
  |   (  |   a  |   s  |   d  |   f  |   g  |   h  |   j  |   k  |   l  |   ;  |   '  |
  |      | CTRL | ALT  |  GUI | SHIFT| NUMBR| SYMBL| SHIFT| GUI  | ALT  | CTRL |      |
  |------|------|------|------|------|------|------|------|------|------|------|------|
  |   [  |   z  |   x  |   c  |   v  |   b  |   n  |   m  |   ,  |   .  |   /  |   >  |
  |      |      |      |      |      |      |      |      |      |      |      |      |
  |------|------|------|------|------|------|------|------|------|------|------|------|
  | ctrl | alt  |  gui | Esc  | Tab  |   space     | Bksp |  Del | hyper| meh  | warp |
  |      |      |      | FUNC |NUMBER|   SHIFT     |SYMBOL|      |      |      |      |
 */
 [_QWERTY] = LAYOUT_planck_grid(
    KC_HASH, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_SCLN,
    KC_LPRN, A_CTRL,  S_ALT,   D_GUI,   F_SHFT,  G_NUM,   H_NAV,   J_SHFT,  K_GUI,   L_ALT,   MINSCTL, KC_QUOT,
    KC_LBRC, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RABK,
    KC_CAPS, ONE_ALT, ONE_GUI, ESC_FUN, TAB_NUM, SPC_SHF, SPC_SHF, BSP_SYM, DEL_ADJ, ONE_HYP, ONE_MEH, ONE_WRP
 ),

/* Symbol
  |      |   &  |   `  |   ~  |   [  |   ]  |   <  |   >  |   +  |   |  |      |   -  |
  |      |   $  |   %  |   =  |   (  |   )  |      |   :  |   !  |   @  |   *  |   '  |
  |      |      |   ^  |   #  |   {  |   }  |      |   "  |   |  |   \  |      |      |
  |      |      |      |      | LOCK |             | .... |      |      |      |      |
 */
 [_SYMBOL] = LAYOUT_planck_grid(
     _______, KC_AMPR, KC_GRV,  KC_TILD, KC_LBRC, KC_RBRC, KC_LABK, KC_RABK, KC_PLUS, KC_ASTR, XXXXXXX, _______,
     _______, KC_DLR,  KC_PERC, KC_EQL,  KC_LPRN, KC_RPRN, KC_SCLN, KC_COLN, KC_EXLM, KC_AT,   KC_ASTR, _______,
     _______, XXXXXXX, KC_CIRC, KC_HASH, KC_LCBR, KC_RCBR, KC_QUOT, KC_DQUO, KC_PIPE, KC_BSLS, XXXXXXX, _______,
     _______, _______, _______, _______, SYMLOCK, _______, _______, _______, _______, _______, _______, _______
 ),
/* Number
  |      |      |<-word|  up  |word->| PgUp |   .  |   7  |   8  |   9  |   +  |   *  |
  |      | Enter| left | down | right| PgDn |   0  |   4  |   5  |   6  |   -  |   /  |
  |      | Bksp | Home |  tab | End  | Del  |   ,  |   1  |   2  |   3  |   =  |   %  |
  |      |      |      |      | .... |             | LOCK |      |   :  |   $  |      |
 */
[_NUMBER] = LAYOUT_planck_grid(
    XXXXXXX, _______, BWORD,   KC_UP,   FWORD,   KC_PGUP, KC_DOT,  KC_7,    KC_8,    KC_9,    KC_PLUS, KC_ASTR,
    XXXXXXX, KC_ENT , KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_0,    KC_4,    KC_5,    KC_6,    KC_MINS, KC_SLSH,
    XXXXXXX, KC_BSPC, KC_HOME, KC_TAB,  KC_END,  KC_DEL,  KC_COMM, KC_1,    KC_2,    KC_3,    KC_EQL,  KC_PERC,
    _______, _______, _______, _______, _______, _______, _______, NUMLOCK, _______, KC_COLN, KC_DLR,  _______
),
/* Function
 * |      | Mctl | Pspc | Nwin | Nspc | Desk |      |  F7  |  F8  |  F9  | F10  | F13  |
 * |      | Nctr | Ptab | Pwin | Ntab |      |      |  F4  |  F5  |  F6  | F11  | F14  |
 * | Mute | Vol- | Vol+ | Trk- | Trk+ | Play |      |  F1  |  F2  |  F3  | F12  | F15  |
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 */
[_FUNC] = LAYOUT_planck_grid(
    XXXXXXX, XMSNCTL, XPRVSPC, NWIN,    XNXTSPC, XDSKTOP, XXXXXXX, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F13,
    XXXXXXX, XNOTIFY, PTAB,    PWIN,    NTAB,    XXXXXXX, XXXXXXX, KC_F4,   KC_F5,   KC_F6,   KC_F11,  KC_F14,
    KC_MUTE, KC_VOLD, KC_VOLU, KC_MRWD, KC_MFFD, KC_MPLY, XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F12,  KC_F15,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * | Reset| Debug|      |      |      |      |      |      |      |      |      |      |
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
    RESET,   DEBUG,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______
)


};

#ifdef AUDIO_ENABLE
#endif

uint32_t layer_state_set_user(uint32_t state) {
  /* state = update_tri_layer_state(state, _SYMBOL, _NUMBER, _ADJUST); */
  return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
  }
  return true;
}



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
//#include "muse.h"

enum preonic_layers {
  _QWERTY,
  _COLEMAK,
  _GAMING,
  _GMNGLR,
  _GMNGRS,
  _MEDIA,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum preonic_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  GAMING,
  GMNGLR,
  GMNGRS,
  MEDIA,
  LOWER,
  RAISE
};

enum combo_events {
  ZC_SCOPY,
  XV_SPASTE
  };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |  Esc |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |   \  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Leader|   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  |MEDIA | Alt  |Lower |Space | Bksp |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_preonic_grid( \
  KC_GESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,  \
  KC_LEAD,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,  \
  KC_LCTL,  KC_LGUI, MEDIA,   KC_LALT, LOWER,   KC_SPC,  LCTL(KC_BSPC),  RAISE,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT  \
),

/* Colemak DH
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   F  |   P  |   B  |   J  |   L  |   U  |   Y  |   ;  |  \   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Leader|   A  |   R  |   S  |   T  |   G  |   M  |   N  |   E  |   I  |   O  |  '   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   D  |   V  |   K  |   H  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  |Media | Alt  |Lower |Space |Leader|Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_COLEMAK] = LAYOUT_preonic_grid( \
  KC_GESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  KC_TAB,   KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSLS,  \
  KC_LEAD,  KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT, \
  KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,  \
  KC_LCTL,  KC_LGUI, MEDIA,   KC_LALT, LOWER,   KC_SPC,  KC_BSPC,  RAISE,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT  \
),

/* Media + Numpad
 * ,-----------------------------------------------------------------------------------.
 * |Player|      |      |      |      |      |      |      |   /  |   *  |   -  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Mute | VolU |      |      |      |      |      |   7  |   8  |   9  |   +  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | VolD | Prev | Next | Pause|      |      |   4  |   5  |   6  |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |   1  |   2  |   3  |Equal |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |   0  |      |   .  |Enter |      |
 * `-----------------------------------------------------------------------------------'
 */
[_MEDIA] = LAYOUT_preonic_grid( \
  KC_MSEL,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_PSLS,  KC_PAST,  KC_PMNS,  _______, \
  KC_MUTE,  KC_VOLU,  _______,  _______,  _______,  _______,  _______,  KC_KP_7,  KC_KP_8,  KC_KP_9,  KC_PPLS,  _______,  \
  _______,  KC_VOLD,  KC_MPRV,  KC_MNXT,  KC_MPLY,  _______,  _______,  KC_KP_4,  KC_KP_5,  KC_KP_6,  _______,  _______, \
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_KP_1,  KC_KP_2,  KC_KP_3,  KC_PEQL,  _______,  \
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_KP_0,  _______,  KC_PDOT,  KC_PENT,  _______  \
),

/* Lower (Numbers and Symbols)
 * ,----------------------------------------------------------------------------------.
 * | Mute |Ctrl+K|      |      |      |      |      |      |      |      |      | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  !   |   @  |   #  |   $  |  %   |   ^  |   &  |   *  |   (  |   )  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  1   |   2  |   3  |   4  |  5   |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  {   |   }  |   [  |   ]  |      |      |   -  |   _  |   =  |   +  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      | Home | PGDN | PGUP |  End |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_preonic_grid( \
  KC_MUTE, LGUI(KC_K), _______, _______,  _______, _______, _______, _______, _______, _______,  _______,  KC_DEL, \
  _______, KC_EXLM, KC_AT,   KC_HASH,  KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN,  KC_RPRN,  _______,  \
  _______, KC_1,    KC_2,    KC_3,     KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,     KC_0,     KC_GRV, \
  _______, KC_LCBR, KC_RCBR, KC_LBRC,  KC_RBRC, _______, _______, KC_MINS, KC_UNDS, KC_EQL,   KC_PLUS,  _______, \
  _______, _______, _______, _______,  _______, _______, _______, _______, KC_HOME, KC_PGDN,  KC_PGUP,  KC_END \
),

/* Raise
 * ,----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      | Del  | PGDN | PGUP |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F0  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |  F11 |  F12 |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_preonic_grid( \
  _______,  _______,  _______, _______, _______, _______,  _______,  _______,   _______,  _______,  _______,  KC_NUMLOCK, \
  _______,  KC_F1,    KC_F2,   KC_F3,   KC_F4,   _______,  KC_PGUP,  _______,   KC_UP,    _______,  _______,  KC_INS,  \
  _______,  KC_F5,    KC_F6,   KC_F7,   KC_F8,   _______,  KC_PGDN,  KC_LEFT,   KC_DOWN,  KC_RGHT,  _______,  _______, \
  _______,  KC_F9,    KC_F10,  KC_F11,  KC_F12,  _______,  _______,  _______,   _______,  _______,  _______,  _______, \
  _______,  _______,  _______, _______, _______, _______,  _______,  _______,   _______,  _______,  _______,  _______  \
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |Sleep |      |      |      |      |      |      |      |      |      |      |Wake  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Reset |      |      |ComboT|AudTog|      |      |Qwerty|Colemk|Gaming|      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_preonic_grid( \
  KC_SLEP, _______,  _______,   _______,   _______,   _______,   _______,   _______,   _______,  _______,  _______,  KC_WAKE,  \
  _______, _______,  _______,   _______,   _______,   _______,   _______,   _______,   _______,  _______,  _______,  _______,  \
  RESET,   _______,  _______,   CMB_TOG,   AU_TOG,    _______,   _______,   QWERTY,    COLEMAK,  GAMING,   _______,  _______, \
  _______, _______,  _______,   _______,   _______,   _______,   _______,   _______,   _______,  _______,  _______,  _______, \
  _______, _______,  _______,   _______,   _______,   _______,   _______,   _______,   _______,  _______,  _______,  _______  \
),

/* Gaming
 * ,-----------------------------------------------------------------------------------.
 * |  Esc |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |   \  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |GMNGRS|   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  |MEDIA | Alt  |GMNGLR|Space |Leader|Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_GAMING] = LAYOUT_preonic_grid( \
  KC_GESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,  \
  GMNGRS,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,  \
  KC_LCTL,  KC_LGUI, MEDIA,   KC_LALT, GMNGLR,  KC_SPC,  KC_LEAD, RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT  \
),

/* Gaming Lower
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  6   |  7   |  8   |  9   |  10  |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |  U   |  J   |  L   |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  K   |  P   |  O   |  M   |  I   |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_GMNGLR] = LAYOUT_preonic_grid( \
  _______, _______,  _______,   _______,   _______,   _______,   _______,   _______,   _______,  _______,  _______,  KC_DEL,  \
  KC_ENT,  KC_6,     KC_7,      KC_8,      KC_9,      KC_0,      _______,   _______,   _______,  _______,  _______,  _______,  \
  _______, _______,  _______,   KC_U,      KC_J,      KC_L,      _______,   _______,   _______,  _______,  _______,  _______, \
  _______, KC_K,     KC_P,      KC_O,      KC_M,      KC_I,      _______,   _______,   _______,  _______,  _______,  _______, \
  _______, _______,  _______,   _______,   _______,   _______,   _______,   _______,   _______,  _______,  _______,  _______  \
),

/* Gaming Raise
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |  /   |  ;   |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |  ,   |  .   |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_GMNGRS] = LAYOUT_preonic_grid( \
  _______, _______,  _______,   _______,   _______,   _______,   _______,   _______,   _______,  _______,  _______,  _______,  \
  _______, _______,  _______,   _______,   _______,   _______,   _______,   _______,   _______,  _______,  _______,  _______,  \
  _______, _______,  KC_SLSH,   KC_SCLN,   _______,   _______,   _______,   _______,   _______,  _______,  _______,  _______, \
  _______, _______,  KC_COMM,   KC_DOT,    _______,   _______,   _______,   _______,   _______,  _______,  _______,  _______, \
  _______, _______,  _______,   _______,   _______,   _______,   _______,   _______,   _______,  _______,  _______,  _______  \
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
        case COLEMAK:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_COLEMAK);
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
        case MEDIA:
          if (record->event.pressed) {
            layer_on(_MEDIA);
          } else {
            layer_off(_MEDIA);
          }
          return false;
          break;
        case GAMING:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_GAMING);
          }
          return false;
          break;
        case GMNGLR:
          if (record->event.pressed) {
            layer_on(_GMNGLR);
            update_tri_layer(_GMNGLR, _GMNGRS, _ADJUST);
          } else {
            layer_off(_GMNGLR);
            update_tri_layer(_GMNGLR, _GMNGRS, _ADJUST);
          }
          return false;
          break;
        case GMNGRS:
          if (record->event.pressed) {
            layer_on(_GMNGRS);
            update_tri_layer(_GMNGLR, _GMNGRS, _ADJUST);
          } else {
            layer_off(_GMNGRS);
            update_tri_layer(_GMNGLR, _GMNGRS, _ADJUST);
          }
          return false;
          break;
      }
    return true;
};

void encoder_update_user(uint8_t index, bool clockwise) {
  if(IS_LAYER_ON(_RAISE)) { // on Raise layer control volume
    if (clockwise){
      tap_code(KC_WH_D);
    } else{
      tap_code(KC_WH_U);
    }
} else if(IS_LAYER_ON(_LOWER)) {
	if (clockwise){
		tap_code(KC_VOLU);
	} else{
		tap_code(KC_VOLD);
	}
}
else{// on other layers page down or up
    if (clockwise){
      tap_code(KC_PGDN);
    } else{
      tap_code(KC_PGUP);
    }
  }
}

LEADER_EXTERNS();

void matrix_scan_user(void) {
	LEADER_DICTIONARY(){
		leading = false;
		leader_end();

        SEQ_ONE_KEY(KC_T){
		      SEND_STRING("sudo /etc/init.d/tomcat7 restart");
	      }
        SEQ_TWO_KEYS(KC_T,KC_T){
		      SEND_STRING("sudo /etc/init.d/tomcat7 stop");
	      }
        SEQ_THREE_KEYS(KC_T,KC_T,KC_T){
		      SEND_STRING("sudo /etc/init.d/tomcat7 start");
	      }
        SEQ_ONE_KEY(KC_COMM){
          SEND_STRING("sudo service delegosrv-"SS_TAP(X_TAB)"restart");
        }
        SEQ_TWO_KEYS(KC_COMM,KC_COMM){
          SEND_STRING("sudo service delegosrv-"SS_TAP(X_TAB)"stop");
        }
        SEQ_THREE_KEYS(KC_COMM,KC_COMM,KC_COMM){
          SEND_STRING("sudo service delegosrv- start");
          SEND_STRING(SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT));
        }
        SEQ_ONE_KEY(KC_M){
          SEND_STRING("sudo service delegomt-"SS_TAP(X_TAB)"restart");
        }
        SEQ_TWO_KEYS(KC_M,KC_M){
          SEND_STRING("sudo service delegomt-"SS_TAP(X_TAB)"stop");
        }
        SEQ_THREE_KEYS(KC_M,KC_M,KC_M){
          SEND_STRING("sudo service delegomt- start");
          SEND_STRING(SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT));
        }
        SEQ_ONE_KEY(KC_N){
          SEND_STRING("sudo service delegosecure-"SS_TAP(X_TAB)"restart");
        }
        SEQ_TWO_KEYS(KC_N,KC_N){
          SEND_STRING("sudo service delegosecure-"SS_TAP(X_TAB)"stop");
        }
        SEQ_THREE_KEYS(KC_N,KC_N,KC_N){
          SEND_STRING("sudo service delegosecure- start");
          SEND_STRING(SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT));
        }
	      SEQ_ONE_KEY(KC_V){
		      SEND_STRING("sudo puppet agent --test");
	    }
        SEQ_TWO_KEYS(KC_V,KC_V){
		      SEND_STRING("sudo puppet agent --disable ");
          SEND_STRING(SS_LSFT("'"));
          SEND_STRING(SS_LSFT("'"));
          SEND_STRING(SS_TAP(X_LEFT));
	      }
        SEQ_THREE_KEYS(KC_V,KC_V,KC_V){
		      SEND_STRING("sudo puppet agent --enable");
	      }
        SEQ_TWO_KEYS(KC_D,KC_H){
          SEND_STRING("delego-home.sh");
        }
        SEQ_ONE_KEY(KC_P){
          SEND_STRING(SS_LCTRL(SS_LSFT("p")));
        }
	      SEQ_ONE_KEY(KC_T){
	    	  SEND_STRING(SS_LCTRL(SS_LALT("t")));
	      }
        SEQ_ONE_KEY(KC_BSPC){
          SEND_STRING(SS_LCTRL("`"));
        }
        SEQ_ONE_KEY(KC_F){
          SEND_STRING(SS_LCTRL("k0"));
        }
        SEQ_TWO_KEYS(KC_F,KC_F){
            SEND_STRING(SS_LCTRL("kj"));
        }
        SEQ_TWO_KEYS(KC_T,KC_S){
          SEND_STRING("export PYTHONWARNINGS=ignore;uname -r && test_ws_secure.py && test_ws_mt.py `test_ws_secure.py` && testCE.sh && grep ");
          SEND_STRING(SS_LSFT("'"));
          SEND_STRING("Connected with SAP");
          SEND_STRING(SS_LSFT("'"));
          SEND_STRING(" /var/log/delego/*/*/Delego*`date +%Y-%m-%d`.log");
        }
        SEQ_THREE_KEYS(KC_T,KC_S,KC_S){
          SEND_STRING("export PYTHONWARNINGS=ignore;uname -r && test_ws_secure.py && test_ws_mt.py `test_ws_secure.py`");
        }
        SEQ_FOUR_KEYS(KC_T,KC_S,KC_S,KC_S){
          SEND_STRING("uname -r && testCE.sh");
        }
	      SEQ_ONE_KEY(KC_1){
		      SEND_STRING(SS_TAP(X_LGUI));
		      wait_ms(175);
		      SEND_STRING("cmd");
		      wait_ms(175);
		      SEND_STRING(SS_TAP(X_ENTER));
		      wait_ms(500);
		      SEND_STRING(SS_LSFT("'")"AWSMulti.bat"SS_LSFT("'")SS_TAP(X_ENTER));
	      }
        SEQ_ONE_KEY(KC_4){
            SEND_STRING(SS_LCTRL(SS_TAP(X_F4)));
        }
        SEQ_FOUR_KEYS(KC_F,KC_I,KC_L,KC_L){
            SEND_STRING("Christian"SS_TAP(X_TAB));
            SEND_STRING("Eguaras"SS_TAP(X_TAB));
            SEND_STRING("email@email.com"SS_TAP(X_TAB)SS_TAP(X_TAB)SS_TAP(X_TAB)SS_TAP(X_TAB));
        }
	}
}

// const uint16_t PROGMEM copy_combo[] = {KC_Z, KC_C, COMBO_END};
// const uint16_t PROGMEM paste_combo[] = {KC_X, KC_V, COMBO_END};

// combo_t key_combos[COMBO_COUNT] = {
//     [ZC_SCOPY] = COMBO_ACTION(copy_combo),
//     [XV_SPASTE] = COMBO_ACTION(paste_combo),
//     };

// void process_combo_event(uint8_t combo_index, bool pressed) {
//   switch(combo_index) {
//     case ZC_SCOPY:
//       if (pressed) {
//         register_code(KC_LCTL);
//         register_code(KC_INSERT);
//         unregister_code(KC_INSERT);
//         unregister_code(KC_LCTL);
//       }
//       break;

//     case XV_SPASTE:
//       if (pressed) {
//         register_code(KC_LSFT);
//         register_code(KC_INSERT);
//         unregister_code(KC_INSERT);
//         unregister_code(KC_LSFT);
//       }
//       break;
//     }
// }

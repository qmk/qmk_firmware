/* Copyright 2018 Josh Turner (/u/tdl-jturner)
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

enum xd75_layers {
  _QWERTY,
  _COLEMAK,
  _LYMD,
  _LYFK,
  _LYMED,
  _LYNUM,
  _LYNAV,
  _LYMOS,
  _LYSYS,
  _LYLT
};

enum xd75_keycodes {
  HELP = SAFE_RANGE,
  KC_BSDEL,
  KC_FBSLH,
  KC_DOTQ,
  KC_CPIPE,
  COLEMAK,
  QWERTY,
  KC_LYDEF
};

//Tap Dance Declarations
enum {
  TD_LOCK_SLEEP,
  TD_ABK,
  TD_BRC,
  TD_CBR,
};

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Esc, twice for Caps Lock
  [TD_LOCK_SLEEP]  = ACTION_TAP_DANCE_DOUBLE(LGUI(KC_L), KC_SLEP),
  [TD_ABK] = ACTION_TAP_DANCE_DOUBLE(KC_LABK,KC_RABK),
  [TD_BRC] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC,KC_RBRC),
  [TD_CBR] = ACTION_TAP_DANCE_DOUBLE(KC_LCBR,KC_RCBR)
// Other declarations would go here, separated by commas, if you have them
};

//remaps for pretty layouts
#define ________ KC_TRNS
#define ___XX___ KC_NO


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 //QWERY - Base Layer
 [_QWERTY] = LAYOUT_ortho_5x15(
         KC_GRV ,  KC_1  ,  KC_2  ,  KC_3  ,  KC_4  ,  KC_5  ,________  ,________,________,  KC_6  ,  KC_7  ,  KC_8  ,  KC_9  ,  KC_0  ,KC_MINUS,
         KC_TAB ,  KC_Q  ,  KC_W  ,  KC_E  ,  KC_R  ,  KC_T  ,________  ,________,________,  KC_Y  ,  KC_U  ,  KC_I  ,  KC_O  ,  KC_P  ,KC_BSDEL, //Custom shift Codes. Backspace ^ Delete
LT(_LYMD,KC_ESC),  KC_A  ,  KC_S  ,  KC_D  ,  KC_F  ,  KC_G  ,________  ,________,________,  KC_H  ,  KC_J  ,  KC_K  ,  KC_L  ,KC_SCLN ,KC_QUOT,
         SC_LSPO,  KC_Z  ,  KC_X  ,  KC_C  ,  KC_V  ,  KC_B  ,________  ,________,________,  KC_N  ,  KC_M  ,KC_CPIPE,KC_DOTQ ,KC_FBSLH,SC_RSPC, // Custom Shift Codes. ,^| .^?  /^|
      KC_MEH ,KC_LCTL ,KC_LGUI ,KC_LALT ,MO(_LYNUM), KC_SPC ,________  ,________,________, KC_ENT ,MO(_LYNAV),TD(TD_CBR) ,TD(TD_BRC),TD(TD_ABK),TD(TD_LOCK_SLEEP)

 ),

 //_COLEMAK - Colemak Layout - Identical to qwerty layer except for the layout changes
 [_COLEMAK] = LAYOUT_ortho_5x15(
         KC_GRV ,  KC_1  ,  KC_2  ,  KC_3  ,  KC_4  ,  KC_5  ,________  ,________,________,  KC_6  ,  KC_7  ,  KC_8  ,  KC_9  ,  KC_0  ,KC_MINUS,
         KC_TAB ,  KC_Q  ,  KC_W  ,  KC_F  ,  KC_P  ,  KC_G  ,________  ,________,________,  KC_J  ,  KC_L  ,  KC_U  ,  KC_Y  ,KC_SCLN ,KC_BSDEL, //Custom shift Codes. Backspace ^ Delete
LT(_LYMD,KC_ESC),  KC_A  ,  KC_R  ,  KC_S  ,  KC_T  ,  KC_D  ,________  ,________,________,  KC_H  ,  KC_N  ,  KC_E  ,  KC_I  ,  KC_O  ,KC_QUOT,
         SC_LSPO,  KC_Z  ,  KC_X  ,  KC_C  ,  KC_V  ,  KC_B  ,________  ,________,________,  KC_K  ,  KC_M  ,KC_CPIPE,KC_DOTQ ,KC_FBSLH,SC_RSPC, // Custom Shift Codes. ,^| .^?  /^|
     KC_MEH ,KC_LCTL ,KC_LGUI ,KC_LALT ,MO(_LYNUM), KC_SPC ,________  ,________,________, KC_ENT ,MO(_LYNAV),TD(TD_CBR) ,TD(TD_BRC),TD(TD_ABK),TD(TD_LOCK_SLEEP)

 ),

 // Decision Layer
 [_LYMD] =
    LAYOUT_ortho_5x15(
       ________,________  ,________  ,________  ,________,________,___XX___,___XX___,___XX___,___XX___,___XX___,___XX___,___XX___,___XX___,___XX___,
       ________,MO(_LYFK) ,MO(_LYMED),________  ,________,________,___XX___,___XX___,___XX___,___XX___,___XX___,___XX___,___XX___,___XX___,________,
       ________,MO(_LYNUM),MO(_LYNAV),________  ,________,________,___XX___,___XX___,___XX___,___XX___,___XX___,___XX___,___XX___,___XX___,___XX___,
       ________,MO(_LYMOS),MO(_LYSYS),MO(_LYLT) ,________,________,___XX___,___XX___,___XX___,___XX___,___XX___,___XX___,___XX___,___XX___,___XX___,
       ________,________  ,________  ,________  ,________,________,________,________,________,________,___XX___,___XX___,___XX___,___XX___,___XX___
     ),

 //F Keys
 [_LYFK] =
    LAYOUT_ortho_5x15(
      ________,________,________,________,________,________,___XX___,___XX___,___XX___,___XX___,___XX___,___XX___,___XX___,___XX___,___XX___,
      KC_LYDEF,________,________,________,________,________,___XX___,___XX___,___XX___,___XX___,KC_F7   ,KC_F8   ,KC_F9   ,KC_F12  ,________,
      ________,________,________,________,________,________,___XX___,___XX___,___XX___,___XX___,KC_F4   ,KC_F5   ,KC_F6   ,KC_F11  ,___XX___,
      ________,________,________,________,________,________,___XX___,___XX___,___XX___,___XX___,KC_F1   ,KC_F2   ,KC_F3   ,KC_F10  ,___XX___,
      ________,________,________,________,________,________,________,________,________,________,___XX___,___XX___,___XX___,___XX___,___XX___
    ),
//Media Keys
[_LYMED] =
   LAYOUT_ortho_5x15(
     ________,________,________,________,________,________,___XX___,___XX___,___XX___,___XX___,___XX___,___XX___,___XX___,___XX___,___XX___,
     KC_LYDEF,________,________,________,________,________,___XX___,___XX___,___XX___,___XX___,___XX___,KC_VOLU ,___XX___,___XX___,________,
     ________,________,________,________,________,________,___XX___,___XX___,___XX___,___XX___,KC_MPRV ,KC_MUTE ,KC_MNXT ,___XX___,___XX___,
     ________,________,________,________,________,________,___XX___,___XX___,___XX___,___XX___,___XX___,KC_VOLD ,___XX___,KC_MSTP ,___XX___,
     ________,________,________,________,________,________,___XX___,___XX___,___XX___,___XX___,KC_MPLY ,___XX___,___XX___,___XX___,___XX___
   ),
//Num Keys
[_LYNUM] =
  LAYOUT_ortho_5x15(
    ________,________,________,________,________,________,___XX___,___XX___,___XX___,___XX___,KC_PEQL ,KC_PSLS ,KC_PAST ,KC_PMNS ,___XX___,
    KC_LYDEF,________,________,________,________,________,___XX___,___XX___,___XX___,___XX___,KC_7    ,KC_8    ,KC_9    ,KC_MINUS,________,
    ________,________,________,________,________,________,___XX___,___XX___,___XX___,___XX___,KC_4    ,KC_5    ,KC_6    ,KC_PPLS ,KC_PSLS,
    ________,________,________,________,________,________,___XX___,___XX___,___XX___,___XX___,KC_1    ,KC_2    ,KC_3    ,KC_PENT ,KC_PAST,
    ________,________,________,________,________,________,________,________,________,________,KC_0    ,KC_0    ,KC_PDOT ,KC_PEQL ,___XX___
  ),
//Navigation Keys
[_LYNAV] =
 LAYOUT_ortho_5x15(
   ________,________,________,________,________,________,___XX___,___XX___,___XX___,___XX___,___XX___,___XX___,___XX___,___XX___,___XX___,
   KC_LYDEF,________,________,________,________,________,___XX___,___XX___,___XX___,___XX___,KC_HOME ,KC_UP   ,KC_PGUP ,KC_PSCR ,________,
   ________,________,________,________,________,________,___XX___,___XX___,___XX___,___XX___,KC_LEFT ,KC_F5   ,KC_RIGHT,KC_SCRL ,___XX___,
   ________,________,________,________,________,________,___XX___,___XX___,___XX___,___XX___,KC_END  ,KC_DOWN ,KC_PGDN ,KC_PAUS ,___XX___,
   ________,________,________,________,________,________,________,________,________,________,________,KC_INS  ,KC_DEL  ,___XX___,___XX___
 ),
 //Mouse Keys
 [_LYMOS] =
  LAYOUT_ortho_5x15(
    ________,________,________,________,________,________,___XX___,___XX___,___XX___,___XX___,___XX___,___XX___,___XX___,___XX___,___XX___,
    KC_LYDEF,________,________,________,________,________,___XX___,___XX___,___XX___,___XX___,___XX___,KC_MS_U ,KC_WH_U ,KC_ACL2 ,________,
    _______,________,________,________,________,________,___XX___,___XX___,___XX___,___XX___,KC_MS_L ,KC_ACL0 ,KC_MS_R ,KC_ACL1 ,___XX___,
    ________,________,________,________,________,________,___XX___,___XX___,___XX___,___XX___,___XX___,KC_MS_D ,KC_WH_D ,KC_BTN2 ,___XX___,
    ________,________,________,________,________,________,________,________,________,________,KC_BTN1 ,KC_BTN3 ,KC_BTN4 ,___XX___,___XX___
  ),
  //Systen Keys
  [_LYSYS] =
   LAYOUT_ortho_5x15(
     ________,________,________,________,________,________,___XX___,___XX___,___XX___,___XX___,___XX___,___XX___,___XX___,___XX___,___XX___,
     KC_LYDEF,________,________,________,________,________,___XX___,___XX___,___XX___,___XX___,___XX___,___XX___,___XX___,___XX___,________,
     ________,________,________,________,________,________,___XX___,___XX___,___XX___,___XX___,___XX___,QWERTY  ,COLEMAK ,___XX___,QK_BOOT,
     ________,________,________,________,________,________,___XX___,___XX___,___XX___,___XX___,___XX___,___XX___,___XX___,___XX___,___XX___,
     ________,________,________,________,________,________,________,________,________,________,___XX___,___XX___,___XX___,___XX___,___XX___
   ),

// Light Control
[_LYLT] =
  LAYOUT_ortho_5x15(
     ________,________,________,________,________,________,___XX___,___XX___,___XX___,___XX___,___XX___,___XX___,___XX___,___XX___,___XX___,
     KC_LYDEF,________,________,________,________,________,___XX___,___XX___,___XX___,RGB_HUD ,RGB_HUI ,RGB_SAD ,RGB_SAI ,RGB_VAD ,RGB_VAI,
     ________,________,________,________,________,________,___XX___,___XX___,___XX___,RGB_TOG ,RGB_RMOD,RGB_MOD ,___XX___,___XX___,___XX___,
     ________,________,________,________,________,________,___XX___,___XX___,___XX___,BL_TOGG ,BL_DOWN ,BL_UP   ,BL_BRTG ,___XX___,___XX___,
     ________,________,________,________,________,________,________,________,________,________,___XX___,___XX___,___XX___,___XX___,___XX___
  )
};

//Define layer colors
#define rgblight_setrgb_user_base()  rgblight_sethsv(325,255,255)
#define rgblight_setrgb_user_LYFK()  rgblight_sethsv(HSV_RED)
#define rgblight_setrgb_user_LYMED() rgblight_sethsv(HSV_BLUE)
#define rgblight_setrgb_user_LYNUM() rgblight_sethsv(HSV_PURPLE)
#define rgblight_setrgb_user_LYNAV() rgblight_sethsv(HSV_CYAN)
#define rgblight_setrgb_user_LYMOS() rgblight_sethsv(HSV_ORANGE)
#define rgblight_setrgb_user_LYSYS() rgblight_sethsv(HSV_GREEN)
#define rgblight_setrgb_user_LYLT()  rgblight_sethsv(HSV_YELLOW)
#define rgblight_setrgb_user_LYMD()  rgblight_sethsv(HSV_WHITE)

//initialize rgb
void matrix_init_user(void) {
  rgblight_enable();
  rgblight_mode(1);
  rgblight_setrgb_user_base();
}

//Set a color based on the layer
layer_state_t layer_state_set_user(layer_state_t state) {
  switch(get_highest_layer(state)) {
    case _LYFK:
      rgblight_setrgb_user_LYFK();
      break;
    case _LYMED:
      rgblight_setrgb_user_LYMED();
      break;
    case _LYNUM:
      rgblight_setrgb_user_LYNUM();
      break;
    case _LYNAV:
      rgblight_setrgb_user_LYNAV();
      break;
    case _LYMOS:
      rgblight_setrgb_user_LYMOS();
      break;
    case _LYSYS:
      rgblight_setrgb_user_LYSYS();
      break;
    case _LYLT:
      rgblight_setrgb_user_LYLT();
      break;
    case _LYMD:
      rgblight_setrgb_user_LYMD();
      break;
    default:
      rgblight_setrgb_user_base();
      break;
  }
  return state;
}


//Const for shift
const uint8_t shift = MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT);

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch(keycode) {
    case KC_LYDEF:
      layer_clear();
      return false;
      break;
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
    case KC_BSDEL:
      if (record->event.pressed) {
        if (keyboard_report->mods & shift) {
          if (keyboard_report->mods & MOD_BIT(KC_LSFT)) {
            unregister_code(KC_LEFT_SHIFT);
          }
          else {
            unregister_code(KC_RIGHT_SHIFT);
          }
          register_code(KC_DEL);
        }
        else {
          register_code(KC_BSPC);
        }
      }
      else {
        unregister_code(KC_DEL);
        unregister_code (KC_BSPC);
      }
      return false;
      break;
    case KC_FBSLH:
      if (record->event.pressed) {
        if (keyboard_report->mods & shift) {
            if (keyboard_report->mods & MOD_BIT(KC_LSFT)) {
              unregister_code(KC_LEFT_SHIFT);
            }
            else {
              unregister_code(KC_RIGHT_SHIFT);
            }
          register_code(KC_BACKSLASH);
        }
        else {
          register_code(KC_SLSH);
        }
      }
      else {
        unregister_code(KC_BACKSLASH);
        unregister_code (KC_SLSH);
      }
      return false;
      break;
    case KC_DOTQ:
      if (record->event.pressed) {
        if (keyboard_report->mods & shift) {
          register_code(KC_SLSH); // shifted slash = ?
        }
        else {
          register_code(KC_DOT);
        }
      }
      else {
        unregister_code(KC_SLSH); // shifted slash = ?
        unregister_code (KC_DOT);
      }
      return false;
      break;
    case KC_CPIPE:
      if (record->event.pressed) {
        if (keyboard_report->mods & shift) {
          register_code(KC_BSLS);
        }
        else {
          register_code(KC_COMM);
        }
      }
      else {
        unregister_code(KC_BSLS);
        unregister_code (KC_COMM);
      }
      return false;
      break;
    }
    return true;
};

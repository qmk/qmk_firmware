#ifndef XD75_DRZ_LAYOUT_MIRRORED

/*
Drzoid's mirrored 5x15 ortho layout
This layout:
  -> http://www.keyboard-layout-editor.com/#/gists/a59dd1a00a45c5dcd38d9e765675dd41
*/
#include QMK_KEYBOARD_H
#include "config.h"
#include "keymap.h"
#include "keymap_french.h"

#define _QWERTY 0
#define _QWERTY_ON_INTL_QWERTY 0
#define _QWERTY_ON_FR_AZERTY 0
#define _L2 1
#define _L3 2
#define _FN 3

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  FN,
  L2,
  L3,
  DRZ_LOCK,
  DRZ_SWAP_HANDS,
  DRZ_LEFT_SHIFT_CAPSLOCK,
  DRZ_RIGHT_SHIFT_CAPSLOCK,
  DRZ_ACCENTS_TAPDANCE,
  DRZ_EMOJIS_TAPDANCE
};

enum custom_macros {
  DRZ_MACRO_COMMENT_START,
  DRZ_MACRO_COMMENT_END
};

//Unicode chars
#define DRZ_UC_STAR     RALT(UC(0x2605))    // ★
#define DRZ_UC_SQUARE   RALT(UC(0x00B2))    // ²
#define DRZ_UC_CUBE     RALT(UC(0x00B3))    // ³

//uni-sized keycodes for keymap uses
#define DRZ_UST  DRZ_UC_STAR
#define DRZ_USQ  DRZ_UC_SQUARE
#define DRZ_UCU  DRZ_UC_CUBE
#define DRZ_LCK  DRZ_LOCK
#define DRZ__ST  LSFT(KC_TAB)
#define DRZ__SH  DRZ_SWAP_HANDS
#define DRZ__LS  KC_LSHIFT
#define DRZ__RS  KC_RSHIFT
#define DRZ__AC  DRZ_ACCENTS_TAPDANCE
#define DRZ__EM  DRZ_EMOJIS_TAPDANCE
#define DRZ__CA  LCTL(KC_LALT)
#define DRZ__CS  LCTL(KC_LSHIFT)
#define DRZ__EU  LCTL(RALT(KC_E))
#define DRZ_MCS  M(DRZ_MACRO_COMMENT_START)
#define DRZ_MCE  M(DRZ_MACRO_COMMENT_END)

#define DRZ_AZERTY_FR_OS       /* Qwerty keycaps & layout with Azerty French OS */
//#define DRZ_QWERTY_INTL_OS     /* Qwerty keycaps & layout with Qwerty Intl OS */

/*\ ------------------------------------------------------*/
//  QWERTY KEYMAP ON QWERTY INTL OS !
/*\-------------------------------------------------------*/


#ifdef DRZ_QWERTY_INTL_OS
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY_ON_INTL_QWERTY] =
    KEYMAP(
      DRZ_LCK,  KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     _______,  KC_6,    KC_7,      KC_8,     KC_9,    KC_0,      KC_ESC,   DRZ_LCK,
      MO(_FN),  KC_LGUI,  KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     _______,  KC_Y,    KC_U,      KC_I,     KC_O,    KC_P,      KC_LGUI,  MO(_FN),
      MO(_L3),  KC_LALT,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     _______,  KC_H,    KC_J,      KC_K,     KC_L,    KC_SCLN,   KC_LALT,  MO(_L3),
      MO(_L2),  DRZ__LS,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     _______,  KC_N,    KC_M,      _______,  KC_UP,   KC_COLN,   DRZ__RS,  MO(_L2),
      DRZ__SH,  KC_LCTL,  DRZ__AC,  DRZ__EM,  KC_MENU,  KC_SPC,   KC_SPC,   KC_ENT,   KC_SPC,  KC_SPC,    KC_LEFT,  KC_DOWN, KC_RGHT,   KC_RCTL,  DRZ__SH
    ),

  [_FN] =
    KEYMAP(
      _______,  _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    _______,  KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   _______,  _______,
      _______,  _______,  KC_F11,   KC_F12,   KC_F13,   KC_F14,   KC_F15,   _______,  KC_F16,   KC_F17,   KC_F18,   KC_F19,   KC_F20,   _______,  _______,
      _______,  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  _______,  _______,
      _______,  _______,  KC_PSCR,  KC_CALC,  KC_PAUS,  XXXXXXX,  XXXXXXX,  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  _______,  _______,
      _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______
    ),

  [_L2] =
    KEYMAP(
      _______,  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX, KC_QUOT, KC_DQT,     _______,   XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_UNDS, KC_EQL,   _______,  _______,
      _______,  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, KC_LBRC,    _______,   KC_RBRC,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX,  _______,  _______,
      _______,  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, KC_LPRN,    _______,   KC_RPRN,  XXXXXXX,  XXXXXXX,  XXXXXXX, KC_EXLM,  _______,  _______,
      _______,  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, KC_LCBR,    _______,   KC_RCBR,  XXXXXXX,  KC_PIPE,  KC_PGUP, KC_QUES,  _______,  _______,
      _______,  DRZ__CA,  _______,  _______,  _______, KC_BSPC, DRZ_ST,     _______,   KC_TAB,   KC_DELT,  KC_HOME,  KC_PGDN, KC_END,   DRZ__CA,  _______
    ),

  [_L3] =
    KEYMAP(
      _______,  _______,  KC_TILD,  DRZ_USQ,  DRZ_UCU,  XXXXXXX, KC_GRV,    _______,   KC_ASTR,  XXXXXXX,  XXXXXXX,  KC_MINS, KC_PLUS,  _______,  _______,
      _______,  _______,  XXXXXXX,  XXXXXXX,  DRZ_EU ,  XXXXXXX, KC_BSLS,   _______,   KC_SLASH, XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX,  _______,  _______,
      _______,  _______,  XXXXXXX,  KC_DLR,   XXXXXXX,  XXXXXXX, KC_LABK,   _______,   KC_RABK,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX,  _______,  _______,
      _______,  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, DRZ_MCS,   _______,   DRZ_MCE,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX,  _______,  _______,
      _______,  DRZ__CS,  _______,  _______,  _______,  _______, _______,   _______,   _______,  _______,  _______,  _______, _______,  DRZ__CS,  _______
    )

};
#endif

/*\ ------------------------------------------------------*/
//  QWERTY KEYMAP ON AZERTY OS !
/*\-------------------------------------------------------*/

#ifdef DRZ_AZERTY_FR_OS

#define DRZ_TIL RALT(FR_EACU) //  ~ (tilde)
#define DRZ_SBL RALT(FR_LPAR) //  [ (square bracket left)
#define DRZ_SBR RALT(FR_RPAR) //  ] (square bracket right)
#define DRZ_CBL RALT(FR_APOS) //  { (curly bracket left)
#define DRZ_CBR RALT(FR_EQUA) //  } (curly bracket right)
#define DRZ_PIP RALT(FR_MOIN) //  | (pipe)
#define DRZ_INT LSFT(FR_COMM) //  ? (interrogation mark)
#define DRZ_SQT RALT(FR_EGRV) //  ` (special quote ?)
#define DRZ_ASL LALT(FR_UNDS) //  \ (antislash)
#define DRZ_SUP LSFT(FR_LESS) //  > (superior)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY_ON_FR_AZERTY] =
    KEYMAP(
      DRZ_LCK,  KC_ESC,   FR_1,     FR_2,     FR_3,     FR_4,     FR_5,     _______,  FR_6,     FR_7,     FR_8,     FR_9,     FR_0,     KC_ESC,   DRZ_LCK,
      MO(_FN),  KC_LGUI,  FR_Q,     FR_W,     FR_E,     FR_R,     FR_T,     _______,  FR_Y,     FR_U,     FR_I,     FR_O,     FR_P,     KC_LGUI,  MO(_FN),
      MO(_L3),  KC_LALT,  FR_A,     FR_S,     FR_D,     FR_F,     FR_G,     _______,  FR_H,     FR_J,     FR_K,     FR_L,     FR_SCLN,  KC_LALT,  MO(_L3),
      MO(_L2),  DRZ__LS,  FR_Z,     FR_X,     FR_C,     FR_V,     FR_B,     _______,  FR_N,     FR_M,     _______,  KC_UP,    FR_COLN,  DRZ__RS,  MO(_L2),
      DRZ__SH,  KC_LCTL,  DRZ__AC,  DRZ__EM,  KC_MENU,  KC_SPC,   KC_SPC,   KC_ENT,   KC_SPC,   KC_SPC,   KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_RCTL,  DRZ__SH
    ),

  [_FN] =
    KEYMAP(
      _______,  _______,  FR_F1,    FR_F2,    FR_F3,    FR_F4,    FR_F5,    _______,  FR_F6,    FR_F7,    FR_F8,    FR_F9,    FR_F10,   _______,  _______,
      _______,  _______,  FR_F11,   FR_F12,   FR_F13,   FR_F14,   FR_F15,   _______,  FR_F16,   FR_F17,   FR_F18,   FR_F19,   FR_F20,   _______,  _______,
      _______,  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  _______,  _______,
      _______,  _______,  KC_PSCR,  KC_CALC,  KC_PAUS,  XXXXXXX,  XXXXXXX,  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  _______,  _______,
      _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______
    ),

  [_L2] =
    KEYMAP(
      _______,  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX, FR_APOS, FR_QUOT,    _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  FR_UNDS,  FR_EQUA,  _______,  _______,
      _______,  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, DRZ_SBL,    _______,  DRZ_SBL,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  _______,  _______,
      _______,  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, FR_LPAR,    _______,  FR_RPAR,  XXXXXXX,  XXXXXXX,  XXXXXXX,  FR_EXCL,  _______,  _______,
      _______,  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, DRZ_CBL,    _______,  DRZ_CBR,  XXXXXXX,  DRZ_PIP,  FR_PGUP,  DRZ_INT,  _______,  _______,
      _______,  DRZ__CA,  _______,  _______,  _______, FR_BSPC, DRZ__ST,    _______,  FR_TAB,   FR_DEL,   FR_HOME,  FR_PGDN,  FR_END,   DRZ__CA,  _______
    ),

  [_L3] =
    KEYMAP(
      _______,  _______,  DRZ_TIL,  DRZ_USQ,  DRZ_UST,  XXXXXXX, DRZ_SQT,   _______,  FR_AST,   XXXXXXX,  XXXXXXX,  FR_MINS,  FR_PLUS,  _______,  _______,
      _______,  _______,  XXXXXXX,  XXXXXXX,  DRZ__EU,  XXXXXXX, DRZ_ASL,   _______,  FR_SLSH,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  _______,  _______,
      _______,  _______,  XXXXXXX,  FR_DLR,   XXXXXXX,  XXXXXXX, FR_LESS,   _______,  DRZ_SUP,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  _______,  _______,
      _______,  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, DRZ_MCS,   _______,  DRZ_MCE,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  _______,  _______,
      _______,  DRZ__CS,  _______,  _______,  _______,  _______, _______,   _______,  _______,  _______,  _______,  _______,  _______,  DRZ__CS,  _______
    )

};
#endif

/*\ ------------------------------------------------------*/
//  SETUP ACTIONS
//  - Set unicode input mode
/*\-------------------------------------------------------*/
void matrix_init_user(void) {
  set_unicode_input_mode(UC_WINC);
}

/*\ ------------------------------------------------------*/
//  LOOP ACTIONS
//  - nothing yet
/*\-------------------------------------------------------*/
void matrix_scan_user(void) {

}

/*\ ------------------------------------------------------*/
//  MACRO ACTIONS
//  - Comment start:  / *
//  - Comment end:    * /
/*\-------------------------------------------------------*/
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
	switch (id) {

    //->  /*
    case DRZ_MACRO_COMMENT_START:
      if(IS_PRESSED(record->event)) {
        return MACRO(T(KP_SLASH), T(KP_ASTERISK), END);
      }
    break;

    //->  */
    case DRZ_MACRO_COMMENT_END:
      if(IS_PRESSED(record->event)) {
        return MACRO(T(KP_ASTERISK), T(KP_SLASH), END);
      }
    break;

    /* Sample from fredizzimo:
    case 10001:
      if (record->event.pressed) {
        if (keyboard_report->mods & MOD_BIT(KC_LSFT) || keyboard_report->mods & MOD_BIT(KC_RSFT)) { // when shift is pressed
            unregister_code(KC_LSHIFT);
            register_code(FR_EXCL); // register !
        } else { // if shift is not pressed
            register_code(FR_1);    // register 1
        }
      } else {
        if (keyboard_report->mods & MOD_BIT(KC_LSFT) || keyboard_report->mods & MOD_BIT(KC_RSFT)) { // when shift is pressed
            unregister_code(FR_EXCL);
        } else { // if shift is not pressed
            unregister_code(FR_1);
        }
      }
    break;
    */
	}
	return MACRO_NONE;
}

void press_key_with_level_mods(uint16_t key) {
    const uint8_t interesting_mods = MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT) | MOD_BIT(KC_RALT);

    // Save the state
    const uint8_t real_mods = get_mods();
    const uint8_t weak_mods = get_weak_mods();
    const uint8_t macro_mods = get_macro_mods();

    uint8_t target_mods = (key >> 8) & (QK_MODS_MAX >> 8);
    // The 5th bit indicates that it's a right hand mod,
    // which needs some fixup
    if (target_mods & 0x10) {
        target_mods &= 0xF;
        target_mods <<= 4;
    }

    // Clear the mods that we are potentially going to modify,
    del_mods(interesting_mods);
    del_weak_mods(interesting_mods);
    del_macro_mods(interesting_mods);

    // Enable the mods that we need
    add_mods(target_mods & interesting_mods);

    // Press and release the key
    register_code(key & 0xFF);
    unregister_code(key & 0xFF);

    // Restore the previous state
    set_mods(real_mods);
    set_weak_mods(weak_mods);
    set_macro_mods(macro_mods);
    send_keyboard_report();
}

bool override_key(keyrecord_t* record, uint16_t normal, uint16_t shifted) {
    const uint8_t shift = MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT);
    // Todo, should maybe also check at least the weak mods
    uint8_t current_mods = get_mods();
    if (record->event.pressed) {
        // Todo share this code with send keyboard report
#ifndef NO_ACTION_ONESHOT
        if (get_oneshot_mods()) {
#if (defined(ONESHOT_TIMEOUT) && (ONESHOT_TIMEOUT > 0))
            if (has_oneshot_mods_timed_out()) {
                dprintf("Oneshot: timeout\n");
                clear_oneshot_mods();
            }
#endif
            current_mods |= get_oneshot_mods();
            clear_oneshot_mods();
        }
#endif
        bool shift_pressed = current_mods & shift;
        const uint16_t target = shift_pressed ? shifted : normal;
        uint8_t keycode = target & 0xFF;
        if (keycode == KC_NO) {
            return false;
        }
        press_key_with_level_mods(target);
    }
    return false;
}

/*
static bool wake_dead_key(uint16_t keycode, keyrecord_t* record) {
    if (record->event.pressed) {
        register_code16(keycode);
        unregister_code16(keycode);
        register_code16(KC_SPACE);
        unregister_code16(KC_SPACE);
    }
    // Let QMK handle onshots
    return true;
}
*/

/*\ ------------------------------------------------------*/
//  LAYER CHANGE ACTIONS
//  - L2, L3, and FN layers to RGB underglow mapping
/*\-------------------------------------------------------*/
uint32_t layer_state_set_user(uint32_t state) {

    //Store current value to put back after
    uint16_t h = rgblight_get_hue();
    uint8_t s = rgblight_get_sat();
    uint8_t v = rgblight_get_val();

    //Set layer rgb color or reset to original value
    switch (biton32(state)) {
      case _FN:
          rgblight_setrgb_azure();
          break;
      case _L2:
          rgblight_setrgb_pink();
          break;
      case _L3:
          rgblight_setrgb_purple();
          break;
      default:
          //Put back to original value
          rgblight_sethsv(h, s, v);
          break;
    }

  return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  bool returnValue = true;

  //Fait rien sur les touches de layer
  switch(keycode) {

    case TO(_FN):
    case TO(_L2):
    case TO(_L3):
      return true;
    break;

    case FR_1:  //!
        returnValue = override_key(record, FR_1, FR_EXCL);
        break;
    case FR_2:  //~
        returnValue = override_key(record, FR_2, RALT(KC_0));
        break;
    case FR_3:  //#
        returnValue = override_key(record, FR_3, RALT(KC_3));
        break;
    case FR_4:  //$
        returnValue = override_key(record, FR_4, FR_DLR);
        break;
    case FR_5:  //%
        returnValue = override_key(record, FR_5, LSFT(FR_UGRV));
        break;
    case FR_6:  //^
        returnValue = override_key(record, FR_6, FR_HAT);
        break;
    case FR_7:  //&
        returnValue = override_key(record, FR_7, FR_AMP);
        break;
    case FR_8:  //*
        returnValue = override_key(record, FR_8, FR_AST);
        break;
    case FR_9:  //(
        returnValue = override_key(record, FR_9, FR_LPAR);
        break;
    case FR_0:  //(
        returnValue = override_key(record, FR_0, FR_RPAR);
        break;
/*
    case DRZ_CMS:
      if(IS_RELEASED(record->event)) {

        returnValue = false;
      }
    break;
    case DRZ_CME:
      if(IS_RELEASED(record->event)) {
        MACRO(SS_TAP(FR_AST)SS_LSFT(SS_TAP(FR_COLN)));
        returnValue = false;
      }
    break;
*/
  }

  if(IS_PRESSED(record->event)) {
    rgblight_setrgb_white();
  }

  if(IS_RELEASED(record->event)){
    uint16_t h = rgblight_get_hue();
    uint8_t s = rgblight_get_sat();
    uint8_t v = rgblight_get_val();
    rgblight_sethsv(h, s, v);
  }

	return returnValue;
}

void led_set_user(uint8_t usb_led) {

}

#endif

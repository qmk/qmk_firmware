#ifndef XD75_DRZ_LAYOUT_MIRRORED

/*
Drzoid's mirrored 5x15 ortho layout
This layout:
  -> http://www.keyboard-layout-editor.com/#/gists/a59dd1a00a45c5dcd38d9e765675dd41
*/

#include QMK_KEYBOARD_H
#include "config.h"
#include "keymap.h"

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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  //DEFAULT LAYER
  //KLE url: http://www.keyboard-layout-editor.com/#/gists/3aede80592346f947cbc1eb91574d1c7
  /*
    [LOCK+] [ESC  ] [1!   ] [2@   ] [3#   ] [4$   ] [5%   ] [Macro] [6^   ] [7&   ] [8*   ] [9(   ] [0)   ] [ESC  ] [LOCK+]
    [FN   ] [OS   ] [Q    ] [W    ] [E    ] [R    ] [T    ] [M1   ] [Y    ] [U    ] [I    ] [O    ] [P    ] [OS   ] [FN   ]
    [L3   ] [LALT ] [A    ] [S    ] [D    ] [F    ] [G    ] [M2   ] [H    ] [J    ] [K    ] [L    ] [:;   ] [RALT ] [L3   ]
    [L2   ] [/CAPS] [Z    ] [X    ] [C    ] [V    ] [B/<i ] [M3   ] [N    ] [M    ] [\ | /] [↑    ] [.,   ] [/CAPS] [L2   ]
    [SWAP ] [CTRL ] [/Acce] [/Smil] [MENU ] [SPACE] [SPACE] [ENTER] [SPACE] [SPACE] [←    ] [↓    ] [→    ] [RCTRL] [SWAP ]
  */
  [_QWERTY_ON_FR_AZERTY] =
    KEYMAP(
      DRZ_LCK,  KC_ESC,   DRZ___1,  DRZ___2,  DRZ___3,  DRZ___4,  DRZ___5,  _______,  DRZ___6,  DRZ___7,  DRZ___8,  DRZ___9,  DRZ___0,  KC_ESC,   DRZ_LCK,
      MO(_FN),  KC_LGUI,  DRZ___Q,  DRZ___W,  DRZ___E,  DRZ___R,  DRZ___T,  _______,  DRZ___Y,  DRZ___U,  DRZ___I,  DRZ___O,  DRZ___P,  KC_RGUI,  MO(_FN),
      MO(_L3),  KC_LALT,  DRZ___A,  DRZ___S,  DRZ___D,  DRZ___F,  DRZ___G,  _______,  DRZ___H,  DRZ___J,  DRZ___K,  DRZ___L,  DRZ_SCL,  KC_RALT,  MO(_L3),
      MO(_L2),  DRZ__LS,  DRZ___Z,  DRZ___X,  DRZ___C,  DRZ___V,  DRZ___B,  _______,  DRZ___N,  DRZ___M,  _______,  KC_UP,    DRZ_CLN,  DRZ__RS,  MO(_L2),
      DRZ__SH,  KC_LCTL,  DRZ__AC,  DRZ__EM,  KC_MENU,  DRZ_SPA,  DRZ_SPA,  DRZ_ENT,  DRZ_SPA,  DRZ_SPA,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_RCTL,  DRZ__SH
    ),

  //FN LAYER
  //KLE url: http://www.keyboard-layout-editor.com/#/gists/ea5fd62e5090bfd1ace06bb00ebc35b5
  /*
    [LOCK+] [ESC  ] [F1   ] [F2   ] [F3   ] [F4   ] [F5   ] [Macro] [F6   ] [F7   ] [F8   ] [F9   ] [F10  ] [ESC  ] [LOCK+]
    [     ] [OS   ] [F11  ] [F12  ] [F13  ] [F14  ] [F15  ] [M1   ] [F16  ] [F17  ] [F18  ] [F19  ] [F20  ] [OS   ] [     ]
    [L3   ] [LALT ] [     ] [     ] [     ] [     ] [     ] [M2   ] [     ] [     ] [     ] [     ] [     ] [RALT ] [L3   ]
    [L2   ] [/CAPS] [/scre] [calc ] [pause] [     ] [     ] [M3   ] [     ] [     ] [     ] [↑    ] [     ] [/CAPS] [L2   ]
    [SWAP ] [CTRL ] [/Acce] [/Smil] [MENU ] [SPACE] [SPACE] [ENTER] [SPACE] [SPACE] [←    ] [↓    ] [→    ] [RCTRL] [SWAP ]
  */
  [_FN] =
    KEYMAP(
      _______,  _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    _______,  KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   _______,  _______,
      _______,  _______,  KC_F11,   KC_F12,   KC_F13,   KC_F14,   KC_F15,   _______,  KC_F16,   KC_F17,   KC_F18,   KC_F19,   KC_F20,   _______,  _______,
      _______,  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  _______,  _______,
      _______,  _______,  KC_PSCR,  KC_PAUS,  KC_CALC,  XXXXXXX,  XXXXXXX,  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  _______,  _______,
      _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______
    ),

  //LAYER 2
  //KLE url: http://www.keyboard-layout-editor.com/#/gists/873f4eb3c290906364daf000cb132b69
  /*
    [LOCK+] [ESC  ] [     ] [     ] [     ] ['    ] ["    ] [Macro] [     ] [     ] [     ] [_    ] [=    ] [ESC  ] [LOCK+]
    [FN   ] [OS   ] [     ] [     ] [     ] [     ] [[    ] [M1   ] []    ] [     ] [     ] [     ] [     ] [OS   ] [FN   ]
    [L3   ] [LALT ] [/:ah:] [     ] [     ] [     ] [(    ] [M2   ] [)    ] [     ] [     ] [     ] [!    ] [RALT ] [L3   ]
    [     ] [/CAPS] [     ] [     ] [     ] [     ] [{    ] [M3   ] [}    ] [     ] [|    ] [PgUp/] [?    ] [/CAPS] [     ]
    [SWAP ] [ctrl/] [/Acce] [/Smil] [MENU ] [shift] [tab  ] [ENTER] [back/] [del  ] [Home ] [PgDn ] [End  ] [ctrl/] [SWAP ]
  */
  [_L2] =
    KEYMAP(
      _______,  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  DRZ_APS,  DRZ_QOT,  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  DRZ_UDS,  DRZ_EQU,  _______,  _______,
      _______,  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  DRZ_SBL,  _______,  DRZ_SBL,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  _______,  _______,
      _______,  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  DRZ_LPR,  _______,  DRZ_RPR,  XXXXXXX,  XXXXXXX,  XXXXXXX,  DRZ_EXC,  _______,  _______,
      _______,  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  DRZ_CBL,  _______,  DRZ_CBR,  XXXXXXX,  DRZ_PIP,  KC_PGUP,  DRZ_INT,  _______,  _______,
      _______,  DRZ__CA,  _______,  _______,  _______,  DRZ__ST,  KC_TAB ,  _______,  DRZ_BSP,  KC_DELT,  KC_HOME,  KC_PGDN,  KC_END,   DRZ__CA,  _______
    ),

  //LAYER 3
  //KLE url: http://www.keyboard-layout-editor.com/#/gists/6ee8724672840abd6863985fa9fe7014
  /*
    [LOCK+] [ESC  ] [~    ] [²    ] [     ] [     ] [`    ] [Macro] [*    ] [     ] [     ] [-    ] [+    ] [ESC  ] [LOCK+]
    [FN   ] [OS   ] [     ] [     ] [€    ] [     ] [\    ] [M1   ] [/    ] [     ] [     ] [     ] [     ] [OS   ] [FN   ]
    [     ] [LALT ] [     ] [$    ] [     ] [     ] [<    ] [M2   ] [>    ] [     ] [     ] [     ] [£    ] [RALT ] [     ]
    [L2   ] [/CAPS] [     ] [     ] [     ] [     ] [/ *   ] [M3   ] [* /  ] [     ] [     ] [↑    ] [     ] [/CAPS] [L2   ]
    [SWAP ] [ctrl/] [/Acce] [/Unic] [MENU ] [SPACE] [alt/t] [ENTER] [SPACE] [SPACE] [←    ] [↓    ] [→    ] [ctrl/] [SWAP ]
  */
  [_L3] =
    KEYMAP(
      _______,  _______,  DRZ_TIL,  DRZ_USQ,  DRZ_UST,  XXXXXXX, DRZ_SQT,   _______,  DRZ_AST,  XXXXXXX,  XXXXXXX,  DRZ_MNS,  DRZ_PLS,  _______,  _______,
      _______,  _______,  XXXXXXX,  XXXXXXX,  DRZ__EU,  XXXXXXX, DRZ_ASL,   _______,  DRZ_SLA,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  _______,  _______,
      _______,  _______,  XXXXXXX,  DRZ_DLR,  XXXXXXX,  XXXXXXX, DRZ_LES,   _______,  DRZ_SUP,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  _______,  _______,
      _______,  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, DRZ_MCS,   _______,  DRZ_MCE,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  _______,  _______,
      _______,  DRZ__CS,  _______,  _______,  _______,  _______, _______,   _______,  _______,  _______,  _______,  _______,  _______,  DRZ__CS,  _______
    )

};


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

#ifdef DRZ_AZERTY_FR_OS
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
#endif
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

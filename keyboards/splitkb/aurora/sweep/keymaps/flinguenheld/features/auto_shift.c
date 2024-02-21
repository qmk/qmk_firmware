// Copyright 2023 Florent Linguenheld (@FLinguenheld)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "keycodes.h"

/* Only for basis letters
   Exceptions like Tab or Enter */
bool get_auto_shifted_key(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case KC_TAB:
    // case KC_ENT:

  case US_EACU:
  case US_CCED:
  case US_AE:
  case US_OE:

  // --
  case KC_A:
  case KC_B:
  case KC_C:
  case KC_D:
  case KC_E:
  case KC_F:
  case KC_G:
  case KC_H:
  case KC_I:
  case KC_J:
  case KC_K:
  case KC_L:
  case KC_M:
  case KC_N:
  case KC_O:
  case KC_P:
  case KC_Q:
  case KC_R:
  case KC_S:
  case KC_T:
  case KC_U:
  case KC_V:
  case KC_W:
  case KC_X:
  case KC_Y:
  case KC_Z:

    return true;
  }

  return get_custom_auto_shifted_key(keycode, record);
}

/* Custom auto shift
   I use this instead of tap dance because double tap is horrible
   Add here the letter or the custom enum, then add in press_user and press_release the actions */
bool get_custom_auto_shifted_key(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case KC_BSPC:

  // Double them !!!
  case KC_AMPERSAND:
  case KC_AT:
  case KC_BACKSLASH:
  case KC_CIRCUMFLEX:
  case KC_COLON:
  case KC_DOLLAR:
  case KC_EQUAL:
  case KC_EXCLAIM:
  case KC_GRAVE:
  case KC_HASH:
  case KC_MINUS:
  case KC_PERC:
  case KC_PIPE:
  case KC_PLUS:
  case KC_QUESTION:
  case KC_QUOTE:
  case KC_DOUBLE_QUOTE:
  case KC_SEMICOLON:
  case KC_SLASH:
  case KC_ASTERISK:
  case KC_TILDE:
  case KC_UNDERSCORE:

  case KC_LEFT_ANGLE_BRACKET: // Easy indent with vim
  case KC_RIGHT_ANGLE_BRACKET:

  case KC_LEFT_BRACKET:
  case KC_RIGHT_BRACKET:
  case KC_LEFT_CURLY_BRACE:
  case KC_RIGHT_CURLY_BRACE:
  case KC_LEFT_PAREN:
  case KC_RIGHT_PAREN:

  /* French */
  case CS_A_GRAVE:
  case CS_E_GRAVE:
  case CS_U_GRAVE:

  case CS_A_CIRCUMFLEX:
  case CS_E_CIRCUMFLEX:
  case CS_I_CIRCUMFLEX:
  case CS_O_CIRCUMFLEX:
  case CS_U_CIRCUMFLEX:

  case CS_E_DIAERESIS:
  case CS_I_DIAERESIS:
  case CS_U_DIAERESIS:
  case CS_Y_DIAERESIS:
    return true;

  default:
    return false;
  }
}

void autoshift_press_user(uint16_t keycode, bool shifted, keyrecord_t *record) {
  switch (keycode) {
  case KC_BSPC:
    if (shifted) {
      tap_code16(KC_DEL);
    } else {
      tap_code16(KC_BSPC);
    }
    break;
    break;

  case KC_AMPERSAND:
    if (shifted) {
      tap_code16(KC_AMPERSAND);
      tap_code16(KC_AMPERSAND);
    } else {
      tap_code16(KC_AMPERSAND);
    }
    break;
  case KC_AT:
    if (shifted) {
      tap_code16(KC_AT);
      tap_code16(KC_AT);
    } else {
      tap_code16(KC_AT);
    }
    break;
  case KC_BACKSLASH:
    if (shifted) {
      tap_code16(KC_BACKSLASH);
      tap_code16(KC_BACKSLASH);
    } else {
      tap_code16(KC_BACKSLASH);
    }
    break;
  case KC_CIRCUMFLEX:
    if (shifted) {
      tap_code16(KC_CIRCUMFLEX);
      tap_code16(KC_CIRCUMFLEX);
    } else {
      tap_code16(KC_CIRCUMFLEX);
    }
    break;
  case KC_COLON:
    if (shifted) {
      tap_code16(KC_COLON);
      tap_code16(KC_COLON);
    } else {
      tap_code16(KC_COLON);
    }
    break;
  case KC_DOLLAR:
    if (shifted) {
      tap_code16(KC_DOLLAR);
      tap_code16(KC_DOLLAR);
    } else {
      tap_code16(KC_DOLLAR);
    }
    break;
  case KC_EQUAL:
    if (shifted) {
      tap_code16(KC_EQUAL);
      tap_code16(KC_EQUAL);
    } else {
      tap_code16(KC_EQUAL);
    }
    break;
  case KC_EXCLAIM:
    if (shifted) {
      tap_code16(KC_EXCLAIM);
      tap_code16(KC_EXCLAIM);
    } else {
      tap_code16(KC_EXCLAIM);
    }
    break;
  case KC_GRAVE:
    if (shifted) {
      tap_code16(KC_GRAVE);
      tap_code16(KC_GRAVE);
    } else {
      tap_code16(KC_GRAVE);
    }
    break;
  case KC_HASH:
    if (shifted) {
      tap_code16(KC_HASH);
      tap_code16(KC_HASH);
    } else {
      tap_code16(KC_HASH);
    }
    break;
  case KC_MINUS:
    if (shifted) {
      tap_code16(KC_MINUS);
      tap_code16(KC_MINUS);
    } else {
      tap_code16(KC_MINUS);
    }
    break;
  case KC_PERCENT:
    if (shifted) {
      tap_code16(KC_PERCENT);
      tap_code16(KC_PERCENT);
    } else {
      tap_code16(KC_PERCENT);
    }
    break;
  case KC_PIPE:
    if (shifted) {
      tap_code16(KC_PIPE);
      tap_code16(KC_PIPE);
    } else {
      tap_code16(KC_PIPE);
    }
    break;
  case KC_PLUS:
    if (shifted) {
      tap_code16(KC_PLUS);
      tap_code16(KC_PLUS);
    } else {
      tap_code16(KC_PLUS);
    }
    break;
  case KC_QUESTION:
    if (shifted) {
      tap_code16(KC_QUESTION);
      tap_code16(KC_QUESTION);
    } else {
      tap_code16(KC_QUESTION);
    }
    break;
  case KC_QUOTE:
    if (shifted) {
      tap_code16(KC_QUOTE);
      tap_code16(KC_QUOTE);
    } else {
      tap_code16(KC_QUOTE);
    }
    break;
  case KC_DOUBLE_QUOTE:
    if (shifted) {
      tap_code16(KC_DOUBLE_QUOTE);
      tap_code16(KC_DOUBLE_QUOTE);
    } else {
      tap_code16(KC_DOUBLE_QUOTE);
    }
    break;
  case KC_SEMICOLON:
    if (shifted) {
      tap_code16(KC_SEMICOLON);
      tap_code16(KC_SEMICOLON);
    } else {
      tap_code16(KC_SEMICOLON);
    }
    break;
  case KC_SLASH:
    if (shifted) {
      tap_code16(KC_SLASH);
      tap_code16(KC_SLASH);
    } else {
      tap_code16(KC_SLASH);
    }
    break;
  case KC_ASTERISK:
    if (shifted) {
      tap_code16(KC_ASTERISK);
      tap_code16(KC_ASTERISK);
    } else {
      tap_code16(KC_ASTERISK);
    }
    break;
  case KC_TILDE:
    if (shifted) {
      tap_code16(KC_TILDE);
      tap_code16(KC_TILDE);
    } else {
      tap_code16(KC_TILDE);
    }
    break;
  case KC_UNDERSCORE:
    if (shifted) {
      tap_code16(KC_UNDERSCORE);
      tap_code16(KC_UNDERSCORE);
    } else {
      tap_code16(KC_UNDERSCORE);
    }
    break;

  case KC_LEFT_ANGLE_BRACKET:
    if (shifted) {
      tap_code16(KC_LEFT_ANGLE_BRACKET);
      tap_code16(KC_LEFT_ANGLE_BRACKET);
    } else {
      tap_code16(KC_LEFT_ANGLE_BRACKET);
    }
    break;
  case KC_RIGHT_ANGLE_BRACKET:
    if (shifted) {
      tap_code16(KC_RIGHT_ANGLE_BRACKET);
      tap_code16(KC_RIGHT_ANGLE_BRACKET);
    } else {
      tap_code16(KC_RIGHT_ANGLE_BRACKET);
    }
    break;

  case KC_LEFT_BRACKET:
    if (shifted) {
      tap_code16(KC_LEFT_BRACKET);
      tap_code16(KC_LEFT_BRACKET);
    } else {
      tap_code16(KC_LEFT_BRACKET);
    }
    break;
  case KC_RIGHT_BRACKET:
    if (shifted) {
      tap_code16(KC_RIGHT_BRACKET);
      tap_code16(KC_RIGHT_BRACKET);
    } else {
      tap_code16(KC_RIGHT_BRACKET);
    }
    break;
  case KC_LEFT_CURLY_BRACE:
    if (shifted) {
      tap_code16(KC_LEFT_CURLY_BRACE);
      tap_code16(KC_LEFT_CURLY_BRACE);
    } else {
      tap_code16(KC_LEFT_CURLY_BRACE);
    }
    break;
  case KC_RIGHT_CURLY_BRACE:
    if (shifted) {
      tap_code16(KC_RIGHT_CURLY_BRACE);
      tap_code16(KC_RIGHT_CURLY_BRACE);
    } else {
      tap_code16(KC_RIGHT_CURLY_BRACE);
    }
    break;
  case KC_LEFT_PAREN:
    if (shifted) {
      tap_code16(KC_LEFT_PAREN);
      tap_code16(KC_LEFT_PAREN);
    } else {
      tap_code16(KC_LEFT_PAREN);
    }
    break;
  case KC_RIGHT_PAREN:
    if (shifted) {
      tap_code16(KC_RIGHT_PAREN);
      tap_code16(KC_RIGHT_PAREN);
    } else {
      tap_code16(KC_RIGHT_PAREN);
    }
    break;

  /* French
     Release is not necessary with 'send_unicode_string()' */
  case CS_A_GRAVE:
    if (shifted) {
      tap_code16(US_DGRV);
      tap_code16(S(KC_A));
    } else {
      tap_code16(US_DGRV);
      tap_code16(KC_A);
    }
    break;
  case CS_E_GRAVE:
    if (shifted) {
      tap_code16(US_DGRV);
      tap_code16(S(KC_E));
    } else {
      tap_code16(US_DGRV);
      tap_code16(KC_E);
    }
    break;
  case CS_U_GRAVE:
    if (shifted) {
      tap_code16(US_DGRV);
      tap_code16(S(KC_U));
    } else {
      tap_code16(US_DGRV);
      tap_code16(KC_U);
    }
    break;

  case CS_A_CIRCUMFLEX:
    if (shifted) {
      tap_code16(US_DCIR);
      tap_code16(S(KC_A));
    } else {
      tap_code16(US_DCIR);
      tap_code16(KC_A);
    }
    break;
  case CS_E_CIRCUMFLEX:
    if (shifted) {
      tap_code16(US_DCIR);
      tap_code16(S(KC_E));
    } else {
      tap_code16(US_DCIR);
      tap_code16(KC_E);
    }
    break;
  case CS_I_CIRCUMFLEX:
    if (shifted) {
      tap_code16(US_DCIR);
      tap_code16(S(KC_I));
    } else {
      tap_code16(US_DCIR);
      tap_code16(KC_I);
    }
    break;
  case CS_O_CIRCUMFLEX:
    if (shifted) {
      tap_code16(US_DCIR);
      tap_code16(S(KC_O));
    } else {
      tap_code16(US_DCIR);
      tap_code16(KC_O);
    }
    break;
  case CS_U_CIRCUMFLEX:
    if (shifted) {
      tap_code16(US_DCIR);
      tap_code16(S(KC_U));
    } else {
      tap_code16(US_DCIR);
      tap_code16(KC_U);
    }
    break;

  case CS_E_DIAERESIS:
    if (shifted) {
      tap_code16(US_DIAE);
      tap_code16(S(KC_E));
    } else {
      tap_code16(US_DIAE);
      tap_code16(KC_E);
    }
    break;
  case CS_I_DIAERESIS:
    if (shifted) {
      tap_code16(US_DIAE);
      tap_code16(S(KC_I));
    } else {
      tap_code16(US_DIAE);
      tap_code16(KC_I);
    }
    break;
  case CS_U_DIAERESIS:
    if (shifted) {
      tap_code16(US_DIAE);
      tap_code16(S(KC_U));
    } else {
      tap_code16(US_DIAE);
      tap_code16(KC_U);
    }
    break;
  case CS_Y_DIAERESIS:
    if (shifted) {
      tap_code16(US_DIAE);
      tap_code16(S(KC_Y));
    } else {
      tap_code16(US_DIAE);
      tap_code16(KC_Y);
    }
    break;

  default:
    if (shifted) {
      add_weak_mods(MOD_BIT(KC_LSFT));
    }
    /* & 0xFF gets the Tap key for Tap Holds, required when using Retro Shift */
    register_code16((IS_RETRO(keycode)) ? keycode & 0xFF : keycode);
  }
}

void autoshift_release_user(uint16_t keycode, bool shifted, keyrecord_t *record) {
  switch (keycode) {
  case KC_BSPC:
    unregister_code16((!shifted) ? KC_BSPC : KC_DEL);
    break;

  default:
    /* & 0xFF gets the Tap key for Tap Holds, required when using Retro Shift
       The IS_RETRO check isn't really necessary here, always using
       keycode & 0xFF would be fine. */
    unregister_code16((IS_RETRO(keycode)) ? keycode & 0xFF : keycode);
  }
}

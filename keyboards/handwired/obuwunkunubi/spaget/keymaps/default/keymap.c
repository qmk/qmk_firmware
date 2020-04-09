/* Copyright 2020 obuwunkunubi
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

// Defines for shortcut macros
#define KC_CAD LALT(LCTL(KC_DEL)) // CTRL + ALT + DEL
#define KC_CPY LCTL(KC_C) // Copy
#define KC_PST LCTL(KC_V) // Paste
#define KC_AF4 LALT(KC_F4) // ALT + F4

enum custom_keycodes {
  SELWN = SAFE_RANGE,
  SELWP,
  EM1,
  EM2,
  EM3,
  EM4,
  EM5,
  EM6,
  EM7,
  EM8,
  EM9,
  MAKE1,
  MAKE2,
  MAIL1,
  MAIL2,
  OBUWUN,
  DIR
};

enum layer_names {
  BASE,
  ONE,
  TWO
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Keymap BASE: Base Layer
  *
  *      ,---.       ,---.
  *      |NUM|       |PLY|-----
  *      `---'       `---'    |
  *        |                  |
  *        -----------------  |
  *      ,---------------. |  |
  *      |CAL| UP|PRE|NXT| |  |
  *      |---------------| |  |
  *      | = | / | * | - | |  |
  *      |---------------| |  |
  *      | 7 | 8 | 9 |NUM|--  |
  *      |---------------|    |
  *      | 4 | 5 | 6 | + |    |
  *      |---------------|    |
  *      | 1 | 2 | 3 |PLY|-----
  *      |---------------|
  *      | NO| 0 | . |ENT|
  *      `---------------'
  */
  [BASE] = LAYOUT(     \
    KC_CALC, TO(ONE), KC_MPRV, KC_MNXT, \
    KC_EQL,  KC_PSLS, KC_PAST, KC_MINS, \
    KC_P7,   KC_P8,   KC_P9,   KC_NLCK, \
    KC_P4,   KC_P5,   KC_P6,   KC_PPLS, \
    KC_P1,   KC_P2,   KC_P3,   KC_MPLY, \
             KC_P0,   KC_PDOT, KC_PENT  \
  ),

  /* Keymap ONE: Util Layer
  *
  *      ,---.       ,---.
  *      |RST|       |CAD|-----
  *      `---'       `---'    |
  *        |                  |
  *        -----------------  |
  *      ,---------------. |  |
  *      |BAS|TWO|MK1|MK2| |  |
  *      |---------------| |  |
  *      |DIR|@1 |@2 |OBU| |  |
  *      |---------------| |  |
  *      |SWP|AF4|SWN|RST|--  |
  *      |---------------|    |
  *      |CPY| U |PST|PSC|    |
  *      |---------------|    |
  *      | L | D | R |CAD|-----
  *      |---------------|
  *      | NO| NO| NO| NO|
  *      `---------------'
  */
  [ONE] = LAYOUT(       \
    TO(BASE), TO(TWO), MAKE1,   MAKE2,   \
    DIR,      MAIL1,   MAIL2,   OBUWUN,  \
    SELWP,    KC_AF4,  SELWN,   RESET,   \
    KC_CPY,   KC_UP,   KC_PST,  KC_PSCR, \
    KC_LEFT,  KC_DOWN, KC_RGHT, KC_CAD,  \
             KC_P0,   KC_PDOT, KC_PENT  \
  ),


  /* Keymap TWO: Emoji Layer
  *
  *      ,---.       ,---.
  *      | NO|       | NO|-----
  *      `---'       `---'    |
  *        |                  |
  *        -----------------  |
  *      ,---------------. |  |
  *      |ONE|BAS| [ | ] | |  |
  *      |---------------| |  |
  *      |F13|F14|F15|F16| |  |
  *      |---------------| |  |
  *      |EM7|EM8|EM9| NO|--  |
  *      |---------------|    |
  *      |EM4|EM5|EM6| NO|    |
  *      |---------------|    |
  *      |EM1|EM2|EM3| NO|-----
  *      |---------------|
  *      | NO| NO| NO| NO|
  *      `---------------'
  */
  [TWO] = LAYOUT(       \
    TO(ONE), TO(BASE), KC_LBRC, KC_RBRC, \
    KC_F13,  KC_F14,   KC_F15,  KC_F16,  \
    EM7,     EM8,      EM9,     KC_NO,   \
    EM4,     EM5,      EM6,     KC_NO,   \
    EM1,     EM2,      EM3,     KC_NO,   \
             KC_NO,    KC_NO,   KC_NO    \
  ),

};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {

    case SELWN:
    if (record->event.pressed) {
      // when keycode SELWN is pressed

      send_string(SS_DOWN(X_LCTRL)SS_DOWN(X_LSHIFT)SS_TAP(X_RIGHT)SS_UP(X_LSHIFT)"c"SS_UP(X_LCTRL)); // select and copy next word
      return false; break;

    } else {
      // when keycode SELWN is released
    }
    break;

    case SELWP:
    if (record->event.pressed) {
      // when keycode SELWP is pressed

      send_string(SS_DOWN(X_LCTRL)SS_DOWN(X_LSHIFT)SS_TAP(X_LEFT)SS_UP(X_LSHIFT)"c"SS_UP(X_LCTRL)); // select and copy previous word
      return false; break;

    } else {
      // when keycode SELWP is released
    }
    break;

    case MAKE1:
    if (record->event.pressed) {
      // when keycode MAKE1 is pressed

      send_string("make handwired/obuwunkunubi/spaget:default:avrdude");

    } else {
      // when keycode MAKE1 is released
    }
    break;

    case MAKE2:
    if (record->event.pressed) {
      // when keycode MAKE2 is pressed

      send_string("make preonic/rev3:obuwunkunubi:dfu-util");

    } else {
      // when keycode MAKE2 is released
    }
    break;

    case DIR:
    if (record->event.pressed) {
      // when keycode DIR is pressed

      send_string("cd /d/Keyboards/qmk/qmk_firmware/");

    } else {
      // when keycode DIR is released
    }
    break;

    case OBUWUN:
    if (record->event.pressed) {
      // when keycode OBUWUN is pressed

      send_string("obuwunkunubi");

    } else {
      // when keycode OBUWUN is released
    }
    break;

    case MAIL1:
    if (record->event.pressed) {
      // when keycode MAIL1 is pressed

      send_string("marko.bakan7");

    } else {
      // when keycode MAIL1 is released
    }
    break;

    case MAIL2:
    if (record->event.pressed) {
      // when keycode MAIL2 is pressed

      send_string("bakan.marko7");

    } else {
      // when keycode MAIL2 is released
    }
    break;

    case EM1:
    if (record->event.pressed) {
      // when keycode EM1 is pressed

      send_unicode_string("ʕ•ᴥ•ʔ");

    } else {
      // when keycode EM1 is released
    }
    break;

    case EM2:
    if (record->event.pressed) {
      // when keycode EM2 is pressed

      send_unicode_string("༼ つ ◕_◕ ༽つ");

    } else {
      // when keycode EM2 is released
    }
    break;

    case EM3:
    if (record->event.pressed) {
      // when keycode EM3 is pressed

      send_unicode_string("( ⌐■_■)");

    } else {
      // when keycode EM3 is released
    }
    break;

    case EM4:
    if (record->event.pressed) {
      // when keycode EM4 is pressed

      send_unicode_string("(╯°□°）╯彡 ┻━┻");

    } else {
      // when keycode EM4 is released
    }
    break;

    case EM5:
    if (record->event.pressed) {
      // when keycode EM5 is pressed

      send_unicode_string("ಠ_ಠ");

    } else {
      // when keycode EM5 is released
    }
    break;

    case EM6:
    if (record->event.pressed) {
      // when keycode EM6 is pressed

      send_unicode_string("( ͡° ͜ʖ ͡°)");

    } else {
      // when keycode EM6 is released
    }
    break;

    case EM7:
    if (record->event.pressed) {
      // when keycode EM7 is pressed

      send_unicode_string("(☞ﾟヮﾟ)☞");

    } else {
      // when keycode EM7 is released
    }
    break;

    case EM8:
    if (record->event.pressed) {
      // when keycode EM8 is pressed

      send_unicode_string("(^‿^)");

    } else {
      // when keycode EM8 is released
    }
    break;

    case EM9:
    if (record->event.pressed) {
      // when keycode EM9 is pressed

      send_unicode_string("¯\\_(ツ)_/¯");

    } else {
      // when keycode EM9 is released
    }
    break;

  }
  return true;
};

// Unicode input mode set to Windows using WinCompose
void matrix_init_user(void) {
    set_unicode_input_mode(UC_WINC);
};

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}

#ifdef OLED_DRIVER_ENABLE
void oled_task_user(void) {
  oled_write_P(PSTR("       spaget v1\n\n"), false);

  // Host Keyboard Layer Status
  oled_write_P(PSTR("Layer: "), false);

  switch (get_highest_layer(layer_state)) {
    case BASE:
    oled_write_P(PSTR("Base\n"), false);
    break;
    case ONE:
    oled_write_P(PSTR("Util\n"), false);
    break;
    case TWO:
    oled_write_P(PSTR("Emoji\n"), false);
    break;
    default:
    oled_write_ln_P(PSTR("Undefined"), false);
  }

  // Host Keyboard LED Status
  led_t led_state = host_keyboard_led_state();
  oled_write_P(PSTR("Lock: "), false);
  oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
  oled_write_P(led_state.caps_lock ? PSTR("CAPS ") : PSTR("     "), false);
  oled_write_P(led_state.scroll_lock ? PSTR("SCROLL ") : PSTR("       "), false);
}
#endif

void encoder_update_user(uint8_t index, bool clockwise) {
  if(IS_LAYER_ON(BASE)) {
    if (index == 0) { /* First encoder */
      if (clockwise) {
        tap_code(KC_PGDN);
      } else {
        tap_code(KC_PGUP);
      }
    } else if (index == 1) { /* Second encoder */
      if (clockwise) {
        tap_code(KC_VOLU);
      } else {
        tap_code(KC_VOLD);
      }
    }
  }
  else if(IS_LAYER_ON(ONE)) {
    if (index == 0) { /* First encoder */
      if (clockwise) {
        tap_code(KC_WH_R);
      } else {
        tap_code(KC_WH_L);
      }
    } else if (index == 1) { /* Second encoder */
      if (clockwise) {
        tap_code(KC_WH_D);
      } else {
        tap_code(KC_WH_U);
      }
    }
  }
  else if(IS_LAYER_ON(TWO)) {
    if (index == 0) { /* First encoder */
      if (clockwise) {
        tap_code(KC_DEL);
      } else {
        tap_code(KC_BSPC);
      }
    } else if (index == 1) { /* Second encoder */
      if (clockwise) {
        tap_code(KC_DOWN);
      } else {
        tap_code(KC_UP);
      }
    }
  }
  else {
    if (index == 0) { /* First encoder */
      if (clockwise) {
        tap_code(KC_PGDN);
      } else {
        tap_code(KC_PGUP);
      }
    } else if (index == 1) { /* Second encoder */
      if (clockwise) {
        tap_code(KC_VOLU);
      } else {
        tap_code(KC_VOLD);
      }
    }
  }
}

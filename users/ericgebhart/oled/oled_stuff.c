/*
  Copyright 2018-2022 Eric Gebhart <e.a.gebhart@gmail.com>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "ericgebhart.h"
#include <string.h>
#include <stdio.h>

#ifdef OLED_CUSTOM_ENABLE

extern uint32_t current_locale;

void oled_render_locale(void) {
  // oled_write_P(PSTR("Layout: "), false);
  switch (current_locale) {
    WRITE_STR_CASE(LOCALE_DEFAULT, DEFAULT_LANG_NAME)
#ifdef SECOND_LOCALE
      WRITE_STR_CASE(LOCALE_TWO, SECOND_LOCALE_NAME)
#endif
    }
}

void oled_render_keylock_status(uint8_t led_usb_state) {
  oled_write_P(PSTR(" Lock:"), false);
  oled_write_P(PSTR("N"), led_usb_state & (1 << USB_LED_NUM_LOCK));
  oled_write_P(PSTR("C"), led_usb_state & (1 << USB_LED_CAPS_LOCK));
  oled_write_P(PSTR("S"), led_usb_state & (1 << USB_LED_SCROLL_LOCK));
}

void oled_render_mod_status(uint8_t modifiers) {
  oled_write_P(PSTR("Mods:"), false);
  oled_write_P(PSTR("S"), (modifiers & MOD_MASK_SHIFT));
  oled_write_P(PSTR("C"), (modifiers & MOD_MASK_CTRL));
  oled_write_P(PSTR("A"), (modifiers & MOD_MASK_ALT));
  oled_write_P(PSTR("G"), (modifiers & MOD_MASK_GUI));
}

void oled_render_mod_lock_status(void){
  oled_render_mod_status(get_mods() | get_oneshot_mods());
  oled_render_keylock_status(host_keyboard_leds());
}


#ifdef KEYLOGGER_ENABLE
char mkeylog_str[22] = {};

const char mcode_to_name[60] = {
  ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
  'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
  'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
  '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
  'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
  '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};


void oled_render_keylog(void) {
  oled_write_ln(mkeylog_str, false);
}


void add_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
  if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
      (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) {
    keycode = keycode & 0xFF;
  }
  if (keycode < 60) {
    name = mcode_to_name[keycode];
  }

  // update keylog
  memset(mkeylog_str, ' ', sizeof(mkeylog_str) - 1);
  snprintf(mkeylog_str, sizeof(mkeylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);
}
#endif

__attribute__((weak)) oled_rotation_t oled_init_keymap(oled_rotation_t rotation) { return rotation; }

oled_rotation_t oled_init_user(oled_rotation_t rotation) {

  // for the big screen.
#ifdef OLED_DISPLAY_128X64
  return OLED_ROTATION_180;
#endif
  // rotate the slave side of the corne to be bottom side in.
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;
  }

  return oled_init_keymap(rotation);
}

/* oled_rotation_t oled_init_user(oled_rotation_t rotation) { */
/* memset(mkeylog_str, ' ', sizeof(mkeylog_str) - 1); */
/*   if (is_keyboard_master()) { */
/*     return OLED_ROTATION_270; */
/*   } else { */
/*     return OLED_ROTATION_180; */
/*   } */
/* } */


void render_bootmagic_status(bool status) {
  /* Show Ctrl-Gui Swap options */
  static const char PROGMEM logo[][2][3] = {
    {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
    {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
  };
  if (status) {
    oled_write_ln_P(logo[0][0], false);
    oled_write_ln_P(logo[0][1], false);
  } else {
    oled_write_ln_P(logo[1][0], false);
    oled_write_ln_P(logo[1][1], false);
  }
}


__attribute__((weak)) void oled_render_logo(void) {
  // clang-format off
  static const char PROGMEM qmk_logo[] = {
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};
  // clang-format on
  oled_write_P(qmk_logo, false);
}


bool process_record_user_oled(uint16_t keycode, keyrecord_t *record) {
#ifdef KEYLOGGER_ENABLE
  if (record->event.pressed) {
    //oled_timer = timer_read32();
    add_keylog(keycode, record);
    //add_keylog(keycode);
  }
#endif
  return true;
}

bool oled_task_user(void) {
  //oled_clear();
  if (is_keyboard_master()) {
    oled_render_mod_lock_status();
    oled_advance_page(false);
    oled_render_default_layer_state();
    oled_render_locale();
    oled_write_ln_P(PSTR(" "), false);
    oled_render_layer_state();
    oled_write_ln_P(PSTR(" "), false);
#ifdef OLED_DISPLAY_128X64
    oled_render_layer_map();
#endif
#ifdef KEYLOGGER_ENABLE
    oled_render_keylog();
#endif

  // slave side display.
  } else {
    oled_clear();
#ifdef OLED_LOGO_ENABLE
    oled_render_logo();
#endif
    oled_render_default_layer_state();
    oled_render_locale();
    oled_write_ln_P(PSTR(" "), false);
#ifdef SPLIT_LAYER_STATE_ENABLE
    oled_render_layer_state();
    oled_render_layer_map();
#endif
  }
  return(false);

}
#endif

/* oled_render_keylock_status(host_keyboard_leds()); */
/* oled_render_mod_status(get_mods() | get_oneshot_mods()); */

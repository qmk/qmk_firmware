/*
  Copyright 2018 Eric Gebhart <e.a.gebhart@gmail.com>

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

void oled_render_default_layer_state(void) {
  oled_write_P(PSTR("Layout: "), false);
  switch (get_highest_layer(default_layer_state)) {
    case _QWERTY:
      oled_write_ln_P(PSTR("Qwerty"), false);
      break;
    case _COLEMAK:
      oled_write_ln_P(PSTR("Colemak"), false);
      break;
    case _DVORAK_BP:
    case _DVORAK:
      oled_write_ln_P(PSTR("Dvorak"), false);
      break;


      /* case _WORKMAN: */
      // oled_write_ln_P(PSTR("Workman\n"), false);
      /*         break; */
      /*     case _NORMAN: */
      // oled_write_ln_P(PSTR("Norman\n"), false);
      /*         break; */
      /*     case _MALTRON: */
      // oled_write_ln_P(PSTR("Maltron\n"), false);
      /*         break; */

      /* case _EUCALYN: */
      // oled_write_ln_P(PSTR("Eucalyn\n"), false);
      /*   break; */
      /* case _CARPLAX: */
      // oled_write_ln_P(PSTR("Carplax\n"), false);
      /*   break; */

    case _BEAKL:
    case _BEAKL_BP:
      oled_write_ln_P(PSTR("Beakl"), false);
      break;
    case _BEPO:
      oled_write_ln_P(PSTR("Bepo"), false);
      break;
    }
}

void oled_render_layer_state(void) {
  oled_write_P(PSTR("Layer: "), false);
  switch (get_highest_layer(layer_state)) {
    case _NAV:
      oled_write_P(PSTR("Navigation"), false);
      break;
    case _LAYERS:
      oled_write_P(PSTR("Layers"), false);
      break;
    case _RGB:
      oled_write_P(PSTR("RGB"), false);
      break;
    case _TOPROWS:
    case _TOPROWS_BP:
      oled_write_P(PSTR("TopRows"), false);
      break;
    case _SYMB:
    case _SYMB_BP:
      oled_write_P(PSTR("Symbols"), false);
      break;
    case _KEYPAD:
    case _KEYPAD_BP:
      oled_write_P(PSTR("Keypad"), false);
      break;
    case _ADJUST:
      oled_write_P(PSTR("Adjust"), false);
      break;
    }
  oled_write_ln_P(PSTR(" "), false);
}

// this is part of my answer to a challenge.
// My friend Ross thinks that the only use of an oled
// is to say which layer.
// I think there is more. this is just a beginning.
void oled_render_layer_map(void) {
  uint8_t lyr = get_highest_layer(layer_state);
  if (lyr <= _BEPO) {
    switch (get_highest_layer(default_layer_state)) {
    case _QWERTY:
      oled_write_ln_P(PSTR("   qwert  yuiop"), false);
      oled_write_ln_P(PSTR("   asdfg  hjkl;"), false);
      oled_write_ln_P(PSTR("   zxcvb  nm,./"), false);
      break;
    case _COLEMAK:
      oled_write_ln_P(PSTR("   qwfpb  jluy;"), false);
      oled_write_ln_P(PSTR("   arstg  mneio"), false);
      oled_write_ln_P(PSTR("   zxcdv  kh,./"), false);
      break;
    case _DVORAK_BP:
    case _DVORAK:
      oled_write_ln_P(PSTR("   \",.py  fgcrl"), false);
      oled_write_ln_P(PSTR("   aoeui  dhtns"), false);
      oled_write_ln_P(PSTR("   ;qjkx  bmwvz "), false);
      break;

    case _BEAKL:
    case _BEAKL_BP:
      oled_write_ln_P(PSTR("   qhoux  gcrfz"), false);
      oled_write_ln_P(PSTR("   yiea.  dstnb"), false);
      oled_write_ln_P(PSTR("   j/,k'  wmlpv"), false);
      break;

    case _BEPO:
      oled_write_P(PSTR("   cbe'po`e  vdljz %"), false);
      oled_write_P(PSTR("    auie,    tsrnmc"), false);
      oled_write_P(PSTR("   e^a'yx.k  'qghfw"), false);
      break;
    }

  } else {

    switch (lyr) {
    case _TOPROWS:
    case _TOPROWS_BP:
      oled_write_ln_P(PSTR("   !@#$%  ^&*()"), false);
      oled_write_ln_P(PSTR("   40123  76598"), false);
      oled_write_ln_P(PSTR(" F1-    --    -F12"), false);
      break;

    case _SYMB:
    case _SYMB_BP:
      oled_write_ln_P(PSTR("   `<$>'  ?[_]-"), false);
      oled_write_ln_P(PSTR("  -\\(\")#  !{:}/;"), false);
      oled_write_ln_P(PSTR("   @=*+;  %&^~|"), false);
      break;

    case _NAV:
      oled_write_ln_P(PSTR("54321 0  ctn 12345"), false);
      oled_write_ln_P(PSTR(" ldur 1  ccv ldur"), false);
      oled_write_ln_P(PSTR(" ldur 2  cwq hdue"), false);
      break;

    case _KEYPAD:
      oled_write_ln_P(PSTR("     523:   F9-F12"), false);
      oled_write_ln_P(PSTR("   -7.104   F5-F8"), false);
      oled_write_ln_P(PSTR("    /698,   F1-F4"), false);
      break;

    case _LAYERS:
      oled_write_ln_P(PSTR("  Bp Dv Bk|Nv S K TR"), false);
      oled_write_ln_P(PSTR("Q Cl Dv Bk|Nv S K TR"), false);
      oled_write_P(PSTR(" "), false);
      //oled_write_ln_P(PSTR("Ctrls?-> RGB ___ ___ Adjust"), false);
      break;
    }
  }
}

void oled_render_keylock_status(uint8_t led_usb_state) {
  oled_write_P(PSTR("  Lock:"), false);
  oled_write_P(PSTR(" "), false);
  oled_write_P(PSTR("N"), led_usb_state & (1 << USB_LED_NUM_LOCK));
  oled_write_P(PSTR("C"), led_usb_state & (1 << USB_LED_CAPS_LOCK));
  oled_write_ln_P(PSTR("S"), led_usb_state & (1 << USB_LED_SCROLL_LOCK));
}

void oled_render_mod_status(uint8_t modifiers) {
  oled_write_P(PSTR("Mods:"), false);
  oled_write_P(PSTR("S"), (modifiers & MOD_MASK_SHIFT));
  oled_write_P(PSTR("C"), (modifiers & MOD_MASK_CTRL));
  oled_write_P(PSTR("A"), (modifiers & MOD_MASK_ALT));
  oled_write_P(PSTR("G"), (modifiers & MOD_MASK_GUI));
}

void oled_render_mod_lock_status(){
  oled_render_mod_status(get_mods() | get_oneshot_mods());
  oled_render_keylock_status(host_keyboard_leds());
}


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
  // sometimes there's an extra row. this is because sometimes it drops
  // to the last line. and this clears it.
  oled_write_ln_P(PSTR(" "), false);
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

__attribute__((weak)) oled_rotation_t oled_init_keymap(oled_rotation_t rotation) { return rotation; }

oled_rotation_t oled_init_user(oled_rotation_t rotation) {

  // for the big screen.
#ifdef OLED_DISPLAY_128X64
  return OLED_ROTATION_180;
#endif

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

bool process_record_user_oled(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    //oled_timer = timer_read32();
    add_keylog(keycode, record);
    //add_keylog(keycode);
  }
  return true;
}

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

bool oled_task_user(void) {
  if (is_keyboard_master()) {
    oled_render_mod_lock_status();
    oled_render_default_layer_state();
    oled_render_layer_state();
#ifdef OLED_DISPLAY_128X64
    oled_render_layer_map();
#endif
    oled_render_keylog();
  } else {
    oled_render_logo();
    oled_render_default_layer_state();
  }
  return(true);

}
/* oled_render_keylock_status(host_keyboard_leds()); */
/* oled_render_mod_status(get_mods() | get_oneshot_mods()); */

#include "ericgebhart.h"
#include <string.h>
#include <stdio.h>

void oled_render_default_layer_state(void) {
  oled_write_P(PSTR("Layout: "), false);
  switch (get_highest_layer(default_layer_state)) {
    case _QWERTY:
      oled_write_ln_P(PSTR("Qwerty"), false);
      break;
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
  switch (get_highest_layer(layer_state))
    //        (layer_state)

    {
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

void oled_render_keylock_status(uint8_t led_usb_state) {
  oled_write_P(PSTR("Lock:"), false);
  oled_write_P(PSTR(" "), false);
  oled_write_P(PSTR("N"), led_usb_state & (1 << USB_LED_NUM_LOCK));
  oled_write_P(PSTR("C"), led_usb_state & (1 << USB_LED_CAPS_LOCK));
  oled_write_ln_P(PSTR("S"), led_usb_state & (1 << USB_LED_SCROLL_LOCK));
  //  oled_write_ln_P(PSTR(" "), false);
}

void oled_render_mod_status(uint8_t modifiers) {
  oled_write_P(PSTR("Mods:"), false);
  oled_write_P(PSTR("S"), (modifiers & MOD_MASK_SHIFT));
  oled_write_P(PSTR("C"), (modifiers & MOD_MASK_CTRL));
  oled_write_P(PSTR("A"), (modifiers & MOD_MASK_ALT));
  oled_write_P(PSTR("G"), (modifiers & MOD_MASK_GUI));
  oled_write_P(PSTR("  "), false);
  //oled_write_ln_P(PSTR(" "), false);
}


char mkeylog_str[21] = {};

const char mcode_to_name[60] = {
  ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
  'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
  'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
  '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
  'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
  '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};


void oled_render_keylog(void) {
  oled_write(mkeylog_str, false);
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
  snprintf(mkeylog_str, sizeof(mkeylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);
  oled_render_keylog();
}

__attribute__((weak)) oled_rotation_t oled_init_keymap(oled_rotation_t rotation) { return rotation; }

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  memset(mkeylog_str, '!', sizeof(mkeylog_str) - 1);

  // for the small screen.
  return OLED_ROTATION_180;

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
    oled_render_default_layer_state();
    oled_render_layer_state();
    oled_render_mod_status(get_mods() | get_oneshot_mods());
    oled_render_keylock_status(host_keyboard_leds());
    oled_render_keylog();
  } else {
    oled_render_logo();
    oled_render_default_layer_state();
    // oled_driver_render_logo();
    //oled_render_keylog();
  }
  return(true);

}
/* oled_render_keylock_status(host_keyboard_leds()); */
/* oled_render_mod_status(get_mods() | get_oneshot_mods()); */

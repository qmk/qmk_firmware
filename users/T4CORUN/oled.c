#include "oled.h"

#if defined(KEYLOG_ENABLE)
char     keylog_str[KEYLOG_LEN] = {0};
uint8_t  keylogs_str_idx        = 0;
uint16_t log_timer              = 0;

const char code_to_name[60] = {
  ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
  'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
  'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
  '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
  'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
  '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '
}; 

void add_keylog(uint16_t keycode) {
  if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) {
      keycode = keycode & 0xFF;
  }

  for (uint8_t i = KEYLOG_LEN - 1; i > 0; i--) {
    keylog_str[i] = keylog_str[i - 1];
  }
  if (keycode < 60) {
    keylog_str[0] = code_to_name[keycode];
  }
  keylog_str[KEYLOG_LEN - 1] = 0;
  log_timer = timer_read();
}

void update_log(void) {
  if (timer_elapsed(log_timer) > 750) {
    add_keylog(0);
  }
}

void render_keylogger_status(void) {
  oled_write_P(PSTR(OLED_RENDER_KEYLOGGER_NAME), false);
  oled_write(keylog_str, false);
}
#endif //KEYLOG_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (is_keyboard_master()) {
    return OLED_ROTATION_270;
  } else {
    return OLED_ROTATION_180;
  }
}

void render_crkbd_logo(void) {
  static const char PROGMEM crkbd_logo[] = {
    0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
    0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
    0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
    0};
  oled_write_P(crkbd_logo, false);
}

void render_default_layer_state(void) {
  oled_write_P(PSTR(OLED_RENDER_LAYOUT_NAME), false);
  switch (get_highest_layer(default_layer_state)) {
    case _QWERTY:
      oled_write_P(PSTR(OLED_RENDER_LAYOUT_QWERTY), false);
      break;
    case _COLEMAK_DH:
      oled_write_P(PSTR(OLED_RENDER_LAYOUT_COLEMAK_DH), false);
      break;
    case _GAMING:
      oled_write_P(PSTR(OLED_RENDER_LAYOUT_GAMING), false);
      break;
    }
}

void render_layer_state(void) {
  oled_write_P(PSTR(OLED_RENDER_LAYER_NAME), false);
  oled_write_P(PSTR(OLED_RENDER_LAYER_BASE), layer_state_is(FIRST_DEFAULT_LAYER));
  oled_write_P(PSTR(OLED_RENDER_LAYER_NUMBER), layer_state_is(_GAMENUMBER) || layer_state_is(_NUMBER));
  oled_write_P(PSTR(OLED_RENDER_LAYER_NAVIGATION), layer_state_is(_NAVIGATION));
  oled_write_P(PSTR(OLED_RENDER_LAYER_FUNCTION), layer_state_is(_FUNCTION));
  oled_write_P(PSTR(OLED_RENDER_LAYER_MOUSE), layer_state_is(_MOUSE));
  oled_write_P(PSTR(OLED_RENDER_LAYER_ADJUST), layer_state_is(_ADJUST));


}

void render_keylock_status(uint8_t led_usb_state) {
  oled_write_P(PSTR(OLED_RENDER_KEYLOCK_NAME), false);
  oled_write_P(PSTR(" "), false);
  oled_write_P(PSTR("N"), led_usb_state & (1 << USB_LED_NUM_LOCK));
  oled_write_P(PSTR("C"), led_usb_state & (1 << USB_LED_CAPS_LOCK));
  oled_write_ln_P(PSTR("S"), led_usb_state & (1 << USB_LED_SCROLL_LOCK));
}

void render_mod_status(uint8_t modifiers) {
  oled_write_P(PSTR(OLED_RENDER_MODS_NAME), false);
  oled_write_P(PSTR(" "), false);
  oled_write_P(PSTR("G"), (modifiers & MOD_MASK_GUI));
  oled_write_P(PSTR("A"), (modifiers & MOD_MASK_ALT));
  oled_write_P(PSTR("C"), (modifiers & MOD_MASK_CTRL));
  oled_write_P(PSTR("S"), (modifiers & MOD_MASK_SHIFT));
}

/*
void render_bootmagic_status(void) {
  // Show Ctrl-Gui Swap options 
  static const char PROGMEM logo[][2][3] = {
    {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
    {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
  };
  oled_write_P(PSTR("BTMGK"), false);
  oled_write_P(PSTR(" "), false);
  oled_write_P(logo[0][0], !keymap_config.swap_lctl_lgui);
  oled_write_P(logo[1][0], keymap_config.swap_lctl_lgui);
  oled_write_P(PSTR(" "), false);
  oled_write_P(logo[0][1], !keymap_config.swap_lctl_lgui);
  oled_write_P(logo[1][1], keymap_config.swap_lctl_lgui);
  oled_write_P(PSTR(" NKRO"), keymap_config.nkro);
}
*/

void render_oled_main(void) {
  render_default_layer_state();
  render_keylock_status(host_keyboard_leds());
  render_mod_status(get_mods());
  render_layer_state();
  //render_bootmagic_status();

#if defined(KEYLOG_ENABLE)
  render_keylogger_status();
#endif // KEYLOG_ENABLE
}

void render_oled_secondary(void) {
  render_default_layer_state();
  render_layer_state();
}

bool oled_task_user(void) {
  
#if defined(KEYLOG_ENABLE)
  update_log();
#endif //KEYLOG ENABLE

  if (is_keyboard_left()) {
    render_oled_main();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
  } else {
    render_crkbd_logo();
  }
  return false;
}


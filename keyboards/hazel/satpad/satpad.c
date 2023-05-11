#include QMK_KEYBOARD_H
#include <stdio.h>

#ifdef OLED_ENABLE
  oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
  };


  bool oled_task_kb(void) {
    if (oled_task_user()) {
      oled_set_cursor(0,0);
      oled_write_P(PSTR("SAT    PAD"), false);
      uint8_t modifiers = get_mods() | get_oneshot_mods();
      
      oled_set_cursor(1,14);
      oled_write_P(PSTR("S"), (modifiers & MOD_MASK_SHIFT) || is_caps_word_on());
      oled_write_P(PSTR("C"), (modifiers & MOD_MASK_CTRL));
      oled_write_P(PSTR("A"), (modifiers & MOD_MASK_ALT));
      oled_write_P(PSTR("G"), (modifiers & MOD_MASK_GUI));
    }
    return true;
  };
#endif
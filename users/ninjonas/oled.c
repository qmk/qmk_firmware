#include QMK_KEYBOARD_H
#include <stdio.h>
#include "ninjonas.h"

#if defined(OLED_ENABLE) & !defined(KEYBOARD_kyria_rev1)

static uint32_t oled_timer = 0;


oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (is_keyboard_master()) {
    return OLED_ROTATION_0;
  }
  return OLED_ROTATION_180;
}

bool process_record_oled(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        oled_timer = timer_read32();
    }
    return true;
}

void render_layout_state(void) {
  oled_write_P(PSTR("Layout: "), false);
  switch (biton32(default_layer_state)) {
      case _COLEMAK:
        oled_write_P(PSTR("Colemak"), false);
        break;
      case _DVORAK:
        oled_write_P(PSTR("Dvorak"), false);
        break;
      case _QWERTY:
        oled_write_P(PSTR("Qwerty"), false);
        break;
      default:
        oled_write_ln_P(PSTR("Undefined"), false);
  }
}

void oled_white_space(void){
  oled_write_P(PSTR(" "), false);
}

void render_layer_state(void) {
  oled_write_P(PSTR("\nLayer:"), false);
  bool lower = layer_state_is(_LOWER) & !layer_state_is(_ADJUST);
  bool raise = layer_state_is(_RAISE) & !layer_state_is(_ADJUST);
  bool adjust = layer_state_is(_ADJUST);
  bool numpad = layer_state_is(_NUMPAD);

  if(lower){
    oled_write_P(PSTR(" Lower "), true);
  } else if(raise){
    oled_write_P(PSTR(" Raise "), true);
  } else if(adjust){
      oled_write_P(PSTR(" Adjust "), true);
  } else if(numpad) {
      oled_write_P(PSTR(" Numpad "), true);
  } else {
    oled_write_P(PSTR(" Default"), false);
  }
}

void render_mod_state(uint8_t modifiers) {
  oled_write_P(PSTR("\nMods: "), false);
  oled_write_P(PSTR("SHF"), (modifiers & MOD_MASK_SHIFT));
  oled_white_space();
  oled_write_P(PSTR("CTL"), (modifiers & MOD_MASK_CTRL));
  oled_white_space();
  oled_write_P(PSTR("ALT"), (modifiers & MOD_MASK_ALT));
  oled_white_space();
  oled_write_P(PSTR("GUI"), (modifiers & MOD_MASK_GUI));
}

void render_status(void){
  render_layout_state();
  oled_write_P(PSTR("\n"), false);
  render_layer_state();
  render_mod_state(get_mods()|get_oneshot_mods());
}

static void render_logo(void) {
  static const char PROGMEM qmk_logo[] = {
      0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
      0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
      0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
      0};

  oled_write_P(qmk_logo, false);
}

bool oled_task_user(void) {
    if (timer_elapsed32(oled_timer) > 15000) {
        oled_off();
        return;
    }
    #ifndef SPLIT_KEYBOARD
    else { oled_on(); }
    #endif

    if (is_keyboard_master()) {
        render_status();
    } else {
        render_logo();
        oled_write_P(PSTR("\n"), false);
        oled_scroll_left();
    }
    return false;
}

#endif

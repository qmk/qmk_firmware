#include "process_unicode_common.h"

void set_unicode_input_mode(uint8_t os_target)
{
  input_mode = os_target;
}

uint8_t get_unicode_input_mode(void) {
  return input_mode;
}

__attribute__((weak))
void unicode_input_start (void) {
  // save current mods
  unicode_mods = keyboard_report->mods;

  // unregister all mods to start from clean state
  if (unicode_mods & MOD_BIT(KC_LSFT)) unregister_code(KC_LSFT);
  if (unicode_mods & MOD_BIT(KC_RSFT)) unregister_code(KC_RSFT);
  if (unicode_mods & MOD_BIT(KC_LCTL)) unregister_code(KC_LCTL);
  if (unicode_mods & MOD_BIT(KC_RCTL)) unregister_code(KC_RCTL);
  if (unicode_mods & MOD_BIT(KC_LALT)) unregister_code(KC_LALT);
  if (unicode_mods & MOD_BIT(KC_RALT)) unregister_code(KC_RALT);
  if (unicode_mods & MOD_BIT(KC_LGUI)) unregister_code(KC_LGUI);
  if (unicode_mods & MOD_BIT(KC_RGUI)) unregister_code(KC_RGUI);

  switch(input_mode) {
  case UC_OSX:
    register_code(KC_LALT);
    break;
  case UC_LNX:
    register_code(KC_LCTL);
    register_code(KC_LSFT);
    register_code(KC_U);
    unregister_code(KC_U);
    unregister_code(KC_LSFT);
    unregister_code(KC_LCTL);
    break;
  case UC_WIN:
    register_code(KC_LALT);
    register_code(KC_PPLS);
    unregister_code(KC_PPLS);
    break;
  case UC_WINC:
    register_code(KC_RALT);
    unregister_code(KC_RALT);
    register_code(KC_U);
    unregister_code(KC_U);
  }
  wait_ms(UNICODE_TYPE_DELAY);
}

__attribute__((weak))
void unicode_input_finish (void) {
  switch(input_mode) {
    case UC_OSX:
    case UC_WIN:
      unregister_code(KC_LALT);
      break;
    case UC_LNX:
      register_code(KC_SPC);
      unregister_code(KC_SPC);
      break;
  }

  // reregister previously set unicode_mods
  if (unicode_mods & MOD_BIT(KC_LSFT)) register_code(KC_LSFT);
  if (unicode_mods & MOD_BIT(KC_RSFT)) register_code(KC_RSFT);
  if (unicode_mods & MOD_BIT(KC_LCTL)) register_code(KC_LCTL);
  if (unicode_mods & MOD_BIT(KC_RCTL)) register_code(KC_RCTL);
  if (unicode_mods & MOD_BIT(KC_LALT)) register_code(KC_LALT);
  if (unicode_mods & MOD_BIT(KC_RALT)) register_code(KC_RALT);
  if (unicode_mods & MOD_BIT(KC_LGUI)) register_code(KC_LGUI);
  if (unicode_mods & MOD_BIT(KC_RGUI)) register_code(KC_RGUI);
}

void register_hex(uint16_t hex) {
  for(int i = 3; i >= 0; i--) {
    uint8_t digit = ((hex >> (i*4)) & 0xF);
    register_code(hex_to_keycode(digit));
    unregister_code(hex_to_keycode(digit));
  }
}
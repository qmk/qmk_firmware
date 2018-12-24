
#include <stdio.h>
#include "comet46.h"

char mod_state_str[22];

const char *read_mod_state(void)
{
  snprintf(mod_state_str, sizeof(mod_state_str), "Mod: %s%s%s%s",
           (keyboard_report->mods & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT))) ? "SFT " : "",
           (keyboard_report->mods & (MOD_BIT(KC_LCTL) | MOD_BIT(KC_RCTL))) ? "CTL " : "",
           (keyboard_report->mods & (MOD_BIT(KC_LALT) | MOD_BIT(KC_RALT))) ? "ALT " : "",
           (keyboard_report->mods & (MOD_BIT(KC_LGUI) | MOD_BIT(KC_RGUI))) ? "GUI" : "");

  return mod_state_str;
}

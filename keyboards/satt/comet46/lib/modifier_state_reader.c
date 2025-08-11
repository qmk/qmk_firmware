#include <stdio.h>
#include "action_util.h"

char modifier_state_str[22];

const char *read_modifier_state(void) {
  uint8_t modifiers = get_mods();
  uint8_t one_shot = get_oneshot_mods();
  
  snprintf(modifier_state_str, sizeof(modifier_state_str), "Mod: %s%s%s%s",
    (modifiers & MODS_CTRL_MASK || one_shot & MODS_CTRL_MASK) ? "CTL " : "",
    (modifiers & MODS_GUI_MASK || one_shot & MODS_GUI_MASK) ? "GUI " : "",
    (modifiers & MODS_ALT_MASK || one_shot & MODS_ALT_MASK) ? "ALT " : "",
    (modifiers & MODS_SHIFT_MASK || one_shot & MODS_SHIFT_MASK) ? "SFT" : ""
  );

  return modifier_state_str;
}

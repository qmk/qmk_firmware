#include "talljoe.h"

extern keymap_config_t keymap_config;

ostype_t get_os() {
  if(keymap_config.swap_lalt_lgui) {
    return MACOSX;
  }

  return WINDOWS;
}

#define IS_OSX() (get_os() == MACOSX)

#define MOD_SEND(KEY) (IS_OSX() ? SEND_STRING(SS_LCMD(KEY)) : SEND_STRING(SS_LCTRL(KEY)))

void macro_copy() { MOD_SEND("c"); }
void macro_paste() { MOD_SEND("v"); }
void macro_lock() {
  if (IS_OSX()) {
    SEND_STRING(SS_LCTRL(SS_LCMD("q")));
  } else {
    SEND_STRING(SS_LGUI("l"));
  }
}

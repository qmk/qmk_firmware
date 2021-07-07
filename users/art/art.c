#include "art.h"
#include "string.h"

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}

__attribute__ ((weak))
void led_show_current_os(void) {
}

static bool mac_ctrl_on = false; //for switching tabs
static bool mac_gui_on = false; //for switching languages
static bool mac_alt_tab_on = false; //for switching windows

static const char *key_up[2] = {SS_UP(X_LALT), SS_UP(X_LCTL)};
static const char *key_down[2] = {SS_DOWN(X_LALT), SS_DOWN(X_LCTL)};

int char_to_del = 1;
static bool sarcasm_on = false;
static bool sarcasm_key = false;

void backspace_n_times(int times) {
  for (int i=0; i<times; i++) {
    SEND_STRING(SS_TAP(X_BSPC));  
  }
}

void send_string_remembering_length(char *string) {
  send_string(string);
  char_to_del = strlen(string);
}

void send_shifted_strings(char *string1, char *string2) {
  if ( get_mods() & MOD_MASK_SHIFT ) {
    clear_mods();
    send_string_remembering_length(string2);
  } else {
    send_string_remembering_length(string1);
  }
}

void send_shifted_strings_add(char *string1, char *string2) {
  bool shifted = get_mods() & MOD_MASK_SHIFT;
  clear_mods();

  send_string_remembering_length(string1);

  if (shifted) {
    send_string(string2);
    char_to_del = strlen(string1) + strlen(string2);
  }
}

bool is_mac_with_base_layer_off(void) {
  return !is_win && !layer_state_is(BASE);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (sarcasm_on) {
    sarcasm_key = ! sarcasm_key;  
    if (sarcasm_key) {
      SEND_STRING(SS_TAP(X_CAPS));
    }
  }

  //Checking all other non-backspace keys to clear the backspace buffer. This is to prevent the bug of deleting N chars sometime after using a macro
  if (record->event.pressed && (keycode != KC_BSPACE && keycode != XXXXXXX)) {
    char_to_del = 1;
  }

  switch (keycode) {
    case KC_TAB:
      if (record->event.pressed && is_mac_with_base_layer_off()) {
        uint8_t mods = get_mods();
        uint8_t mod_state = mods & MOD_MASK_ALT;
        if (get_mods() & mod_state) {
          del_mods(mod_state);
          add_mods(MOD_LCTL);
          mac_alt_tab_on = true;
        }

        mod_state = mods & MOD_MASK_CTRL;
        if (get_mods() & mod_state && !mac_alt_tab_on) {
          del_mods(mod_state);
          add_mods(MOD_LGUI);
          mac_ctrl_on = true;
        }
      }
      break;
    case KC_LSFT:
      if (record->event.pressed && is_mac_with_base_layer_off()) {
        uint8_t mods = get_mods();
        uint8_t mod_state = mods & MOD_MASK_AG;
        if (get_mods() & mod_state) {
          del_mods(mod_state);
          add_mods(MOD_LGUI);
          mac_gui_on = true;
          SEND_STRING(SS_TAP(X_SPACE));
          return false;
        } else {
          return true;
        }
      }
      break;
    case KC_LEFT:
    case KC_RIGHT:
      if (record->event.pressed && is_mac_with_base_layer_off()) {
        /* && !mac_ctrl_on/!mac_alt_tab_on are required since setting the state while holding the key changes
        the modifier from OS's perspective. As a result, just the pressed key cannot be the single source
        of truth to determine which state we're in, and a separate bool is required */
        uint8_t mods = get_mods();
        uint8_t mod_state = mods & MOD_MASK_ALT;
        //Allows Ctrl <-/-> on Mac if Ctrl Tab is already pressed
        if (get_mods() & mod_state && mac_alt_tab_on && !mac_ctrl_on) {
          del_mods(mod_state);
          add_mods(MOD_LCTL);
        }

        mod_state = mods & MOD_MASK_CTRL;
        if (get_mods() & mod_state && !mac_alt_tab_on) {
          del_mods(mod_state);
          add_mods(MOD_LALT);
          mac_ctrl_on = true;
        }
      }
      break;
    case KC_DEL:
      if (record->event.pressed && is_mac_with_base_layer_off()) {
        uint8_t mod_state = get_mods() & MOD_MASK_CTRL;
        if (get_mods() & mod_state) {
          del_mods(mod_state);
          add_mods(MOD_LALT);
          mac_ctrl_on = true;
        }
      }
      break;
    case KC_LALT:
      if (!record->event.pressed && is_mac_with_base_layer_off()) {
        if (mac_alt_tab_on) {
          unregister_mods(MOD_LCTL);
          mac_alt_tab_on = false;
          return false;
        } else if (mac_gui_on) {
          SEND_STRING(SS_UP(X_LGUI));
          mac_gui_on = false;
          return false;
        }
      }
      break;
    case KC_RALT:
      if (!record->event.pressed && mac_alt_tab_on && is_mac_with_base_layer_off()) {
        unregister_mods(MOD_LCTL);
        mac_alt_tab_on = false;
        return false;
      }
      break;
    case KC_LCTL:
    case KC_RCTL:
      if (!record->event.pressed && mac_ctrl_on && is_mac_with_base_layer_off()) {
        SEND_STRING(SS_UP(X_LGUI) SS_UP(X_LALT));
        mac_ctrl_on = false;
        return false;
      }
      break;

    case KC_HOME:
      if (record->event.pressed && is_mac_with_base_layer_off()) {
        SEND_STRING(SS_LCTL(SS_TAP(X_LEFT)));
        return false;
      }
      break;
    case KC_END:
      if (record->event.pressed && is_mac_with_base_layer_off()) {
        SEND_STRING(SS_LCTL(SS_TAP(X_RIGHT)));
        return false;
      }
      break;
    case KC_BSPC:
      if (record->event.pressed) {
        if (char_to_del > 1) {
          layer_off(GIT_C);
          layer_off(GIT_S);
          backspace_n_times(char_to_del);
          char_to_del = 1;
          return false;
        }

        if (is_mac_with_base_layer_off()) {
          uint8_t mod_state = get_mods() & MOD_MASK_CTRL;
          if (get_mods() & mod_state) {
            del_mods(mod_state);
            add_mods(MOD_LALT);
            mac_ctrl_on = true;
          }
        }
      }
      break;

    /* -------------------------------------------------------------------------
     *                            CUSTOM MACROS
     * ------------------------------------------------------------------------ */
    case CTRL_CTV:
      if (record->event.pressed) {
        if ( get_mods() & MOD_MASK_SHIFT ) {
          clear_mods();
          SEND_STRING(SS_LCTL("ctv"));
        } else {
          SEND_STRING(SS_LCTL("ctv") SS_TAP(X_ENTER));
        }
      }
      break;
    case CTRL_LCTV:
      if (record->event.pressed) {
        if ( get_mods() & MOD_MASK_SHIFT ) {
          //Firefox
          clear_mods();
          SEND_STRING(SS_LCTL("lcP"));
          wait_ms(200);
          SEND_STRING(SS_LCTL("v") SS_TAP(X_ENTER));
        } else if ( get_mods() & MOD_MASK_CTRL ) {
          //Chrome
          clear_mods();
          SEND_STRING(SS_LCTL("lcNv") SS_TAP(X_ENTER));
        } else {
          SEND_STRING(SS_LCTL("lctv"));
        }
      }
      break;
    case CTRL_CAV:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTL("c" SS_TAP(X_TAB)));
        wait_ms(50);
        SEND_STRING(SS_LCTL("av"));
      }
      break;
    case SARCASM:
      if (record->event.pressed) {
        sarcasm_on = !sarcasm_on;
      }
      break;

    /* -------------------------------------------------------------------------
     *                            OS TOGGLING
     * ------------------------------------------------------------------------ */
    case TOG_OS:
      if (record->event.pressed) {
        is_win = ! is_win;
        led_show_current_os();
      }
      break;
    case CTR_ALT:
      if (record->event.pressed) {
        send_string(key_down[is_win]);
      } else {
        send_string(key_up[is_win]);
      }
      break;
    case OS_CTRL:
      if (is_win) {
        if (record->event.pressed) {
          SEND_STRING(SS_DOWN(X_LCTL));
        } else {
          SEND_STRING(SS_UP(X_LCTL));
        }
      } else {
        if (record->event.pressed) {
          SEND_STRING(SS_DOWN(X_LGUI));
        } else {
          SEND_STRING(SS_UP(X_LGUI));
        }
      }
      break;
    case OS_WIN:
      if (is_win) {
        if (record->event.pressed) {
          SEND_STRING(SS_DOWN(X_LGUI));
        } else {
          SEND_STRING(SS_UP(X_LGUI));
        }
      } else {
        if (record->event.pressed) {
          SEND_STRING(SS_DOWN(X_LCTL));
        } else {
          SEND_STRING(SS_UP(X_LCTL));
        }
      }
      break;

    /* -------------------------------------------------------------------------
     *                            STRING MACROS
     * ------------------------------------------------------------------------ */
    // case :
    //   if (record->event.pressed) {
    //     send_string_remembering_length("");
    //   }
    //   break;
    // case :
    //   if (record->event.pressed) {
    //     send_string_remembering_length("", "");
    //   }
    //   break;
    case TILD_BLOCK:
      if (record->event.pressed) {
        SEND_STRING("```" SS_LSFT(SS_TAP(X_ENTER) SS_TAP(X_ENTER)) "```" SS_TAP(X_UP));
        char_to_del = 4;
      }
      break;
    case ADMINS:
      if (record->event.pressed) {
        send_shifted_strings_add("admin", "/aurora/status");
      }
      break;
    case PRESCRIPTION:
      if (record->event.pressed) {
        SEND_STRING("55\t12122019\t");
        char_to_del = 8;
      }
      break;
    case FOURS:
      if (record->event.pressed) {
        SEND_STRING("4444333322221111\t1\t12\t21\t123\n");
        char_to_del = 16;
      }
      break;
      
  case G_ADD:
    if (record->event.pressed) {
      send_string_remembering_length("git add ");
    }
    break;
  case G_BRCH:
    if (record->event.pressed) {
      send_shifted_strings_add("git branch ", "-d ");
    }
    break;
  case G_C:
    if (record->event.pressed) {
      send_string_remembering_length("git c[Heckout/Ommit]");
      layer_on(GIT_C);
    }
    break;
  case G_CHEC:
    if (!record->event.pressed) {
      bool shifted = get_mods() & MOD_MASK_SHIFT;
      clear_mods();
            
      backspace_n_times(15);
      SEND_STRING("heckout ");
      char_to_del = 13;
      if (shifted) {
        SEND_STRING("-b ");
        char_to_del = 16;
      }
      layer_off(GIT_C);
    }
    break;
  case G_COMM:
    if (!record->event.pressed) {
      bool shifted = get_mods() & MOD_MASK_SHIFT;
      clear_mods();
      
      backspace_n_times(15);
      SEND_STRING("ommit -");
      char_to_del = 15;
      if (shifted) {
        SEND_STRING("a");
        char_to_del = 16;
      }
      SEND_STRING("m \"\"" SS_TAP(X_LEFT));
      layer_off(GIT_C);
    }
    break;
  case G_DEV:
    if (record->event.pressed) {
      send_shifted_strings("develop", "master");
    }
    break;
  case G_DIFF:
    if (record->event.pressed) {
      send_string_remembering_length("git diff ");
    }
    break;	
  case G_FTCH:
    if (record->event.pressed) {
      send_string_remembering_length("git fetch ");
    }
    break;
  case G_LOG:
    if (record->event.pressed) {
      send_string_remembering_length("git log ");
    }
    break;
  case G_MERG:
    if (record->event.pressed) {
      send_string_remembering_length("git merge ");
    }
    break;
  case G_P:
    if (record->event.pressed) {
      send_shifted_strings_add("git pu", "sh -u ");
    }
    break;
  case G_RST:
    if (record->event.pressed) {
      send_string_remembering_length("git reset ");
    }
    break;
  case G_S:
    if (!record->event.pressed) {
      send_string_remembering_length("git s[taSh/How/taTus]");
      layer_on(GIT_S);			
    }
    break;
  case G_SHOW:
    if (!record->event.pressed) {
      backspace_n_times(16);
      SEND_STRING("how ");
      char_to_del = 9;
      layer_off(GIT_S);
    }
    break;			
  case G_STSH:
    if (!record->event.pressed) {
      bool shifted = get_mods() & MOD_MASK_SHIFT;
      clear_mods();

      backspace_n_times(16);
      SEND_STRING("tash ");
      char_to_del = 10;

      if (shifted) {
        clear_mods();
        SEND_STRING("apply ");

        char_to_del = 16;
      }

      layer_off(GIT_S);
    }
    break;		
  case G_STAT:
    if (!record->event.pressed) {
      backspace_n_times(16);
      SEND_STRING("tatus ");
      char_to_del = 11;
      layer_off(GIT_S);
    }
    break;

  case CTL_ALT_START ... CTL_ALT_END:
    if (record->event.pressed) {
      if (is_win) {
        tap_code16(LCTL(keycode - CTL_ALT_START));
      } else {
        tap_code16(LALT(keycode - CTL_ALT_START));
      }
    }
    break;
  }

  return process_record_keymap(keycode, record);
}

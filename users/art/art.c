#include <art.h>

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}

static bool mac_alt_tab_on = false; //for switching windows
static bool mac_ctrl_on = false; //for switching tabs

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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (sarcasm_on) {
    sarcasm_key = ! sarcasm_key;  
    if (sarcasm_key) {
      SEND_STRING(SS_TAP(X_CAPS));
    }
  }	

  //Checking all other non-backspace keys to clear the backspace buffer. This is to prevent the bug of deleting N chars sometime after using a macro
  if (record->event.pressed && (keycode != N_BSPACE)) {
    char_to_del = 1;
  }

  switch (keycode) {
    case KC_TAB:
      if (record->event.pressed && !is_win) {
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
    case KC_LEFT:
    case KC_RIGHT:
      if (record->event.pressed && !is_win) {
        uint8_t mod_state = get_mods() & MOD_MASK_CTRL;
        if (get_mods() & mod_state) {
          del_mods(mod_state);
          add_mods(MOD_LALT);
          mac_ctrl_on = true;
        }
      }
      break;
    case KC_LALT:
      if (!record->event.pressed && !is_win && mac_alt_tab_on) {
        unregister_mods(MOD_LCTL);
        mac_alt_tab_on = false;
        return false;
      }
      break;
    case KC_LCTL:
      if (!record->event.pressed && !is_win && mac_ctrl_on) {
        SEND_STRING(SS_UP(X_LGUI) SS_UP(X_LALT));
        mac_ctrl_on = false;
        return false;
      }
      break;

    case KC_HOME:
      if (record->event.pressed && !is_win) {
        SEND_STRING(SS_LCTL(SS_TAP(X_LEFT)));
        return false;
      }
      break;
    case KC_END:
      if (record->event.pressed && !is_win) {
        SEND_STRING(SS_LCTL(SS_TAP(X_RIGHT)));
        return false;
      }
      break;

    /* -------------------------------------------------------------------------
     *                            CUSTOM KEYCODES
     * -------------------------------------------------------------------------
     */ 
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
          SEND_STRING(SS_LCTL("lcPv") SS_TAP(X_ENTER));
        } else if ( get_mods() & MOD_MASK_CTRL ) {
          //Chrome
          SEND_STRING(SS_LCTL("lcNv") SS_TAP(X_ENTER));
        } else {
          SEND_STRING(SS_LCTL("lctv"));
        }
      }
      break;
    case SARCASM:
      if (record->event.pressed) {
        sarcasm_on = !sarcasm_on;
      }
      break;
    case N_BSPACE:
      if (record->event.pressed) {
        if (!is_win) {
          uint8_t mod_state = get_mods() & MOD_MASK_CTRL;
          if (get_mods() & mod_state) {
            del_mods(mod_state);
            add_mods(MOD_LALT);
            mac_ctrl_on = true;
          }
        }

        backspace_n_times(char_to_del);
        char_to_del = 1;
      }
      break;

    case TOG_OS:
      if (record->event.pressed) {
        is_win = ! is_win;
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
    case OS_HOME:
      if (is_win) {
        if (record->event.pressed) {
          SEND_STRING(SS_DOWN(X_HOME));
        } else {
          SEND_STRING(SS_UP(X_HOME));
        }
      } else {
        if (record->event.pressed) {
          SEND_STRING(SS_LCTL(SS_TAP(X_LEFT)));
        }
      }
      break;
    case OS_END:
      if (is_win) {
        if (record->event.pressed) {
          SEND_STRING(SS_DOWN(X_END));
        } else {
          SEND_STRING(SS_UP(X_END));
        }
      } else {
        if (record->event.pressed) {
          SEND_STRING(SS_LCTL(SS_TAP(X_RIGHT)));
        }
      }
      break;

    // case :
    //   if (record->event.pressed) {
    //     SEND_STRING("");
    //     char_to_del = ;
    //   }
    //   break;
    // case :
    //   if (record->event.pressed) {
    //     if ( get_mods() & MOD_MASK_SHIFT ) {
    //       clear_mods();
    //       SEND_STRING("");
    //       char_to_del = ;
    //     } else {
    //       SEND_STRING("");
    //       char_to_del = ;
    //     }
    //   }
    //   break;
    case TILD_BLOCK:
      if (record->event.pressed) {
        SEND_STRING("```" SS_TAP(X_ENTER) SS_TAP(X_ENTER) "```" SS_TAP(X_UP));
        char_to_del = 4;
      }
      break;
    case ADMINS:
      if (record->event.pressed) {
        if ( get_mods() & MOD_MASK_SHIFT ) {
          clear_mods();
          SEND_STRING("admin/aurora/status");
          char_to_del = 19;
        } else {
          SEND_STRING("admin");
          char_to_del = 5;
        }
      }
      break;
    case PRESCRIPTION:
      if (record->event.pressed) {
        SEND_STRING("55" SS_TAP(X_TAB) "12122019" SS_TAP(X_TAB));
        char_to_del = 8;
      }
      break;
    case FOURS:
      if (record->event.pressed) {
        SEND_STRING("4444333322221111" SS_TAP(X_TAB) "1" SS_TAP(X_TAB) "12" SS_TAP(X_TAB) "21" SS_TAP(X_TAB) "123" SS_TAP(X_ENTER));
        char_to_del = 16;
      }
      break;
      
  case G_ADD:
    if (record->event.pressed) {
      SEND_STRING("git add ");
        char_to_del = 8;
    }
    break;
  case G_BRCH:
    if (record->event.pressed) {
      if ( get_mods() & MOD_MASK_SHIFT ) {
        clear_mods();
        SEND_STRING("master");
        char_to_del = 6;
      } else {
        SEND_STRING("develop");
        char_to_del = 7;
      }
    }
    break;
  case G_C:
    if (record->event.pressed) {
      SEND_STRING("git c[Heckout/Ommit]");
      layer_on(GIT_C);
    }
    break;
  //These layers are required for sole purpose of switching off _C/S layer before removing chars
  case G_BS_C:
    if (record->event.pressed) {
      layer_off(GIT_C);
      //Not setting char_to_del as it's deleted explicitly in G_BS_X
      backspace_n_times(20);
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
  case G_DIFF:
    if (record->event.pressed) {
      SEND_STRING("git diff ");
      char_to_del = 9;
    }
    break;	
  case G_FTCH:
    if (record->event.pressed) {
      SEND_STRING("git fetch ");
      char_to_del = 10;
    }
    break;
  case G_LOG:
    if (record->event.pressed) {
      SEND_STRING("git log ");
      char_to_del = 8;
    }
    break;
  case G_MERG:
    if (record->event.pressed) {
      SEND_STRING("git merge ");
      char_to_del = 10;
    }
    break;
  case G_P:
    if (record->event.pressed) {
      if ( get_mods() & MOD_MASK_SHIFT ) {
        clear_mods();
        SEND_STRING("git push -u");
        char_to_del = 11;
      } else {
        SEND_STRING("git pu");
        char_to_del = 6;
      }
    }
    break;
  case G_RST:
    if (record->event.pressed) {
      SEND_STRING("git reset ");
      char_to_del = 10;
    }
    break;
  case G_S:
    if (!record->event.pressed) {
      SEND_STRING("git s[How/taSh/taTus]");
      //Not setting char_to_del as it's deleted explicitly in G_BS_X
      char_to_del = 21;
      layer_on(GIT_S);			
    }
    break;
  case G_BS_S:
    if (record->event.pressed) {
      layer_off(GIT_S);
      backspace_n_times(21);
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
      backspace_n_times(16);
      SEND_STRING("tash ");
      char_to_del = 10;
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
  }

  return process_record_keymap(keycode, record);
}
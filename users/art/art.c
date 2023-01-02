// Copyright 2022 Artjoms Rizihs (@artjomsR)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "art.h"
#include "custom_definitions.h"
#include "secr.h"
#include "funcs/led_funcs.h"
#include "funcs/string_funcs.h"

static const int COPY_DELAY = 50;
static const int INCOGNITO_DELAY = 500;
static const int LMB_SPAM_INTERVAL = 30;
static const uint8_t OS_MOD_KEYS[2] = {MOD_LALT, MOD_LCTL};

bool mac_ctrl_on = false; //for switching tabs
bool mac_gui_on = false; //for switching languages
bool mac_alt_window_switching_on = false; //for switching windows

int char_to_bspace = 1;
int char_to_del = 0;

static bool sarcasm_on = false;
static bool sarcasm_key = false;
static bool full_caps_mode = false;
bool hw_caps_on;

static bool is_lmb_timer_active = false;
static uint16_t lmb_timer = 0;

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void keyboard_post_init_user(void) {
  led_show_variable_status(is_win);
  layer_state_set_user(layer_state);
}

void matrix_scan_user(void) {
  if (is_lmb_timer_active) {
    if (timer_elapsed(lmb_timer) > LMB_SPAM_INTERVAL) {
      SEND_STRING(SS_TAP(X_BTN1)); //do stuff that needs spamming
      lmb_timer = timer_read();
    }
  }
}

bool caps_word_on(void) {
  return hw_caps_on && !full_caps_mode;
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    if (sarcasm_on) {
      sarcasm_key = ! sarcasm_key;
      del_mods(MOD_LSFT);
      if (sarcasm_key) {
        add_mods(MOD_LSFT);
      }
    }

    //Checking all other non-backspace keys to clear the backspace buffer. This is to prevent the bug of deleting N chars sometime after using a macro
    switch (keycode) {
      case LT(COMBOS,KC_BSPC):
      case KC_BACKSPACE:
      case KC_DEL:
      case KC_LSFT:
      case KC_RSFT:
      case XXXXXXX:
        break;
      default:
        char_to_bspace = 1;
        char_to_del = 0;
        break;
    }
  }

  switch (keycode) {
    case XXXXXXX:
      if (record->event.pressed && !layer_state_is(BASE)) {
        blink_leds(NUM_SCROLL_LED_ON);
        return true;
      }
      break;
    case KC_TAB:
      if (record->event.pressed && is_mac_with_base_layer_off()) {
        uint8_t mod_state = get_mods() & MOD_MASK_CTRL;
        if (get_mods() & mod_state && !mac_alt_window_switching_on) {
          del_mods(mod_state);
          add_mods(MOD_LGUI);
          mac_ctrl_on = true;
        }
      }
    case KC_GRAVE:
      if (record->event.pressed && is_mac_with_base_layer_off()) {
        uint8_t mod_state = get_mods() & MOD_MASK_ALT;
        if (get_mods() & mod_state) {
          del_mods(mod_state);
          add_mods(MOD_LCTL);
          mac_alt_window_switching_on = true;
        }
      }
      break;
    case KC_LSFT:
      if (record->event.pressed && is_mac_with_base_layer_off() && !mac_ctrl_on) {
        uint8_t mod_state = get_mods() & MOD_MASK_AG;
        if (get_mods() & mod_state) {
          del_mods(mod_state);
          add_mods(MOD_LGUI);
          mac_gui_on = true;
          send_string(lang_switch_combo);
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
        uint8_t alt_state = get_mods() & MOD_MASK_ALT;
        uint8_t ctrl_state = get_mods() & MOD_MASK_CTRL;

        //Allows Ctrl <-/-> on Mac if Ctrl Tab is already pressed
        if (get_mods() & alt_state && mac_alt_window_switching_on && !mac_ctrl_on) {
          del_mods(alt_state);
          add_mods(MOD_LCTL);
        }

        if (get_mods() & ctrl_state && !mac_alt_window_switching_on && !mac_gui_on) {
          del_mods(ctrl_state);
          add_mods(MOD_LALT);
          mac_ctrl_on = true;
        }
      }
      break;
    case KC_LALT:
      if (!record->event.pressed && is_mac_with_base_layer_off()) {
        if (mac_alt_window_switching_on) {
          unregister_mods(MOD_LCTL);
          mac_alt_window_switching_on = false;
          return false;
        } else if (mac_gui_on) {
          unregister_mods(MOD_LGUI);
          mac_gui_on = false;
          return false;
        }
        return true;
      }
      break;
    case KC_RALT:
      if (!record->event.pressed && mac_alt_window_switching_on && is_mac_with_base_layer_off()) {
        unregister_mods(MOD_LCTL);
        mac_alt_window_switching_on = false;
        return false;
      }
      break;
    case KC_LCTL:
    case KC_RCTL:
      if (!record->event.pressed && mac_ctrl_on && is_mac_with_base_layer_off()) {
        // Need to remove only previously set mods (e.g. WIN & ALT) to preserve Shift, etc
        unregister_mods(MOD_LGUI);
        unregister_mods(MOD_LALT);
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
    case KC_DEL:
    case KC_BSPC:
      if (record->event.pressed) {
        return handle_del_bspace();
      }
      break;
    case LT(COMBOS, KC_BSPC):
      if (record->event.pressed && record->tap.count == 1) {
        return handle_del_bspace();
      }
      break;
    case LT(NAV,KC_APP):
      if (!record->event.pressed && !is_win) {
        mac_ctrl_on = false;
        mac_gui_on = false;
        mac_alt_window_switching_on = false;
        clear_mods();
        SEND_STRING(SS_TAP(X_LCTL) SS_TAP(X_LGUI) SS_TAP(X_LALT) SS_TAP(X_LSFT));
        return true;
      }
      break;
    /* -------------------------------------------------------------------------
     *                            CAPS WORD
     * ------------------------------------------------------------------------ */
    case KC_CAPS:
      if (record->event.pressed && !layer_state_is(BASE))  {
        if (get_mods() & MOD_MASK_SHIFT) {
          full_caps_mode = true;
          led_show_variable_status(full_caps_mode);
          if (hw_caps_on) {
            SEND_STRING(SS_TAP(X_CAPS));
          }
        } else if (hw_caps_on) {
          full_caps_mode = false;
        }
      }
      break;
    // case KC_SPACE:
    case LT(MEDIA,KC_SPC):
    case LT(NAV,KC_SPC):
      if (record->event.pressed && caps_word_on() && !layer_state_is(BASE) && record->tap.count == 1) {
        SEND_STRING(SS_TAP(X_CAPS));
      }
      break;
    case KC_MINS:
      if (record->event.pressed && caps_word_on() && !layer_state_is(BASE)) {
        SEND_STRING("_");
        return false;
      }
      break;
    /* -------------------------------------------------------------------------
     *                            CUSTOM MACROS
     * ------------------------------------------------------------------------ */
    
    case CTRL_CTV:
      if (record->event.pressed) {
        bool shifted = get_mods() & MOD_MASK_SHIFT;
        clear_mods();

        SEND_STRING(SS_LCTL("c"));
        wait_ms(COPY_DELAY);
        SEND_STRING(SS_LCTL("tv"));

        if (!shifted) {
          SEND_STRING(SS_TAP(X_ENTER));
        }
      }
      break;
    case BEAT_BROWSER:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTL("c"));
        wait_ms(COPY_DELAY);
        SEND_STRING(SS_LGUI("1") SS_LCTL("tv") SS_TAP(X_ENTER));
      }
      break;
    case CTRL_LCTV:
      if (record->event.pressed) {
        if (get_mods() & MOD_MASK_SHIFT) {
          //Firefox
          clear_mods();
          SEND_STRING(SS_LCTL("lc"));
          wait_ms(COPY_DELAY);
          SEND_STRING(SS_LCTL("P"));
          wait_ms(INCOGNITO_DELAY);
          SEND_STRING(SS_LCTL("v") SS_TAP(X_ENTER));
        } else if (get_mods() & MOD_MASK_CTRL) {
          //Chrome
          clear_mods();
          SEND_STRING(SS_LCTL("lc"));
          wait_ms(COPY_DELAY);
          SEND_STRING(SS_LCTL("Nv") SS_TAP(X_ENTER));
        } else {
          SEND_STRING(SS_LCTL("lc"));
          wait_ms(COPY_DELAY);
          SEND_STRING(SS_LCTL("tv"));
        }
      }
      break;
    case CTRL_CAV:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTL("c" SS_TAP(X_TAB)));
        wait_ms(COPY_DELAY);
        SEND_STRING(SS_LCTL("av"));
      }
      break;
    case NEUTRAL_COPY:
      if (record->event.pressed && is_win) {
        uint8_t shifted = get_mods() & MOD_MASK_SHIFT;
        if (shifted) {
          del_mods(shifted);
          SEND_STRING(SS_LCTL("z"));
        }
        SEND_STRING(SS_LCTL("c"));
        wait_ms(COPY_DELAY);
        SEND_STRING(SS_LGUI("r") SS_LCTL("vac") SS_TAP(X_ESC));
      }
      break;
    case SARCASM:
      if (record->event.pressed) {
        del_mods(MOD_LSFT);
        sarcasm_on = !sarcasm_on;
        led_show_variable_status(sarcasm_on);
      }
      break;
    case LMB_SPAM:
      if (record->event.pressed) {
        is_lmb_timer_active = ! is_lmb_timer_active;
        lmb_timer = timer_read();
      }
      break;

    /* -------------------------------------------------------------------------
     *                            OS TOGGLING
     * ------------------------------------------------------------------------ */
    case TOG_OS:
      if (record->event.pressed) {
        is_win = ! is_win;
        led_show_variable_status(is_win);
      }
      break;
    case CTR_ALT:
      if (record->event.pressed) {
        add_mods(OS_MOD_KEYS[is_win]);
      } else {
        unregister_mods(OS_MOD_KEYS[is_win]);
      }
      break;
    case CTR_ALT_SHIFT:
      if (record->event.pressed) {
        add_mods(OS_MOD_KEYS[is_win]);
        add_mods(MOD_RSFT);
      } else {
        unregister_mods(OS_MOD_KEYS[is_win]);
        unregister_mods(MOD_RSFT);
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
    //     send_shifted_strings("", "");
    //   }
    //   break;
    case TILD_BLOCK:
      if (record->event.pressed) {
        uint8_t alted = get_mods() & MOD_MASK_ALT;
        uint8_t switch_lang_state = get_mods() & MOD_MASK_CTRL;

        if (switch_lang_state) {
          del_mods(switch_lang_state);
          switch_lang();
        }

        if (alted) {
          del_mods(alted);
          SEND_STRING(SS_TAP(X_ESC) "```" SS_LSFT(SS_TAP(X_ENTER) SS_TAP(X_ENTER)) "```" SS_TAP(X_UP));
          char_to_bspace = 4;
          char_to_del = 4;
        } else {
          SEND_STRING("`` ");

          uint8_t shifted = get_mods() & MOD_MASK_SHIFT;
          del_mods(shifted);
          SEND_STRING(SS_TAP(X_LEFT) SS_TAP(X_LEFT));
          add_mods(shifted);
          char_to_bspace = 1;
          char_to_del = 2;
        } 

        if (switch_lang_state) {
          switch_lang();
        }
      }
      break;
    case ALL_BEST:
      if (record->event.pressed) {
        send_shifted_strings_add("All the best,\nArt", "joms");
      }
      break;
    case AT_EMAIL:
      if (record->event.pressed) {
        send_string_remembering_length("@gmail.com");
      }
      break;      
    case BRACES:
      if (record->event.pressed) {
        uint8_t shifted = get_mods() & MOD_MASK_SHIFT;
        uint8_t switch_lang_state = get_mods() & MOD_MASK_CTRL;
        if (switch_lang_state) {
          del_mods(switch_lang_state);
          switch_lang();
        }

        add_mods(shifted);
        SEND_STRING("[]");

        del_mods(shifted);
        SEND_STRING(SS_TAP(X_LEFT));
        add_mods(shifted);

        if (switch_lang_state) {
          switch_lang();
        }
        char_to_bspace = 1;
        char_to_del = 1;
      }
      break;
    case DASHES:
      if (record->event.pressed) {
        SEND_STRING("--");

        uint8_t shifted = get_mods() & MOD_MASK_SHIFT;
        del_mods(shifted);
        SEND_STRING(" " SS_TAP(X_LEFT) SS_TAP(X_LEFT));
        add_mods(shifted);
        char_to_bspace = 1;
        char_to_del = 2;
      }
      break;
    case PARENTHS:
      if (record->event.pressed) {
        clear_mods();
        SEND_STRING("() " SS_TAP(X_LEFT) SS_TAP(X_LEFT));
        char_to_bspace = 1;
        char_to_del = 2;
      }
      break;
    case QUOTES:
      if (record->event.pressed) {
        uint8_t shifted = get_mods() & MOD_MASK_SHIFT;
        uint8_t switch_lang_state = get_mods() & MOD_MASK_CTRL;
        if (switch_lang_state) {
          del_mods(switch_lang_state);
          switch_lang();
        }

        add_mods(shifted);
        SEND_STRING("''");

        del_mods(shifted);
        wait_ms(LONG_TYPING_INTERVAL);
        SEND_STRING(" " SS_TAP(X_LEFT) SS_TAP(X_LEFT));
        add_mods(shifted);

        if (switch_lang_state) {
          switch_lang();
        }
        char_to_bspace = 1;
        char_to_del = 2;
      }
      break;
    case QUOTES_RU:
      if (record->event.pressed) {
        clear_mods();
        SEND_STRING("@@ ");
        wait_ms(LONG_TYPING_INTERVAL);
        SEND_STRING(SS_TAP(X_LEFT) SS_TAP(X_LEFT));
        char_to_bspace = 1;
        char_to_del = 2;
      }
      break;
    case STARS:
      if (record->event.pressed) {
        clear_mods();
        SEND_STRING("** " SS_TAP(X_LEFT) SS_TAP(X_LEFT));
        char_to_bspace = 1;
        char_to_del = 2;
      }
      break;

    case ADMINS:
      if (record->event.pressed) {
        send_string_remembering_length("admin");
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
              
        press_n_times(15, KC_BACKSPACE);
        send_string_with_translation("heckout ");
        char_to_bspace = 13;
        if (shifted) {
          send_string_with_translation("-b ");
          char_to_bspace = 16;
        }
        layer_off(GIT_C);
      }
      break;
    case G_COMM:
      if (!record->event.pressed) {
        bool ctrled = get_mods() & MOD_MASK_CTRL;
        bool shifted = get_mods() & MOD_MASK_SHIFT;
        clear_mods();

        press_n_times(15, KC_BACKSPACE);
        send_string_with_translation("ommit ");
        char_to_bspace = 11;
        layer_off(GIT_C);

        if (ctrled) {
          return false;
        }

        SEND_STRING("-");
        char_to_bspace = 15;
        if (shifted) {
          send_string_with_translation("a");
          char_to_bspace = 16;
        }
        send_string_with_translation("m");
        SEND_STRING(" \"\"" SS_TAP(X_LEFT));
        char_to_del = 1;
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
    case G_PULL:
      if (record->event.pressed) {
        send_string_remembering_length("git pull ");
      }
      break;
    case G_PUSH:
      if (record->event.pressed) {
        send_string_remembering_length("git push -u ");
      }
      break;
    case G_R:
      if (!record->event.pressed) {
        send_string_remembering_length("git re[Set/Vert/Base -i]");
        layer_on(GIT_R);
      }
      break;
    case G_RBASE:
      if (!record->event.pressed) {
        press_n_times(18, KC_BACKSPACE);
        send_string_with_translation("base -i ");
        char_to_bspace = 14;
        layer_off(GIT_R);
      }
      break;
    case G_RVERT:
      if (!record->event.pressed) {
        press_n_times(18, KC_BACKSPACE);
        send_string_with_translation("vert ");
        char_to_bspace = 11;
        layer_off(GIT_R);
      }
      break;
    case G_RST:
      if (!record->event.pressed) {
        bool shifted = get_mods() & MOD_MASK_SHIFT;
        clear_mods();

        press_n_times(18, KC_BACKSPACE);
        send_string_with_translation("set ");
        char_to_bspace = 10;

        if (shifted) {
          send_string_with_translation("--hard ");
          char_to_bspace = 17;
        }
        layer_off(GIT_R);
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
        press_n_times(16, KC_BACKSPACE);
        send_string_with_translation("how ");
        char_to_bspace = 9;
        layer_off(GIT_S);
      }
      break;			
    case G_STSH:
      if (!record->event.pressed) {
        bool shifted = get_mods() & MOD_MASK_SHIFT;
        clear_mods();

        press_n_times(16, KC_BACKSPACE);
        send_string_with_translation("tash ");
        char_to_bspace = 10;

        if (shifted) {
          clear_mods();
          send_string_with_translation("apply ");

          char_to_bspace = 16;
        }

        layer_off(GIT_S);
      }
      break;		
    case G_STAT:
      if (!record->event.pressed) {
        press_n_times(16, KC_BACKSPACE);
        send_string_with_translation("tatus ");
        char_to_bspace = 11;
        layer_off(GIT_S);
      }
      break;

    case K_CUST1 ... K_CUST3: // custom strings not stored in source control
      if (!record->event.pressed) {
          send_string_remembering_length(custom[keycode - K_CUST1]);
          blink_leds(NUM_SCROLL_LED_ON);
      }
      break;
    case K_SECR1 ... K_SECR4: // Secrets!  Externally defined strings, not stored in repo
      if (!record->event.pressed) {
          send_string_remembering_length(secrets[keycode - K_SECR1]);
          blink_leds(NUM_SCROLL_LED_ON);
      }
      break;

    case CTL_ALT_START ... CTL_ALT_END:
      if (record->event.pressed) {
        if (is_win) {
          register_code16(LCTL(keycode - CTL_ALT_START));
        } else {
          register_code16(LALT(keycode - CTL_ALT_START));
        }
      } else {
        if (is_win) {
          unregister_code16(LCTL(keycode - CTL_ALT_START));
        } else {
          unregister_code16(LALT(keycode - CTL_ALT_START));
        }
      }
      break;
  }

  return process_record_keymap(keycode, record);
}

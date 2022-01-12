// Copyright 2021 Artjoms Rizihs (@artjomsR)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "art.h"
#include "string_funcs.h"
#include "string.h"

bool mac_ctrl_on;

int char_to_bspace;
int char_to_del;

// don't forget to change COMBO_COUNT in config.h
const uint16_t PROGMEM combo_up[] = {KC_W, KC_R, COMBO_END};
const uint16_t PROGMEM combo_left[] = {KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM combo_right[] = {KC_E, KC_R, COMBO_END};
const uint16_t PROGMEM combo_down[] = {KC_S, KC_F, COMBO_END};
const uint16_t PROGMEM combo_ctrl_left[] = {KC_Q, KC_E, COMBO_END};
const uint16_t PROGMEM combo_ctrl_right[] = {KC_E, KC_T, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  COMBO(combo_up, KC_UP),
  COMBO(combo_left, KC_LEFT),
  COMBO(combo_right, KC_RIGHT),
  COMBO(combo_down, KC_DOWN),
  COMBO(combo_ctrl_left, LCTL(KC_LEFT)),
  COMBO(combo_ctrl_right, LCTL(KC_RIGHT)),
};

bool is_mac_with_base_layer_off(void) {
  return !is_win && !layer_state_is(BASE);
}

void switch_lang(void) {
  if (is_win) {
    SEND_STRING(SS_LALT(SS_TAP(X_LSFT)));
  } else {
    send_string(lang_switch_combo);
    wait_ms(10);
  }
}

void press_n_times(int times, uint16_t key) {
  for (int i=0; i<times; i++) {
    // wait_ms(TYPING_INTERVAL);
    tap_code16(key);
  }
}


bool handle_del_bspace(void) {
  if (char_to_bspace > 1 || char_to_del > 0) {
    layer_off(GIT_C);
    layer_off(GIT_R);
    layer_off(GIT_S);

    press_n_times(char_to_bspace, KC_BSPACE);
    char_to_bspace = 1;
    press_n_times(char_to_del, KC_DEL);
    char_to_del = 0;

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
  return true;
}

void send_string_with_translation(char *string) {
  #if WORKMAN_TO_QWERTY_HW_MAPPING
  if (layer_state_is(WORKMAN)) {
    int isUpperCase = 0;
    for (int i = 0; i < strlen(string); i++) {
      char toPrint = string[i];
      if (isupper(toPrint)) {
        if (toPrint == 'P') {
          SEND_STRING(":");
          continue;
        }

        isUpperCase = 1;
        toPrint = tolower(toPrint);
      }
      switch (toPrint) {
        case ':':
          toPrint = 'I';
          break;

        case 'w':
          toPrint = 'd';
          break; 
        case 'e':
          toPrint = 'r';
          break; 
        case 'r':
          toPrint = 'w';
          break; 
        case 't':
          toPrint = 'b';
          break; 
        case 'y':
          toPrint = 'j';
          break; 
        case 'u':
          toPrint = 'f';
          break; 
        case 'i':
          toPrint = 'u';
          break; 
        case 'o':
          toPrint = 'p';
          break; 
        case 'p':
          toPrint = ';';
          break; 

        case 'd':
          toPrint = 'h';
          break; 
        case 'f':
          toPrint = 't';
          break; 
        case 'h':
          toPrint = 'y';
          break; 
        case 'j':
          toPrint = 'n';
          break; 
        case 'k':
          toPrint = 'e';
          break; 
        case 'l':
          toPrint = 'o';
          break; 
        case ';':
          toPrint = 'i';
          break; 

        case 'b':
          toPrint = 'm';
          break; 
        case 'n':
          toPrint = 'k';
          break; 
        case 'm':
          toPrint = 'l';
          break; 
      }
      if (isUpperCase) {
        isUpperCase = 0;
        toPrint = toupper(toPrint);
      }
      send_char(toPrint);
    }
  } else {
    send_string(string);
  }
  #else
  send_string(string);
  #endif
}

void send_string_remembering_length(char *string) {
  send_string_with_translation(string);
  char_to_bspace = strlen(string);
}

void send_shifted_strings(char *string1, char *string2) {
  if (get_mods() & MOD_MASK_SHIFT) {
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
    char_to_bspace = strlen(string1) + strlen(string2);
  }
}
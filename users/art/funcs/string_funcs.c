// Copyright 2022 Artjoms Rizihs (@artjomsR)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "art.h"
#include "string_funcs.h"
#include "string.h"

bool mac_ctrl_on;

int char_to_bspace;
int char_to_del;

enum combo_events {
  WR_UP,
  WE_LEFT,
  ER_RIGHT,
  SF_DOWN,
  QE_PREV_WORD,
  ET_NEXT_WORD,
  QR_HOME,
  WT_END,

  Q1_F1,
  W2_F2,
  E3_F3,
  R4_F4,
  T5_F5,
  Y6_F6,
  U7_F7,
  I8_F8,
  O9_F9,
  P0_F10,
  // _F11,
  QUOTE_LBRACE_F12,

  BSPACE_DEL_ENTER,

  LEFT_RIGHT_C_S_ENTER,
  BSPC_LSFT_CLEAR,
  COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH; // do not remove - needed for combos to work

const uint16_t PROGMEM combo_up[] = {KC_W, KC_R, COMBO_END};
const uint16_t PROGMEM combo_left[] = {KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM combo_right[] = {KC_E, KC_R, COMBO_END};
const uint16_t PROGMEM combo_down[] = {KC_S, KC_F, COMBO_END};
const uint16_t PROGMEM combo_prev_word[] = {KC_Q, KC_E, COMBO_END};
const uint16_t PROGMEM combo_next_word[] = {KC_E, KC_T, COMBO_END};
const uint16_t PROGMEM combo_end[] = {KC_Q, KC_R, COMBO_END};
const uint16_t PROGMEM combo_home[] = {KC_W, KC_T, COMBO_END};

const uint16_t PROGMEM combo_enter[] = {KC_BSPC, KC_DEL, COMBO_END};

const uint16_t PROGMEM combo_f1[] = {KC_1, KC_Q, COMBO_END};
const uint16_t PROGMEM combo_f2[] = {KC_2, KC_W, COMBO_END};
const uint16_t PROGMEM combo_f3[] = {KC_3, KC_E, COMBO_END};
const uint16_t PROGMEM combo_f4[] = {KC_4, KC_R, COMBO_END};
const uint16_t PROGMEM combo_f5[] = {KC_5, KC_T, COMBO_END};
const uint16_t PROGMEM combo_f6[] = {KC_6, KC_Y, COMBO_END};
const uint16_t PROGMEM combo_f7[] = {KC_7, KC_U, COMBO_END};
const uint16_t PROGMEM combo_f8[] = {KC_8, KC_I, COMBO_END};
const uint16_t PROGMEM combo_f9[] = {KC_9, KC_O, COMBO_END};
const uint16_t PROGMEM combo_f10[] = {KC_0,KC_P, COMBO_END};
// const uint16_t PROGMEM combo_f11[] = {KC_, KC_, COMBO_END};
const uint16_t PROGMEM combo_f12[] = {KC_LBRC, KC_QUOT, COMBO_END};

const uint16_t PROGMEM done_sm[] = {KC_LEFT, KC_RIGHT, COMBO_END};
const uint16_t PROGMEM clear_line_combo[] = {KC_BSPC, KC_LSFT, COMBO_END};

combo_t key_combos[] = {
  [WR_UP] = COMBO(combo_up, KC_UP),
  [WE_LEFT] = COMBO(combo_left, KC_LEFT),
  [ER_RIGHT] = COMBO(combo_right, KC_RIGHT),
  [SF_DOWN] = COMBO(combo_down, KC_DOWN),
  [QE_PREV_WORD] = COMBO_ACTION(combo_prev_word),
  [ET_NEXT_WORD] = COMBO_ACTION(combo_next_word),
  [QR_HOME] = COMBO(combo_end, KC_HOME),
  [WT_END] = COMBO(combo_home, KC_END),

  #if defined(KEYBOARD_ktec_ergodone)
  [BSPACE_DEL_ENTER] = COMBO(combo_enter, KC_ENTER),

  [Q1_F1] = COMBO(combo_f1, KC_F1),
  [W2_F2] = COMBO(combo_f2, KC_F2),
  [E3_F3] = COMBO(combo_f3, KC_F3),
  [R4_F4] = COMBO(combo_f4, KC_F4),
  [T5_F5] = COMBO(combo_f5, KC_F5),
  [Y6_F6] = COMBO(combo_f6, KC_F6),
  [U7_F7] = COMBO(combo_f7, KC_F7),
  [I8_F8] = COMBO(combo_f8, KC_F8),
  [O9_F9] = COMBO(combo_f9, KC_F9),
  [P0_F10] = COMBO(combo_f10, KC_F10),

  [QUOTE_LBRACE_F12] = COMBO(combo_f12, KC_F12),

  [LEFT_RIGHT_C_S_ENTER] = COMBO_ACTION(done_sm),
  #endif

  [BSPC_LSFT_CLEAR] = COMBO_ACTION(clear_line_combo),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
    switch(combo_index) {
      case QE_PREV_WORD:
        if (pressed) {
          if (is_win) {
            tap_code16(C(KC_LEFT));
          } else {
            tap_code16(A(KC_LEFT));
          }
        }
        break;
      case ET_NEXT_WORD:
        if (pressed) {
          if (is_win) {
            tap_code16(C(KC_RIGHT));
          } else {
            tap_code16(A(KC_RIGHT));
          }
        }
        break; 
      case BSPC_LSFT_CLEAR:
        if (pressed) {
          tap_code16(KC_END);
          tap_code16(S(KC_HOME));
          tap_code16(KC_BSPC);
        }
        break;
      case LEFT_RIGHT_C_S_ENTER:
        if (pressed) {
          tap_code16(C(S(KC_ENTER)));
        }
        break;        
    }
}

bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
  return !layer_state_is(BASE);
}

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
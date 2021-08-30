#include QMK_KEYBOARD_H
#include "vimmode.h"
#include <print.h>
#include <string.h>

#define HOLD_SHIFT register_mods(MOD_BIT(KC_LSFT))
#define UNHOLD_SHIFT unregister_mods(MOD_BIT(KC_LSFT))
#define HOLD_ALT register_mods(MOD_BIT(KC_LALT))
#define UNHOLD_ALT unregister_mods(MOD_BIT(KC_LALT))
#define HOLD_GUI register_mods(MOD_BIT(KC_LGUI))
#define UNHOLD_GUI unregister_mods(MOD_BIT(KC_LGUI))
#define HOLD_CTRL register_mods(MOD_BIT(KC_LCTRL))
#define UNHOLD_CTRL unregister_mods(MOD_BIT(KC_LCTRL))
#define ALT KC_LALT
#define GUI KC_LGUI
#define SHIFT KC_LSFT

#define CMDBUFFSIZE 16
#define SAVEBUFFSIZE 16
#define NO_CHAR '\0'

enum mode {
  INSERT_MODE,
  INSERT_SAVE_MODE,
  COMMAND_MODE,
  REPLACE_MODE_INIT,
  REPLACE_MODE,
  REPEAT_MODE
};

bool visual_mode = false;

int       currmode = INSERT_MODE;
uint8_t   vim_layer;
int       currcmdsize = 0;
char      currcmd[CMDBUFFSIZE];
int       savedcmdsize = 0;
char      savedcmd[CMDBUFFSIZE];
int       currsavesize = 0;
uint16_t  saved_keycodes[SAVEBUFFSIZE];
bool      saved_shiftstate[SAVEBUFFSIZE];

// If REPEAT_MODE (user used .)
// just insert everything from buffer, then go back to command mode
// else go insert mode
void go_insert_mode(void) {
  if(currmode == REPEAT_MODE) {
    for(int i = 0; i < currsavesize; i++) {
      if(saved_shiftstate[i]) HOLD_SHIFT;
      tap_code(saved_keycodes[i]);
      if(saved_shiftstate[i]) UNHOLD_SHIFT;
    }
    currmode = COMMAND_MODE;
    return;
  }
  savedcmdsize = currcmdsize;
  memcpy(savedcmd, currcmd, CMDBUFFSIZE);
  currcmdsize = 0;
  currsavesize = 0;
  currmode = INSERT_SAVE_MODE;
  visual_mode = false;
  layer_off(vim_layer);
}

void add_to_vim_cmd(char c) {
  currcmd[currcmdsize++] = c;
  currcmd[currcmdsize]   = NO_CHAR;
  if(currcmdsize == CMDBUFFSIZE - 1)
    go_insert_mode();
}

void tap_code_num(uint16_t keycode, int num) {
  for (int i = 0; i < num; i++)
    tap_code(keycode);
}

void mod_type_num(uint16_t modcode, uint16_t keycode, int num) {
  register_mods(MOD_BIT(modcode));
  tap_code_num(keycode, num);
  unregister_mods(MOD_BIT(modcode));
}

void mod_type(uint16_t modcode, uint16_t keycode) {
  mod_type_num(modcode, keycode, 1);
}

int get_prev_num(void) {
  int val = 0;
  int dec = 1;
  for (int i = currcmdsize - 2; i >= 0; i--) {
    char c = currcmd[i];
    if (c >= '0' && c <= '9') {
      val += (c - '0') * dec;
      dec *= 10;
    }
  }
  return val > 500 ? 500 : val;
}

char get_prev_char(void) {
  for (int i = currcmdsize - 2; i >= 0; i--) {
    char c = currcmd[i];
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
      return c;
  }
  return NO_CHAR;
}

char get_2nd_prev_char(void) {
  bool first_found = false;
  for (int i = currcmdsize - 2; i >= 0; i--) {
    char c = currcmd[i];
    if (!first_found && ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')))
      first_found = true;
    else if (first_found && ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')))
      return c;
  }
  return NO_CHAR;
}

void handle_vim_cmd(void);

bool handle_cmd(char last_char, char prev_char, int num) {
  uint16_t direction = KC_RIGHT;
  if (num == 0) num = 1;

  switch (last_char) {
    case 'h':
    case 'j':
    case 'k':
    case 'l':
      if (last_char == 'h')
        direction = KC_LEFT;
      else if (last_char == 'j')
        direction = KC_DOWN;
      else if (last_char == 'k')
        direction = KC_UP;

      switch (prev_char) {
        case 'c':
        case 'd':
        case 'y':
          mod_type_num(SHIFT, direction, num);
          if (prev_char == 'y') {
            mod_type(GUI, KC_C);
            tap_code(KC_LEFT);
            tap_code(KC_RIGHT);
          }
          tap_code(KC_DEL);
          if (prev_char == 'c')
            go_insert_mode();
          break;
        default:
          if(visual_mode) HOLD_SHIFT;
          tap_code_num(direction, num);
          if(visual_mode) UNHOLD_SHIFT;
          break;
      }
      return true;

    case 'w':
    case 'e':
      switch (prev_char) {
        case 'd':
        case 'c':
        case 'y':
          HOLD_ALT;
          HOLD_SHIFT;
          tap_code_num(KC_RIGHT, num);
          // e vs w, going one further and then back again works in both word and
          // mac apps. Will not work well if this is the last word in the document however
          if (last_char == 'w') {
            tap_code(KC_RIGHT);
            tap_code(KC_LEFT);
          }
          UNHOLD_ALT;
          UNHOLD_SHIFT;

          // yw, ye, copy
          if (prev_char == 'y') {
            mod_type(GUI, KC_C);
            tap_code(KC_LEFT);
            tap_code(KC_RIGHT);
          } else {
            tap_code(KC_DEL);
          }
          // cw, ce leave go insert mode
          if (prev_char == 'c')
            go_insert_mode();

          // :w is save
          if (prev_char == ':' && last_char == 'w' && num == 1) {
            mod_type(GUI, KC_S);
          }
          return true;

        // Just w or e
        default:
          if(visual_mode) HOLD_SHIFT;
          mod_type_num(ALT, KC_RIGHT, num);
          if (last_char == 'w') {
            mod_type(ALT, KC_RIGHT);
            mod_type(ALT, KC_LEFT);
          }
          if(visual_mode) UNHOLD_SHIFT;
          return true;
      }

    case 'v':
      if(visual_mode) {
        visual_mode = false;
        tap_code(KC_RIGHT);
        tap_code(KC_LEFT);
      } else {
        visual_mode = true;
      }
      return true;

    case 'a':
      tap_code(KC_RIGHT);
    case 'i':
      go_insert_mode();
      return true;

    case '/':
      mod_type(GUI, KC_F);
      go_insert_mode();
      return true;

    case 'u':
      mod_type(GUI, KC_Z);
      return true;

    case 'o':
      mod_type(GUI, KC_RIGHT);
      tap_code(KC_ENT);
      go_insert_mode();
      return true;

    case 'D':
    case 'C':
      HOLD_GUI;
      mod_type(SHIFT, KC_RIGHT);
      UNHOLD_GUI;
      tap_code(KC_DEL);
      if (last_char == 'c')
        go_insert_mode();
      return true;

    case 'I':
      mod_type(GUI, KC_LEFT);
      go_insert_mode();
      return true;

    case 'A':
      mod_type(GUI, KC_RIGHT);
      go_insert_mode();
      break;

    case 'O':
      tap_code(KC_UP);
      mod_type(GUI, KC_RIGHT);
      tap_code(KC_ENT);
      go_insert_mode();
      return true;

    case 'p':
      mod_type(GUI, KC_V);
      return true;

    case 'n':
      mod_type(GUI, KC_G);
      return true;

    // This is a special case. In vi(m) p either pastes a new line or at the cursor depending
    // on what's in the paste buffer. I can't do that. So p and \ (button right of p) acts
    // as these two cases
    case '\\':
      mod_type(GUI, KC_RIGHT);
      tap_code(KC_ENT);
      mod_type(GUI, KC_V);
      return true;

    case 'q':
      // :q is save
      if (prev_char == ':' && num == 1) {
        mod_type(GUI, KC_Q);
      }
      return true;

    case 'b':
      switch (prev_char) {
        case 'd':
          HOLD_SHIFT;
          mod_type_num(ALT, KC_LEFT, num);
          UNHOLD_SHIFT;
          tap_code(KC_DEL);
          break;

        default:
          if(visual_mode) HOLD_SHIFT;
          mod_type_num(ALT, KC_LEFT, num);
          if(visual_mode) UNHOLD_SHIFT;
          break;
      }
      return true;

    case 'd':
      switch (prev_char) {
        case 'd':
          mod_type(GUI, KC_LEFT);
          mod_type_num(SHIFT, KC_DOWN, num);
          tap_code(KC_DEL);
          return true;
        case NO_CHAR:
          if(visual_mode) {
            visual_mode = false;
            num = 1;
            tap_code_num(KC_DEL, num);
            return true;
          }
      }
      return false;

    case 'y':
      switch (prev_char) {
        case 'y':
          mod_type(GUI, KC_LEFT);
          mod_type_num(SHIFT, KC_DOWN, num);
          mod_type(GUI, KC_C);
          tap_code(KC_RIGHT);
          tap_code(KC_LEFT);
          return true;
        default:
          if(visual_mode) {
            visual_mode = false;
            mod_type(GUI, KC_C);
            tap_code(KC_LEFT);
            return true;
          }
      }
      return false;

    case 'x':
      if(visual_mode) {
        visual_mode = false;
        num = 1;
      }
      tap_code_num(KC_DEL, num);
      return true;

    case 'X':
      if(visual_mode) {
        visual_mode = false;
        num = 1;
      }
      tap_code_num(KC_BSPACE, num);
      return true;

    case '0':
    case '^':
      if (currcmdsize != 1)
        return false;
      if(visual_mode) HOLD_SHIFT;
      mod_type(GUI, KC_LEFT);
      if(visual_mode) UNHOLD_SHIFT;
      return true;

    case '$':
      switch (prev_char) {
        case 'd':
        case 'c':
        case 'y':
          HOLD_GUI;
          mod_type(SHIFT, KC_RIGHT);
          UNHOLD_GUI;
          if (prev_char == 'y') {
            mod_type(GUI, KC_C);
            tap_code(KC_LEFT);
            tap_code(KC_RIGHT);
            tap_code(KC_LEFT);
            visual_mode = false;
          } else {
            tap_code(KC_DEL);
            if (prev_char == 'c')
              go_insert_mode();
          }
          return true;

        default:
          if(visual_mode) HOLD_SHIFT;
          mod_type(GUI, KC_RIGHT);
          if(visual_mode) UNHOLD_SHIFT;
          return true;
      }
      return true;

    case 'G':
      if(prev_char == 'd' || prev_char == 'x' || prev_char == 'X' || prev_char == 'c' || prev_char == 'y') {
        HOLD_SHIFT;
        mod_type(GUI, KC_DOWN);
        UNHOLD_SHIFT;
        if (prev_char == 'c' || prev_char == 'd')
          tap_code(KC_DEL);
        if (prev_char == 'c')
          go_insert_mode();
        if (prev_char == 'y') {
          mod_type(GUI, KC_C);
          tap_code(KC_LEFT);
          tap_code(KC_RIGHT);
        }
      } else {
        if(visual_mode) HOLD_SHIFT;
        mod_type(GUI, KC_DOWN);
        if(visual_mode) UNHOLD_SHIFT;
      }
      return true;

    case 'g':
      if (prev_char == 'g') {
        char ch2 = get_2nd_prev_char();
        if(ch2 == 'd' || ch2 == 'x' || ch2 == 'X' || ch2 == 'c' || ch2 == 'y') {
          HOLD_SHIFT;
          mod_type(GUI, KC_UP);
          UNHOLD_SHIFT;
          if (ch2 == 'c' || ch2 == 'd')
            tap_code(KC_DEL);
          if (ch2 == 'c')
            go_insert_mode();
          if (ch2 == 'y') {
            mod_type(GUI, KC_C);
            tap_code(KC_RIGHT);
            tap_code(KC_LEFT);
          }
        } else {
          if(visual_mode) HOLD_SHIFT;
          mod_type(GUI, KC_UP);
          if(visual_mode) UNHOLD_SHIFT;
        }
      }
      return false;

    case 'r':
      tap_code(KC_DEL);
      currcmdsize = 0;
      visual_mode = false;
      currmode = REPLACE_MODE_INIT;
      return true;

    case '.':
      if(savedcmdsize != 0) {
        currmode = REPEAT_MODE;
        currcmdsize = savedcmdsize;
        memcpy(currcmd, savedcmd, CMDBUFFSIZE);
        handle_vim_cmd();
        currcmdsize = 0;
      }
      return true;
  }
  return false;
}

const char keycode_to_char_map[58] = {
  NO_CHAR, NO_CHAR, NO_CHAR, NO_CHAR,
  'a','b','c','d','e',NO_CHAR,'g','h','i','j',
  'k','l',NO_CHAR, NO_CHAR,'o','p','q','r', NO_CHAR, NO_CHAR,
  'u','v','w','x','y',NO_CHAR,
  '1','2','3','4','5','6','7','8','9','0',
  NO_CHAR, NO_CHAR, NO_CHAR, NO_CHAR, ' ', NO_CHAR, NO_CHAR, NO_CHAR, NO_CHAR, '\\',
  NO_CHAR, NO_CHAR, NO_CHAR, NO_CHAR, NO_CHAR, '.', '/'
};

const char keycode_to_char_map_shifted[58] = {
  NO_CHAR, NO_CHAR, NO_CHAR, NO_CHAR,
  'A',NO_CHAR,'C','D',NO_CHAR,NO_CHAR,'G',NO_CHAR,'I',NO_CHAR,
  NO_CHAR,NO_CHAR,NO_CHAR, NO_CHAR,'O','P',NO_CHAR,NO_CHAR,NO_CHAR, NO_CHAR,
  'U','V',NO_CHAR,'X',NO_CHAR,NO_CHAR,
  NO_CHAR,NO_CHAR,NO_CHAR,'$',NO_CHAR,'^',NO_CHAR,NO_CHAR,NO_CHAR,NO_CHAR,
  NO_CHAR, NO_CHAR, NO_CHAR, NO_CHAR, NO_CHAR, NO_CHAR, NO_CHAR, NO_CHAR, NO_CHAR, '|',
  NO_CHAR, ':', NO_CHAR, NO_CHAR, NO_CHAR, NO_CHAR, NO_CHAR
};

char keycode_to_char(uint16_t keycode, keyrecord_t *record) {
  if (SHIFT_HELD) {
    return keycode_to_char_map_shifted[keycode];
  }
  if(keycode < KC_A || keycode > KC_SLASH)
    return NO_CHAR;
  return keycode_to_char_map[keycode];
}

void handle_vim_cmd(void) {
  char last_char = currcmd[currcmdsize - 1];
  char prev_char = get_prev_char();
  int  prev_num  = get_prev_num();
  bool lshift    = L_SHIFT_HELD;
  bool rshift    = R_SHIFT_HELD;
  if (lshift) UNHOLD_SHIFT;
  if (rshift) unregister_mods(MOD_BIT(KC_RSFT));

  if (handle_cmd(last_char, prev_char, prev_num))
    currcmdsize = 0;

  if (lshift) HOLD_SHIFT;
  if (rshift) register_mods(MOD_BIT(KC_RSFT));
}

bool handle_vim_mode(uint16_t keycode, keyrecord_t *record, uint8_t vim_layer_no) {
  if (currmode == COMMAND_MODE) {
    switch (keycode) {
      case KC_LALT:
      case KC_LSHIFT:
      case KC_LCTRL:
      case KC_LGUI:
      case KC_RALT:
      case KC_RSHIFT:
      case KC_RCTRL:
      case KC_RGUI:
        return false;
    }

    if (currcmdsize == 0) {
      // This takes care of holding down one of hjklwbe
      uint16_t newKey = 0;
      switch(keycode) {
        case KC_H:
          newKey = KC_LEFT;
          break;
        case KC_J:
          newKey = KC_DOWN;
          break;
        case KC_K:
          newKey = KC_UP;
          break;
        case KC_L:
          newKey = KC_RIGHT;
          break;
        case KC_W:
          if(record->event.pressed)
            HOLD_ALT;
          else
            UNHOLD_ALT;

          newKey = KC_RIGHT;
          break;
        case KC_E:
          if(record->event.pressed)
            HOLD_ALT;
          else
            UNHOLD_ALT;
          newKey = KC_RIGHT;
          break;
        case KC_B:
          if(record->event.pressed)
            HOLD_ALT;
          else
            UNHOLD_ALT;
          newKey = KC_LEFT;
          break;
      }
      if(newKey != 0) {
        if(record->event.pressed) {
          if(visual_mode)
            HOLD_SHIFT;
          register_code(newKey);
        } else {
          unregister_code(newKey);
          if(keycode == KC_W) {
            mod_type(ALT, KC_RIGHT);
            mod_type(ALT, KC_LEFT);
          }
          if(visual_mode)
            UNHOLD_SHIFT;
        }
        return true;
      }
    }
  }

  if(currmode == REPLACE_MODE_INIT) {
    currmode = REPLACE_MODE;
    return true;
  } else
  if(currmode == REPLACE_MODE) {
    if (!record->event.pressed) {
      currmode = COMMAND_MODE;
    }
    return false;
  }

  if (!record->event.pressed)
    return currmode != INSERT_MODE && currmode != INSERT_SAVE_MODE;

  vim_layer = vim_layer_no;

  if (keycode == VIM_ESC) {
    currmode = COMMAND_MODE;
    layer_on(vim_layer);
    visual_mode = false;
    currcmdsize = 0;
  }

  if (currmode == INSERT_SAVE_MODE) {
    if(currsavesize == SAVEBUFFSIZE || keycode < KC_A || keycode > KC_SLASH) {
        currmode = INSERT_MODE;
        savedcmdsize = 0;
        currsavesize = 0;
        return false;
    }

    saved_keycodes[currsavesize] = keycode;
    saved_shiftstate[currsavesize++] = SHIFT_HELD;
    return false;
  } else if (currmode == INSERT_MODE) {
    return false;
  }

  if(GUI_HELD) {
    go_insert_mode();
    return false;
  }

  if (CTRL_HELD) {
    if (keycode == KC_R) {
      HOLD_SHIFT;
      UNHOLD_CTRL;
      mod_type(GUI, KC_Z);
      HOLD_CTRL;
      UNHOLD_SHIFT;
      return true;
    } else if (keycode == KC_F) {
      UNHOLD_CTRL;
      tap_code(KC_PGDOWN);
      HOLD_CTRL;
      return true;
    } else if (keycode == KC_B) {
      UNHOLD_CTRL;
      tap_code(KC_PGUP);
      HOLD_CTRL;
      return true;
    }
    go_insert_mode();
    return false;
  }

  char ch = keycode_to_char(keycode, record);
  if(ch == NO_CHAR)
    return true;

  add_to_vim_cmd(ch);
  handle_vim_cmd();
  return true;
}

 /* Copyright 2015-2017 Christon DeWan *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "xtonhasvim.h"


uint16_t vstate = VIM_START;
static bool yank_was_lines = false;
static bool SHIFTED = false;
static uint32_t mod_override_layer_state = 0;
static uint16_t mod_override_triggering_key = 0;

static void edit(void) { vstate = VIM_START; layer_clear(); }
#define EDIT edit()


static void simple_movement(uint16_t keycode) {
  switch(keycode) {
    case VIM_B:
      register_code(KC_LALT);
        tap_code16(LSFT(KC_LEFT)); // select to start of this word
      unregister_code(KC_LALT);
      break;
    case VIM_E:
      register_code(KC_LALT);
        tap_code16(LSFT(KC_RIGHT)); // select to end of this word
      unregister_code(KC_LALT);
      break;
    case VIM_H:
      tap_code16(LSFT(KC_LEFT));
      break;
    case VIM_J:
      tap_code16(LGUI(KC_LEFT));
      tap_code16(LSFT(KC_DOWN));
      tap_code16(LSFT(KC_DOWN));
      break;
    case VIM_K:
      tap_code16(LGUI(KC_LEFT));
      tap_code(KC_DOWN);
      tap_code16(LSFT(KC_UP));
      tap_code16(LSFT(KC_UP));
      break;
    case VIM_L:
      tap_code16(LSFT(KC_RIGHT));
      break;
    case VIM_W:
      register_code(KC_LALT);
      tap_code16(LSFT(KC_RIGHT)); // select to end of this word
      tap_code16(LSFT(KC_RIGHT)); // select to end of next word
      tap_code16(LSFT(KC_LEFT));  // select to start of next word
      unregister_code(KC_LALT);
      break;
  }
}

static void comma_period(uint16_t keycode) {
  switch (keycode) {
  case VIM_COMMA:
    if (SHIFTED) {
      // indent
      tap_code16(LGUI(KC_LBRACKET));
    } else {
      // toggle comment
      tap_code16(LGUI(KC_SLASH));
    }
    break;
  case VIM_PERIOD:
    if (SHIFTED) {
      // outdent
      tap_code16(LGUI(KC_RBRACKET));
    }
    break;
  }
}


bool process_record_vimlayer(uint16_t keycode, keyrecord_t *record) {

  /****** mod passthru *****/
  if(record->event.pressed && layer_state_is(vim_cmd_layer()) && (IS_MOD(keycode) || keycode == LSFT(KC_LALT))) {
    mod_override_layer_state = layer_state;
    mod_override_triggering_key = keycode;
    // TODO: change this to track key location instead
    layer_clear();
    return true; // let the event fall through...
  }
  if(mod_override_layer_state && !record->event.pressed && keycode == mod_override_triggering_key) {
    layer_state_set(mod_override_layer_state);
    mod_override_layer_state = 0;
    mod_override_triggering_key = 0;
    return true;
  }

  if (VIM_START <= keycode && keycode <= VIM_ESC) {
    if(keycode == VIM_SHIFT) {
      SHIFTED = record->event.pressed;
      return false;
    }

    if (record->event.pressed) {
      if(keycode == VIM_START) {
        // entry from anywhere
        layer_on(vim_cmd_layer());
        vstate = VIM_START;

        // reset state
        yank_was_lines = false;
        SHIFTED = false;
        mod_override_layer_state = 0;
        mod_override_triggering_key = 0;

        return false;
      }
      switch(vstate) {
        case VIM_START:
          switch(keycode){
            /*****************************
             * ground state
             *****************************/
            case VIM_A:
              if(SHIFTED) {
                // tap_code16(LGUI(KC_RIGHT));
                tap_code16(LCTL(KC_E));
              } else {
                tap_code(KC_RIGHT);
              }
              EDIT;
              break;
            case VIM_B:
              register_code(KC_LALT);
              register_code(KC_LEFT);
              break;
            case VIM_C:
              if(SHIFTED) {
                register_code(KC_LSHIFT);
                  tap_code16(LGUI(KC_RIGHT));
                unregister_code(KC_LSHIFT);
                tap_code16(LGUI(KC_X));
                yank_was_lines = false;
                EDIT;
              } else {
                vstate = VIM_C;
              }
              break;
            case VIM_D:
              if(SHIFTED) {
                tap_code16(LCTL(KC_K));
              } else {
                vstate = VIM_D;
              }
              break;
            case VIM_E:
              register_code(KC_LALT);
              register_code(KC_RIGHT);
              break;
            case VIM_G:
              if(SHIFTED) {
                tap_code(KC_END);
              } else {
                vstate = VIM_G;
              }
              break;
            case VIM_H:
              register_code(KC_LEFT);
              break;
            case VIM_I:
              if(SHIFTED){
                tap_code16(LCTL(KC_A));
              }
              EDIT;
              break;
            case VIM_J:
              if(SHIFTED) {
                tap_code16(LGUI(KC_RIGHT));
                tap_code(KC_DEL);
              } else {
                register_code(KC_DOWN);
              }
              break;
            case VIM_K:
              register_code(KC_UP);
              break;
            case VIM_L:
              register_code(KC_RIGHT);
              break;
            case VIM_O:
              if(SHIFTED) {
                tap_code16(LGUI(KC_LEFT));
                tap_code(KC_ENTER);
                tap_code(KC_UP);
                EDIT;
              } else {
                tap_code16(LGUI(KC_RIGHT));
                tap_code(KC_ENTER);
                EDIT;
              }
              break;
            case VIM_P:
              if(SHIFTED) {
                tap_code16(LGUI(KC_LEFT));
                tap_code16(LGUI(KC_V));
              } else {
                if(yank_was_lines) {
                  tap_code16(LGUI(KC_RIGHT));
                  tap_code(KC_RIGHT);
                  tap_code16(LGUI(KC_V));
                } else {
                  tap_code16(LGUI(KC_V));
                }
              }
              break;
            case VIM_S:
              // s for substitute?
              if(SHIFTED) {
                tap_code16(LGUI(KC_LEFT));
                register_code(KC_LSHIFT);
                  tap_code16(LGUI(KC_RIGHT));
                unregister_code(KC_LSHIFT);
                tap_code16(LGUI(KC_X));
                yank_was_lines = false;
                EDIT;
              } else {
                tap_code16(LSFT(KC_RIGHT));
                tap_code16(LGUI(KC_X));
                yank_was_lines = false;
                EDIT;
              }
              break;
            case VIM_U:
              if(SHIFTED) {
                register_code(KC_LSFT);
                  tap_code16(LGUI(KC_Z));
                unregister_code(KC_LSHIFT);
              } else {
                tap_code16(LGUI(KC_Z));
              }
              break;
            case VIM_V:
              if(SHIFTED) {
                tap_code16(LGUI(KC_LEFT));
                tap_code16(LSFT(KC_DOWN));
                vstate = VIM_VS;
              } else {
                vstate = VIM_V;
              }
              break;
            case VIM_W:
              register_code(KC_LALT);
                tap_code(KC_RIGHT);
                tap_code(KC_RIGHT);
                tap_code(KC_LEFT);
              unregister_code(KC_LALT);
              break;
            case VIM_X:
              // tap_code16(LSFT(KC_RIGHT));
              // tap_code16(LGUI(KC_X));
              register_code(KC_DEL);
              break;
            case VIM_Y:
              if(SHIFTED) {
                tap_code16(LGUI(KC_LEFT));
                tap_code16(LSFT(KC_DOWN));
                tap_code16(LGUI(KC_C));
                tap_code(KC_RIGHT);
                yank_was_lines = true;
              } else {
                vstate = VIM_Y;
              }
              break;
            case VIM_COMMA:
            case VIM_PERIOD:
              comma_period(keycode);
              break;
          }
          break;
        case VIM_C:
          /*****************************
           * c-  ...for change. I never use this...
           *****************************/
          switch(keycode) {
          case VIM_B:
          case VIM_E:
          case VIM_H:
          case VIM_J:
          case VIM_K:
          case VIM_L:
          case VIM_W:
            simple_movement(keycode);
            tap_code16(LGUI(KC_X));
            yank_was_lines = false;
            EDIT;
            break;

          case VIM_C:
            tap_code16(LGUI(KC_LEFT));
            register_code(KC_LSHIFT);
              tap_code16(LGUI(KC_RIGHT));
            unregister_code(KC_LSHIFT);
            tap_code16(LGUI(KC_X));
            yank_was_lines = false;
            EDIT;
            break;
          case VIM_I:
            vstate = VIM_CI;
            break;
          default:
            vstate = VIM_START;
            break;
          }
          break;
        case VIM_CI:
          /*****************************
           * ci-  ...change inner word
           *****************************/
          switch(keycode) {
            case VIM_W:
              tap_code16(LALT(KC_LEFT));
              register_code(KC_LSHIFT);
                tap_code16(LALT(KC_RIGHT));
              unregister_code(KC_LSHIFT);
              tap_code16(LGUI(KC_X));
              yank_was_lines = false;
              EDIT;
            default:
              vstate = VIM_START;
              break;
          }
          break;
        case VIM_D:
          /*****************************
           * d-  ...delete stuff
           *****************************/
          switch(keycode) {
          case VIM_B:
          case VIM_E:
          case VIM_H:
          case VIM_J:
          case VIM_K:
          case VIM_L:
          case VIM_W:
            simple_movement(keycode);
            tap_code16(LGUI(KC_X));
            yank_was_lines = false;
            vstate = VIM_START;
            break;
          case VIM_D:
            tap_code16(LGUI(KC_LEFT));
            tap_code16(LSFT(KC_DOWN));
            tap_code16(LGUI(KC_X));
            yank_was_lines = true;
            vstate = VIM_START;
            break;
          case VIM_I:
            vstate = VIM_DI;
            break;
          default:
            vstate = VIM_START;
            break;
          }
          break;
        case VIM_DI:
          /*****************************
           * ci-  ...delete a word... FROM THE INSIDE!
           *****************************/
          switch(keycode) {
            case VIM_W:
              tap_code16(LALT(KC_LEFT));
              register_code(KC_LSHIFT);
                tap_code16(LALT(KC_RIGHT));
              unregister_code(KC_LSHIFT);
              tap_code16(LGUI(KC_X));
              yank_was_lines = false;
              vstate = VIM_START;
            default:
              vstate = VIM_START;
              break;
          }
          break;
        case VIM_V:
          /*****************************
           * visual!
           *****************************/
          switch(keycode) {
            case VIM_D:
            case VIM_X:
              tap_code16(LGUI(KC_X));
              yank_was_lines = false;
              vstate = VIM_START;
              break;
            case VIM_B:
              register_code(KC_LALT);
              register_code(KC_LSHIFT);
              register_code(KC_LEFT);
              // leave open for key repeat
              break;
            case VIM_E:
              register_code(KC_LALT);
              register_code(KC_LSHIFT);
              register_code(KC_RIGHT);
              // leave open for key repeat
              break;
            case VIM_H:
              register_code(KC_LSHIFT);
              register_code(KC_LEFT);
              break;
            case VIM_I:
              vstate = VIM_VI;
              break;
            case VIM_J:
              register_code(KC_LSHIFT);
              register_code(KC_DOWN);
              break;
            case VIM_K:
              register_code(KC_LSHIFT);
              register_code(KC_UP);
              break;
            case VIM_L:
              register_code(KC_LSHIFT);
              register_code(KC_RIGHT);
              break;
            case VIM_W:
              register_code(KC_LALT);
              tap_code16(LSFT(KC_RIGHT)); // select to end of this word
              tap_code16(LSFT(KC_RIGHT)); // select to end of next word
              tap_code16(LSFT(KC_LEFT));  // select to start of next word
              unregister_code(KC_LALT);
              break;
            case VIM_P:
              tap_code16(LGUI(KC_V));
              vstate = VIM_START;
              break;
            case VIM_Y:
              tap_code16(LGUI(KC_C));
              tap_code(KC_RIGHT);
              yank_was_lines = false;
              vstate = VIM_START;
              break;
            case VIM_V:
            case VIM_ESC:
              tap_code(KC_RIGHT);
              vstate = VIM_START;
              break;
            case VIM_COMMA:
            case VIM_PERIOD:
              comma_period(keycode);
              break;
            default:
              // do nothing
              break;
          }
          break;
        case VIM_VI:
          /*****************************
           * vi-  ...select a word... FROM THE INSIDE!
           *****************************/
          switch(keycode) {
            case VIM_W:
              tap_code16(LALT(KC_LEFT));
              register_code(KC_LSHIFT);
                tap_code16(LALT(KC_RIGHT));
              unregister_code(KC_LSHIFT);
              vstate = VIM_V;
            default:
              // ignore
              vstate = VIM_V;
              break;
          }
          break;
        case VIM_VS:
          /*****************************
           * visual line
           *****************************/
          switch(keycode) {
            case VIM_D:
            case VIM_X:
              tap_code16(LGUI(KC_X));
              yank_was_lines = true;
              vstate = VIM_START;
              break;
            case VIM_J:
              register_code(KC_LSHIFT);
              register_code(KC_DOWN);
              break;
            case VIM_K:
              register_code(KC_LSHIFT);
              register_code(KC_UP);
              break;
            case VIM_Y:
              tap_code16(LGUI(KC_C));
              yank_was_lines = true;
              tap_code(KC_RIGHT);
              vstate = VIM_START;
              break;
            case VIM_P:
              tap_code16(LGUI(KC_V));
              vstate = VIM_START;
              break;
            case VIM_V:
            case VIM_ESC:
              tap_code(KC_RIGHT);
              vstate = VIM_START;
              break;
            case VIM_COMMA:
            case VIM_PERIOD:
              comma_period(keycode);
              break;
            default:
              // do nothing
              break;
          }
          break;
        case VIM_G:
          /*****************************
           * gg, and a grab-bag of other macros i find useful
           *****************************/
          switch(keycode) {
            case VIM_G:
              tap_code(KC_HOME);
              break;
            // codes b
            case VIM_H:
              tap_code16(LCTL(KC_A));
              break;
            case VIM_J:
              register_code(KC_PGDN);
              break;
            case VIM_K:
              register_code(KC_PGUP);
              break;
            case VIM_L:
              tap_code16(LCTL(KC_E));
              break;
            default:
              // do nothing
              break;
          }
          vstate = VIM_START;
          break;
        case VIM_Y:
          /*****************************
           * yoink!
           *****************************/
          switch(keycode) {
          case VIM_B:
          case VIM_E:
          case VIM_H:
          case VIM_J:
          case VIM_K:
          case VIM_L:
          case VIM_W:
            simple_movement(keycode);
            tap_code16(LGUI(KC_C));
            tap_code(KC_RIGHT);
            yank_was_lines = false;
            break;
          case VIM_Y:
            tap_code16(LGUI(KC_LEFT));
            tap_code16(LSFT(KC_DOWN));
            tap_code16(LGUI(KC_C));
            tap_code(KC_RIGHT);
            yank_was_lines = true;
            break;
          default:
            // NOTHING
            break;
          }
          vstate = VIM_START;
          break;
        }
    } else {
      /************************
       * key unregister_code events
       ************************/
      clear_keyboard();
    }
    return false;
  } else {
    return true;
  }
}


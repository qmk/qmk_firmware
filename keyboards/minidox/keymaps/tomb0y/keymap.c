#include "minidox.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

#define _WM      0
#define _DK      1
#define _FUN     2

#define _DK_ACT  0
#define _DK_REL  1
#define _KC_COMS 2
#define _KC_CENT 3

#define DK_ACT   M(_DK_ACT)        // activate dead key layer
#define DK_REL   M(_DK_REL)        // release dead key layer
#define KC_COMS  M(_KC_COMS)       // comma + space
#define KC_CENT  M(_KC_CENT)       // comma + enter
#define KC_ENOP  ALT_T(KC_ENT)     // press for enter, hold for option
#define KC_BSCM  GUI_T(KC_BSPC)    // press for backspace, hold for command
#define KC_CTES  CTL_T(KC_ESC)     // press for escape, hold for control
#define KC_SHTB  SFT_T(KC_TAB)     // press for tab, hold for shift
#define KC_SPFN  LT(_FUN, KC_SPC)  // press for space, hold for function layer (aka spacefn)
#define KC_OPTB  RALT(KC_TAB)      // option + tab
#define KC_CCSP  RGUI(RCTL(KC_P))  // control + command + p
#define KC_CSTB  S(RCTL(KC_TAB))   // shift + control + tab
#define KC_C_TB  RCTL(KC_TAB)      // control + tab
#define KC_C_LF  RCTL(KC_LEFT)     // control + left
#define KC_C_RT  RCTL(KC_RGHT)     // control + right
#define KC_BRUP  KC_F15            // brightness up on osx
#define KC_BRDN  KC_F14            // brightness down on osx

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Base layer - workman
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   q  |   d  |   r  |   w  |   b  |           |   j  |   f  |   u  |   p  |   ;  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   a  |   s  |   h  |   t  |   g  |           |   y  |   n  |   e  |   o  |   i  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   z  |   x  |   m  |   c  |   v  |           |   k  |   l  | dead |   .  |   /  |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,---------------------.
 *                 | tab   | esc  | enter|    |bckspc| space|   tab |
 *                 | shift | ctrl | alt  |    |  gui |   fn | shift |
 *                 `-------+------+      |    |      |------+-------.
 *                                `------'    `------'
 */
  [_WM] = KEYMAP( \
    KC_Q,    KC_D,    KC_R,    KC_W,    KC_B,        KC_J,    KC_F,    KC_U,    KC_P,    KC_SCLN, \
    KC_A,    KC_S,    KC_H,    KC_T,    KC_G,        KC_Y,    KC_N,    KC_E,    KC_O,    KC_I,    \
    KC_Z,    KC_X,    KC_M,    KC_C,    KC_V,        KC_K,    KC_L,    DK_ACT,  KC_DOT,  KC_SLSH, \
                      KC_SHTB, KC_CTES, KC_ENOP,     KC_BSCM, KC_SPFN, KC_SHTB                    \
  ),

/* Dead key layer
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   %  |   &  |   ?  |   +  |   @  |           |   $  |   _  |   [  |   ]  |   !  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   #  |   (  |   =  |   0  |   {  |           |   }  |   1  |   *  |   )  |   -  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   6  |   7  |   8  |   9  |   |  |           |   \  |   2  |   3  |   4  |   5  |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,---------------------.
 *                 | tab   | esc  | comma|    |bckspc| comma|   tab |
 *                 | shift | ctrl |+enter|    |  gui |+space| shift |
 *                 `-------+------+      |    |      |------+-------.
 *                                `------'    `------'
 */
  [_DK] = KEYMAP( \
    KC_PERC, KC_AMPR, KC_QUES, KC_PLUS, KC_AT,       KC_DLR,  KC_UNDS, KC_LBRC, KC_RBRC, KC_EXLM, \
    KC_HASH, KC_LPRN, KC_EQL,  KC_0,    KC_LCBR,     KC_RCBR, KC_1,    KC_ASTR, KC_RPRN, KC_MINS, \
    KC_6,    KC_7,    KC_8,    KC_9,    KC_PIPE,     KC_BSLS, KC_2,    DK_REL,  KC_4,    KC_5,    \
                      KC_SHTB, KC_CTES, KC_CENT,     KC_BSCM, KC_COMS, KC_SHTB                    \
  ),

/* Function layer
 *
 * ,----------------------------------.           ,---------------------------------.
 * |      |  del |⌃←  |  ⌃→ |      |           | mute | vol- | vol+ | ⌘⌃p |      |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   `  |  end | pgup | pgdn | home |           |  ←  |   ↓  |   ↑  |  →  |   '  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * | ⌥⇥ |      |⇧⌃⇥| ⌃⇥  |       |           |      |  br- | ,    | br+  |  ^   |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,---------------------.
 *                 | tab   |      | enter|    |bckspc|      |   tab |
 *                 | shift |      | alt  |    |  gui |      | shift |
 *                 `-------+------+      |    |      |------+-------.
 *                                `------'    `------'
 */
 [_FUN] = KEYMAP( \
    XXXXXXX, KC_DEL,  KC_C_LF, KC_C_RT, XXXXXXX,     KC_MUTE, KC_VOLD, KC_VOLU, KC_CCSP, XXXXXXX, \
    KC_GRV,  KC_END,  KC_PGUP, KC_PGDN, KC_HOME,     KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_QUOT, \
    KC_OPTB, XXXXXXX, KC_CSTB, KC_C_TB, XXXXXXX,     XXXXXXX, KC_BRDN, KC_COMM, KC_BRUP, KC_CIRC, \
                      KC_SHTB, XXXXXXX, KC_ENOP,     KC_BSCM, _______, KC_SHTB                    \
  )
};

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  switch(id) {
    case _KC_COMS:
      if (record->event.pressed) {
        return MACRO(T(COMM), T(SPC), END); // comma + space
      }
      break;
    case _KC_CENT:
      if (record->event.pressed) {
        return MACRO(T(COMM), T(ENT), END); // comma + enter
      }
      break;
    case _DK_ACT:
      if (record->event.pressed) {
        if (keyboard_report->mods & MOD_BIT(KC_LSFT) || keyboard_report->mods & MOD_BIT(KC_RSFT)) { // act as comma when shift is pressed (eg <)
          register_code(KC_COMM);
        } else { // activate oneshot dead key layer otherwise
          layer_on(_DK);
          set_oneshot_layer(_DK, ONESHOT_START);
        }
      } else { // make sure to deactive dead key layer on key release
        clear_oneshot_layer_state(ONESHOT_PRESSED);
        unregister_code(KC_COMM);
      }
      break;
    case _DK_REL:
      if (record->event.pressed) { // act as 3 on keypress
        register_code(KC_3);
      } else { // make sure to deactive dead key layer on key release
        clear_oneshot_layer_state(ONESHOT_PRESSED);
        unregister_code(KC_3);
      }
      break;
  }

  return MACRO_NONE;
};

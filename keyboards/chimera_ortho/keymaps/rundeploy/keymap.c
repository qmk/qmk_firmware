#include "chimera_ortho.h"

//@mechanical keyboard chimera_ortho keymap
//@author:  Cristian aka rundeploy
//@updated: 29/01/2018

enum custom_keycodes {
    KC_EML = SAFE_RANGE, //MESC + EML = email insertion
    KC_PSW,             //MESC + PSW = pass insertion           
};
enum {
  TD_LCTRL_CAPS = 0
};

#define KC_MESC LT(_MACROS, KC_ESC) //MacroESC - Hold is Macro Layer, Press is ESC
#define KC_TO0 TO(0) //Turn ON layer 0 when pressed
#define KC_TO2 TO(2) //Turn ON layer 2 when pressed
#define KC_MO MO(1)  // Momentarily turn on layer 1 when pressed
#define KC_SWT SFT_T(KC_TAB) // SHIFT when held, TAB when tapped
#define KC_TD_CTRLCAPS TD(TD_LCTRL_CAPS) //Tap-Dance for CAPS LOCK DOESNT WORK NEED FIX

#define LONGPRESS_DELAY 150
//#define LAYER_TOGGLE_DELAY 300

#define _QWERTY   0   //Base layer
#define _FUNCTION 1   //Function layer
#define _FROW     2   //F Row layer
#define _MACROS   3   //Macro layer

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {



  /*  Layer 0: (Base Layer) Default Layer
   * ,----------------------------------.     ,----------------------------------.
   * |MESC| Q  | W  | E  | R  | T  | Y  |     | U  | I  | O  | P  | [  | ]  |BKSP|
   * |----------------------------------|     |----------------------------------|
   * |LSFT| A  | S  | D  | F  | G  | H  |     | J  | K  | L  | ;  | '' | UP |ENTR|
   * |----------------------------------|     |----------------------------------|
   * |CTRL| Z  | X  | C  | V  | B  | N  |     | M  | ,  | .  | /  |LEFT|DOWN|RGHT|
   * '----------------------------------'     '----------------------------------'
   *  \                   ____ ____    /       \    ____ ____                   /
   *   \                 |CMD |ALT |  /         \  | FN |SPCE|                 /
   *    \                `----'----' /           \ `----'----'                /
   *     \__________________________/             \__________________________/
   *
   * MESC - Hold is Macro Layer,  Press is ESC
   * FN + CTRL to turn Caps Lock On and Off
   * CTRL - sould be a tap dance, like two consecutive taps to toggle it ON/OFF
   * or may be i should to the LSFT to toggle, lets see what is more practical
   * FN + '' - jump to layer 2
   * LSFT - SHIFT when held, TAB when tapped
   */
  [_QWERTY] = KEYMAP(
      MESC, Q, W, E, R, T, Y,                   U, I, O, P, LBRC, RBRC, BSPC,
      SWT, A, S, D, F, G, H,                    J, K, L, SCLN, QUOT, UP, ENT,
      TD_CTRLCAPS, Z, X, C, V, B, N,            M, COMM, DOT, SLSH, LEFT, DOWN, RIGHT,
                LGUI, LALT,                            MO, SPC),
    


  /*  MO(1): Function Layer, activates by FN
   * ,----------------------------------.     ,----------------------------------.
   * |    | !  | @  | #  | $  | %  | ^  |     |    | 7  | 8  | 9  |MPrv| PP |MFwd|
   * |----------------------------------|     |----------------------------------|
   * |TAB | &  | *  | (  | )  | -  | =  |     |    | 4  | 5  | 6  | L2 |PgUP| V+ |
   * |----------------------------------|     |----------------------------------|
   * |CAPS| `  | ~  | \  | |  | _  | +  |     | 0  | 1  | 2  | 3  | L0 |PgDw| V- |
   * '----------------------------------'     '----------------------------------'
   *  \                   ____ ____    /       \    ____ ____                   /
   *   \                 |    |    |  /         \  | X  |    |                 /
   *    \                `----'----' /           \ `----'----'                /
   *     \__________________________/             \__________________________/
   *
   * X - already pressed on layer 0 or layer 2
   * when on layer 0: FN + L2 - jump to layer 2
   * when on layer 2: FN + L0 - jump to layer 0
   */
  [_FUNCTION] = KEYMAP(
    TRNS, EXLM, AT, HASH, DLR, PERC, CIRC,       TRNS, 7, 8, 9, MRWD, MPLY, MFFD,
    TAB, AMPR, ASTR, LPRN, RPRN, MINS, EQL,      TRNS, 4, 5, 6, TO2, PGUP, _VOLUP,
    CAPS, GRV, TILDE, BSLS, PIPE, UNDS, PLUS,       0, 1, 2, 3, TO0, PGDN, _VOLDOWN,
                          TRNS, TRNS,                  TRNS, TRNS),



  /* Layer 2: F Row, activates by pressing FN + L2
   * ,----------------------------------.     ,----------------------------------.
   * | ~ `| 1  | 2  | 3  | 4  | 5  | 6  |     | 7  | 8  | 9  | 0  | -  | =  |    |
   * |----------------------------------|     |----------------------------------|
   * |    | F1 | F2 | F3 | F4 | F5 | F6 |     | F7 | F8 | F9 | F10| F11| F12|    |
   * |----------------------------------|     |----------------------------------|
   * |    |    |    |    |    |    |    |     |    |    |    |    | L0 |    |    |
   * '----------------------------------'     '----------------------------------'
   *  \                   ____ ____    /       \    ____ ____                   /
   *   \                 |    |    |  /         \  | FN |    |                 /
   *    \                `----'----' /           \ `----'----'                /
   *     \__________________________/             \__________________________/
   *
   * FN + L0 - jump to layer 0
   */
  [_FROW] = KEYMAP(
      GRV, 1, 2, 3, 4, 5, 6,                       7, 8, 9, 0, MINS, EQL, TRNS,
      TRNS, F1, F2, F3, F4, F5, F6,                F7, F8, F9, F10, F11, F12, TRNS,
      TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,    TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, 
                              TRNS, TRNS,                MO, TRNS),


  /* Layer 3: Macro Layer, activates by holding MESC
   * ,----------------------------------.     ,----------------------------------.
   * | X  | EML| PSW|    |    |    |    |     |    |    |    |    |    |    |    |
   * |----------------------------------|     |----------------------------------|
   * |    |    |    |    |    |    |    |     |    |    |    |    |    |    |    |
   * |----------------------------------|     |----------------------------------|
   * |    |    |    |    |    |    |    |     |    |    |    |    |    |    |    |
   * '----------------------------------'     '----------------------------------'
   *  \                   ____ ____    /       \    ____ ____                   /
   *   \                 |    |    |  /         \  |    |    |                 /
   *    \                `----'----' /           \ `----'----'                /
   *     \__________________________/             \__________________________/
   *
   * MESC + EML = email insertion
   * MESC + PSW = pass insertion
   */
  [_MACROS] = KEYMAP(
      TRNS, EML, PSW, TRNS, TRNS, TRNS, TRNS,     TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,
      TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,   TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,
      TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,   TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,
                              TRNS, TRNS,               TRNS, TRNS),
};




//_MACROS
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    case KC_EML:
      if (record->event.pressed) {
        SEND_STRING("myemail@gmail.com"); //change before compile
      }
    return false;
    break;

    case KC_PSW:
      if (record->event.pressed) {
        SEND_STRING("mychar"); //change before compile
      }
    return false;
    break;
  }
  return true;
};


//Tap twice the LCTRL to toggle CAPS LOCK ON/OFF and once for LCTRL (not sure about that)
qk_tap_dance_action_t tap_dance_actions[] = {

  [TD_LCTRL_CAPS]  = ACTION_TAP_DANCE_DOUBLE(KC_LCTL, KC_CAPS)

};



//Receiver LED colors on layer changes
void matrix_scan_user(void) {
    uint8_t layer = biton32(layer_state);
    
    switch (layer) {
      case _QWERTY:
        set_led_green;
        break;
      case _FUNCTION:
        set_led_blue;
        break;
      case _FROW:
        set_led_white;
        break;
      case _MACROS:
        set_led_red;
        break;
      default:
        set_led_green;
        break;
    }
};


/* Other possible receiver LED colors
  set_led_magenta;
  set_led_cyan;
*/

/* For Copy&Paste
   * ,----------------------------------.     ,----------------------------------.
   * |    |    |    |    |    |    |    |     |    |    |    |    |    |    |    |
   * |----------------------------------|     |----------------------------------|
   * |    |    |    |    |    |    |    |     |    |    |    |    |    |    |    |
   * |----------------------------------|     |----------------------------------|
   * |    |    |    |    |    |    |    |     |    |    |    |    |    |    |    |
   * '----------------------------------'     '----------------------------------'
   *  \                   ____ ____    /       \    ____ ____                   /
   *   \                 |    |    |  /         \  |    |    |                 /
   *    \                `----'----' /           \ `----'----'                /
   *     \__________________________/             \__________________________/
   *
   */

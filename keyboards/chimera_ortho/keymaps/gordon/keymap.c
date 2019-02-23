// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

#include QMK_KEYBOARD_H
#include "version.h"
#include "gordon.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

#define CALTDEL LCTL(LALT(KC_DEL))
#define TSKMGR LCTL(LSFT(KC_ESC))

#define KC_SNAPLEFT LGUI(KC_LEFT)
#define KC_SNAPRIGHT LGUI(KC_RIGHT)
#define KC_SNAPUP LGUI(KC_UP)
#define KC_SNAPDOWN LGUI(KC_DOWN)
#define KC_PREVTAB LCTL(LSFT(KC_TAB))
#define KC_NEXTTAB LCTL(KC_TAB)
#define KC_WORKRIGHT LCTL(LGUI(KC_RIGHT))
#define KC_WORKLEFT LCTL(LGUI(KC_LEFT))

#define KC_NMPD TG(_NUMPAD)
#define KC_SYMB TG(_SYMBOLS)

#define KC_SCTL MT(MOD_LCTL, KC_LBRC)
#define KC_SCTR MT(MOD_LCTL, KC_RBRC)
#define KC_SPLT MT(MOD_LALT, KC_MINS)
#define KC_SPRT MT(MOD_LALT, KC_1)
#define KC_GBRC MT(MOD_RGUI, KC_8)
#define KC_GQOT MT(MOD_LGUI, KC_QUOT)
#define KC_CSHW MT(MOD_LCTL|MOD_LSFT,KC_W)

#define KC_CDEL LCTL(KC_DEL)
#define KC_AUDUP KC_AUDIO_VOL_UP
#define KC_AUDOWN KC_AUDIO_VOL_DOWN


#define KC_MEHS MEH_T(KC_S)
#define KC_MEHL MEH_T(KC_L)
#define KC_GWIN GUI_T(KC_G)
#define KC_FCTL CTL_T(KC_F)
#define KC_JCTL CTL_T(KC_J)
#define KC_ZCTL CTL_T(KC_Z)
#define KC_ALTV ALT_T(KC_V)
#define KC_ALTN ALT_T(KC_N)
#define KC_MEHX ALL_T(KC_X)
#define KC_RESET RESET

//LTs
#define KC_MESC LT(_MACROS, KC_ESC)
#define KC_DNUM LT(_NUMPAD, KC_D)
#define KC_SPFN LT(_NAV,KC_EQL)
#define KC_EMAUS LT(_MOUSE,KC_E)
#define KC_ENAV LT(_NAV,KC_E)
#define KC_INAV LT(_TEXTNAV,KC_I)
#define KC_BSPSYM LT(_SYMBOLS,KC_BSPACE)
#define KC_ENTSYM LT(_SYMBOLS,KC_ENTER)
#define KC_CLNMAUS LT(_MOUSE,KC_SCOLON)

#define KC_FUNC TT(_FUNCTION)

//TAP DANCE
#define KC_F6F7 TD(F6F7)
#define KC_ALF4 TD(ALTF4)
#define KC_TTT TD(TTT)
#define KC_ENHM TD(HOME_END)
#define KC_CLPS TD(CALC_PRINTSCREEN)


#define KC_INCL M(0)
#define KC_PULL M(1)
#define KC_PUSH M(2)
#define KC_SCAP M(3)
#define KC_SCOF M(4)
#define KC_CAD LALT(LCTL(KC_DEL))

#define LONGPRESS_DELAY 150
//#define LAYER_TOGGLE_DELAY 300

// Fillers to make layering more clear
#define KC_ KC_TRNS

/* TODO:
 *
 * DONE: RESET and CAD into macro layer.
 * DONE: WINUP AND WINDOWN in NAV layer
 * DONE: Get rid of caps layer. not sure what it is even for.
 * DONE: LMEH
 * DONE: plus, divide, multiply on left hand for num layer
 * DONE: F1 - F12 on a layer toggle (not a temp toggle but a one shot or something)
 * DONE: Volume, page up and down for mouse layer.
 * DONE: Add full user files - without using anything.
 * DONE: Insert, ctrl delete
 * DONE: Home and End
 * DONE: Printscreen

 * Easier way to open new terminal (instead of alt + F2)
 * Intellij/text navigation layer (ctrl delete could be here).
 * Macro for "System.exit(0)" probably macro layer and "c"
 * Some sort of tap dance for comma, H, right pinky, and possibly other corners.
 * Something more with the right hand. not sure what.
 * Mouse: Left scroll, right scroll
 * Passwords and any other macros.
 * LED for control
 * All modifiers reset
 * Russain layer
 * Hebrew layer
 * Get rid of stupid git pull and push macros.
 *
*/

//Tap dance enums
enum {
  F12ETAPS = 0,
  CALCCOMP,
  ALTF4,
  F6F7,
  TTT,
  HOME_END,
  CALC_PRINTSCREEN
};

static xtap ttt_state = {
  .is_press_action = true,
  .state = 0
};


//Already exists in gordon.c, shouldn't need this anymore
/*// To activate SINGLE_HOLD, you will need to hold for 200ms first.
// This tap dance favors keys that are used frequently in typing like 'f'
int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted) {
      return SINGLE_TAP;
    }
    else {
      if (!state->pressed) return SINGLE_TAP;
      else return SINGLE_HOLD;
    }
  }
  //If count = 2, and it has been interrupted - assume that user is trying to type the letter associated
  //with single tap.
  else if (state->count == 2) {
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  else if ((state->count == 3) && ((state->interrupted) || (!state->pressed))) return TRIPLE_TAP;
  else if (state->count == 3) return TRIPLE_HOLD;
  else return 8; //magic number. At some point this method will expand to work for more presses
}*/

/* "Super tap toggle"
 * Basically, TT but for two or more layers for a single key.
 * This particular dance:
 * Single tap/hold - TT for Function layer
 * Double tap/hold - TT for Numpad layer
 * Triple tap/hold - TT for Mouse layer
 *
*/
void TTT_finished (qk_tap_dance_state_t *state, void *user_data) {
  ttt_state.state = cur_dance(state);
  switch (ttt_state.state) {
    case SINGLE_TAP: layer_invert(_FUNCTION); break;
    case SINGLE_HOLD: layer_on(_FUNCTION); break;
    case DOUBLE_TAP: layer_invert(_NUMPAD); break;
    case DOUBLE_HOLD: layer_on(_NUMPAD); break;
    case DOUBLE_SINGLE_TAP: layer_invert(_NUMPAD); break;
    case TRIPLE_TAP: layer_invert(_MOUSE); break;
    case TRIPLE_HOLD: layer_on(_MOUSE); break;
  }
}

void TTT_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (ttt_state.state) {
    case SINGLE_TAP: break;
    case SINGLE_HOLD: layer_off(_FUNCTION); break;
    case DOUBLE_TAP:  break;
    case DOUBLE_HOLD: layer_off(_NUMPAD); break;
    case DOUBLE_SINGLE_TAP:  break;
    case TRIPLE_TAP:  break;
    case TRIPLE_HOLD: layer_off(_MOUSE); break;
  }
  ttt_state.state = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {
  // simple tap dance
  [F12ETAPS] = ACTION_TAP_DANCE_DOUBLE(KC_F12,LSFT(LCTL(KC_F10))),
  [CALCCOMP] = ACTION_TAP_DANCE_DOUBLE(KC_CALCULATOR, KC_MY_COMPUTER),
  [CALC_PRINTSCREEN] = ACTION_TAP_DANCE_DOUBLE(KC_CALCULATOR, KC_PSCR),
  [ALTF4] = ACTION_TAP_DANCE_DOUBLE(KC_F4,LALT(KC_F4)),
  [F6F7] = ACTION_TAP_DANCE_DOUBLE(LSFT(KC_F6), LALT(KC_F7)),
  [HOME_END] = ACTION_TAP_DANCE_DOUBLE(KC_END, KC_HOME),
  [TTT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL,TTT_finished, TTT_reset),
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_kc(
  //,----+----+----+----+----+----+----.      ,----+----+----+----+----+----+----.
     MESC, Q  ,CSHW,ENAV, R  , T  ,SPC ,       CLPS, Y  , U  ,INAV, O  , P  ,TTT,
  //|----+----+----+----+----+----+----|      |----+----+----+----+----+----+----|
     TAB , A , MEHS,DNUM,FCTL,GWIN,GRAVE,      TILD, H  ,JCTL, K ,MEHL,CLNMAUS,ENHM,
  //|----+----+----+----+----+----+----|      |----+----+----+----+----+----+----|
    MINUS,ZCTL,MEHX, C  ,ALTV, B  ,DELETE,     INS ,ALTN, M  ,COMM,DOT ,SLSH,UNDS,
  //|----+----+----+----+----+----+----|      |----+----+----+----+----+----+----|
                         LSHIFT,BSPSYM,                SPC ,ENTSYM
  // \------------------+----+----+---/       \---+----+----+-------------------/
  ),

  [_NUMPAD] = LAYOUT_kc(
  //,----+----+----+----+----+----+----.     ,----+----+----+----+----+----+----.
         ,    ,    ,    ,ASTR,    ,    ,          ,    , 7  , 8  , 9  ,ASTR,/**/,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
         ,MINS,PLUS,/**/,EQUAL,    ,   ,          ,    , 4  , 5  , 6  ,PLUS,    ,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
         ,    ,    ,    ,SLSH,    ,    ,          ,    , 1  , 2  , 3  ,SLSH,    ,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
                             ,    ,                     , 0
  // \------------------+----+----+---/       \---+----+----+-------------------/
  ),

  [_SYMBOLS] = LAYOUT_kc(
  //,----+----+-----+----+----+----+----.     ,----+----+----+----+----+----+----.
         ,EXLM, AT  ,LCBR,RCBR,HASH,    ,          ,CIRC,AMPR,ASTR,LPRN,RPRN,/**/,
  //|----+----+-----+----+----+----+----|     |----+----+----+----+----+----+----|
         ,EXLM,EXLM,LPRN,RPRN ,    ,    ,          ,    ,DQUO,EQUAL,QUOTE,RCBR,    ,
  //|----+----+----+----+----+----+----|      |----+----+----+----+----+----+----|
      ,DOLLAR, PERC,LBRACKET,RBRACKET, ,      ,    ,PIPE,BSLASH,PLUS,  ,  ,  ,
  //|----+----+-----+----+----+----+----|     |----+----+----+----+----+----+----|
                          UNDS,/**/,                    ,/**/
  // \-------------------+----+----+---/       \---+----+----+-------------------/
  ),

  [_FUNCTION] = LAYOUT_kc(
  //,----+----+----+----+----+----+----.     ,----+----+----+----+----+----+----.
    F6F7 ,F1  ,F2  ,F3  ,ALF4,F5  ,F6  ,      F7  ,F8  ,F9  ,F10 ,F11 ,F12 ,/**/,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,          ,    ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,          ,    ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
                             ,    ,                    ,
  // \------------------+----+----+---/       \---+----+----+-------------------/
  ),

  [_NAV] = LAYOUT_kc(
  //,----+----+----+----+----+----+----.     ,----+----+----+----+----+----+----.
      ,   ,SNAPLEFT,/**/,SNAPRIGHT,,  ,           ,    ,    , UP ,    ,    ,    ,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
     ,SNAPUP,PREVTAB, ,NEXTTAB,SNAPDOWN,,   ,    ,LEFT,DOWN,RGHT,    ,    ,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
    ,    ,WORKLEFT,    ,WORKRIGHT,,    ,          ,    ,PGUP,PGDN,    ,    ,    ,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
                            CDEL ,DEL,                 ,
  // \------------------+----+----+---/       \---+----+----+-------------------/
  ),

  [_TEXTNAV] = LAYOUT_kc(
  //,----+----+----+----+----+----+----.     ,----+----+----+----+----+----+----.
         ,   ,    ,    ,    ,    ,  ,             ,    ,    ,/**/,    ,    ,    ,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,          ,    ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,          ,    ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
                                 ,    ,                 ,
  // \------------------+----+----+---/       \---+----+----+-------------------/
  ),

   [_MOUSE] = LAYOUT_kc(
  //,----+----+----+----+----+----+----.     ,----+----+----+----+----+----+----.
         ,    ,    ,MS_UP,   ,   ,    ,      ,    ,    , UP ,    ,    ,    ,/**/
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
      ,   ,MS_LEFT,MS_DOWN,MS_RIGHT,   ,    ,     ,    ,LEFT,DOWN,RGHT,/**/,    ,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,          ,    ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
                      ,MS_BTN1 ,MS_BTN2              ,
  // \------------------+----+----+---/       \---+----+----+-------------------/
  ),


  [_MACROS] = LAYOUT_kc(
  //,----+----+----+----+----+----+----.     ,----+----+----+----+----+----+----.
    /**/,RESET,SECRET_2,SECRET_3,   ,   ,   ,SYSTEM_SLEEP,    ,    ,INCL,    ,    ,    ,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
     CAD ,SECRET_1,    ,   ,   ,   ,   ,      ,    ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
     SCAP,    ,    ,    ,    ,    ,    ,          ,    ,    ,    ,    ,    ,SCAP,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
                             ,    ,                    ,
  // \------------------+----+----+---/       \---+----+----+-------------------/
  )

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  switch(id) {
    /* include some kind of library or header */
    case 0:
      if (record->event.pressed) {
        SEND_STRING("#include <>");
        return MACRO( T(LEFT), END);
      }
      break;
    case 1:
      if (record->event.pressed) {
        SEND_STRING("git pull");
        return MACRO( T(ENT), END );
      }
      break;
    case 2:
      if (record->event.pressed){
        SEND_STRING("git push");
        return MACRO( T(ENT), END );
      }
      break;
    case 3:
      if (record->event.pressed){
        // layer_on(_CAPS);
        // register_code(KC_CAPSLOCK);
        // unregister_code(KC_CAPSLOCK);
      }
      break;
    case 4:
      if (record->event.pressed){
        // layer_off(_CAPS);
        // register_code(KC_CAPSLOCK);
        // unregister_code(KC_CAPSLOCK);
      }
      break;
  }
  return MACRO_NONE;
};


void matrix_scan_user(void) {
    uint8_t layer = biton32(layer_state);

    switch (layer) {
      case _QWERTY:
        set_led_green;
        break;
      case _MOUSE:
        set_led_yellow;
        break;
      case _NUMPAD:
        set_led_blue;
        break;
      case _SYMBOLS:
        set_led_red;
        break;
      case _NAV:
        set_led_magenta;
        break;
      case _MACROS:
        set_led_green;
        _delay_ms(45);
        set_led_red;
        _delay_ms(45);
        break;
      case _FUNCTION:
        set_led_green;
        _delay_ms(45);
        set_led_blue;
        _delay_ms(45);
        break;
      default:
        set_led_green;
        break;
    }
};

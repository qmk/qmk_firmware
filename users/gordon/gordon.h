#ifndef GORDON
#define GORDON

#include "quantum.h"
#include "process_keycode/process_tap_dance.h"


// Fillers to make layering more clear
#define _______ KC_TRNS
#define ________ KC_TRNS
#define _________ KC_TRNS
#define XXXXXXX KC_NO

// KC codes that are too long
#define DOLLAR KC_DOLLAR
#define LSQUIGLY KC_LBRACKET
#define RSQUIGLY KC_RBRACKET
#define NUMLOCK KC_NUMLOCK
#define CAPLOCK KC_CAPSLOCK
#define BK_SLASH KC_BSLASH
#define ASTERSK KC_KP_ASTERISK
 
// Navigation
#define SNAPLEFT  LGUI(KC_LEFT)
#define SNAPRGHT  LGUI(KC_RIGHT)
#define SNAPUP    LGUI(KC_UP)
#define SNAPDOWN  LGUI(KC_DOWN)
#define PREVTAB   LCTL(LSFT(KC_TAB))
#define NEXTTAB   LCTL(KC_TAB)
#define WORKRIGHT LCTL(LGUI(KC_RIGHT))
#define WORKLEFT  LCTL(LGUI(KC_LEFT))

// KC/modifier hold
#define CTRL_F   CTL_T(KC_F)
#define CTRL_J   CTL_T(KC_J)
#define CTRL_Z   CTL_T(KC_Z)
#define ALT_V    ALT_T(KC_V)
#define ALT_M    ALT_T(KC_M)
#define WIN_G    GUI_T(KC_G)
#define WIN_H    GUI_T(KC_H)
#define HYPER_X  ALL_T(KC_X)
#define HYPE_DOT ALL_T(KC_DOT)
#define MEH_S    MEH_T(KC_S)
#define MEH_L    MEH_T(KC_L)
#define ALT_HOME ALT_T(KC_HOME)


// KC/Layer Hold
#define NAV_E    LT(_NAV,KC_E)
#define NUMPAD_D LT(_NUMPAD,KC_D)
#define MOUSE_C  LT(_MOUSE,KC_C)
#define SYMB_BSP LT(_SYMBOLS,KC_BSPACE)
#define COL_MOUS LT(_MOUSE,KC_SCOLON)
#define SPAC_SYM LT(_SYMBOLS,KC_SPACE)

// Double Modifier ONLY hold
#define ALT_SHFT LSFT(KC_LALT)
#define CTR_SHFT LSFT(KC_LCTL)

// KC/Double modifier Hold
#define CTR_SH_W MT(MOD_LCTL|MOD_LSFT,KC_W)
#define CTR_AL_R MT(MOD_LCTL|MOD_LALT,KC_R)

//MISC
#define PRINTSCR KC_PSCREEN
#define CALTDEL LCTL(LALT(KC_DEL))
#define TSKMGR LCTL(LSFT(KC_ESC))


typedef struct {
  bool is_press_action;
  int state;
} xtap;

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  DOUBLE_SINGLE_TAP = 5, //send two single taps
  TRIPLE_TAP = 6,
  TRIPLE_HOLD = 7
};

enum gordon_layers
{
  _QWERTY = 0,
  _SYMBOLS,
  _MOUSE,
  _NUMPAD,
  _NAV,
  _MACROS,
  _FUNCTION,
  _TEXTNAV
};



void register_hyper (void);
void unregister_hyper (void);

void register_ctrl_a (void); 
void unregister_ctrl_a (void); 

void register_alt_f7 (void); 
void unregister_alt_f7 (void);

void register_shift_f6 (void); 
void unregister_shift_f6 (void); 

void register_ctrl_shift (void); 
void unregister_ctrl_shift (void); 

void register_alt_shift (void); 
void unregister_alt_shift (void);

int cur_dance (qk_tap_dance_state_t *state); 
int hold_cur_dance (qk_tap_dance_state_t *state); 

void x_finished (qk_tap_dance_state_t *state, void *user_data);
void x_reset (qk_tap_dance_state_t *state, void *user_data);

void h_finished (qk_tap_dance_state_t *state, void *user_data);
void h_reset (qk_tap_dance_state_t *state, void *user_data);

void tab_finished (qk_tap_dance_state_t *state, void *user_data);
void tab_reset (qk_tap_dance_state_t *state, void *user_data);

void comma_finished (qk_tap_dance_state_t *state, void *user_data);
void comma_reset (qk_tap_dance_state_t *state, void *user_data);

void bt_finished (qk_tap_dance_state_t *state, void *user_data);
void bt_reset (qk_tap_dance_state_t *state, void *user_data);

// Macro Declarations
enum {
  INFOQM,
  TIL_SLASH,
  DEREF,
  EQRIGHT,
  TILD3,
  TICK3,
  ALTTAB_START,
  ALTTAB_END
};

enum secret_strings {
  KC_SECRET_1 = SAFE_RANGE,
  KC_SECRET_2,
  KC_SECRET_3,
  KC_SECRET_4,
  KC_SECRET_5,
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt);

#endif
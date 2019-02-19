#ifndef GORDON
#define GORDON

#include "quantum.h"
#include "process_keycode/process_tap_dance.h"


// Fillers to make layering more clear
#define ________  KC_TRNS
#define _________ KC_TRNS
#define _XXXXXX_  KC_TRNS

// KC codes that are too long
#define DOLLAR    KC_DOLLAR
#define LSQUIGLY  KC_LBRACKET
#define RSQUIGLY  KC_RBRACKET
#define NUMLOCK   KC_NUMLOCK
#define CAPLOCK   KC_CAPSLOCK
#define BK_SLASH  KC_BSLASH
#define ASTERSK   KC_KP_ASTERISK

// Navigation
#define SNAPLEFT  LGUI(KC_LEFT)
#define SNAPRGHT  LGUI(KC_RIGHT)
#define SNAPUP    LGUI(KC_UP)
#define SNAPDOWN  LGUI(KC_DOWN)
#define PREVTAB   LCTL(LSFT(KC_TAB))
#define NEXTTAB   LCTL(KC_TAB)
#define WORKRIGHT LCTL(LGUI(KC_RIGHT))
#define WORKLEFT  LCTL(LGUI(KC_LEFT))

#define APP_1     LCTL(LGUI(KC_1))
#define APP_2     LCTL(LGUI(KC_2))
#define APP_3     LCTL(LGUI(KC_3))
#define APP_4     LCTL(LGUI(KC_4))
#define APP_5     LCTL(LGUI(KC_5))
#define APP_6     LCTL(LGUI(KC_6))
#define APP_7     LCTL(LGUI(KC_7))
#define APP_8     LCTL(LGUI(KC_8))

// KC/modifier hold
#define CTRL_F    CTL_T(KC_F)
#define CTRL_J    CTL_T(KC_J)
#define CTRL_Z    CTL_T(KC_Z)
#define ALT_V     ALT_T(KC_V)
#define ALT_M     ALT_T(KC_M)
#define WIN_G     GUI_T(KC_G)
#define WIN_H     GUI_T(KC_H)
#define HYPER_X   ALL_T(KC_X)
#define HYPE_DOT  ALL_T(KC_DOT)
#define MEH_S     MEH_T(KC_S)
#define MEH_L     MEH_T(KC_L)
#define ALT_HOME  ALT_T(KC_HOME)


// KC/Layer Hold
#define NAV_E    LT(_NAV,KC_E)
#define NUMPAD_D LT(_NUMPAD,KC_D)
#define MOUSE_C  LT(_MOUSE,KC_C)
#define SYMB_BSP LT(_SYMBOLS,KC_BSPACE)
#define COL_MOUS LT(_MOUSE,KC_SCOLON)
#define SPAC_SYM LT(_SYMBOLS,KC_SPACE)
#define SPAC_TXT LT(_TEXTNAV,KC_SPACE)

#define APP_SW_I LT(_APPSWITCH,KC_I)
#define APP_SW_K LT(_APPSWITCH,KC_K)

// #define TLSLSH   TIL_SLASH
// #define TILDA_3x TILD3
// #define _RESET_  UP_ENTER_RESET


// Double Modifier ONLY hold
#define ALT_SHFT LSFT(KC_LALT)
#define CTR_SHFT LSFT(KC_LCTL)

// KC/Double modifier Hold
#define CTR_SH_W MT(MOD_LCTL|MOD_LSFT,KC_W)
#define CTR_AL_R MT(MOD_LCTL|MOD_LALT,KC_R)
#define ALT_SH_R MT(MOD_LSFT|MOD_LALT,KC_R)

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

//Tap dance enums
enum
{
  F12TAP = 0,
  F12ETAPS,
  CALCCOMP,
  REFRESH, //send R, or Control+R if double tapped.
  ENDESC,
  XESC, //'quad function'. x, control, escape, alt
  ALY2, //'quad function': a, Hyper, ctrl+a, layer 2
  PRLOCK,
  F6F7, // Shift F6 or Alt F7
  TABCOMBO,
  FCTRL,
  F3D,
  ALTF4,
  COMMA,
  AT,
  HTAB,
  F1F13,
  F2F14,
  F5F15,
  ENDHOME,
  Q_ESCAPE
};

#ifdef TAP_DANCE_ENABLE
#define F1_F13      TD(F1F13)
#define F2_F14      TD(F2F14)
#define F5_F15      TD(F5F15)
#define F4_ALTF4    TD(ALTF4)
#define END_ESC     TD(ENDESC)
#define Q_ESC       TD(Q_ESCAPE)
#define END_HOME    TD(ENDHOME)
#define SHF6_AF7    TD(F6F7)
#define F12_RUN     TD(F12ETAPS)
#define COMMA_TD    TD(COMMA)
#define CALC_COM    TD(CALCCOMP)
#else //just to make things compile
#define F1_F13      KC_1
#define F2_F14      KC_1
#define F5_F15      KC_1
#define F4_ALTF4    KC_1
#define END_ESC     KC_1
#define END_HOME    KC_1
#define SHF6_AF7    KC_1
#define F12_RUN     KC_1
#define COMMA_TD    KC_1
#define CALC_COM    KC_1
#endif

enum gordon_layers
{
  _QWERTY = 0,
  _SYMBOLS,         // Programming and all other commonlye used symbols
  _MOUSE,           // Mouse movement and also a few macros
  _NUMPAD,          // For getting a numpad under the right hand, and a few helpful things under the left
  _NAV,             // Windows navigation. Windows snapping, changing workspaces, and ARROWS
  _MACROS,          // Non-text related Macros.
  _FUNCTION,        // Not sure what I had in mind for this one
  _APPSWITCH,       // For switching between apps using the `ctrl + Win + [num]` shortcut.
                    // This allows for toggling windows of the same app with one button.
                    // Example: Press and hold `I`, then tap `j` multiple times to cycle through all
                    // Intellij windows (and only Intellij). This requires the app to be pinned to the Windows bar
  _ONESHOT,         // A layer I use for shortcuts that require multiple modifiers and a button not on my home layer
                    // Example: If I need to hit `alt + shift + 5`
  _TEXTNAV,         // Navigate through text
  _QWERTY_KIDS,     // So my kids can do nothing but type. Could also be a `speed typing` layer with no LT or MTs
  _STREET_FIGHTER,  // For Street Fighter 5. Die 1000x Deaths!!!!
  _DIRNAV,          // For navigating to different directories.
  _TEXT_MACROS      // For text-manipulation macros. Passwords, saved strings, pre-formatting
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

enum secret_strings {
  KC_SECRET_1 = SAFE_RANGE,
  KC_SECRET_2,
  KC_SECRET_3,
  KC_SECRET_4,
  KC_SECRET_5,
  END_SECRET_SAFE_RANGE
};


// Macro Declarations
enum {
  INFOQM = END_SECRET_SAFE_RANGE,
  MODRESET,
  TIL_SLASH,
  DEREF,
  EQRIGHT,
  TILD3,
  TICK3,
  SPRK_TCK,
  ALTTAB_START,
  ALTTAB_END,
  UP_ENTER_RESET,
  DBMS_OUT,
  DIE_1000X_RIGHT,
  DIE_1000X_LEFT,
  ID_MAN_IP
};



const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt);

#endif

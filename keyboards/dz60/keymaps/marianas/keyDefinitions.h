
//Control
#define MO_FNLR MO(FN_LAYER)
#define BACKSPC KC_BSPC
#define ENTER_OR_SQL LT(SQLMACROS,KC_ENT)
#define ESCAP KC_ESC
#define PSCR KC_PSCR
#define SCRL KC_SCRL
#define PAUS KC_PAUSE
#define NSRT KC_INSERT
#define HOME KC_HOME
#define PGUP KC_PGUP
#define PGDN KC_PGDN
#define END_ KC_END
#define DEL  KC_DELETE
#define UPUP KC_UP
#define D_WN KC_DOWN
#define LEFT KC_LEFT
#define RGHT KC_RIGHT

//KEYPAD
#define KP_1 KC_KP_1
#define KP_2 KC_KP_2
#define KP_3 KC_KP_3
#define KP_4 KC_KP_4
#define KP_5 KC_KP_5
#define KP_6 KC_KP_6
#define KP_7 KC_KP_7
#define KP_8 KC_KP_8
#define KP_9 KC_KP_9
#define KP_0 KC_KP_0
#define NMLK KC_NUM_LOCK
#define STAR KC_KP_ASTERISK
#define KSSH KC_KP_SLASH
#define KMIN KC_KP_MINUS
#define PLUS KC_KP_PLUS
#define KNTR KC_KP_ENTER
#define KDOT KC_KP_DOT

//Modifiers
#define CTLL KC_LCTL
#define LEFTSHFT SC_LSPO
#define WINL KC_LGUI
#define ALTL KC_LALT
#define CTLR KC_RCTL
#define RIGHT_SHIFT__PAREN SC_RSPC
#define WINR KC_RGUI
#define ALTR KC_RALT
#define APPR KC_APP


//Punctuation
#define CMMA KC_COMM
#define PRRD KC_DOT
#define SLSH KC_SLSH
#define QUOT KC_QUOT
#define COLN KC_SCLN
#define LBRC KC_LBRC
#define RBRC KC_RBRC
#define EQUL KC_EQL
#define MNUS KC_MINS
#define BSLASH KC_BSLS

//Layers
#define QWRTY TO(QWERTY)
#define NAVS TO(NAV_CLUSTER)
#define GAME TO(GAMING)

//Space
#define ____ KC_TRNS
#define _____ KC_TRNS
#define ______ KC_TRNS
#define ________ KC_TRNS
#define ___________ KC_TRNS
#define _________________ KC_TRNS
#define SPAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAACE KC_SPC
#define KCNO KC_NO

enum sql_macros {
  S_LFTJN = SAFE_RANGE, // L
  S_INRJN, // I
  S_SLCT,  // S
  S_FROM,  // F
  S_DSNCT, // D
  S_ORDER, // O
  S_WHERE, // W
  S_ALTER, // Esc
  S_ASTRK, // *

  TD_A,
  TD_B,
  TD_C, // Corp, Corporation, Company
  TD_D, // Distribution, Dist, Distributor
  TD_E,
  TD_F,
  TD_G, // GlobalLookup
  TD_H,
  TD_I, // Instance, Item
  TD_J,
  TD_K,
  TD_L,
  TD_M,
  TD_N, // NadRate
  TD_O,
  TD_P, // Product, Person,
  TD_Q, // Darden
  TD_R,
  TD_S, // Supplier, Step
  TD_T, // Task, Type
  TD_U,
  TD_V,
  TD_W, // Workflow,
  TD_X,
  TD_Y,
  TD_Z,
  TD_BSPC,
  TD_ENT,
  TD_ESC,

  FN_QT
};

bool isShifted(void);

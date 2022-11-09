#pragma once

#include "quantum.h"

// LAYERS
// ======

#define BASE             0 // base dvorak layer
#define KEYNAV           1 // arrow navigation (right hand)
#define KEYSEL           2 // arrow navigation + shift (allow text selection)
#define SHELL_NAV        3 // bash shortcuts
#define SHELL_SCREEN     4 // linux screen shortcuts
#define BROWSER_CONTROL  5 // control browser and mouse
#define COMBINED         6 // combined numbers and symbols layer
#define ANDROID_STUDIO   7 // android studio specific layer
#define VSCODE           8 // visual studio code specific layer
#define SHORTCUTS        9 // shortcuts to be intercepted by autohotkey
#define RGB_CONTROL      10 // control RGB effects

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD,
  
  // shell nav macros
  SHELL_LS,
  SHELL_LSLTR,
  SHELL_LSLA,
  SHELL_CDPRE,
  SHELL_LESS,
  SHELL_PLESS,
  SHELL_PGREP,
  SHELL_TAILF,

  SHELL_SCREENRD,
  SHELL_SCREEN_NEW,
  SHELL_SCREEN_LIST,

  SHELL_GIT_DIFF,
  SHELL_GIT_STATUS,

  // linux screen macros
  SCREEN_TAB_LEFT,
  SCREEN_TAB_RIGHT,

  SCREEN_NEW_TAB,
  SCREEN_DETACH,
  SCREEN_RENAME,
  SCREEN_NUMBER,
  SCREEN_KILL,

  SCREEN_0,
  SCREEN_1,
  SCREEN_2,
  SCREEN_3,
  SCREEN_4,
  SCREEN_5,
  SCREEN_6,
  SCREEN_7,
  SCREEN_8,
  SCREEN_9,

  SCREEN_COPY_MODE,
  SCREEN_PASTE,

  SCREEN_READREG_1,
  SCREEN_READREG_2,
  SCREEN_READREG_3,
  SCREEN_PASTEREG_1,
  SCREEN_PASTEREG_2,
  SCREEN_PASTEREG_3,

  // Windows 10 macros
  WINDOWS10_WORKSPACE_LEFT,
  WINDOWS10_WORKSPACE_RIGHT,
  WINDOWS10_TASK_VIEW,

};






// Notepad++ shortcuts
// ===================
#define NP_DUPE_LINE LCTL(KC_D)

// ChromeOS shortcuts
// ==================
#define CO_WS_LEFT RGUI(KC_LBRACKET)
#define CO_WS_RIGHT RGUI(KC_RBRACKET)


// Android Studio shortcuts
#define AS_TABLEFT LALT(KC_LEFT)
#define AS_TABRIGHT LALT(KC_RIGHT)
#define AS_SYMBOL LCTL(LALT(KC_N))
#define AS_CLASS LCTL(KC_N)
#define AS_FINDUSAGE LALT(KC_F7)
#define AS_BACK LCTL(LALT(KC_LEFT))
#define AS_BRACKET LCTL(LSFT(KC_M))
#define AS_GO_DECLARATION LCTL(KC_B)
#define AS_GO_IMPLEMENTATION LCTL(LALT(KC_B))
#define AS_CLOSETAB LCTL(KC_F4)
#define AS_CLOSETOOLWINDOW LCTL(LSFT(KC_F4))
#define AS_COPYLINEDOWN LCTL(KC_D)
#define AS_DEL_LINE LCTL(KC_Y)
#define AS_LINE LCTL(KC_G)
#define AS_CMT_BLOCK LCTL(LSFT(KC_SLSH))
#define AS_CMT_LINE LCTL(KC_SLSH)
#define AS_BM_PREV LALT(KC_P)
#define AS_BM_NEXT LALT(KC_N)
#define AS_BM_TOGGLE KC_F11
#define AS_BM_LIST LSFT(KC_F11)

// visual studio code shortcuts
// ============================

#include "vscode_macros.h"

// unused vscode shortcuts
// #define VS_BM_LIST LCTL(LALT(KC_L))
// #define VS_BM_LISTALL LCTL(LALT(KC_A))
// #define VS_BM_CLEARALL LCTL(LALT(KC_C))

// #define VS_TERMINAL_PREV MEH(KC_F12)
// #define VS_TERMINAL_NEXT MEH(KC_F13)
// #define VS_TERMINAL_NEW MEH(KC_F14)
// #define VS_TERMINAL_DETACH MEH(KC_F15)
// #define VS_TERMINAL_RENAME MEH(KC_F16)
// #define VS_JUMPY MEH(KC_F17)
// #define VS_FIND MEH(KC_F19)
// #define VS_CLOSEPANEL LCTL(LSFT(KC_W))
// #define VS_BUILD LCTL(LSFT(KC_B))
// #define VS_OPEN_FILE        MEH(KC_F2)
// #define VS_TERMINAL         MEH(KC_F15)



#define MACRO_SCREEN_NUM(MACRO_NAME,NUM) \
        case MACRO_NAME:\
             if (record->event.pressed) {\
                return MACRO( D(LCTL), T(A), U(LCTL), T(NUM), END);\
            }\
        break;\

#define MACRO_SCREEN_REG(MACRO_NAME,NUM) \
        case MACRO_NAME:\
             if (record->event.pressed) {\
                return MACRO( D(LCTL), T(A), U(LCTL), D(LSFT), T(SCOLON), U(LSFT),\
                              T(R),\
                              T(E),\
                              T(A),\
                              T(D),\
                              T(R),\
                              T(E),\
							  T(G),\
                              T(SPC),\
							  T(NUM),\
							  T(ENTER),\
                             END);\
            }\
        break;\

#define MACRO_SCREEN_PASTE(MACRO_NAME,NUM)\
        case MACRO_NAME:\
             if (record->event.pressed) {\
                return MACRO( D(LCTL), T(A), U(LCTL), D(LSFT), T(SCOLON), U(LSFT),\
                              T(P),\
                              T(A),\
                              T(S),\
                              T(T),\
                              T(E),\
                              T(SPC),\
							  T(NUM),\
							  T(ENTER),\
                             END);\
            }\
        break;\

// tap-dance configuration
// =======================

enum {
    // TD_BSPC_CTL_BSPC,
    // TD_BSPC_CTL_BSPC_IOS,
    TD_DEL_WORD_DEL,
    TD_DEL_WORD_DEL_IOS
};

typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;

#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold) \
    { .fn = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}), }

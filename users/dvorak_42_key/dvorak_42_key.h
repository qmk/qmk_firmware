#pragma once

#include "quantum.h"

// LAYERS
// ======

#define BASE             0 // base dvorak layer
#define BASE_IOS         1 // base dvorak layer, for ipad / IOS
#define KEYNAV           2 // arrow navigation (right hand)
#define KEYNAV_IOS       3 // arrow navigation (right hand)
#define KEYSEL           4 // arrow navigation + shift (allow text selection)
#define KEYSEL_IOS       5 // arrow navigation + shift (allow text selection)
#define SHELL_NAV        6 // bash shortcuts
#define SHELL_SCREEN     7 // linux screen shortcuts
#define BROWSER_CONTROL  8 // control browser and mouse
#define BROWSER_CONTROL_IOS 9 // control browser and mouse
#define COMBINED            10 // combined numbers and symbols layer
#define ANDROID_STUDIO     11 // android studio specific layer
#define VSCODE             12 // visual studio code specific layer
#define SHORTCUTS          13 // shortcuts to be intercepted by autohotkey
#define RGB_CONTROL        14 // control RGB effects

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

  // these macros assume that caps lock is mapped to globe in iOS preferences
  IOS_APP_PREV,
  IOS_APP_NEXT,
  IOS_APP_LIST,
  IOS_SHOW_SLIDEOVER,
};






// Notepad++ shortcuts
// ===================
#define NP_DUPE_LINE LCTL(KC_D)


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

#define VS_FILE             MEH(KC_F1) // workbench.action.quickOpen

#define VS_LINE             MEH(KC_F3) // workbench.action.gotoLine
#define VS_SYMBOLEDITOR     MEH(KC_F4) // workbench.action.gotoSymbol
#define VS_DEFINITION       MEH(KC_F5) // editor.action.revealDefinition
#define VS_IMPLEMENTATION   MEH(KC_F6) // editor.action.goToImplementation
#define VS_REFERENCES       MEH(KC_F7) // editor.action.goToReferences
#define VS_BACK             MEH(KC_F8) // workbench.action.navigateBack
#define VS_BRACKET          MEH(KC_F9) // editor.action.jumpToBracket
#define VS_TABLEFT          MEH(KC_F10) // workbench.action.previousEditor
#define VS_TABRIGHT         MEH(KC_F11) // workbench.action.nextEditor
#define VS_CLOSETAB         MEH(KC_F12) // workbench.action.closeActiveEditor

#define VS_GROUP_1          MEH(KC_F13) // workbench.action.focusFirstEditorGroup
#define VS_GROUP_2          MEH(KC_F14) // workbench.action.focusSecondEditorGroup

#define VS_COMMANDS         MEH(KC_F16) // workbench.action.showCommands
#define VS_CMT_BLOCK        MEH(KC_F17) // editor.action.blockComment
#define VS_CMT_LINE         MEH(KC_F18) // editor.action.commentLine
#define VS_DEL_LINE         MEH(KC_F19) // editor.action.deleteLines
#define VS_COPYLINEDOWN     MEH(KC_0) // editor.action.copyLinesDownAction

// visual studio bookmark commands
#define VS_BM_PREV          MEH(KC_1) // bookmarks.jumpToPrevious
#define VS_BM_NEXT          MEH(KC_2) // bookmarks.jumpToNext
#define VS_BM_TOGGLE        MEH(KC_8) // bookmarks.toggle
#define VS_BM_CLEARALL      MEH(KC_9) // bookmarks.clearFromAllFiles
#define VS_BM_LIST          MEH(KC_A) // bookmarks.list
#define VS_BM_LISTALL       MEH(KC_B) // bookmarks.listFromAllFiles
#define VS_JUMPY            MEH(KC_C) // extension.jumpy-word

// visual studio code navigation shortcuts
#define VS_FOCUS_EDITOR     MEH(KC_4) // workbench.action.focusActiveEditorGroup
#define VS_FOCUS_TERMINAL   MEH(KC_5) // workbench.action.terminal.focus
#define VS_TOGGLE_TERMINAL  MEH(KC_6) // workbench.action.terminal.toggleTerminal


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
    TD_DEL_WORD_DEL_IOS,
};

typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;

#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold) \
    { .fn = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}), }

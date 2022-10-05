#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"


// to build this keymap
// make ergodox_ez:dvorak_42_key:teensy
// or:
// qmk compile -kb ergodox_ez -km dvorak_42_key_crkbd
// flashing from rpi:
// sudo teensy_loader_cli -v -w .build/ergodox_ez_dvorak_42_key.hex --mcu atmega32u4

// keeping fork up to date:
// https://help.github.com/articles/configuring-a-remote-for-a-fork/
// https://help.github.com/articles/syncing-a-fork/
// pushing dev branch
// git push origin dev:dev

// debounce settings
// remove these after getting a new keyboard
// #define DEBOUNCE 50

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

  SCREEN_UP_JUMP,
  SCREEN_DOWN_JUMP,

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

// visual studio code navigation shortcuts
#define VS_FOCUS_EDITOR     MEH(KC_4) // workbench.action.focusActiveEditorGroup
#define VS_FOCUS_TERMINAL   MEH(KC_5) // workbench.action.terminal.focus
#define VS_TOGGLE_TERMINAL  MEH(KC_6) // workbench.action.terminal.toggleTerminal
#define VS_CLEAR_TERMINAL   MEH(KC_7) // workbench.action.terminal.clear


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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [BASE] = LAYOUT_ergodox(
      // left hand
      KC_TRNS,           KC_TRNS,       KC_TRNS,    KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS,
      OSL(VSCODE),       KC_QUOTE,      KC_COMMA,   KC_DOT,       KC_P,    KC_Y,    KC_TRNS,
      OSL(SHELL_NAV),    KC_A,          KC_O,       KC_E,         KC_U,    KC_I,
      OSL(SHELL_SCREEN), KC_SCOLON,     KC_Q,       KC_J,         KC_K,    KC_X,    KC_TRNS,
      KC_TRNS,           KC_TRNS,       KC_TRNS,    KC_TRNS,      MO(BROWSER_CONTROL),

      // left thumb cluster
                KC_TRNS,KC_TRNS,
                        KC_TRNS,
      MO(COMBINED),MO(KEYNAV), KC_TRNS,

      // right hand
      KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS,   KC_F,  KC_G,  KC_C,   KC_R,   KC_L,   KC_BSPC,
                 KC_D,  KC_H,  KC_T,   KC_N,   KC_S,   RCTL(KC_BSPC),
      KC_TRNS,   KC_B,  KC_M,  KC_W,   KC_V,   KC_Z,   OSM(MOD_LSFT),
      OSL(SHORTCUTS), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

      // right thumb cluster
        KC_TRNS, KC_TRNS,
        KC_TRNS,
        KC_TRNS, KC_ENTER, KC_SPACE

  ),

  [BASE_IOS] = LAYOUT_ergodox(
      // left hand
      KC_TRNS,           KC_TRNS,       KC_TRNS,    KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS,           KC_TRNS,       KC_TRNS,    KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS,           KC_TRNS,       KC_TRNS,    KC_TRNS,      KC_TRNS, KC_TRNS,
      KC_TRNS,           KC_TRNS,       KC_TRNS,    KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS,           KC_TRNS,       KC_TRNS,    KC_TRNS,      MO(BROWSER_CONTROL_IOS),

      // left thumb cluster
                KC_TRNS,KC_TRNS,
                        KC_TRNS,
      KC_TRNS,MO(KEYNAV_IOS), KC_TRNS,

      // right hand
      KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LALT(KC_BSPC),
      KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

      // right thumb cluster
        KC_TRNS, KC_TRNS,
        KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS

  ),

  [KEYNAV] = LAYOUT_ergodox(
    // left hand
    KC_TRNS,         KC_TRNS,       KC_TRNS,        KC_TRNS,         KC_TRNS,          KC_TRNS,      KC_TRNS,
    KC_TRNS,         KC_ESC,        RCTL(KC_K),     RCTL(KC_Z),      RCTL(KC_S),       RCTL(KC_N),   KC_TRNS,
    KC_TRNS,         MO(KEYSEL),    KC_TRNS,        RSFT(KC_TAB),    KC_TAB,           RCTL(KC_F),
    KC_TRNS,         OSM(MOD_LSFT), OSM(MOD_LGUI),  OSM(MOD_LALT),   OSM(MOD_LCTL),    NP_DUPE_LINE, KC_TRNS,
    KC_TRNS,         KC_TRNS,       KC_TRNS,        KC_TRNS,         KC_TRNS,
    // left thumb cluster
    KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,


    // right hand
    KC_TRNS,KC_TRNS,       KC_TRNS,    KC_TRNS,         KC_TRNS,    KC_TRNS,          KC_TRNS,
    KC_TRNS,KC_NO,         KC_HOME,    KC_UP,           KC_END,     KC_PGUP,          KC_DELETE,
            LCTL(KC_LEFT), KC_LEFT,    KC_DOWN,         KC_RIGHT,   LCTL(KC_RIGHT),   RCTL(KC_DELETE),
    KC_TRNS,KC_TRNS,       RCTL(KC_C), RCTL(KC_X),      RCTL(KC_V), KC_PGDOWN,        KC_NO,
                           KC_TRNS,    KC_TRNS,         KC_TRNS,    KC_TRNS,          KC_TRNS,

    // right thumb cluster
    KC_TRNS, KC_TRNS,
    KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS
  ),

  // https://medium.com/macoclock/best-text-editing-keyboard-shortcuts-for-ipad-41e8234a4c42
  // alt == option
  // gui/win == command
  // 
  [KEYNAV_IOS] = LAYOUT_ergodox(
    // left hand
    KC_TRNS,         KC_TRNS,         KC_TRNS,        KC_TRNS,         KC_TRNS,          KC_TRNS,     KC_TRNS,
    KC_TRNS,         KC_ESC,          KC_TRNS,        RGUI(KC_Z),      RCTL(KC_S),       KC_TRNS,     KC_TRNS,
    KC_TRNS,         MO(KEYSEL_IOS),  KC_TRNS,        KC_TRNS,         KC_TRNS,          KC_TRNS,
    KC_TRNS,         KC_TRNS,         KC_TRNS,        KC_TRNS,         KC_TRNS,          KC_TRNS,     KC_TRNS,
    KC_TRNS,         KC_TRNS,         KC_TRNS,        KC_TRNS,         KC_TRNS,
    // left thumb cluster
    KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,


    // right hand
    KC_TRNS,KC_TRNS,       KC_TRNS,       KC_TRNS,         KC_TRNS,        KC_TRNS,          KC_TRNS,
    KC_TRNS,KC_NO,         RGUI(KC_LEFT), KC_UP,           RGUI(KC_RIGHT), KC_PGUP,          KC_DELETE,
            LALT(KC_LEFT), KC_LEFT,       KC_DOWN,         KC_RIGHT,       LALT(KC_RIGHT),   LALT(KC_DELETE),
    KC_TRNS,KC_TRNS,       RGUI(KC_C),    RGUI(KC_X),      RGUI(KC_V),     KC_PGDOWN,        KC_NO,
                           KC_TRNS,       KC_TRNS,         KC_TRNS,        KC_TRNS,          KC_TRNS,

    // right thumb cluster
    KC_TRNS, KC_TRNS,
    KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS
  ),  

    // key selection layer
    [KEYSEL] = LAYOUT_ergodox(
           // left hand
           KC_TRNS,KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
           KC_TRNS,KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
           KC_TRNS,KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   
           KC_TRNS,KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
                   // bottom row
                   QK_BOOT,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                           // thumb cluster
                                           KC_TRNS,KC_TRNS,
                                                   KC_TRNS,
                                   KC_TRNS,KC_TRNS,KC_TRNS,
           // right hand
           KC_TRNS,   KC_TRNS,             KC_TRNS,       KC_TRNS,       KC_TRNS,        KC_TRNS,              KC_TRNS,
           KC_TRNS,   KC_TRNS,             RSFT(KC_HOME), RSFT(KC_UP),   RSFT(KC_END),   RSFT(KC_PGUP),        KC_TRNS,
                      RSFT(RCTL(KC_LEFT)), RSFT(KC_LEFT), RSFT(KC_DOWN), RSFT(KC_RIGHT), RSFT(RCTL(KC_RIGHT)), KC_TRNS,
           KC_TRNS,   KC_TRNS,             RCTL(KC_C),    RCTL(KC_X),    RCTL(KC_V),     RSFT(KC_PGDN),        KC_TRNS,
                    // bottom row
                      KC_TRNS,   KC_TRNS,   KC_TRNS,  KC_TRNS, KC_TRNS,
           // thumb cluster
           KC_TRNS, KC_TRNS,
           KC_TRNS,
           KC_TRNS, KC_TRNS, KC_TRNS
    ),

    // key selection layer
    [KEYSEL_IOS] = LAYOUT_ergodox(
           // left hand
           KC_TRNS,KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
           KC_TRNS,KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
           KC_TRNS,KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   
           KC_TRNS,KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
                   // bottom row
                   QK_BOOT,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                           // thumb cluster
                                           KC_TRNS,KC_TRNS,
                                                   KC_TRNS,
                                   KC_TRNS,KC_TRNS,KC_TRNS,
           // right hand
           KC_TRNS,   KC_TRNS,             KC_TRNS,             KC_TRNS,       KC_TRNS,              KC_TRNS,              KC_TRNS,
           KC_TRNS,   KC_TRNS,             RSFT(RGUI(KC_LEFT)), RSFT(KC_UP),   RSFT(RGUI(KC_RIGHT)), RSFT(KC_PGUP),        KC_TRNS,
                      RSFT(LALT(KC_LEFT)), RSFT(KC_LEFT),       RSFT(KC_DOWN), RSFT(KC_RIGHT),       RSFT(LALT(KC_RIGHT)), KC_TRNS,
           KC_TRNS,   KC_TRNS,             RGUI(KC_C),          RGUI(KC_X),    RGUI(KC_V),           RSFT(KC_PGDN),        KC_TRNS,
                    // bottom row
                      KC_TRNS,   KC_TRNS,   KC_TRNS,  KC_TRNS, KC_TRNS,
           // thumb cluster
           KC_TRNS, KC_TRNS,
           KC_TRNS,
           KC_TRNS, KC_TRNS, KC_TRNS
    ),    

  // shell navigation layer
  [SHELL_NAV] = LAYOUT_ergodox(
       // left hand
       KC_NO,  KC_TRNS,           KC_TRNS,        KC_TRNS,          KC_TRNS,     KC_TRNS,     KC_TRNS,
       KC_TRNS,SHELL_GIT_DIFF,    SHELL_PGREP,    SHELL_PLESS,      SHELL_LESS,  KC_TRNS,     KC_TRNS,
       KC_TRNS,SHELL_GIT_STATUS,  SHELL_CDPRE,    SHELL_LSLTR,      SHELL_LS,    SHELL_LSLA,
       KC_TRNS,SHELL_SCREEN_LIST, SHELL_SCREENRD, SHELL_SCREEN_NEW, SHELL_TAILF, KC_TRNS,     KC_TRNS,
               // bottom row
               KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                       // thumb cluster
                                       KC_TRNS,KC_TRNS,
                                               KC_TRNS,
                               KC_TRNS,KC_TRNS,KC_TRNS,
       // right hand
       KC_TRNS,    KC_TRNS,    KC_TRNS,             KC_TRNS,         KC_TRNS,    KC_TRNS,    KC_TRNS,
       KC_TRNS,    KC_TRNS,    KC_HOME,             KC_UP,           KC_END,     RCTL(KC_L), RCTL(KC_X),
                   LALT(KC_B), KC_LEFT,             KC_DOWN,         KC_RIGHT,   LALT(KC_F), RCTL(KC_W),
       KC_TRNS,    RCTL(KC_U), LALT(KC_DOT),        RCTL(KC_R),      KC_BTN2,    RCTL(KC_K), RCTL(KC_C),
                   // bottom row 
                   KC_TRNS,   KC_TRNS,   KC_TRNS,  KC_TRNS, KC_TRNS,
       // thumb cluster
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TAB
  ),


    // linux screen layer
  [SHELL_SCREEN] = LAYOUT_ergodox(
       // left hand
       KC_NO,  KC_TRNS,   KC_TRNS,            KC_TRNS,             KC_TRNS,     KC_TRNS,   KC_TRNS,
       KC_TRNS,KC_TRNS,   SCREEN_READREG_3,   SCREEN_READREG_2,    SCREEN_READREG_1,      KC_TRNS,   KC_TRNS,
       KC_TRNS,KC_TRNS,   SCREEN_PASTEREG_3,  SCREEN_PASTEREG_2,   SCREEN_PASTEREG_1,     KC_TRNS,
       KC_TRNS,KC_TRNS,   KC_TRNS,            KC_TRNS,             KC_TRNS,     KC_TRNS,   KC_TRNS,
               // bottom row
               KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                       // thumb cluster
                                       KC_TRNS,KC_TRNS,
                                               KC_TRNS,
                               KC_TRNS,KC_TRNS,KC_TRNS,
       // right hand
       KC_TRNS, KC_TRNS,            KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,             KC_TRNS,
       KC_TRNS, SCREEN_NEW_TAB,     SCREEN_7,    SCREEN_8,    SCREEN_9,    SCREEN_RENAME,       KC_TRNS,
                SCREEN_TAB_LEFT,    SCREEN_4,    SCREEN_5,    SCREEN_6,    SCREEN_TAB_RIGHT,    SCREEN_COPY_MODE,
       KC_TRNS, KC_TRNS,            SCREEN_1,    SCREEN_2,    SCREEN_3,    SCREEN_NUMBER,       SCREEN_PASTE,
                                    // bottom row
                                    SCREEN_0,    KC_TRNS,     KC_TRNS,     KC_TRNS,             SCREEN_DETACH,
       // thumb cluster
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
  ),

    // android studio shortcuts
  [ANDROID_STUDIO] = LAYOUT_ergodox(
       // left hand
       KC_NO,  KC_TRNS,    KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,   KC_TRNS,
       KC_TRNS,KC_TRNS,    KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,   KC_TRNS,
       KC_TRNS,KC_TRNS,    KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,
       KC_TRNS,KC_TRNS,    KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,   KC_TRNS,
               // bottom row
               KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                       // thumb cluster
                                       KC_TRNS,KC_TRNS,
                                               KC_TRNS,
                               KC_TRNS,KC_TRNS,KC_TRNS,
       // right hand
       KC_TRNS,      KC_TRNS,         KC_TRNS,       KC_TRNS,           KC_TRNS,              KC_TRNS,              KC_TRNS,
       AS_CMT_LINE,  AS_COPYLINEDOWN, AS_FINDUSAGE,  AS_GO_DECLARATION, AS_GO_IMPLEMENTATION, AS_LINE,              AS_BRACKET,
                     AS_CLOSETAB,     AS_TABLEFT,    AS_TABRIGHT,       AS_SYMBOL,            AS_CLASS,             AS_BACK,
       AS_CMT_BLOCK, KC_TRNS,         AS_BM_PREV,    AS_BM_NEXT,        KC_TRNS,              AS_CLOSETOOLWINDOW,   AS_BM_TOGGLE,
                         // bottom row
                         KC_TRNS,     AS_BM_LIST,    KC_TRNS,        KC_TRNS,              KC_TRNS,
       // thumb cluster
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, AS_DEL_LINE, KC_TRNS
  ),

    // vscode shortcuts shortcuts
  [VSCODE] = LAYOUT_ergodox(
       // left hand
       KC_NO,  KC_TRNS,           KC_TRNS,             KC_TRNS,           KC_TRNS,             KC_TRNS,   KC_TRNS,
       KC_TRNS,KC_TRNS,           KC_TRNS,             VS_CMT_BLOCK,      VS_CMT_LINE,         KC_TRNS,   KC_TRNS,
       KC_TRNS,VS_CLEAR_TERMINAL, VS_TOGGLE_TERMINAL,  VS_FOCUS_TERMINAL, VS_FOCUS_EDITOR,     KC_TRNS,
       KC_TRNS,KC_TRNS,           KC_TRNS,             KC_TRNS,           KC_TRNS,             KC_TRNS,   KC_TRNS,
               // bottom row
               KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                       // thumb cluster
                                       KC_TRNS,KC_TRNS,
                                               KC_TRNS,
                               KC_TRNS,KC_TRNS,KC_TRNS,
       // right hand
       KC_TRNS,      KC_TRNS,          KC_TRNS,       KC_TRNS,          KC_TRNS,             KC_TRNS,         KC_TRNS,
       KC_TRNS,      VS_COPYLINEDOWN,  VS_REFERENCES, VS_DEFINITION,    VS_IMPLEMENTATION,   VS_LINE,         VS_BRACKET,
                     VS_CLOSETAB,      VS_TABLEFT,    VS_TABRIGHT,      VS_SYMBOLEDITOR,     VS_FILE,         VS_BACK,
       KC_TRNS,      KC_TRNS,          VS_BM_PREV,    VS_BM_NEXT,       VS_GROUP_1,          VS_GROUP_2,      VS_BM_TOGGLE,
                                       // bottom row
                                       VS_COMMANDS,   KC_TRNS,          KC_TRNS,             KC_TRNS,         KC_TRNS,
       // thumb cluster
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, VS_DEL_LINE, KC_TRNS
  ),


  [COMBINED] = LAYOUT_ergodox(

    // left hand
    KC_NO,    KC_TRNS, KC_TRNS,    KC_TRNS,     KC_TRNS,     KC_TRNS, KC_TRNS,
    KC_TILD,  KC_EXLM, KC_AT,      KC_HASH,     KC_DLR,      KC_PERC, KC_TRNS,
    KC_GRAVE, KC_LPRN, KC_RPRN,    KC_LBRACKET, KC_RBRACKET, KC_UNDS,
    KC_CIRC,  KC_COLN, KC_DQUO,    KC_LCBR,     KC_RCBR,     KC_AMPR, KC_TRNS,
    // bottom row
    KC_TRNS,KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS,
    // thumb cluster
    KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,

    // right hand
    KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS,
    KC_TRNS, KC_PLUS,     KC_7,    KC_8,    KC_9,    KC_ASTR,     KC_PIPE,
             KC_MINS,     KC_4,    KC_5,    KC_6,    KC_SLSH,     KC_BSLS,
    KC_TRNS, KC_EQUAL,    KC_1,    KC_2,    KC_3,    KC_QUES,     KC_DOT,
    // bottom row
                          KC_0,    KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS,
    // thumb cluster
    KC_TRNS,KC_TRNS,
	KC_TRNS,
	KC_TRNS,KC_TRNS,KC_TRNS),


    [BROWSER_CONTROL] = LAYOUT_ergodox(
		   // left hand
           KC_TRNS, KC_TRNS,      KC_TRNS,       KC_TRNS,       KC_TRNS,      KC_TRNS, KC_TRNS,
           KC_TRNS, KC_TRNS,      KC_BTN3,       KC_MS_U,       KC_BTN1,      KC_BTN2, KC_TRNS,
           KC_TRNS, KC_TRNS,      KC_MS_L,       KC_MS_D,       KC_MS_R,      KC_TRNS,
           KC_TRNS, KC_TRNS,      KC_TRNS,       WINDOWS10_WORKSPACE_LEFT,   WINDOWS10_WORKSPACE_RIGHT,      KC_TRNS, KC_TRNS,
		   // bottom row
           KC_TRNS, KC_TRNS,      KC_TRNS,       KC_TRNS,       KC_TRNS,

                                               KC_TRNS, KC_TRNS,
                                                        KC_TRNS,
                                      KC_TRNS, KC_TRNS, KC_TRNS,
          // right hand
           KC_TRNS,  KC_TRNS,   KC_TRNS,            KC_TRNS,      KC_TRNS,       KC_TRNS,       KC_TRNS,
           KC_TRNS,  KC_UP,     KC_PGUP,            KC_PGDN,      KC_MS_WH_UP,   KC_TRNS,       KC_TRNS,
                     KC_DOWN,   RCTL(KC_PGUP), 	    RCTL(KC_PGDN),KC_MS_WH_DOWN, LALT(KC_LEFT), KC_TRNS,
           KC_TRNS,  KC_TRNS,   RCTL(KC_1),         RCTL(KC_9),   KC_F6,         KC_F5,         KC_TRNS,
                                // bottom row
                                RCTL(LSFT(KC_TAB)), RCTL(KC_TAB),      KC_TRNS,       KC_TRNS,       KC_TRNS,
           KC_TRNS, KC_TRNS,
           KC_TRNS,
           KC_TRNS, RCTL(KC_W), RCTL(KC_T)
    ),

    // https://support.brave.com/hc/en-us/articles/360032272171-What-keyboard-shortcuts-can-I-use-in-Brave-
    // note: need capslock to be mapped to Globe in iOS setting
    [BROWSER_CONTROL_IOS] = LAYOUT_ergodox(
		   // left hand
           KC_TRNS, KC_TRNS,      KC_TRNS,            KC_TRNS,       KC_TRNS,        KC_TRNS,      KC_TRNS,
           KC_TRNS, KC_TRNS,      KC_BTN3,            KC_MS_U,       KC_BTN1,        KC_BTN2,      KC_TRNS,
           KC_TRNS, KC_TRNS,      KC_MS_L,            KC_MS_D,       KC_MS_R,        KC_TRNS,
           KC_TRNS, KC_TRNS,      IOS_SHOW_SLIDEOVER, IOS_APP_PREV,  IOS_APP_NEXT,   IOS_APP_LIST, KC_TRNS,
		   // bottom row
           KC_TRNS, KC_TRNS,      KC_TRNS,       KC_TRNS,       KC_TRNS,

                                               KC_TRNS, KC_TRNS,
                                                        KC_TRNS,
                                      KC_TRNS, KC_TRNS, KC_TRNS,
          // right hand
           KC_TRNS,  KC_TRNS,   KC_TRNS,             KC_TRNS,              KC_TRNS,       KC_TRNS,       KC_TRNS,
           KC_TRNS,  KC_UP,     KC_PGUP,             KC_PGDN,              KC_MS_WH_UP,   KC_TRNS,       KC_TRNS,
                     KC_DOWN,   RGUI(LALT(KC_LEFT)), RGUI(LALT(KC_RIGHT)), KC_MS_WH_DOWN, LALT(KC_LEFT), KC_TRNS,
           KC_TRNS,  KC_TRNS,   RCTL(KC_1),          RCTL(KC_9),           RGUI(KC_L),    KC_F5,         KC_TRNS,
                                // bottom row
                                RCTL(LSFT(KC_TAB)),  RCTL(KC_TAB),         KC_TRNS,       KC_TRNS,       KC_TRNS,
           KC_TRNS, KC_TRNS,
           KC_TRNS,
           KC_TRNS, RGUI(KC_W), RGUI(KC_T)
    ),

  // shortcuts to be intercepted by autohotkey
  [SHORTCUTS] = LAYOUT_ergodox(
       // left hand
       KC_TRNS,   KC_TRNS,    KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,   KC_TRNS,
       MEH(KC_0), MEH(KC_1), MEH(KC_2), MEH(KC_3),   MEH(KC_4),   MEH(KC_5), KC_TRNS,
       MEH(KC_6), MEH(KC_7), MEH(KC_8), MEH(KC_9),   MEH(KC_A),   MEH(KC_B),
       MEH(KC_C), MEH(KC_D), MEH(KC_E), MEH(KC_F),   MEH(KC_G),   MEH(KC_H),   KC_TRNS,
               // bottom row
               KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,TG(BASE_IOS),
                                       // thumb cluster
                                       KC_TRNS,KC_TRNS,
                                               KC_TRNS,
                               KC_TRNS,DF(BASE),DF(BASE_IOS),
       // right hand
       KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,     KC_TRNS,     QK_BOOT,
       KC_TRNS, MEH(KC_I), MEH(KC_J), MEH(KC_K), MEH(KC_L),   MEH(KC_M),   MEH(KC_N),
                MEH(KC_O), MEH(KC_P), MEH(KC_Q), MEH(KC_R),   MEH(KC_S),   MEH(KC_T),
       KC_TRNS, MEH(KC_U), MEH(KC_V), MEH(KC_W), MEH(KC_X),   MEH(KC_Y),   MEH(KC_Z),
                                    // bottom row
                KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,             KC_TRNS,
       // thumb cluster
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
  ),


};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;
    case RGB_SLD:
      if (record->event.pressed) {
        // rgblight_mode(1);
      }
      return false;
      break;
  }

  // shell macros
  if(record->event.pressed) {
    switch (keycode) {
        case SHELL_LS:
            SEND_STRING("ls\n");
            return true;
            break;
        case SHELL_LSLTR:
            SEND_STRING("ls -ltr\n");
            return true;
            break;
        case SHELL_LSLA:
            SEND_STRING("ls -la\n");
            return true;
            break;
        case SHELL_CDPRE:
            SEND_STRING("cd ..\n");
            return true;
            break;
        case SHELL_LESS:
            SEND_STRING("less ");
            return true;
            break;
        case SHELL_PLESS:
            SEND_STRING(" | less");
            return true;
            break;
        case SHELL_PGREP:
            SEND_STRING(" | grep ");
            return true;
            break;
        case SHELL_TAILF:
            SEND_STRING("tail -f ");
            return true;
            break;
        case SHELL_SCREENRD:
            SEND_STRING("screen -r -d ");
            return true;
            break;
        case SHELL_SCREEN_NEW:
            SEND_STRING("screen -S ");
            return true;
            break;
        case SHELL_SCREEN_LIST:
            SEND_STRING("screen -list\n");
            return true;
            break;

        case SHELL_GIT_DIFF:
            SEND_STRING("git diff\n");
            return true;
            break;

        case SHELL_GIT_STATUS:
            SEND_STRING("git status\n");
            return true;
            break;            

        case WINDOWS10_WORKSPACE_LEFT:
            SEND_STRING(SS_LGUI(SS_LCTRL(SS_TAP(X_LEFT))));
            return true;
            break;
        case WINDOWS10_WORKSPACE_RIGHT:
            SEND_STRING(SS_LGUI(SS_LCTRL(SS_TAP(X_RIGHT))));
            break;
        case WINDOWS10_TASK_VIEW:
            SEND_STRING(SS_LGUI(SS_TAP(X_TAB)));
            break;
        // IOS shortcuts
        case IOS_APP_PREV:
            SEND_STRING(SS_DOWN(X_CAPS) SS_TAP(X_LEFT) SS_UP(X_CAPS));
            break;
        case IOS_APP_NEXT:
            SEND_STRING(SS_DOWN(X_CAPS) SS_TAP(X_RIGHT) SS_UP(X_CAPS));
            break;            
        case IOS_APP_LIST:
            SEND_STRING(SS_DOWN(X_CAPS) SS_TAP(X_UP) SS_UP(X_CAPS));
            break;                        
        case IOS_SHOW_SLIDEOVER:
            SEND_STRING(SS_DOWN(X_CAPS) SS_TAP(X_BSLS) SS_UP(X_CAPS));
            break;                                    
        // linux screen shortcuts
        case SCREEN_TAB_LEFT:
            SEND_STRING(SS_LCTL("a") "p");
            break;
        case SCREEN_TAB_RIGHT:
            SEND_STRING(SS_LCTL("a") "n");
            break;
        case SCREEN_NEW_TAB:
            SEND_STRING(SS_LCTL("a") "c");
            break;
        case SCREEN_DETACH:
            SEND_STRING(SS_LCTL("a") "d");
            break;
        case SCREEN_RENAME:
            SEND_STRING(SS_LCTL("a") SS_LSFT("a"));
            break;
        case SCREEN_NUMBER:
            SEND_STRING(SS_LCTL("a") ":number ");
            break;
        case SCREEN_0:
            SEND_STRING(SS_LCTL("a") "0");
            break;
        case SCREEN_1:
            SEND_STRING(SS_LCTL("a") "1");
            break;
        case SCREEN_2:
            SEND_STRING(SS_LCTL("a") "2");
            break;
        case SCREEN_3:
            SEND_STRING(SS_LCTL("a") "3");
            break;
        case SCREEN_4:
            SEND_STRING(SS_LCTL("a") "4");
            break;
        case SCREEN_5:
            SEND_STRING(SS_LCTL("a") "5");
            break;
        case SCREEN_6:
            SEND_STRING(SS_LCTL("a") "6");
            break;
        case SCREEN_7:
            SEND_STRING(SS_LCTL("a") "7");
            break;
        case SCREEN_8:
            SEND_STRING(SS_LCTL("a") "8");
            break;
        case SCREEN_9:
            SEND_STRING(SS_LCTL("a") "9");
            break;
        case SCREEN_COPY_MODE:
            SEND_STRING(SS_LCTL("a") "[");
            break;
        case SCREEN_PASTE:
            SEND_STRING(SS_LCTL("a") "]");
            break;

        case SCREEN_UP_JUMP:
            tap_code(KC_5);
            tap_code(KC_UP);
            break;
		case SCREEN_DOWN_JUMP:
            tap_code(KC_5);
            tap_code(KC_DOWN);
            break;

        case SCREEN_READREG_1:
            tap_code16(C(KC_A));
            tap_code16(S(KC_SCOLON));
            SEND_STRING("readreg 1\n");
            break;
        case SCREEN_READREG_2:
            tap_code16(C(KC_A));
            tap_code16(S(KC_SCOLON));
            SEND_STRING("readreg 2\n");
            break;
        case SCREEN_READREG_3:
            tap_code16(C(KC_A));
            tap_code16(S(KC_SCOLON));
            SEND_STRING("readreg 3\n");
            break;

        case SCREEN_PASTEREG_1:
            tap_code16(C(KC_A));
            tap_code16(S(KC_SCOLON));
            SEND_STRING("paste 1\n");
            break;
        case SCREEN_PASTEREG_2:
            tap_code16(C(KC_A));
            tap_code16(S(KC_SCOLON));
            SEND_STRING("paste 2\n");
            break;
        case SCREEN_PASTEREG_3:
            tap_code16(C(KC_A));
            tap_code16(S(KC_SCOLON));
            SEND_STRING("paste 3\n");
            break;
    }
  }

  return true;
}

void led_set_user(uint8_t usb_led) {
    if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
        ergodox_right_led_1_on();
    } else {
        ergodox_right_led_1_off();
    }
}

void matrix_scan_user(void) {

    uint8_t layer = get_highest_layer(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
        case BASE_IOS:
            ergodox_right_led_1_on();
            ergodox_right_led_3_on();
            break;
        case COMBINED:
            ergodox_right_led_2_on();
            break;
        case SHELL_NAV:
        case SHELL_SCREEN:
        case KEYNAV:
        case KEYSEL:
        case VSCODE:
            ergodox_right_led_3_on();
            break;
	case BROWSER_CONTROL:
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
            break;
	case SHORTCUTS:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
            break;            
        default:
            break;
    }

};

#pragma once


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
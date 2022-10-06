#include "dvorak_42_key.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
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
        case SCREEN_KILL:
            SEND_STRING(SS_LCTL("a") "k" "y");
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

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD_BSPC_CTL_BSPC] = ACTION_TAP_DANCE_DOUBLE(KC_BSPC, RCTL(KC_BSPC)),
    [TD_BSPC_CTL_BSPC_IOS] = ACTION_TAP_DANCE_DOUBLE(KC_BSPC, LALT(KC_BSPC)),
};
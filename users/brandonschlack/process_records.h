#pragma once
#include "brandonschlack.h"

// Macros
enum custom_keycodes {
    KC_MAKE = SAFE_RANGE,
    CMD_TAB,
    WN_SLPD,
    OS_MAC,
    OS_WIN,
    TG_NAVI,
    TG_REDR,
    TG_MEDA,
    TG_KYPD,
    KEYMAP_SAFE_RANGE
};

bool process_record_keymap(uint16_t keycode, keyrecord_t *record);
void matrix_scan_cmd_tab(void);

// Useful Defines
#define HY_CAPS   ALL_T(KC_CAPS)
#define TG_MAGC   TG(_MAGIC)
// Media Mod-Tap
#define MM_RGUI   RGUI_T(KC_MRWD)
#define MM_RALT   RALT_T(KC_MFFD)
#define MM_FN_M   LT(_MACFN, KC_MPLY)
#define MM_FN_W   LT(_WINFN, KC_MPLY)
#define MM_RSFT   RSFT_T(KC_MUTE)
// MacOS
#define MC_POWR   KC_POWER             // Mac Power alias
#define MC_SLPD   LCTL(LSFT(KC_POWER)) // Sleep Display
#define MC_MSSN   LCTL(KC_UP)          // Mission Control
#define MC_LHPD   KC_F13               // Launchpad: Configure karabiner for F13 -> Launchpad
#define MC_CMTB   LGUI(KC_TAB)         // Basic CMD+TAB
#define CLS_TAB   LGUI(KC_W)           // Cmd+W: Closes Tab
#define REO_TAB   LGUI(LSFT(KC_W))     // Shift+Cmd+T: Reopen Last Tab
#define NXT_TAB   LCTL(KC_TAB)         // Control+Tab: Next Tab
#define PRV_TAB   LCTL(LSFT(KC_TAB))   // Shift+Control+Tab: Previous Tab
#define MC_PLYR   LGUI(KC_F8)          // Focuses current Media Player
// Reverse scrolling for using with macOS Natural Scrolling.
#define MC_WH_U   KC_WH_D
#define MC_WH_D   KC_WH_U
#define MC_WH_L   KC_WH_R
#define MC_WH_R   KC_WH_L
// Windows
#define WN_LOCK   LGUI(KC_L)           // Lock Computer
#define WN_TSKM   LCTL(LALT(KC_DEL))   // Task Manager (Ctrl+Alt+Del)

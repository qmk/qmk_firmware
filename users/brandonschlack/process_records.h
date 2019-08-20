#pragma once
#include "brandonschlack.h"

// Macros
enum custom_keycodes {
    KC_MAKE = SAFE_RANGE,
    CMD_TAB,
    TG_NAVI,
    TG_REDR,
    TG_MEDA,
    TG_KYPD,
    RGB_LYR,
    RGB_THEME_FORWARD,
    RGB_THEME_REVERSE,
    KEYMAP_SAFE_RANGE
};

bool process_record_keymap(uint16_t keycode, keyrecord_t *record);
void matrix_scan_cmd_tab(void);

// Useful Defines
#define HY_CAPS   ALL_T(KC_CAPS)
#define TG_MAGC   TG(_MAGIC)
#if RGB_ENABLE
#define TG_LGHT   TG(_LIGHT)
#endif
// Media Mod-Tap
#define MM_RGUI   RGUI_T(KC_MRWD)
#define MM_RALT   RALT_T(KC_MFFD)
#define MM_FNPY   LT(_MACFN, KC_MPLY)
#define MM_RSFT   RSFT_T(KC_MUTE)
// Arrow Mod-Tap
#define MT_RSUP   RSFT_T(KC_UP)
#define MT_RALT   RALT_T(KC_LEFT)
#define MT_RFDN   LT(_MACFN, KC_DOWN)
#define MT_RCRT   RCTL_T(KC_RGHT)
// Nav Mod-Tap
#define MT_RSPU   RSFT_T(KC_PGUP)
#define MT_RAHM   RALT_T(KC_HOME)
#define MT_RFPD   LT(_MACFN, KC_PGDN)
#define MT_RCED   RCTL_T(KC_END)

// MacOS
#define MC_POWR   KC_POWER             // Mac Power alias
#define MC_SLEP   LALT(LGUI(KC_POWER)) // Mac Sleep
#define MC_SLPD   LCTL(LSFT(KC_POWER)) // Sleep Display
#define MC_MSSN   KC_FIND              // Mission Control: Configure karabiner for find -> mission_control
#define MC_LHPD   KC_MENU              // Launchpad: Configure karabiner for menu -> Launchpad
#define MC_CMTB   LGUI(KC_TAB)         // Basic CMD+TAB
#define CLS_TAB   LGUI(KC_W)           // Cmd+W: Closes Tab
#define REO_TAB   LSFT(LGUI(KC_T))     // Shift+Cmd+T: Reopen Last Tab
#define NXT_TAB   LCTL(KC_TAB)         // Control+Tab: Next Tab
#define PRV_TAB   LSFT(LCTL(KC_TAB))   // Shift+Control+Tab: Previous Tab
#define MC_PLYR   LGUI(KC_F8)          // Focuses current Media Player
#define MC_UNDO   LGUI(KC_Z)           // Undo
#define MC_REDO   LSFT(LGUI(KC_Z))     // Redo
// Reverse scrolling for using with macOS Natural Scrolling.
#define MC_WH_U   KC_WH_D
#define MC_WH_D   KC_WH_U
#define MC_WH_L   KC_WH_R
#define MC_WH_R   KC_WH_L

// RGB Theme
#define RGB_THM   RGB_THEME_FORWARD
#define RGB_RTHM  RGB_THEME_REVERSE

void send_make_command(bool flash_bootloader);

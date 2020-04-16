#pragma once
#include "brandonschlack.h"

// Macros
enum custom_keycodes {
    QM_MAKE = SAFE_RANGE,
    QM_FLSH,
    QM_VRSN,
    QM_KYBD,
    QM_KYMP,
    CMD_TAB,
    RGB_LYR,
    RGB_THEME_FORWARD,
    RGB_THEME_REVERSE,
    KEYMAP_SAFE_RANGE
};

bool process_record_keymap(uint16_t keycode, keyrecord_t *record);
void matrix_scan_cmd_tab(void);

/**
 * QMK Defines
 * Some meta aliases for QMK features such as Mod-Taps
 * and for cleaner looking Layer Toggles
 */
/* Hyper Mod-Tap */
#define HY_ESC    ALL_T(KC_ESC)        // Hold Escape for Hyper (Shift-Control-Option-Command)
#define HY_TAB    ALL_T(KC_TAB)        // Hold Tab for Hyper (Shift-Control-Option-Command)
#define HY_CAPS   ALL_T(KC_CAPS)       // Hold Caps Lock for Hyper (Shift-Control-Option-Command)
/* Shift Mod-Tap */
#define SF_CAPS   LSFT_T(KC_CAPS)      // Hold Caps Lock for Left Shift
#define SFT_ENT   RSFT_T(KC_ENT)       // Hold Enter for Right Shift
/* Layer Aliases */
#define FN_LYR    MO(_FN1)             // Hold for FN Layer
#define LOWER     MO(_LOWER)           // Hold for LOWER Layer
#define SPC_LWR   LT(_LOWER, KC_SPC)   // Tap for Space, Hold for LOWER Layer
#define SPC_RAI   LT(_RAISE, KC_SPC)   // Tap for Space, Hold for RAISE Layer
#define RAISE     MO(_RAISE)           // Hold for RAISE Layer
#define MCO_LYR   MO(_MACRO)           // Hold for MACRO Layer
#define TG_ADJT   TG(_ADJUST)          // Toggle ADJUST Layer
#define TG_LGHT   TG(_LIGHT)           // Toggle LIGHT Layer
/**
 * Media Mod-Tap
 * Use the Mod-Tap feature for easy media controls
 * Used with >=65% layouts
 */
#define RWD_CMD   RCMD_T(KC_MPRV)      // Tap Right Command for Prev Track
#define PLY_CMD   RCMD_T(KC_MPLY)      // Tap Right Command for Play/Pause
#define FFD_OPT   ROPT_T(KC_MNXT)      // Tap Right Option for Next Track
#define PLY_FN1   LT(1, KC_MPLY)       // Tap Fn for Play/Pause
#define PLY_FN2   LT(2, KC_MPLY)       // Tap Fn2 for Play/Pause
#define PLY_MCO   LT(_MACRO, KC_MPLY)  // Tap MacroFn for Play/Pause
#define MUT_SFT   RSFT_T(KC_MUTE)      // Tap Right Shift for Mute
/**
 * Arrow Mod-Tap
 * Use the Mod-Tap feature for arrow keys
 * Mostly used for 40-60% layouts
 */
#define UP_RSFT   RSFT_T(KC_UP)        // Tap Right Shift for Up
#define LFT_OPT   ROPT_T(KC_LEFT)      // Tap Right Option for Left
#define LFT_CMD   RCMD_T(KC_LEFT)      // Tap Right Command for Left
#define DWN_FN1   LT(1, KC_DOWN)       // Tap Fn for Down
#define DWN_LWR   DWN_FN1              // Tap Lower for Down
#define DWN_FN2   LT(2, KC_DOWN)       // Tap Fn2 for Down
#define DWN_RAI   DWN_FN2              // Tap Raise for Down
#define DWN_OPT   ROPT_T(KC_DOWN)      // Tap Right Option for Down
#define RGT_OPT   ROPT_T(KC_RGHT)      // Tap Right Option for Right
#define RGT_CTL   RCTL_T(KC_RGHT)      // Tap Right Ctrl for Right
/**
 * Nav Mod-Tap
 * Use the Mod-Tap feature for nav keys (Home/End, Page Up/Down)
 * Mostly used for 40-60% layouts, on a function layer
 */
#define PGU_SFT   RSFT_T(KC_PGUP)      // Tap Right Shift for Page Up
#define HOM_OPT   ROPT_T(KC_HOME)      // Tap Right Option for Home
#define HOM_CMD   RCMD_T(KC_HOME)      // Tap Right Command for Home
#define PGD_FN1   LT(1, KC_PGDN)       // Tap Fn for Page Down
#define PGD_LWR   PGD_FN1              // Tap Lower for Page Down
#define PGD_FN2   LT(2, KC_PGDN)       // Tap Fn2 for Page Down
#define PGD_RAI   PGD_FN2              // Tap Raise for Page Down
#define END_OPT   ROPT_T(KC_END)       // Tap Right Option for End
#define END_CTL   RCTL_T(KC_END)       // Tap Right Control for End

/**
 * MacOS
 * Common shortcuts used in macOS
 * Reference: https://support.apple.com/en-us/HT201236
 */
#define MC_POWR   KC_POWER             // Power (KC_POWER)
#define MC_SLEP   LOPT(LCMD(KC_POWER)) // Sleep (Option-Command-Power)
#define MC_SLPD   LCTL(LSFT(KC_POWER)) // Sleep Display (Control-Shift-Power)
#define MC_LOCK   LCTL(LCMD(KC_Q))     // Lock Screen (Control-Command-Q)
#define MC_MSSN   KC_FIND              // Mission Control: Configure karabiner for find -> mission_control
#define MC_LHPD   KC_MENU              // Launchpad: Configure karabiner for menu -> launchpad
#define MC_CMTB   LCMD(KC_TAB)         // Command-Tab
#define MC_BACK   LCMD(KC_LBRC)        // Back (Command–Left Bracket)
#define MC_FWRD   LCMD(KC_RBRC)        // Forward (Command–Right Bracket)
#define CLS_TAB   LCMD(KC_W)           // Close Tab (Command–W)
#define REO_TAB   LSFT(LCMD(KC_T))     // Reopen Last Tab (Shift-Command-T)
#define NXT_TAB   LCTL(KC_TAB)         // Next Tab (Control-Tab)
#define PRV_TAB   LSFT(LCTL(KC_TAB))   // Previous Tab (Shift-Control-Tab)
#define NXT_WIN   LCMD(KC_GRV)         // Next Window (Control-Grave)
#define PRV_WIN   LCMD(KC_TILD)        // Previous Window (Shift-Control-Grave)
#define MC_PLYR   LCMD(KC_F8)          // Focuses current Media Player
#define MC_UNDO   LCMD(KC_Z)           // Undo (Command-Z)
#define MC_REDO   LSFT(LCMD(KC_Z))     // Redo (Shift-Command-Z)
#define OP_AFLL   HYPR(KC_BSLS)        // 1Password Autofill (Shift-Control-Option-Command-\)
#define PX_AFLL   LSFT(LOPT(KC_X))     // 1PasswordX Autofill (Shift-Option-X)
// Reverse scrolling for using with macOS Natural Scrolling.
#define MC_WH_U   KC_WH_D              // Mouse Wheel Up
#define MC_WH_D   KC_WH_U              // Mouse Wheel Down
#define MC_WH_L   KC_WH_R              // Mouse Wheel Left
#define MC_WH_R   KC_WH_L              // Mouse Wheel Right

// Macropad Defines
#if defined(IS_MACROPAD)
// Macropad Default Layer keycodes
#define DF_REDR   DF(_REEDER)          // Set Default Layer to Reeder shortcuts
#define DF_MEDA   DF(_MEDIA)           // Set Default Layer to Media controls
#define DF_NAVI   DF(_NAVI)            // Set Default Layer to Navigation shortcuts
#define DF_KBNR   DF(_KARABINER)       // Set Default Layer to Basic Macro keys
#endif

// RGB Theme
#define RGB_THM   RGB_THEME_FORWARD    // Cycle next RGB_THEME
#define RGB_RTHM  RGB_THEME_REVERSE    // Cycle previous RGB_THEME

void send_make_command(bool flash_bootloader);

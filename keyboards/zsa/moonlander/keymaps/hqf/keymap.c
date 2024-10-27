/**
 * Copyright 2024 Olivier Pons / HQF Development <olivier.pons@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * MACRO DOCUMENTATION
 * ------------------
 * This keymap supports several types of customizable macros:
 *
 * 1. SIGNATURE MACROS (M_SIGN1, M_SIGN2)
 *    Example structure:
 *    case M_SIGN1:
 *        SEND_STRING(SS_TAP(X_ENT) SS_TAP(X_ENT)   // Two newlines
 *            "Name - Role\n"                        // Basic signature
 *            "Additional Info");                    // Extra information
 *
 *    Advanced example with formatting:
 *    case M_SIGN2:
 *        PLAY_SONG(unicode_windows);               // Optional: play sound
 *        SEND_STRING(
 *            SS_TAP(X_ENT) SS_TAP(X_ENT)          // Two newlines
 *            SS_DOWN(X_LSFT) SS_TAP(X_N) SS_UP(X_LSFT) // Capital letter
 *            "ame - "                              // Continue text
 *            SS_DOWN(X_LSFT) SS_TAP(X_R) SS_UP(X_LSFT) // Another capital
 *            "ole\n"                               // Newline
 *            "https://website.com"                 // URL
 *        );
 *
 * 2. EMAIL MACROS (M_EMAIL1, M_EMAIL2)
 *    Example structure:
 *    case M_EMAIL1:
 *        PLAY_SONG(chromatic_sound); // Optional: play sound
 *        SEND_STRING(
 *            "username" // Email prefix
 *            SS_DOWN(X_RALT) SS_TAP(X_0) SS_UP(X_RALT) // @ symbol
 *            "domain.com" // Domain
 *        );
 *
 * 3. TEMPLATE MACROS (M_TPL1, M_TPL2)
 *    For frequently used code snippets or text templates:
 *    case M_TPL1:
 *        SEND_STRING(
 *            "template_text" // Your template text
 *            SS_TAP(X_ENT) // Add newline
 *            "more_text" // Continue template
 *        );
 *
 * SPECIAL CHARACTERS REFERENCE
 * --------------------------
 * @ symbol: SS_DOWN(X_RALT) SS_TAP(X_0) SS_UP(X_RALT)
 * # symbol: SS_DOWN(X_RALT) SS_TAP(X_3) SS_UP(X_RALT)
 * { symbol: SS_DOWN(X_RALT) SS_TAP(X_4) SS_UP(X_RALT)
 * [ symbol: SS_DOWN(X_RALT) SS_TAP(X_5) SS_UP(X_RALT)
 * | symbol: SS_DOWN(X_RALT) SS_TAP(X_6) SS_UP(X_RALT)
 * ` symbol: SS_DOWN(X_RALT) SS_TAP(X_7) SS_UP(X_RALT)
 * \ symbol: SS_DOWN(X_RALT) SS_TAP(X_8) SS_UP(X_RALT)
 * ~ symbol: SS_DOWN(X_RALT) SS_TAP(X_2) SS_UP(X_RALT)
 *
 * FORMATTING COMMANDS
 * -----------------
 * Newline:     SS_TAP(X_ENT)
 * Space:       SS_TAP(X_SPC)
 * Tab:         SS_TAP(X_TAB)
 * Shift+Key:   SS_DOWN(X_LSFT) SS_TAP(X_KEY) SS_UP(X_LSFT)
 * Alt+Key:     SS_DOWN(X_LALT) SS_TAP(X_KEY) SS_UP(X_LALT)
 * Ctrl+Key:    SS_DOWN(X_LCTL) SS_TAP(X_KEY) SS_UP(X_LCTL)
 */

#include QMK_KEYBOARD_H
#include "version.h"

// Include local configuration if it exists
#if __has_include("config.local.h")
    #include "config.local.h"
#else
    // Default values if config.local.h doesn't exist
    #define SIGNATURE_1 "Example Name - Role"
    #define SIGNATURE_2 "Example Name - Role\nhttps://example.com"
    #define EMAIL_1 "example@domain.com"
    #define EMAIL_2 "example@company.com"
    #define CUSTOM_SOUND SONG(STARTUP_SOUND)
    #define TEMPLATE_1 "Template 1"
    #define TEMPLATE_2 "Template 2"
    #define CUSTOM_SHORTCUT_1 SS_DOWN(X_LCTL) SS_TAP(X_A) SS_UP(X_LCTL)
    #define CUSTOM_SHORTCUT_2 SS_DOWN(X_LCTL) SS_TAP(X_B) SS_UP(X_LCTL)
#endif

/**
 * Tap Dance State Definitions
 * --------------------------
 * Defines the possible states for tap dance actions:
 * - TD_NONE: No tap dance action in progress
 * - TD_UNKNOWN: Unrecognized tap pattern
 * - TD_SINGLE_TAP: Single tap detected
 * - TD_SINGLE_HOLD: Key is being held after single tap
 * - TD_DOUBLE_TAP: Double tap detected
 * - TD_TRIPLE_TAP: Triple tap detected
 */
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_TRIPLE_TAP
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

enum {
    TD_RF, // TD_RF = Tap Dance Rapid Fire toggle
};

// Function associated with all tap dances
td_state_t cur_dance(tap_dance_state_t *state);

// Functions associated with individual tap dances
void ql_finished(tap_dance_state_t *state, void *user_data);
void ql_reset(tap_dance_state_t *state, void *user_data);

/**
 * Layer Definitions
 * ----------------
 * L_0: Base AZERTY layout
 * L_1: Symbols and Navigation layer
 * L_2: Numpad and French accents
 * L_3: Gaming/Alternative layout
 * L_4: RGB Controls
 * L_5: Sound Effects
 * L_6: Rapid Fire Gaming mode
 */
enum layers {
    L_0,
    L_1,
    L_2,
    L_3,
    L_4,
    L_5,
    L_6
};

/**
 * Custom Keycodes
 * --------------
 * M_VRSN: Version information
 * M_ATG: Advanced tag helper
 * M_SOUND00-39: Sound effect triggers
 * M_SIGN1-2: Signature templates
 * M_EMAIL1-2: Email templates
 * RF_MOUSE1-3: Rapid fire mouse buttons
 * RF_SPACE: Rapid fire spacebar
 */
enum custom_keycodes {
    M_VRSN = SAFE_RANGE,
    M_ATG,
    // Sound effects (M_SOUND00 through M_SOUND39)
    M_SOUND00,
    M_SOUND01,
    M_SOUND02,
    M_SOUND03,
    M_SOUND04,
    M_SOUND05,
    M_SOUND06,
    M_SOUND07,
    M_SOUND08,
    M_SOUND09,
    M_SOUND10,
    M_SOUND11,
    M_SOUND12,
    M_SOUND13,
    M_SOUND14,
    M_SOUND15,
    M_SOUND16,
    M_SOUND17,
    M_SOUND18,
    M_SOUND19,
    M_SOUND20,
    M_SOUND21,
    M_SOUND22,
    M_SOUND23,
    M_SOUND24,
    M_SOUND25,
    M_SOUND26,
    M_SOUND27,
    M_SOUND28,
    M_SOUND29,
    M_SOUND30,
    M_SOUND31,
    M_SOUND32,
    M_SOUND33,
    M_SOUND34,
    M_SOUND35,
    M_SOUND36,
    M_SOUND37,
    M_SOUND38,
    M_SOUND39,
    // Templates and macros
    M_SIGN1,
    M_SIGN2,
    M_EMAIL1,
    M_EMAIL2,
	// Special characters and symbols
    M_NBSP,
    M_PAR,
    M_GT,
    M_PPE,
    M_BKS,
    M_LBK,
    M_RBK,
    M_SLH,
    M_HTG,
    M_OSB,
    M_CSB,
    M_ARB,
    M_TLD,
    M_BQT,
	// French accented characters
    M_C_A,
    M_C_E,
    M_C_I,
    M_C_O,
    M_C_U,
	// Navigation shortcuts
    M_XLT,
    M_XRT,
    // Layer change sounds
    M_L4_SP,
    M_L5_SP,
    M_L6_SP,
    // Gaming features
    RF_MOUSE1,
    RF_MOUSE2,
    RF_MOUSE3,
    RF_SPACE,
};

// Key combination defines for better readability
#define LSCTL(kc) (QK_LCTL | QK_LSFT | (kc))
#define KC_SLSH KC_SLASH

// Layer shortcuts
#define L_0 0 // Default layer
#define L_1 1 // Symbols & Navigation
#define L_2 2 // Numpad & Accents
#define L_3 3 // Gaming/Alternative
#define L_4 4 // RGB Controls
#define L_5 5 // Sound Effects
#define L_6 6 // Rapid Fire Gaming

// Copy/Paste shortcuts for different systems
#define C_COPY   LCTL(KC_C)   // Classical Copy (Ctrl + C)
#define C_CUT    LCTL(KC_X)   // Classical Cut (Ctrl + X)
#define C_PASTE  LCTL(KC_V)   // Classical Paste (Ctrl + V)
#define I_COPY   LCTL(KC_INS) // Alternative Copy (Ctrl + Insert)
#define I_CUT    LSFT(KC_DEL) // Alternative Cut (Shift + Delete)
#define I_PASTE  LSFT(KC_INS) // Alternative Paste (Shift + Insert)
#define L_COPY   LSCTL(KC_C)  // Linux Copy
#define L_PASTE  LSCTL(KC_V)  // Linux Paste

#define I_PCT    LSFT(KC_QUOT) // % Percent

#define C_HTG    RALT(KC_3) // Hashtag '#'

// Navigation shortcuts
#define C_LEFT   LCTL(KC_LEFT)  // Word left
#define C_RIGHT  LCTL(KC_RIGHT) // Word right
#define X_LT     LCA(KC_LEFT)   // Linux: previous desktop
#define X_RT     LCA(KC_RIGHT)  // Linux: next desktop
#define X_MX     LCA(KC_UP)     // Linux: maximize window
#define W_LT     LGUI(KC_LEFT)  // Windows: previous desktop
#define W_RT     LGUI(KC_RIGHT) // Windows: next desktop
#define X_SB     LCA(KC_B)      // Linux: maximize window

/**
 * Note: for some macros like LT() or TG():
 *
 * LT = Momentary Layer Toggle: Switch to the selected layer when held, send
 *      the selected key when tapped QMK limits this macro to switch to layers
 *      under layer 16.
 *
 * TG = Toggle layer: Switch to a given layer.
 *      Tap this key again to return to the current layer.
 */

float ag_norm_sound          [][2] = SONG(AG_NORM_SOUND);
float ag_swap_sound          [][2] = SONG(AG_SWAP_SOUND);
float audio_off_sound        [][2] = SONG(AUDIO_OFF_SOUND);
float audio_on_sound         [][2] = SONG(AUDIO_ON_SOUND);
float campanella             [][2] = SONG(CAMPANELLA);
float caps_lock_off_sound    [][2] = SONG(CAPS_LOCK_OFF_SOUND);
float caps_lock_on_sound     [][2] = SONG(CAPS_LOCK_ON_SOUND);
float chromatic_sound        [][2] = SONG(CHROMATIC_SOUND);
float clueboard_sound        [][2] = SONG(CLUEBOARD_SOUND);
float colemak_sound          [][2] = SONG(COLEMAK_SOUND);
float dvorak_sound           [][2] = SONG(DVORAK_SOUND);
float fantasie_impromptu     [][2] = SONG(FANTASIE_IMPROMPTU);
float goodbye_sound          [][2] = SONG(GOODBYE_SOUND);
float guitar_sound           [][2] = SONG(GUITAR_SOUND);
float major_sound            [][2] = SONG(MAJOR_SOUND);
float minor_sound            [][2] = SONG(MINOR_SOUND);
float music_off_sound        [][2] = SONG(MUSIC_OFF_SOUND);
float music_on_sound         [][2] = SONG(MUSIC_ON_SOUND);
float music_scale_sound      [][2] = SONG(MUSIC_SCALE_SOUND);
float nocturne_op_9_no_1     [][2] = SONG(NOCTURNE_OP_9_NO_1);
float num_lock_off_sound     [][2] = SONG(NUM_LOCK_OFF_SOUND);
float num_lock_on_sound      [][2] = SONG(NUM_LOCK_ON_SOUND);
float ode_to_joy             [][2] = SONG(ODE_TO_JOY);
float planck_sound           [][2] = SONG(PLANCK_SOUND);
float plover_goodbye_sound   [][2] = SONG(PLOVER_GOODBYE_SOUND);
float plover_sound           [][2] = SONG(PLOVER_SOUND);
float preonic_sound          [][2] = SONG(PREONIC_SOUND);
float qwerty_sound           [][2] = SONG(QWERTY_SOUND);
float rock_a_bye_baby        [][2] = SONG(ROCK_A_BYE_BABY);
float scroll_lock_off_sound  [][2] = SONG(SCROLL_LOCK_OFF_SOUND);
float scroll_lock_on_sound   [][2] = SONG(SCROLL_LOCK_ON_SOUND);
float startup_sound          [][2] = SONG(STARTUP_SOUND);
float terminal_sound         [][2] = SONG(TERMINAL_SOUND);
float unicode_linux          [][2] = SONG(UNICODE_LINUX);
float unicode_windows        [][2] = SONG(UNICODE_WINDOWS);
float ussr_anthem            [][2] = SONG(USSR_ANTHEM);
float violin_sound           [][2] = SONG(VIOLIN_SOUND);
float voice_change_sound     [][2] = SONG(VOICE_CHANGE_SOUND);
float workman_sound          [][2] = SONG(WORKMAN_SOUND);
float tos_hymn_risen         [][2] = SONG(TOS_HYMN_RISEN);
float custom_sound           [][2] = SONG(B__NOTE(_G6), B__NOTE(_C7), W__NOTE(_G6), H__NOTE(_A6), B__NOTE(_B6), W__NOTE(_E6), W__NOTE(_E6), B__NOTE(_A6), W__NOTE(_G6), H__NOTE(_F6), B__NOTE(_G6), W__NOTE(_C6), W__NOTE(_C6), B__NOTE(_D6), W__NOTE(_D6), W__NOTE(_E6), B__NOTE(_D6), W__NOTE(_D6), W__NOTE(_G6), B__NOTE(_F6), W__NOTE(_G6), W__NOTE(_A6), B__NOTE(_B6),);

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [L_0] = LAYOUT_moonlander(
  /* ┏━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┓   ┏━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┓ */
  /* ┃   Esc   │   & 1   │   é 2   │   " 3   │   ' 4   │   ( 5   │ Goto L5 ┃   ┃  Pscr   │   - 6   │   è 7   │   _ 8   │   ç 9   │   à 0   │  Bkspc  ┃ */
       KC_ESC  ,  KC_1   ,  KC_2   ,  KC_3   ,  KC_4   ,  KC_5   , M_L5_SP ,     KC_PSCR , KC_6   ,  KC_7   ,  KC_8   ,  KC_9   ,  KC_0   ,  KC_BSPC ,
  /* ┠─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┨   ┠─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┨ */
  /* ┃   Tab   │   a A   │   z Z   │   e E   │   r R   │   t T   │   Del   ┃   ┃  Bkspc  │   y Y   │   u U   │   i I   │   o O   │   p P   │   ^ ¨   ┃ */
       KC_TAB  ,  KC_Q   ,  KC_W   ,  KC_E   ,  KC_R   ,  KC_T   , KC_DEL  ,     KC_BSPC ,  KC_Y   ,  KC_U   ,  KC_I   ,  KC_O   ,  KC_P   , KC_LBRC ,
  /* ┠─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┨   ┠─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┨ */
  /* ┃  Bkspc  │   q Q   │   s S   │   d D   │   f F   │   g G   │   Del   ┃   ┃ RShft ⇧ │   h H   │   j J   │   k K   │   l L   │   m M   │ Enter ⏎ ┃ */
       KC_BSPC ,  KC_A   ,  KC_S   ,  KC_D   ,  KC_F   ,  KC_G   , KC_DEL  ,     KC_RSFT ,  KC_H   ,  KC_J   ,  KC_K   ,  KC_L   , KC_SCLN , KC_ENT  ,
  /* ┠─────────┼─────────┼─────────┼─────────┼─────────┼─────────┲━━━━━━━━━┛   ┗━━━━━━━━━┱─────────┼─────────┼─────────┼─────────┼─────────┼─────────┨ */
  /* ┃ LShft ⇧ │   w W   │   x X   │   c C   │   v V   │   b B   ┃                       ┃   n N   │   , ?   │   ; .   │   : /   │   ! §   │ RShft ⇧ ┃ */
       KC_LSFT ,  KC_Z   ,  KC_X   ,  KC_C   ,  KC_V   ,  KC_B   ,                          KC_N   ,  KC_M   , KC_COMM , KC_DOT  , KC_SLSH , KC_RSFT,
  /* ┠─────────┼─────────┼─────────┼─────────┼─────────┲━━━━━━━━━┛┏━━━━━━━━━┓ ┏━━━━━━━━━┓┗━━━━━━━━━┱─────────┼─────────┼─────────┼─────────┼─────────┨ */
  /* ┃  LCtl   │         │   LAlt  │   Del   │   Del   ┃          ┃ Goto L4 ┃ ┃  <> </> ┃          ┃   Spc   │   RSft  │   RAlt  │   RGui  │   RCtl  ┃ */
       KC_LCTL , KC_MEH  , KC_LALT , KC_DEL  , KC_DEL  ,           TD(TD_RF),    M_ATG  ,            KC_SPC  , KC_RSFT , KC_RALT , KC_RGUI , KC_RCTL ,
  /* ┗━━━━━━━━━┷━━━━━━━━━┷━━━━━━━━━┷━━━━━━━━━┷━━━━━━━━━┛          ┠─────────┨ ┠─────────┨          ┗━━━━━━━━━┷━━━━━━━━━┷━━━━━━━━━┷━━━━━━━━━┷━━━━━━━━━┛ */
  /*                                          ┏━━━━━━━━━┯━━━━━━━━━╃─────────┨ ┠─────────╄━━━━━━━━━┯━━━━━━━━━┓                                          */
  /*                                          ┃   ~L3   │   ~L2   │  Lgui   ┃ ┃  Nbsp   │   ~L2   │  ~L1    ┃                                          */
                                                MO(L_3) , MO(L_2) , KC_LGUI ,   M_NBSP  , MO(L_2) , MO(L_1)
  /*                                          ┗━━━━━━━━━┷━━━━━━━━━┷━━━━━━━━━┛ ┗━━━━━━━━━┷━━━━━━━━━┷━━━━━━━━━┛                                          */
    ),

    [L_1] = LAYOUT_moonlander(
  /* ┏━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┓   ┏━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┓ */
  /* ┃   Esc   │    f①   │    f②   │    f③   │    f④   │    f⑤   │    f⑥   ┃   ┃   f⑦    │    f⑧   │    f⑨   │   f⑩    │   f⑪    │   f⑫    │  Bkspc  ┃ */
       _______ ,  KC_F1  ,  KC_F2  ,  KC_F3  ,  KC_F4  ,  KC_F5  ,  KC_F6  ,      KC_F7  ,  KC_F8  ,  KC_F9  ,  KC_F10 ,  KC_F11 ,  KC_F12 , KC_BSPC ,
  /* ┠─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┨   ┠─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┨ */
  /* ┃    -    │    \    │    *    │    $    │    {    │    }    │    ~    ┃   ┃  Sign.  │  PgUp   │ Ctrl ←  │    ↑    │ Ctrl →  │  PgDn   │   ^ ¨   ┃ */
       _______ ,  M_BKS  , KC_BSLS , KC_RBRC ,  M_LBK  ,  M_RBK  ,  M_TLD  ,     M_SIGN1 , KC_PGUP , C_LEFT  ,  KC_UP  , C_RIGHT , KC_PGDN , KC_LBRC ,
  /* ┠─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┨   ┠─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┨ */
  /* ┃    -    │    =    │    |    │    /    │    (    │    )    │         ┃   ┃  Email  │   Home  │    ←    │    ↓    │    →    │   End   │ Enter ⏎ ┃ */
        C_HTG  , KC_EQL  ,  M_PPE  ,  M_SLH  ,  KC_5   , KC_MINS ,  I_PCT  ,     M_EMAIL2, KC_HOME , KC_LEFT , KC_DOWN , KC_RGHT , KC_END  , KC_PENT ,
  /* ┠─────────┼─────────┼─────────┼─────────┼─────────┼─────────┲━━━━━━━━━┛   ┗━━━━━━━━━┱─────────┼─────────┼─────────┼─────────┼─────────┼─────────┨ */
  /* ┃ LShft ⇧ │    <    │    @    │    >    │    [    │    ]    ┃                       ┃   n N   │   Bspc  │   Del   │  PgDn   │         │ RShft ⇧ ┃ */
       _______ , KC_NUBS ,  M_ARB  ,  M_GT   ,  M_OSB  ,  M_CSB  ,                         _______ , KC_BSPC , KC_DEL  , KC_PGDN , _______ , _______ ,
  /* ┠─────────┼─────────┼─────────┼─────────┼─────────┲━━━━━━━━━┛┏━━━━━━━━━┓ ┏━━━━━━━━━┓┗━━━━━━━━━┱─────────┼─────────┼─────────┼─────────┼─────────┨ */
  /* ┃         │         │         │         │         ┃          ┃         ┃ ┃         ┃          ┃   Spc   │         │         │         │         ┃ */
       _______ , _______ , _______ , _______ , _______ ,            _______ ,   _______ ,            KC_SPC  , _______ , _______ , _______ , _______ ,
  /* ┗━━━━━━━━━┷━━━━━━━━━┷━━━━━━━━━┷━━━━━━━━━┷━━━━━━━━━┛          ┠─────────┨ ┠─────────┨          ┗━━━━━━━━━┷━━━━━━━━━┷━━━━━━━━━┷━━━━━━━━━┷━━━━━━━━━┛ */
  /*                                          ┏━━━━━━━━━┯━━━━━━━━━┛         ┃ ┃         ┗━━━━━━━━━━━━━━━━━━━┓                                          */
                                                _______ , _______ , _______ ,   _______ , _______ , _______
  /*                                          ┗━━━━━━━━━┷━━━━━━━━━┷━━━━━━━━━┛ ┗━━━━━━━━━┷━━━━━━━━━┷━━━━━━━━━┛                                          */
    ),

    [L_2] = LAYOUT_moonlander(
  /* ┏━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┓   ┏━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┓ */
  /* ┃         │         │         │         │         │         │         ┃   ┃  CAPS   │   NUM   │   NUM   │    /    │    *    │   P-    │  Bkspc  ┃ */
       _______ , _______ , _______ , _______ , _______ , _______ , _______ ,     KC_CAPS , KC_NUM  , KC_NUM  , KC_PSLS , KC_PAST , KC_PMNS , KC_BSPC ,
  /* ┠─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┨   ┠─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┨ */
  /* ┃         │         │         │ CtAlt↑  │    û    │    ù    │    ~    ┃   ┃ Sign. L │  Copy   │   P7    │   P8    │   P9    │   P+    │   ^ ¨   ┃ */
       _______ , _______ , _______ ,  X_MX   ,  M_C_U  , KC_QUOT ,  M_TLD  ,     M_SIGN2 , _______ ,  KC_P7  ,  KC_P8  ,  KC_P9  , KC_PPLS , _______ ,
  /* ┠─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┨   ┠─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┨ */
  /* ┃   ()    │    -    │ CtAlt←  │ CtAltB  │ CtAlt→  │    ù    │    ù    ┃   ┃ Sign. L │  Home   │   P4    │   P5    │   P6    │   P+    │ PEnt  ⏎ ┃ */
        M_PAR  , _______ ,  X_LT   ,  X_SB   ,  X_RT   , KC_QUOT , KC_QUOT ,     M_EMAIL1, KC_HOME ,  KC_P4  ,  KC_P5  ,  KC_P6  , KC_PPLS , KC_PENT ,
  /* ┠─────────┼─────────┼─────────┼─────────┼─────────┼─────────┲━━━━━━━━━┛   ┗━━━━━━━━━┱─────────┼─────────┼─────────┼─────────┼─────────┼─────────┨ */
  /* ┃         │         │         │         │         │         ┃                       ┃         │         │         │         │         │         ┃ */
  /* ┃    -    │    â    │    ê    │    î    │    ô    │   ``    ┃                       ┃    -    │   P1    │   P2    │   P3    │ PEnt  ⏎ │ RShft ⇧ ┃ */
       _______ ,  M_C_A  ,  M_C_E  ,  M_C_I  ,  M_C_O  , M_BQT   ,                         _______ ,  KC_P1  ,  KC_P2  ,  KC_P3  , KC_PENT , _______ ,
  /* ┠─────────┼─────────┼─────────┼─────────┼─────────┲━━━━━━━━━┛┏━━━━━━━━━┓ ┏━━━━━━━━━┓┗━━━━━━━━━┱─────────┼─────────┼─────────┼─────────┼─────────┨ */
  /* ┃         │         │         │         │         ┃          ┃         ┃ ┃         ┃          ┃   P0    │    .    │         │         │         ┃ */
       _______ , _______ , _______ , _______ , _______ ,            _______ ,   _______ ,             KC_P0  , KC_PDOT , _______ , _______ , _______ ,
  /* ┗━━━━━━━━━┷━━━━━━━━━┷━━━━━━━━━┷━━━━━━━━━┷━━━━━━━━━┛          ┠─────────┨ ┠─────────┨          ┗━━━━━━━━━┷━━━━━━━━━┷━━━━━━━━━┷━━━━━━━━━┷━━━━━━━━━┛ */
  /*                                          ┏━━━━━━━━━┯━━━━━━━━━┛         ┃ ┃         ┗━━━━━━━━━━━━━━━━━━━┓                                          */
                                                _______ , _______ , _______ ,   _______ , _______ , _______
  /*                                          ┗━━━━━━━━━┷━━━━━━━━━┷━━━━━━━━━┛ ┗━━━━━━━━━┷━━━━━━━━━┷━━━━━━━━━┛                                          */
    ),

    [L_3] = LAYOUT_moonlander(
  /* Copy/paste + all Linux flavors for my left hand                           Right hand = moving cursor + cut/copy/paste                             */
  /* ┏━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┓   ┏━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┓ */
  /* ┃   Esc   │    f①   │    f②   │    f③   │    f④   │    f⑤   │    f⑥   ┃   ┃   f⑦    │    f⑧   │    f⑨   │   f⑩    │   f⑪    │   f⑫    │  Bkspc  ┃ */
       _______ ,  KC_F1  ,  KC_F2  ,  KC_F3  ,  KC_F4  ,  KC_F5  ,  KC_F6  ,      KC_F7  ,  KC_F8  ,  KC_F9  ,  KC_F10 ,  KC_F11 ,  KC_F12 , KC_BSPC ,
  /* ┠─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┨   ┠─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┨ */
  /* ┃    -    │    \    │ C-Copy  │ C-Paste │ L-Copy  │ L-Paste │    ~    ┃   ┃  Bkspc  │  PgUp   │ Ctrl ←  │    ↑    │ Ctrl →  │  PgDn   │   ^ ¨   ┃ */
       _______ ,  M_BKS  , C_COPY  , C_PASTE , L_COPY  , L_PASTE ,  M_TLD  ,     KC_BSPC , KC_PGUP , C_LEFT  ,  KC_UP  , C_RIGHT , KC_PGDN , KC_LBRC ,
  /* ┠─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┨   ┠─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┨ */
  /* ┃    -    │    =    │  C-Cut  │ C-Paste │ I-Copy  │ I-Paste │   Del   ┃   ┃ RShft ⇧ │   Home  │    ←    │    ↓    │    →    │   End   │ Enter ⏎ ┃ */
        C_HTG  , KC_EQL  ,  C_CUT  , C_PASTE , I_COPY  , I_PASTE , KC_DEL  ,     KC_RSFT , KC_HOME , KC_LEFT , KC_DOWN , KC_RGHT , KC_END  , KC_PENT ,
  /* ┠─────────┼─────────┼─────────┼─────────┼─────────┼─────────┲━━━━━━━━━┛   ┗━━━━━━━━━┱─────────┼─────────┼─────────┼─────────┼─────────┼─────────┨ */
  /* ┃ LShft ⇧ │    <    │    @    │    >    │  I-Cut  │ I-Paste ┃                       ┃   n N   │   Bspc  │   Del   │  PgDn   │         │ RShft ⇧ ┃ */
       _______ , KC_NUBS ,  M_ARB  ,  M_GT   ,  I_CUT  , I_PASTE ,                         _______ , KC_BSPC , KC_DEL  , KC_PGDN , _______ , _______ ,
  /* ┠─────────┼─────────┼─────────┼─────────┼─────────┲━━━━━━━━━┛┏━━━━━━━━━┓ ┏━━━━━━━━━┓┗━━━━━━━━━┱─────────┼─────────┼─────────┼─────────┼─────────┨ */
  /* ┃         │         │         │         │         ┃          ┃         ┃ ┃         ┃          ┃   Spc   │ I-Copy  │ I-Paste │         │         ┃ */
       _______ , _______ , _______ , _______ , _______ ,            _______ ,   _______ ,            KC_SPC  , I_COPY  , I_PASTE , _______ , _______ ,
  /* ┗━━━━━━━━━┷━━━━━━━━━┷━━━━━━━━━┷━━━━━━━━━┷━━━━━━━━━┛          ┠─────────┨ ┠─────────┨          ┗━━━━━━━━━┷━━━━━━━━━┷━━━━━━━━━┷━━━━━━━━━┷━━━━━━━━━┛ */
  /*                                          ┏━━━━━━━━━┯━━━━━━━━━┛         ┃ ┃         ┗━━━━━━━━━━━━━━━━━━━┓                                          */
                                                _______ , _______ , _______ ,   _______ , _______ , _______
  /*                                          ┗━━━━━━━━━┷━━━━━━━━━┷━━━━━━━━━┛ ┗━━━━━━━━━┷━━━━━━━━━┷━━━━━━━━━┛                                          */
    ),

    [L_4] = LAYOUT_moonlander(

  /* RGB_M_P  | Static (no animation) mode                                     */
  /* RGB_M_B  | Breathing animation mode                                       */
  /* RGB_M_R  | Rainbow animation mode                                         */
  /* RGB_M_SW | Swirl animation mode                                           */
  /* RGB_M_SN | Snake animation mode                                           */
  /* RGB_M_K  | "Knight Rider" animation mode                                  */
  /* RGB_M_X  | Christmas animation mode                                       */
  /* RGB_M_G  | Static gradient animation mode                                 */
  /* RGB_M_T  | Red,Green,Blue test animation mode                             */
  /* RGB_HUI  | Increase hue, decrease hue when Shift is held                  */
  /* RGB_HUD  | Decrease hue, increase hue when Shift is held                  */
  /* RGB_SAI  | Increase saturation, decrease saturation when Shift is held    */
  /* RGB_SAD  | Decrease saturation, increase saturation when Shift is held    */
  /* RGB_VAI  | Increase value (brightness), decrease value when Shift is held */
  /* RGB_VAD  | Decrease value (brightness), increase value when Shift is held */

  /* ┏━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┓   ┏━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┓ */
  /* ┃ A on/off│         │         │         │         │         │         ┃   ┃         │         │         │         │         │         │         ┃ */
       RGB_TOG , _______ , _______ , _______ , _______ , _______ , _______ ,     _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
  /* ┠─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┨   ┠─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┨ */
  /* ┃         │         │         │         │         │         │         ┃   ┃         │         │         │         │         │         │         ┃ */
       RGB_M_P , RGB_M_SW, RGB_M_X , _______ , RGB_SAI , RGB_SAD , _______ ,     _______ , _______ ,  AU_ON  , MU_ON   , CK_ON   , _______ , _______ ,
  /* ┠─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┨   ┠─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┨ */
  /* ┃         │         │         │         │         │         │         ┃   ┃         │         │         │(Audio/J)│(Click/J)│         │         ┃ */
       RGB_M_B , RGB_M_SN, RGB_M_G , _______ , RGB_VAI , RGB_VAD , _______ ,     _______ , _______ ,  AU_OFF , MU_OFF  , CK_OFF  , _______ , _______ ,
  /* ┠─────────┼─────────┼─────────┼─────────┼─────────┼─────────┲━━━━━━━━━┛   ┗━━━━━━━━━┱─────────┼─────────┼─────────┼─────────┼─────────┼─────────┨ */
  /* ┃         │         │         │         │         │         ┃                       ┃         │         │         │         │         │         ┃ */
       RGB_M_R , RGB_M_K , RGB_M_T , _______ , RGB_HUI , RGB_HUD ,                         _______ , _______ , MU_NEXT , CK_UP   , _______ , _______ ,
  /* ┠─────────┼─────────┼─────────┼─────────┼─────────┲━━━━━━━━━┛┏━━━━━━━━━┓ ┏━━━━━━━━━┓┗━━━━━━━━━┱─────────┼─────────┼─────────┼─────────┼─────────┨ */
  /* ┃         │         │         │         │         ┃          ┃ Goto L4 ┃ ┃         ┃          ┃         │         │         │         │         ┃ */
       _______ , _______ , _______ , _______ , _______ ,           TD(TD_RF),   _______ ,            _______ , MU_TOGG , CK_DOWN , _______ , _______ ,
  /* ┗━━━━━━━━━┷━━━━━━━━━┷━━━━━━━━━┷━━━━━━━━━┷━━━━━━━━━┛          ┠─────────┨ ┠─────────┨          ┗━━━━━━━━━┷━━━━━━━━━┷━━━━━━━━━┷━━━━━━━━━┷━━━━━━━━━┛ */
  /*                                          ┏━━━━━━━━━┯━━━━━━━━━┛         ┃ ┃         ┗━━━━━━━━━━━━━━━━━━━┓                                          */
                                               RGB_RMOD , RGB_MOD , _______ ,   _______ , _______ , _______
  /*                                          ┗━━━━━━━━━┷━━━━━━━━━┷━━━━━━━━━┛ ┗━━━━━━━━━┷━━━━━━━━━┷━━━━━━━━━┛                                          */
      ),

    [L_5] = LAYOUT_moonlander(

  /* ┏━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┓   ┏━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┓ */
  /* ┃         │         │         │         │         │         │ Goto L0 ┃   ┃         │         │         │         │         │         │         ┃ */
       _______ ,M_SOUND00,M_SOUND01,M_SOUND02,M_SOUND03,M_SOUND04, M_L5_SP,      _______ ,M_SOUND20,M_SOUND21,M_SOUND22,M_SOUND23,M_SOUND24, _______ ,
  /* ┠─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┨   ┠─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┨ */
  /* ┃         │         │         │         │         │         │         ┃   ┃         │         │         │         │         │         │         ┃ */
       _______ ,M_SOUND05,M_SOUND06,M_SOUND07,M_SOUND08,M_SOUND09, _______ ,     _______ ,M_SOUND25,M_SOUND26,M_SOUND27,M_SOUND28,M_SOUND29, _______ ,
  /* ┠─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┨   ┠─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┨ */
  /* ┃         │         │         │         │         │         │         ┃   ┃         │         │         │         │         │         │         ┃ */
       _______ ,M_SOUND10,M_SOUND11,M_SOUND12,M_SOUND13,M_SOUND14, _______ ,     _______ ,M_SOUND30,M_SOUND31,M_SOUND32,M_SOUND33,M_SOUND34, _______ ,
  /* ┠─────────┼─────────┼─────────┼─────────┼─────────┼─────────┲━━━━━━━━━┛   ┗━━━━━━━━━┱─────────┼─────────┼─────────┼─────────┼─────────┼─────────┨ */
  /* ┃         │         │         │         │         │         ┃                       ┃         │         │         │         │         │         ┃ */
       _______ ,M_SOUND15,M_SOUND16,M_SOUND17,M_SOUND18,M_SOUND19,                        M_SOUND35,M_SOUND36,M_SOUND37,M_SOUND38,M_SOUND39, _______ ,
  /* ┠─────────┼─────────┼─────────┼─────────┼─────────┲━━━━━━━━━┛┏━━━━━━━━━┓ ┏━━━━━━━━━┓┗━━━━━━━━━┱─────────┼─────────┼─────────┼─────────┼─────────┨ */
  /* ┃         │         │         │         │         ┃          ┃         ┃ ┃         ┃          ┃         │         │         │         │         ┃ */
       _______ , _______ , _______ , _______ , _______ ,            _______ ,   _______ ,            _______ , _______ , _______ , _______ , _______ ,
  /* ┗━━━━━━━━━┷━━━━━━━━━┷━━━━━━━━━┷━━━━━━━━━┷━━━━━━━━━┛          ┠─────────┨ ┠─────────┨          ┗━━━━━━━━━┷━━━━━━━━━┷━━━━━━━━━┷━━━━━━━━━┷━━━━━━━━━┛ */
  /*                                          ┏━━━━━━━━━┯━━━━━━━━━┛         ┃ ┃         ┗━━━━━━━━━━━━━━━━━━━┓                                          */
                                                _______ , _______ , _______ ,   _______ , _______ , _______
  /*                                          ┗━━━━━━━━━┷━━━━━━━━━┷━━━━━━━━━┛ ┗━━━━━━━━━┷━━━━━━━━━┷━━━━━━━━━┛                                          */
      ),
    [L_6] = LAYOUT_moonlander(
  /* ┏━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┓   ┏━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┯━━━━━━━━━┓ */
  /* ┃   Esc   │   & 1   │   é 2   │   " 3   │   ' 4   │   ( 5   │ Goto L0 ┃   ┃  Pscr   │   - 6   │   è 7   │   _ 8   │   ç 9   │   à 0   │  Bkspc  ┃ */
       KC_ESC  ,  KC_1   ,  KC_2   ,  KC_3   ,  KC_4   ,  KC_5   , M_L6_SP ,     KC_PSCR , KC_6   ,  KC_7   ,  KC_8   ,  KC_9   ,  KC_0   ,  KC_BSPC ,
  /* ┠─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┨   ┠─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┨ */
  /* ┃   Tab   │   a A   │   z Z   │   e E   │   r R   │   t T   │   Del   ┃   ┃  Bkspc  │   y Y   │   u U   │   i I   │   o O   │   p P   │   ^ ¨   ┃ */
       KC_TAB  ,  KC_Q   ,  KC_W   ,  KC_E   ,  KC_R   ,  KC_T   , KC_DEL  ,     KC_BSPC ,  KC_Y   ,  KC_U   ,  KC_I   ,  KC_O   ,  KC_P   , KC_LBRC ,
  /* ┠─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┨   ┠─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┨ */
  /* ┃         │   q Q   │   s S   │   d D   │   f F   │   g G   │   Del   ┃   ┃ RShft ⇧ │   h H   │   j J   │   k K   │   l L   │   m M   │ Enter ⏎ ┃ */
       _______ ,  KC_A   ,  KC_S   ,  KC_D   ,  KC_F   ,  KC_G   , KC_DEL  ,     KC_RSFT ,  KC_H   ,  KC_J   ,  KC_K   ,  KC_L   , KC_SCLN , KC_ENT  ,
  /* ┠─────────┼─────────┼─────────┼─────────┼─────────┼─────────┲━━━━━━━━━┛   ┗━━━━━━━━━┱─────────┼─────────┼─────────┼─────────┼─────────┼─────────┨ */
  /* ┃         │   w W   │   x X   │   c C   │   v V   │   b B   ┃                       ┃   n N   │   , ?   │   ; .   │   : /   │   ! §   │ RShft ⇧ ┃ */
       _______ ,  KC_Z   ,  KC_X   ,  KC_C   ,  KC_V   ,  KC_B   ,                          KC_N   ,  KC_M   , KC_COMM , KC_DOT  , KC_SLSH , KC_RSFT,
  /* ┠─────────┼─────────┼─────────┼─────────┼─────────┲━━━━━━━━━┛┏━━━━━━━━━┓ ┏━━━━━━━━━┓┗━━━━━━━━━┱─────────┼─────────┼─────────┼─────────┼─────────┨ */
  /* ┃  LCtl   │         │   LAlt  │   Del   │   Del   ┃          ┃ Goto L4 ┃ ┃  <> </> ┃          ┃   Spc   │   RSft  │   RAlt  │   RGui  │   RCtl  ┃ */
       KC_LCTL , KC_MEH  , KC_LALT , KC_DEL  , KC_DEL  ,           TD(TD_RF),    M_ATG  ,            RF_SPACE, KC_RSFT , KC_RALT , KC_RGUI , KC_RCTL ,
  /* ┗━━━━━━━━━┷━━━━━━━━━┷━━━━━━━━━┷━━━━━━━━━┷━━━━━━━━━┛          ┠─────────┨ ┠─────────┨          ┗━━━━━━━━━┷━━━━━━━━━┷━━━━━━━━━┷━━━━━━━━━┷━━━━━━━━━┛ */
  /*                                          ┏━━━━━━━━━┯━━━━━━━━━╃─────────┨ ┠─────────╄━━━━━━━━━┯━━━━━━━━━┓                                          */
  /*                                          ┃ RapidF3 │ RapidF1 │ RapidF2 ┃ ┃  Nbsp   │   ~L2   │  ~L1    ┃                                          */
                                               RF_MOUSE3,RF_MOUSE1,RF_MOUSE2,   M_NBSP  , MO(L_2) , MO(L_1)
  /*                                          ┗━━━━━━━━━┷━━━━━━━━━┷━━━━━━━━━┛ ┗━━━━━━━━━┷━━━━━━━━━┷━━━━━━━━━┛                                          */
    ),
};

uint16_t rapid_fire = 0;
uint16_t rapid_fire_double = 0;
uint16_t rapid_fire_double_wait = 0;

void matrix_scan_user(void) {
    if (rapid_fire_double) {
        switch (rapid_fire_double_wait) {
            case 0:
                tap_code16(KC_MS_BTN1);
                tap_code16(KC_MS_BTN2);
                break;
            case 32:
                break;
            case 48:
                break;
            case 64:
                break;
            case 96:
                break;
            case 128:
                break;
        }
        rapid_fire_double_wait = (++rapid_fire_double) % 3;
    } else if (rapid_fire) {
        tap_code16(rapid_fire);
    }
}
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
        case RF_MOUSE1:
            rapid_fire = KC_MS_BTN1;
            return false;
        case RF_MOUSE2:
            rapid_fire = KC_MS_BTN2;
            return false;
        case RF_MOUSE3:
            rapid_fire = KC_MS_BTN1;
            rapid_fire_double = KC_MS_BTN2;
            rapid_fire_double_wait = 15;
            return false;
        case RF_SPACE:
            rapid_fire = KC_SPACE;
            return false;
        case M_L4_SP:
            PLAY_SONG(dvorak_sound);
            layer_invert(L_4);
            return false;
        case M_L5_SP:
            PLAY_SONG(colemak_sound);
            layer_invert(L_5);
            return false;
        case M_L6_SP:
            PLAY_SONG(goodbye_sound);
            layer_invert(L_6);
            return false;
        case M_VRSN:
            SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
            return false;
        case M_ATG: // Advanced tag <></>
             SEND_STRING( \
                SS_DOWN(X_RCTL) SS_DOWN(X_LSFT) SS_TAP(X_LEFT) SS_UP(X_LSFT) \
                SS_TAP(X_X) SS_UP(X_RCTL) \
                SS_TAP(X_NUBS) \
                SS_DOWN(X_RCTL) SS_TAP(X_V) SS_UP(X_RCTL) \
                SS_DOWN(X_RSFT) SS_TAP(X_NUBS) SS_UP(X_RSFT) \
                SS_TAP(X_NUBS) \
                SS_DOWN(X_RSFT) SS_TAP(X_DOT) SS_UP(X_RSFT) \
                SS_DOWN(X_RCTL) SS_TAP(X_V) SS_UP(X_RCTL) \
                SS_DOWN(X_RSFT) SS_TAP(X_NUBS) SS_UP(X_RSFT) \
                SS_TAP(X_LEFT)SS_DOWN(X_RCTL) SS_TAP(X_LEFT) SS_UP(X_RCTL) \
                SS_TAP(X_LEFT) SS_TAP(X_LEFT));
             return false;
        case M_SOUND00:
            PLAY_SONG(ode_to_joy);
            return false;
        case M_SOUND01:
            PLAY_SONG(rock_a_bye_baby);
            return false;
        case M_SOUND02:
            PLAY_SONG(clueboard_sound);
            return false;
        case M_SOUND03:
            PLAY_SONG(startup_sound);
            return false;
        case M_SOUND04:
            PLAY_SONG(goodbye_sound);
            return false;
        case M_SOUND05:
            PLAY_SONG(planck_sound);
            return false;
        case M_SOUND06:
            PLAY_SONG(preonic_sound);
            return false;
        case M_SOUND07:
            PLAY_SONG(qwerty_sound);
            return false;
        case M_SOUND08:
            PLAY_SONG(colemak_sound);
            return false;
        case M_SOUND09:
            PLAY_SONG(dvorak_sound);
            return false;
        case M_SOUND10:
            PLAY_SONG(workman_sound);
            return false;
        case M_SOUND11:
            PLAY_SONG(plover_sound);
            return false;
        case M_SOUND12:
            PLAY_SONG(plover_goodbye_sound);
            return false;
        case M_SOUND13:
            PLAY_SONG(music_on_sound);
            return false;
        case M_SOUND14:
            PLAY_SONG(audio_on_sound);
            return false;
        case M_SOUND15:
            PLAY_SONG(audio_off_sound);
            return false;
        case M_SOUND16:
            PLAY_SONG(music_scale_sound);
            return false;
        case M_SOUND17:
            PLAY_SONG(music_off_sound);
            return false;
        case M_SOUND18:
            PLAY_SONG(voice_change_sound);
            return false;
        case M_SOUND19:
            PLAY_SONG(chromatic_sound);
            return false;
        case M_SOUND20:
            PLAY_SONG(major_sound);
            return false;
        case M_SOUND21:
            PLAY_SONG(minor_sound);
            return false;
        case M_SOUND22:
            PLAY_SONG(guitar_sound);
            return false;
        case M_SOUND23:
            PLAY_SONG(violin_sound);
            return false;
        case M_SOUND24:
            PLAY_SONG(caps_lock_on_sound);
            return false;
        case M_SOUND25:
            PLAY_SONG(caps_lock_off_sound);
            return false;
        case M_SOUND26:
            PLAY_SONG(scroll_lock_on_sound);
            return false;
        case M_SOUND27:
            PLAY_SONG(scroll_lock_off_sound);
            return false;
        case M_SOUND28:
            PLAY_SONG(num_lock_on_sound);
            return false;
        case M_SOUND29:
            PLAY_SONG(num_lock_off_sound);
            return false;
        case M_SOUND30:
            PLAY_SONG(ag_norm_sound);
            return false;
        case M_SOUND31:
            PLAY_SONG(ag_swap_sound);
            return false;
        case M_SOUND32:
            PLAY_SONG(unicode_windows);
            return false;
        case M_SOUND33:
            PLAY_SONG(unicode_linux);
            return false;
        case M_SOUND34:
            PLAY_SONG(terminal_sound);
            return false;
        case M_SOUND35:
            PLAY_SONG(campanella);
            return false;
        case M_SOUND36:
            PLAY_SONG(fantasie_impromptu);
            return false;
        case M_SOUND37:
            PLAY_SONG(nocturne_op_9_no_1);
            return false;
        case M_SOUND38:
            PLAY_SONG(ussr_anthem);
            return false;
        case M_SOUND39:
            PLAY_SONG(tos_hymn_risen);
            return false;

        case M_SIGN1:
            SEND_STRING(SIGNATURE_1);
            return false;
        case M_SIGN2:
            PLAY_SONG(unicode_windows);
            SEND_STRING(SIGNATURE_2);
            return false;
        case M_EMAIL1:
            PLAY_SONG(chromatic_sound);
            SEND_STRING(EMAIL_1);
            return false;
        case M_EMAIL2:
            PLAY_SONG(planck_sound);
            SEND_STRING(EMAIL_2);
            return false;
        case M_NBSP: // &nbsp;
            SEND_STRING( \
                SS_TAP(X_1) SS_TAP(X_N) SS_TAP(X_B) SS_TAP(X_S) SS_TAP(X_P) \
                SS_TAP(X_COMM));
            return false;
        case M_PAR: // ()
            SEND_STRING(SS_TAP(X_5) SS_TAP(X_MINS) SS_TAP(X_LEFT));
            return false;
        case M_GT: // > Greater than
            SEND_STRING(SS_DOWN(X_RSFT) SS_TAP(X_NUBS) SS_UP(X_RSFT));
            return false;
        case M_PPE: // | Pipe
            SEND_STRING(SS_DOWN(X_RALT) SS_TAP(X_6) SS_UP(X_RALT));
            return false;
        case M_BKS: // \ Backslash
            SEND_STRING(SS_DOWN(X_RALT) SS_TAP(X_8) SS_UP(X_RALT));
            return false;
        case M_LBK: // { Left bracket
            SEND_STRING(SS_DOWN(X_RALT) SS_TAP(X_4) SS_UP(X_RALT));
            return false;
        case M_RBK: // } Right bracket
            SEND_STRING(SS_DOWN(X_RALT) SS_TAP(X_EQL) SS_UP(X_RALT));
            return false;
        case M_SLH: // / Slash
            SEND_STRING(SS_DOWN(X_RSFT) SS_TAP(X_DOT) SS_UP(X_RSFT));
            return false;
        case M_HTG: // # Hashtag
            SEND_STRING(SS_DOWN(X_RALT) SS_TAP(X_3) SS_UP(X_RALT));
            return false;
        case M_OSB: // [ Opening Square bracket
            SEND_STRING(SS_DOWN(X_RALT) SS_TAP(X_5) SS_UP(X_RALT));
            return false;
        case M_CSB: // ] Closing Square bracket
            SEND_STRING(SS_DOWN(X_RALT) SS_TAP(X_MINS) SS_UP(X_RALT));
            return false;
        case M_ARB: // @ Arobase
            SEND_STRING(SS_DOWN(X_RALT) SS_TAP(X_0) SS_UP(X_RALT));
            return false;
        case M_TLD: // ~ Tilde
            SEND_STRING(SS_DOWN(X_RALT) SS_TAP(X_2) SS_UP(X_RALT) SS_TAP(X_SPC));
            return false;
        case M_BQT: // ` Backquote
            SEND_STRING(SS_DOWN(X_RALT) SS_TAP(X_7) SS_UP(X_RALT) SS_TAP(X_SPC) \
                SS_DOWN(X_RALT) SS_TAP(X_7) SS_UP(X_RALT) SS_TAP(X_SPC) \
                SS_TAP(X_LEFT));
            return false;
        case M_C_A: // â
            SEND_STRING(SS_TAP(X_LBRC) SS_TAP(X_Q));
            return false;
        case M_C_E: // ê
            SEND_STRING(SS_TAP(X_LBRC) SS_TAP(X_E));
            return false;
        case M_C_I: // î
            SEND_STRING(SS_TAP(X_LBRC) SS_TAP(X_I));
            return false;
        case M_C_O: // ô
            SEND_STRING(SS_TAP(X_LBRC) SS_TAP(X_O));
            return false;
        case M_C_U: // û
            SEND_STRING(SS_TAP(X_LBRC) SS_TAP(X_U));
            return false;
        case M_XLT: // LCtrl - LAlt - ←
            SEND_STRING(SS_DOWN(X_LCTL) SS_DOWN(X_LALT) SS_TAP(X_LEFT) \
                SS_UP(X_LALT) SS_UP(X_LCTL));
            return false;
        case M_XRT: // LCtrl - LAlt - →
            SEND_STRING(SS_DOWN(X_LCTL) SS_DOWN(X_LALT) SS_TAP(X_RIGHT) \
                SS_UP(X_LALT) SS_UP(X_LCTL));
            return false;

        }
    } else { // key released
        switch (keycode) {
        case RF_MOUSE1:
        case RF_MOUSE2:
        case RF_MOUSE3:
        case RF_SPACE:
            rapid_fire = 0;
            rapid_fire_double = 0;
            return false;
        }
    }
    return true;
}

/* -------------------------------------------------------------------------- */
/* Tap Dance: footer: */
// Determine the current tap dance state
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) {
            return TD_SINGLE_TAP;
        } else {
            return TD_SINGLE_HOLD;
        }
    } else if (state->count == 2) {
        return TD_DOUBLE_TAP;
    } else if (state->count == 3) {
        return TD_TRIPLE_TAP;
    }
    return TD_UNKNOWN;
}

// Initialize tap structure associated with example tap dance key
static td_tap_t ql_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void ql_finished(tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:
            // only change if not on layer 6:
            if (!layer_state_is(L_6)) {
                PLAY_SONG(dvorak_sound);
                layer_invert(L_4);
            }
            break;
        case TD_SINGLE_HOLD:
            break;
        case TD_DOUBLE_TAP:
            PLAY_SONG(guitar_sound);
            if (layer_state_is(L_6)) {
                // already set: switch it off:
                layer_off(L_6);
            } else {
                // not already set: switch it on:
                layer_on(L_6);
            }
            break;
        case TD_TRIPLE_TAP:
            PLAY_SONG(ussr_anthem);
            break;
        default:
            break;
    }
}

void ql_reset(tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    // if (ql_tap_state.state == TD_SINGLE_HOLD) {
    //     layer_off(L_3);
    // }
    ql_tap_state.state = TD_NONE;
}

// Associate our tap dance key with its functionality
tap_dance_action_t tap_dance_actions[] = {
    [TD_RF] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ql_finished, ql_reset)
};


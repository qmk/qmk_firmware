#ifndef USERSPACE
#define USERSPACE

#include "quantum.h"

// Use 7 wide characters for keymaps
#define _______ KC_TRNS
#define XXX     KC_NO

// Layers
#define _BA 0 // Base layer
#define _GA 1 // Game layer
#define _NU 2 // Numbers layer
#define _SE 3 // Settings layer
#define _MO 4 // Mouse emulation
#define _MU 5 // Music mode

// Rename mouse keys with 7 letters
#ifdef MOUSEKEY_ENABLE
#define MO_S_N  KC_MS_WH_UP
#define MO_S_S  KC_MS_WH_DOWN
#define MO_S_E  KC_MS_WH_RIGHT
#define MO_S_W  KC_MS_WH_LEFT
#define MO_N    KC_MS_UP
#define MO_S    KC_MS_DOWN
#define MO_E    KC_MS_RIGHT
#define MO_W    KC_MS_LEFT
#define MO_CL_L KC_MS_BTN1
#define MO_CL_R KC_MS_BTN2
#define MO_CL_M KC_MS_BTN3
#define MO_CL_4 KC_MS_BTN4
#define MO_CL_5 KC_MS_BTN5
#define MO_AC_0 KC_MS_ACCEL0
#define MO_AC_1 KC_MS_ACCEL1
#define MO_AC_2 KC_MS_ACCEL2
#else
#define MO_S_N  KC_NO
#define MO_S_S  KC_NO
#define MO_S_E  KC_NO
#define MO_S_W  KC_NO
#define MO_N    KC_NO
#define MO_S    KC_NO
#define MO_E    KC_NO
#define MO_W    KC_NO
#define MO_CL_L KC_NO
#define MO_CL_R KC_NO
#define MO_CL_M KC_NO
#define MO_CL_1 KC_NO
#define MO_CL_2 KC_NO
#define MO_AC_0 KC_NO
#define MO_AC_1 KC_NO
#define MO_AC_2 KC_NO
#endif

// Rename music keys with <8 letters
#ifdef AUDIO_ENABLE
#define MU_REC  KC_LCTL
#define MU_STOP KC_LALT
#define MU_PLAY KC_LGUI
#define MU_PLAY KC_LGUI
#define MU_FAST KC_UP
#define MU_SLOW KC_DOWN
#define MU_MASK KC_A
#else
#define MU_REC  KC_NO
#define MU_STOP KC_NO
#define MU_PLAY KC_NO
#define MU_PLAY KC_NO
#define MU_FAST KC_NO
#define MU_SLOW KC_NO
#define MU_MASK KC_NO
#endif

// Define non-capitalized UTF shortcuts here
#ifdef UNICODE_ENABLE
#define PHY_HBR UC(0x0127)
#define PHY_DEG UC(0x00b0)
#define CUR_LIR UC(0x20ba)
#define CUR_BIT UC(0x20bf)
#define CUR_EUR UC(0x20ac)
#define CUR_BPN UC(0x00a3)
#define CUR_YEN UC(0x00a5)
#else
#define PHY_HBR KC_NO
#define PHY_DEG KC_NO
#define CUR_LIR KC_NO
#define CUR_BIT KC_NO
#define CUR_EUR KC_NO
#define CUR_BPN KC_NO
#define CUR_YEN KC_NO
#endif

// Custom keycodes
enum userspace_custom_keycodes {
    // Unicode mode switch
    UNI_LI = SAFE_RANGE,
    UNI_WN,
    // Double keys
    DBL_SPC,
    DBL_ENT,
    DBL_ANG,
    DBL_PAR,
    DBL_SQR,
    DBL_BRC,
    DBL_QUO,
    DBL_DQT,
    DBL_GRV,
    // Diagonal mouse movements
    MO_NE,
    MO_NW,
    MO_SE,
    MO_SW,
    MO_S_NE,
    MO_S_NW,
    MO_S_SE,
    MO_S_SW,
    // Lock functionality
    K_LOCK,
    // Secret macros
    SECRET1,
    SECRET2,
    SECRET3,
    SECRET4,
};

// Do tap dancable keys
#ifdef TAP_DANCE_ENABLE
enum {
    NUG = 0,
    SEM
};
#define K_NU_GA TD(NUG)
#define K_SE_MO TD(SEM)
#else
#define K_NU_AL MO(_NU)
#define K_SE_MO MO(_SE)
#endif

// Shared keymaps
#define LAYOUT_planck_wrapper(...) LAYOUT_planck_grid(__VA_ARGS__)
#define LAYOUT_letssplit_wrapper(...) LAYOUT_ortho_4x12(__VA_ARGS__)

/* Base
 * ,------------------------------------------------------------------------.
 * | Esc |  Q  |  W  |  E  |  R  |  T  ||  Y  |  U  |  I  |  O  |  P  | Bkp |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * | Tab |  A  |  S  |  D  |  F  |  G  ||  H  |  J  |  K  |  L  | ; : | ' " |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * | Sft |  Z  |  X  |  C  |  V  |  B  ||  N  |  M  | , < | . > | / ? |Enter|
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * | Ctrl|Super| Alt |AltGr| Num |   Space    | Set | Lft | Dwn |  Up | Rght|
 * `------------------------------------------------------------------------'
 */
#define BASE \
    KC_ESC, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_BSPC, \
    KC_TAB, KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT, \
    KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_ENT,  \
    KC_LCTL,KC_LGUI,KC_LALT,KC_RALT,K_NU_AL,KC_SPC, KC_SPC, K_SE_MO,KC_LEFT,KC_DOWN,KC_UP,  KC_RGHT

/* Game layer
 * ,------------------------------------------------------------------------.
 * |     |     |     |     |     |     ||     |     |     |  ^  |     |     |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * |     |     |     |     |     |     ||     |     |  <  |  v  |  >  |     |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * |     |     |     |     |     |     ||     |     |     |     |     |     |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * |     |     |     |     |     |            |     |     |     |     |     |
 * `------------------------------------------------------------------------'
 */
#define GAME \
    _______,_______,_______,_______,_______,_______,_______,_______,_______,KC_UP,  _______,_______, \
    _______,_______,_______,_______,_______,_______,_______,_______,KC_LEFT,KC_DOWN,KC_RGHT,_______, \
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______, \
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______

/* Symbols layer
 * ,------------------------------------------------------------------------.
 * | OFF |  `  |  1  |  2  |  3  |  -  ||  !  |  @  |  #  | [ { | ] } |     |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * |     |  ~  |  4  |  5  |  6  |  =  ||  $  |  %  |  ^  | ' " | # ~ | Ins |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * |     |  |  |  7  |  8  |  9  |  0  ||  &  |  *  |  (  |  )  | \ | |     |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * |     |     |     |     |     |            |CapsL| Home|Pg Dn|Pg Up| End |
 * `------------------------------------------------------------------------'
 */
#define NUMBERS \
    _______,KC_GRV, KC_1,   KC_2,   KC_3,   KC_MINS,KC_EXLM,KC_AT,  KC_HASH,KC_LBRC KC_RBRC,KC_DEL,  \
    _______,KC_TILD KC_4,   KC_5,   KC_4,   KC_EQL  KC_DLR, KC_PERC,KC_CIRC,KC_QUOT,KC_NUHS,KC_INS,  \
    _______,KC_PIPE,KC_7,   KC_8,   KC_9,   KC_0,   KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,KC_BSLS,_______, \
    _______,_______,_______,_______,_______,_______,_______,KC_CAPS,KC_HOME,KC_PGDN,KC_PGUP,KC_END,

/* Settings layer
 * ,------------------------------------------------------------------------.
 * |     |  F1 |  F2 |  F3 |  F4 | Lin || Woke|     | Mode| Togg| BLit|Reset|
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * |     |  F5 |  F6 |  F7 |  F8 | Win ||PrtSc| Lira|     |Hue +|Sat +|Bri +|
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * |     |  F9 | F10 | F11 | F12 |Vol -||Vol +| BTC |     |Hue -|Sat -|Bri -|
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * |     |     |     |     |     |    Mute    |     | Prev| Stop|TogMu| Next|
 * `------------------------------------------------------------------------'
 */
#define SETTINGS \
    _______,KC_F1,  KC_F2,  KC_F3,  KC_F4,  UNI_LI, KC_WAKE,_______,RGB_MOD,RGB_TOG,BL_STEP,RESET, \
    _______,KC_F5,  KC_F6,  KC_F7,  KC_F8,  UNI_WN, KC_PSCR,CUR_LIR,_______,RGB_HUI,RGB_SAI,RGB_VAI, \
    _______,KC_F9,  KC_F10, KC_F11, KC_F12, KC_VOLD,KC_VOLU,CUR_BIT,_______,RGB_HUD,RGB_SAD,RGB_VAD, \
    _______,_______,_______,_______,MU_TOG, KC_MUTE,KC_MUTE,_______,KC_MPRV,KC_MSTP,KC_MPLY,KC_MNXT

/* Mouse layer
 * ,------------------------------------------------------------------------.
 * |Ulock|  \  |  ^  |  /  | Sec | Sec || Sec | Sec | |\|.| |^| | |/|.|     |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * |     |  <  |.....|  >  |Btn L|Btn 4||Btn 5|Btn R| <-- |.....| --> |     |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * |     |  /  |  v  |  \  |.....|.....||.....|.....| |/| | |v| | |\| |     |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * |     |     |     |     | LCK |   MidClk   |     |Accl0|Accl1|Accl2|     |
 * `------------------------------------------------------------------------'
 */
#define MOUSE \
    _______,MO_NW,  MO_N,   MO_NE,  SECRET1,SECRET2,SECRET3,SECRET4 MO_S_NW,MO_S_N, MO_S_NE,_______, \
    _______,MO_W,   XXX,    MO_E,   MO_CL_L,MO_CL_4,MO_CL_5,MO_CL_R,MO_S_W, XXX,    MO_S_E, _______, \
    _______,MO_SW,  MO_S,   MO_SE,  XXX,    XXX    ,XXX,    XXX,    MO_S_SW,MO_S_S, MO_S_SE,_______, \
    _______,_______,_______,_______,K_LOCK, MO_CL_M,MO_CL_M,_______,MO_AC_0,MO_AC_1,MO_AC_2,_______

/* Music layer
 * ,------------------------------------------------------------------------.
 * |.....|.....|.....|.....|.....|.....||.....|.....|.....|.....|.....|.....|
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * |.....|.....|.....|.....|.....|.....||.....|.....|.....|.....|.....|.....|
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * |.....|.....|.....|.....|.....|.....||.....|.....|.....|.....|.....|.....|
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * | slow| fast| rec | stop| togg|    Play    | Mode|.....|.....|.....|.....|
 * `------------------------------------------------------------------------'
 */
#define MUSIC \
    MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK, \
    MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK, \
    MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK, \
    MU_SLOW,MU_FAST,MU_REC, MU_STOP,MU_TOG, MU_PLAY,MU_PLAY,MU_MOD, MU_MASK,MU_MASK,MU_MASK,MU_MASK

#endif

// This is a modified version of Let's Split keyboard from bbaserdem

#pragma once

#include "quantum.h"

#define XXX     KC_NO

// Layers
#define _DV 0 // Base layer
#define _AL 1 // Alt char overlay
#define _GA 2 // Game layer
#define _NU 3 // Numbers layer
#define _SE 4 // Settings layer
#define _MO 5 // Mouse emulation
#define _MU 6 // Music mode

// Define short macros
#define UNDO    LCTL(KC_Z)
#define REDO    LCTL(KC_Y)
#define COPY    LCTL(KC_C)
#define CUT     LCTL(KC_X)
#define PASTE   LCTL(KC_V)
#define EXIT    LALT(KC_F4)
#define	CAPS	SFT_T(KC_CAPS)	


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
    // Turkish letters, with shifting
    TUR_A = SAFE_RANGE,
    TUR_C,
    TUR_G,
    TUR_I,
    TUR_O,
    TUR_S,
    TUR_U,
    // Unicode mode switch
    UNI_LI,
    UNI_WN,
    // Double keys
    DBL_SPC,
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
    // Layer switches and lock functionality
    K_MOUSE,
    K_NUMBR,
    K_LOCK,
    K_GAMES,
    // Secret macros
    SECRET1,
    SECRET2,
    SECRET3
};

// Do tap dancable semicolon key if available
#ifdef TAP_DANCE_ENABLE
enum {
    SCL = 0
};
#define MY_SCL  TD(SCL)
#else
#define MY_SCL  KC_SCLN
#endif

// Shared keymaps
#define LAYOUT_planck_wrapper(...) LAYOUT_planck_grid(__VA_ARGS__)
#define LAYOUT_letssplit_wrapper(...) LAYOUT_ortho_4x12(__VA_ARGS__)

/* Dvorak
 * ,------------------------------------------------------------------------.
 * | ' " |  ,  |  .  |  P  |  Y  | Esc || Del |  F  |  G  |  C  |  R  |  L  |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * |  A  |  O  |  E  |  U  |  I  | Bkp || Ent |  D  |  H  |  T  |  N  |  S  |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|	
 * | ; : |  Q  |  J  |  K  |  X  | Spc || SET |  B  |  M  |  W  |  V  |  Z  |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * | Ctrl|  OS | Alt | Tab | Cps | ACH || SYM | Spc | Lft |  Up | Dwn | Rght| 
 * `------------------------------------------------------------------------' */
#define DVORAK \
    KC_QUOT,KC_COMM,KC_DOT, KC_P,   KC_Y,	KC_ESC,	KC_DEL,	KC_F,   KC_G,   KC_C,   KC_R,   KC_L,    \
    KC_A,   KC_O,   KC_E,   KC_U,   KC_I,   KC_BSPC,KC_ENT, KC_D,   KC_H,   KC_T,   KC_N,   KC_S,    \
    MY_SCL, KC_Q,   KC_J,   KC_K,   KC_X,  	KC_SPC,	MO(_SE),KC_B,   KC_M,   KC_W,   KC_V,   KC_Z,    \
    KC_LCTL,KC_LGUI,KC_LALT,KC_TAB,	CAPS, 	MO(_AL),K_NUMBR,KC_SPC, KC_LEFT,KC_UP,	KC_DOWN,KC_RGHT

/* Alternative character overlay
 * ,------------------------------------------------------------------------.
 * | ` ~ | ' ' | " " | Euro|Pound|     || Del | Home| PgUp| Prn | \ | | / ?	|
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * | Redo| < > | ( ) | [ ] | { } | Alt || Ins | End |PgDwn| Scl | BTC | - _ |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * | Undo| Cut | Copy|Paste| EXIT| Shf ||     |     |     |     | Yen | = + |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * |     |     |     |     |     |     ||     |     |     |     |     |     |
 * `------------------------------------------------------------------------' */
#define ALTCHAR \
    KC_GRV,	DBL_QUO,DBL_DQT,CUR_EUR,CUR_BPN,_______,_______,KC_HOME,KC_PGUP,KC_PSCREEN,		KC_BSLASH,	KC_SLSH, \
    REDO,	DBL_ANG,DBL_PAR,DBL_SQR,DBL_BRC,KC_LALT,KC_INS,	KC_END, KC_PGDN,KC_SCROLLLOCK,	CUR_BIT,	KC_MINUS, \
    UNDO,	CUT,    COPY,   PASTE,	EXIT,	KC_LSFT,_______,_______,_______,_______,		CUR_YEN,	KC_EQUAL,   \
    _______,_______,_______,_______,_______,_______,_______,DBL_SPC,_______,_______,		_______,	_______

/* Game layer
 * ,------------------------------------------------------------------------.
 * | OFF |  Q  |  W  |  E  |  R  |  T  || Esc |  7  |  8  |  9  |NumLk|Bkspc|
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * | Tab |  A  |  S  |  D  |  F  |  G  ||  F1 |  4  |  5  |  6  |  \  | Ent |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * | Shf |  Z  |  X  |  C  |  V  |  B  ||  F2 |  1  |  2  |  3  |  ^  | MSE |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * | Ctrl| Alt |  /  |  `  | SYM | Spc ||  F5 | Ent |  0  |  <  |  v  |  >  |
 * `------------------------------------------------------------------------' */
#define GAME \
    K_GAMES,KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_ESC, KC_P7,  KC_P8,  KC_P9,  KC_NLCK,KC_BSPC, \
    KC_TAB, KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_F1,  KC_P4,  KC_P5,  KC_P6,  KC_BSLS,KC_ENT , \
    KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_F2,  KC_P1,  KC_P2,  KC_P3,  KC_UP,K_MOUSE, \
    KC_LCTL,KC_LALT,KC_SLSH,KC_GRV,	K_NUMBR,KC_SPC, KC_F5, 	KC_ENT, KC_P0,  KC_LEFT,KC_DOWN,KC_RGHT

/* Symbols layer
 * ,------------------------------------------------------------------------.
 * | OFF |  `  |  ~  |  \  |  [  |  {  ||  }  |  ]  |  -  |  _  |  =  |  +  |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * |  1  |  2  |  3  |  4  |  5  |     || LCK |  6  |  7  |  8  |  9  |  0  |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * |  !  |  @  |  #  |  $  |  %  |     ||Vol +|  ^  |  &  |  *  |  (  |  )  |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * |  |  |     |     |     |     |     ||     |     |     |     |     |     |
 * `------------------------------------------------------------------------' */
#define NUMBERS \
    K_NUMBR,KC_GRV, KC_TILD,KC_BSLS,KC_LBRC,KC_LCBR,KC_RCBR,KC_RBRC,KC_MINS,KC_UNDS,KC_EQL, KC_PLUS, \
    KC_1,   KC_2,   KC_3,   KC_4,   KC_5,	_______,K_LOCK,  KC_6,   KC_7,   KC_8,   KC_9,   KC_0,    \
    KC_EXLM,KC_AT,  KC_HASH,KC_DLR, KC_PERC,_______,KC_VOLU,KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN, \
    KC_PIPE,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______
	
/* Settings layer
 * ,------------------------------------------------------------------------.
 * |BLLed|  F1 |  F2 |  F3 |  F4 | Lin || Win | Wake|     |Hue -|Hue +|Reset|
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * |     |  F5 |  F6 |  F7 |  F8 |     ||Vol 0|     |RGBto|Sat -|Sat +|     |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * | Game|  F9 | F10 | F11 | F12 |Vol 0||     |PrtSc|RGBan|Bri -|Bri +|     |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * |Musir|     |     |     |     |Vol +||Vol -| Prev| Stop|TogMu| Next|     |
 * `------------------------------------------------------------------------' */
#define SETTINGS \
    BL_STEP,KC_F1,  KC_F2,  KC_F3,  KC_F4,  UNI_LI, UNI_WN, KC_WAKE,_______,RGB_HUD,RGB_HUI,RESET  , \
    _______,KC_F5,  KC_F6,  KC_F7,  KC_F8,  _______,KC_MUTE,_______,RGB_TOG,RGB_SAD,RGB_SAI,_______, \
    K_GAMES,KC_F9,  KC_F10, KC_F11, KC_F12, KC_MUTE,_______,KC_PSCR,RGB_MOD,RGB_VAD,RGB_VAI,_______, \
    MU_TOG, _______,_______,_______,_______,KC_VOLU,KC_VOLD,KC_MPRV,KC_MSTP,KC_MPLY,KC_MNXT,_______

/* Mouse layer
 * ,------------------------------------------------------------------------.
 * |Ulock|  \  |  ^  |  /  |.....|.....||.....|.....| |\|.| |^| | |/|.|     |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * |     |  <  | Mid |  >  |Btn 4|.....||.....|Btn 5| <-- | Mid | --> |     |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * |     |  /  |  v  |  \  |.....|.....||.....|.....| |/| | |v| | |\| | LCK |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * |     |     |     |     |     | Left||Right|     |     |Accl0|Accl1|Accl2|
 * `------------------------------------------------------------------------' */
#define MOUSE \
    K_MOUSE,MO_NW,  MO_N,   MO_NE,  XXX,    XXX    ,XXX,    XXX,    MO_S_NW,MO_S_N, MO_S_NE,_______, \
    _______,MO_W,   MO_CL_M,MO_E,   MO_CL_4,XXX    ,XXX,    MO_CL_5,MO_S_W, MO_CL_M,MO_S_E, _______, \
    _______,MO_SW,  MO_S,   MO_SE,  XXX,    XXX    ,XXX,    XXX,    MO_S_SW,MO_S_S, MO_S_SE,K_LOCK , \
    _______,_______,_______,_______,_______,MO_CL_L,MO_CL_R,_______,MO_AC_0,MO_AC_1,MO_AC_2,_______

/* Music layer
 * ,------------------------------------------------------------------------.
 * |.....|.....|.....|.....|.....|.....||.....|.....|.....|.....|.....|.....|
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * |.....|.....|.....|.....|.....|.....||.....|.....|.....|.....|.....|.....|
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * |.....|.....|.....|.....|.....|.....||.....|.....|.....|.....|.....|.....|
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * | togg| rec | stop| play| slow| fast||modes|.....|.....|.....|.....|.....|
 * `------------------------------------------------------------------------'
 */
#define MUSIC \
    MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK, \
    MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK, \
    MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK, \
    MU_TOG, MU_REC, MU_STOP,MU_PLAY,MU_SLOW,MU_FAST,MU_MOD, MU_MASK,MU_MASK,MU_MASK,MU_MASK,MU_MASK

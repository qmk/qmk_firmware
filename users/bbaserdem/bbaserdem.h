#ifndef USERSPACE
#define USERSPACE

#include "quantum.h"

// Use 7 wide characters for keymaps
#define _______ KC_TRNS
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

// Rename mouse keys
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

// Make only KC_NO be grabbed by music mode
#ifdef AUDIO_ENABLE
#define MUSIC_MASK keycode == XXX
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
    MOUSE,
    NUMBERS,
    LOCK,
    GAME,
    MUSIC,
    // Secret macros
    SECRET1,
    SECRET2,
    SECRET3
};

// Do tap dancable semicolon key if available
#ifdef TAP_DANCE_ENABLE
#define TAPPING_TERM 300
#define TAPPING_TOGGLE 1
enum {
    SCL = 0
};
#define MY_SCL  TD(SCL)
#else
#define MY_SCL  KC_SCLN
#endif

// Shared keymaps
#define KM(...) KEYMAP(__VA_ARGS__) // Required to expand the CSVs

/* Dvorak
 * ,------------------------------------------------------------------------.
 * | Esc |  "  |  ,  |  .  |  P  |  Y  ||  F  |  G  |  C  |  R  |  L  | Bkp |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * | Tab |  A  |  O  |  E  |  U  |  I  ||  D  |  H  |  T  |  N  |  S  | / ? |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * |Shift| ; : |  Q  |  J  |  K  |  X  ||  B  |  M  |  W  |  V  |  Z  |  Up |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * | Ctl | Alt |  OS | Tur | SYM | Spc || Ent |Funct|Mouse| Lft | Dwn | Rgt |
 * `------------------------------------------------------------------------' */
#define DVORAK_L1       KC_ESC,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y
#define DVORAK_R1       KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_BSPC
#define DVORAK_L2       KC_TAB,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I
#define DVORAK_R2       KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_SLSH
#define DVORAK_L3       KC_LSFT, MY_SCL,  KC_Q,    KC_J,    KC_K,    KC_X
#define DVORAK_R3       KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_UP
#define DVORAK_L4       KC_LCTL, KC_LALT, KC_LGUI, MO(_AL), NUMBERS, KC_SPC
#define DVORAK_R4       KC_ENT,  MO(_SE), MOUSE,   KC_LEFT, KC_DOWN, KC_RGHT

/* Alternative character overlay
 * ,------------------------------------------------------------------------.
 * |     |     | Undo| Redo|Pound| Yen ||     |  G  |  C  |     |TLira| Del |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * |     |  A  |  O  | Euro|  U  |  I  ||Degre|Plank|     |     |  S  | Ins |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * |     |     | Cut | Copy|Paste|     || BTC |     | sec.| sec.| sec.| PgUp|
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * |     |     |     |     |     |     ||     |     |     | Home|PgDwn| End |
 * `------------------------------------------------------------------------' */
#define ALTCHAR_L1      _______, _______, UNDO,    REDO,    CUR_BPN, CUR_YEN
#define ALTCHAR_R1      _______, TUR_G,   TUR_C,   _______, CUR_LIR, KC_DEL
#define ALTCHAR_L2      _______, TUR_A,   TUR_O,   CUR_EUR, TUR_U,   TUR_I
#define ALTCHAR_R2      PHY_DEG, PHY_HBR, _______, _______, TUR_S,   KC_INS
#define ALTCHAR_L3      _______, _______, CUT,     COPY,    PASTE,   _______
#define ALTCHAR_R3      CUR_BIT, _______, SECRET1, SECRET2, SECRET3, KC_PGUP
#define ALTCHAR_L4      _______, _______, _______, _______, _______, _______
#define ALTCHAR_R4      _______, _______, _______, KC_HOME, KC_PGDN, KC_END

/* Game layer
 * ,------------------------------------------------------------------------.
 * | OFF |  Q  |  W  |  E  |  R  |  T  || Esc |  7  |  8  |  9  |NumLk|Bkspc|
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * | Tab |  A  |  S  |  D  |  F  |  G  ||  F1 |  4  |  5  |  6  |  \  |     |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+Enter|
 * | Shf |  Z  |  X  |  C  |  V  |  B  ||  F2 |  1  |  2  |  3  |  ^  |     |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * | Ctrl| Alt | ` ~ |  /  |     | Spc || Spc |     |  0  |  <  |  v  |  >  |
 * `------------------------------------------------------------------------' */
#define GAME_L1         GAME,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T
#define GAME_R1         KC_ESC,  KC_P7,   KC_P8,   KC_P9,   KC_NLCK, KC_BSPC
#define GAME_L2         KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G
#define GAME_R2         KC_F1,   KC_P4,   KC_P5,   KC_P6,   KC_BSLS, KC_ENT
#define GAME_L3         KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B
#define GAME_R3         KC_F2,   KC_P1,   KC_P2,   KC_P3,   KC_UP,   KC_ENT
#define GAME_L4         KC_LCTL, KC_LALT, KC_GRV,  KC_SLSH, _______, KC_SPC
#define GAME_R4         KC_SPC,  _______, KC_P0,   KC_LEFT, KC_DOWN, KC_RGHT

/* Symbols layer
 * ,------------------------------------------------------------------------.
 * | OFF |  `  |  ~  |  [  |  ]  |  {  ||  }  |  =  |  +  |  -  |  _  |     |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * |     |  1  |  2  |  3  |  4  |  5  ||  6  |  7  |  8  |  9  |  0  |  \  |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * |     |  !  |  @  |  #  |  $  |  %  ||  ^  |  &  |  *  |  (  |  )  |     |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * |     |     |     |  |  |     |     ||     | LCK |     |     |     |     |
 * `------------------------------------------------------------------------' */
#define NUMBERS_L1      NUMBERS, KC_GRV,  KC_TILD, KC_LBRC, KC_RBRC, KC_LCBR
#define NUMBERS_R1      KC_RCBR, KC_EQL,  KC_PLUS, KC_MINS, KC_UNDS, _______
#define NUMBERS_L2      _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5
#define NUMBERS_R2      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS
#define NUMBERS_L3      _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC
#define NUMBERS_R3      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______
#define NUMBERS_L4      _______, _______, _______, KC_PIPE, _______, _______
#define NUMBERS_R4      _______, LOCK,    _______, _______, _______, _______

/* Settings layer
 * ,------------------------------------------------------------------------.
 * |BLLed|  F1 |  F2 |  F3 |  F4 | Lin || Win | Wake|     |Hue -|Hue +|Reset|
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * |     |  F5 |  F6 |  F7 |  F8 |     ||     |     |RGBto|Sat -|Sat +|     |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * |     |  F9 | F10 | F11 | F12 |Vol 0||PrtSc|     |RGBan|Bri -|Bri +|Stop |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * |PwOff|     |     |Music| Game|Vol -||Vol +|     |     | Prev|TogMu| Next|
 * `------------------------------------------------------------------------' */
#define SETTINGS_L1     BL_STEP, KC_F1,   KC_F2,   KC_F3,   KC_F4,   UNI_LI
#define SETTINGS_R1     UNI_WN,  KC_WAKE, _______, RGB_HUD, RGB_HUI, RESET
#define SETTINGS_L2     _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   _______
#define SETTINGS_R2     _______, _______, RGB_TOG, RGB_SAD, RGB_SAI, _______
#define SETTINGS_L3     _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_MUTE
#define SETTINGS_R3     KC_PSCR, _______, RGB_MOD, RGB_VAD, RGB_VAI, KC_MSTP
#define SETTINGS_L4     KC_PWR,  _______, _______, MU_TOG,  GAME,    KC_VOLD
#define SETTINGS_R4     KC_VOLU, _______, _______, KC_MPRV, KC_MPLY, KC_MNXT

/* Mouse layer
 * ,------------------------------------------------------------------------.
 * |Ulock|  \  |  ^  |  /  |.....|.....||.....|.....| |\|.| |^| | |/|.|     |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * |     |  <  | Mid |  >  |Btn 4|.....||.....|Btn 5| <-- | Mid | --> |     |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * |     |  /  |  v  |  \  |.....|.....||.....|.....| |/| | |v| | |\| |     |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * |     |     |     |     |     | Left||Right|     |     |Accl0|Accl1|Accl2|
 * `------------------------------------------------------------------------' */
#define MOUSE_L1        TG(_MO), MO_NW,   MO_N,    MO_NE,   XXX,     XXX
#define MOUSE_R1        XXX,     XXX,     MO_S_NW, MO_S_N,  MO_S_NE, _______
#define MOUSE_L2        _______, MO_W,    MO_CL_M, MO_E,    MO_CL_4, XXX
#define MOUSE_R2        XXX,     MO_CL_5, MO_S_W,  MO_CL_M, MO_S_E,  _______
#define MOUSE_L3        _______, MO_SW,   MO_S,    MO_SE,   XXX,     XXX
#define MOUSE_R3        XXX,     XXX,     MO_S_SW, MO_S_S,  MO_S_SE, _______
#define MOUSE_L4        _______, _______, _______, _______, _______, MO_CL_L
#define MOUSE_R4        MO_CL_R, _______, _______, MO_AC_0, MO_AC_1, MO_AC_2

/* Music layer
 * ,------------------------------------------------------------------------.
 * |.....|.....|.....|.....|.....|.....||.....|.....|.....|.....|.....|.....|
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * |.....|.....|.....|.....|.....|.....||.....|.....|.....|.....|.....|.....|
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * |.....|.....|.....|.....|.....|.....||.....|.....|.....|.....|.....|.....|
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * | rec | stop|plbck|ulock| slow| fast||modes|.....|.....|.....|.....|.....|
 * `------------------------------------------------------------------------'
 */
#define MASK XXX, XXX, XXX, XXX, XXX, XXX
#define MUSIC_4 KC_LCTL, KC_LALT, KC_LGUI, MU_TOG, KC_DOWN, KC_UP, MU_MOD, XXX, XXX, XXX, XXX, XXX

#endif

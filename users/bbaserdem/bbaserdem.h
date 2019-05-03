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
 * | Esc | ' " |  ,  |  .  |  P  |  Y  ||  F  |  G  |  C  |  R  |  L  | Bkp |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * | Tab |  A  |  O  |  E  |  U  |  I  ||  D  |  H  |  T  |  N  |  S  | / ? |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * | SYM | ; : |  Q  |  J  |  K  |  X  ||  B  |  M  |  W  |  V  |  Z  | SET |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * | TUR | OS  | Ctrl| Alt | Shf | Spc || Ent | Lft | Dwn |  Up | Rght| MSE |
 * `------------------------------------------------------------------------' */
#define DVORAK_1 \
    KC_ESC, KC_QUOT,KC_COMM,KC_DOT, KC_P,   KC_Y,   KC_F,   KC_G,   KC_C,   KC_R,   KC_L,   KC_BSPC
#define DVORAK_2 \
    KC_TAB, KC_A,   KC_O,   KC_E,   KC_U,   KC_I,   KC_D,   KC_H,   KC_T,   KC_N,   KC_S,   KC_SLSH
#define DVORAK_3 \
    K_NUMBR,MY_SCL, KC_Q,   KC_J,   KC_K,   KC_X,   KC_B,   KC_M,   KC_W,   KC_V,   KC_Z,   MO(_SE)
#define DVORAK_4 \
    MO(_AL),KC_LGUI,KC_LCTL,KC_LALT,KC_LSFT,KC_SPC, KC_ENT, KC_LEFT,KC_DOWN,KC_RGHT,KC_UP,  K_MOUSE
#define DVORAK KM(DVORAK_1,DVORAK_2,DVORAK_3,DVORAK_4)

/* Alternative character overlay
 * ,------------------------------------------------------------------------.
 * |     | ' ' | Undo| Redo|Pound| Yen ||     |  G  |  C  |     |TLira| Del |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * |     |  A  |  O  | Euro|  U  |  I  ||Degre|Plank|     |     |  S  | Ins |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * |     | " " | Cut | Copy|Paste|     || BTC | < > | ( ) | [ ] | { } | PgUp|
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * |     |     |     |     |     |     ||     | Home|PgDwn| PgUp| End |     |
 * `------------------------------------------------------------------------' */
#define ALTCHAR_1 \
    _______,DBL_QUO,UNDO,   REDO,   CUR_BPN,CUR_YEN,_______,TUR_G,  TUR_C,  _______,CUR_LIR,KC_DEL
#define ALTCHAR_2 \
    _______,TUR_A,  TUR_O,  CUR_EUR,TUR_U,  TUR_I,  PHY_DEG,PHY_HBR,_______,_______,TUR_S,  KC_INS
#define ALTCHAR_3 \
    _______,DBL_DQT,CUT,    COPY,   PASTE,  _______,CUR_BIT,DBL_ANG,DBL_PAR,DBL_SQR,DBL_BRC,_______
#define ALTCHAR_4 \
    _______,_______,_______,_______,_______,_______,_______,KC_HOME,KC_PGDN,KC_PGUP,KC_END,_______
#define ALTCHAR KM(ALTCHAR_1,ALTCHAR_2,ALTCHAR_3,ALTCHAR_4)

/* Game layer
 * ,------------------------------------------------------------------------.
 * | OFF |  Q  |  W  |  E  |  R  |  T  || Esc |  7  |  8  |  9  |NumLk|Bkspc|
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * | Tab |  A  |  S  |  D  |  F  |  G  ||  F1 |  4  |  5  |  6  |  \  | Ent |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * |     |  Z  |  X  |  C  |  V  |  B  ||  F2 |  1  |  2  |  3  |  ^  |     |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * |  /  |  `  |     |     |     | Spc || Spc | Ent |  0  |  <  |  v  |  >  |
 * `------------------------------------------------------------------------' */
#define GAME_1 \
    K_GAMES,KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_ESC, KC_P7,  KC_P8,  KC_P9,  KC_NLCK,KC_BSPC
#define GAME_2 \
    KC_TAB, KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_F1,  KC_P4,  KC_P5,  KC_P6,  KC_BSLS,KC_ENT 
#define GAME_3 \
    _______,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_F2,  KC_P1,  KC_P2,  KC_P3,  KC_UP,  _______
#define GAME_4 \
    KC_SLSH,KC_GRV, _______,_______,_______,KC_SPC, KC_SPC, KC_ENT, KC_P0,  KC_LEFT,KC_DOWN,KC_RGHT
#define GAME KM(GAME_1,GAME_2,GAME_3,GAME_4)

/* Symbols layer
 * ,------------------------------------------------------------------------.
 * | OFF |  `  |  ~  |  [  |  ]  |  {  ||  }  |  -  |  _  |  =  |  +  |     |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * |     |  1  |  2  |  3  |  4  |  5  ||  6  |  7  |  8  |  9  |  0  |  \  |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * |     |  !  |  @  |  #  |  $  |  %  ||  ^  |  &  |  *  |  (  |  )  | LCK |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * |  |  |     |     |  |  |     |     ||     |     |     |     |     |     |
 * `------------------------------------------------------------------------' */
#define NUMBERS_1 \
    K_NUMBR,KC_GRV, KC_TILD,KC_LBRC,KC_RBRC,KC_LCBR,KC_RCBR,KC_MINS,KC_UNDS,KC_EQL, KC_PLUS,_______
#define NUMBERS_2 \
    _______,KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_BSLS
#define NUMBERS_3 \
    _______,KC_EXLM,KC_AT,  KC_HASH,KC_DLR, KC_PERC,KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,K_LOCK
#define NUMBERS_4 \
    KC_PIPE,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______
#define NUMBERS KM(NUMBERS_1,NUMBERS_2,NUMBERS_3,NUMBERS_4)

/* Settings layer
 * ,------------------------------------------------------------------------.
 * |BLLed|  F1 |  F2 |  F3 |  F4 | Lin || Win | Wake|     |Hue -|Hue +|Reset|
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * |     |  F5 |  F6 |  F7 |  F8 |     ||     |     |RGBto|Sat -|Sat +|     |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * | Game|  F9 | F10 | F11 | F12 |Vol 0||PrtSc|     |RGBan|Bri -|Bri +|     |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * |Musir|     |     |     |     |Vol -||Vol +| Prev| Stop|TogMu| Next|     |
 * `------------------------------------------------------------------------' */
#define SETTINGS_1 \
    BL_STEP,KC_F1,  KC_F2,  KC_F3,  KC_F4,  UNI_LI, UNI_WN, KC_WAKE,_______,RGB_HUD,RGB_HUI,RESET  
#define SETTINGS_2 \
    _______,KC_F5,  KC_F6,  KC_F7,  KC_F8,  _______,_______,_______,RGB_TOG,RGB_SAD,RGB_SAI,_______
#define SETTINGS_3 \
    K_GAMES,KC_F9,  KC_F10, KC_F11, KC_F12, KC_MUTE,KC_PSCR,_______,RGB_MOD,RGB_VAD,RGB_VAI,_______
#define SETTINGS_4 \
    MU_TOG, _______,_______,_______,_______,KC_VOLD,KC_VOLU,KC_MPRV,KC_MSTP,KC_MPLY,KC_MNXT,_______
#define SETTINGS KM(SETTINGS_1,SETTINGS_2,SETTINGS_3,SETTINGS_4)

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
#define MOUSE_1 \
    K_MOUSE,MO_NW,  MO_N,   MO_NE,  XXX,    XXX    ,XXX,    XXX,    MO_S_NW,MO_S_N, MO_S_NE,_______
#define MOUSE_2 \
    _______,MO_W,   MO_CL_M,MO_E,   MO_CL_4,XXX    ,XXX,    MO_CL_5,MO_S_W, MO_CL_M,MO_S_E, _______
#define MOUSE_3 \
    _______,MO_SW,  MO_S,   MO_SE,  XXX,    XXX    ,XXX,    XXX,    MO_S_SW,MO_S_S, MO_S_SE,K_LOCK
#define MOUSE_4 \
    _______,_______,_______,_______,_______,MO_CL_L,MO_CL_R,_______,MO_AC_0,MO_AC_1,MO_AC_2,_______
#define MOUSE KM(MOUSE_1,MOUSE_2,MOUSE_3,MOUSE_4)

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
#define MASK XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX
#define MUSIC_4 MU_TOG, KC_LCTL, KC_LALT, KC_LGUI, KC_DOWN, KC_UP, MU_MOD, XXX, XXX, XXX, XXX, XXX
#define MUSIC KM(MASK,MASK,MASK,MUSIC_4)

#endif

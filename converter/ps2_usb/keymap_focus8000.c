#include "keymap_common.h"

/* Focus 8000 layout
 * -----------------
 *  * big enter key
 *  * pipe/backslash between right ctrl and right alt
 *  * blank keycap with NUBS keycode between left ctrl and alt
 *  * TODO: 'calculator' keys report 'Overrun' when debugging keyboard
 */
#define KEYMAP_FOCUS8000( \
    K76,K05,K06,K04,K0C,K03,K0B,K83,K0A,K01,K09,K78,K07,     KFC,K7E,KFE,  KPC,KSQ,KAC,KSW,     \
    K0E,K16,K1E,K26,K25,K2E,K36,K3D,K3E,K46,K45,K4E,K55,K66, KF0,KEC,KFD,  KCE,K77,KCA,K7C,K7B, \
    K0D,K15,K1D,K24,K2D,K2C,K35,K3C,K43,K44,K4D,K54,K5B,     KF1,KE9,KFA,  KMC,K6C,K75,K7D,     \
    K58,K1C,K1B,K23,K2B,K34,K33,K3B,K42,K4B,K4C,K52,    K5A,               KMR,K6B,K73,K74,K79, \
    K12,K1A,K22,K21,K2A,K32,K31,K3A,K41,K49,K4A,        K59,     KF5,      KMM,K69,K72,K7A,     \
    K14,K61,K11,            K29,                K91,K5D,K94, KEB,KF2,KF4,  KMP,K70,    K71,KDA  \
) \
KEYMAP_ALL( \
    K76,K05,K06,K04,K0C,K03,K0B,K83,K0A,K01,K09,K78,K07,     KFC,K7E,KFE,                       \
    K0E,K16,K1E,K26,K25,K2E,K36,K3D,K3E,K46,K45,K4E,K55,K66, KF0,KEC,KFD,  K77,KCA,K7C,K7B,     \
    K0D,K15,K1D,K24,K2D,K2C,K35,K3C,K43,K44,K4D,K54,K5B,K5D, KF1,KE9,KFA,  K6C,K75,K7D,         \
    K58,K1C,K1B,K23,K2B,K34,K33,K3B,K42,K4B,K4C,K52,    K5A,               K6B,K73,K74,K79,     \
    K12,K1A,K22,K21,K2A,K32,K31,K3A,K41,K49,K4A,        K59,     KF5,      K69,K72,K7A,         \
    K14,NO, K11,        K29,                K91,NO, NO, K94, KEB,KF2,KF4,  K70,    K71,KDA,     \
                                                                                                \
    K61,                                                                                        \
    RO, KANA, JYEN, HENK, MHEN,                                                                 \
    F13, F14, F15, F16, F17, F18, F19, F20, F21, F22, F23, F24,                                 \
    SYSTEM_POWER, SYSTEM_SLEEP, SYSTEM_WAKE,                                                    \
    AUDIO_MUTE, AUDIO_VOL_UP, AUDIO_VOL_DOWN,                                                   \
    MEDIA_NEXT_TRACK, MEDIA_PREV_TRACK, MEDIA_STOP, MEDIA_PLAY_PAUSE, MEDIA_SELECT,             \
    MAIL, CALCULATOR, MY_COMPUTER,                                                              \
    WWW_SEARCH, WWW_HOME, WWW_BACK, WWW_FORWARD,                                                \
    WWW_STOP, WWW_REFRESH, WWW_FAVORITES                                                        \
)



const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* 0: default
 * ,---.   ,---------------. ,---------------. ,---------------. ,-----------. ,-------------------.
 * |Esc|   |F1 |F2 |F3 |F4 | |F5 |F6 |F7 |F8 | |F9 |F10|F11|F12| |PrS|ScL|Pau| | %  |SqRt| AC |Kb/C|
 * `---'   `---------------' `---------------' `---------------' `-----------' `-------------------'
 * ,-----------------------------------------------------------. ,-----------. ,-------------------.
 * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backspa| |Ins|Hom|PgU| |CE |NmL|  /|  *|  -|
 * |-----------------------------------------------------------| |-----------| |-------------------|
 * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|     | |Del|End|PgD| |MC |  7|  8|  9|   |
 * |-----------------------------------------------------+     | `-----------' |---------------|  +|
 * |CapsLo|  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return  |               |MR |  4|  5|  6|   |
 * |-----------------------------------------------------------|     ,---.     |-------------------|
 * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  ,|  /|Shift     |     |Up |     |M- |  1|  2|  3|   |
 * |-----------------------------------------------------------| ,-----------. |---------------|Ent|
 * |Ctrl |Fn0| Alt |           Space           | Alt |  /|Ctrl | |Lef|Dow|Rig| |M+ |      0|  .|   |
 * `-----------------------------------------------------------' `-----------' `-------------------'
 */
KEYMAP_FOCUS8000(

    ESC,      F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12,      PSCR,SLCK,BRK,     NO,  NO,  NO,  NO,

    GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC,     INS, HOME,PGUP,    NO,  NLCK,PSLS,PAST,PMNS,
    TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,          DEL, END, PGDN,    NO,  P7,  P8,  P9,
    LCTL,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,     ENT,                         NO,  P4,  P5,  P6,  PPLS,
    LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,          RSFT,          UP,           NO,  P1,  P2,  P3,
    FN0, LGUI,LALT,               SPC,                     RALT,BSLS,CAPS,     LEFT,DOWN,RGHT,    NO,  P0,       PDOT,PENT

),

/* 1: extra keys
 * -------------
 *  - vim keys
 *  - media keys
 *  - mouse keys
 * ,---.   ,---------------. ,---------------. ,---------------. ,-----------. ,-------------------.
 * |   |   |   |   |   |   | |   |   |   |   | |   |   |   |   | |   |   |   | |    |    |    |    |
 * `---'   `---------------' `---------------' `---------------' `-----------' `-------------------'
 * ,-----------------------------------------------------------. ,-----------. ,-------------------.
 * |   |   |   |   |   |   |   |   |   |   |   |   |   |       | |   |   |   | |   |   |   |   |   |
 * |-----------------------------------------------------------| |-----------| |-------------------|
 * |     |   |   |   |   |   |   |   |   |   |   |   |   |     | |   |   |   | |   |Bn1|MsU|Bn2|   |
 * |-----------------------------------------------------+     | `-----------' |---------------|WUp|
 * |      |   |   |   |   |   |   |Lef|Dow|Up |Rig|   |        |               |   |MsL|MsD|MsR|   |
 * |-----------------------------------------------------------|     ,---.     |-------------------|
 * |        |   |   |   |   |   |   |   |   |   |   |          |     |   |     |   |   |   |   |   |
 * |-----------------------------------------------------------| ,-----------. |---------------|WDn|
 * |     |   |    |                            |VolDn|Mut|VolUp| |   |   |   | |   |       |   |   |
 * `-----------------------------------------------------------' `-----------' `-------------------'
 */
KEYMAP_FOCUS8000(

    TRNS,     TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS,TRNS,TRNS,    TRNS,TRNS,TRNS,TRNS,

    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS,TRNS,TRNS,    TRNS,TRNS,TRNS,TRNS,TRNS,
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,          TRNS,TRNS,TRNS,    TRNS,BTN1,MS_U,BTN2,
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,LEFT,DOWN,UP,  RGHT,TRNS,TRNS,     TRNS,                        TRNS,MS_L,MS_D,MS_R,WH_U,
    TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,          TRNS,          TRNS,         TRNS,TRNS,TRNS,TRNS,
    TRNS,TRNS,TRNS,               TRNS,                    VOLD,MUTE,VOLU,     TRNS,TRNS,TRNS,    TRNS,TRNS,     TRNS,WH_D

),

};

const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_MOMENTARY(1),
};

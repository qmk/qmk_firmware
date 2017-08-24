#include "lets_split.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

#define _COLEMAK  0
#define _KAMELOC  1
#define _IKAPILA  2
#define _IKASHFT  3
#define _ARROWKY  4
#define _FNCTION  5
#define _NINEKEY  6
#define _NAVIGAT  7
#define _QWERTY   8
#define _MLAYER   9
#define _GRVTABL  15

enum custom_keycodes {
  COLEMAK = SAFE_RANGE,
  KAMELOC,
  IKAPILA,
  IKASHFT,
  ARROWKY,
  FNCTION,
  NINEKEY,
  NAVIGAT,
  QWERTY,
  MLAYER,
  GRVTABL,
};

//TD Declarations
enum {
VOM = 0,
PRN,
EGT,
HRD,
XRD,
DSH,
ESC,
EQE,
PGN,
HND,
COD,
UND,
F11,
F12,
F13,
F14,
F15,
F16,
F17,
F18,
F19,
F20,
//unicode_inputctl
LINUX,
WIN,
WINSH,
OSX,
};

#define _______     KC_TRNS
#define XXXXXXX     KC_NO

// action-TAP for key/mod behavior LT(layer, KC)
#define XK_TAB      LT(_FNCTION, KC_TAB)
#define XK_BSP      LT(_KAMELOC, KC_BSPC)
#define XK_APO      LT(_KAMELOC, KC_QUOT)

#define XK_SPC    LT(_IKAPILA, KC_SPC)
#define XK_ENT      LT(_IKAPILA, KC_ENT)
#define XK_PGDN     LT(_IKASHFT, KC_PGDN)
#define XK_PGUP     LT(_IKASHFT, KC_PGUP)
#define PIPBOY      LT(_FNCTION, KC_BSLS)
#define XK_DEL      LT(_IKASHFT, KC_DEL)
#define XK_GRV      LT(_GRVTABL, KC_GRV)

// mod-TAP for mod/key behavior MT(modkey, KC)
#define ALT_IT      MT(MOD_RALT, KC_SCLN)
#define CTL_IT      MT(MOD_RCTL, KC_DOT)
#define SFT_ENT	    MT(MOD_RSFT, KC_ENT)

//sticky modifiers
#define KYCTL       OSM(MOD_LCTL)
#define KYSFT       OSM(MOD_LSFT)
#define CAKY        OSM(MOD_LCTL | MOD_LALT)

//shortcuts
#define CADEL       LALT(LCTL(KC_DEL))
#define CAINS       LALT(LCTL(KC_INS))
#define TGNKRO      MAGIC_TOGGLE_NKRO

#define NAVCH       LCTL(KC_HOME)
#define NAVCPD      LCTL(KC_PGDN)
#define NAVCPU      LCTL(KC_PGUP)
#define NAVCE       LCTL(KC_END)
#define NAVCU       LCTL(KC_UP)
#define NAVCD       LCTL(KC_DOWN)
#define NAVCL       LCTL(KC_LEFT)
#define NAVCR       LCTL(KC_RGHT)
#define NAVGU       LGUI(KC_UP)
#define NAVGD       LGUI(KC_DOWN)
#define NAVGL       LGUI(KC_LEFT)
#define NAVGR       LGUI(KC_RGHT)

#define KC_NDSH     LCTL(KC_PMNS)
#define KC_MDSH     LALT(LCTL(KC_PMNS))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
  TAP
  ┌────┬────┬────┬────┬────┬────┐    ┌────┬────┬────┬────┬────┬────┐
  │TAB │ Q  │ W  │ F  │ P  │ B  │    │ J  │ L  │ U  │ Y  │ ;  │DEL │
  ├────┼────┼────┼────┼────┼────┤    ├────┼────┼────┼────┼────┼────┤
  │BKSP│ A  │ R  │ S  │ T  │ G  │    │ M  │ N  │ E  │ I  │ O  │ '  │
  ├────┼────┼────┼────┼────┼────┤    ├────┼────┼────┼────┼────┼────┤
  │OSFT│ X  │ C  │ D  │ V  │ Z  │    │ K  │ H  │ ,  │    │ .  │ /  │
  ├────┼────┼────┼────┼────┼────┤    ├────┼────┼────┼────┼────┼────┤
  │OCTL│GUI │ESC │ALT │PGUP│SPC │    │ENT │PGDN│ () │ {} │ \  │ `  │
  └────┴────┴────┴────┴────┴────┘    └────┴────┴────┴────┴────┴────┘
   HOLD
  ┌────┬────┬────┬────┬────┬────┐    ┌────┬────┬────┬────┬────┬────┐
  │L FN│    │    │    │    │    │    │    │    │    │    │ALT │L!@#│
  ├────┼────┼────┼────┼────┼────┤    ├────┼────┼────┼────┼────┼────┤
  │L OH│    │    │    │    │    │    │    │    │    │    │    │L OH│
  ├────┼────┼────┼────┼────┼────┤    ├────┼────┼────┼────┼────┼────┤
  │SFT │    │    │    │    │    │    │    │    │    │    │CTL │SFT │
  ├────┼────┼────┼────┼────┼────┤    ├────┼────┼────┼────┼────┼────┤
  │CTL │GUI │ESC │ALT │L!@#│L123│    │L123│L!@#│L  M│    │L FN│LGRV│
  └────┴────┴────┴────┴────┴────┘    └────┴────┴────┴────┴────┴────┘
   DOUBLETAP
  ┌────┬────┬────┬────┬────┬────┐    ┌────┬────┬────┬────┬────┬────┐
  │    │    │    │    │    │    │    │    │    │    │    │    │    │
  ├────┼────┼────┼────┼────┼────┤    ├────┼────┼────┼────┼────┼────┤
  │    │    │    │    │    │    │    │    │    │    │    │    │    │
  ├────┼────┼────┼────┼────┼────┤    ├────┼────┼────┼────┼────┼────┤
  │OSML│    │    │    │    │    │    │    │    │    │    │    │    │
  ├────┼────┼────┼────┼────┼────┤    ├────┼────┼────┼────┼────┼────┤
  │OSML│OSML│!F4 │    │    │    │    │    │    │    │    │    │    │
  └────┴────┴────┴────┴────┴────┘    └────┴────┴────┴────┴────┴────┘
  Switch type
  ┌────┬────┬────┬────┬────┬────┐    ┌────┬────┬────┬────┬────┬────┐
  │Br  │mxC │Z   │Z   │Z   │Z   │    │Z   │Z   │Z   │Z   │Br  │G   │
  ├────┼────┼────┼────┼────┼────┤    ├────┼────┼────┼────┼────┼────┤
  │G   │Z   │Z   │Z   │Z   │Z   │    │Z   │Z   │Z   │Z   │Z   │Z   │
  ├────┼────┼────┼────┼────┼────┤    ├────┼────┼────┼────┼────┼────┤
  │Y   │Z   │Z   │Z   │Z   │Z   │    │Z   │Z   │Z   │B   │B   │Y   │
  ├────┼────┼────┼────┼────┼────┤    ├────┼────┼────┼────┼────┼────┤
  │Y   │Y   │mxC │Z   │BLK │BLK │    │BLK │BLK │Z   │Z   │B   │G   │
  └────┴────┴────┴────┴────┴────┘    └────┴────┴────┴────┴────┴────┘
  with DCS keycaps
  Top Row   R1 (reversed?)
  M Row1    R3 (with reversed pointer finger)
  M Row2    R4
  B Row     R2 (reversed)
*/

// Colemak PB&J (Mod-DH)
[_COLEMAK] = KEYMAP( \
   XK_TAB,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,            KC_J,    KC_L,        KC_U,         KC_Y,  ALT_IT,         XK_DEL, \
   XK_BSP,    KC_A,    KC_R,    KC_S,    KC_T,    KC_G,            KC_M,    KC_N,        KC_E,         KC_I,    KC_O,         XK_APO, \
    KYSFT,    KC_X,    KC_C,    KC_D,    KC_V,    KC_Z,            KC_K,    KC_H,     TD(COD),       KC_DOT,  CTL_IT, SFT_T(KC_SLSH), \
    KYCTL, KC_LGUI, TD(ESC), KC_LALT, XK_PGUP,  XK_SPC,          XK_ENT, XK_PGDN, MO(_MLAYER), TT(_NAVIGAT),  PIPBOY,         XK_GRV \
),

// useful for one-handed typing
[_KAMELOC] = KEYMAP( \
   XK_DEL, KC_SCLN,    KC_Y,    KC_U,    KC_L,    KC_J,            KC_B,    KC_P,    KC_F,    KC_W,    KC_Q,  XK_TAB, \
  _______,    KC_O,    KC_I,    KC_E,    KC_N,    KC_M,            KC_G,    KC_T,    KC_S,    KC_R,    KC_A, _______, \
    KYSFT, KC_SLSH,  KC_DOT, KC_COMM,    KC_H,    KC_K,         TD(UND),    KC_V,    KC_D,    KC_C,    KC_X,   KYSFT, \
   XK_GRV,  PIPBOY,    M(1), KC_BTN1, KC_HOME,  KC_ENT,          KC_ENT,  KC_END, KC_LGUI, TD(ESC), KC_LALT,   KYCTL \
),

/*
  ┌────┬────┬────┬────┬────┬────┐    ┌────┬────┬────┬────┬────┬────┐
  │    │ 1  │ 2  │ 3  │ 4  │ 5  │    │ 6  │ 7  │ 8  │ 9  │ 0  │    │
  ├────┼────┼────┼────┼────┼────┤    ├────┼────┼────┼────┼────┼────┤
  │    │ M  │ V- │ V+ │NEXT│PLAY│    │ ←  │ ↓  │ ↑  │ →  │DASH│INS │
  ├────┼────┼────┼────┼────┼────┤    ├────┼────┼────┼────┼────┼────┤
  │    │ -  │ =  │TGL │    │    │    │HOME│END │HOME│    │ \  │ ~  │
  ├────┼────┼────┼────┼────┼────┤    ├────┼────┼────┼────┼────┼────┤
  │    │    │    │    │    │    │    │    │    │    │    │    │    │
  └────┴────┴────┴────┴────┴────┘    └────┴────┴────┴────┴────┴────┘
*/
[_IKAPILA] = KEYMAP( \
  _______,    KC_1,    KC_2,    KC_3,    KC_4,       KC_5,            KC_6,    KC_7,    KC_8,    KC_9,    KC_0, _______, \
  _______, KC_MUTE, KC_VOLD, KC_VOLU, KC_MNXT,    KC_MPLY,         KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, TD(DSH),  KC_INS, \
  _______, KC_MINS,  KC_EQL, XXXXXXX, XXXXXXX, LCTL(KC_Z),         KC_HOME, TD(HND), KC_HOME, XXXXXXX, KC_BSLS, KC_TILD, \
  _______, _______, _______, _______, _______,    _______,         _______, _______, _______, _______, _______, _______ \
),

/*
  ┌────┬────┬────┬────┬────┬────┐    ┌────┬────┬────┬────┬────┬────┐
  │    │ !  │ @  │ #  │ $  │ %  │    │ ^  │ &  │ *  │ (  │ )  │BSPC│
  ├────┼────┼────┼────┼────┼────┤    ├────┼────┼────┼────┼────┼────┤
  │DEL │    │ ←  │ ↓  │ ↑  │ →  │    │NEXT│PGUP│ V+ │ V- │DASH│PSCR│
  ├────┼────┼────┼────┼────┼────┤    ├────┼────┼────┼────┼────┼────┤
  │    │ _  │ +  │END │HOME│END │    │    │    │    │ [  │ ]  │    │
  ├────┼────┼────┼────┼────┼────┤    ├────┼────┼────┼────┼────┼────┤
  │    │    │    │    │    │    │    │    │    │    │    │    │    │
  └────┴────┴────┴────┴────┴────┘    └────┴────┴────┴────┴────┴────┘
*/

[_IKASHFT] =  KEYMAP( \
  _______, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,         KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC, \
   KC_DEL, TD(PGN), KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,         KC_MNXT, KC_PGUP, KC_VOLU, TD(VOM), KC_MDSH, KC_PSCR, \
  _______, KC_UNDS, KC_PLUS,  KC_END, KC_HOME,  KC_END,            M(1),    M(0),    M(2), KC_LBRC, KC_RBRC, _______, \
  _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______ \
),

/*
  ┌────┬────┬────┬────┬────┬────┐    ┌────┬────┬────┬────┬────┬────┐
  │    │ →  │ ↑  │ ←  │ ↓  │ →  │    │ →  │ ↓  │ ←  │ ↑  │ ↑  │    │ just in case someone hacks my IP with a 10MeG pipe, you know?
  ├────┼────┼────┼────┼────┼────┤    ├────┼────┼────┼────┼────┼────┤
  │    │ ←  │ ↓  │ →  │ ↑  │ ←  │    │ ↑  │ ←  │ ↓  │ →  │ ←  │    │ hacker_evasion layer
  ├────┼────┼────┼────┼────┼────┤    ├────┼────┼────┼────┼────┼────┤ >>init network SEQUENCE
  │    │ ↑  │ ←  │ ↓  │ →  │ ↑  │    │ ↓  │ ←  │ ↑  │ →  │ ←  │    │   sleep 11; echo "DONE\n"
  ├────┼────┼────┼────┼────┼────┤    ├────┼────┼────┼────┼────┼────┤   throttle INPUT 11001001 OUTPUT 010011001 ? FULL )); \
  │    │    │    │ →  │ ←  │ ↓  │    │ →  │ ↑  │ ←  │ ↓  │ ↑  │    │ <<chKConfig cargoCode ==== "'1'"
  └────┴────┴────┴────┴────┴────┘    └────┴────┴────┴────┴────┴────┘   up down left right KC_b KC_a GUI
*/

[_ARROWKY] =  KEYMAP( \


  _______, KC_RGHT,   KC_UP, KC_LEFT, KC_DOWN, KC_RGHT,           KC_UP, KC_LEFT, KC_DOWN, KC_RGHT,   KC_UP, _______, \
  _______, KC_LEFT, KC_DOWN, KC_RGHT,   KC_UP, KC_LEFT,         KC_DOWN, KC_RGHT,   KC_UP, KC_LEFT, KC_DOWN, _______, \
  _______,   KC_UP, KC_LEFT, KC_DOWN, KC_RGHT,   KC_UP,         KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, KC_LEFT, _______, \
  _______, _______, KC_RGHT,   KC_UP, KC_LEFT, KC_DOWN,         KC_RGHT,   KC_UP, KC_LEFT, KC_DOWN, KC_RGHT, _______ \
),

/*
  ┌────┬────┬────┬────┬────┬────┐    ┌────┬────┬────┬────┬────┬────┐
  │    │ F1 │ F2 │ F3 │ F4 │ F5 │    │ F6 │ F7 │ F8 │ F9 │ F10│    │
  ├────┼────┼────┼────┼────┼────┤    ├────┼────┼────┼────┼────┼────┤
  │    │ F21│ F22│ F23│ F24│PAUS│    │    │SCLK│BOOT│    │NKRO│CAPS│
  ├────┼────┼────┼────┼────┼────┤    ├────┼────┼────┼────┼────┼────┤
  │    │    │    │    │    │    │    │    │    │    │    │    │    │
  ├────┼────┼────┼────┼────┼────┤    ├────┼────┼────┼────┼────┼────┤
  │    │    │    │    │    │    │    │    │    │    │    │    │    │
  └────┴────┴────┴────┴────┴────┘    └────┴────┴────┴────┴────┴────┘
*/

[_FNCTION] =  KEYMAP( \
  _______, TD(F11), TD(F12), TD(F13), TD(F14), TD(F15),         TD(F16), TD(F17), TD(F18), TD(F19), TD(F20), _______, \
  _______,  KC_F21,  KC_F22,  KC_F23,  KC_F24, XXXXXXX,         XXXXXXX, KC_SLCK, XXXXXXX, XXXXXXX,  TGNKRO, XXXXXXX, \
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_CAPS, \
  _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______ \
),

/*
  ┌────┬────┬────┬────┬────┬────┐    ┌────┬────┬────┬────┬────┬────┐
  │    │ →  │ F7 │ F8 │ F9 │ ↑  │    │ P7 │ P8 │ P9 │NLCK│ P- │BDEL│
  ├────┼────┼────┼────┼────┼────┤    ├────┼────┼────┼────┼────┼────┤
  │    │ ←  │ F4 │ F5 │ F6 │ ↓  │    │ P4 │ P5 │ P6 │^INS│ P+ │ () │
  ├────┼────┼────┼────┼────┼────┤    ├────┼────┼────┼────┼────┼────┤
  │    │CALT│ F1 │ F2 │ F3 │    │    │ P1 │ P2 │ P3 │    │ P* │ =  │
  ├────┼────┼────┼────┼────┼────┤    ├────┼────┼────┼────┼────┼────┤
  │    │    │ F0?│    │    │    │    │ P0 │ 0  │ P. │TGL │ P/ │    │
  └────┴────┴────┴────┴────┴────┘    └────┴────┴────┴────┴────┴────┘
*/

[_NINEKEY] =  KEYMAP( \
  _______, KC_RGHT,   KC_F7,   KC_F8,   KC_F9,   KC_UP,       KC_P7,   KC_P8,   KC_P9,      KC_NLCK,KC_PMNS, KC_DEL, \
  _______, KC_LEFT,   KC_F4,   KC_F5,   KC_F6, KC_DOWN,       KC_P4,   KC_P5,   KC_P6,        CAINS,KC_PPLS, M(0), \
  _______,    CAKY,   KC_F1,   KC_F2,   KC_F3, XXXXXXX,       KC_P1,   KC_P2,   KC_P3,      XXXXXXX,KC_PAST, TD(EQE), \
  _______, _______, _______,  KC_F11, _______, _______,       KC_P0,    KC_0, KC_PDOT,         CAKY,KC_PSLS, _______ \
),

/*
  ┌────┬────┬────┬────┬────┬────┐    ┌────┬────┬────┬────┬────┬────┐
  │ESC │^HOM│^PGD│^UP │^PGU│^PGU│    │    │MW_L│ MU │MW_R│ AC2│    │
  ├────┼────┼────┼────┼────┼────┤    ├────┼────┼────┼────┼────┼────┤
  │    │^END│^LFT│^DWN│^RGT│^PGD│    │    │ ML │ MD │ MR │ AC1│    │
  ├────┼────┼────┼────┼────┼────┤    ├────┼────┼────┼────┼────┼────┤
  │    │ M5 │ M2 │ M4 │ M3 │ M1 │    │    │MW_D│MW_U│    │ AC0│    │
  ├────┼────┼────┼────┼────┼────┤    ├────┼────┼────┼────┼────┼────┤
  │    │    │    │    │    │    │    │    │    │    │    │    │    │
  └────┴────┴────┴────┴────┴────┘    └────┴────┴────┴────┴────┴────┘
*/

[_NAVIGAT] =  KEYMAP( \
   KC_ESC,   NAVCH,  NAVCPD,   NAVCU,  NAVCPU,  NAVCPU,         XXXXXXX, KC_WH_L, KC_MS_U, KC_WH_R, KC_ACL2, _______, \
  _______,   NAVCE,   NAVCL,   NAVCD,   NAVCR,  NAVCPD,         XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, KC_ACL1, _______, \
  _______, KC_BTN5, KC_BTN2, KC_BTN4, KC_BTN3, KC_BTN1,         XXXXXXX, KC_WH_D, KC_WH_U, XXXXXXX, KC_ACL0, _______, \
  _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______ \
),

//ew. jk
[_QWERTY] = KEYMAP( \
  _______,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,            KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC, \
  _______,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,            KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT, \
  _______,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,            KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, SFT_ENT, \
  _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______ \
),

[_MLAYER] =  KEYMAP( \
  _______,UC(0x250C),UC(0x252C),UC(0x2510),UC(0x2500),UC(0x2502),       _______, _______, _______, _______, _______, _______, \
  KC_QUOT,UC(0x251C),UC(0x253C),UC(0x2524),   _______,   _______,          M(1),    M(0),    M(2), _______, _______, _______, \
  _______,UC(0x2514),UC(0x2534),UC(0x2518),   _______,   _______,       _______, _______, _______, _______, _______, _______, \
  _______,     WINSH,       WIN,       OSX,   _______,   _______,       _______, _______, _______, _______, _______, _______ \
),

[_GRVTABL] =  KEYMAP( \
    TG(5),LALT(KC_PSCR),    M(4),  KC_PWR,KC_POWER,   RESET,           RESET,    KC_R,    KC_E,    KC_I,LALT(KC_PSCR),TG(3), \
    TG(1),        TG(6),   TG(7),   TG(9),   TG(3),   TG(2),           TG(2),    KC_S,    KC_U,    KC_B,   TG(6),   TG(1), \
     M(3),        TG(8), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         KC_MYCM, KC_CALC, XXXXXXX, XXXXXXX,   TG(8),    M(3), \
   TT(15),        TG(6),   TG(7),   TG(9),   TG(3),   TG(2),           TG(2),   TG(3),   TG(9),   TG(7),   TG(6), _______ \
)};


qk_tap_dance_action_t tap_dance_actions[] = {
 [VOM] = ACTION_TAP_DANCE_DOUBLE(KC_VOLD, KC_MUTE),
 [PRN] = ACTION_TAP_DANCE_DOUBLE(KC_LPRN, KC_RPRN),
 [EGT] = ACTION_TAP_DANCE_DOUBLE(KC_LCBR, KC_RCBR),
 [HRD] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_RBRC),
 [DSH] = ACTION_TAP_DANCE_DOUBLE(KC_NDSH, KC_MDSH),
 [ESC] = ACTION_TAP_DANCE_DOUBLE(KC_ESC,  LALT(KC_F4)),
 [EQE] = ACTION_TAP_DANCE_DOUBLE(KC_EQL,  KC_ENT),
 [UND] = ACTION_TAP_DANCE_DOUBLE(KC_Z,    LCTL(KC_Z)),
 [PGN] = ACTION_TAP_DANCE_DOUBLE(KC_PGDN, KC_PGUP),
 [HND] = ACTION_TAP_DANCE_DOUBLE(KC_HOME, KC_END),
 [COD] = ACTION_TAP_DANCE_DOUBLE(KC_COMM, KC_DOT),
 [F11] = ACTION_TAP_DANCE_DOUBLE(KC_F1,   KC_F11),
 [F12] = ACTION_TAP_DANCE_DOUBLE(KC_F2,   KC_F12),
 [F13] = ACTION_TAP_DANCE_DOUBLE(KC_F3,   KC_F13),
 [F14] = ACTION_TAP_DANCE_DOUBLE(KC_F4,   KC_F14),
 [F15] = ACTION_TAP_DANCE_DOUBLE(KC_F5,   KC_F15),
 [F16] = ACTION_TAP_DANCE_DOUBLE(KC_F6,   KC_F16),
 [F17] = ACTION_TAP_DANCE_DOUBLE(KC_F7,   KC_F17),
 [F18] = ACTION_TAP_DANCE_DOUBLE(KC_F8,   KC_F18),
 [F19] = ACTION_TAP_DANCE_DOUBLE(KC_F9,   KC_F19),
 [F20] = ACTION_TAP_DANCE_DOUBLE(KC_F10,  KC_F20),
};

void matrix_init_user(){
  set_unicode_input_mode(UC_LNX);
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  if (record->event.pressed) {
    switch(id) {
  case 0:
    return MACRO( D(LSFT), T(9), U(LSFT), D(LSFT), T(0), U(LSFT), T(LEFT), END );
  case 1:
    return MACRO( D(LSFT), T(LBRC), U(LSFT), D(LSFT), T(RBRC), U(LSFT), T(LEFT), END );
  case 2:
    return MACRO( T(LBRC), T(RBRC), T(LEFT), END);
  case 3:
    clear_keyboard();
  case 4:
    return MACRO( D(LSFT), T(SCOLON), U(LSFT), D(LSFT), T(9), U(LSFT), D(LSFT), T(0), U(LSFT), D(LSFT), T(LBRACKET), U(LSFT), D(LSFT), T(9), U(LSFT), D(LSFT), T(SCOLON), U(LSFT), D(LSFT), T(0), U(LSFT), D(LSFT), T(BSLASH), U(LSFT), D(LSFT), T(SCOLON), U(LSFT), D(LSFT), T(7), U(LSFT), D(LSFT), T(RBRACKET), U(LSFT), T(SCOLON), D(LSFT), T(SCOLON), U(LSFT), END );
  case WINSH:
    set_unicode_input_mode(UC_WIN);
    return false;
    break;
  case WIN:
    set_unicode_input_mode(UC_WINC);
    return false;
    break;
  case OSX:
    set_unicode_input_mode(UC_OSX);
    return false;
    break;
   }
  }
 return MACRO_NONE;
};

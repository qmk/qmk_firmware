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
  GRVTABL,
};

//TD Declarations
enum {
  VOM = 0,
  PRN,
  EGT,
  HRD,
  DSH,
  QUT,
  ESC,
  EQE,
  PGN,
  UND,
  BSDEL,
  bsdel_mods,
  BOOTME,
};

#define _______     KC_TRNS
#define XXXXXXX     KC_NO

// action-TAP for key/mod behavior LT(layer, kc)
#define XK_TAB      LT(_FNCTION, KC_TAB)
#define XK_BSP      LT(_KAMELOC, M(3))

#define XK_HARD     LT(_FNCTION, M(1))
#define XK_SPC      LT(_IKAPILA, KC_SPC)
#define XK_ENT      LT(_IKAPILA, KC_ENT)
#define XK_PGDN     LT(_NAVIGAT, TD(PGN))
#define XK_PREN     LT(_IKASHFT, M(0))
#define PIPBOY      LT(_FNCTION, KC_BSLS)

#define XK_DEL      LT(_KAMELOC, KC_DEL)
#define XK_GRV      LT(_GRVTABL, KC_GRV)

// mod-TAP for mod/key behavior MT(modkey, kc)
#define ESC_IT      MT(MOD_MEH, TD(ESC))

#define ALT_IT      MT(MOD_LALT, KC_SCLN)
#define CTL_IT      MT(MOD_LCTL, KC_SLSH)
#define XK_EGPT     MT((MOD_LCTL | MOD_LALT | MOD_LGUI), M(2))

#define SFT_IT      MT(MOD_RSFT, TG(_NAVIGAT))
#define SFT_ENT	    MT(MOD_RSFT, KC_ENT)

//sticky modifiers
#define KYCTL       OSM(MOD_LCTL)
#define KYGUI       OSM(MOD_LGUI)
#define KYSFT       OSM(MOD_LSFT)
#define KYALT       OSM(MOD_LALT)
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

#define KC_NDSH 	LCTL(KC_PMNS)
#define KC_MDSH 	LALT(LCTL(KC_PMNS))

//!not sure if this old TMK code will work
//#define BOOTME      ACTION_FUNCTION(BOOTLOADER)
#define LCLEAR      ACTION_LAYER_SET_CLEAR(0)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
  TAP
  ┌────┬────┬────┬────┬────┬────┐    ┌────┬────┬────┬────┬────┬────┐
  │TAB │ Q  │ W  │ F  │ P  │ B  │    │ J  │ L  │ U  │ Y  │ ;  │DEL │
  ├────┼────┼────┼────┼────┼────┤    ├────┼────┼────┼────┼────┼────┤
  │BKSP│ A  │ R  │ S  │ T  │ G  │    │ M  │ N  │ E  │ I  │ O  │ '  │
  ├────┼────┼────┼────┼────┼────┤    ├────┼────┼────┼────┼────┼────┤
  │OSFT│ X  │ C  │ D  │ V  │ Z  │    │ K  │ H  │ ,  │ .  │ /  │LNAV│
  ├────┼────┼────┼────┼────┼────┤    ├────┼────┼────┼────┼────┼────┤
  │OCTL│OALT│L9KY│ [] │OGUI│SPC │    │ENT │PGDN│ () │ {} │ \  │ `  │
  └────┴────┴────┴────┴────┴────┘    └────┴────┴────┴────┴────┴────┘
   HOLD
  ┌────┬────┬────┬────┬────┬────┐    ┌────┬────┬────┬────┬────┬────┐
  │L FN│    │    │    │    │    │    │    │    │    │    │ALT │L!@#│
  ├────┼────┼────┼────┼────┼────┤    ├────┼────┼────┼────┼────┼────┤
  │L OH│    │    │    │    │    │    │    │    │    │    │    │L OH│
  ├────┼────┼────┼────┼────┼────┤    ├────┼────┼────┼────┼────┼────┤
  │SFT │    │    │    │    │    │    │    │    │    │    │CTL │SFT │
  ├────┼────┼────┼────┼────┼────┤    ├────┼────┼────┼────┼────┼────┤
  │CTL │ALT │L9KY│L!@#│GUI │L123│    │L123│LNAV│L!@#│MEH │L FN│LGRV│
  └────┴────┴────┴────┴────┴────┘    └────┴────┴────┴────┴────┴────┘
   DOUBLETAP
  ┌────┬────┬────┬────┬────┬────┐    ┌────┬────┬────┬────┬────┬────┐
  │    │!F4 │    │    │    │    │    │    │    │    │    │    │    │
  ├────┼────┼────┼────┼────┼────┤    ├────┼────┼────┼────┼────┼────┤
  │    │    │    │    │    │    │    │    │    │    │    │    │    │
  ├────┼────┼────┼────┼────┼────┤    ├────┼────┼────┼────┼────┼────┤
  │OSML│    │    │    │    │UNDO│    │    │    │    │    │    │    │
  ├────┼────┼────┼────┼────┼────┤    ├────┼────┼────┼────┼────┼────┤
  │OSML│OSML│ESC │    │OSML│    │    │    │PGUP│    │    │    │    │
  └────┴────┴────┴────┴────┴────┘    └────┴────┴────┴────┴────┴────┘
  Switch type
  ┌────┬────┬────┬────┬────┬────┐    ┌────┬────┬────┬────┬────┬────┐
  │Br  │Z   │Z   │Z   │Z   │Z   │    │Z   │Z   │Z   │Z   │Br  │G   │
  ├────┼────┼────┼────┼────┼────┤    ├────┼────┼────┼────┼────┼────┤
  │G   │Z   │Z   │Z   │Z   │Z   │    │Z   │Z   │Z   │Z   │Z   │Z   │
  ├────┼────┼────┼────┼────┼────┤    ├────┼────┼────┼────┼────┼────┤
  │Y   │Z   │Z   │Z   │Z   │Z   │    │Z   │Z   │Z   │Z   │B   │Y   │
  ├────┼────┼────┼────┼────┼────┤    ├────┼────┼────┼────┼────┼────┤
  │Y   │Y   │C   │Z   │BLK │BLK │    │BLK │BLK │Z   │Z   │B   │G   │
  └────┴────┴────┴────┴────┴────┘    └────┴────┴────┴────┴────┴────┘
*/

// Colemak PB&J (Mod-DH)
[_COLEMAK] = KEYMAP( \
   XK_TAB, TD(QUT),    KC_W,    KC_F,    KC_P,    KC_B,            KC_J,    KC_L,    KC_U,    KC_Y, ALT_IT,  XK_GRV,  \
   XK_BSP,    KC_A,    KC_R,    KC_S,    KC_T,    KC_G,            KC_M,    KC_N,    KC_E,    KC_I,    KC_O,  XK_DEL, \
    KYSFT,    KC_X,    KC_C,    KC_D,    KC_V, TD(UND),            KC_K,    KC_H, KC_COMM,  KC_DOT,  CTL_IT,  SFT_IT, \
    KYCTL,   KYALT,  ESC_IT,  XK_HARD,  KYGUI,  XK_SPC,          XK_ENT, XK_PGDN, XK_PREN, XK_EGPT,  PIPBOY,  XK_GRV \
),

// useful for one-handed typing
[_KAMELOC] = KEYMAP( \
  _______, KC_SCLN,    KC_Y,    KC_U,    KC_L,    KC_J,            KC_B,    KC_P,    KC_F,    KC_W, TD(QUT), _______, \
  _______,    KC_O,    KC_I,    KC_E,    KC_N,    KC_M,            KC_G,    KC_T,    KC_S,    KC_R,    KC_A, _______, \
  _______, KC_SLSH,  KC_DOT, KC_COMM,    KC_H,    KC_K,         TD(UND),    KC_V,    KC_D,    KC_C,    KC_X, _______, \
  _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______ \
),

/*
  ┌────┬────┬────┬────┬────┬────┐    ┌────┬────┬────┬────┬────┬────┐
  │ ~  │ 1  │ 2  │ 3  │ 4  │ 5  │    │ 6  │ 7  │ 8  │ 9  │ 0  │    │
  ├────┼────┼────┼────┼────┼────┤    ├────┼────┼────┼────┼────┼────┤
  │    │DASH│MV- │ V+ │NEXT│PLAY│    │ ←  │ ↓  │ ↑  │ →  │INS │    │
  ├────┼────┼────┼────┼────┼────┤    ├────┼────┼────┼────┼────┼────┤
  │    │ -  │ =  │ [  │ ]  │ \  │    │HOME│PGDN│PGUP│END │ \  │    │
  ├────┼────┼────┼────┼────┼────┤    ├────┼────┼────┼────┼────┼────┤
  │    │    │    │    │    │    │    │    │    │    │    │    │    │
  └────┴────┴────┴────┴────┴────┘    └────┴────┴────┴────┴────┴────┘
*/
[_IKAPILA] = KEYMAP( \
  KC_TILD,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,            KC_6,    KC_7,    KC_8,    KC_9,    KC_0, _______, \
  _______, TD(DSH), TD(VOM), KC_VOLU, KC_MNXT, KC_MPLY,         KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,  KC_INS, _______, \
  _______, KC_MINS,  KC_EQL, TD(HRD), KC_RBRC, KC_BSLS,         KC_HOME, KC_PGDN, KC_PGUP,  KC_END, KC_BSLS, _______, \
  _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______ \
),

/*
  ┌────┬────┬────┬────┬────┬────┐    ┌────┬────┬────┬────┬────┬────┐
  │    │ !  │ @  │ #  │ $  │ %  │    │ ^  │ &  │ *  │ (  │ )  │    │
  ├────┼────┼────┼────┼────┼────┤    ├────┼────┼────┼────┼────┼────┤
  │    │DASH│MV- │ V+ │NEXT│PLAY│    │HOME│PGDN│PGUP│END │PSCR│    │
  ├────┼────┼────┼────┼────┼────┤    ├────┼────┼────┼────┼────┼────┤
  │    │ _  │ +  │ {  │ }  │ |  │    │ ←  │ ↓  │ ↑  │ →  │    │    │
  ├────┼────┼────┼────┼────┼────┤    ├────┼────┼────┼────┼────┼────┤
  │    │    │    │    │    │    │    │    │    │    │    │    │    │
  └────┴────┴────┴────┴────┴────┘    └────┴────┴────┴────┴────┴────┘
*/

[_IKASHFT] =  KEYMAP( \
  _______, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,         KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______, \
   KC_DEL, TD(DSH), TD(VOM), KC_VOLU, KC_MNXT, KC_MPLY,         KC_HOME, KC_PGDN, KC_PGUP,  KC_END, KC_PSCR, _______, \
  _______, KC_UNDS, KC_PLUS, TD(EGT), KC_RCBR, KC_PIPE,         KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, KC_PAUS, _______, \
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
  │    │    │    │ →  │ ←  │ ↓  │    │ →  │ ↑  │ ←  │ ↓  │ ↑  │    │ <<chkconfig cargoCode ==== "'1'"
  └────┴────┴────┴────┴────┴────┘    └────┴────┴────┴────┴────┴────┘   up down left right kc_b kc_a GUI
*/

[_ARROWKY] =  KEYMAP( \
  _______, KC_RGHT,   KC_UP, KC_LEFT, KC_DOWN, KC_RGHT,           KC_UP, KC_LEFT, KC_DOWN, KC_RGHT,   KC_UP, _______, \
  _______, KC_LEFT, KC_DOWN, KC_RGHT,   KC_UP, KC_LEFT,         KC_DOWN, KC_RGHT,   KC_UP, KC_LEFT, KC_DOWN, _______, \
  _______,   KC_UP, KC_LEFT, KC_DOWN, KC_RGHT,   KC_UP,         KC_LEFT, KC_DOWN, KC_RGHT,   KC_UP, KC_LEFT, _______, \
  _______, _______, KC_RGHT,   KC_UP, KC_LEFT, KC_DOWN,         KC_RGHT,   KC_UP, KC_LEFT, KC_DOWN, KC_RGHT, _______ \
),

/*
  ┌────┬────┬────┬────┬────┬────┐    ┌────┬────┬────┬────┬────┬────┐
  │    │ F1 │ F2 │ F3 │ F4 │ F5 │    │ F6 │ F7 │ F8 │ F9 │ F10│    │
  ├────┼────┼────┼────┼────┼────┤    ├────┼────┼────┼────┼────┼────┤
  │    │ F11│ F12│ F13│ F14│ F15│    │ F16│ F17│ F18│ F19│ F20│    │
  ├────┼────┼────┼────┼────┼────┤    ├────┼────┼────┼────┼────┼────┤
  │    │ F21│ F22│ F23│ F24│PAUS│    │    │    │BOOT│RSET│NKRO│CAPS│
  ├────┼────┼────┼────┼────┼────┤    ├────┼────┼────┼────┼────┼────┤
  │    │    │    │    │    │    │    │    │    │    │    │    │    │
  └────┴────┴────┴────┴────┴────┘    └────┴────┴────┴────┴────┴────┘
*/

[_FNCTION] =  KEYMAP( \
  _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,           KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, _______, \
  _______,  KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,          KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20, _______, \
  _______,  KC_F21,  KC_F22,  KC_F23,  KC_F24, _______,         _______, _______,M(BOOTME),   RESET,  TGNKRO, KC_CAPS, \
  _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______ \
),

/*
  ┌────┬────┬────┬────┬────┬────┐    ┌────┬────┬────┬────┬────┬────┐
  │    │ →  │ F7 │ F8 │ F9 │ ↑  │    │NLCK│ P7 │ P8 │ P9 │ P- │BDEL│
  ├────┼────┼────┼────┼────┼────┤    ├────┼────┼────┼────┼────┼────┤
  │    │ ←  │ F4 │ F5 │ F6 │ ↓  │    │^INS│ P4 │ P5 │ P6 │ P+ │ () │
  ├────┼────┼────┼────┼────┼────┤    ├────┼────┼────┼────┼────┼────┤
  │    │CALT│ F1 │ F2 │ F3 │    │    │CALT│ P1 │ P2 │ P3 │ P* │ =  │
  ├────┼────┼────┼────┼────┼────┤    ├────┼────┼────┼────┼────┼────┤
  │    │    │ F0?│    │    │    │    │TGL │ P0 │ 0  │ P. │ P/ │    │
  └────┴────┴────┴────┴────┴────┘    └────┴────┴────┴────┴────┴────┘
*/

[_NINEKEY] =  KEYMAP( \
  _______, KC_RGHT,   KC_F7,   KC_F8,   KC_F9,   KC_UP,         KC_NLCK,   KC_P7,   KC_P8,   KC_P9, KC_PMNS, M(BSDEL), \
  _______, KC_LEFT,   KC_F4,   KC_F5,   KC_F6, KC_DOWN,           CAINS,   KC_P4,   KC_P5,   KC_P6, KC_PPLS, XK_PREN, \
  _______,    CAKY,   KC_F1,   KC_F2,   KC_F3, _______,            CAKY,   KC_P1,   KC_P2,   KC_P3, KC_PAST, TD(EQE), \
  _______, _______, _______,  KC_F11, _______, _______,    TG(_NINEKEY),   KC_P0,    KC_0, KC_PDOT, KC_PSLS, _______ \
),

/*
  ┌────┬────┬────┬────┬────┬────┐    ┌────┬────┬────┬────┬────┬────┐
  │ESC │^PGD│^UP │^PGU│^PGU│^HOM│    │    │MW_L│ MU │MW_R│ AC2│    │
  ├────┼────┼────┼────┼────┼────┤    ├────┼────┼────┼────┼────┼────┤
  │    │^LFT│^DWN│^RGT│^PGD│^END│    │    │ ML │ MD │ MR │ AC1│    │
  ├────┼────┼────┼────┼────┼────┤    ├────┼────┼────┼────┼────┼────┤
  │    │ M2 │ M4 │ M3 │ M1 │ M5 │    │    │MW_D│MW_U│SLCK│ AC0│    │
  ├────┼────┼────┼────┼────┼────┤    ├────┼────┼────┼────┼────┼────┤
  │    │    │    │    │    │    │    │    │    │    │    │    │    │
  └────┴────┴────┴────┴────┴────┘    └────┴────┴────┴────┴────┴────┘
*/

[_NAVIGAT] =  KEYMAP( \
   KC_ESC,  NAVCPD,   NAVCU,  NAVCPU,  NAVCPU,   NAVCH,         XXXXXXX, KC_WH_L, KC_MS_U, KC_WH_R, KC_ACL2, _______, \
  _______,   NAVCL,   NAVCD,   NAVCR,  NAVCPD,   NAVCE,         XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, KC_ACL1, _______, \
  _______, KC_BTN2, KC_BTN4, KC_BTN3, KC_BTN1, KC_BTN5,         XXXXXXX, KC_WH_D, KC_WH_U, KC_SLCK, KC_ACL0, _______, \
  _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______ \
),

//ew. jk
[_QWERTY] = KEYMAP( \
  _______,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,            KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC, \
  _______,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,            KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT, \
  _______,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,            KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, SFT_ENT, \
  _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______ \
),

/*
//add greek symbols
//set_unicode_input_mode(UC_WINC); // Windows (with WinCompose, see wiki)

//UC(0x250C),UC(0x252C),UC(0x2510),UC(0x2500),UC(0x2502)
//UC(0x251C),UC(0x253C),UC(0x2524),
//UC(0x2514),UC(0x2534),UC(0x2518),
*/
[_GRVTABL] =  KEYMAP( \
    TG(5), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   TG(3), \
    TG(1), XXXXXXX, TD(VOM), KC_VOLU, KC_MNXT, KC_MPLY,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   TG(1), \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,           TG(0), XXXXXXX,   TG(4), XXXXXXX,   TG(8),  LCLEAR, \
  XXXXXXX, XXXXXXX,   TG(6),   TG(3), XXXXXXX,   TG(2),         TG(2),   TG(7),   TG(3), OSM(MOD_MEH), TG(5), _______ \
)};

qk_tap_dance_action_t tap_dance_actions[] = {
 [VOM] = ACTION_TAP_DANCE_DOUBLE(KC_VOLD, KC_MUTE),
 [PRN] = ACTION_TAP_DANCE_DOUBLE(KC_LPRN, KC_RPRN),
 [EGT] = ACTION_TAP_DANCE_DOUBLE(KC_LCBR, KC_RCBR),
 [HRD] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_RBRC),
 [DSH] = ACTION_TAP_DANCE_DOUBLE(KC_NDSH, KC_MDSH),
 [QUT] = ACTION_TAP_DANCE_DOUBLE(KC_Q,    LALT(KC_F4)),
 [ESC] = ACTION_TAP_DANCE_DOUBLE(TT(_NINEKEY), KC_ESC),
 [EQE] = ACTION_TAP_DANCE_DOUBLE(KC_EQL,  KC_ENT),
 [PGN] = ACTION_TAP_DANCE_DOUBLE(KC_PGDN,  KC_PGUP),
 [UND] = ACTION_TAP_DANCE_DOUBLE(KC_Z, LCTL(KC_Z)),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
	if (record->event.pressed) {
		switch(id) {
			case 0:
				return MACRO(D(LSHIFT),T(9), T(0),U(LSHIFT), T(LEFT), END);
			case 1:
				return MACRO(T(LBRC), T(RBRC), T(LEFT), END);
                        case 2:
                                return MACRO(D(LSHIFT),T(LBRC), T(RBRC),U(LSHIFT), T(ENT), T(UP), END);
            case 3:
                                return MACRO(T(BSPC), END);
/*                static bool bsdel_mods = false;
                case BSDEL: {
                  uint8_t kc = KC_BSPC;
                if (record->event.pressed) {
                  if (keyboard_report->mods) {
                    kc = KC_DEL;
                  }
                register_code (kc);
                bsdel_mods = keyboard_report->mods;
                }
                else {
                if (bsdel_mods) {
                  kc = KC_DEL;
                }

                unregister_code (kc);
                }
                }
*/            case 4:
                if (!record->event.pressed) {
//                bootloader();
                }
        }
	}
	return MACRO_NONE;
};

//
// This layout is based on the following needs:
//
// should be as close as possible to querty/us-international layout (using international/AltGr as o/s driver)
// added german umlauts at known places from de-layout
// all movement keys should be at known places from vi/bash (eg HJKL for cursor keys)
// Fn layer (at CapsLock place like the Pok3r does) for missing keys
// additional layer for tmux window switching
//
// This is work in Progress! If you have suggestions write me at github.com/mollat/qmk_firmware/ and check
// this fork for updates as I probably won't bother jack with my pull requests frequently.
//

#include QMK_KEYBOARD_H

#define _QWERTY 0
#define _HIGH 1
#define _LOW 2
#define _FN 3
#define _TMUX 4
#define _LCTL 5
#define _MOUSE 6
#define __________ KC_NO // just for easy reading

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT_planck_grid( /* Qwerty */
   LT(_MOUSE, KC_ESC),KC_Q,KC_W,       KC_E,       KC_R,       KC_T,       KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_BSPC    ,
   LT(_FN, KC_TAB),KC_A,   KC_S,       KC_D,       KC_F,       KC_G,       KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    KC_QUOT    ,
   KC_LSFT,    KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,    SFT_T(KC_ENT),
   __________, __________, KC_LGUI,    KC_LALT,    KC_LCTL,LT(_TMUX, KC_SPC),LT(_HIGH, KC_SPC),MO(_LOW),KC_RALT,KC_RGUI,   __________, __________
),

// missing keys regarding to the form factor
// keeping the dot and comma for typing faster IP addresses and (german) float values
// putting the backslash on the slash's place
[_HIGH] = LAYOUT_planck_grid(
   KC_GRV,     KC_EXLM,    KC_AT,      KC_HASH,    KC_DLR,     KC_PERC,    KC_CIRC,    KC_AMPR,    KC_ASTR,    KC_LPRN,    KC_RPRN,    KC_MINS    ,
   __________, KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_EQL     ,
   __________, __________, __________, __________, __________, __________, __________, __________, KC_COMM,    KC_DOT,     KC_BSLS,    LSFT(KC_BSLS),
   __________, __________, __________, __________, __________, __________, KC_TRNS,    __________, __________, __________, __________, __________
),

// classic Fn-Layer triggered with 'CapsLock-key' like on Pok3r
// SPC and ENT are doubled for using repeat (which I switched off, see https://github.com/tmk/tmk_keyboard/issues/287)
// '€' sign is on the '5' position as this is the usual AltGr place on the US Internation layout
// home/end at the 'a' and 'e' position like in bash
// ins at 'i'
// del besides backspace (had no better place for it because of the umlauts)
// pg-down at 'f' (forward in vi), pg-up at 'b' (back in 'vi')
//
[_FN] = LAYOUT_planck_grid(
   __________, __________, __________, KC_END,     __________, __________, __________, __________, KC_INS,     __________, KC_DEL,     RALT(KC_Y) ,
   KC_TRNS,    __________, RALT(KC_S), __________, KC_PGDN,    RALT(KC_5), KC_LEFT,    KC_DOWN,    KC_UP,      KC_RGHT,    RALT(KC_P), RALT(KC_Q) ,
   __________, KC_HOME,    __________, __________, __________, KC_PGUP,    __________, __________, __________, __________, __________, KC_ENT     ,
   RESET,      __________, __________, __________, __________, KC_SPC,     KC_SPC,     __________, __________, __________, __________, __________
),

// function key layer and some shift + (missing key at the small form factor)
[_LOW] = LAYOUT_planck_grid(
   KC_TILD,    __________, __________, __________, __________, __________, __________, __________, __________, KC_LCBR,    KC_RCBR,    KC_UNDS    ,
   __________, KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,      KC_F7,      KC_F8,      KC_LBRC,    KC_RBRC,    KC_PLUS    ,
   __________, __________, __________, __________, __________, KC_F9,      KC_F10,     KC_F11,     KC_F12,     __________, __________, __________ ,
   __________, __________, __________, __________, __________, __________, __________, KC_TRNS,    __________, __________, __________, __________
),

// most macros will switch tmux screens
// two macros are for vi's save/quit at 'w' and 'q'
[_TMUX] = LAYOUT_planck_grid(
   __________, M(14),      M(13),      __________, __________, __________, __________, __________, __________, __________, M(11),      __________ ,
   M(0),       M(1),       M(2),       M(3),       M(4),       M(5),       M(6),       M(7),       M(8),       M(9),       __________, __________ ,
   __________, __________, __________, M(12),      __________, __________, M(10),      __________, __________, __________, __________, __________ ,
   __________, __________, __________, __________, __________, KC_TRNS,    __________, __________, __________, __________, __________, __________
),

// mouse movement can be improved (e.g. can't press hj at once), but I will use this seldom, so I stick with hjkl keys.
[_MOUSE] = LAYOUT_planck_grid(
   KC_TRNS,    __________, __________, __________, __________, __________, __________, __________, __________, __________, __________, __________ ,
   __________, __________, __________, __________, KC_WH_D,    __________, KC_MS_L,    KC_MS_D,    KC_MS_U,    KC_MS_R,    __________, __________ ,
   __________, __________, __________, __________, __________, KC_WH_U,    __________, __________, __________, __________, __________, __________ ,
   __________, __________, __________, KC_ACL2,    KC_ACL1,    KC_ACL0,    KC_MS_BTN1, KC_MS_BTN3, KC_MS_BTN2, __________, __________, __________
)
};

const uint16_t PROGMEM fn_actions[] = {
    [_LCTL] = ACTION_MODS_TAP_KEY(KC_LCTL, M(12)),    // does not work
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
      switch(id) {
        case 0:
          return MACRODOWN( DOWN(KC_LCTL), TYPE(KC_B), UP(KC_LCTL), TYPE(KC_0), END );
          break;
        case 1:
          return MACRODOWN( DOWN(KC_LCTL), TYPE(KC_B), UP(KC_LCTL), TYPE(KC_1), END );
          break;
        case 2:
          return MACRODOWN( DOWN(KC_LCTL), TYPE(KC_B), UP(KC_LCTL), TYPE(KC_2), END );
          break;
        case 3:
          return MACRODOWN( DOWN(KC_LCTL), TYPE(KC_B), UP(KC_LCTL), TYPE(KC_3), END );
          break;
        case 4:
          return MACRODOWN( DOWN(KC_LCTL), TYPE(KC_B), UP(KC_LCTL), TYPE(KC_4), END );
          break;
        case 5:
          return MACRODOWN( DOWN(KC_LCTL), TYPE(KC_B), UP(KC_LCTL), TYPE(KC_5), END );
          break;
        case 6:
          return MACRODOWN( DOWN(KC_LCTL), TYPE(KC_B), UP(KC_LCTL), TYPE(KC_6), END );
          break;
        case 7:
          return MACRODOWN( DOWN(KC_LCTL), TYPE(KC_B), UP(KC_LCTL), TYPE(KC_7), END );
          break;
        case 8:
          return MACRODOWN( DOWN(KC_LCTL), TYPE(KC_B), UP(KC_LCTL), TYPE(KC_8), END );
          break;
        case 9:
          // tmux last window
          return MACRODOWN( DOWN(KC_LCTL), TYPE(KC_B), UP(KC_LCTL), TYPE(KC_L), END );
          break;
          // tmux next window
        case 10:
          return MACRODOWN( DOWN(KC_LCTL), TYPE(KC_B), UP(KC_LCTL), TYPE(KC_N), END );
          break;
          // tmux previous window
        case 11:
          return MACRODOWN( DOWN(KC_LCTL), TYPE(KC_B), UP(KC_LCTL), TYPE(KC_P), END );
          break;
          // tmux new window
        case 12:
          return MACRODOWN( DOWN(KC_LCTL), TYPE(KC_B), UP(KC_LCTL), TYPE(KC_C), END );
          break;
        case 13:
          // vi save document
          return MACRODOWN( TYPE(KC_ESC), DOWN(KC_LSFT), TYPE(KC_SCLN), UP(KC_LSFT), TYPE(KC_W), TYPE(KC_ENT), END );
          break;
        case 14:
          // vi quit
          return MACRODOWN( TYPE(KC_ESC), DOWN(KC_LSFT), TYPE(KC_SCLN), UP(KC_LSFT), TYPE(KC_Q), TYPE(KC_ENT), END );
          break;
          // tmux press ctrl-b
        case 15:
          return MACRODOWN( DOWN(KC_LCTL), TYPE(KC_B), UP(KC_LCTL), END );
          break;
      }
    return MACRO_NONE;
};

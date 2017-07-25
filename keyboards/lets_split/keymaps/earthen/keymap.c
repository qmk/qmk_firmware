#include "lets_split.h"
#include "action_layer.h"
#include "eeconfig.h"
#include "keymap_extras/keymap_german_ch.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define QWERTY 1
#define JOAN 2
#define MARC 0
#define SYMB 3
#define SYMBUS 4
#define LOWER 5
#define RAISE 6
#define CODE 7
#define ADJUST 8
#define MOUSE 9


// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Adjust| Ctrl | Alt  | GUI  |Lower |Space |Space |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[QWERTY] = KEYMAP( \
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
  KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT , \
  ADJUST,  KC_LCTL, KC_LALT, KC_LGUI, LT(LOWER,KC_SPC),   LT(RAISE,KC_BSPC),  LT(LOWER,KC_DELT),  LT(RAISE,KC_ENT),   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT \
),

/* JOAN
 * ,---------------------------------------------------------------------------------------.
 * |Tab/CODE|   ü  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   T  |   Z  |PtS/Code|
 * |--------+------+------+------+------+-------------+------+------+------+------+--------|
 * |Esc/SYMB|   A  |   O  |   E  |   I  |   U  |   H  |   D  |   R  |   N  |   S  |L/SYMB  |
 * |--------+------+------+------+------+------|------+------+------+------+------+--------|
 * |ä/Shift |   ö  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   -  | Shift  |
 * |--------+------+------+------+------+------+------+------+------+------+------+--------|
 * | Ctrl   | Ctrl | Alt  | GUI  |Space/| Bksp/| Del/ |Enter/| Left | Down |  Up  |Right   |
 * |        |      |      |      | RAISE| LOWER| RAISE| LOWER|      |      |      |        |
 * `---------------------------------------------------------------------------------------'
 */
[JOAN] = KEYMAP( \
  LT(CODE,KC_TAB),   CH_UE,          CH_COMM, CH_DOT,  CH_P,               CH_Y,               CH_F,               CH_G,               CH_C,    CH_R,    CH_Z,    LT(CODE,KC_PSCR), \
  LT(SYMB, KC_ESC),  SFT_T(CH_A),    CH_O,    CH_E,    CH_U,               CH_I,               CH_D,               CH_H,               CH_T,    CH_N,    SFT_T(CH_S),    LT(SYMB,CH_L), \
  SFT_T(CH_AE),      CH_OE,          CH_Q,    CH_J,    CH_K,               CH_X,               CH_B,               CH_M,               CH_W,    CH_V,    CH_Z,    KC_LSFT , \
  KC_LCTL,           KC_LCTL,        KC_LALT, KC_LGUI, LT(LOWER,KC_SPC),   LT(RAISE,KC_BSPC),  LT(LOWER,KC_DELT),  LT(RAISE,KC_ENT),   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT \
),
/* Marc
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   "  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  |  -   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | TAB |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |  /   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  | Shift|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Alt  | GUI  |Right |Lower | Bksp |Space |Raise |  Up  | Down |  GUI |Enter |
 * `-----------------------------------------------------------------------------------'
 */

[MARC] = KEYMAP ( \
  LT(CODE, KC_ESC),  KC_QUOT, KC_COMM, KC_DOT,             KC_P,              KC_Y,             KC_F,             KC_G,              KC_C,    KC_R,    KC_L,    LT(CODE,KC_MINS),\
  LT(SYMBUS,KC_TAB), KC_A,    KC_O,    KC_E,               KC_U,              KC_I,             KC_D,             KC_H,              KC_T,    KC_N,    KC_S,    LT(SYMBUS,KC_SLSH), \
  KC_LSFT,           KC_SCLN, KC_Q,    KC_J,               KC_K,              KC_X,             KC_B,             KC_M,              KC_W,    KC_V,    KC_Z,    KC_RSFT, \
  KC_LCTL,           KC_LALT, KC_RGUI, LT(MOUSE, KC_LEFT), LT(LOWER,KC_BSPC), LT(RAISE,KC_ENT), LT(RAISE,KC_SPC), LT(LOWER,KC_DELT), KC_UP,   KC_DOWN, KC_RGUI, KC_ENT \
                  ),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |ADJUST|  F4 |  F3  |   F2 |  F1   |      |      | HOME |  UP  |  END |  *   |      |
 * |------+-----+------+------+----- -+-------------+------+------+------+------+------|
 * |      |  F8 |   F7 |   F6 |   F5  |      |      | LEFT | DOWN | RIGHT|   +  |  \   |
 * |------+-----+------+------+----- -+------|------+------+------+------+------+------|
 * |      |  12  | F11  |  F10 |  F9  |      |      |   1  |   2  |   3  |   /  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[MOUSE] = KEYMAP( \
  TG(ADJUST),  _______, _______, _______, _______, _______, _______, KC_BTN1,    KC_MS_UP, KC_BTN2,_______,_______, \
  _______, _______, _______, _______, _______, _______, _______, KC_MS_LEFT, KC_MS_DOWN,  KC_MS_RIGHT, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, KC_ACL0, KC_ACL1, KC_ACL2, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______,_______, _______, _______, _______ \
),

/* Symbol
 * ,-----------------------------------------------------------------------------------.
 * |      |   !  |   @  |   {  |   }  |   |  |   ç |   "  |   '  |   &   |  *   | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   #  |   $  |   (  |   )  |   `  |  ´   |   \  |   /  |   ?  |   +  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   %  |   ^  |   [  |   ]  |   ~  |   §  |   <  |   >  |      |   /  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[SYMB] = KEYMAP( \
  _______, CH_EXLM,CH_AT,  CH_LCBR,CH_RCBR,CH_PIPE, CH_CELA,   CH_DQOT,   CH_QUOT,    CH_AMPR,    CH_QST, KC_BSPC, \
  _______,  CH_HASH,CH_DLR, CH_LPRN,CH_RPRN,CH_GRV,  CH_ACUT, CH_BSLS,   CH_SLSH,    CH_PAST,    CH_EQL,  _______, \
  _______, CH_PERC,CH_CARR,CH_LBRC,CH_RBRC,CH_TILD, CH_PARA, CH_LESS,   CH_MORE,    CH_PLUS,    KC_AMPR,  _______, \
  _______, _______, _______, _______, _______, _______, _______, _______,    KC_MNXT,    KC_VOLD, KC_VOLU, KC_MPLY \
),

[SYMBUS] = KEYMAP( \
  _______, KC_EXLM,KC_AT,  KC_LCBR,KC_RCBR,KC_PIPE, LSFT(KC_4),   LSFT(KC_2),   KC_QUOT,    KC_AMPR,    KC_ASTR, KC_BSPC, \
  _______,  KC_HASH,KC_DLR, KC_LPRN,KC_RPRN,KC_GRV, ALGR(KC_MINS), KC_BSLS,   KC_SLSH,    KC_PAST,    KC_EQL,  _______, \
  _______, KC_PERC,KC_CIRC,KC_LBRC,KC_RBRC,KC_TILD, LSFT(KC_DOT), LSFT(KC_COMMA), LSFT(KC_DOT) ,    KC_PLUS,    KC_AMPR,  _______, \
  _______, _______, _______, _______, _______, _______, _______, _______,    KC_MNXT,    KC_VOLD, KC_VOLU, KC_MPLY \
),
/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |      |  F4 |  F3  |   F2 |  F1   |      |      |   7  |   8  |   9  |  *   |      |
 * |------+-----+------+------+----- -+-------------+------+------+------+------+------|
 * |      |  F8 |   F7 |   F6 |   F5  |      |      |   4  |   5  |   6  |   +  |      |
 * |------+-----+------+------+----- -+------|------+------+------+------+------+------|
 * |      |  12  | F11  |  F10 |  F9  |      |      |   1  |   2  |   3  |   /  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[LOWER] = KEYMAP( \
  _______, KC_F4,   KC_F3,   KC_F2,   KC_F1,   _______, _______, KC_7,    KC_8,    KC_9,    KC_0,    _______, \
  _______, KC_F8,   KC_F7,   KC_F6,   KC_F5,   _______, _______, KC_4, KC_5,  KC_6, KC_EQL, _______, \
  _______, KC_F12,  KC_F11,  KC_F10,  KC_F9,   _______,    KC_0, KC_1, KC_2, KC_3, KC_PGDN, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY \
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |ADJUST|  F4 |  F3  |   F2 |  F1   |      |      | HOME |  UP  |  END |  *   |      |
 * |------+-----+------+------+----- -+-------------+------+------+------+------+------|
 * |      |  F8 |   F7 |   F6 |   F5  |      |      | LEFT | DOWN | RIGHT|   +  |  \   |
 * |------+-----+------+------+----- -+------|------+------+------+------+------+------|
 * |      |  12  | F11  |  F10 |  F9  |      |      |   1  |   2  |   3  |   /  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[RAISE] = KEYMAP( \
  TG(ADJUST),  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_INS,    KC_HOME,    KC_UP,    KC_END,    KC_0,    KC_BSPC, \
  _______,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_LEFT, KC_DOWN,  KC_RIGHT, KC_RBRC, KC_BSLS, \
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, KC_PGUP, KC_PGDN, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY \
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[CODE] =  KEYMAP( \
  _______, RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL, \
  _______, _______, _______, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, _______,  _______, _______,  _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
),
/*
  Name 	Description
  RGB_TOG 	toggle on/off
  RGB_MOD 	cycle through modes
  RGB_HUI 	hue increase
  RGB_HUD 	hue decrease
  RGB_SAI 	saturation increase
  RGB_SAD 	saturation decrease
  RGB_VAI 	value increase
  RGB_VAD 	value decrease
*/
/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|LOnOff|LedMod|      |      |      |      | led- | led+ |      | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[ADJUST] =  KEYMAP( \
  _______, RESET , RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI, _______, KC_DEL, \
  _______, _______, _______, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, TO(QWERTY),  TO(JOAN), TO(MARC),  _______, _______, \
  _______, _______, _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
)

};


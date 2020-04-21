#include QMK_KEYBOARD_H
// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _ALPHAS 0
#define _MODS 1
#define _VIM 2
#define _NUMPAD 3
#define _CODE 4
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Alphas
 * ,--------------------------------------------------------------------------------------------.
 * | Tab    |   q  |  w  |   e  |    r    |  t   |   y  |   u   |   i  |   o  |   p    |   ins  |
 * |--------+------+-----+------+---------+------+------+-------+------+------+--------+--------|
 * |ctl(esc)|   a  |  s  |   d  |    f    |  g   |   h  |   j   |  k   |   l  |LT(2,;:)|sft(ent)|
 * |--------+------+-----+------+---------+------|------+-------+------+------+--------+--------|
 * |LSPO    |   z  |  x  |   c  |    v    |  b   |   n  |   m   |  ,<  |  .>  |   up   |  RSPC  |
 * |--------+------+-----+------+---------+------+------+-------+------+------+--------+--------|
 * | ctl    |  GUI | alt |MO(1) |lt(3,del)|Space |Space |bckspc |MO(4) | left |  down  |  right |
 * `--------------------------------------------------------------------------------------------'
 */
[_ALPHAS] = LAYOUT_ortho_4x12(
  KC_TAB,         KC_Q,    KC_W,    KC_E,  KC_R,         KC_T,   KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,          KC_INS,
  LCTL_T(KC_ESC), KC_A,    KC_S,    KC_D,  KC_F,         KC_G,   KC_H,   KC_J,    KC_K,    KC_L,    LT(2,KC_SCLN), RSFT_T(KC_ENT),
  KC_LSPO,        KC_Z,    KC_X,    KC_C,  KC_V,         KC_B,   KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_UP,         KC_RSPC,
  KC_LCTL,        KC_LGUI, KC_LALT, MO(1), LT(3,KC_DEL), KC_SPC, KC_SPC, KC_BSPC, MO(4),   KC_LEFT, KC_DOWN,       KC_RGHT
),

/* MODS
 * ,-----------------------------------------------------------------------------------.
 * |  `~   |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  | F10  |PrtSc |
 * |-------+------+------+------+------+-------------+------+------+------+------+------|
 * |Meh(F7)|  !   |   *  |   #  |  $   |  %   |  ^   |   &  |  *   |  '"  |  "   |  \|  |
 * |-------+------+------+------+------+------|------+------+------+------+------+------|
 * | LS/(  |  z   |   x  |  [{  |  ]   |   b  |  -_  |  =+  |  /?  |  \|  | PgUp | RS/) |
 * |-------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl  |      |      |      |      | spc  |  _   |bckspc|      | Home |PgDwn | End  |
 * `------------------------------------------------------------------------------------'
 */
[_MODS] =  LAYOUT_ortho_4x12(
    KC_GRV,          KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_PSCR,
    MEH(KC_F7),      KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_QUOT, KC_DQUO, KC_BSLS,
    LSFT_T(KC_LCBR), KC_Z,    KC_X,    KC_LBRC, KC_RBRC, KC_B,    KC_MINS, KC_EQL,  KC_SLSH, KC_BSLS, KC_PGUP, RSFT_T(KC_RCBR),
    KC_LCTL,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_SPC,  KC_UNDS, KC_BSPC, KC_NO,   KC_HOME, KC_PGDN, KC_END
),

/* VIM layer that adds vim navigation by holding the ; key. Includes keys like $,^ for end/beg of line and b,w,e,d,y. Also includes
 * quick keys for excel like alt(=) for sum, ctl(+) & ctl(-) to add/remove columns/rows.
 * ,--------------------------------------------------------------------------------------.
 * |  Tab   |  "'  |  b  |  w  |   e    |  d  |   y  | Vol- | Vol+ | TO(0)|  TG(2) |reset |
 * |--------+------+-----+-----+--------+-----+------+------+------+------+--------+------|
 * |Ctl(Esc)| Home |Home |Pg Up|Pg Down | End | Left | Down |  Up  |Right |LT(2,;:)|Enter |
 * |--------+------+-----+-----+--------+-----|------+------+------+------+--------+------|
 * | sft    |  ;:  |  q  |  ^  |   $    |  x  |alt(=)|ctl(+)|ctl(-)|      |        |      |
 * |--------+------+-----+-----+--------+-----+------+------+------+------+--------+------|
 * | Ctl    |  GUI | alt | sft |sft(ctl)| spc |  del | bspc |      |      |        |      |
 * `--------------------------------------------------------------------------------------'
 */
[_VIM] =  LAYOUT_ortho_4x12(
    KC_TAB,         KC_QUOT, KC_B,    KC_W,    KC_E,          KC_D,   KC_Y,         KC_VOLD,       KC_VOLU,       TO(0),   TG(2),         RESET,
    LCTL_T(KC_ESC), KC_HOME, KC_HOME, KC_PGUP, KC_PGDN,       KC_END, KC_LEFT,      KC_DOWN,       KC_UP,         KC_RGHT, LT(2,KC_SCLN), KC_ENT,
    KC_LSFT,        KC_SCLN, KC_Q,    KC_CIRC, KC_DLR,        KC_X,   RALT(KC_EQL), RCTL(KC_PLUS), RCTL(KC_PMNS), KC_NO,   KC_NO,         KC_TRNS,
    KC_LCTL,        KC_LGUI, KC_LALT, KC_LSFT, LSFT(KC_LCTL), KC_SPC, KC_DEL,       KC_BSPC,       KC_NO,         KC_NO,   KC_NO,         KC_TRNS
),

/* NUMPAD: Numpad with operators and other keys
 * ,-------------------------------------------------------------------------------------.
 * |  [{  |   !  |   @  |   #  |   $  |   %  |  (   |   7  |  8   |   9  |  )   |   ]}   |
 * |------+------+------+------+------+-------------+------+------+------+------+--------|
 * |  {   |  /   |   *  |   -  |  +   |      |  =   |   4  |  5   |  6   |  ;:  |   }    |
 * |------+------+------+------+------+------|------+------+------+------+------+--------|
 * | sft( |      |      |      |      |      |      |   1  |  2   |  3   |      |kc_sft()|
 * |------+------+------+------+------+------+------+------+------+------+------+--------|
 * |      |      |      |      |      |Space |Space |   0  |      |      |      |        |
 * `-------------------------------------------------------------------------------------'
 */
[_NUMPAD] =  LAYOUT_ortho_4x12(
    KC_LBRC, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_LPRN, KC_7, KC_8,  KC_9,  KC_RPRN, KC_RBRC,
    KC_LCBR, KC_PSLS, KC_PAST, KC_PMNS, KC_PPLS, KC_NO,   KC_EQL,  KC_4, KC_5,  KC_6,  KC_SCLN, KC_RCBR,
    KC_LSPO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_TRNS, KC_1, KC_2,  KC_3,  KC_PEQL, KC_RSPC,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_SPC,  KC_0, KC_NO, KC_NO, KC_NO,   KC_NO
),

/* CODE
 * ,---------------------------------------------------------------------------.
 * | ~` | F11 | F12 | 3  |  4  |  5  |  6   |   :  |   -  |   >  |   0  |  Del |
 * |----+-----+-----+----+-----+-------------+------+-----+------+------+------|
 * |    |  /  |  *  | {  | [{  |  (  |   )  |  ]}  |  }   |  '"  |  ]}  |  \|  |
 * |----+-----+-----+----+-----+-----|------+------+------+------+------+------|
 * |    | F7  | F8  | F9 | F10 | F11 |   ~  |  =   |  \   |RGBTOG|RGBHUI|RGBHUD|
 * |----+-----+-----+----+-----+-----+------+------+------+------+------+------|
 * |    |     |     |    |     |     |      |      |      |RGBVAD|RBGVAI|RGBMOD|
 * `---------------------------------------------------------------------------'
 */
[_CODE] =  LAYOUT_ortho_4x12( \
    KC_GRV,  KC_F11,  KC_F12,  KC_3,    KC_4,    KC_5,    KC_6,    KC_COLN, KC_MINS, KC_GT,   KC_0,    KC_DEL, \
    KC_TRNS, KC_PSLS, KC_PAST, KC_LCBR, KC_LBRC, KC_LPRN, KC_RPRN, KC_RBRC, KC_RCBR, KC_QUOT, KC_RBRC, KC_BSLS, \
    KC_TRNS, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_TILD, KC_EQL,  KC_NUBS, RGB_TOG, RGB_HUI, RGB_HUD, \
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RGB_VAD, RGB_VAI, RGB_MOD \
)

};

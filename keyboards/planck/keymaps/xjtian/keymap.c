#include QMK_KEYBOARD_H


enum planck_layers {
    _QWERTY,
    _NUM,
    _SYMBOL,
    _FUNCTION,
    _ADJUST
};

#define MON MO(_NUM)
#define MOS MO(_SYMBOL)
#define MOF MO(_FUNCTION)
#define MOA MO(_ADJUST)
#define LTS LT(_SYMBOL, KC_ESC)
#define LTN LT(_NUM, KC_ENT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,---------------------------------------------------------------------------------------------------------.
 * |  Tab  |   Q  |   W  |   E   |     R    |    T    |   Y   |     U    |   I   |   O    |   P  |   Bksp    |
 * |-------+------+------+-------+----------+---------+-------+----------+-------+--------+------+-----------|
 * |Esc/Ctl|   A  |   S  |   D   |     F    |    G    |   H   |     J    |   K   |   L    |   ;  |    "      |
 * |-------+------+------+-------+----------+---------+-------+----------+-------+--------+------+-----------|
 * | Shift |   Z  |   X  |   C   |     V    |    B    |   N   |     M    |   ,   |   .    |   /  |Enter/Shift|
 * |-------+------+------+-------+----------+---------+-------+----------+-------+--------+------+-----------|
 * |  Ctrl |L(Fn) | Alt  |   OS  |Esc/L(Sym)|Shft/Bksp| Space |Ent/L(Num)|OS/Left|Alt/Down|Ctl/Up|   Right   |
 * `---------------------------------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_ortho_4x12(
    KC_TAB,         KC_Q,  KC_W,    KC_E,     KC_R, KC_T,           KC_Y,   KC_U, KC_I,           KC_O,           KC_P,           KC_BSPC,
    CTL_T(KC_ESC),  KC_A,  KC_S,    KC_D,     KC_F, KC_G,           KC_H,   KC_J, KC_K,           KC_L,           KC_SCLN,        KC_QUOT,
    KC_LSFT,        KC_Z,  KC_X,    KC_C,     KC_V, KC_B,           KC_N,   KC_M, KC_COMM,        KC_DOT,         KC_SLSH,        RSFT_T(KC_ENT),
    KC_LCTL,        MOF,   KC_LALT, KC_LGUI,  LTS,  SFT_T(KC_BSPC), KC_SPC, LTN,  GUI_T(KC_LEFT), ALT_T(KC_DOWN), CTL_T(KC_UP),   KC_RGHT
),


/* Numbers, calculator
 * ,-------------------------------------------------------------------------.
 * |      |     |     |     |     |     |     |  =  |  -  |  *  |  /  | Bksp |
 * |------+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+------|
 * |  v   |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |      |
 * |------+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+------|
 * |  v   |     |     |     |     |     |     |     |  ,  |  .  |     |  v   |
 * |------+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+------|
 * |  v   |  v  |  v  |  v  |L(Ad)|  v  |  v  |  v  | OS  | Alt | Ctl |      |
 * `-------------------------------------------------------------------------'
 */
[_NUM] = LAYOUT_ortho_4x12(
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,   KC_NO,   KC_EQUAL, KC_MINUS, KC_PAST, KC_SLSH,  KC_BSPC,
    _______, KC_1,    KC_2,    KC_3,    KC_4,  KC_5,    KC_6,    KC_7,     KC_8,     KC_9,    KC_0,     KC_NO,
    _______, KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,   KC_NO,   KC_NO,    KC_COMM,  KC_DOT,  KC_NO,    _______,
    _______, _______, _______, _______, MOA,   _______, _______, _______,  KC_RGUI,  KC_RALT, KC_RCTRL, KC_NO
),

/* Symbols
 * ,------------------------------------------------------------------------.
 * |  `  |  !  |  @  |  #  |  $  |  %  |  ^  |  &  |  *  |  -  |  =  | Bksp |
 * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+------|
 * |  v  |     |  |  |  {  |  (  |  [  |  ]  |  )  |  }  |  \  |  '  |      |
 * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+------|
 * |  v  |  ~  |     |     |     |     |     |     |     |  _  |  +  |  v   |
 * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+------|
 * |  v  |  v  |  v  |  v  |  v  |  v  |  v  |L(Ad)| OS  | Alt | Ctl |      |
 * `------------------------------------------------------------------------'
 */
[_SYMBOL] = LAYOUT_ortho_4x12(
    KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_MINS, KC_EQL,   KC_BSPC,
    _______, KC_NO,   KC_PIPE, KC_LCBR, KC_LPRN, KC_LBRC, KC_RBRC, KC_RPRN, KC_RCBR, KC_BSLS, KC_QUOT,  KC_NO,
    _______, KC_TILD, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_UNDS, KC_PLUS,  _______,
    _______, _______, _______, _______, _______, _______, _______, MOA,     KC_RGUI, KC_RALT, KC_RCTRL, KC_NO
),

/* Function keys
 * ,------+------+------+------+------+------+------+------+------+------+------+------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  | F10  | F11  | F12  |
 * +------+------+------+------+------+------+------+------+------+------+------+------|
 * |  v   |      |      |      | Home |      |      | End  |      |      |      |      |
 * +------+------+------+------+------+------+------+------+------+------+------+------|
 * |  v   |      |      |      |      |      |      |      |      |      |      |  v   |
 * +------+------+------+------+------+------+------+------+------+------+------+------|
 * |  v   |  v   |  v   |  v   |  v   |  v   |  v   |   v  |  OS  | Alt  | Ctl  |      |
 * .-----------------------------------------------------------------------------------'
 */
[_FUNCTION] = LAYOUT_ortho_4x12(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,   KC_F12,
    _______, KC_NO,   KC_NO,   KC_NO,   KC_HOME, KC_NO,   KC_NO,   KC_END,  KC_NO,   KC_NO,   KC_NO,    KC_NO,
    _______, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    _______,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_RGUI, KC_RALT, KC_RCTRL, KC_NO
),

/* Adjust (Num + Symbol)
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      | Left | Down |  Up  | Right|      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |Rewind| Vol- | Stop | Play | Vol+ | Skip |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |QK_BOOT |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_ortho_4x12(
    KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_MRWD, KC_VOLD, KC_MSTP, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_MRWD, KC_VOLD, KC_MSTP, KC_MPLY, KC_VOLU, KC_MFFD, KC_NO,   KC_NO, KC_NO,
    QK_BOOT, KC_NO, KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO
),
};

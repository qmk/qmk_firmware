/* Based on the default layout of the kyria keymap, 
 * modified to fit my needs. 
 * author: smerck
 * Modifications from base layout:
 * 
 * * Removed colemak, dvorak mappings
 * * removed adjust layer, moved rgb controls to nav layer
 * * moved thumb modifier key mappings
 * * changed NUM mappings, added mirrors braces/brackets around homerow
 * * changed to right_shift/enter key for right shift  
 */
#include QMK_KEYBOARD_H

enum layers {
    _QWERTY = 0,
    _NAV,
    _NUM,
    _SYM,
    _FUNCTION,
};


// Aliases for readability
#define QWERTY   DF(_QWERTY)

#define NUM      MO(_NUM)
#define NAV      MO(_NAV)
#define FKEYS    MO(_FUNCTION)

// modtap macros
#define CTL_ESC  MT(MOD_LCTL, KC_ESC)
#define CTL_QUOT MT(MOD_RCTL, KC_QUOTE)
#define CTL_MINS MT(MOD_RCTL, KC_MINUS)
#define ALT_ENT  MT(MOD_LALT, KC_ENT)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: QWERTY
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  Tab   |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |  Bksp  |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |Ctrl/Esc|   A  |   S  |   D  |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : |Ctrl/' "|
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  | [ {  |F-Keys|  |F-keys|  ] } |   N  |   M  | ,  < | . >  | /  ? | RShift |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |LAlt  | NUM  | CMD  | Space| NAV  |  | NAV  | Space| CMD  | NUM  | RAlt |
 *                        |      | LAYER|      |      | LAYER|  | LAYER|      |      | LAYER|      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_QWERTY] = LAYOUT(
     KC_TAB  , KC_Q ,  KC_W   ,  KC_E  ,   KC_R ,   KC_T ,                                        KC_Y,   KC_U ,  KC_I ,   KC_O ,  KC_P , KC_BSPC,
     CTL_ESC , KC_A ,  KC_S   ,  KC_D  ,   KC_F ,   KC_G ,                                        KC_H,   KC_J ,  KC_K ,   KC_L ,KC_SCLN,CTL_QUOT,
     KC_LSFT , KC_Z ,  KC_X   ,  KC_C  ,   KC_V ,   KC_B , KC_LBRC, FKEYS,     FKEYS  , KC_RBRC, KC_N,   KC_M ,KC_COMM, KC_DOT ,KC_SLSH, KC_SFTENT,
                            KC_LALT, NUM, KC_LGUI, KC_SPC , NAV   ,    NAV , KC_SPC,KC_RGUI, NUM, KC_RALT
    ),

/*
 * Nav Layer: Media, navigation
 *
 * ,----------------------------------------------------------.                              ,-------------------------------------------.
 * |        | RGB_TOG | RGB_SAI | RGB_HUI | RGB_VAI | RGB_MOD  |                              | PgUp | Home |   ↑  | End  | VolUp| Delete |
 * |--------+---------+---------+---------+---------+--------- |                              |------+------+------+------+------+--------|
 * |        |         | RGB_SAD | RGB_HUD | RGB_VAD | RGB_RMOD |                              | PgDn |  ←   |   ↓  |   →  | VolDn| Insert |
 * |--------+---------+---------+---------+---------+----------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |         |         |         |         |          |      |ScLck |  |      |      | Pause|M Prev|M Play|M Next|VolMut| PrtSc  |
 * `----------------------------+---------+---------+----------+------+------|  |------+------+------+------+------+----------------------'
 *                              |         |         |          |      |      |  |      |      |      |      |      |
 *                              |         |         |          |      |      |  |      |      |      |      |      |
 *                              `--------------------------------------------'  `----------------------------------'
 */
    [_NAV] = LAYOUT(
      _______, RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI,  RGB_MOD,                                     KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_VOLU, KC_DEL,
      _______, _______, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD,                                     KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_VOLD, KC_INS,
      _______, _______, _______, _______, _______, _______, _______, KC_SLCK, _______, _______,KC_PAUSE, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_PSCR,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

/*
 * Sym Layer: Numbers 
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |    `   |  1   |  2   |  3   |  4   |  5   |                              |   6  |  7   |  8   |  9   |  0   |   =    |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |    ~   |  !   |  @   |  #   |  $   |  %   |                              |   ^  |  &   |  *   |  (   |  )   |   +    |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |    |   |   \  |  (   |  _   |  [   |  {   |      |      |  |      |      |   }  |  ]   |  -  |  )   |  \   |   |    |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
// Removing unnecessary symbols (symbols not represented in the base layer) from this layout
    [_NUM] = LAYOUT(
      KC_GRV ,   KC_1 ,   KC_2 ,   KC_3 ,   KC_4 ,   KC_5 ,                                       KC_6 ,   KC_7 ,   KC_8 ,   KC_9 ,   KC_0 , KC_EQL ,
     KC_TILD , KC_EXLM,  KC_AT , KC_HASH,  KC_DLR, KC_PERC,                                     KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PLUS,
     KC_PIPE , KC_BSLS, KC_LPRN, KC_UNDS, KC_LBRC, KC_LCBR, _______, _______, _______, _______, KC_RCBR, KC_RBRC, KC_MINS, KC_RPRN, KC_BSLS, KC_PIPE,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

/*
 * Function Layer: Function keys
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  F9  | F10  | F11  | F12  |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  F5  |  F6  |  F7  |  F8  |      |                              |      | Shift| Ctrl |  Alt |  GUI |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  F1  |  F2  |  F3  |  F4  |      |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_FUNCTION] = LAYOUT(
      _______,  KC_F9 ,  KC_F10,  KC_F11,  KC_F12, _______,                                     _______, _______, _______, _______, _______, _______,
      _______,  KC_F5 ,  KC_F6 ,  KC_F7 ,  KC_F8 , _______,                                     _______, KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI, _______,
      _______,  KC_F1 ,  KC_F2 ,  KC_F3 ,  KC_F4 , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

};


#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"

#include <stdarg.h>

/* use UK keymap */

#define UK_HASH KC_NONUS_HASH
#define UK_BSLS KC_NONUS_BSLASH
#define UK_PIPE LSFT(UK_BSLS)

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define NUMB 2 // numbers and hex
#define CRSR 3 // cursor keys
#define MOUS 4 // mouse keys
#define KEYW 5 // keyword macros
#define EMAC 6 // emacs

// my macros
#define UM_ECET   M(0)  // { }
#define UM_0x     M(1)
#define UM_PUB    M(2)
#define UM_PRO    M(3)
#define UM_PRV    M(4)
#define UM_CLS    M(5)
#define UM_STR    M(6)
#define UM_RET    M(7)
#define UM_INC    M(8)
#define UM_OBJ    M(9)
#define UM_GITLOG M(10)
#define UM_GOODM  M(11)
#define UM_NAMESP M(12)
#define UM_EMTR   M(14) // emacs toggle read-only
#define UM_EMWR   M(15) // emacs write buffer (save)
#define UM_EMUN   M(16) // emacs undo
#define UM_EMRE   M(17) // emacs redo
#define UM_EMPB   M(18) // emacs previous buffer
#define UM_EMNB   M(19) // emacs next buffer
#define UM_GOODN  M(20)
#define UM_ECETS  M(22)  // { };
#define UM_TMPL   M(23)
#define UM_TYPN   M(24)
#define UM_CONT   M(25)
#define UM_BREAK  M(26)
#define UM_CONST  M(27)
#define UM_SMILY  M(28)
#define UM_SADF   M(29)
#define UM_SCARF  M(30)
#define UM_DECAF  M(31)
#define UM_OPER   M(32)
#define UM_NULP   M(33)
#define UM_EXTR   M(34)
#define UM_VIRT   M(35)
#define UM_EMFB   M(36) // emacs font bigger
#define UM_EMFS   M(37) // emacs font smaller
#define UM_VOLAT  M(38)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Base layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | ESC    |   1  |   2  |   3  |   4  |   5  | SfLt |           | SfRt |   6  |   7  |   8  |   9  |   0  | BkSp   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |  L1  |           |  L1  |   Y  |   U  |   I  |   O  |   P  | Del    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | Caps/L2|   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |Enter/L2|
 * |--------+------+------+------+------+------|  L6  |           |  L6  |------+------+------+------+------+--------|
 * | LSft/( |   Z  |   X  |   C  | V/L3 | B/L4 |      |           |      | N/L4 | M/L3 |   ,  |   .  |   /  | RSft/) |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |Ctrl/[| Alt/]|   #  | Left |Right |                                       |  Up  | Down |   -  | Alt/[|Ctrl/]|
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |  L2  | lead |       | lead |  Ins |
 *                                 ,------|------|------|       |------+------+------.
 *                                 | Space| BkSp | Home |       | PgUp | Enter|Space |
 *                                 |  /   |  /   |------|       |------|   /  |  /   |
 *                                 | Ctrl | Alt  |End/L5|       |PDn/L5|  Alt | Ctrl |
 *                                 `--------------------'       `--------------------'
 */
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_ESC,            KC_1,            KC_2,       KC_3,      KC_4,           KC_5,           LSFT(KC_LEFT),
        KC_TAB,            KC_Q,            KC_W,       KC_E,      KC_R,           KC_T,           MO(SYMB),
        LT(NUMB, KC_CAPS), KC_A,            KC_S,       KC_D,      KC_F,           KC_G,
        KC_LSPO,           KC_Z,            KC_X,       KC_C,      LT(CRSR, KC_V), LT(MOUS, KC_B), MO(EMAC),
        CTL_T(KC_LBRC),    ALT_T(KC_RBRC),  UK_HASH,    KC_LEFT,   KC_RGHT,
                                                                                     TG(NUMB),        KC_LEAD,
                                                                                                      KC_HOME,
                                                                     CTL_T(KC_SPC),  ALT_T(KC_BSPC),  LT(KEYW, KC_END),
        // right hand
             LSFT(KC_RGHT),   KC_6,            KC_7,            KC_8,      KC_9,       KC_0,             KC_BSPC,
             MO(SYMB),        KC_Y,            KC_U,            KC_I,      KC_O,       KC_P,             KC_DELT,
                              KC_H,            KC_J,            KC_K,      KC_L,       KC_SCLN,          LT(NUMB, KC_ENT),
             MO(EMAC),        LT(MOUS, KC_N),  LT(CRSR, KC_M),  KC_COMM,   KC_DOT,     KC_SLSH,          KC_RSPC,
                                               KC_UP,           KC_DOWN,   KC_MINS,    ALT_T(KC_LBRC),   CTL_T(KC_RBRC),
           KC_LEAD,            KC_INS,
           KC_PGUP,
           LT(KEYW, KC_PGDN),  ALT_T(KC_ENT),   CTL_T(KC_SPC)
    ),
/* Keymap 1: Symbol Layer with F keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   ##   |  F1  |  F2  |  F3  |  F4  |  F5  |  ##  |           |  ##  |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |--------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |   ##   |   !  |   "  |   £  |   $  |   %  |  ##  |           |  ##  |   -  |   +  |   =  |   @  |   ~  |   F12  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |   ##   |   ^  |   &  |   *  |   _  |   #  |------|           |------|   {  |   }  |   ;  |   '  |   #  |   ##   |
 * |--------+------+------+------+------+------|  ##  |           |  ##  |------+------+------+------+------+--------|
 * |   ##   |   \  |   |  |   `  |   -  |   /  |      |           |      |   [  |   ]  |   <  |   >  |   ?  |   ##   |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |  ##  |  ##  |  ##  |  ##  |  ##  |                                       |  ##  |  ##  |  ##  |  ##  |  ##  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |  ##  |  ##  |       |  ##  |  ##  |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |  ##  |       |  ##  |      |      |
 *                                 |  ##  |  ##  |------|       |------|  ##  |  ##  |
 *                                 |      |      |  ##  |       |  ##  |      |      |
 *                                 `--------------------'       `--------------------'
 */
[SYMB] = LAYOUT_ergodox(
        // left hand
        KC_TRNS,   KC_F1,       KC_F2,       KC_F3,       KC_F4,          KC_F5,       KC_TRNS,
        KC_TRNS,   KC_EXLM,     LSFT(KC_2),  LSFT(KC_3),  LSFT(KC_4),     LSFT(KC_5),  KC_TRNS,
        KC_TRNS,   LSFT(KC_6),  LSFT(KC_7),  LSFT(KC_8),  LSFT(KC_MINS),  UK_HASH,
        KC_TRNS,   UK_BSLS,     UK_PIPE,     KC_GRV,      KC_MINS,        KC_SLSH,     KC_TRNS,
        KC_TRNS,   KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,
                                                                            KC_TRNS,   KC_TRNS,
                                                                                       KC_TRNS,
                                                                 KC_TRNS,   KC_TRNS,   KC_TRNS,
        // right hand
             KC_TRNS,   KC_F6,       KC_F7,       KC_F8,          KC_F9,          KC_F10,         KC_F11,
             KC_TRNS,   KC_MINS,     KC_PLUS,     KC_EQL,         LSFT(KC_QUOT),  LSFT(UK_HASH),  KC_F12,
                        KC_LCBR,     KC_RCBR,     KC_SCLN,        KC_QUOT,        UK_HASH,        KC_TRNS,
             KC_TRNS,   KC_LBRC,     KC_RBRC,     LSFT(KC_COMM),  LSFT(KC_DOT),   LSFT(KC_SLSH),  KC_TRNS,
                                     KC_TRNS,     KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
           KC_TRNS,   KC_TRNS,
           KC_TRNS,
           KC_TRNS,   KC_TRNS,  KC_TRNS
    ),
/* Keymap 2: Numerics and hex
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |   ##    |  A   |  B   |  C   |  D   |  E   |  F   |           |  A   |  B   |  C   |  D   |   E  |   F  |   ##   |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |   ##    |  *   |  7   |  8   |  9   |  *   |  0x  |           |  0x  |  *   |   7  |   8  |   9  |   *  |   ##   |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |   ##    |  /   |  4   |  5   |  6   |  /   |------|           |------|  /   |   4  |   5  |   6  |   /  |   ##   |
 * |---------+------+------+------+------+------|  ##  |           |  ##  |------+------+------+------+------+--------|
 * |   ##    |  -   |  1   |  2   |  3   |  -   |      |           |      |  -   |   1  |   2  |   3  |   -  |   ##   |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |   =   |  +   |  0   |  ,   |  .   |                                       |   0  |   ,  |   .  |   +  |  =   |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |  ##  |  ##  |       |  ##  |  ##  |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |  ##  |       |  ##  |      |      |
 *                                 |  ##  |  ##  |------|       |------|  ##  |  ##  |
 *                                 |      |      |  ##  |       |  ##  |      |      |
 *                                 `--------------------'       `--------------------'
 */
[NUMB] = LAYOUT_ergodox(
        // left hand
        KC_TRNS,   KC_A,        KC_B,        KC_C,        KC_D,           KC_E,        KC_F,
        KC_TRNS,   KC_ASTR,     KC_7,        KC_8,        KC_9,           KC_ASTR,     UM_0x,
        KC_TRNS,   KC_SLSH,     KC_4,        KC_5,        KC_6,           KC_SLSH,
        KC_TRNS,   KC_MINS,     KC_1,        KC_2,        KC_3,           KC_MINS,     KC_TRNS,
        KC_EQL,    KC_PLUS,     KC_0,        KC_COMM,     KC_DOT,
                                                                            KC_TRNS,   KC_TRNS,
                                                                                       KC_TRNS,
                                                                 KC_TRNS,   KC_TRNS,   KC_TRNS,
        // right hand
             KC_A,      KC_B,        KC_C,        KC_D,           KC_E,           KC_F,           KC_TRNS,
             UM_0x,     KC_ASTR,     KC_7,        KC_8,           KC_9,           KC_ASTR,        KC_TRNS,
                        KC_SLSH,     KC_4,        KC_5,           KC_6,           KC_SLSH,        KC_TRNS,
             KC_TRNS,   KC_MINS,     KC_1,        KC_2,           KC_3,           KC_MINS,        KC_TRNS,
                                     KC_0,        KC_COMM,        KC_DOT,         KC_PLUS,        KC_EQL,
           KC_TRNS,   KC_TRNS,
           KC_TRNS,
           KC_TRNS,   KC_TRNS,   KC_TRNS
    ),
/* Keymap 3: Cursor movement
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |         |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         | Home |      |  Up  |      | PgUp |      |           |      | PgUp |      |  Up  |      | Home |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         | End  | Left | Down | Right| PgDn |------|           |------| PgDn | Left | Down | Right| End  |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |   ##    |  Up  |      | Down |  ##  |      |      |           |      |      |  ##  | Down |      |  Up  |   ##   |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | Left  | Down | Right|      |      |                                       |      |      | Left | Down | Right|
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |  ##  |  ##  |------|       |------|  ##  |  ##  |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[CRSR] = LAYOUT_ergodox(
        // left hand
        KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,
        KC_NO,     KC_HOME,   KC_NO,     KC_UP,     KC_NO,     KC_PGUP,   KC_NO,
        KC_NO,     KC_END,    KC_LEFT,   KC_DOWN,   KC_RGHT,   KC_PGDN,
        KC_TRNS,   KC_UP,     KC_NO,     KC_DOWN,   KC_TRNS,   KC_NO,     KC_NO,
        KC_LEFT,   KC_DOWN,   KC_RGHT,   KC_NO,     KC_NO,
                                                                   KC_NO,     KC_NO,
                                                                              KC_NO,
                                                        KC_TRNS,   KC_TRNS,   KC_NO,
        // right hand
             KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,
             KC_NO,     KC_PGUP,   KC_NO,     KC_UP,     KC_NO,     KC_HOME,   KC_NO,
                        KC_PGDN,   KC_LEFT,   KC_DOWN,   KC_RGHT,   KC_END,    KC_NO,
             KC_NO,     KC_NO,     KC_TRNS,   KC_DOWN,   KC_NO,     KC_UP,     KC_TRNS,
                                   KC_NO,     KC_NO,     KC_LEFT,   KC_DOWN,   KC_RGHT,
           KC_NO,   KC_NO,
           KC_NO,
           KC_NO,   KC_TRNS,   KC_TRNS
    ),
/* Keymap 4: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      | Lclk | MsUp | Rclk |      |      |           |      |      | Lclk | MsUp | Rclk |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      |MsLeft|MsDown|MsRght|      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  Lclk  | MsUp | Rclk |MsDown|      |  ##  |      |           |      |  ##  |      |MsDown| Lclk | MsUp | Rclk   |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |MsLeft|MsDown|MsRight      |      |                                       |      |      |MsLeft|MsDown|MsRght|
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[MOUS] = LAYOUT_ergodox(
        // left hand
        KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,
        KC_NO,     KC_NO,     KC_BTN1,   KC_MS_U,   KC_BTN2,   KC_NO,     KC_NO,
        KC_NO,     KC_NO,     KC_MS_L,   KC_MS_D,   KC_MS_R,   KC_NO,
        KC_BTN1,   KC_MS_U,   KC_BTN2,   KC_MS_D,   KC_NO,     KC_TRNS,   KC_NO,
        KC_MS_L,   KC_MS_D,   KC_MS_R,   KC_NO,     KC_NO,
                                                                   KC_NO,   KC_NO,
                                                                            KC_NO,
                                                          KC_NO,   KC_NO,   KC_NO,
        // right hand
             KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,
             KC_NO,     KC_NO,     KC_BTN1,   KC_MS_U,   KC_BTN2,   KC_NO,     KC_NO,
                        KC_NO,     KC_MS_L,   KC_MS_D,   KC_MS_R,   KC_NO,     KC_NO,
             KC_NO,     KC_TRNS,   KC_NO,     KC_MS_D,   KC_BTN1,   KC_MS_U,   KC_BTN2,
                                   KC_NO,     KC_NO,     KC_MS_L,   KC_MS_D,   KC_MS_R,
           KC_NO,   KC_NO,
           KC_NO,
           KC_NO,   KC_NO,   KC_NO
    ),
/* Keymap 5: Keywords
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |         |      |      | scarf| sadf | smily|      |           |      | decaf|      |      |      |      |        |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         | const| volat| oper |  ret | tmpl |      |           |      | typen| cont |  prv |  pro | pub  |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |      |  str |  obj |      | gitl |------|           |------|      |      |      | nulp |      |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |      | extr |  cls | virt | break|      |           |      |namesp| goodm| goodn|      |      |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |       |      |  inc |      |      |                                       |      |      |      |      |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       | ecet | ecets|
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |  ##  |       |  ##  |      |      |
 *                                 `--------------------'       `--------------------'
 */
[KEYW] = LAYOUT_ergodox(
        // left hand
        KC_NO,     KC_NO,     KC_NO,     UM_SCARF,  UM_SADF,   UM_SMILY,   KC_NO,
        KC_NO,     UM_CONST,  UM_VOLAT,  UM_OPER,   UM_RET,    UM_TMPL,    KC_NO,
        KC_NO,     KC_NO,     UM_STR,    UM_OBJ,    KC_NO,     UM_GITLOG,
        KC_NO,     KC_NO,     UM_EXTR,   UM_CLS,    UM_VIRT,   UM_BREAK,   KC_NO,
        KC_NO,     KC_NO,     UM_INC,    KC_NO,     KC_NO,
                                                                   KC_NO,    KC_NO,
                                                                             KC_NO,
                                                          KC_NO,   KC_NO,    KC_TRNS,
        // right hand
             KC_NO,     UM_DECAF,  KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,
             KC_NO,     UM_TYPN,   UM_CONT,   UM_PRV,    UM_PRO,    UM_PUB,    KC_NO,
                        KC_NO,     KC_NO,     KC_NO,     UM_NULP,   KC_NO,     KC_NO,
             KC_NO,     UM_NAMESP, UM_GOODM,  UM_GOODN,  KC_NO,     KC_NO,     KC_NO,
                                   KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,
           UM_ECET,  UM_ECETS,
           KC_NO,
           KC_TRNS,  KC_NO,   KC_NO
    ),
/* Keymap 6: emacs
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |         |      |      |      |      |      | empb |           | emnb | emfs | emfb |      |      |      |        |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         | emtr |      |      |      |      |      |           |      | emun | emre | w-up |      |      |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |      | emwr |      |      |      |------|           |------|      |w-left|w-down|w-rght|      |        |
 * |---------+------+------+------+------+------|  ##  |           |  ##  |------+------+------+------+------+--------|
 * |         |      |      |      |      |      |      |           |      |      |      |w-down|      |      |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |       |      |      |      |      |                                       |      |      |      |      |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[EMAC] = LAYOUT_ergodox(
        // left hand
        KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     UM_EMPB,
        KC_NO,     UM_EMTR,   KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,
        KC_NO,     KC_NO,     UM_EMWR,   KC_NO,     KC_NO,     KC_NO,
        KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_TRNS,
        KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,
                                                                   KC_NO,   KC_NO,
                                                                            KC_NO,
                                                          KC_NO,   KC_NO,   KC_NO,
        // right hand
             UM_EMNB,   UM_EMFS,  UM_EMFB,        KC_NO,          KC_NO,          KC_NO,     KC_NO,
             KC_NO,     UM_EMUN,  UM_EMRE,        LSFT(KC_UP),    KC_NO,          KC_NO,     KC_NO,
                        KC_NO,    LSFT(KC_LEFT),  LSFT(KC_DOWN),  LSFT(KC_RGHT),  KC_NO,     KC_NO,
             KC_TRNS,   KC_NO,    KC_NO,          LSFT(KC_DOWN),  KC_NO,          KC_NO,     KC_NO,
                                  KC_NO,          KC_NO,          KC_NO,          KC_NO,     KC_NO,
           KC_NO,   KC_NO,
           KC_NO,
           KC_NO,   KC_NO,   KC_NO
    ),
};

enum next_key_down_up {
    NK_DOWN_UP,
    NK_DOWN,
    NK_UP // a bit of a hack, this works as long as NK_UP < KC_A
};

void send_keystrokes(uint8_t key, ...)
{
    va_list vl;
    va_start(vl, key);
    enum next_key_down_up nkdu = NK_DOWN_UP;
    while (key != KC_NO) {
        if (key < KC_A) {
            nkdu = key;
        } else {
            switch (nkdu) {
            case NK_DOWN_UP:
                register_code(key);
            case NK_UP:
                unregister_code(key);
                break;
            case NK_DOWN:
                register_code(key);
            }
            nkdu = NK_DOWN_UP;
        }
        key = va_arg(vl, int);
    }
    va_end(vl);
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
    switch(id) {
    case 0: // { }
        if (record->event.pressed) {
            return MACRO(T(ENT), D(LSFT), T(LBRC), U(LSFT), T(ENT),
                         D(LSFT), T(RBRC), U(LSFT), T(UP),
                         T(TAB), END);
        }
        break;
    case 1:
        if (record->event.pressed) {
            return MACRO(T(0), T(X), END);
        }
        break;
    case 2:
        if (record->event.pressed) {
            SEND_STRING("public");
        }
        break;
    case 3:
        if (record->event.pressed) {
            SEND_STRING("protected");
        }
        break;
    case 4:
        if (record->event.pressed) {
            SEND_STRING("private");
        }
        break;
    case 5: // class
        if (record->event.pressed) {
            return MACRO(T(C), T(L), T(A), T(S), T(S), T(ENT),
                         D(LSFT), T(LBRC), U(LSFT), T(ENT),
                         T(P), T(U), T(B), T(L), T(I), T(C),
                         D(LSFT), T(SCLN), U(LSFT), T(ENT), T(ENT),
                         T(P), T(R), T(I), T(V), T(A), T(T), T(E),
                         D(LSFT), T(SCLN), U(LSFT), T(ENT),
                         D(LSFT), T(RBRC), U(LSFT), T(SCLN), T(ENT),
                         T(UP), T(UP), T(UP), T(UP), T(UP), T(UP), T(UP),
                         T(END), T(SPC), END);
        }
        break;
    case 6: // struct
        if (record->event.pressed) {
            return MACRO(T(S), T(T), T(R), T(U), T(C), T(T), T(ENT),
                         D(LSFT), T(LBRC), U(LSFT), T(ENT),
                         D(LSFT), T(RBRC), U(LSFT), T(SCLN), T(ENT),
                         T(UP), T(UP), T(UP), T(UP),
                         T(END), T(SPC), END);
        }
        break;
    case 7:
        if (record->event.pressed) {
            SEND_STRING("return");
        }
        break;
    case 8: // #include
        if (record->event.pressed) {
            return MACRO(T(NONUS_HASH), T(I), T(N), T(C), T(L), T(U), T(D), T(E), END);
        }
        break;
    case 9:
        if (record->event.pressed) {
            SEND_STRING("objdump -CT -x -d");
        }
        break;
    case 10:
        if (record->event.pressed) {
            SEND_STRING("git log --oneline --graph --decorate=short");
        }
        break;
    case 11:
        if (record->event.pressed) {
            SEND_STRING("good morning");
        }
        break;
    case 12:
        if (record->event.pressed) {
            SEND_STRING("namespace");
        }
        break;
    case 14: // emacs toggle read-only
        if (record->event.pressed) {
            return MACRO(D(LCTL), T(X), T(Q), U(LCTL), END);
        }
        break;
    case 15: // emacs write buffer
        if (record->event.pressed) {
            return MACRO(D(LCTL), T(X), T(S), U(LCTL), END);
        }
        break;
    case 16: // emacs undo
        if (record->event.pressed) {
            return MACRO(D(LCTL), D(LSFT), T(MINS), U(LSFT), U(LCTL), END);
        }
        break;
    case 17: // emacs redo
        if (record->event.pressed) {
            return MACRO(D(LALT), D(LSFT), T(MINS), U(LSFT), U(LALT), END);
        }
        break;
    case 18: // emacs previous buffer
        if (record->event.pressed) {
            return MACRO(D(LCTL), T(X), U(LCTL), T(LEFT), END);
        }
        break;
    case 19: // emacs next buffer
        if (record->event.pressed) {
            return MACRO(D(LCTL), T(X), U(LCTL), T(RGHT), END);
        }
        break;
    case 20:
        if (record->event.pressed) {
            SEND_STRING("good night");
        }
        break;
    case 22: // { };
        if (record->event.pressed) {
            return MACRO(T(ENT), D(LSFT), T(LBRC), U(LSFT), T(ENT),
                         D(LSFT), T(RBRC), U(LSFT), T(SCLN), T(UP),
                         T(TAB), END);
        }
        break;
    case 23:
        if (record->event.pressed) {
            SEND_STRING("template");
        }
        break;
    case 24:
        if (record->event.pressed) {
            SEND_STRING("typename");
        }
        break;
    case 25:
        if (record->event.pressed) {
            SEND_STRING("continue");
            return MACRO(T(SCLN), END);
        }
        break;
    case 26:
        if (record->event.pressed) {
            SEND_STRING("break");
            return MACRO(T(SCLN), END);
        }
        break;
    case 27:
        if (record->event.pressed) {
            SEND_STRING("const");
        }
        break;
    case 28:
        if (record->event.pressed) {
            SEND_STRING(":-)");
        }
        break;
    case 29:
        if (record->event.pressed) {
            SEND_STRING(":-(");
        }
        break;
    case 30: // dazed
        if (record->event.pressed) {
            send_keystrokes(NK_DOWN, KC_LSFT, KC_8, KC_MINS, KC_8, NK_UP, KC_LSFT, KC_NO);
        }
        break;
    case 31: // decaf
        if (record->event.pressed) {
            send_keystrokes(NK_DOWN, KC_LSFT, KC_C, KC_9, KC_MINS, KC_0, NK_UP, KC_LSFT, KC_NO);
        }
        break;
    case 32:
        if (record->event.pressed) {
            SEND_STRING("operator");
        }
        break;
    case 33:
        if (record->event.pressed) {
            SEND_STRING("nullptr");
        }
        break;
    case 34:
        if (record->event.pressed) {
            SEND_STRING("extern");
        }
        break;
    case 35:
        if (record->event.pressed) {
            SEND_STRING("virtual");
        }
        break;
    case 36: // emacs font smaller
        if (record->event.pressed) {
            return MACRO(D(LCTL), T(X), T(EQL), U(LCTL), END);
        }
        break;
    case 37:  // emacs font bigger
        if (record->event.pressed) {
            return MACRO(D(LCTL), T(X), T(MINS), U(LCTL), END);
        }
        break;
    case 38:
        if (record->event.pressed) {
            SEND_STRING("volatile");
        }
        break;
    }
    return MACRO_NONE;
}

LEADER_EXTERNS();

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    LEADER_DICTIONARY() {
        leading = false;
        leader_end();

        SEQ_TWO_KEYS(KC_G, KC_A) {
            SEND_STRING("git add .");
        }
        SEQ_TWO_KEYS(KC_G, KC_D) {
            SEND_STRING("git diff");
        }
        SEQ_THREE_KEYS(KC_G, KC_D, KC_S) {
            SEND_STRING("git diff --staged");
        }
        SEQ_TWO_KEYS(KC_G, KC_L) {
            SEND_STRING("git log");
        }
        SEQ_THREE_KEYS(KC_G, KC_L, KC_O) {
            SEND_STRING("git log --oneline");
        }
        SEQ_TWO_KEYS(KC_G, KC_F) {
            SEND_STRING("git fetch");
        }
        SEQ_TWO_KEYS(KC_G, KC_O) {
            SEND_STRING("git checkout");
        }
        SEQ_TWO_KEYS(KC_G, KC_P) {
            SEND_STRING("git pull");
        }
        SEQ_TWO_KEYS(KC_G, KC_S) {
            SEND_STRING("git status");
        }
        SEQ_TWO_KEYS(KC_G, KC_C) {
            SEND_STRING("git commit -m ''");
            send_keystrokes(KC_LEFT, KC_NO);
        }
        SEQ_THREE_KEYS(KC_G, KC_C, KC_A) {
            SEND_STRING("git commit --amend");
        }

        SEQ_TWO_KEYS(KC_C, KC_C) {
            SEND_STRING("const_cast<>");
            send_keystrokes(KC_LEFT, KC_NO);
        }
        SEQ_TWO_KEYS(KC_C, KC_D) {
            SEND_STRING("dynamic_cast<>");
            send_keystrokes(KC_LEFT, KC_NO);
        }
        SEQ_TWO_KEYS(KC_C, KC_R) {
            SEND_STRING("reinterpret_cast<>");
            send_keystrokes(KC_LEFT, KC_NO);
        }
        SEQ_TWO_KEYS(KC_C, KC_S) {
            SEND_STRING("static_cast<>");
            send_keystrokes(KC_LEFT, KC_NO);
        }

        SEQ_ONE_KEY(KC_SLSH) {
            send_keystrokes(KC_SLSH, NK_DOWN, KC_LSFT, KC_8, KC_8, NK_UP, KC_LSFT, KC_ENT,
                            NK_DOWN, KC_LSFT, KC_8, NK_UP, KC_LSFT, KC_ENT,
                            NK_DOWN, KC_LSFT, KC_8, NK_UP, KC_LSFT, KC_SLSH, KC_UP, KC_END, KC_SPC,
                            KC_NO);
        }
    }
}

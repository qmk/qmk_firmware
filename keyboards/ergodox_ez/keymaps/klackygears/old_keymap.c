#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"

#include "action_util.h"
#include "eeconfig.h"
#include "wait.h"

#define DVRK 0 // dvorak custom layer
#define MACD 1 // Mac dvorak
#define NUMB 2 // numpad layer
#define MCNB 3 // MAC numpad layer
#define MDIA 4 // media keys
#define SYMB 5 // FN & Punctuation
#define MCSM 6 // MAC FN & Punctuation

#define IGNORE_MOD_TAP_INTERRUPT

//klackygears, work in progress
//Tap Dance Declarations
enum {
  TD_PSTI,
  TD_PTSP,
  TD_FNDR,
  TD_CCPY,
  TD_DDEL,
  TD_ACCW,
  TD_YESC,
  TD_DTEX,
  TD_COMQUES,
  TD_MINPLS,
  TD_DIVMLT,
  TD_DOTEQL,
  TD_LSHSYM,
  TD_RSHSYM,
  TD_MCROTOG,
  TD_SCNSP,
  TD_MCCCPY,
  TD_MCPSTIN,
};
enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD,
  DYNAMIC_MACRO_RANGE
};

#include "dynamic_macro.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: dvorak custom layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |        |   '  |   ,  |   .  |   p  |   y  |      |           |      |   f  |   g  |   c  |   r  |   l  | WIN L  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | WNATF4 |   a  |   o  |   e  |   u  |   i  |      |           |      |   d  |   h  |   t  |   n  |   s  | WINTAB |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |  WIN |  ALT | CTRL | SHFT |      |------|           |------|      | SHFT | CTRL |  ALT |MOMDIA|        |
 * | SCRNSP |   ;  |   q  |   j  |   k  |   x  |      |           |      |   b  |   m  |   w  |   v  |   z  | RECPLY |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |  MDIA| WIN  |  ALT | CTRL |SWAP  |                                       | SHIFT| CTRL |  ALT | WIN  | MDIA   |
 *   `----------------------------------'                                       `------------------------------------'
 *                                        ,-------------.       ,---------------.
 *                                        |      |      |       |      |C_S_T = |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      |      |       |      |        |      |
 *                                 | Space|Backsp|------|       |------|  Tab   |Enter |
 *                                 |MOSYMB|MONUMB|      |       |      | MONUMB |MOSYMB|
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[DVRK] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        XXXXXXX,        XXXXXXX,              XXXXXXX,           XXXXXXX,           XXXXXXX,           XXXXXXX,     XXXXXXX,
        KC_ESC,         KC_QUOT,              TD(TD_COMQUES),    TD(TD_DTEX),       KC_P,              KC_Y, XXXXXXX,
        LALT(KC_F4),    KC_A,                 KC_O,              KC_E,              KC_U,              KC_I,
        TD(TD_SCNSP),   MT(MOD_LGUI,KC_SCLN), MT(MOD_LALT,KC_Q), MT(MOD_LCTL,KC_J), MT(MOD_LSFT,KC_K), KC_X,        XXXXXXX,
        MO(MDIA),       KC_LGUI,              KC_LALT,           KC_LCTL,           SH_MON,
                                                                XXXXXXX,  XXXXXXX,
                                                                          XXXXXXX,
                                       LT(SYMB,KC_SPC), LT(NUMB,KC_BSPC), XXXXXXX,
        // right hand
             XXXXXXX,  XXXXXXX,  XXXXXXX,           XXXXXXX,           XXXXXXX,           XXXXXXX,       XXXXXXX,
             XXXXXXX,  KC_F,     KC_G,              KC_C,              KC_R,              KC_L,          LGUI(KC_L),
                       KC_D,     KC_H,              KC_T,              KC_N,              KC_S,          LGUI(KC_TAB),
             XXXXXXX,  KC_B,     MT(MOD_LSFT,KC_M), MT(MOD_LCTL,KC_W), MT(MOD_LALT,KC_V), LT(MDIA,KC_Z), TD(TD_MCROTOG),
                                 KC_RSFT,           KC_RCTL,           KC_RALT,           KC_RGUI,       MO(MDIA),
             XXXXXXX,  TD(TD_MCROTOG),
             XXXXXXX,
             XXXXXXX,  LT(NUMB,KC_TAB), LT(SYMB,KC_ENT)
    ),

/* Keymap 0: Mac Dvorak
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |        |   '  |   ,  |   .  |   p  |   y  |      |           |      |   f  |   g  |   c  |   r  |   l  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | QUIT   |   a  |   o  |   e  |   u  |   i  |      |           |      |   d  |   h  |   t  |   n  |   s  | CMDTAB |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        | CTRL |  ALT | CMD  | SHFT |      |------|           |------|      | SHFT | CMD  |  ALT |MOMDIA|        |
 * |        |   ;  |   q  |   j  |   k  |   x  |      |           |      |   b  |   m  |   w  |   v  |   z  | RECPLY |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | MDIA | CTRL |  ALT | CMD  |SHFT  |                                       | SHIFT| CMD  |  ALT | CTRL | MDIA |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,---------------.
 *                                        | SWAP |      |       |      |C_S_T = |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      |      |       |      |        |      |
 *                                 | Space|Backsp|------|       |------|  Tab   |Enter |
 *                                 |MOSYMB|MONUMB|      |       |      | MONUMB |MOSYMB|
 *                                 `--------------------'       `----------------------'
 */
[MACD] = LAYOUT_ergodox(  // layer  
        // left hand
        XXXXXXX,       XXXXXXX,              XXXXXXX,           XXXXXXX,           XXXXXXX,           XXXXXXX,     XXXXXXX,
        KC_ESC,       KC_QUOT,              TD(TD_COMQUES),    TD(TD_DTEX),       KC_P,               KC_Y,        XXXXXXX,
        LCTL(KC_Q),    KC_A,                 KC_O,              KC_E,              KC_U,              KC_I,
        XXXXXXX,       MT(MOD_LCTL,KC_SCLN), MT(MOD_LALT,KC_Q), MT(MOD_LGUI,KC_J), MT(MOD_LSFT,KC_K), KC_X,        XXXXXXX,
        MO(MDIA),      KC_LCTL,              KC_LALT,           KC_LCMD,           SH_MON,
                                                   XXXXXXX,   XXXXXXX,
                                                              XXXXXXX,
                           LT(MCSM,KC_SPC), LT(MCNB,KC_BSPC), XXXXXXX,
        // right hand
             XXXXXXX,  XXXXXXX,                    XXXXXXX,           XXXXXXX,           XXXXXXX,           XXXXXXX,  XXXXXXX,
             XXXXXXX,  KC_F,    KC_G,              KC_C,              KC_R,              KC_L,              XXXXXXX,
                       KC_D,    KC_H,              KC_T,              KC_N,              KC_S, LGUI(KC_TAB),
             XXXXXXX,  KC_B,    MT(MOD_LSFT,KC_M), MT(MOD_LGUI,KC_W), MT(MOD_LALT,KC_V), LT(MDIA,KC_Z),     TD(TD_MCROTOG),
                                KC_RSFT,           KC_RCMD,           KC_RALT,           KC_RCTL,           MO(MDIA),
             TD(TD_DNCE), XXXXXXX,
             XXXXXXX,
             XXXXXXX,     LT(MCNB,KC_TAB), LT(MCSM,KC_ENT)
    ),

/* Keymap 1: numpad layer
 *
 * ,------------------------------------------------------.           ,--------------------------------------------------.
 * |         |      |       |       |       |      |      |           |      |      |      |      |      |      |        |
 * |---------+------+-------+-------+-------+------+------|           |------+------+------+------+------+------+--------|
 * |         | PGUp | PGDown| HOME  |  End  |FINDRE|      |           |      | -  + |   7  |   8  |   9  |      |        |
 * |---------+------+-------+-------+-------+------|      |           |      |------+------+------+------+------+--------|
 * | STRIKE  |LEFT  |DOWN   |UP     |RIGHT  |  PTSP|      |           |      | /  * |   4  |   5  |   6  |   0  |        |
 * |---------+------+-------+-------+-------+------|      |           |      |------+------+------+------+------+--------|
 * |         |      |       |       |       |      |------|           |------|      | SHIFT| CTRL |  ALT |  WIN |        |
 * |         | ACCW |  ALL  |  CCPY |  PSTI |  DDEL|      |           |      | .  = |   1  |   2  |   3  |   0  |        |
 * `---------+------+-------+-------+-------+-------------'           `-------------+------+------+------+------+--------'
 *   |       |      |       |       |       |                                       |      |      |      |      |      |
 *   `--------------------------------------'                                       `----------------------------------'
 *                                        ,--------------.            ,--------------.
 *                                        |      |       |            |       |      |
 *                                 ,------|------|-------|            |-------+------+------.
 *                                 |      |      |       |            |       |      |      |
 *                                 |      |      |-------|            |-------|      |      |
 *                                 |      |      |       |            |       |      |      |
 *                                 `---------------------'            `---------------------'
 */
// SYMBOLS
[NUMB] = LAYOUT_ergodox(
       // left hand
       KC_TRNS,    KC_TRNS,     KC_TRNS,    KC_TRNS,     KC_TRNS,     KC_TRNS,      KC_TRNS,
       KC_TRNS,    KC_PGUP,     KC_PGDN,    KC_HOME,     KC_END,      TD(TD_FNDR),  KC_TRNS,
       LCTL(KC_5), KC_LEFT,     KC_UP,      KC_DOWN,     KC_RIGHT,    TD(TD_PTSP),
       KC_TRNS,    TD(TD_ACCW), LCTL(KC_A), TD(TD_CCPY), TD(TD_PSTI), TD(TD_DDEL),  KC_TRNS,
       KC_TRNS,    KC_TRNS,     KC_TRNS,    KC_TRNS,     KC_TRNS,
                                                                      KC_TRNS,      KC_TRNS,
                                                                                    KC_TRNS,
                                                         KC_TRNS,     KC_TRNS,      KC_TRNS,
       // right hand
       KC_TRNS,   KC_TRNS,       KC_TRNS,           KC_TRNS,           KC_TRNS,           KC_TRNS,            KC_TRNS,
       KC_TRNS,   TD(TD_MINPLS), KC_7,              KC_8,              KC_9,              KC_PPLS,            KC_TRNS,
                  TD(TD_DIVMLT), KC_4,              KC_5,              KC_6,              KC_0,               KC_TRNS,
       KC_TRNS,   TD(TD_DOTEQL), MT(MOD_LSFT,KC_1), MT(MOD_LCTL,KC_2), MT(MOD_LALT,KC_3), MT(MOD_LGUI,KC_0),  KC_TRNS,
                                 KC_0,              KC_0,              KC_TRNS,           KC_TRNS,            KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),

/* Keymap 1: MAC numpad layer
 *
 * ,------------------------------------------------------.           ,--------------------------------------------------.
 * |         |      |       |       |       |      |      |           |      |      |      |      |      |      |        |
 * |---------+------+-------+-------+-------+------+------|           |------+------+------+------+------+------+--------|
 * |         | PGUp | PGDown| HOME  |  End  |FINDRE|      |           |      | -  + |   7  |   8  |   9  |      |        |
 * |---------+------+-------+-------+-------+------|      |           |      |------+------+------+------+------+--------|
 * |         |LEFT  |DOWN   |UP     |RIGHT  |  PTSP|      |           |      | /  * |   4  |   5  |   6  |   0  |        |
 * |---------+------+-------+-------+-------+------|      |           |      |------+------+------+------+------+--------|
 * |         |      |       |       |       |      |------|           |------|      | SHIFT| CTRL |  ALT |  WIN |        |
 * |         |      |  ALL  |  CCPY |  PSTI |      |      |           |      | .  = |   1  |   2  |   3  |   0  |        |
 * `---------+------+-------+-------+-------+-------------'           `-------------+------+------+------+------+--------'
 *   |       |      |       |       |       |                                       |      |      |      |      |      |
 *   `--------------------------------------'                                       `----------------------------------'
 *                                        ,--------------.            ,--------------.
 *                                        |      |       |            |       |      |
 *                                 ,------|------|-------|            |-------+------+------.
 *                                 |      |      |       |            |       |      |      |
 *                                 |      |      |-------|            |-------|      |      |
 *                                 |      |      |       |            |       |      |      |
 *                                 `---------------------'            `---------------------'
 */
// SYMBOLS
[MCNB] = LAYOUT_ergodox(
       // left hand
       KC_TRNS,    KC_TRNS,     KC_TRNS,    KC_TRNS,       KC_TRNS,        KC_TRNS,  KC_TRNS,
       KC_TRNS,    KC_PGUP,     KC_PGDN,    KC_HOME,       KC_END,         KC_TRNS,  KC_TRNS,
       KC_TRNS,    KC_LEFT,     KC_UP,      KC_DOWN,       KC_RIGHT,       KC_TRNS,
       KC_TRNS,    KC_TRNS,     LGUI(KC_A), TD(TD_MCCCPY), TD(TD_MCPSTIN), KC_TRNS,  KC_TRNS,
       KC_TRNS,    KC_TRNS,     KC_TRNS,    KC_TRNS,       KC_TRNS,
                                                                      KC_TRNS,      KC_TRNS,
                                                                                    KC_TRNS,
                                                         KC_TRNS,     KC_TRNS,      KC_TRNS,
       // right hand
       KC_TRNS,   KC_TRNS,       KC_TRNS,           KC_TRNS,           KC_TRNS,           KC_TRNS,            KC_TRNS,
       KC_TRNS,   TD(TD_MINPLS), KC_7,              KC_8,              KC_9,              KC_PPLS,            KC_TRNS,
                  TD(TD_DIVMLT), KC_4,              KC_5,              KC_6,              KC_0,               KC_TRNS,
       KC_TRNS,   TD(TD_DOTEQL), MT(MOD_LSFT,KC_1), MT(MOD_LGUI,KC_2), MT(MOD_LALT,KC_3), MT(MOD_LCTL,KC_0),  KC_TRNS,
                                 KC_0,              KC_0,              KC_TRNS,           KC_TRNS,            KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),

/* Keymap 3: Media and mouse keys
 *
 * ,-----------------------------------------------------.           ,-----------------------------------------------------.
 * |        |      |       |       |       |      |      |           |      |      |      |       |       |       |        |
 * |--------+------+-------+-------+-------+-------------|           |------+------+------+-------+-------+-------+--------|
 * |        | PGUp | PGDown|       |       |      |      |           |      |      |      |       |       |       |        |
 * |--------+------+-------+-------+-------+------|      |           |      |------+------+-------+-------+-------+--------|
 * |        |MsLeft|Msup   |Msdn   |MsRght |      |------|           |------|      |KCMUTE|KCVOLD |KCVOLU |       |        |
 * |--------+------+-------+-------+-------+------|      |           |      |------+------+-------+-------+-------+--------|
 * |        |      |KC_WH_D|KC_WH_U|       |      |      |           |      |      |KCACL0|KCACL1 |KCACL2 |       |        |
 * `--------+------+-------+-------+-------+-------------'           `-------------+------+-------+-------+-------+--------'
 *   |      |      |       |       |       |                                       |      |       |       |       |       |
 *   `-------------------------------------'                                       `--------------------------------------'
 *                                         ,-------------.           ,-------------.
 *                                         | BT3  |      |           |      |      |
 *                                  ,------|------|------|           |------+------+------.
 *                                  | Lclk | Rclk |      |           |      |      |Brwser|
 *                                  |      |      |------|           |------|      |Back  |
 *                                  |      |      |      |           |      |      |      |
 *                                  `--------------------'           `--------------------'
 */
// MEDIA AND MOUSE
[MDIA] = LAYOUT_ergodox(
       XXXXXXX, XXXXXXX,  XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
       XXXXXXX, KC_PGUP,  KC_PGDOWN, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
       XXXXXXX, KC_MS_L,  KC_MS_U,   KC_MS_D, KC_MS_R, KC_TRNS,
       XXXXXXX, KC_TRNS,  KC_WH_U,   KC_WH_D, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,  KC_TRNS,   KC_TRNS, KC_TRNS,
                                                       KC_BTN3, KC_TRNS,
                                                                KC_TRNS,
                                              KC_BTN1, KC_BTN2, KC_TRNS,
    // right hand
       XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
       XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                 XXXXXXX, KC_MUTE, KC_VOLD, KC_VOLU, KC_TRNS, XXXXXXX,
       XXXXXXX,  XXXXXXX, KC_ACL0, KC_ACL1, KC_ACL2, KC_TRNS, XXXXXXX,
                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_WBAK
),
/* Keymap 4: FN & Punctuation
 *
 * ,-----------------------------------------------------.           ,-----------------------------------------------------.
 * |        |      |       |       |       |      |      |           |      |      |      |       |       |       |        |
 * |--------+------+-------+-------+-------+-------------|           |------+------+------+-------+-------+-------+--------|
 * |        |   \  |  @    |   #   |   $   |   %  |      |           |      | MAC  | F9   |  F10  |  F11  |  F12  |        |
 * |--------+------+-------+-------+-------+------|      |           |      |------+------+-------+-------+-------+--------|
 * |        |   +  |   -   |   *   |   /   |   =  |------|           |------| WIN  | F5   |  F6   |  F7   |  F8   |        |
 * |--------+------+-------+-------+-------+------|      |           |      |------+------+-------+-------+-------+--------|
 * |        |   [  |   ]   |   (   |   )   |   &  |      |           |      |  GRV | F1   |  F2   |  F3   |  F4   |        |
 * |        |      |       |       |       |      |------|           |------|      | SHFT |  CTRL |  ALT  |  WIN  |        |
 * `--------+------+-------+-------+-------+-------------'           `-------------+------+-------+-------+-------+--------'
 *   |      |      |       |       |       |                                       |      |       |       |       |       |
 *   `-------------------------------------'                                       `--------------------------------------'
 *                                         ,-------------.           ,-------------.
 *                                         |      |      |           |      |      |
 *                                  ,------|------|------|           |------+------+------.
 *                                  |      |      |      |           |      |      |      |
 *                                  |      |  DEL |------|           |------| CAPS |      |
 *                                  |      |      |      |           |      |      |      |
 *                                  `--------------------'           `--------------------'
 */
[SYMB] = LAYOUT_ergodox(
       KC_TRNS,   KC_TRNS,      KC_TRNS,   KC_TRNS,              KC_TRNS,      KC_TRNS, KC_TRNS,
       KC_CIRC,   KC_BSLS,      KC_AT,     KC_HASH,              KC_DLR,       KC_PERC, KC_TRNS,
       KC_TRNS,   KC_PLUS,      KC_MINS,   KC_ASTR,              KC_SLSH,      KC_EQL,
       KC_TRNS,   KC_LBRC,      KC_RBRC,   KC_LPRN,              KC_RPRN,      KC_AMPR, KC_TRNS,
       KC_TRNS,   KC_TRNS,      KC_TRNS,   KC_TRNS,              KC_TRNS,
                                                        KC_TRNS,  KC_TRNS,
                                                                  KC_TRNS,
                                                 KC_TRNS, KC_DEL, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,            KC_TRNS,            KC_TRNS,            KC_TRNS,
       KC_TRNS,  TO(MACD), KC_F9,              KC_F10,             KC_F11,             KC_F12,             KC_TRNS,
                 TO(DVRK), KC_F5,              KC_F6,              KC_F7,              KC_F8,              KC_TRNS,
       KC_TRNS,  KC_GRV,   MT(MOD_LSFT,KC_F1), MT(MOD_LCTL,KC_F2), MT(MOD_LALT,KC_F3), MT(MOD_LGUI,KC_F4), KC_TRNS,
                           KC_TRNS,            KC_TRNS,            KC_TRNS,            KC_TRNS,            KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_CAPS, KC_TRNS
),

/* Keymap 4: MAC FN & Punctuation
 *
 * ,-----------------------------------------------------.           ,-----------------------------------------------------.
 * |        |      |       |       |       |      |      |           |      |      |      |       |       |       |        |
 * |--------+------+-------+-------+-------+-------------|           |------+------+------+-------+-------+-------+--------|
 * |        |   \  |  @    |   #   |   $   |   %  |      |           |      | MAC  | F9   |  F10  |  F11  |  F12  |        |
 * |--------+------+-------+-------+-------+------|      |           |      |------+------+-------+-------+-------+--------|
 * |        |   +  |   -   |   *   |   /   |   =  |------|           |------| WIN  | F5   |  F6   |  F7   |  F8   |        |
 * |--------+------+-------+-------+-------+------|      |           |      |------+------+-------+-------+-------+--------|
 * |        |   [  |   ]   |   (   |   )   |   &  |      |           |      |  GRV | F1   |  F2   |  F3   |  F4   |        |
 * |        |      |       |       |       |      |------|           |------|      | SHFT |  CMD  |   ALT | CTRL  |        |
 * `--------+------+-------+-------+-------+-------------'           `-------------+------+-------+-------+-------+--------'
 *   |      |      |       |       |       |                                       |      |       |       |       |       |
 *   `-------------------------------------'                                       `--------------------------------------'
 *                                         ,-------------.           ,-------------.
 *                                         |      |      |           |      |      |
 *                                  ,------|------|------|           |------+------+------.
 *                                  |      |      |      |           |      |      |      |
 *                                  |      |  DEL |------|           |------| CAPS |      |
 *                                  |      |      |      |           |      |      |      |
 *                                  `--------------------'           `--------------------'
 */
[MCSM] = LAYOUT_ergodox(
       KC_TRNS,   KC_TRNS,      KC_TRNS,   KC_TRNS,              KC_TRNS,      KC_TRNS, KC_TRNS,
       KC_CIRC,   KC_BSLS,      KC_AT,     KC_HASH,              KC_DLR,       KC_PERC, KC_TRNS,
       KC_TRNS,   KC_PLUS,      KC_MINS,   KC_ASTR,              KC_SLSH,      KC_EQL,
       KC_TRNS,   KC_LBRC,      KC_RBRC,   KC_LPRN,              KC_RPRN,      KC_AMPR, KC_TRNS,
       KC_TRNS,   KC_TRNS,      KC_TRNS,   KC_TRNS,              KC_TRNS,
                                                        KC_TRNS,  KC_TRNS,
                                                                  KC_TRNS,
                                                 KC_TRNS, KC_DEL, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,            KC_TRNS,            KC_TRNS,            KC_TRNS,
       KC_TRNS,  TO(MACD), KC_F9,              KC_F10,             KC_F11,             KC_F12,             KC_TRNS,
                 TO(DVRK), KC_F5,              KC_F6,              KC_F7,              KC_F8,              KC_TRNS,
       KC_TRNS,  KC_GRV,   MT(MOD_LSFT,KC_F1), MT(MOD_LGUI,KC_F2), MT(MOD_LALT,KC_F3), MT(MOD_LCTL,KC_F4), KC_TRNS,
                           KC_TRNS,            KC_TRNS,            KC_TRNS,            KC_TRNS,            KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_CAPS, KC_TRNS
),

};

// on each tap, light up one led, from right to left
// on the forth tap, turn them off from right to left





void pstinsrt(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->count > 1)
  {
    register_code(KC_LALT);
    register_code(KC_I);
    unregister_code(KC_I);
    register_code(KC_E);
    unregister_code(KC_E);
    unregister_code(KC_LALT);
  }
  else
  {
    register_code(KC_LCTL);
    register_code(KC_V);
    unregister_code(KC_V);
    unregister_code(KC_LCTL);
  }
  reset_tap_dance(state);
}

void ccopy(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->count > 1)
  {
    register_code(KC_LCTL);
    register_code(KC_X);
    unregister_code(KC_X);
    unregister_code(KC_LCTL);
  }
  else
  {
    register_code(KC_LCTL);
    register_code(KC_C);
    unregister_code(KC_C);
    unregister_code(KC_LCTL);
  }
  reset_tap_dance(state);
}

void pstspecial(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->count > 1)
  {
    register_code(KC_LALT);
    register_code(KC_E);
    unregister_code(KC_E);
    register_code(KC_S);
    unregister_code(KC_S);
    unregister_code(KC_LALT);
    register_code(KC_V);
    unregister_code(KC_V);
  }
  else
  {
    register_code(KC_LALT);
    register_code(KC_E);
    unregister_code(KC_E);
    register_code(KC_S);
    unregister_code(KC_S);
    unregister_code(KC_LALT);
    register_code(KC_T);
    unregister_code(KC_T);
  }
  reset_tap_dance(state);
}

void deldel(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->count > 1)
  {
    register_code(KC_LALT);
    register_code(KC_E);
    unregister_code(KC_E);
    register_code(KC_D);
    unregister_code(KC_D);
    unregister_code(KC_LALT);
  }
  else
  {
    register_code(KC_DEL);
    unregister_code(KC_DEL);
  }
  reset_tap_dance(state);
}

void findreplace(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->count > 1)
  {
    register_code(KC_LCTL);
    register_code(KC_H);
    unregister_code(KC_H);
    unregister_code(KC_LCTL);
  }
  else
  {
    register_code(KC_LCTL);
    register_code(KC_F);
    unregister_code(KC_F);
    unregister_code(KC_LCTL);
  }
  reset_tap_dance(state);
}

void cyclawin(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->count > 1)
  {
    register_code(KC_LCTL);
    register_code(KC_LSFT);
    register_code(KC_F6);
    unregister_code(KC_F6);
    unregister_code(KC_LSFT);
    unregister_code(KC_LCTL);
  }
  else
  {
    register_code(KC_LCTL);
    register_code(KC_F6);
    unregister_code(KC_F6);
    unregister_code(KC_LCTL);
  }
  reset_tap_dance(state);
}


void SCRNSNP(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->count > 1)
  {
    register_code(KC_LALT);
    register_code(KC_PSCR);
    unregister_code(KC_PSCR);
    unregister_code(KC_LALT);
  }
  else
  {
    SEND_STRING(SS_TAP(X_LGUI));
    SEND_STRING("SN");
    register_code(KC_LCTL);
    register_code(KC_N);
    unregister_code(KC_N);
    unregister_code(KC_LCTL);
  }
  reset_tap_dance(state);
}

void mcccpy(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->count > 1)
  {
    register_code(KC_LGUI);
    register_code(KC_X);
    unregister_code(KC_X);
    unregister_code(KC_LGUI);
  }
  else
  {
    register_code(KC_LGUI);
    register_code(KC_C);
    unregister_code(KC_C);
    unregister_code(KC_LGUI);
  }
  reset_tap_dance(state);
}

void macroTogKey(qk_tap_dance_state_t *state, void *user_data) {
  keyrecord_t kr;

  if (state->count == 1)
  {
    kr.event.pressed = false;
    process_record_dynamic_macro( DYN_MACRO_PLAY1, &kr );
  }
  else if (state->count == 2)
  {
    kr.event.pressed = true;
    process_record_dynamic_macro( DYN_REC_STOP, &kr );
  }
  else if (state->count == 3)
  {
    kr.event.pressed = false;
    process_record_dynamic_macro( DYN_REC_START1, &kr );
  }
}

void mcpstin(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->count > 1)
  {
    register_code(KC_LGUI);
    register_code(KC_I);
    unregister_code(KC_I);
    unregister_code(KC_LGUI);
  }
  else
  {
    register_code(KC_LGUI);
    register_code(KC_V);
    unregister_code(KC_V);
    unregister_code(KC_LGUI);
  }
  reset_tap_dance(state);
}

qk_tap_dance_action_t tap_dance_actions[] = {
        [TD_DNCE] = ACTION_TAP_DANCE_FN_ADVANCED (dance_flsh_each, dance_flsh_finished, dance_flsh_reset),
        [TD_PSTI] = ACTION_TAP_DANCE_FN(pstinsrt),
        [TD_PTSP] = ACTION_TAP_DANCE_FN(pstspecial),
        [TD_FNDR] = ACTION_TAP_DANCE_FN(findreplace),
        [TD_CCPY] = ACTION_TAP_DANCE_FN(ccopy),
        [TD_DDEL] = ACTION_TAP_DANCE_FN(deldel),
        [TD_ACCW] = ACTION_TAP_DANCE_FN(cyclawin),
        [TD_YESC] = ACTION_TAP_DANCE_DOUBLE(KC_Y,KC_ESC),
        [TD_DTEX] = ACTION_TAP_DANCE_DOUBLE(KC_DOT,KC_EXLM),
        [TD_COMQUES] = ACTION_TAP_DANCE_DOUBLE(KC_COMM,KC_QUES),
        [TD_MINPLS] = ACTION_TAP_DANCE_DOUBLE(KC_PMNS,KC_PPLS),
        [TD_DIVMLT] = ACTION_TAP_DANCE_DOUBLE(KC_PSLS,KC_PAST),
        [TD_DOTEQL] = ACTION_TAP_DANCE_DOUBLE(KC_DOT,KC_EQL),
        [TD_MCROTOG]  = ACTION_TAP_DANCE_FN(macroTogKey),
        [TD_SCNSP]  = ACTION_TAP_DANCE_FN(SCRNSNP),
        [TD_MCCCPY] = ACTION_TAP_DANCE_FN(mcccpy),
        [TD_MCPSTIN] = ACTION_TAP_DANCE_FN(mcpstin)
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(NUMB)                // FN1 - Momentary Layer 1 (Symbols)
};
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    if (record->event.pressed) {
        switch(id) {
            case 0: 
                return MACRO(D(LALT), T(E), T(D), U(LALT), END);
        }
    }
        return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  
  if (!process_record_dynamic_macro(keycode, record)) {
        return false;
    }

  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;
    case RGB_SLD:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_mode(1);
        #endif
      }
      return false;
      break;
  }
  return true;
}

void matrix_init_user(void) {
    ergodox_led_all_set( LED_BRIGHTNESS_HI );
};

void led_set_user(uint8_t usb_led) {
    if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
        ergodox_right_led_1_on();
    } else {
        ergodox_right_led_1_off();
    }
}

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
        case NUMB:
            // Binary 1 represented by the leds
            // --*
            ergodox_right_led_3_on();
            break;
        case MDIA:
            // Binary 2 represented by the leds
            // -*-
            ergodox_right_led_2_on();
            break;
        case SYMB:
            // Binary 3 represented by the leds
            // -**
            ergodox_right_led_3_on();
            ergodox_right_led_2_on();
            break;
        default:
            // none
            break;
    
};
}
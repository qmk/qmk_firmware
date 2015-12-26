/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Jeo layout for ErgoDox EZ. Optimised for OS X.                            *
 *                                                                           *
 * v1.0.0                                                                    *
 *                                                                           *
 * Joe Cridge, 2015.                                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "ergodox_ez.h"
#include "action_layer.h"
#include "debug.h"

#define  BASE  0  /* qgmlwy...                 */
#define  CAPS  1  /* QGMLWY...                 */
#define  SYMB  2  /* Neo symbol layer          */
#define  FPAD  3  /* Function and numpad layer */
#define  WASD  4  /* Standard QWERTY layout    */
#define  LOCK  5  /* Kitten-proof layer        */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[BASE] = KEYMAP(
  /**
   * BASE: Left Hand
   *
   *        ,--------------------------------------------------.
   *        |Activity|1     |2     |3     |4     |5     |Pause |
   *        |--------+------+------+------+------+-------------|
   *        |Tab     |q     |g     |m     |l     |w     |Volume|
   *        |--------+------+------+------+------+------|Up    |
   *        |Symbol  |d     |s     |t     |n     |r     |------|
   *        |--------+------+------+------+------+------|Volume|
   *        |Upper   |z     |x     |c     |v     |j     |Down  |
   *        `--------+------+------+------+------+-------------'
   *          |QWERTY|Left  |Right |Up    |Down  |
   *          `----------------------------------'
   *                                                    ,-------------.
   *                                                    |Prev  |Next  |
   *                                             ,------|------|------|
   *                                             |Cmd   |Ctrl  |Mute  |
   *                                             |      |      |------|
   *                                             |      |      |Alt   |
   *                                             `--------------------'
   */
   KC_F16,    KC_1,     KC_2,     KC_3,   KC_4,     KC_5,     KC_MPLY,
   KC_TAB,    KC_Q,     KC_G,     KC_M,   KC_L,     KC_W,     KC_VOLU,
   MO(SYMB),  KC_D,     KC_S,     KC_T,   KC_N,     KC_R,
   MO(CAPS),  KC_Z,     KC_X,     KC_C,   KC_V,     KC_J,     KC_VOLD,
   TO(WASD),  KC_LEFT,  KC_RGHT,  KC_UP,  KC_DOWN,

                                                    KC_MPRV,  KC_MNXT,
                                                              KC_MUTE,
                                          KC_LGUI,  KC_LCTL,  KC_LALT,

  /**
   * BASE: Right Hand
   *
   *               ,--------------------------------------------------.
   *               |Prefs |6     |7     |8     |9     |0     |Search  |
   *               |------+------+------+------+------+------+--------|
   *               |Page  |y     |f     |u     |b     |Escape|BckSpace|
   *               |Up    |------+------+------+------+------+--------|
   *               |------|i     |a     |e     |o     |h     |Symbol  |
   *               |Page  |------+------+------+------+------+--------|
   *               |Down  |k     |p     |,     |.     |/     |Upper   |
   *               `-------------+------+------+------+------+--------'
   *                             |Down  |Up    |Right |Left  |Save  |
   *                             `----------------------------------'
   *        ,-------------.
   *        |Term  |Editor|
   *        |------+------+------.
   *        |Delete|Enter |Space |
   *        |------|      |      |
   *        |Fn    |      |      |
   *        `--------------------'
   *
   */
   KC_F17,      KC_6,    KC_7,     KC_8,     KC_9,      KC_0,      KC_F18,
   KC_PGUP,     KC_Y,    KC_F,     KC_U,     KC_B,      KC_ESC,    KC_BSCP,
                KC_I,    KC_A,     KC_E,     KC_O,      KC_H,      MO(SYMB),
   KC_PGDN,     KC_K,    KC_P,     KC_COMM,  KC_DOT,    KC_SLSH,   MO(CAPS),
                         KC_DOWN,  KC_UP,    KC_RIGHT,  KC_LEFT,   KC_F19,

   KC_F20,      KC_F21,
   KC_DELETE,
   TO(FPAD),    KC_ENT,  KC_SPC
),

[CAPS] = KEYMAP(
  /**
   * CAPS: Left Hand
   *
   * Blank keys are transparent (i.e. fall back to BASE).
   *
   *        ,--------------------------------------------------.
   *        |        |      |      |      |      |      |      |
   *        |--------+------+------+------+------+-------------|
   *        |TAB     |Q     |G     |M     |L     |W     |      |
   *        |--------+------+------+------+------+------|      |
   *        |        |D     |S     |T     |N     |R     |------|
   *        |--------+------+------+------+------+------|      |
   *        |        |Z     |X     |C     |V     |J     |      |
   *        `--------+------+------+------+------+-------------'
   *          |LOCK  |      |      |      |      |
   *          `----------------------------------'
   *                                                    ,-------------.
   *                                                    |      |      |
   *                                             ,------|------|------|
   *                                             |CMD   |CTRL  |      |
   *                                             |      |      |------|
   *                                             |      |      |ALT   |
   *                                             `--------------------'
   */
   KC_TRNS,    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,     KC_TRNS,
   S(KC_TAB),  S(KC_Q),  S(KC_G),  S(KC_M),  S(KC_L),    S(KC_W),     KC_TRNS,
   KC_TRNS,    S(KC_D),  S(KC_S),  S(KC_T),  S(KC_N),    S(KC_R),
   KC_TRNS,    S(KC_Z),  S(KC_X),  S(KC_C),  S(KC_V),    S(KC_J),     KC_TRNS,
   TO(LOCK),   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,

                                                         KC_TRNS,     KC_TRNS,
                                                                      KC_TRNS,
                                             (KC_LGUI),  S(KC_LCTL),  S(KC_LALT),

  /**
   * CAPS: Right Hand
   *
   * Blank keys are transparent (i.e. fall back to BASE).
   *
   *               ,--------------------------------------------------.
   *               |      |      |      |      |      |      |        |
   *               |------+------+------+------+------+------+--------|
   *               |      |Y     |F     |U     |B     |      |        |
   *               |      |------+------+------+------+------+--------|
   *               |------|I     |A     |E     |O     |H     |        |
   *               |      |------+------+------+------+------+--------|
   *               |      |K     |P     |EmDash|MidDot|?     |        |
   *               `-------------+------+------+------+------+--------'
   *                             |      |      |      |      |SAVE  |
   *                             `----------------------------------'
   *        ,-------------.
   *        |      |      |
   *        |------+------+------.
   *        |      |ENTER |SPACE |
   *        |------|      |      |
   *        |      |      |      |
   *        `--------------------'
   *
   */
   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,
   KC_TRNS,  S(KC_Y),  S(KC_F),  S(KC_U),     S(KC_B),     KC_TRNS,     KC_TRNS,
             S(KC_I),  S(KC_A),  S(KC_E),     S(KC_O),     S(KC_H),     KC_TRNS,
   KC_TRNS,  S(KC_K),  S(KC_P),  UC(0x2014),  UC(0x00B7),  S(KC_SLSH),  KC_TRNS,
                       KC_TRNS,  KC_TRNS,     KC_TRNS,     KC_TRNS,     S(KC_F19),

   KC_TRNS,  KC_TRNS,
   KC_TRNS,
   KC_TRNS,  S(KC_ENT),  S(KC_SPC)
),

[SYMB] = KEYMAP(
  /**
   * SYMB: Left Hand
   *
   * Blank keys are transparent.
   *
   *        ,--------------------------------------------------.
   *        |        |      |@     |GBP   |EUR   |      |      |
   *        |--------+------+------+------+------+-------------|
   *        |        |...   |_     |[     |]     |^     |      |
   *        |--------+------+------+------+------+------|      |
   *        |        |\     |/     |{     |}     |*     |------|
   *        |--------+------+------+------+------+------|      |
   *        |        |#     |$     ||     |~     |`     |      |
   *        `--------+------+------+------+------+-------------'
   *          |      |      |      |      |      |
   *          `----------------------------------'
   *                                                    ,-------------.
   *                                                    |      |      |
   *                                             ,------|------|------|
   *                                             |      |      |      |
   *                                             |      |      |------|
   *                                             |      |      |      |
   *                                             `--------------------'
   */
   KC_TRNS,  KC_TRNS,     KC_AT,    UC(0x00A3),  UC(0x20AC),  KC_TRNS,  KC_TRNS,
   KC_TRNS,  UC(0x2026),  KC_UNDS,  KC_LBRC,     KC_RBRC,     KC_CIRC,  KC_TRNS,
   KC_TRNS,  KC_BSLS,     KC_SLSH,  KC_LCBR,     KC_RCBR,     KC_ASTR,
   KC_TRNS,  KC_HASH,     KC_DLR,   KC_PIPE,     KC_TILD,     KC_GRV,   KC_TRNS,
   KC_TRNS,  KC_TRNS,     KC_TRNS,  KC_TRNS,     KC_TRNS,

                                                              KC_TRNS,  KC_TRNS,
                                                                        KC_TRNS,
                                                KC_TRNS,      KC_TRNS,  KC_TRNS,

  /**
   * SYMB: Right Hand
   *
   * Blank keys are transparent.
   *
   *               ,--------------------------------------------------.
   *               |      |      |LDQUO |RDQUO |LSQUO |LDQUO |        |
   *               |------+------+------+------+------+------+--------|
   *               |      |!     |<     |>     |=     |&     |        |
   *               |      |------+------+------+------+------+--------|
   *               |------|?     |(     |)     |-     |:     |        |
   *               |      |------+------+------+------+------+--------|
   *               |      |+     |%     |"     |'     |;     |        |
   *               `-------------+------+------+------+------+--------'
   *                             |      |      |      |      |      |
   *                             `----------------------------------'
   *        ,-------------.
   *        |      |      |
   *        |------+------+------.
   *        |      |      |      |
   *        |------|      |      |
   *        |      |      |      |
   *        `--------------------'
   *
   */
   KC_TRNS,  KC_TRNS,  UC(0x201C),  UC(0x201D),  UC(0x2018), UC(0x2019), KC_TRNS,
   KC_TRNS,  KC_Y,     KC_F,        KC_U,        KC_B,       KC_BSPC,    KC_ESC,
             KC_I,     KC_A,        KC_E,        KC_O,       KC_H,       MO(SYMB),
   KC_PGDN,  KC_K,     KC_P,        KC_COMM,     KC_DOT,     KC_SLSH,    MO(CAPS),
                       KC_DOWN,     KC_UP,       KC_RIGHT,   KC_LEFT,    KC_F19,

   KC_TRNS,  KC_TRNS,
   KC_TRNS,
   KC_TRNS,  KC_TRNS,  KC_TRNS
),

/* Keymap 1: Symbol Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   !  |   @  |   {  |   }  |   |  |      |           |      |   Up |   7  |   8  |   9  |   *  |   F12  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   #  |   $  |   (  |   )  |   `  |------|           |------| Down |   4  |   5  |   6  |   +  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |   \  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |    . |   0  |   =  |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[SYMB] = KEYMAP(
       // left hand
       KC_TRNS,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_TRNS,
       KC_TRNS,KC_EXLM,KC_AT,  KC_LCBR,KC_RCBR,KC_PIPE,KC_TRNS,
       KC_TRNS,KC_HASH,KC_DLR, KC_LPRN,KC_RPRN,KC_GRV,
       KC_TRNS,KC_PERC,KC_CIRC,KC_LBRC,KC_RBRC,KC_TILD,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                       KC_TRNS,KC_TRNS,
                                               KC_TRNS,
                               KC_TRNS,KC_TRNS,KC_TRNS,
       // right hand
       KC_TRNS, KC_F6,   KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,
       KC_TRNS, KC_UP,   KC_7,   KC_8,    KC_9,    KC_ASTR, KC_F12,
                KC_DOWN, KC_4,   KC_5,    KC_6,    KC_PLUS, KC_TRNS,
       KC_TRNS, KC_AMPR, KC_1,   KC_2,    KC_3,    KC_BSLS, KC_TRNS,
                         KC_TRNS,KC_DOT,  KC_0,    KC_EQL,  KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MsUp |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      |      |      |      |      |  Play  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      | Prev | Next |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      | Lclk | Rclk |                                       |VolUp |VolDn | Mute |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |Brwser|
 *                                 |      |      |------|       |------|      |Back  |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
KEYMAP(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS,
                          KC_VOLU, KC_VOLD, KC_MUTE, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_WBAK
),
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB)                // FN1 - Momentary Layer 1 (Symbols)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
        if (record->event.pressed) {
          register_code(KC_RSFT);
        } else {
          unregister_code(KC_RSFT);
        }
        break;
      }
    return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void * matrix_init_user(void) {

};

// Runs constantly in the background, in a loop.
void * matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      // TODO: Make this relevant to the ErgoDox EZ.
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        default:
            // none
            break;
    }

};

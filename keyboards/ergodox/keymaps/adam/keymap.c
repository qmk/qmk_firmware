#include "ergodox.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"


#define BASE 0 // default layer
#define FLOCK 1 // symbols arrows and F keys on F held down
#define JLOCK 2 // same as Flock but with fall thru J and mapped to J held down
#define CAPLOCK 3 //caps on until space / enter / esc
#define SFLOCK 11 // symbols arrows and F keys on F held down
#define SJLOCK 12 // same as Flock but with fall thru J and mapped to J held down

#define _______ KC_TRNS
#define XXXXXXX KC_NO

// Sends macro when key is tapped, presses mod when key is held
#define tap_mod_macro(record, mod, macro) ( ((record)->event.pressed) ? \
     ( ((record)->tap.count <= 0 || (record)->tap.interrupted) ? MACRO(D(mod), END) : MACRO_NONE ) : \
     ( ((record)->tap.count > 0 && !((record)->tap.interrupted)) ? (macro) : MACRO(U(mod), END) ) )

#define tap_mod_shift(record, mod, macro) ( ((record)->event.pressed) ? \
          ( ((record)->tap.count <= 0 || (record)->tap.interrupted) ? MACRO(D(mod), END) : MACRO_NONE ) : \
          ( ((record)->tap.count > 0 && !((record)->tap.interrupted)) ? (MACRO( D(LSFT), T(LBRC), U(LSFT), END)) : MACRO(U(mod), END) ) )

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Layout
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |   1  |   2  |   3  |   4  |   5  |      |           |      |   6  |   7  |   8  |   9  |   0  |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   Q  |   W  |   E  |   R  |   T  |      |           |      |   Y  |   U  |   I  |   O  |   P  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |;     |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |  Z   |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |       |     |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |        |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      |      |       |      |        |      |
 *                                 |      |      |------|       |------|        |      |
 *                                 |      |      |      |       |      |        |      |
 *                                 `--------------------'       `----------------------'
 */
        [BASE] = KEYMAP(
                // left hand
                GUI_T(KC_ESC), KC_1, KC_2, KC_3, KC_4, KC_5, KC_MINS,
                _______, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_TAB,
                _______, SFT_T(KC_A), ALT_T(KC_S), CTL_T(KC_D), F(FLOCK), GUI_T(KC_G),
                _______, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_BSPC,
                _______, _______,  _______,  _______ ,_______,
                _______,  _______,
                _______,
                KC_SPC, _______, _______ ,

                // right hand
                KC_EQL,     KC_6,   KC_7,   KC_8,   KC_9,   KC_0,             _______,
                KC_TAB,     KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,             _______,
                GUI_T(KC_H),   F(JLOCK),   CTL_T(KC_K),   ALT_T(KC_L),   SFT_T(KC_SCLN),           _______,
                KC_DELETE,  KC_N,   KC_M,   KC_COMM,KC_DOT, KC_QUOT,           _______,
                _______,  _______,_______,_______,          _______,
                _______,        _______,
                _______,
                _______,_______, KC_ENT
        ),
        [FLOCK] = KEYMAP(
                // left hand
                XXXXXXX,   KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F11,
                XXXXXXX,KC_LBRC,XXXXXXX,  XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
                XXXXXXX,S(KC_LBRC),XXXXXXX, XXXXXXX,_______,XXXXXXX,
                XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,TO(CAPLOCK),XXXXXXX,
                XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
                XXXXXXX,XXXXXXX,
                XXXXXXX,
                KC_ESC,XXXXXXX,XXXXXXX,
                // right hand
                KC_F12, KC_F6,   KC_F7,  KC_F8,   KC_F9,   KC_F10,  XXXXXXX,
                XXXXXXX, XXXXXXX, KC_HOME,   KC_PGUP,    XXXXXXX,    KC_RBRC, XXXXXXX,
                KC_LEFT, KC_DOWN,   KC_UP,    KC_RIGHT,    S(KC_RBRC), XXXXXXX,
                XXXXXXX, XXXXXXX, KC_END,   KC_PGDOWN,    KC_QUES,    KC_SLSH, XXXXXXX,
                XXXXXXX, XXXXXXX,  XXXXXXX,    XXXXXXX,  XXXXXXX,
                XXXXXXX, XXXXXXX,
                XXXXXXX,
                XXXXXXX, XXXXXXX, XXXXXXX
        ),
        [JLOCK] = KEYMAP(
                // left hand
                XXXXXXX,   KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F11,
                XXXXXXX,KC_LBRC,KC_GRV,  KC_TILD,XXXXXXX,XXXXXXX,XXXXXXX,
                XXXXXXX,S(KC_LBRC),XXXXXXX, XXXXXXX,XXXXXXX,XXXXXXX,
                XXXXXXX,KC_BSLS,KC_PIPE,XXXXXXX,XXXXXXX,TO(CAPLOCK),XXXXXXX,
                XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
                XXXXXXX,XXXXXXX,
                XXXXXXX,
                KC_ESC,XXXXXXX,XXXXXXX,
                // right hand
                KC_F12, KC_F6,   KC_F7,  KC_F8,   KC_F9,   KC_F10,  XXXXXXX,
                  XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX,    XXXXXXX,    KC_RBRC, XXXXXXX,
                XXXXXXX, _______,   XXXXXXX,  XXXXXXX,    S(KC_RBRC), XXXXXXX,
                XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX,
                XXXXXXX,XXXXXXX,  XXXXXXX,    XXXXXXX,  XXXXXXX,
                XXXXXXX, XXXXXXX,
                XXXXXXX,
                XXXXXXX, XXXXXXX, XXXXXXX
        ),
        [CAPLOCK] = KEYMAP(
                // left hand
                TO(BASE), _______, _______, _______, _______, _______, _______,
                _______, S(KC_Q), S(KC_W), S(KC_E), S(KC_R), S(KC_T), _______,
                // _______, SFT_T(S(KC_A)), ALT_T(KC_S), CTL_T(KC_D), F(FLOCK), GUI_T(KC_G),
                _______, S(KC_A), S(KC_S), S(KC_D), S(KC_F), S(KC_G),
                _______, S(KC_Z), S(KC_X), S(KC_C), S(KC_V), S(KC_B), _______,
                _______, _______,  _______,  _______ ,_______,
                _______,  _______,
                _______,
                TO(BASE), _______, _______ ,

                // right hand
                _______,     _______,   _______,   _______,   _______,   _______,             _______,
                _______,     S(KC_Y),   S(KC_U),   S(KC_I),   S(KC_O),   S(KC_P),             _______,
                         S(KC_H),   S(KC_J),   S(KC_K),   S(KC_L),   S(KC_SCLN),           _______,
                _______,  S(KC_N),   S(KC_M),   S(KC_COMM),S(KC_DOT), S(KC_QUOT),           _______,
                _______,  _______,_______,_______,          _______,
                _______,        _______,
                _______,
                _______,_______, TO(BASE)
        )
};

const uint16_t PROGMEM fn_actions[] = {
        [1] = ACTION_LAYER_TAP_KEY(FLOCK,KC_F),
        [2] = ACTION_LAYER_TAP_KEY(JLOCK,KC_J),
        [11] = ACTION_LAYER_TAP_KEY(FLOCK,LSFT(KC_F)),
        [12] = ACTION_LAYER_TAP_KEY(JLOCK,LSFT(KC_J))
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
        // MACRODOWN only works in this function
        switch(id) {
        case 0:
                if (record->event.pressed) {
                        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
                }
                break;
        }

        return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};


// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
  uint8_t layer = biton32(layer_state);

  switch (layer) {
    // TODO: Make this relevant to the ErgoDox EZ.
      case 1:
          break;
      case 2:
          break;
      default:
          // none
          break;
  }
};

#include QMK_KEYBOARD_H
#include "version.h"

#define BASE 0 // default layer
#define SYMB 2 // symbols
#define MDIA 3 // media keys

enum unicode_name {
    a_grave = 0x00e0, // à
    e_grave = 0x00e8, // è
    u_grave = 0x00f9, // ù
    e_aigue = 0x00e9, // é
    c_cedil = 0x00e0 // ç
};

enum custom_keycodes {
  VRSN = SAFE_RANGE,
  GMEET,
  TD_A = 0,
  TD_E = 0,
  TD_U = 0,
  TD_C = 0
};

void tap_dance_a (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    SEND_STRING ("a");
    reset_tap_dance (state);
  }
  if (state->count >= 2) {
    unicode_input_start();
    register_hex( a_grave );
    unicode_input_finish();
    reset_tap_dance (state);
  }
};
void tap_dance_c (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    SEND_STRING ("c");
    reset_tap_dance (state);
  }
  if (state->count >= 2) {
    unicode_input_start();
    register_hex( c_cedil );
    unicode_input_finish();
    reset_tap_dance (state);
  }
};
void tap_dance_e (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    SEND_STRING ("e");
    reset_tap_dance (state);
  }
  if (state->count == 2) {
    unicode_input_start();
    register_hex( e_aigue );
    unicode_input_finish();
    reset_tap_dance (state);
  }
  if (state->count >= 3) {
    unicode_input_start();
    register_hex( e_grave );
    unicode_input_finish();
    reset_tap_dance (state);
  }
};
void tap_dance_u (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    SEND_STRING ("u");
    reset_tap_dance (state);
  }
  if (state->count >= 2) {
    unicode_input_start();
    register_hex( u_grave );
    unicode_input_finish();
    reset_tap_dance (state);
  }
};
//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Esc, twice for Caps Lock
  [TD_A]  = ACTION_TAP_DANCE_FN(tap_dance_a),
  [TD_C]  = ACTION_TAP_DANCE_FN(tap_dance_c),
  [TD_E]  = ACTION_TAP_DANCE_FN(tap_dance_e),
  [TD_U]  = ACTION_TAP_DANCE_FN(tap_dance_u);
// Other declarations would go here, separated by commas, if you have them
};



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | Escape |   1  |   2  |   3  |   4  |   5  |   `  |           |   =  |   6  |   7  |   8  |   9  |   0  | BkSp   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Del    |   q  |   w  |   f  |   p  |   g  |  L2  |           |  L2  |   j  |   l  |   u  |   y  |   ;  |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | BkSp   |   a  |   r  |   s  |   t  |   d  |------|           |------|   h  |   n  |   e  |   i  |   o  | Enter  |
 * |--------+------+------+------+------+------|   -  |           |  '   |------+------+------+------+------+--------|
 * | L1     |   w  |   x  |   c  |   v  |   b  |      |           |      |   k  |   m  |   ,  |   .  |   /  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | Ctrl | XXX  | Alt  | Esc  | XXX  |                                       | left | Down |  up  |right | PAUSE  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,---------------.
 *                                        |Print |  {   |       |  }   |   Del  |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 | Space|Backsp|------|       |------|  Tab   |Enter |
 *                                 |      |ace   | End  |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_ESC,         KC_1,         KC_2,       KC_3,       KC_4,       KC_5,     KC_GRV,
        KC_TAB,         KC_Q,         KC_W,       KC_F,       KC_P,       KC_G,     TG(SYMB),
        KC_BSPC,        TD(TD_A),     KC_R,       KC_S,       KC_T,       KC_D,
        KC_LSHIFT,      KC_Z,         KC_X,       TD(TD_C),   KC_V,       KC_B,     KC_MINS,

        KC_RCTL,        KC_NO,        KC_LALT,    KC_ESC,     KC_NO,

                                                                          KC_PSCR,  KC_LCBR,
                                                                                    KC_HOME,
                                                              KC_SPACE,   KC_BSPC,  KC_END,

        // right hand
        KC_EQUAL,       KC_6,         KC_7,       KC_8,       KC_9,       KC_0,     KC_BSPC,
        TG(SYMB),       KC_J,         KC_L,       TD(TD_U),   KC_Y,       KC_SCLN,  KC_BSLS,
                        KC_H,         KC_N,       TD(TD_E),   KC_I,       KC_O,     KC_ENTER,
        KC_QUOT,        KC_K,         KC_M,       KC_COMMA,   KC_DOT,     KC_SLSH,  KC_RSHIFT,

                                      KC_LEFT,    KC_DOWN,    KC_UP,      KC_RIGHT, KC_PAUSE,


        KC_RCBR,        KC_DEL,
        KC_PGUP,
        KC_PGDN,        KC_TAB,KC_ENT
    ),
/* Keymap 1: Symbol Layer
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |Version  |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |   !  |   @  |   {  |   }  |   |  |      |           |      |   Up |   7  |   8  |   9  |   *  |   F12  |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   #  |   $  |   (  |   )  |   `  |------|           |------| Down |   4  |   5  |   6  |   +  |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |   \  |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 * | EEP_RST  |RESET|      |      |      |                                       |      |    . |   0  |   =  |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |Animat|      |       |Toggle|      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |Bright|Bright|      |       |      |Hue-  |Hue+  |
 *                                 |ness- |ness+ |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[SYMB] = LAYOUT_ergodox(
       // left hand
       VRSN,      KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_TRNS,
       GMEET,   KC_EXLM,  KC_AT,    KC_LCBR,  KC_RCBR,  KC_PIPE,  KC_TRNS,
       KC_TRNS,   KC_HASH,  KC_DLR,   KC_LPRN,  KC_RPRN,  KC_GRV,
       KC_TRNS,   KC_PERC,  KC_CIRC,  KC_LBRC,  KC_RBRC,  KC_TILD,  KC_TRNS,
       EEP_RST,   RESET,KC_TRNS,KC_TRNS,KC_TRNS,
                                       RGB_MOD,KC_TRNS,
                                               KC_TRNS,
                               RGB_VAD,RGB_VAI,KC_TRNS,
       // right hand
       KC_TRNS, KC_F6,   KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,
       KC_TRNS, KC_UP,   KC_7,   KC_8,    KC_9,    KC_ASTR, KC_F12,
                KC_DOWN, KC_4,   KC_5,    KC_6,    KC_PLUS, KC_TRNS,
       KC_TRNS, KC_AMPR, KC_1,   KC_2,    KC_3,    KC_BSLS, KC_TRNS,
                         KC_TRNS,KC_DOT,  KC_0,    KC_EQL,  KC_TRNS,
       RGB_TOG, KC_TRNS,
       KC_TRNS,
       KC_TRNS, RGB_HUD, RGB_HUI
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
[MDIA] = LAYOUT_ergodox(
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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;
  // Test macro 1
    case GMEET:
      if (record->event.pressed) {
        // when keycode QMKBEST is pressed
        SEND_STRING("QMK is the best thing ever!\n QMK.fm\n Accents: à/é/è/ê");
      } else {
        // when keycode QMKBEST is released
      }
      break;
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
    set_unicode_input_mode(UC_LNX);
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

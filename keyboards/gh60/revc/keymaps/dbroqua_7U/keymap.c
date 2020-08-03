#include QMK_KEYBOARD_H

#define _DEFAULT 0
#define _FN 1

int esc_led = 0;

// Fillers to make layering more clear
#define ______ KC_TRNS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Qwerty gui/alt/space/alt/gui
 * ,-----------------------------------------------------------------------------------------.
 * | Esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |  \  |  `  |
 * |-----------------------------------------------------------------------------------------+
 * | Tab    |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |  Bksp  |
 * |-----------------------------------------------------------------------------------------+
 * | Ctrl    |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |    Enter    |
 * |-----------------------------------------------------------------------------------------+
 * | Shift     |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  | RShift    | FN  |
 * |-----------------------------------------------------------------------------------------+
 *         |LGUI | LAlt  |               Space                | RAlt   |RGUI |
 *         `-----------------------------------------------------------------'
 */
  [_DEFAULT] = LAYOUT_60_ansi_split_bs_rshift( /* Basic QWERTY */
      KC_ESC,  KC_1,    KC_2,    KC_3, KC_4, KC_5,   KC_6, KC_7, KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_GRV, \
      KC_TAB,  KC_Q,    KC_W,    KC_E, KC_R, KC_T,   KC_Y, KC_U, KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,  \
      KC_LCTL, KC_A,    KC_S,    KC_D, KC_F, KC_G,   KC_H, KC_J, KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,  \
      KC_LSFT, KC_Z,    KC_X,    KC_C, KC_V, KC_B,   KC_N, KC_M, KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, MO(_FN), \
      ______,  KC_LGUI, KC_LALT,             KC_SPC,             ______,  KC_RALT, KC_RGUI, ______ \
      ),

/* FN Layer
 * ,-----------------------------------------------------------------------------------------.
 * | Led | F1  | F2  | F3  | F4  | F5  | F6  | F7  | F8  | F9  | F10 | F11 | F12 | Ins | Del |
 * |-----------------------------------------------------------------------------------------+
 * |  CAPS  |     |     |     |     |     |     |     | Psc | Slck| Paus| Up  |     |        |
 * |-----------------------------------------------------------------------------------------+
 * |         | Vol-| Vol+| Mute|     |     | *   | /   | Home| PgUp| Left|Right|             |
 * |-----------------------------------------------------------------------------------------+
 * |           | Prev| Play| Next|     |     | +   | -   | End  |PgDn| Down|           |     |
 * |-----------------------------------------------------------------------------------------+
 *         |       |       |                                 | Stop  |       |
 *         `-----------------------------------------------------------------'
 */
  [_FN] = LAYOUT_60_ansi_split_bs_rshift( /* Layer 1 */
      F(0),   KC_F1,   KC_F2,   KC_F3,   KC_F4,  KC_F5,  KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, KC_F12, KC_INS,  KC_DEL, \
      KC_CAPS, ______,  ______,  ______,  ______, ______, ______,  ______,  KC_PSCR, KC_SLCK, KC_PAUS, KC_UP,  ______, ______,  \
      ______,  KC_VOLD, KC_VOLU, KC_MUTE, ______, ______, KC_PAST, KC_PSLS, KC_HOME, KC_PGUP, KC_LEFT, KC_RGHT,______,   \
      ______,  KC_MPRV, KC_MPLY, KC_MNXT, ______, ______, KC_PPLS, KC_PMNS, KC_END,  KC_PGDN, KC_DOWN, ______, ______,  \
      ______,  ______,  ______,                   ______,                   ______,  KC_MSTP, ______,  ______ \
      )
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
  return MACRO_NONE;
};

enum function_id {
    LED_TOGGLE
};

const uint16_t PROGMEM fn_actions[] = {
  [0]  = ACTION_FUNCTION(LED_TOGGLE)
};

void esc_led_toggle(void) {
    if (esc_led == 0){
        esc_led = 1;
        gh60_esc_led_on();
    } else {
        esc_led = 0;
        gh60_esc_led_off();
    }
}

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
  switch (id) {
    case LED_TOGGLE:
      if (record->event.pressed) {
        esc_led_toggle();
      }
      break;
  }
}
#include QMK_KEYBOARD_H

#define _BL 0
#define _AL 1
#define _FL 2
#define _UL 3

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
   /*
   *  Base layer, pretty standard ANSI layout.
   * ,-----------------------------------------------------------.
   * |F(12)| 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |
   * |-----------------------------------------------------------|
   * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|
   * |-----------------------------------------------------------|
   * |Caps/Fn|  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |
   * |-----------------------------------------------------------|
   * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift     |
   * |-----------------------------------------------------------|
   * |Ctrl|Gui |Alt |      Space             |Alt |Fn  |Menu|Ctrl|
   * `-----------------------------------------------------------'
   */
  [_BL] = LAYOUT(
        F(12),KC_1,KC_2,KC_3,KC_4,KC_5,KC_6,KC_7,KC_8,KC_9,KC_0,KC_MINS,KC_EQL,KC_BSPC, \
        KC_TAB,KC_Q,KC_W,KC_E,KC_R,KC_T,KC_Y,KC_U,KC_I,KC_O,KC_P,KC_LBRC,KC_RBRC,KC_BSLS, \
        F(2),KC_A,KC_S,KC_D,KC_F,KC_G,KC_H,KC_J,KC_K,KC_L,KC_SCLN,KC_QUOT,KC_NO,KC_ENT,  \
        KC_LSFT,KC_NO,KC_Z,KC_X,KC_C,KC_V,KC_B,KC_N,KC_M,KC_COMM,KC_DOT,KC_SLSH,KC_NO,KC_RSFT, \
        KC_LCTL,KC_LGUI,KC_LALT,        KC_SPC,      KC_NO,KC_RALT,MO(2),KC_APP,KC_RCTL),

   /*
   * Locking arrow keys to WASD for when you need dedicated arrow keys
   * ,-----------------------------------------------------------.
   * |    |  |   |   |   |   |   |   |   |   |   |   |   |       |
   * |-----------------------------------------------------------|
   * |     |   |Up |   |   |   |   |   |   |   |   |   |   |     |
   * |-----------------------------------------------------------|
   * |       |Left|Down|Rght|   |   |   |   |   |   |   |   |    |
   * |-----------------------------------------------------------|
   * |        |   |   |   |   |   |   |   |   |   |   |          |
   * |-----------------------------------------------------------|
   * |    |    |    |                        |    |    |    |    |
   * `-----------------------------------------------------------'
   */
  [_AL] = LAYOUT(
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, \
        KC_TRNS,KC_TRNS,KC_UP,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, \
        KC_TRNS,KC_LEFT,KC_DOWN,KC_RGHT,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, \
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,   \
        KC_TRNS,KC_TRNS,KC_TRNS,          KC_TRNS,               KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS),


   /*
   * Primary function layer, mostly the same as the traditional Pok3r layout.
   * ,-------------------------------------------------------------.
   * |`~ | F1| F2| F3| F4| F5| F6| F7| F8| F9| F10| F11| F12|DEL   |
   * |-------------------------------------------------------------|
   * |    |_AL|   |   |  |  |Calc|PgUp|Up|PgDn|Ptscn|Srlck|Pause|  |
   * |-------------------------------------------------------------|
   * |      |   |   |   |   |   |Home|Left|Down|Rght|Ins|   |      |
   * |-------------------------------------------------------------|
   * |        |_UL|   |   |   |   |   |    |    |    |   |         |
   * |-------------------------------------------------------------|
   * |    |    |    |                          |    |    |    |    |
   * `-------------------------------------------------------------'
   */
  [_FL] = LAYOUT(
        KC_GRAVE,KC_F1,KC_F2,KC_F3,KC_F4,KC_F5,KC_F6,KC_F7,KC_F8,KC_F9,KC_F10,KC_F11,KC_F12,KC_DELETE, \
        KC_TRNS,F(1),KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_CALC,KC_PGUP,KC_UP,KC_PGDN,KC_PSCR,KC_SLCK,KC_PAUS,KC_TRNS, \
        KC_TRNS,KC_MUTE,KC__VOLDOWN,KC__VOLUP,KC_TRNS,KC_TRNS,KC_HOME,KC_LEFT,KC_DOWN,KC_RGHT,KC_INS,KC_TRNS,KC_TRNS,KC_TRNS, \
        KC_TRNS,KC_TRNS,F(3),KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_END,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, \
        KC_TRNS,KC_TRNS,KC_TRNS,          KC_TRNS,               KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS),

   /*
   * Locking layer for controlling the underglow.
   *
   * ,-----------------------------------------------------------.
   * |    |  |   |   |   |   |   |   |   |   |   |   |   |       |
   * |-----------------------------------------------------------|
   * |     |   |   |   |   |   |   |   |   |   |   |   |   |     |
   * |-----------------------------------------------------------|
   * |       |On|Mode|   |   |   |   |   |   |   |   |   |       |
   * |-----------------------------------------------------------|
   * |        |   |Hue+|Hue-|Sat+|Sat-|Val+|Val-|  |  |   |      |
   * |-----------------------------------------------------------|
   * |    |    |    |                        |    |    |    |    |
   * `-----------------------------------------------------------'
   */
  [_UL] = LAYOUT(
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, \
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, \
        KC_TRNS,F(4),F(5),KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, \
        KC_TRNS,KC_TRNS,KC_TRNS,F(6),F(7),F(8),F(9),F(10),F(11),KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,   \
        KC_TRNS,KC_TRNS,KC_TRNS,          KC_TRNS,               KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS),
};

enum function_id {
    RGBLED_TOGGLE,
    RGBLED_STEP_MODE,
    RGBLED_INCREASE_HUE,
    RGBLED_DECREASE_HUE,
    RGBLED_INCREASE_SAT,
    RGBLED_DECREASE_SAT,
    RGBLED_INCREASE_VAL,
    RGBLED_DECREASE_VAL,
    SHIFT_ESC,
};

const uint16_t PROGMEM fn_actions[] = {
    [1]  = ACTION_LAYER_TOGGLE(1),     // Toggle Arrow Layer overlay
    [2]  = ACTION_LAYER_TAP_KEY(2, KC_CAPS), // Tap to toggle caps lock and hold to activate function layer
    [3]  = ACTION_LAYER_TOGGLE(3),     // Toggle Underglow Layer overlay
    [4]  = ACTION_FUNCTION(RGBLED_TOGGLE), //Turn on/off underglow
    [5]  = ACTION_FUNCTION(RGBLED_STEP_MODE), // Change underglow mode
    [6]  = ACTION_FUNCTION(RGBLED_INCREASE_HUE),
    [7]  = ACTION_FUNCTION(RGBLED_DECREASE_HUE),
    [8]  = ACTION_FUNCTION(RGBLED_INCREASE_SAT),
    [9]  = ACTION_FUNCTION(RGBLED_DECREASE_SAT),
    [10] = ACTION_FUNCTION(RGBLED_INCREASE_VAL),
    [11] = ACTION_FUNCTION(RGBLED_DECREASE_VAL),
    [12] = ACTION_FUNCTION(SHIFT_ESC),
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

void matrix_scan_user(void) {

// Layer LED indicators
// ESC led on when in function layer, WASD cluster leds enabled when on arrow cluster
    uint32_t layer = layer_state;
    if (layer & (1<<1)) {
        gh60_wasd_leds_on();
    } else {
        gh60_wasd_leds_off();
    }

    if (layer & (1<<2)) {
        gh60_esc_led_on();
    } else {
        gh60_esc_led_off();
    }
};

#define MODS_CTRL_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
  switch (id) {
    case RGBLED_TOGGLE:
      //led operations
      if (record->event.pressed) {
        rgblight_toggle();
        }
        break;
    case RGBLED_INCREASE_HUE:
      if (record->event.pressed) {
        rgblight_increase_hue();
        }
        break;
    case RGBLED_DECREASE_HUE:
      if (record->event.pressed) {
        rgblight_decrease_hue();
        }
        break;
    case RGBLED_INCREASE_SAT:
      if (record->event.pressed) {
        rgblight_increase_sat();
        }
        break;
    case RGBLED_DECREASE_SAT:
      if (record->event.pressed) {
        rgblight_decrease_sat();
        }
        break;
    case RGBLED_INCREASE_VAL:
        if (record->event.pressed) {
          rgblight_increase_val();
        }
        break;
    case RGBLED_DECREASE_VAL:
        if (record->event.pressed) {
          rgblight_decrease_val();
        }
        break;
    case RGBLED_STEP_MODE:
        if (record->event.pressed) {
          rgblight_step();
        }
        break;
    static uint8_t shift_esc_shift_mask;
    // Shift + ESC = ~
    case SHIFT_ESC:
      shift_esc_shift_mask = get_mods()&MODS_CTRL_MASK;
      if (record->event.pressed) {
        if (shift_esc_shift_mask) {
          add_key(KC_GRV);
          send_keyboard_report();
        } else {
          add_key(KC_ESC);
          send_keyboard_report();
        }
      } else {
        if (shift_esc_shift_mask) {
          del_key(KC_GRV);
          send_keyboard_report();
        } else {
          del_key(KC_ESC);
          send_keyboard_report();
        }
      }
      break;
    }
};

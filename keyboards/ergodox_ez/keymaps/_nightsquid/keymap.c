#include QMK_KEYBOARD_H
#include "version.h"

#define KC_MAC_UNDO LGUI(KC_Z)
#define KC_MAC_CUT LGUI(KC_X)
#define KC_MAC_COPY LGUI(KC_C)
#define KC_MAC_PASTE LGUI(KC_V)
#define KC_PC_UNDO LCTL(KC_Z)
#define KC_PC_CUT LCTL(KC_X)
#define KC_PC_COPY LCTL(KC_C)
#define KC_PC_PASTE LCTL(KC_V)
#define ES_LESS_MAC KC_GRAVE
#define ES_GRTR_MAC LSFT(KC_GRAVE)
#define ES_BSLS_MAC ALGR(KC_6)
#define NO_PIPE_ALT KC_GRAVE
#define NO_BSLS_ALT KC_EQUAL

enum custom_keycodes {
  RGB_SLD = EZ_SAFE_RANGE,
  CTRL_CMD_SPACE = EZ_SAFE_RANGE,
  XCTABLEFT = EZ_SAFE_RANGE + 1,
  XCTABRIGHT = EZ_SAFE_RANGE + 2,
};   

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_ergodox_pretty(
    KC_GRAVE,       KC_1,           KC_2,           KC_3,           KC_4,           KC_5,           KC_MS_BTN1,                                     KC_MS_BTN2,     KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           KC_MINUS,
    KC_TAB,         KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,           KC_TRANSPARENT,                                 KC_LALT,        KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           KC_BSLASH,
    KC_ESCAPE,      KC_A,           KC_S,           KC_D,           KC_F,           KC_G,                                                                           KC_H,           KC_J,           KC_K,           KC_L,           KC_SCOLON,      KC_QUOTE,
    KC_LSHIFT,      KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,           KC_TRANSPARENT,                                 KC_LGUI,        KC_N,           KC_M,           KC_COMMA,       KC_DOT,         KC_SLASH,       KC_RSHIFT,
    KC_LCTRL,       KC_TRANSPARENT, CTRL_CMD_SPACE, KC_LALT,        KC_LGUI,                                                                                                        XCTABLEFT,      XCTABRIGHT,   KC_AUDIO_VOL_DOWN,KC_AUDIO_VOL_UP,KC_EQUAL,
                                                                                                    KC_MS_WH_LEFT,  KC_MS_WH_RIGHT, KC_MS_LEFT,     KC_MS_RIGHT,
                                                                                                                    KC_MS_WH_UP,    KC_MS_UP,
                                                                                    KC_SPACE,       TT(1),          TT(2),          TT(3),          KC_BSPACE,      KC_ENTER
  ),

  [1] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_F6,          KC_F7,          KC_F8,          KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_LPRN,        KC_RPRN,        KC_LCBR,        KC_RCBR,        KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_PLUS,        KC_MS_WH_LEFT,  KC_MS_WH_DOWN,  KC_MS_WH_UP,    KC_MS_WH_RIGHT, KC_TRANSPARENT,
    KC_ESCAPE,      KC_LCTRL,       KC_LALT,        KC_LGUI,        KC_MS_BTN1,     KC_MS_BTN2,                                                                     KC_MINUS,       KC_LEFT,        KC_DOWN,        KC_UP,          KC_RIGHT,       KC_TRANSPARENT,
    KC_TRANSPARENT, KC_LBRACKET,    KC_RBRACKET,    KC_TRANSPARENT, KC_LSHIFT,      KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_MS_LEFT,     KC_MS_DOWN,     KC_MS_UP,       KC_MS_RIGHT,  KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_AUDIO_MUTE,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, TG(1),          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  
  [2] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_5,           KC_6,           KC_7,           KC_8,           KC_9,           KC_TRANSPARENT,     
    KC_ESCAPE,      KC_LCTRL,       KC_LALT,        KC_LGUI,        KC_MS_BTN1,     KC_MS_BTN2,                                                                     KC_0,           KC_1,           KC_2,           KC_3,           KC_4,           KC_TRANSPARENT,     
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_LSHIFT,      KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, TG(2),          TG(2),          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),

  [3] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, MI_E_3,         MI_F_3,         MI_Fs_3,        MI_G_3,         KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, MI_E_5,         MI_F_5,         MI_Fs_5,        MI_G_5,         KC_TRANSPARENT,
    KC_TRANSPARENT, MI_C_3,         MI_Cs_3,        MI_D_3,         MI_Ds_3,        KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, MI_C_5,         MI_Cs_5,        MI_D_5,         MI_Ds_5,        KC_TRANSPARENT,
    KC_TRANSPARENT, MI_Gs_2,        MI_A_2,         MI_As_2,        MI_B_2,         KC_TRANSPARENT,                                                                 KC_TRANSPARENT, MI_Gs_4,        MI_A_4,         MI_As_4,        MI_B_4,         KC_TRANSPARENT,
    KC_TRANSPARENT, MI_E_2,         MI_F_2,         MI_Fs_2,        MI_G_2,         KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, MI_E_4,         MI_F_4,         MI_Fs_4,        MI_G_4,         KC_TRANSPARENT,
    KC_TRANSPARENT, MI_C_2,         MI_Cs_2,        MI_D_2,         MI_Ds_2,                                                                                                        MI_C_4,         MI_Cs_4,        MI_D_4,         MI_Ds_4,        KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, TT(1),          TT(2),          TT(3),          KC_TRANSPARENT, KC_TRANSPARENT
  ),
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case CTRL_CMD_SPACE:
      if (record->event.pressed) {
        // Press command, alt and control
        register_code(KC_LGUI);
        register_code(KC_LCTRL);
        register_code(KC_SPACE);
      } else {
        unregister_code(KC_LGUI);
        unregister_code(KC_LCTRL);
        unregister_code(KC_SPACE);
      }
      break;
    case XCTABLEFT:
      if (record->event.pressed) {
        register_code(KC_LGUI);
        register_code(KC_LSHIFT);
        register_code(KC_LBRC);
      } else {
        unregister_code(KC_LGUI);
        unregister_code(KC_LSHIFT);
        unregister_code(KC_LBRC);
      }
      break;
    case XCTABRIGHT:
      if (record->event.pressed) {
        register_code(KC_LGUI);
        register_code(KC_LSHIFT);
        register_code(KC_RBRC);
      } else {
        unregister_code(KC_LGUI);
        unregister_code(KC_LSHIFT);
        unregister_code(KC_RBRC);
      }
    break;
  }
  return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
  uint8_t layer = biton32(state);
  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();
  switch (layer) {
    case 1:
      ergodox_right_led_1_on();
      break;
    case 2:
      ergodox_right_led_2_on();
      break;
    case 3:
      ergodox_right_led_3_on();
      break;
    case 4:
      ergodox_right_led_1_on();
      ergodox_right_led_2_on();
      break;
    case 5:
      ergodox_right_led_1_on();
      ergodox_right_led_3_on();
      break;
    case 6:
      ergodox_right_led_2_on();
      ergodox_right_led_3_on();
      break;
    case 7:
      ergodox_right_led_1_on();
      ergodox_right_led_2_on();
      ergodox_right_led_3_on();
      break;
    default:
      break;
  }
  return state;
};

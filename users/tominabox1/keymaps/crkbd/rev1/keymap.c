#include QMK_KEYBOARD_H
#include "tominabox1.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_wrapper(
    KC_TABESC, _______________COLEMAK1____________________, KC_BSPC,
    KC_CTLTB,  _______________COLEMAK2____________________, KC_QUOT,
    KC_LSFT,   _______________COLEMAK3____________________, KC_RSFT,
    KC_LGUI, KC_LALT, KC_NUM_SPC,  KC_NUM_SPC,  KC_NAV_ENT, MO(_FKEY)
  ),
/*
  [_RAISE] = LAYOUT_wrapper(
    ___________________NAV1____________________,
    ___________________NAV2____________________,
    ___________________CRKBD_RAISE3____________,
    ___________________CRKBD_RAISE4____________
  ),

  [_LOWER] = LAYOUT_wrapper(
    _________________LOWER_1___________________,
    _________________LOWER_2___________________,
    ___________________CRKBD_LOW3______________,
    ___________________CRKBD_LOW4______________
  ),

  [_ADJUST] = LAYOUT_wrapper(
    ___________________ADJST1__________________,
    ___________________CRKBD_ADJST2____________,
    ___________________CRKBD_ADJST3____________,
    ___________________CRKBD_ADJST4____________
  ),

  [_ARROW] = LAYOUT_wrapper(
    ___________________ARROW1__________________,
    ___________________ARROW2__________________,
    ___________________ARROW3__________________,
    ___________________ARROW4__________________
  ),
  [_FKEY] = LAYOUT_wrapper(
    ___________________FKEY1___________________,
    ___________________FKEY2___________________,
    ___________________CRKBD_FKEY3_____________,
    ___________________CRKBD_FKEY4_____________
  )
*/
};
void keyboard_post_init_user(void){
  wait_ms(2000);
  oled_init(0);
}

#ifdef RGB_MATRIX_ENABLE
void rgb_matrix_layer_helper(uint8_t hue, uint8_t sat, uint8_t val, uint8_t mode, uint8_t speed, uint8_t led_type);
static bool is_suspended;
static bool rgb_matrix_enabled;

void suspend_power_down_user(void) {
  rgb_matrix_set_suspend_state(true);
  if (!is_suspended) {
    is_suspended = true;
    rgb_matrix_enabled = (bool)rgb_matrix_config.enable;
    rgb_matrix_disable_noeeprom();
  }
}

void suspend_wakeup_init_user(void) {
  rgb_matrix_set_suspend_state(false);
  is_suspended = false;
  if (rgb_matrix_enabled) {
    rgb_matrix_enable_noeeprom();
  }
}

#include "lib/lib8tion/lib8tion.h"
extern led_config_t g_led_config;
void rgb_matrix_layer_helper(uint8_t hue, uint8_t sat, uint8_t val, uint8_t mode, uint8_t speed, uint8_t led_type) {
  HSV hsv = {hue, sat, val};
  if (hsv.v > rgb_matrix_config.hsv.v) {
    hsv.v = rgb_matrix_config.hsv.v;
  }

  switch (mode) {
    case 1:  // breathing
    {
      uint16_t time = scale16by8(g_rgb_counters.tick, speed / 8);
      hsv.v         = scale8(abs8(sin8(time) - 128) * 2, hsv.v);
      RGB rgb       = hsv_to_rgb(hsv);
      for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
        if (HAS_FLAGS(g_led_config.flags[i], led_type)) {
          rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
      }
      break;
    }
    default:  // Solid Color
    {
      RGB rgb = hsv_to_rgb(hsv);
      for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
        if (HAS_FLAGS(g_led_config.flags[i], led_type)) {
          rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
      }
      break;
    }
  }
}
#endif //RGB_MATRIX_ENABLE

extern uint8_t is_master;

uint16_t        oled_timer;

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  #ifdef CONSOLE_ENABLE
  uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
  #endif

  if (record->event.pressed) {
    #ifdef OLED_DRIVER_ENABLE
    oled_timer = timer_read();
    oled_on();
    #endif // OLED_DRIVER_ENABLE
  }
  return true;

}

#ifdef OLED_DRIVER_ENABLE
void render_logo(void) {
  static const char PROGMEM logo[] = {
    0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
    0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
    0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
    0};
    oled_write_P(logo, false);
  }

  void render_status_main(void) {
    // Host Keyboard USB Status
    oled_write_P(PSTR("USB: "), false);
    switch (USB_DeviceState) {
      case DEVICE_STATE_Unattached:
      oled_write_P(PSTR("Unattached\n"), false);
      break;
      case DEVICE_STATE_Suspended:
      oled_write_P(PSTR("Suspended\n"), false);
      break;
      case DEVICE_STATE_Configured:
      oled_write_P(PSTR("Connected\n"), false);
      break;
      case DEVICE_STATE_Powered:
      oled_write_P(PSTR("Powered\n"), false);
      break;
      case DEVICE_STATE_Default:
      oled_write_P(PSTR("Default\n"), false);
      break;
      case DEVICE_STATE_Addressed:
      oled_write_P(PSTR("Addressed\n"), false);
      break;
      default:
      oled_write_P(PSTR("Invalid\n"), false);
    }

    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
    switch (biton32(layer_state)) {
      case _BASE:
      oled_write_P(PSTR("Base\n"), false);
      break;
      case _NUM_SYM:
      oled_write_P(PSTR("Num/Symbol\n"), false);
      break;
      case _NAV:
      oled_write_P(PSTR("Navigation\n"), false);
      break;
      case _FKEY:
      oled_write_P(PSTR("Function\n"), false);
      break;
      default:
      // Or use the write_ln shortcut over adding '\n' to the end of your string
      oled_write_ln_P(PSTR("Undefined"), false);
    }

    // Host Keyboard LED Status

    oled_write_ln_P(IS_HOST_LED_ON(USB_LED_CAPS_LOCK) ? PSTR("Caps Lock\n") : PSTR("         \n"), false);
  }

  void oled_task_user(void) {

    if (timer_elapsed(oled_timer) > 20000) {
      oled_off();
      return;
    }
    if (is_master) {
      render_status_main();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {}
  }

  #endif // OLED_Driver

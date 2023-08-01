#include QMK_KEYBOARD_H
#include "jarred.h"

#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

#define LAYOUT_crkbd_base( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, \
                   K31, K32, K33, K34, K35, K36 \
  )

#define LAYOUT_crkbd_wrapper(...) LAYOUT_split_3x6_3(__VA_ARGS__)

#define QWERTY_4_CRKBD KC_LCTL, MO(_LW), KC_SPC, KC_ENT, MO(_LW), KC_RALT

#define BLANK_4_CRKBD  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QW] = LAYOUT_crkbd_wrapper(
    QWERTY_1_12,
    QWERTY_2_12,
    QWERTY_3_12,
    QWERTY_4_DOX
  ),

  [_LW] = LAYOUT_crkbd_wrapper(
    LOWER_1_12,
    LOWER_2_12,
    LOWER_3_12,
    LOWER_4_DOX
  ),

  [_NV] = LAYOUT_crkbd_wrapper(
    NAV_1_12,
    NAV_2_12,
    NAV_3_12,
    NAV_4_DOX
  ),

  [_NP] = LAYOUT_crkbd_wrapper(
    NUMPAD_1_12,
    NUMPAD_2_12,
    NUMPAD_3_12,
    NUMPAD_4_DOX
  ),

  [_MS] = LAYOUT_crkbd_wrapper(
    MOUSE_1_12,
    MOUSE_2_12,
    MOUSE_3_12,
    MOUSE_4_DOX
  )
};

#ifdef OLED_ENABLE

// When add source files to SRC in rules.mk, you can use functions.
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

char matrix_line_str[24];

const char *read_layer_state(void) {
  uint8_t layer = get_highest_layer(layer_state);

  strcpy(matrix_line_str, "Layer: ");

  switch (layer)
  {
    case _QW:
      strcat(matrix_line_str, "Default");
      break;
    case _LW:
      strcat(matrix_line_str, "Lower");
      break;
    case _NV:
      strcat(matrix_line_str, "Navigation");
      break;
    case _NP:
      strcat(matrix_line_str, "Adjust");
      break;
    case _MS:
      strcat(matrix_line_str, "Mouse");
      break;
    default:
      sprintf(matrix_line_str + strlen(matrix_line_str), "Unknown (%d)", layer);
  }

  return matrix_line_str;
}

const char *read_usb_state(void) {

  strcpy(matrix_line_str, "USB  : ");

  switch (USB_DeviceState) {
    case DEVICE_STATE_Unattached:
      strcat(matrix_line_str, "Unattached");
      break;
    case DEVICE_STATE_Suspended:
      strcat(matrix_line_str, "Suspended");
      break;
    case DEVICE_STATE_Configured:
      strcat(matrix_line_str, "Connected");
      break;
    case DEVICE_STATE_Powered:
      strcat(matrix_line_str, "Powered");
      break;
    case DEVICE_STATE_Default:
      strcat(matrix_line_str, "Default");
      break;
    case DEVICE_STATE_Addressed:
      strcat(matrix_line_str, "Addressed");
      break;
    default:
      strcat(matrix_line_str, "Invalid");
  }

  return matrix_line_str;
}

bool oled_task_user(void) {
  if (is_keyboard_master()) {
    oled_write_ln(read_layer_state(), false);
    oled_write_ln(read_usb_state(), false);
    oled_write_ln(read_keylogs(), false);
  } else {
    oled_write(read_logo(), false);
  }
  return false;
}

#endif

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    set_keylog(keycode, record);
  }

  return true;
}

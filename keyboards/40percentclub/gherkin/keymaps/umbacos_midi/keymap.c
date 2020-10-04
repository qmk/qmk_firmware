#include QMK_KEYBOARD_H

backlight_config_t backlight_config;

enum MUDI_layers {
  _MUDI,
  _QWERTY,
  _SUPER,
  _SHIFT_SUPER,
  _LOWER,
  _ACCENT,
  _ALT_TAB,
  _MUSIC,
  _SERVICE
};

#define FN1_Q LT(_SERVICE, KC_Q)
#define FN2_W LT(_QWERTY, KC_W)
#define FN3_W LT(_MUDI, KC_W)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_MUDI] = LAYOUT_ortho_3x10(
    FN1_Q,   FN2_W,   BL_TOGG, BL_STEP, BL_BRTG,    RGB_TOG,    RGB_MOD,    KC_I,    KC_O,    KC_P,
    MI_Cs_3, MI_Ds_3, MI_OCTU, MI_Fs_3, MI_Gs_3, MI_As_3, MI_OCTD,KC_K,    KC_L,    KC_ESC,
    MI_C_3,  MI_D_3,  MI_E_3, MI_F_3,  MI_G_3,  MI_A_3,  MI_B_3, MI_C_4,KC_M,    KC_ENT
  ),

  [_QWERTY] = LAYOUT_ortho_3x10(
    FN1_Q,   FN3_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_ESC,
    KC_Z,    KC_X,    KC_C,    KC_V,    KC_BSPC, KC_SPC,  KC_B,    KC_N,    KC_M,    KC_ENT
  ),

  [_SERVICE] = LAYOUT_ortho_3x10(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    TO(_QWERTY), RGB_TOG, _______, _______, _______, _______, _______, _______, _______, BL_INC,
    TO(_MUDI), RGB_MOD, _______, _______, _______, _______, RESET,   _______, _______, BL_DEC
  ),

};


void matrix_init_user(void) {
    // Set LED's to max
    _delay_us(300);
    backlight_config.level = 2;
    backlight_config.enable = 1;
    eeconfig_update_backlight(backlight_config.raw);
    backlight_set(backlight_config.level);
}


void led_set_user(uint8_t usb_led) {
  if (IS_LED_ON(usb_led, USB_LED_NUM_LOCK)) {
    writePinLow(D5);
  } else {
    writePinHigh(D5);
  }

  if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
    writePinLow(B0);
  } else {
    writePinHigh(B0);
  }
}

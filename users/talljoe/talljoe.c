#include QMK_KEYBOARD_H

#include "talljoe.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = TEMPLATE_TKL(
      KC_ESC,  KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 ,          KC_PSCR, KC_SLCK, MO_ADJ ,
      KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS, KC_EQL , KC_BSLS, KC_INS , KC_HOME, KC_PGUP,
      KC_TAB , KC_Q,    KC_W,    KC_E,    KC_R,    KC_T   , KC_Y,    KC_U,    KC_I,    KC_O,    KC_P   , KC_LBRC, KC_RBRC, KC_BSPC, KC_DEL , KC_END , KC_PGDN,
      US_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G   , KC_H,    KC_J,    KC_K,    KC_L,    US_SCLN, US_QUOT,          US_ENT ,
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B   , KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                   KC_RSFT,          KC_UP  ,
      KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC2, KC_SPC1, KC_SPC3,                   KC_RALT, KC_RGUI, KC_RCTL, KC_PTT , KC_LEFT, KC_DOWN, KC_RGHT),
  [_WORKMAN] = TEMPLATE(
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, KC_Q   , KC_D   , KC_R   , KC_W   , KC_B   , KC_J   , KC_F   , KC_U   , KC_P   , US_SCLN, _______, _______, _______,
      _______, KC_A   , KC_S   , KC_H   , KC_T   , KC_G   , KC_Y   , KC_N   , KC_E   , KC_O   , KC_I   , _______,          _______,
      _______, KC_Z   , KC_X   , KC_M   , KC_C   , KC_V   , KC_K   , KC_L   , KC_COMM, KC_DOT , KC_SLSH,          _______, _______,
      _______, _______, _______,                   _______, _______, _______,                   _______, _______, _______, _______),
  [_NORMAN] = TEMPLATE(
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, KC_Q   , KC_W   , KC_D   , KC_F   , KC_K   , KC_J   , KC_U   , KC_R   , KC_L   , US_SCLN, _______, _______, _______,
      _______, KC_A   , KC_S   , KC_E   , KC_T   , KC_G   , KC_Y   , KC_N   , KC_I   , KC_O   , KC_H   , _______,          _______,
      _______, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_P   , KC_M   , KC_COMM, KC_DOT , KC_SLSH,          _______, _______,
      _______, _______, _______,                   _______, _______, _______,                   _______, _______, _______, _______),
  [_DVORAK] = TEMPLATE(
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_LBRC, KC_RBRC, _______, _______,
      _______, KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y   , KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH, KC_EQL , _______,
      _______, KC_A,    KC_O,    KC_E,    KC_U,    KC_I   , KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    US_MINS,          _______,
      _______, US_SCLN, KC_Q,    KC_J,    KC_K,    KC_X   , KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,             _______, _______,
      _______, _______, _______,                   _______, _______, _______,                   _______, _______, _______, _______),
  [_COLMAK] = TEMPLATE(
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, KC_Q,    KC_W,    KC_F,    KC_P,    KC_G   , KC_J,    KC_L,    KC_U,    KC_Y,    US_SCLN, _______, _______, _______,
      _______, KC_A,    KC_R,    KC_S,    KC_T,    KC_D   , KC_H,    KC_N,    KC_E,    KC_I,    KC_O   , _______,          _______,
      _______, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B   , KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          _______, _______,
      _______, _______, _______,                   _______, _______, _______,                   _______, _______, _______, _______),

#ifdef ENABLE_GAME_LAYER
  [_GAME] = TEMPLATE(
      KC_ESC , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS, KC_EQL , KC_BSLS, KC_GRV,
      KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_LBRC, KC_RBRC, KC_BSPC,
      MO_NAV , KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,          KC_ENT ,
      KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH,          KC_RSFT, MO_ADJ ,
      KC_LCTL, KC_PTT , KC_PGDN,                   KC_SPC , KC_SPC , KC_SPC ,                    KC_RALT, KC_APP , KC_RCTL, KC_PTT ),
#endif
  [_NAV] = TEMPLATE(
      KC_GRV , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      KC_TAB , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_VOLU, KC_INS , KC_PGUP, KC_UP  , KC_PGDN, KC_BTN1, KC_BTN2, KC_BTN3, KC_DEL ,
      US_CAPS, KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_MUTE, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END , KC_RCTL,          TG_ADJ ,
      KC_LSFT, KC_F9  , KC_F10 , KC_F11 , KC_F12 , KC_VOLD, KC_END , KC_PGDN, KC_WBAK, KC_WFWD, KC_WREF,          KC_RSFT, KC_APP ,
      KC_LCTL, KC_LGUI, KC_LALT,                   NV_SPC2, NV_SPC1, NV_SPC3,                   KC_RALT, KC_RGUI, KC_RCTL, KC_PTT ),
  [_NUM] = TEMPLATE(
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      KC_GRV , KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, XXXXXXX, KC_DEL ,
      US_CAPS, KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN, KC_LBRC, KC_RBRC, KC_4,    KC_5,    KC_6,    KC_PPLS, KC_PENT,          XXXXXXX,
      KC_LSFT, KC_EQL,  KC_PLUS, KC_BSLS, KC_PIPE, KC_SCLN, XXXXXXX, KC_1,    KC_2,    KC_3,    KC_PAST,          KC_PSLS, XXXXXXX,
      KC_LCTL, KC_LGUI, KC_LALT,                   NM_SPC2, NM_SPC1, NM_SPC3,                   KC_PDOT, KC_PCMM, KC_RCTL, KC_PTT ),
 // Adjust layer is on the split-shift key; or NAV+Enter (for non-split keyboards)
  [_ADJUST] = TEMPLATE(
      MO_RST , FX(1)  , FX(2)  , FX(3)  , FX(4)  , FX(5)  , FX(6)  , FX(7)  , FX(8)  , FX(9)  , FX(10) , BR_DEC , BR_INC , XXXXXXX, MO_RST ,
      XXXXXXX, H1_INC , S1_INC , H2_INC , S2_INC , EF_INC , RGB_HUI, RGB_SAI, RGB_MOD, RGB_M_P, DFAULTS, RGB_VAD, RGB_VAI, KC_DEL ,
      XXXXXXX, H1_DEC , S1_DEC , H2_DEC , S2_DEC , EF_DEC , RGB_HUD, RGB_SAD, RGB_RMOD,RGB_M_K, RGB_M_B, RGB_M_G,          TG_ADJ ,
      TG_NKRO, LY_QWER, LY_WORK, LY_NRMN, LY_DVRK, LY_CLMK, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MAKE,          KC_CAPS, XXXXXXX,
      MO_RST , AG_NORM, AG_SWAP,                   XXXXXXX, BL_STEP, XXXXXXX,                   RGB_TOG, XXXXXXX, XXXXXXX, TG_GAME),
  // To Reset hit FN + ` + Esc
  [_RESET] = TEMPLATE(
      RESET  , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RESET  ,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX,
      RESET  , XXXXXXX, XXXXXXX,                   XXXXXXX, KC_SLEP, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX),
};

void matrix_scan_user(void) {
  #ifdef KEYBOARD_gh60
    if (IS_LAYER_ON(_GAME)) {
      gh60_wasd_leds_on();
    } else {
      gh60_wasd_leds_off();
    }
  #endif
}

void matrix_init_user(void) {
  if (!eeconfig_is_enabled()) {
    eeconfig_init();
  }
}

uint32_t default_layer_state_set_kb(uint32_t state) {
  // persist changes to default layers
  eeconfig_update_default_layer(state);
  return state;
}

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

#ifdef RGBLIGHT_ENABLE
  static uint32_t savedRgbMode;
  static uint16_t savedHue;
  static uint8_t savedSat;
  static uint8_t savedVal;

  if (keycode == KC_ESC) {
    if (record->event.pressed) {
      savedRgbMode = rgblight_get_mode();
      savedHue = rgblight_get_hue();
      savedSat = rgblight_get_sat();
      savedVal = rgblight_get_val();
      rgblight_mode(1);
      rgblight_setrgb(255, 0, 0);
    } else {
      rgblight_mode(savedRgbMode);
      rgblight_sethsv(savedHue, savedSat, savedVal);
    }
  }
#endif
// If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
  xprintf("KL: row: %u, column: %u, pressed: %u\n", record->event.key.row, record->event.key.col, record->event.pressed);
#endif //CONSOLE_ENABLE

  switch (keycode) {
    case KC_MAKE:  // Compiles the firmware, and adds the flash command based on keyboard bootloader
      if (!record->event.pressed) {
        SEND_STRING("make " QMK_KEYBOARD ":" QMK_KEYMAP

  #if   defined(BOOTLOADER_HALFKAY)
                    ":teensy"
  #elif defined(BOOTLOADER_CATERINA)
                    ":avrdude"
  #else
                    ":dfu"
  #endif
                    SS_TAP(X_ENTER));
      }
      return false;
      break;
  }
  return process_record_keymap(keycode, record);
}

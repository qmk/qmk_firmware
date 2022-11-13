#include QMK_KEYBOARD_H

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

enum LAYER_NO {
  BASE = 0,
  META,
  CONF
};

enum CUSTOM_KEYCODES {
  RGB_RST = SAFE_RANGE,
  RGB_TYPE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [BASE] = LAYOUT(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,     KC_5,    KC_6,    KC_7,   KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS,
    KC_DEL,  KC_TAB,  KC_Q,    KC_W,    KC_E,     KC_R,    KC_T,    KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,
    KC_LCTL,          KC_A,    KC_S,    KC_D,     KC_F,    KC_G,    KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_GRV,
    KC_LSFT,          KC_Z,    KC_X,    KC_C,     KC_V,    KC_B,    KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_RSFT,
                      MO(META),KC_LALT, KC_LGUI,  KC_ENT,  KC_SPC,  KC_ENT, KC_BSPC, KC_RGUI, KC_RALT, MO(META)
  ),

  [META] = LAYOUT(
    MO(CONF),KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_INS,
    _______, KC_CAPS, _______, _______, _______, _______, _______, _______, _______, _______, KC_SCRL, KC_PSCR, KC_HOME, KC_END,
    _______,          _______, _______, _______, _______, _______, _______, _______, _______, KC_PAUS, KC_PGUP, KC_UP,   KC_PGDN,
    _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT,
                      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

  [CONF] = LAYOUT(
    _______, RGB_TYPE,RGB_MOD,  RGB_VAI, RGB_HUI, RGB_HUI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    RGB_RST, RGB_TOG, RGB_RMOD, RGB_VAD, RGB_HUD, RGB_HUD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX,          XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX,          XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                      XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  )
};

bool enableLEDTypeAnime = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    case RGB_RST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
        }
      #endif
      break;
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
          if (record->event.pressed) {
            enableLEDTypeAnime = false;
            rgblight_step();
          }
      #endif
      return false;
    case RGB_TYPE:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_enable_noeeprom();
          rgblight_mode_noeeprom(1);
          enableLEDTypeAnime = !enableLEDTypeAnime;
        }
      #endif
      return false;
    default:
      break;
  }
  #ifdef RGBLIGHT_ENABLE
    if(enableLEDTypeAnime) {
      rgblight_mode_noeeprom(1);
      uint16_t hue = (rgblight_config.hue + 5) % 360;
      rgblight_sethsv_noeeprom(hue, rgblight_config.sat, rgblight_config.val);
    }
  #endif

  return true;
}

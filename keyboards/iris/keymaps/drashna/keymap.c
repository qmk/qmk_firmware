
#include QMK_KEYBOARD_H
#include "drashna.h"

#ifdef INDICATOR_LIGHTS
extern userspace_config_t userspace_config;

uint8_t last_mod;
uint8_t last_led;
uint8_t last_osm;
bool has_mods_changed = false;
#endif

#define KC_ALAP ALT_T(KC_APP)
#define KC_OSLG OSM(MOD_LGUI)
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_wrapper(
     KC_ESC,  ________________NUMBER_LEFT________________,                       ________________NUMBER_RIGHT_______________, KC_MINS,
     KC_TAB , _________________QWERTY_L1_________________,                       _________________QWERTY_R1_________________, KC_BSLS,
     KC_CCCV, _________________QWERTY_L2_________________,                       _________________QWERTY_R2_________________, KC_QUOT,
     KC_MLSF, _________________QWERTY_L3_________________, KC_ALAP,     KC_OSLG, _________________QWERTY_R3_________________, KC_MRSF,
                             LT(_LOWER,KC_GRV), KC_SPC,  KC_BSPC,         KC_DEL,  KC_ENT,  RAISE
  ),
  [_COLEMAK] = LAYOUT_wrapper(
     KC_ESC , ________________NUMBER_LEFT________________,                       ________________NUMBER_RIGHT_______________, KC_MINS,
     KC_TAB , _________________COLEMAK_L1________________,                       _________________COLEMAK_R1________________, KC_BSLS,
     KC_CCCV, _________________COLEMAK_L2________________,                       _________________COLEMAK_R2________________, KC_QUOT,
     KC_MLSF, _________________COLEMAK_L3________________, KC_ALAP,     KC_OSLG, _________________COLEMAK_R3________________, KC_MRSF,
                             LT(_LOWER,KC_GRV), KC_SPC,  KC_BSPC,         KC_DEL,  KC_ENT,  RAISE
  ),
  [_DVORAK] = LAYOUT_wrapper(
     KC_ESC,  ________________NUMBER_LEFT________________,                       ________________NUMBER_RIGHT_______________, KC_MINS,
     KC_TAB , _________________DVORAK_L1_________________,                       _________________DVORAK_R1_________________, KC_BSLS,
     KC_CCCV, _________________DVORAK_L2_________________,                       _________________DVORAK_R2_________________, KC_QUOT,
     KC_MLSF, _________________DVORAK_L3_________________, KC_ALAP,     KC_OSLG, _________________DVORAK_R3_________________, KC_MRSF,
                             LT(_LOWER,KC_GRV), KC_SPC,  KC_BSPC,         KC_DEL,  KC_ENT,  RAISE
  ),
  [_WORKMAN] = LAYOUT_wrapper(
     KC_ESC,  ________________NUMBER_LEFT________________,                       ________________NUMBER_RIGHT_______________, KC_MINS,
     KC_TAB , _________________WORKMAN_L1________________,                       _________________WORKMAN_R1________________, KC_BSLS,
     KC_CCCV, _________________WORKMAN_L2________________,                       _________________WORKMAN_R2________________, KC_QUOT,
     KC_MLSF, _________________WORKMAN_L3________________, KC_ALAP,     KC_OSLG, _________________WORKMAN_R3________________, KC_MRSF,
                             LT(_LOWER,KC_GRV), KC_SPC,  KC_BSPC,         KC_DEL,  KC_ENT,  RAISE
  ),

  [_MODS] = LAYOUT_wrapper(
     _______, _______, _______, _______, _______, _______,                       _______, _______, _______, _______, _______, _______,
     _______, _______, _______, _______, _______, _______,                       _______, _______, _______, _______, _______, _______,
     _______, _______, _______, _______, _______, _______,                       _______, _______, _______, _______, _______, _______,
     KC_LSFT, _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, KC_RSFT,
                                       _______, _______, _______,         _______, _______, _______
  ),


  [_LOWER] = LAYOUT_wrapper(
     _______, _________________FUNC_LEFT_________________,                       _________________FUNC_RIGHT________________, _______,
     _______, _______, _______, _______, _______, _______,                       _______, _______, _______, _______, _______, _______,
     _______, _______, _______, _______, _______, _______,                       _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
     _______, _______, _______, _______, _______, _______, _______,     _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______,
                                       _______, _______, _______,         _______, _______, _______
  ),

  [_RAISE] = LAYOUT_wrapper(
      _______, _________________FUNC_LEFT_________________,                      _________________FUNC_RIGHT________________, _______,
      _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______,                      _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
      _______, _______, _______, _______, _______, _______, _______,    _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______,
                                        _______, _______, _______,        _______, _______, _______
   ),

  [_ADJUST] = LAYOUT_wrapper(
      KC_MAKE, _______, _______, _______, _______, _______,                      KC_SEC1, KC_SEC2, KC_SEC3, KC_SEC4, KC_SEC5, KC_RST,
      VRSN,    RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_TOG,                      _______, _______, _______, _______, _______, EPRM,
      _______, _______, CK_TOGG, AU_ON,   AU_OFF,  AG_NORM,                      AG_SWAP, KC_QWERTY, KC_COLEMAK, KC_DVORAK, KC_WORKMAN, _______,
      TG(_MODS),RGB_SMOD,RGB_HUD,RGB_SAD, RGB_VAD, KC_RGB_T,_______,    _______, MG_NKRO, KC_MUTE, KC_VOLD, KC_VOLU, KC_MNXT, KC_MPLY,
                                        _______, _______, _______,        _______, _______, _______
   )

};


void matrix_init_keymap(void) {
#ifdef INDICATOR_LIGHTS
  last_mod = get_mods();
  last_led = host_keyboard_leds();
  last_osm =get_oneshot_mods();
#endif
}

uint32_t layer_state_set_keymap (uint32_t state) {
#ifdef INDICATOR_LIGHTS
  uint8_t modifiders = get_mods();
  uint8_t led_usb_state = host_keyboard_leds();
  uint8_t one_shot = get_oneshot_mods();


  if (modifiders & MODS_SHIFT_MASK || led_usb_state & (1<<USB_LED_CAPS_LOCK) || one_shot & MODS_SHIFT_MASK) {
    rgblight_sethsv_at(0, 255, 255, 5);
    rgblight_sethsv_at(0, 255, 255, 10);
  }
  if (modifiders & MODS_CTRL_MASK || one_shot & MODS_CTRL_MASK) {
    rgblight_sethsv_at(51, 255, 255, 6);
    rgblight_sethsv_at(51, 255, 255, 9);
  }
  if (modifiders & MODS_ALT_MASK || one_shot & MODS_ALT_MASK) {
    rgblight_sethsv_at(120, 255, 255, 7);
    rgblight_sethsv_at(120, 255, 255, 8);
  }
#endif

  return state;
}


void matrix_scan_keymap (void) {

#ifdef INDICATOR_LIGHTS
  uint8_t current_mod = get_mods();
  uint8_t current_led = host_keyboard_leds();
  uint8_t current_osm =get_oneshot_mods();

  if (last_mod == current_mod) {
    last_mod = current_mod;
    has_mods_changed = true;
  }
  if (last_led == current_led) {
    last_led = current_led;
    has_mods_changed = true;
  }
  if (last_osm == current_osm) {
    last_osm = current_osm;
    has_mods_changed = true;
  }


  if (userspace_config.rgb_layer_change && has_mods_changed && biton32(layer_state) == 0) {
    if (current_mod & MODS_SHIFT_MASK || current_led & (1<<USB_LED_CAPS_LOCK) || current_osm & MODS_SHIFT_MASK) {
      rgblight_sethsv_at(0, 255, 255, 5);
      rgblight_sethsv_at(0, 255, 255, 10);
    } else {
      rgblight_sethsv_default_helper(5);
      rgblight_sethsv_default_helper(10);
    }
    if (current_mod & MODS_CTRL_MASK || current_osm & MODS_CTRL_MASK) {
      rgblight_sethsv_at(51, 255, 255, 6);
      rgblight_sethsv_at(51, 255, 255, 9);
    } else {
      rgblight_sethsv_default_helper(6);
      rgblight_sethsv_default_helper(9);
    }
    if (current_mod & MODS_GUI_MASK || current_osm & MODS_GUI_MASK) {
      rgblight_sethsv_at(120, 255, 255, 7);
      rgblight_sethsv_at(120, 255, 255, 8);
    } else {
      rgblight_sethsv_default_helper(7);
      rgblight_sethsv_default_helper(8);

    }
  }
#endif

}

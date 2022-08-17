#include QMK_KEYBOARD_H
#include "uzu42.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif


#ifdef RGBLIGHT_ENABLE
#include <stdio.h>
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  RGBRST
};

#define KC_CTES  CTL_T(KC_ESC)
#define KC_SFSP  SFT_T(KC_SPC)
#define KC_ALBS  ALT_T(KC_BSPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
  //,---------------------------------------.                  ,---------------------------------------.
        KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                      KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,
  //|-------+-------+-------+-------+-------|                  |-------+-------+-------+-------+-------|
        KC_A,   KC_S,   KC_D,   KC_F,   KC_G,                      KC_H,   KC_J,   KC_K,   KC_L, KC_ENT,
  //|-------+-------+-------+-------+-------|                  |-------+-------+-------+-------+-------|
        KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,                      KC_N,   KC_M,KC_COMM, KC_DOT,KC_SLSH,
  //|-------+-------+-------+-------+-------+-------|  |-------+-------+-------+-------+-------+-------|
     KC_LSFT, KC_SPC,KC_LALT,KC_LGUI,  LOWER,KC_CTES,   KC_SFSP,  RAISE,KC_ALBS,KC_RCTL,KC_LGUI,XXXXXXX
  //|-------+-------+-------+-------+-------+-------|  |-------+-------+-------+-------+-------+-------|
  ),

  [_LOWER] = LAYOUT(
  //,---------------------------------------.                  ,---------------------------------------.
        KC_1,   KC_2,   KC_3,   KC_4,   KC_5,                      KC_6,   KC_7,   KC_8,   KC_9,   KC_0,
  //|-------+-------+-------+-------+-------|                  |-------+-------+-------+-------+-------|
      KC_TAB,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,                   KC_LEFT,KC_DOWN,  KC_UP,KC_RGHT, KC_ENT,
  //|-------+-------+-------+-------+-------|                  |-------+-------+-------+-------+-------|
     KC_LCTL, KC_SPC,KC_LSFT,KC_LALT, KC_DEL,                   KC_BSPC,KC_HOME, KC_END,XXXXXXX,XXXXXXX,
  //|-------+-------+-------+-------+-------+-------|  |-------+-------+-------+-------+-------+-------|
     _______,_______,_______,_______,_______,_______,   _______,_______,_______,_______,_______,_______
  //|-------+-------+-------+-------+-------+-------|  |-------+-------+-------+-------+-------+-------|
  ),

  [_RAISE] = LAYOUT(
  //,---------------------------------------.                  ,---------------------------------------.
     KC_EXLM,  KC_AT,KC_HASH, KC_DLR,KC_PERC,                   KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,
  //|-------+-------+-------+-------+-------|                  |-------+-------+-------+-------+-------|
      KC_TAB,KC_UNDS,KC_PLUS,KC_PIPE,KC_TILD,                   KC_COLN,KC_DQUO,  KC_GT,KC_LCBR,KC_RCBR,
  //|-------+-------+-------+-------+-------|                  |-------+-------+-------+-------+-------|
     KC_LCTL,KC_MINS, KC_EQL,KC_BSLS, KC_GRV,                   KC_SCLN,KC_QUOT,  KC_LT,KC_LBRC,KC_RBRC,
  //|-------+-------+-------+-------+-------+-------|  |-------+-------+-------+-------+-------+-------|
     _______,_______,_______,_______,_______,_______,   _______,_______,_______,_______,_______,_______
  //|-------+-------+-------+-------+-------+-------|  |-------+-------+-------+-------+-------+-------|
  ),

  [_ADJUST] = LAYOUT(
  //,---------------------------------------.                  ,---------------------------------------.
       KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,                     KC_F6,  KC_F7,  KC_F8,  KC_F9, KC_F10,
  //|-------+-------+-------+-------+-------|                  |-------+-------+-------+-------+-------|
      KC_F11, KC_F12,  QK_BOOT,KC_PSCR, KC_INS,                   RGB_TOG,RGB_HUI,RGB_SAI,RGB_VAI,XXXXXXX,
  //|-------+-------+-------+-------+-------|                  |-------+-------+-------+-------+-------|
     XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,                   RGB_MOD,RGB_HUD,RGB_SAD,RGB_VAD,RGBRST,
  //|-------+-------+-------+-------+-------+-------|  |-------+-------+-------+-------+-------+-------|
     _______,_______,_______,_______,_______,_______,   _______,_______,_______,_______,_______,_______
  //|-------+-------+-------+-------+-------+-------|  |-------+-------+-------+-------+-------+-------|
  )
};

int RGB_current_mode;

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
}

//SSD1306 OLED update loop, make sure to enable OLED_ENABLE=yes in rules.mk
#ifdef OLED_ENABLE

#define L_BASE 0
#define L_LOWER (1 << 1)
#define L_RAISE (1 << 2)
#define L_ADJUST (1 << 3)
#define L_ADJUST_TRI (L_ADJUST | L_RAISE | L_LOWER)

char layer_state_str[24];

const char *read_layer_state(void) {
  switch (layer_state)
  {
  case L_BASE:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Default");
    break;
  case L_RAISE:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Raise");
    break;
  case L_LOWER:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Lower");
    break;
  case L_ADJUST:
  case L_ADJUST_TRI:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Adjust");
    break;
  default:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Undef-%ld", layer_state);
  }

  return layer_state_str;
}

const char *read_logo(void) {
  static char logo[] = {
      0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
      0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
      0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
      0};
  return logo;
}

char keylog_str[24] = {};
char keylogs_str[21] = {};
int keylogs_str_idx = 0;

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', ' ', ' ', ' ', ' ', ' ', ' ',
    ' ', ';', '\'', ' ', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);

  // update keylogs
  if (keylogs_str_idx == sizeof(keylogs_str) - 1) {
    keylogs_str_idx = 0;
    for (int i = 0; i < sizeof(keylogs_str) - 1; i++) {
      keylogs_str[i] = ' ';
    }
  }

  keylogs_str[keylogs_str_idx] = name;
  keylogs_str_idx++;
}

const char *read_keylog(void) {
  return keylog_str;
}

const char *read_keylogs(void) {
  return keylogs_str;
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

bool oled_task_user(void) {
  if (is_keyboard_master()) {
    // If you want to change the display of OLED, you need to change here
    oled_write_ln(read_layer_state(), false);
    oled_write_ln(read_keylog(), false);
    oled_write_ln(read_keylogs(), false);
    //oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
    //oled_write_ln(read_host_led_state(), false);
    //oled_write_ln(read_timelog(), false);
  } else {
    oled_write(read_logo(), false);
  }
    return false;
}
#endif // OLED_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_ENABLE
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
        break;
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
  }
  return true;
}

#ifdef RGBLIGHT_ENABLE

char rbf_info_str[24];
const char *read_rgb_info(void) {

  snprintf(rbf_info_str, sizeof(rbf_info_str), "%s %2d h%3d s%3d v%3d",
    rgblight_config.enable ? "on" : "- ", rgblight_config.mode,
    rgblight_config.hue, rgblight_config.sat, rgblight_config.val);
  return rbf_info_str;
}
#endif

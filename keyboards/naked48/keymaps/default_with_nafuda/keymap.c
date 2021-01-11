#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
  _QWERTY = 0,
  _MOUSE,
  _BROWSER,
  _LOWER,
  _RAISE,
  _ADJUST,
};

enum custom_keycodes {
  MOUSE = SAFE_RANGE,
  BROWSER,
  LOWER,
  RAISE,
  ADJUST,
  RGBRST
};

// Fillers to make layering more clear
#define _____ KC_TRNS
#define XXXXX KC_NO

#define KC_CAD LCA(KC_DEL)
#define KC_APSCR LALT(KC_PSCR)

#define KC_SNUBS S(KC_NUBS)
#define KC_SNUHS S(KC_NUHS)

#define KC_RTAB LCTL(KC_TAB)
#define KC_LTAB LCTL(LSFT(KC_TAB))
#define KC_CTAB LCTL(KC_W)
#define KC_RETAB LCTL(LSFT(KC_T))

#define KC_TGMO TG(_MOUSE)
#define KC_TGBR TG(_BROWSER)
#define KC_BSAD LT(_ADJUST, KC_BSPC)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_with_nafuda(
  //,-----------------------------------------------------|                 |-----------------------------------------------------.      |--------------------------|
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,                 KC_TGMO,
  //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|      |--------+--------+--------|
       KC_ESC,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,        KC_BSAD,   KC_UP, KC_TGBR,
  //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|      |--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ENT,        KC_LEFT, KC_DOWN,KC_RIGHT,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|      |--------------------------|
                ADJUST,KC_LCTRL, KC_LALT, KC_LGUI,   LOWER,  KC_SPC,  KC_SPC,   RAISE, KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT
          //`------------------------------------------------------------------------------------------------------------'
  ),

  [_MOUSE] = LAYOUT_with_nafuda(
  //,-----------------------------------------------------|                 |-----------------------------------------------------.      |--------------------------|
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,                 KC_TGMO,
  //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|      |--------+--------+--------|
       KC_ESC,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,        KC_BTN1, KC_MS_U, KC_BTN2,
  //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|      |--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ENT,        KC_MS_L, KC_MS_D, KC_MS_R,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|      |--------------------------|
                ADJUST,KC_LCTRL, KC_LALT, KC_LGUI,   LOWER,  KC_SPC,  KC_SPC,   RAISE, KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT
          //`------------------------------------------------------------------------------------------------------------'
  ),

  [_BROWSER] = LAYOUT_with_nafuda(
  //,-----------------------------------------------------|                 |-----------------------------------------------------.      |--------------------------|
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,                 KC_CTAB,
  //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|      |--------+--------+--------|
       KC_ESC,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,       KC_RETAB, KC_WH_U, KC_TGBR,
  //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|      |--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ENT,        KC_LTAB, KC_WH_D, KC_RTAB,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|      |--------------------------|
                ADJUST,KC_LCTRL, KC_LALT, KC_LGUI,   LOWER,  KC_SPC,  KC_SPC,   RAISE, KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT
          //`------------------------------------------------------------------------------------------------------------'
  ),

  [_LOWER] = LAYOUT_with_nafuda(
  //,-----------------------------------------------------|                 |-----------------------------------------------------.      |--------------------------|
      KC_TILD, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                   KC_CIRC, KC_AMPR,  KC_ASTR,KC_LPRN, KC_RPRN,  KC_DEL,                 KC_TGMO,
  //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|      |--------+--------+--------|
       KC_DEL,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,        KC_BSAD,   KC_UP, KC_TGBR,
  //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|      |--------+--------+--------|
        _____,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,                    KC_F12,KC_SNUHS,KC_SNUBS,   _____,   _____,   _____,        KC_LEFT, KC_DOWN,KC_RIGHT,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|      |--------------------------|
                 _____,   _____,   _____,   _____,   _____,   _____,   _____,   _____, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
          //`------------------------------------------------------------------------------------------------------------'
  ),

  [_RAISE] = LAYOUT_with_nafuda(
  //,-----------------------------------------------------|                 |-----------------------------------------------------.      |--------------------------|
      KC_TILD,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_DEL,                 KC_TGMO,
  //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|      |--------+--------+--------|
       KC_DEL,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6, KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,        KC_BSAD,   KC_UP, KC_TGBR,
  //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|      |--------+--------+--------|
        _____,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,                    KC_F12, KC_NUHS, KC_NUBS,   _____,   _____,   _____,        KC_LEFT, KC_DOWN,KC_RIGHT,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|      |--------------------------|
                 _____,   _____,   _____,   _____,   _____,   _____,   _____,   _____,   _____,   _____,   _____,   _____
          //`------------------------------------------------------------------------------------------------------------'
  ),

  [_ADJUST] = LAYOUT_with_nafuda( /* Base */
  //,-----------------------------------------------------|                 |-----------------------------------------------------.      |--------------------------|
        _____,   RESET,   XXXXX,   XXXXX,   XXXXX,   XXXXX,                     XXXXX,   XXXXX,   XXXXX,   XXXXX,   XXXXX,   _____,                 RGB_VAD,
  //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|      |--------+--------+--------|
        _____,   XXXXX,   XXXXX,   XXXXX,   XXXXX,   XXXXX,                   RGB_TOG, RGB_MOD,   XXXXX,LCA(KC_DEL),LALT(KC_PSCR),KC_PSCR,  ADJUST, RGB_SAD, RGB_VAI,
  //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|      |--------+--------+--------|
        _____,   _____,   _____,   _____,   _____,   _____,                   RGB_VAD, RGB_VAI, RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI,        RGB_MOD, RGB_TOG, RGB_SAI,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|      |--------------------------|
                 _____,   _____,   _____,   _____,   _____,   _____,   _____,   _____,   _____,   _____,   _____,   _____
          //`------------------------------------------------------------------------------------------------------------'
  )
};

static inline void update_change_layer(bool pressed, uint8_t layer1, uint8_t layer2, uint8_t layer3) {

  pressed ? layer_on(layer1) : layer_off(layer1);
  IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2) ? layer_on(layer3) : layer_off(layer3);
}

int RGB_current_mode;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  bool result = false;
  switch (keycode) {
    case LOWER:
      update_change_layer(record->event.pressed, _LOWER, _RAISE, _ADJUST);
      break;
    case RAISE:
      update_change_layer(record->event.pressed, _RAISE, _LOWER, _ADJUST);
        break;
    #ifdef RGBLIGHT_ENABLE
      case RGB_MOD:
          if (record->event.pressed) {
            rgblight_mode(RGB_current_mode);
            rgblight_step();
            RGB_current_mode = rgblight_config.mode;
          }
        break;
      case RGBRST:
          if (record->event.pressed) {
            eeconfig_update_rgblight_default();
            rgblight_enable();
            RGB_current_mode = rgblight_config.mode;
          }
        break;
    #endif
    default:
      result = true;
      break;
  }

  return result;
}

void matrix_init_user(void) {
  #ifdef RGBLIGHT_ENABLE
    RGB_current_mode = rgblight_config.mode;
  #endif
}

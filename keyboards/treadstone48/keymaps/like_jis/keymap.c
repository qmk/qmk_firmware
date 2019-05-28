#include QMK_KEYBOARD_H
#include "keymap_jp.h"
#include "../common/oled_helper.h"

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
  _BASE = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
};

enum custom_keycodes {
  LOWER = SAFE_RANGE,
  RAISE,
  ADJUST,
  KANJI,
  RGBRST
};

enum tapdances{
  TD_SCCL = 0,
  TD_SLRO,
};

// Layer Mode aliases
#define _____ KC_TRNS
#define XXXXX KC_NO

#define KC_TBSF  LSFT_T(KC_TAB)
// #define KC_SPSF  LSFT_T(KC_SPC)
#define KC_ALAP  LALT_T(KC_APP)
#define KC_JEQL  LSFT(KC_MINS)

#define KC_SCCL  TD(TD_SCCL)
#define KC_SLRO  TD(TD_SLRO)

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_SCCL] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_QUOT),
  [TD_SLRO] = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, KC_RO),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_base( \
  //,--------------------------------------------------------------------------------------------------------------------.
       KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,          KC_MINS,\
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+-----------------|
      KC_TBSF,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L, KC_SCCL,           KC_ENT,\
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLRO,   KC_UP,         \
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------+--------|
     KC_LCTRL, KC_LALT, KC_LGUI,   LOWER,          KC_BSPC,           KC_SPC,   RAISE, KC_ALAP, KC_LEFT, KC_DOWN, KC_RGHT,\
  //`-------------------------------------------------------------------------------------------------------------------'
       KC_DEL \
  // ExtraKey: Split backspace key or it is below the enter key.
  ),

  [_LOWER] = LAYOUT_base( \
  //,--------------------------------------------------------------------------------------------------------------------.
        _____,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5, KC_MINS,  KC_EQL, KC_JYEN, KC_LBRC, KC_RBRC,           KC_DEL,\
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+-----------------|
        _____,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,   XXXXX,   XXXXX, KC_SCLN, KC_QUOT, KC_BSLS,            _____,\
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------+--------|
        _____,  KC_F11,  KC_F12,   XXXXX,   KANJI,  KC_ENT,   XXXXX, KC_COMM,  KC_DOT, KC_SLSH,   KC_RO, KC_PGUP,         \
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------+--------|
        _____,   _____,   _____,   _____,           KC_DEL,            _____,   _____,   XXXXX, KC_HOME, KC_PGDN,  KC_END,\
  //`-------------------------------------------------------------------------------------------------------------------'
      XXXXX \
  // ExtraKey: Split backspace key or it is below the enter key.
  ),

  [_RAISE] = LAYOUT_base( \
  //,--------------------------------------------------------------------------------------------------------------------.
        _____,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,            XXXXX,\
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+-----------------|
        _____,   XXXXX,   XXXXX,   XXXXX,   XXXXX,   XXXXX,   XXXXX,    KC_4,    KC_5,    KC_6, KC_QUOT,            _____,\
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------+--------|
        _____,   XXXXX,   XXXXX,   XXXXX,   XXXXX,   XXXXX,   XXXXX,    KC_1,    KC_2,    KC_3,   KC_RO,   XXXXX,         \
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------+--------|
        _____,   _____,   _____,   _____,            _____,            _____,   _____,    KC_0,  KC_DOT, KC_COMM, KC_SLSH,\
  //`-------------------------------------------------------------------------------------------------------------------'
      XXXXX \
  // ExtraKey: Split backspace key or it is below the enter key.
  ),

  [_ADJUST] = LAYOUT_base( \
  //,--------------------------------------------------------------------------------------------------------------------.
        XXXXX,   RESET,  RGBRST, AG_NORM, AG_SWAP,   XXXXX,   XXXXX, KC_WH_L, KC_WH_U, KC_HOME, KC_PGUP,            XXXXX,\
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+-----------------|
        XXXXX, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI,   XXXXX,   XXXXX, KC_WH_R, KC_WH_D,  KC_END, KC_PGDN,            XXXXX,\
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------+--------|
        _____, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD,   XXXXX,   XXXXX,   XXXXX, KC_BTN1, KC_BTN2,   XXXXX, KC_MS_U,         \
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------+--------|
        _____,   _____,   _____,   _____,            XXXXX,            XXXXX,   _____,   XXXXX, KC_MS_L, KC_MS_D, KC_MS_R,\
  //`-------------------------------------------------------------------------------------------------------------------'
      XXXXX \
  // ExtraKey: Split backspace key or it is below the enter key.
  )
};

#define L_BASE _BASE
#define L_LOWER (1<<_LOWER)
#define L_RAISE (1<<_RAISE)
#define L_ADJUST (1<<_ADJUST)
#define L_ADJUST_TRI (L_ADJUST|L_RAISE|L_LOWER)

#ifdef SSD1306OLED
typedef struct {
  uint8_t state;
  char name[8];
}LAYER_DISPLAY_NAME;

#define LAYER_DISPLAY_MAX 5
const LAYER_DISPLAY_NAME layer_display_name[LAYER_DISPLAY_MAX] = {
  {L_BASE, "Base"},
  {L_BASE + 1, "Base"},
  {L_LOWER, "Lower"},
  {L_RAISE, "Raise"},
  {L_ADJUST_TRI, "Adjust"}
};

static inline const char* get_leyer_status(void) {

  for (uint8_t i = 0; i < LAYER_DISPLAY_MAX; ++i) {
    if (layer_state == 0 && layer_display_name[i].state == default_layer_state) {

      return layer_display_name[i].name;
    } else if (layer_state != 0 && layer_display_name[i].state == layer_state) {

      return layer_display_name[i].name;
    }
  }

  return "?";
}

static char layer_status_buf[24] = "Layer state ready.\n";
static inline void update_keymap_status(void) {

  snprintf(layer_status_buf, sizeof(layer_status_buf) - 1, "OS:%s Layer:%s\n",
    keymap_config.swap_lalt_lgui? "win" : "mac", get_leyer_status());
}

static inline void render_keymap_status(struct CharacterMatrix *matrix) {

  matrix_write(matrix, layer_status_buf);
}

#define UPDATE_KEYMAP_STATUS() update_keymap_status()
#define RENDER_KEYMAP_STATUS(a) render_keymap_status(a)

#else

#define UPDATE_KEYMAP_STATUS()
#define RENDER_KEYMAP_STATUS(a)

#endif

static inline void update_change_layer(bool pressed, uint8_t layer1, uint8_t layer2, uint8_t layer3) {

  pressed ? layer_on(layer1) : layer_off(layer1);
  IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2) ? layer_on(layer3) : layer_off(layer3);
}

int RGB_current_mode;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  UPDATE_KEY_STATUS(keycode, record);

  bool result = false;
  switch (keycode) {
    case LOWER:
      update_change_layer(record->event.pressed, _LOWER, _RAISE, _ADJUST);
      break;
    case RAISE:
      update_change_layer(record->event.pressed, _RAISE, _LOWER, _ADJUST);
        break;
    case KANJI:
      if (record->event.pressed) {
        if (keymap_config.swap_lalt_lgui == false) {
          register_code(KC_LANG2);
        } else {
          SEND_STRING(SS_LALT("`"));
        }
      } else {
        unregister_code(KC_LANG2);
      }
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

  UPDATE_KEYMAP_STATUS();
  return result;
}

void matrix_init_user(void) {
  #ifdef RGBLIGHT_ENABLE
    RGB_current_mode = rgblight_config.mode;
  #endif
  //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
  #ifdef SSD1306OLED
    iota_gfx_init(!has_usb()); // turns on the display
  #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

void matrix_scan_user(void) {
  iota_gfx_task();  // this is what updates the display continuously
}

static inline void matrix_update(struct CharacterMatrix *dest,
                          const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

static inline void render_status(struct CharacterMatrix *matrix) {

  UPDATE_LED_STATUS();
  RENDER_LED_STATUS(matrix);
  RENDER_KEYMAP_STATUS(matrix);
  UPDATE_LOCK_STATUS();
  RENDER_LOCK_STATUS(matrix);
  RENDER_KEY_STATUS(matrix);
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;

  #if DEBUG_TO_SCREEN
    if (debug_enable) {
      return;
    }
  #endif

  matrix_clear(&matrix);
  if (is_master) {
    render_status(&matrix);
  }

  matrix_update(&display, &matrix);
}

#endif

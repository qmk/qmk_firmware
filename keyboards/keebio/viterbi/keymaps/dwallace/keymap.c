#include "viterbi.h"
#include "action_layer.h"
#include "eeconfig.h"
#ifdef RGBLIGHT_ENABLE
#include "rgblight.h"
#endif

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _FN 1

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  STK_SHIFT,
  STK_CTRL,
  STK_ALT,
  STK_GUI,
  STK_META,
  STK_CLEAR,
  RGB_LEVEL_UP,
  RGB_LEVEL_DOWN,
};

#define KC_ KC_TRNS

#define KC_SWIN LGUI(KC_TILD)   // Switch between windows
#define KC_SAPP LGUI(KC_TAB)    // Switch between applications
#define KC_FN1 MO(_FN)
#define KC_LCAG LCAG(KC_NO)
#define KC_RTOG RGB_TOG
#define KC_RGUP RGB_LEVEL_UP
#define KC_RGDN RGB_LEVEL_DOWN
#define KC_RST RESET
#define KC_SSFT STK_SHIFT
#define KC_SCTL STK_CTRL
#define KC_SALT STK_ALT
#define KC_SGUI STK_GUI
#define KC_SMTA STK_META
#define KC_SCLR STK_CLEAR

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_kc(
  //,----+----+----+----+----+----+----.    ,----+----+----+----+----+----+----.
     GRV , 1  , 2  , 3  , 4  , 5  , 6  ,      7  , 8  , 9  , 0  ,MINS,EQL ,BSPC,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     TAB , Q  , W  , E  , R  , T  ,LBRC,      Y  , U  , I  , O  , P  ,BSLS,PGUP,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     ESC , A  , S  , D  , F  , G  ,RBRC,      H  , J  , K  , L  ,SCLN,QUOT,ENT ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     SSFT, Z  , X  , C  , V  , B  ,SWIN,      N  , M  ,COMM,DOT , UP ,SLSH,RSFT,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     SCTL,SMTA,SALT,SGUI,SPC ,SCLR,SAPP,     FN1 ,SPC ,RGUI,LEFT,DOWN,RGHT,PGDN
  //`----+----+----+----+----+----+----'    `----+----+----+----+----+----+----'
  ),

  [_FN] = LAYOUT_kc(
  //,----+----+----+----+----+----+----.    ,----+----+----+----+----+----+----.
         , F1 , F2 , F3 , F4 , F5 , F6 ,      F7 , F8 , F9 ,F10 ,F11 ,F12 ,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    ,    ,    ,RST ,    ,    ,         ,    ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,     RTOG,    ,RGDN,RGUP,    ,    ,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,         ,MUTE,VOLD,VOLU,    ,    ,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,    ,
  //`----+----+----+----+----+----+----'    `----+----+----+----+----+----+----'
  )

};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool modifier_already_applied = false;
uint8_t physically_held_modifiers = 0;
uint8_t last_mods = 0xFF;
uint8_t rgb_dimming = 0;
#define SET_LED_RGB(val, led_num) setrgb(((val >> 16) & 0xFF) >> rgb_dimming, ((val >> 8) & 0xFF) >> rgb_dimming, (val & 0xFF) >> rgb_dimming, (LED_TYPE *)&led[led_num])

void update_underglow_level(void) {
  if (get_mods() == last_mods)
    return;

  last_mods = get_mods();

  if (get_mods() == 0) {
    uint8_t level = 0x10 >> rgb_dimming;
    rgblight_setrgb(level, level, level);
    return;
  }

  uint32_t mod_colors[4] = {0};
  uint8_t mod_count = 0;
  rgblight_setrgb(0x00, 0x00, 0x00);

  if (get_mods() & MOD_BIT(KC_LSFT))
    mod_colors[mod_count++] = 0xFF0000;
  if (get_mods() & MOD_BIT(KC_LCTL))
    mod_colors[mod_count++] = 0x00FF00;
  if (get_mods() & MOD_BIT(KC_LALT))
    mod_colors[mod_count++] = 0x0000FF;
  if (get_mods() & MOD_BIT(KC_LGUI))
    mod_colors[mod_count++] = 0xFFFF00;

  uint8_t led_num = 0;
  for (int m = 0; m < mod_count; m++) {
    for (; led_num < RGBLED_NUM*(m+1)/mod_count; led_num++) {
      SET_LED_RGB(mod_colors[m], led_num);
    }
  }
  rgblight_set();
}

void add_sticky_modifier(uint16_t keycode) {
  add_mods(MOD_BIT(keycode));
  register_code(keycode);
  modifier_already_applied = false;
}

void clear_sticky_modifiers(void) {
  unregister_code(KC_LSFT);
  unregister_code(KC_LCTL);
  unregister_code(KC_LALT);
  unregister_code(KC_LGUI);
  update_underglow_level();
}

void handle_sticky_modifier_event(uint16_t keycode, bool pressed) {
  if (pressed) {
    add_sticky_modifier(keycode);
    physically_held_modifiers |= MOD_BIT(keycode);
  } else {
    del_mods(MOD_BIT(keycode));
    physically_held_modifiers &= ~MOD_BIT(keycode);
    if (modifier_already_applied) {
      clear_sticky_modifiers();
    } else {
      add_sticky_modifier(keycode);
    }
  }
  update_underglow_level();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_qwerty, false, 0);
        #endif
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case STK_SHIFT:
      handle_sticky_modifier_event(KC_LSFT, record->event.pressed);
      return false;
      break;
    case STK_CTRL:
      handle_sticky_modifier_event(KC_LCTL, record->event.pressed);
      return false;
      break;
    case STK_ALT:
      handle_sticky_modifier_event(KC_LALT, record->event.pressed);
      return false;
      break;
    case STK_GUI:
      handle_sticky_modifier_event(KC_LGUI, record->event.pressed);
      return false;
      break;
    case STK_META:
      handle_sticky_modifier_event(KC_LCTL, record->event.pressed);
      handle_sticky_modifier_event(KC_LALT, record->event.pressed);
      handle_sticky_modifier_event(KC_LGUI, record->event.pressed);
      return false;
      break;
    case STK_CLEAR:
      if (record->event.pressed) {
        clear_sticky_modifiers();
      }
      return false;
      break;
    case RGB_LEVEL_DOWN:
      if (record->event.pressed && rgb_dimming < 8) {
        rgb_dimming++;
      }
      return false;
      break;
    case RGB_LEVEL_UP:
      if (record->event.pressed && rgb_dimming > 0) {
        rgb_dimming--;
      }
      return false;
      break;
  }
  if (!record->event.pressed && IS_KEY(keycode)) {
    modifier_already_applied = true;
    if (physically_held_modifiers == 0)
      clear_sticky_modifiers();
  }
  return true;
}

void matrix_init_user(void) {
  #ifdef RGBLIGHT_ENABLE
  rgblight_enable();
  #endif //RGBLIGHT_ENABLE
}

void matrix_scan_user(void) {
  #ifdef RGBLIGHT_ENABLE
  update_underglow_level();
  #endif //RGBLIGHT_ENABLE
}

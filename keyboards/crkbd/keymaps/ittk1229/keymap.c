#include QMK_KEYBOARD_H
#include "keymap_jp.h"

#ifdef SSD1306OLED
  #include "ssd1306.h"
  #include <string.h>
#endif

#ifdef RGBLIGHT_ENABLE
  //Following line allows macro to read current RGB settings
  extern rgblight_config_t rgblight_config;
#endif

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _EUCALYN 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3
#define _QWERTY 4
#define _MINECRAFT 5

#define W_PSCR LGUI(S(KC_S))
#define CAPTURE LGUI(KC_PSCR)
#define NV_REC LALT(KC_F9)


#define LSFT_ENT LSFT(KC_ENT)
#define LCTL_SPC LCTL(KC_SPC)

#define TO_MC TO(_MINECRAFT)
#define TO_EU TO(_EUCALYN)
#define TO_QW TO(_QWERTY)



enum custom_keycodes {
  EUCALYN = SAFE_RANGE,
  CTL_SPC,
  SFT_ENT,
  ESC_MHEN,
  LOWER,
  RAISE,
  ADJUST,
  QWERTY,
  MINECRAFT,
  BACKLIT,
  RGBRST
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_EUCALYN] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     ESC_MHEN,    KC_Q,   KC_W,  JP_COMM,  JP_DOT, JP_SCLN,                         KC_M,    KC_R,    KC_D,    KC_Y,    KC_P, JP_MINS,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_TAB,    KC_A,    KC_O,    KC_E,    KC_I,    KC_U,                         KC_G,    KC_T,    KC_N,    KC_S,    KC_B, JP_QUOT,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LALT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_F,                         KC_H,    KC_J,    KC_K,    KC_L, JP_SLSH,  KC_DEL,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   LOWER, CTL_SPC,    SFT_ENT,   RAISE, KC_BSPC\
                                      //`--------------------------'  `--------------------------'
  ),

  [_LOWER] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        KC_NO,   KC_P1,   KC_P2,   KC_P3,   KC_P4,   KC_P5,                        KC_P6,   KC_P7,   KC_P8,   KC_P9,   KC_P0,   KC_NO,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                      KC_HOME, KC_PGDN, KC_PGUP,  KC_END,   KC_NO,   KC_NO,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LALT,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                      KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,   KC_NO,   KC_NO,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   LOWER, KC_LCTL,    KC_LSFT,   RAISE,LSFT_ENT\
                                      //`--------------------------'  `--------------------------'
    ),

  [_RAISE] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       JP_GRV, JP_TILD,   KC_NO,   JP_LT,   JP_GT, JP_COLN,                        KC_NO, JP_LPRN, JP_RPRN,   KC_NO,   KC_NO, JP_UNDS,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_NO, JP_AMPR,   JP_AT, JP_PLUS,  JP_EQL,   KC_NO,                      JP_CIRC, JP_LCBR, JP_RCBR,  JP_DLR, JP_EXLM, JP_DQUO,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LALT, JP_PIPE, JP_HASH, JP_ASTR, JP_PERC,   KC_NO,                        KC_NO, JP_LBRC, JP_RBRC, JP_BSLS, JP_QUES,   KC_NO,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   LOWER, KC_LCTL,    KC_LSFT,   RAISE,   KC_NO\
                                      //`--------------------------'  `--------------------------'
  ),

  [_ADJUST] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        KC_NO,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,   KC_NO,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_NO,  KC_F11,  KC_F12,   KC_NO,   KC_NO,   KC_NO,                        KC_NO,   KC_NO,   KC_NO,  W_PSCR,  NV_REC,   TO_QW,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LALT,   KC_NO,   KC_NO, JP_CAPS,   KC_NO,   KC_NO,                        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   TO_MC,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   LOWER, KC_LCTL,     KC_LSFT,   RAISE,   KC_NO\
                                      //`--------------------------'  `--------------------------'
  ),

  [_QWERTY] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     ESC_MHEN,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, JP_MINS,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_TAB,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, JP_SCLN, JP_QUOT,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LALT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, JP_COMM,  JP_DOT, JP_SLSH,   TO_EU,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   LOWER, CTL_SPC,    SFT_ENT,   RAISE, KC_BSPC\
                                      //`--------------------------'  `--------------------------'
  ),


  [_MINECRAFT] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,   KC_NO,    KC_Q,    KC_W,    KC_E,    KC_T,                        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_TAB,   KC_NO,    KC_A,    KC_S,    KC_D,    KC_F,                        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      JP_SLSH,   KC_F1,   KC_F5,  KC_F11,   KC_NO,  CAPTURE,                        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   TO_EU,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LCTL, KC_LSFT,  KC_SPC,      KC_NO,   KC_NO,   KC_NO\
                                      //`--------------------------'  `--------------------------'
  ),

};

static bool lower_pressed = false;
static bool raise_pressed = false;

static bool ctl_spc_pressed = false;
static bool sft_ent_pressed = false;
static uint16_t  ctl_spc_pressed_time = 0;
static uint16_t sft_ent_pressed_time = 0;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

void matrix_init_user(void) {
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
      iota_gfx_init();   // turns on the display
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_scan_user(void) {
  iota_gfx_task();
  if (ctl_spc_pressed && timer_elapsed(ctl_spc_pressed_time) > TAPPING_TERM) {
    register_code(KC_LCTL);
    ctl_spc_pressed = false;
  }
  if (sft_ent_pressed && timer_elapsed(sft_ent_pressed_time) > TAPPING_TERM) {
    register_code(KC_LSFT);
    sft_ent_pressed = false;
  }
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_keyboard_master()) {
    // If you want to change the display of OLED, you need to change here
    matrix_write(matrix, read_layer_state());
    matrix_write(matrix, read_keylog());
    //matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write(matrix, read_logo());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}

#endif//SSD1306OLED

static void user_mt(keyrecord_t *record, uint16_t modcode, uint16_t keycode, bool *modifier_pressed, uint16_t *modifier_pressed_time, bool tapping_term_disable) {
  if (record->event.pressed) {
    *modifier_pressed = true;
    *modifier_pressed_time = record->event.time;
  } else {
    if (!*modifier_pressed) unregister_code(modcode);
    if (*modifier_pressed && (tapping_term_disable || (timer_elapsed(*modifier_pressed_time) < TAPPING_TERM))) {
      register_code(keycode);
      unregister_code(keycode);
    }
    *modifier_pressed = false;
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    #ifdef SSD1306OLED
      set_keylog(keycode, record);
    #endif
    // set_timelog();
    if (keycode != CTL_SPC) {
      if (ctl_spc_pressed) {
        register_code(KC_LCTL);
      }
      ctl_spc_pressed = false;
    }
    if (keycode != SFT_ENT) {
      if (sft_ent_pressed) {
        register_code(KC_LSFT);
      }
      sft_ent_pressed = false;
    }
  }

  switch (keycode) {
    case CTL_SPC:
      user_mt(record, KC_LCTL,  KC_SPC, &ctl_spc_pressed, &ctl_spc_pressed_time, true);
      return false;
    case SFT_ENT:
      user_mt(record, KC_LSFT, KC_ENT, &sft_ent_pressed, &sft_ent_pressed_time, true);
      return false;
    case ESC_MHEN:
      register_code(KC_ESC);
      register_code(KC_MHEN);
      return false;
    case EUCALYN:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_EUCALYN);
      }
      return false;
    case LOWER:
      if (record->event.pressed) {
        lower_pressed = true;

        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);

        if (lower_pressed) {
          register_code(KC_MHEN);
          unregister_code(KC_MHEN);
        }
        lower_pressed = false;
      }
      return false;
    case RAISE:
      if (record->event.pressed) {
        raise_pressed = true;

        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);

        if (raise_pressed) {
          register_code(KC_HENK);
          unregister_code(KC_HENK);
        }
        raise_pressed = false;
      }
      return false;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
    default:
      if (record->event.pressed) {
        lower_pressed = false;
        raise_pressed = false;
        if (ctl_spc_pressed) {
          register_code(KC_LCTL);
        }
        if (sft_ent_pressed) {
          register_code(KC_LSFT);
        }
        ctl_spc_pressed = false;
        sft_ent_pressed = false;
      }
      break;
  }
  return true;
}

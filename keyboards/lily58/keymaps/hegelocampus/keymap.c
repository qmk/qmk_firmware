#include QMK_KEYBOARD_H

#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif


extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

#define _DVORAK 0
#define _GAME 1
#define _LOWER 2
#define _RAISE 3
#define _ADJUST 4
#define _FN 5

enum custom_keycodes {
  DVORAK = SAFE_RANGE,
  GAME,
  LOWER,
  RAISE,
  FN,
  ADJUST
};

#define LSPA  LT(_LOWER, KC_SPC)
#define RSPA  LT(_FN, KC_SPC)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* DVORAK
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | `    |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  \   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TAB  |   '  |   ,  |   .  |   p  |   y  |                    |   f  |   g  |   c  |   r  |   l  | BCSPC|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | ESC  |   a  |   o  |   e  |   u  |   i  |-------.    ,-------|   d  |   h  |   t  |   n  |   s  | ENT  |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |SFT+( |   /  |   q  |   j  |   k  |   x  |-------|    |-------|   b  |   m  |   w  |   v  |   z  | SFT+)|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LALT | LGUI |LOWER | /Space  /       \Enter \  |RAISE |LCTRL | LEAD |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_DVORAK] = LAYOUT( \
  KC_GRV,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,     KC_8,    KC_9,    KC_0,    KC_BSLS,\
  KC_TAB,   KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,                     KC_F,    KC_G,     KC_C,    KC_R,    KC_L,    KC_BSPC,\
  KC_ESC,   KC_A,    KC_O,    KC_E,    KC_U,    KC_I,                     KC_D,    KC_H,     KC_T,    KC_N,    KC_S,    KC_ENT, \
  KC_LSPO,  KC_SLSH, KC_Q,    KC_J,    KC_K,    KC_X,  KC_LBRC,  KC_RBRC, KC_B,    KC_M,     KC_W,    KC_V,    KC_Z,    KC_RSPC,\
                              KC_LALT, KC_LGUI, LOWER, KC_SPC,     RSPA,  RAISE,   KC_LCTRL, KC_LALT \
),

[_GAME] = LAYOUT( \
  XXXXXXX, KC_1,    KC_2,    KC_3,    KC_4,     KC_5,                     KC_6,    KC_7,     KC_8,    KC_9,    KC_0,    KC_BSLS,\
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,     KC_T,                     KC_F,    KC_G,     KC_C,    KC_R,    KC_L,    KC_BSPC,\
  XXXXXXX, KC_A,    KC_S,    KC_D,    KC_F,     KC_G,                     KC_H,    KC_J,     KC_K,    KC_L,    KC_QUOT, KC_ENT, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,     KC_B,  KC_LCTRL,  KC_ESC, KC_N,    KC_M,     KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC,\
                            KC_LALT, KC_LCTRL, LOWER, KC_SPC,    RSPA,   RAISE,   KC_LCTRL, KC_LEAD \
),

/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  | F10  | F11  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  |   !  |   @  |   #  |   $  |   %  |-------.    ,-------|   ^  |   &  |   *  |   (  |   )  |   -  |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |   _  |   +  |   {  |   }  |   |  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_LOWER] = LAYOUT( \
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,    KC_F7,   KC_F8,   KC_F9,   KC_F10,   _______,\
  _______, KC_F11,  KC_F12,  KC_LCBR, KC_RCBR, _______,                   KC_COLON, KC_UNDS, KC_PLUS, KC_PIPE, KC_COLON, KC_DEL,\
  _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC,  KC_AMPR, KC_ASTR, KC_LBRC, KC_RBRC,  _______,\
  _______, _______, _______, _______, _______, _______, KC_PGDN, KC_PGUP, KC_TILD,  KC_UNDS, _______, KC_LCBR, KC_RCBR,  KC_PIPE,\
                             _______, _______, _______, _______, _______, _______,  _______, _______\
),

/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |-------.    ,-------|      | Left | Down |  Up  |Right |      |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |  F7  |  F8  |  F9  | F10  | F11  | F12  |-------|    |-------|   +  |   -  |   =  |   [  |   ]  |   \  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_RAISE] = LAYOUT( \
  _______, _______, _______, _______, _______, _______,                     _______, _______, _______,  _______, _______, _______, \
  KC_GRV,  _______, _______, KC_LBRC, KC_RBRC, _______,                     KC_SCLN, KC_MINS,  KC_EQL , KC_BSLS, KC_SCLN, _______, \
  KC_CAPS, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                        KC_6,    KC_7,    KC_8,     KC_9,    KC_0,    _______, \
  _______, _______, _______, _______, _______, _______,  _______, _______,  KC_PGDN, KC_PGUP, KC_GRAVE, KC_LBRC, KC_RBRC, KC_BSLS, \
                             _______, _______, _______,  _______, _______,  _______, _______, _______ \
),

[_FN] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                    _______, _______, _______, _______,  _______, _______, \
  _______, _______, _______, _______, _______, _______,                    KC_SCLN, KC_TILD, KC_SLSH, KC_BSLS,  _______, _______, \
  _______, _______, _______, _______, _______, _______,                    KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, _______, _______, \
  _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______,  _______, _______, \
                             _______, _______, _______,  _______, _______, _______, _______, _______ \
),

/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |RGB ON| HUE+ | SAT+ | VAL+ |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      | MODE | HUE- | SAT- | VAL- |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [_ADJUST] = LAYOUT( \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RESET,   \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, DVORAK,  XXXXXXX, GAME,                      XXXXXXX, XXXXXXX, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD,\
                             _______, _______, _______, _______, _______, _______, _______, _______ \
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

//SSD1306 OLED update loop, make sure to enable OLED_DRIVER_ENABLE=yes in rules.mk
#ifdef OLED_DRIVER_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void oled_task_user(void) {
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
}
#endif // OLED_DRIVER_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  switch (keycode) {
    case DVORAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DVORAK);
      }
      return false;
      break;
    case GAME:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_GAME);
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
    case FN:
      if (record->event.pressed) {
        layer_on(_FN);
        //update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_FN);
        //update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
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
  }
  return true;
}


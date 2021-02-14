#include QMK_KEYBOARD_H

#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif



#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

#define _COLE 0
#define _QWRT 1
#define _BLUE 2
#define _RED 3
#define _FC 4
#define _ADJUST 5

enum custom_keycodes {
  COLE = SAFE_RANGE,
  QWRT,
  BLUE,
  RED,
  FC,
  ADJUST
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* COLEMAK **********************************************************************************************************************
 * .-----------------------------------------.                            .-----------------------------------------.
 * | ~Esc |   1  |   2  |   3  |   4  |   5  |                            |   6  |   7  |   8  |   9  |   0  | BkSp |
 * |------+------+------+------+------+------|                            |------+------+------+------+------+------|
 * |  Tab |   Q  |   W  |   F  |   P  |   G  |                            |   J  |   L  |   U  |   Y  |   ;  |  \   |
 * |------+------+------+------+------+------|                            |------+------+------+------+------+------|
 * | FnCps|   A  |   R  |   S  |   T  |   D  |-------.            .-------|   H  |   N  |   E  |   I  |   O  | Entr |
 * |------+------+------+------+--^^--+------|   [   |            |   ]   |------+--^^--+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |-------|            |-------|   K  |   M  |   ,  |   .  |   /  |Shift |
 * '-----------------------------------------/ Fn   /              \  Fn  \-----------------------------------------'
 *                   | LCtl | LGUI | LAlt | /Space /                \Space \  | RAlt | RGUI | RCtl |
 *                   |      |      |      |/      /                  \      \ |      |      |      |
 *                   '---------------------------'                    '------''--------------------'
 */
 [_COLE] = LAYOUT( \
  KC_GESC,   KC_1,    KC_2,  KC_3,  KC_4,  KC_5,                            KC_6,  KC_7,  KC_8,   KC_9,   KC_0,    KC_BSPC,  \
  KC_TAB,    KC_Q,    KC_W,  KC_F,  KC_P,  KC_G,                            KC_J,  KC_L,  KC_U,   KC_Y,   KC_SCLN, KC_BSLS,  \
  LT(FC,KC_CAPS),KC_A,KC_R,  KC_S,  KC_T,  KC_D,                            KC_H,  KC_N,  KC_E,   KC_I,   KC_O,    KC_ENT,   \
  KC_LSFT,   KC_Z,    KC_X,  KC_C,  KC_V,  KC_B,  KC_LBRC,       KC_RBRC,   KC_K,  KC_M,  KC_COMM,KC_DOT, KC_SLSH, KC_RSFT,  \
                      KC_LCTRL,KC_LGUI,KC_LALT,LT(BLUE, KC_SPC), LT(RED, KC_SPC),KC_RALT,KC_RGUI, KC_RCTRL \
),

/* QWERTY **********************************************************************************************************************
 * .-----------------------------------------.                           .-----------------------------------------.
 * | ~Esc |   1  |   2  |   3  |   4  |   5  |                           |   6  |   7  |   8  |   9  |   0  | BkSp |
 * |------+------+------+------+------+------|                           |------+------+------+------+------+------|
 * |  Tab |   Q  |   W  |   E  |   R  |   T  |                           |   Y  |   U  |   I  |   O  |   P  |  \   |
 * |------+------+------+------+------+------|                           |------+------+------+------+------+------|
 * | FnCps|   A  |   S  |   D  |   F  |   G  |-------.           .-------|   H  |   J  |   K  |   L  |   ;  | Entr |
 * |------+------+------+------+--^^--+------|   [   |           |   ]   |------+--^^--+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |-------|           |-------|   N  |   M  |   ,  |   .  |   /  |Shift |
 * '-----------------------------------------/ Fn   /             \  Fn  \-----------------------------------------'
 *                   | LCtl | LGUI | LAlt | /Space /               \Space \  | RAlt | RGUI | RCtl |
 *                   |      |      |      |/      /                 \      \ |      |      |      |
 *                   '---------------------------'                   '------''--------------------'
 */
 [_QWRT] = LAYOUT( \
  KC_GESC,  KC_1,     KC_2,  KC_3,  KC_4,  KC_5,                               KC_6,  KC_7,  KC_8,   KC_9,   KC_0,    KC_BSPC, \
  KC_TAB,   KC_Q,     KC_W,  KC_E,  KC_R,  KC_T,                               KC_Y,  KC_U,  KC_I,   KC_O,   KC_P,    KC_BSLS, \
  LT(FC,KC_CAPS),KC_A,KC_S,  KC_D,  KC_F,  KC_G,                               KC_H,  KC_J,  KC_K,   KC_L,   KC_SCLN, KC_ENT,  \
  KC_LSFT,  KC_Z,     KC_X,  KC_C,  KC_V,  KC_B,   KC_LBRC,         KC_RBRC,   KC_N,  KC_M,  KC_COMM,KC_DOT, KC_SLSH, KC_RSFT, \
                      KC_LCTRL,KC_LGUI,KC_LALT,LT(BLUE, KC_SPC),     LT(RED, KC_SPC),KC_RALT,KC_RGUI, KC_RCTRL \
),

/* BLUE **********************************************************************************************************************
 * .-----------------------------------------.                         .-----------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                         |  F7  |  F8  |  F9  | F10  | F11  | F12  |
 * |------+------+------+------+------+------|                         |------+------+------+------+------+------|
 * |  `   |  9   |  8   |  7   |  +   |  -   |                         | BkSp | Home | PgDn | PgUp | End  | Tab  |
 * |------+------+------+------+------+------|                         |------+------+------+------+------+------|
 * |  '   |  6   |  5   |  4   |  *   |  /   |-------.         .-------| Del  |   ←  |   ↓  |   ↑  |   →  | Entr |
 * |------+------+------+------+--^^--+------|   [   |         |   ]   |------+--^^--+------+------+------+------|
 * |  _   |  3   |  2   |  1   |  (   |  )   |-------|         |-------| Ins  |  C←  |  C↓  |  C↑  |  C→  |Shift |
 * '-----------------------------------------/+Fn+++/           \  Fn  \-----------------------------------------'
 *                   |  =   |  0   |  .   | /Space+/             \Space \  | RAlt | RGUI | RCtl |
 *                   |      |      |      |/++++++/               \      \ |      |      |      |
 *                   '---------------------------'                 '------''--------------------'
 */
[_BLUE] = LAYOUT( \
  KC_F1,    KC_F2, KC_F3, KC_F4, KC_F5,   KC_F6,                       KC_F7,   KC_F8,     KC_F9,     KC_F10,  KC_F11,     KC_F12, \
  KC_GRAVE, KC_P9, KC_P8, KC_P7, KC_PLUS, KC_MINS,                     KC_BSPC, KC_HOME,   KC_PGDN,   KC_PGUP, KC_END,     KC_TAB, \
  KC_QUOT,  KC_P6, KC_P5, KC_P4, KC_ASTR, KC_SLSH,                     KC_DEL,  KC_LEFT,   KC_DOWN,   KC_UP,   KC_RGHT,    _______,\
  KC_UNDS,  KC_P3, KC_P2, KC_P1, KC_LPRN, KC_RPRN, KC_LBRC,   KC_RBRC, KC_INS,  C(KC_LEFT),C(KC_DOWN),C(KC_UP),C(KC_RGHT), _______,\
                    KC_EQL,   KC_0,   KC_DOT, _______,          _______,  _______, _______, _______\
),                                   /*     |___Fn-SPACE___|---Fn-SPACE---|     */

/* RED **********************************************************************************************************************
 * .-----------------------------------------.                            .-----------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                            |  F7  |  F8  |  F9  | F10  | F11  | F12  |
 * |------+------+------+------+------+------|                            |------+------+------+------+------+------|
 * |  Tab | Home | PgDn | PgUp | End  | BkSp |                            |   -  |  +   |  7   |  8   |  9   |   `  |
 * |------+------+------+------+------+------|                            |------+------+------+------+------+------|
 * | Entr |   ←  |   ↓  |   ↑  |   →  | Del  |-------.            .-------|   /  |  *   |  4   |  5   |  6   |   '  |
 * |------+------+------+------+--^^--+------|   [   |            |   ]   |------+--^^--+------+------+------+------|
 * | Shift|  C←  |  C↓  |  C↑  |  C→  | Ins  |-------|            |-------|   (  |  )   |  1   |  2   |  3   |   _  |
 * '-----------------------------------------/ Fn   /              \++Fn++\-----------------------------------------'
 *                   | LCtl | LGUI | LAlt | /Space /                \Space+\  |   .  |   0  | =    |
 *                   |      |      |      |/      /                  \++++++\ |      |      |      |
 *                   '---------------------------'                    '------''--------------------'
 */
[_RED] = LAYOUT( \
  KC_F1,  KC_F2,     KC_F3,     KC_F4,   KC_F5,   KC_F6,                       KC_F7,   KC_F8,   KC_F9, KC_F10, KC_F11, KC_F12, \
  _______,KC_HOME,   KC_PGDN,   KC_PGUP, KC_END,  KC_BSPC,                     KC_MINS, KC_PLUS, KC_7,  KC_8,   KC_9,   KC_GRAVE,\
  KC_ENT, KC_LEFT,   KC_DOWN,   KC_UP,   KC_RGHT, KC_DEL,                      KC_SLSH, KC_ASTR, KC_4,  KC_5,   KC_6,   KC_QUOT, \
  _______,C(KC_LEFT),C(KC_DOWN),C(KC_UP),C(KC_RGHT),KC_INS,KC_LBRC,    KC_RBRC,KC_LPRN, KC_RPRN, KC_1,  KC_2,   KC_3,   KC_UNDS, \
                     _______, _______, _______, _______,              _______,  KC_DOT,  KC_0,   KC_EQL \
),                                   /*        |---Fn-SPACE---|___Fn-SPACE___|     */

/* FnCaps **********************************************************************************************************************
 * .-----------------------------------------.                               .-----------------------------------------.
 * |TskMgr|      |      |      |      | RESET|                               | Break| NumLk| ScrLk| PScr |      |      |
 * |------+------+------+------+------+------|                               |------+------+------+------+------+------|
 * |      |      |      |      |      | DEBUG|                               |      | MNxt | VolUp| MPly |      |      |
 * |------+------+------+------+------+------|                               |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.               .-------|      | MPrv | VolDn| Mute |      |      |
 * |------+------+------+------+--^^--+------|       |               |       |------+--^^--+------+------+------+------|
 * |      |      |      |      |      |      |-------|               |-------|      |      |      |      |      |      |
 * '-----------------------------------------/       /                \      \-----------------------------------------'
 *                   |QWERTY|COLMAK|      | /       /                  \      \  |      |      |      |
 *                   |      |      |      |/       /                    \      \ |      |      |      |
 *                   '----------------------------'                      '------''--------------------'
 */
[_FC] = LAYOUT( \
  C(S(KC_ESC)),XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RESET,                       KC_BRK,  KC_NLCK, KC_SLCK, KC_PSCR, XXXXXXX, XXXXXXX, \
  XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DEBUG,                       XXXXXXX, KC_MNXT, KC_VOLU, KC_MPLY, XXXXXXX, XXXXXXX, \
  _______,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX, KC_MPRV, KC_VOLD, KC_MUTE, XXXXXXX, XXXXXXX, \
  XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
                               QWRT, COLE,  XXXXXXX, XXXXXXX,            XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX \
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
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
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
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    matrix_write_ln(matrix, read_keylogs());
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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  switch (keycode) {
    case COLE:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLE);
      }
      return false;
      break;
    case QWRT:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWRT);
      }
      return false;
      break;
    case BLUE:
      if (record->event.pressed) {
        layer_on(_BLUE);
        update_tri_layer_RGB(_BLUE, _RED, _ADJUST);
      } else {
        layer_off(_BLUE);
        update_tri_layer_RGB(_BLUE, _RED, _ADJUST);
      }
      return false;
      break;
    case RED:
      if (record->event.pressed) {
        layer_on(_RED);
        update_tri_layer_RGB(_BLUE, _RED, _ADJUST);
      } else {
        layer_off(_RED);
        update_tri_layer_RGB(_BLUE, _RED, _ADJUST);
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

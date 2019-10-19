  #include QMK_KEYBOARD_H
#include "bootloader.h"
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

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  BACKLIT,
  RGBRST
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};
#define BASE 0 // default layer
#define SYMB 1 // symbols
#define NUMB 2 // numbers/motion
#define KC______ KC_TRNS
#define KC_XXXXX KC_NO
#define KC_LOWER LOWER
#define KC_RAISE RAISE
#define KC_RST   RESET
#define KC_LRST  RGBRST
#define KC_LTOG  RGB_TOG
#define KC_LHUI  RGB_HUI
#define KC_LHUD  RGB_HUD
#define KC_LSAI  RGB_SAI
#define KC_LSAD  RGB_SAD
#define KC_LVAI  RGB_VAI
#define KC_LVAD  RGB_VAD
#define KC_LMOD  RGB_MOD
#define KC_CTLTB CTL_T(KC_TAB)
#define KC_GUIEI GUI_T(KC_LANG2)
#define KC_ALTKN ALT_T(KC_LANG1)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap 0: Basic layer
	 *
	 * ,-------------------------------------------.                         ,-------------------------------------------.
	 * | ALT/ta |   Q  |   W  |   E  |   R  |   T  |                        |  Y   |   U  |   I  |   O  |   P  |  | \   |
	 * |--------+------+------+------+------+------|                        |------+------+------+------+------+--------|
	 * |sup /BS |   A  |   S  |  D   |   F  |   G  |                        |   H  |   J  |   K  |   L  | ;  : |  ' "   |
	 * |--------+------+------+------+------+------|                        |------+------+------+------+------+--------|
	 * | LSt    |   Z  |   X  |   C  |   V  |   B  |                        |   N  |   M  | ,  < | . >  | /  ? |  - _   |
	 * `--------+------+------+------+------+-------                        -------+------+------+------+------+--------'
	 *                    .----------.   .-------.                                 .------.   .-----.
	 *                    |esc       |   |ctrl/Del|                               | ent   |   | Tab |
	 *                    '----------'   '-------'                                 `------.   '-----'
	 *                                 ,-----                                ------.
	 *                                 | SYMB |                             | NUMB |
	 *                                 |      |                             |Space |
	 *                                 |      |                             |      |
	 *                                 `-------                             `------'
	 */
	 [BASE] = LAYOUT(
	      KC_TAB,  KC_Q,  KC_W,   KC_E,   KC_R, KC_T,                   KC_Y,    KC_U, KC_I, KC_O,   KC_P,    KC_PIPE,
	     KC_BSPC,  KC_A,  KC_S,   KC_D,   KC_F, KC_G,                  KC_H,    KC_J, KC_K, KC_L,   KC_SCLN, KC_QUOT,
	     KC_LSFT,KC_Z,  KC_X,   KC_C,   KC_V, KC_B,     		            				   KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_MINS,
	     KC_ESC, KC_LCTL, LT(SYMB, KC_SPC),                   					 LT(NUMB, KC_SPC), KC_ENT, KC_TAB
	     ),
/* Keymap 1: Symbols layer
 *
 * ,-------------------------------------------.                         ,-------------------------------------------.
 * |        |  !   |  @   |  {   |  }   |  |   |                         |      |   &  |  =   |   scn|  scn |  \ |   |
 * |--------+------+------+------+------+------|                         |------+------+------+------+------+--------|
 * |        |  #   |  $   |  (   |  )   |  `   |                         |   +  |  -   |  /   |  *   |  %   |  ' "   |
 * |--------+------+------+------+------+------|                         |------+------+------+------+------+--------|
 * |        |  %   |  ^   |  [   |  ]   |  ~   |                         |      |      |  ,   |  .   |  / ? | - _    |
 * `--------+------+------+------+------+-------                          ------+------+------+------+------+--------'
 *                        .------.   .------.                                 .------.   .-----.
 *                        |      |   |      |                                 |      |   | DEL |
 *                        '------'   '------'                                 `------.   '-----'
 *
 *                                 ,------                                   ------.
 *                                 |      |                                 |      |
 *                                 |   ;  |                                 |   ;  |
 *                                 |      |                                 |      |
 *                                 `-------                                 `------'
 */
[SYMB] = LAYOUT(
    KC_LALT, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE,                     KC_TRNS, KC_AMPR, KC_EQL, LCTL(LSFT(KC_3)), LCTL(LSFT(KC_4)), KC_BSLS,
    KC_LGUI,  KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV,                      KC_PLUS, KC_MINS, KC_SLSH, KC_ASTR, KC_PERC, KC_QUOT,
      KC_TRNS, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD,                   KC_AMPR, KC_EQL,  KC_COMM, KC_DOT,  KC_SLSH, KC_MINS,
                                  KC_TRNS, KC_TRNS, KC_SCLN,                  KC_EQL,  KC_SCLN, KC_DEL
    ),
/* Keymap 2: Pad/Function layer
 *
 * ,-------------------------------------------.                         ,-------------------------------------------.
 * |        |   1  |  2   |  3   |  4   |  5   |                         |  6   |  7   |  8   |  9   |  0   | VolUp  |
 * |--------+------+------+------+------+------|                         |------+------+------+------+------+--------|
 * |  F1    |  F2  | F3   | F4   | F5   | F6   |                         |      | LEFT | DOWN |  UP  | RIGHT| VolDn  |
 * |--------+------+------+------+------+------|                         |------+------+------+------+------+--------|
 * |  F7    |  F8  | F9   | F10  | F11  | F12  |                         | MLFT | MDWN | MUP  | MRGHT|Ply/Pa|  Skip  |
 * `--------+------+------+------+------+-------                         `------+------+------+------+------+--------'
 *                        .------.   .------.                                 .------.   .-----.
 *                        |      |   |      |                                 |      |   |     |
 *                        '------'   '------'                                 `------.   '-----
 *                                 ,------|                              ------
 *                                 |      |                             |       |
 *                                 |      |                             |       |
 *                                 |      |                             |       |
 *                                 `-------                             `--------
 */
[NUMB] = LAYOUT(
    KC_TRNS, KC_1, 	  KC_2,    KC_3,    KC_4,    KC_5,                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_VOLU,
    KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                       KC_TRNS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_VOLD,
    KC_TRNS, KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,                      KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_MPLY, KC_MNXT,
                            KC_F11, KC_F12, KC_TRNS,                        KC_TRNS, KC_TRNS, KC_TRNS
    )
};

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

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
      rgblight_setrgb_at(111, 0, 211, 13);
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
    case QWERTY:
      if (record->event.pressed) {
        rgblight_setrgb_at(148, 0, 211, 13);
        persistent_default_layer_set(1UL<<_QWERTY);
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
    default:
    rgblight_enable();
        if(isLeftHand) {                        // this sets the underside LEDs (1-6) to cyan on both sides and does nothing with the rest.
          for(int i=0; i < 6; i ++) {           // this also means that if I manually change LED color to red, the bottom 6 LEDS will ALWAYS be cyan.
            rgblight_setrgb_at(0, 255, 150, i); // it's the only way I found to make it switch back to underglow LEDs after I've used another layer.
          }
        } else {
          for(int j=0; j < 6; j ++) {
            rgblight_setrgb_at(0, 255, 150, j);
          }
        }
        break;
  }
  return true;
}

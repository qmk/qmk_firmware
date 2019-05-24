#include QMK_KEYBOARD_H

#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
    _QWERTY = 0,
    _COLEMAK,
    _FN,
    _ADJ
};

// Keycode defines for layers
#define QWERTY   DF(_QWERTY)
#define COLEMAK  DF(_COLEMAK)
#define FN       MO(_FN)
#define ADJ      MO(_ADJ)

enum custom_keycodes {
  RGBRST = SAFE_RANGE
};

#define FN_ESC   LT(_FN, KC_ESC)
#define FN_CAPS  LT(_FN, KC_CAPS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Qwerty
   * ,------------------------------------------------.  ,------------------------------------------------.
   * | GESC |   1  |   2  |   3  |   4  |   5  |   -  |  |   =  |   6  |   7  |   8  |   9  |   0  | BkSp |
   * |------+------+------+------+------+------|------|  |------|------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |   [  |  |   ]  |   Y  |   U  |   I  |   O  |   P  |   \  |
   * |------+------+------+------+------+------|------|  |------|------+------+------+------+------+------|
   * |FN(CAPS)| A  |   S  |   D  |   F  |   G  |   (  |  |   )  |   H  |   J  |   K  |   L  |   ;  |   '  |
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   * |Shift |   Z  |   X  |   C  |   V  |   B  |   {  |  |   }  |   N  |   M  |   ,  |   .  |   /  |Enter |
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   * | Ctrl |  Win |  Alt |  RGB | ADJ  | Space| DEL  |  | Enter| Space|  FN  | Left | Down | Up   |Right |
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------'
   *                                    | Space| DEL  |  | Enter| Space|
   *                                    `-------------'  `-------------'
   */
  [_QWERTY] = LAYOUT( \
    KC_GESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5, KC_MINS,  KC_EQL,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC, \
     KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T, KC_LBRC, KC_RBRC,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSLS, \
    FN_CAPS,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G, KC_LPRN, KC_RPRN,    KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT, \
    KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B, KC_LCBR, KC_RCBR,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ENT, \
    KC_LCTL, KC_LGUI, KC_LALT, RGB_TOG,     ADJ,  KC_SPC,  KC_DEL,  KC_ENT,  KC_SPC,      FN, KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, \
                                                  KC_SPC,  KC_DEL,  KC_ENT,  KC_SPC \
  ),

  /* Colemak
   * ,------------------------------------------------.  ,------------------------------------------------.
   * | GESC |   1  |   2  |   3  |   4  |   5  |   -  |  |   =  |   6  |   7  |   8  |   9  |   0  | BkSp |
   * |------+------+------+------+------+------|------|  |------|------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   F  |   P  |   B  |   [  |  |   ]  |   J  |   L  |   U  |   Y  |   ;  |   \  |
   * |------+------+------+------+------+------|------|  |------|------+------+------+------+------+------|
   * |FN(CAPS)| A  |   R  |   S  |   T  |   G  |   (  |  |   )  |   K  |   N  |   E  |   I  |   O  |   '  |
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   * |Shift |   Z  |   X  |   C  |   D  |   V  |   {  |  |   }  |   M  |   H  |   ,  |   .  |   /  |Enter |
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   * | Ctrl |  Win |  Alt |  RGB | ADJ  | Space| DEL  |  | Enter| Space|  FN  | Left | Down | Up   |Right |
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------'
   *                                    | Space| DEL  |  | Enter| Space|
   *                                    `-------------'  `-------------'
   */
  [_COLEMAK] = LAYOUT( \
    KC_GESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5, KC_MINS,  KC_EQL,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC, \
     KC_TAB,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B, KC_LBRC, KC_RBRC,    KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN, KC_BSLS, \
    FN_CAPS,    KC_A,    KC_R,    KC_S,    KC_T,    KC_G, KC_LPRN, KC_RPRN,    KC_K,    KC_N,    KC_E,    KC_I,    KC_O, KC_QUOT, \
    KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_D,    KC_V, KC_LCBR, KC_RCBR,    KC_M,    KC_H, KC_COMM, KC_DOT,  KC_SLSH,  KC_ENT, \
    KC_LCTL, KC_LGUI, KC_LALT, RGB_TOG,     ADJ,  KC_SPC,  KC_DEL,  KC_ENT,  KC_SPC,      FN, KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, \
                                                  KC_SPC,  KC_DEL,  KC_ENT,  KC_SPC \
  ),

  /* FN
   * ,------------------------------------------------.  ,------------------------------------------------.
   * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |      |  |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
   * |------+------+------+------+------+------|------|  |------|------+------+------+------+------+------|
   * |      | PGDN |  UP  | PGUP |      |      |      |  |      |      | PGDN |  UP  | PGUP | PRINT| HOME |
   * |------+------+------+------+------+------|------|  |------|------+------+------+------+------+------|
   * |      | LEFT | DOWN | RIGHT|      |      |      |  |      |      | LEFT | DOWN | RIGHT|INSERT| END  |
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   * |      |      |      |RGBMOD|      |      |      |  |      |      | PLAY | NEXT | MUTE | VOL- | VOL+ |
   * `------+------+------+------+------+------+------|  |------+------+------+------+------+------+------'
   *                                    |      |      |  |      |      |
   *                                    `-------------'  `-------------'
   */
  [_FN] = LAYOUT( \
      KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6, _______, KC_PSCR,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12, \
    _______, KC_PGDN,   KC_UP, KC_PGUP, _______, _______, _______, _______, _______, KC_PGDN,   KC_UP, KC_PGUP, KC_PSCR, KC_HOME, \
    _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT,  KC_INS,  KC_END, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, RGB_MOD, _______, _______, _______, _______, _______, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, \
                                                 _______, _______, _______, _______ \
  ),

  /* ADJ
   * ,------------------------------------------------.  ,------------------------------------------------.
   * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |      |  |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
   * |------+------+------+------+------+------|------|  |------|------+------+------+------+------+------|
   * |      | SAD  | VAI  | SAI  | RESET|      |      |  |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------|------|  |------|------+------+------+------+------+------|
   * |      | HUD  | VAD  | HUI  |RGBRST|      |      |  |      |      |QWERTY|COLEMK|      |      |      |
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |  |      |      |      |RGBTOG|  HUI |  SAI | VAI  |
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   * |      |      |      |RGBMOD(|      |      |      |  |      |      |     |RGBRMOD| HUD |  SAD | VAD  |
   * `------+------+------+------+------+------+------|  |------+------+------+------+------+------+------'
   *                                    |      |      |  |      |      |
   *                                    `-------------'  `-------------'
   */

  [_ADJ] =  LAYOUT( \
      KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6, _______, _______,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12, \
    _______, RGB_SAD, RGB_VAI, RGB_SAI,   RESET, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, RGB_HUD, RGB_VAD, RGB_HUI,  RGBRST, _______, _______, _______, _______,  QWERTY, COLEMAK, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, \
    _______, _______, _______, RGB_MOD, _______, _______, _______, _______, _______, _______, RGB_RMOD,RGB_HUD, RGB_SAD, RGB_VAD, \
                                                 _______, _______, _______, _______ \
  )
};

#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) { /* First encoder */
    if (clockwise) {
      tap_code(KC_VOLU);
    } else {
      tap_code(KC_VOLD);
    }
  } else if (index == 1) { /* Second encoder*/
    if (clockwise) {
      tap_code(KC_VOLU);
    } else {
      tap_code(KC_VOLD);
    }
  }
}
#endif

// For RGBRST Keycode
#if defined(RGB_MATRIX_ENABLE)
extern void eeconfig_update_rgb_matrix_default(void);
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static uint16_t reset_timer;
  switch (keycode) {
    case RGBRST:
#if defined(RGBLIGHT_ENABLE)
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
        }
#elif defined(RGB_MATRIX_ENABLE)
        if (record->event.pressed) {
          eeconfig_update_rgb_matrix_default();
        }
#endif
      return false;
    case RESET:
      if (record->event.pressed) {
          reset_timer = timer_read();
      } else {
          if (timer_elapsed(reset_timer) >= 500) {
              reset_keyboard();
          }
      }
      return false;
  }
  return true;
}


// OLED Driver Logic
#ifdef OLED_DRIVER_ENABLE
extern keymap_config_t keymap_config;

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!has_usb())
    return OLED_ROTATION_180;  // flip 180 for offhand
  return rotation;
}

static void render_logo(void) {
  static const char PROGMEM sol_logo[] = {
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};

  oled_write_P(sol_logo, false);
}

static void render_status(void) {
  // Render to mode icon
  static const char PROGMEM mode_logo[4][4] = {
    {0x95,0x96,0x0a,0},
    {0xb5,0xb6,0x0a,0},
    {0x97,0x98,0x0a,0},
    {0xb7,0xb8,0x0a,0} };

  if (keymap_config.swap_lalt_lgui != false) {
    oled_write_P(mode_logo[0], false);
    oled_write_P(mode_logo[1], false);
  } else {
    oled_write_P(mode_logo[2], false);
    oled_write_P(mode_logo[3], false);
  }

  // Define layers here, Have not worked out how to have text displayed for each layer. Copy down the number you see and add a case for it below
  oled_write_P(PSTR("Layer: "), false);
  switch (biton32(layer_state)) {
    case _QWERTY:
      oled_write_P(PSTR("Default\n"), false);
      break;
    case _COLEMAK:
      oled_write_P(PSTR("Colemak\n"), false);
      break;
    case _FN:
      oled_write_P(PSTR("FN\n"), false);
      break;
    case _ADJ:
      oled_write_P(PSTR("_ADJ\n"), false);
      break;
    default:
      oled_write_P(PSTR("Undefined\n"), false);
  }

  // Host Keyboard LED Status
  uint8_t led_usb_state = host_keyboard_leds();
  oled_write_P(led_usb_state & (1<<USB_LED_NUM_LOCK) ? PSTR("NUMLCK ") : PSTR("       "), false);
  oled_write_P(led_usb_state & (1<<USB_LED_CAPS_LOCK) ? PSTR("CAPLCK ") : PSTR("       "), false);
  oled_write_P(led_usb_state & (1<<USB_LED_SCROLL_LOCK) ? PSTR("SCRLCK ") : PSTR("       "), false);
}

void oled_task_user(void) {
  if (is_keyboard_master()) {
    render_status();
  } else {
    render_logo();
    oled_scroll_left();
  }
}

#endif

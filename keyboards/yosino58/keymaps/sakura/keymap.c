#include QMK_KEYBOARD_H

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3

enum custom_keycodes {
  LOWER = SAFE_RANGE,
  RAISE,
  ADJUST,
  RGBRST
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* QWERTY
 * ,-----------------------------------------.                                  ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |                                  |   6  |   7  |   8  |   9  |   0  |  -   |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                                  |   Y  |   U  |   I  |   O  |   P  |  =   |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |LShift|   A  |   S  |   D  |   F  |   G  |                                  |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |LCTRL |   Z  |   X  |   C  |   V  |   B  |-------.-------.  ,---------------|   N  |   M  |   ,  |   .  |   /  |  \   |
 * `-----------------------------------------/  Del  /       /   \       \ Bksp \----------------------------------------'
 *                          | LAlt | LGUI | /-------/ Space /     \ Enter \-------\  |   [  |  ]   |
 *                          |      |      |/ LOWER /       /       \       \ RAISE \ |      |      |
 *                          `-----------------------------'         '------------------------------'
 */
 [_QWERTY] = LAYOUT( \
  KC_GRV,   KC_1, KC_2, KC_3, KC_4,    KC_5,                                           KC_6,    KC_7,    KC_8,    KC_9,   KC_0,    KC_MINS, \
  KC_TAB,   KC_Q, KC_W, KC_E, KC_R,    KC_T,                                           KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,    KC_EQL,  \
  KC_LSFT,  KC_A, KC_S, KC_D, KC_F,    KC_G,                                           KC_H,    KC_J,    KC_K,    KC_L,   KC_SCLN, KC_QUOT, \
  KC_LCTRL, KC_Z, KC_X, KC_C, KC_V,    KC_B,    KC_DEL,    KC_SPC, KC_ENT, KC_BSPC,    KC_N,    KC_M,    KC_COMM, KC_DOT, KC_SLSH, KC_BSLS, \
                              KC_LALT, KC_LGUI, LOWER,                     RAISE,      KC_LBRC, KC_RBRC\
  ),

/* LOWER
 * ,-----------------------------------------.                                  ,-----------------------------------------.
 * | ESC  |  F1  |  F2  |  F3  |  F4  |  F5  |                                  |  F6  |  F7  |  F8  |  F9  |  F10 |      |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * | Tab  |   /  |   -  |   7  |   8  |   9  |                                  | PSCR | SLCK | Pause|      |  ��  |      |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |LShift|   *  |   +  |   4  |   5  |   6  |                                  |Insert| Home |PageUP|      |  ��  |  ��  |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |LCTRL |   .  |   0  |   1  |   2  |   3  |-------.-------.  ,---------------|  Del | End  |PageDN|  ��  | Num  | Caps |
 * `-----------------------------------------/  F11  /       /   \       \  F12  \----------------------------------------'
 *                          | LAlt | LGUI | /-------/ Space /     \ Enter \-------\  |      |      |
 *                          |      |      |/ LOWER /       /       \       \       \ |      |      |
 *                          `-----------------------------'         '------------------------------'
 */
 [_LOWER] = LAYOUT( \
  KC_ESC,  KC_F1,   KC_F2,   KC_F3, KC_F4,   KC_F5,                                       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  XXXXXXX, \
  _______, KC_PSLS, KC_PMNS, KC_P7, KC_P8,   KC_P9,                                       KC_PSCR, KC_SLCK, KC_PAUS, XXXXXXX, KC_UP,   XXXXXXX, \
  _______, KC_PAST, KC_PPLS, KC_P4, KC_P5,   KC_P6,                                       KC_INS,  KC_HOME, KC_PGUP, XXXXXXX, KC_DOWN, KC_RGHT, \
  _______, KC_PDOT, KC_P0,   KC_P1, KC_P2,   KC_P3,   KC_F11,  _______, _______, KC_F12,  KC_DEL,  KC_END,  KC_PGDN, KC_LEFT, KC_NLCK, KC_CLCK, \
                                    _______, _______, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX\
  ),

/* RAISE
 * ,-----------------------------------------.                                  ,-----------------------------------------.
 * |QK_BOOT |      |      |      |      |      |                                  | Mute | Vol+ | Play |      |      |      |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                                  | Prev | Vol- | Next |      |      |      |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |      |MS_Bt1| MS_U |MS_Bt2|MS_WhU|MS_WhL|                                  |      |      |RGB ON| HUE+ | SAT+ | VAL+ |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |      | MS_L | MS_D | MS_R |MS_WhD|MS_WhR|-------.-------.  ,---------------|      |      | MODE | HUE- | SAT- | VAL- |
 * `-----------------------------------------/       /       /   \       \       \----------------------------------------'
 *                          |      |      | /-------/ Space /     \ Enter \-------\  |      |      |
 *                          |      |      |/       /       /       \       \ RAISE \ |      |      |
 *                          `-----------------------------'         '------------------------------'
 */
 [_RAISE] = LAYOUT( \
  QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,                                     KC_MUTE, KC_VOLU, KC_MPLY, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,                                     KC_MPRV, KC_VOLD, KC_MNXT, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, KC_BTN1, KC_MS_U, KC_BTN2, KC_WH_U,    KC_WH_L,                                     XXXXXXX, XXXXXXX, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, \
  XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D,    KC_WH_R, XXXXXXX, _______, _______, XXXXXXX, XXXXXXX, RGBRST,  RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, \
                                      XXXXXXX,    XXXXXXX, XXXXXXX,                   _______, XXXXXXX, XXXXXXX \
  )

/*   ADJUST
 * ,-----------------------------------------.                                  ,-----------------------------------------.
 * |QK_BOOT |      |      |      |      |      |                                  |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                                  |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                                  |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.-------.  ,---------------|      |      |      |      |      |      |
 * `-----------------------------------------/       /       /   \       \       \----------------------------------------'
 *                          |      |      | /-------/       /     \       \-------\  |      |      |
 *                          |      |      |/       /       /       \       \       \ |      |      |
 *                          `-----------------------------'         '------------------------------'

 [_ADJUST] = LAYOUT( \
  QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
                                      XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX \
  ) 
*/
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

#ifdef OLED_ENABLE

//assign the right code to your layers for OLED display
#define L_QWERTY 0
#define L_LOWER 2
#define L_RAISE 4
#define L_ADJUST 8

// When add source files to SRC in rules.mk, you can use functions.
const char *read_logo(void);

bool oled_task_user(void) {
  if (is_keyboard_master()) {
    static char indctr[2][20][5]=
    {
      // white icon
      {
        {0x80,0x81,0x82,0x83,0},
        {0x88,0x89,0x8A,0x8B,0},
        {0x90,0x91,0x92,0x93,0},
        {0x98,0x99,0x9A,0x9B,0},
        {0x01,0x02,0x03,0x04,0},
        {0xA0,0xA1,0xA2,0xA3,0},
        {0xA8,0xA9,0xAA,0xAB,0},
        {0xB0,0xB1,0xB2,0xB3,0},
        {0xB8,0xB9,0xBA,0xBB,0},
        {0x21,0x22,0x23,0x24,0},
        {0xC0,0xC1,0xC2,0xC3,0},
        {0xC8,0xC9,0xCA,0xCB,0},
        {0xD0,0xD1,0xD2,0xD3,0},
        {0xD8,0xD9,0xDA,0xDB,0},
        {0x41,0x42,0x43,0x44,0},
        {0xE0,0xE1,0xE2,0xE3,0},
        {0xE8,0xE9,0xEA,0xEB,0},
        {0xF0,0xF1,0xF2,0xF3,0},
        {0xF8,0xF9,0xFA,0xFB,0},
        {0x61,0x62,0x63,0x64,0}
      },
      // Black icon
      {
        {0x84,0x85,0x86,0x87,0},
        {0x8C,0x8D,0x8E,0x8F,0},
        {0x94,0x95,0x96,0x97,0},
        {0x9C,0x9D,0x9E,0x9F,0},
        {0x05,0x06,0x07,0x08,0},
        {0xA4,0xA5,0xA6,0xA7,0},
        {0xAC,0xAD,0xAE,0xAF,0},
        {0xB4,0xB5,0xB6,0xB7,0},
        {0xBC,0xBD,0xBE,0xBF,0},
        {0x25,0x26,0x27,0x28,0},
        {0xC4,0xC5,0xC6,0xC7,0},
        {0xCC,0xCD,0xCE,0xCF,0},
        {0xD4,0xD5,0xD6,0xD7,0},
        {0xDC,0xDD,0xDE,0xDF,0},
        {0x45,0x46,0x47,0x48,0},
        {0xE4,0xE5,0xE6,0xE7,0},
        {0xEC,0xED,0xEE,0xEF,0},
        {0xF4,0xF5,0xF6,0xF7,0},
        {0xFC,0xFD,0xFE,0xFF,0},
        {0x65,0x66,0x67,0x68,0}
      }
    };

    int rown = 0;
    int rowc = 0;
    int rowl = 0;
    int rowr = 0;
    int rowa = 0;

    //Set Indicator icon
    if (host_keyboard_leds() & (1<<USB_LED_NUM_LOCK)) { rown = 1; } else { rown = 0; }
    if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) { rowc = 1; } else { rowc = 0; }
    if (layer_state == L_LOWER) { rowl = 1; }
    if (layer_state == L_RAISE) { rowr = 1; }
    if (layer_state == L_ADJUST) { rowa = 1; }

    oled_write(indctr[rowl]  [0], false);
    oled_write(indctr[rowr]  [1], false);
    oled_write(indctr[rowa]  [2], false);
    oled_write(indctr[rowc]  [3], false);
    oled_write(indctr[rown]  [4], false);
    oled_write_char(0x13, false);
    oled_write(indctr[rowl]  [5], false);
    oled_write(indctr[rowr]  [6], false);
    oled_write(indctr[rowa]  [7], false);
    oled_write(indctr[rowc]  [8], false);
    oled_write(indctr[rown]  [9], false);
    oled_write_char(0x13, false);
    oled_write(indctr[rowl]  [10], false);
    oled_write(indctr[rowr]  [11], false);
    oled_write(indctr[rowa]  [12], false);
    oled_write(indctr[rowc]  [13], false);
    oled_write(indctr[rown]  [14], false);
    oled_write_char(0x13, false);
    oled_write(indctr[rowl]  [15], false);
    oled_write(indctr[rowr]  [16], false);
    oled_write(indctr[rowa]  [17], false);
    oled_write(indctr[rowc]  [18], false);
    oled_write(indctr[rown]  [19], false);

  }else{
    oled_write(read_logo(), false);
  }
  return false;
}

#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
      } else {
        layer_off(_LOWER);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
      } else {
        layer_off(_RAISE);
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


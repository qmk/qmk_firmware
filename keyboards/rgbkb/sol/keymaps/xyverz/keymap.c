#include QMK_KEYBOARD_H
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "common/ssd1306.h"
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
enum layer_number {
    _DVORAK = 0,
    _DESTINY,
    _QWERTY,
    _COLEMAK,
    _LOWER,
    _RAISE,
    _ADJUST
};

enum custom_keycodes {
  DVORAK = SAFE_RANGE,
  DESTINY,
  QWERTY,
  COLEMAK,
  LOWER,
  RAISE,
  ADJUST,
  BACKLIT,
  RGBRST
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_DVORAK] = LAYOUT( \
      KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_HOME,  KC_PGUP, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS, \
      KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_END,   KC_PGDN, KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH, \
      KC_RCTL, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    XXXXXXX,  XXXXXXX, KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS, \
      KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    XXXXXXX,  XXXXXXX, KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT, \
      KC_GRV,  KC_LGUI, KC_LEFT, KC_RGHT, LOWER,   KC_LCTL, KC_LALT,  KC_RALT, KC_RCTL, RAISE,   KC_UP,   KC_DOWN, KC_RGUI, KC_RCTL, \
                                                   KC_BSPC, KC_RGUI,  KC_ENT,  KC_SPC \

  ),

  [_DESTINY] = LAYOUT( \
      KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_HOME,  KC_PGUP, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS, \
      KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_END,   KC_PGDN, KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH, \
      KC_RCTL, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    XXXXXXX,  XXXXXXX, KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS, \
      KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    XXXXXXX,  XXXXXXX, KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT, \
      KC_GRV,  KC_LGUI, KC_LEFT, KC_RGHT, LOWER,   KC_LCTL, KC_LALT,  KC_RALT, KC_RCTL, RAISE,   KC_UP,   KC_DOWN, KC_RGUI, KC_RCTL, \
                                                   KC_BSPC, KC_RGUI,  KC_ENT,  KC_SPC \

  ),
  
  [_QWERTY] = LAYOUT( \
      KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_HOME,  KC_PGUP, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS, \
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_END,   KC_PGDN, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_SLSH, \
      KC_RCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    XXXXXXX,  XXXXXXX, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    XXXXXXX,  XXXXXXX, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
      KC_GRV,  KC_LGUI, KC_LEFT, KC_RGHT, LOWER,   KC_LCTL, KC_LALT,  KC_RALT, KC_RCTL, RAISE,   KC_UP,   KC_DOWN, KC_RGUI, KC_RCTL, \
                                                   KC_BSPC, KC_RGUI,  KC_ENT,  KC_SPC \
  ),

  [_COLEMAK] = LAYOUT( \
      KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_HOME,  KC_PGUP, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS, \
      KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_END,   KC_PGDN, KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_SLSH, \
      KC_RCTL, KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    XXXXXXX,  XXXXXXX, KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT, \
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    XXXXXXX,  XXXXXXX, KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
      KC_GRV,  KC_LGUI, KC_LEFT, KC_RGHT, LOWER,   KC_LCTL, KC_LALT,  KC_RALT, KC_RCTL, RAISE,   KC_UP,   KC_DOWN, KC_RGUI, KC_RCTL, \
                                                   KC_BSPC, KC_RGUI,  KC_ENT,  KC_SPC \
  ),

  [_LOWER] =  LAYOUT( \
      KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______, _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
      KC_CAPS, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, XXXXXXX, XXXXXXX, _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, \
      _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, XXXXXXX, XXXXXXX, _______, _______, _______, _______, _______, _______, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
                                                   KC_DEL,  _______, _______, KC_INS \
  ),

  [_RAISE] =  LAYOUT( \
      KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______, _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
      KC_CAPS, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, XXXXXXX, XXXXXXX, _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, \
      _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, XXXXXXX, XXXXXXX, _______, _______, _______, _______, _______, _______, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
                                                   KC_DEL,  _______, _______, KC_INS \
  ),

  /* ADJUST
   * ,------------------------------------------------.  ,------------------------------------------------.
   * |  F11 |  F1  |  F2  |  F3  |  F4  |  F5  | RESET|  |      |  F6  |  F7  |  F8  |  F9  |  F10 |  F12 |
   * |------+------+------+------+------+------|------|  |------|------+------+------+------+------+------|
   * |      |      |QWERTY|COLEMK|DVORAK|DESTNY|      |  |      |      | PrSc | ScLk | NmLk |      |      |
   * |------+------+------+------+------+------|------|  |------|------+------+------+------+------+------|
   * |      |      | Mute | Vol- | Vol+ |      |      |  |      |RGBTOG|RGBMOD|  HUI |  SAI | VAI  |      |
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   * |      |      | Prev | Play | Next |      |      |  |      |      |RGBRMD|  HUD |  SAD | VAD  |      |
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   * |      |      |      | Home | End  |      |      |  |      |      | PgUp | PgDn |      |      |      |
   * `------+------+------+------+------+------+------|  |------+------+------+------+------+------+------'
   *                                    | Del  |      |  |      | Ins  |
   *                                    `-------------'  `-------------'
   */

  [_ADJUST] =  LAYOUT( \
      _______, _______, _______, _______, _______, _______, RESET,   _______, _______, _______, _______, _______, _______, _______, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PSCR, KC_SLCK, KC_NLCK, _______, _______, \
      KC_CAPS, _______, QWERTY,  COLEMAK, DVORAK,  DESTINY, XXXXXXX, XXXXXXX, RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, _______, \
      _______, _______, _______, _______, _______, _______, XXXXXXX, XXXXXXX, _______, RGB_RMOD,RGB_HUD, RGB_SAD, RGB_VAD, _______, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
                                                   KC_DEL,  _______, _______, KC_INS \
      )
};



// define variables for reactive RGB
bool TOG_STATUS = false;
int RGB_current_mode;

// Setting ADJ layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    #ifdef RGBLIGHT_ENABLE
      //rgblight_mode(RGB_current_mode);
    #endif
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case DVORAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DVORAK);
      }
      return false;
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;

/*
    Commenting this out since I removed the layer, but I want this in here for reference.

    case FN:
      if (record->event.pressed) {
        //not sure how to have keyboard check mode and set it to a variable, so my work around
        //uses another variable that would be set to true after the first time a reactive key is pressed.
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
          #ifdef RGBLIGHT_ENABLE
            //rgblight_mode(15);
          #endif
        }
        layer_on(_FN);
      } else {
        #ifdef RGBLIGHT_ENABLE
          //rgblight_mode(RGB_current_mode);  // revert RGB to initial mode prior to RGB mode change
        #endif
        layer_off(_FN);
        TOG_STATUS = false;
      }
      return false;
      break;
 */
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
        break;
      //led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
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

// hook point for 'led_test' keymap
//   'default' keymap's led_test_init() is empty function, do nothing
//   'led_test' keymap's led_test_init() force rgblight_mode_noeeprom(35);
__attribute__ ((weak))
void led_test_init(void) {}

void matrix_scan_user(void) {
    led_test_init();
    iota_gfx_task();  // this is what updates the display continuously
}

void matrix_update(struct CharacterMatrix *dest,
                          const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

//assign the right code to your layers for OLED display
#define L_BASE 0
#define L_FN (1<<_FN)
#define L_ADJ (1<<_ADJ)

static void render_logo(struct CharacterMatrix *matrix) {

  static char logo[]={
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,
    0};
  matrix_write(matrix, logo);
  //matrix_write_P(&matrix, PSTR(" Split keyboard kit"));
}



void render_status(struct CharacterMatrix *matrix) {

  // Render to mode icon
  static char logo[][2][3]={{{0x95,0x96,0},{0xb5,0xb6,0}},{{0x97,0x98,0},{0xb7,0xb8,0}}};
  if(keymap_config.swap_lalt_lgui==false){
    matrix_write(matrix, logo[0][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write(matrix, logo[0][1]);
  }else{
    matrix_write(matrix, logo[1][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write(matrix, logo[1][1]);
  }

  // Define layers here, Have not worked out how to have text displayed for each layer. Copy down the number you see and add a case for it below
  char buf[40];
  snprintf(buf,sizeof(buf), "Undef-%ld", layer_state);
  matrix_write_P(matrix, PSTR("\nLayer: "));
    switch (layer_state) {
        case L_BASE:
           matrix_write_P(matrix, PSTR("Default"));
           break;
        /* case L_FN:
           matrix_write_P(matrix, PSTR("FN"));
           break; */
        case L_ADJ:
        /* case L_ADJ_TRI: */
           matrix_write_P(matrix, PSTR("ADJ"));
           break;
        default:
           matrix_write(matrix, buf);
    }

  // Host Keyboard LED Status
  char led[40];
    snprintf(led, sizeof(led), "\n%s  %s  %s",
            (IS_HOST_LED_ON(USB_LED_NUM_LOCK)) ? "NUMLOCK" : "       ",
            (IS_HOST_LED_ON(USB_LED_CAPS_LOCK)) ? "CAPS" : "    ",
            (IS_HOST_LED_ON(USB_LED_SCROLL_LOCK)) ? "SCLK" : "    ");
  matrix_write(matrix, led);
}


void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;

#if DEBUG_TO_SCREEN
  if (debug_enable) {
    return;
  }
#endif

  matrix_clear(&matrix);
  if(is_master){
    render_status(&matrix);
  }else{
    render_logo(&matrix);
  }
  matrix_update(&display, &matrix);
}

#endif

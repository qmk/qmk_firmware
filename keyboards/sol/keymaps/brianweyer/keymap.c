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
    _QWERTY = 0,
    _FN,
    _ADJ
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  FN,
  ADJ,
  RGBRST
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* QWERTY
   * ,------------------------------------------------.  ,------------------------------------------------.
   * |   `  |   1  |   2  |   3  |   4  |   5  |   -  |  |   =  |   6  |   7  |   8  |   9  |   0  | Bspc |
   * |------+------+------+------+------+------|------|  |------|------+------+------+------+------+------|
   * |  Tab |   Q  |   W  |   E  |   R  |   T  |   [  |  |   ]  |   Y  |   U  |   I  |   O  |   P  |   \  |
   * |------+------+------+------+------+------|------|  |------|------+------+------+------+------+------|
   * |  Esc |   A  |   S  |   D  |   F  |   G  |      |  |      |   H  |   J  |   K  |   L  |   ;  |   '  |
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |      |  |      |   N  |   M  |   ,  |   .  |   /  | Shift|
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   * | Ctrl |  Alt |  FN  | LGui |  RGB |  Spc |  Del |  | Bspc |  Spc |  Adj | LGui |  FN  |  Alt | Ctrl |
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   *                                    |  Spc |  Ent |  |  Ent |  Spc |
   *                                    `-------------'  `-------------'
   */
  [_QWERTY] = LAYOUT_kc( \
  //,--------+--------+--------+--------+--------+--------+--+--------+.   ,--------+--+--------+--------+--------+--------+--------+--------+
          GRV,       1,       2,       3,       4,       5,       MINS,          EQL,          6,       7,       8,       9,       0,    BSPC,
  //|--------+--------+--------+--------+--------+--------+--+--------|    |--------+--+--------+--------+--------+--------+--------+--------|
          TAB,       Q,       W,       E,       R,       T,       LBRC,         RBRC,          Y,       U,       I,       O,       P,    BSLS,
  //|--------+--------+--------+--------+--------+--------+--+--------|    |--------+--+--------+--------+--------+--------+--------+--------|
          ESC,       A,       S,       D,       F,       G,    _______,      _______,          H,       J,       K,       L,    SCLN,    QUOT,
  //|--------+--------+--------+--------+--------+--------+--+--------|    |--------+--+--------+--------+--------+--------+--------+--------|
         LSPO,       Z,       X,       C,       V,       B,    _______,      _______,          N,       M,    COMM,     DOT,    SLSH,    RSPC,
  //|--------+--------+--------+--------+--------+--------+--+--------|    |--------+--+--------+--------+--------+--------+--------+--------|
         LCTL,    LALT,      FN,    LGUI, RGB_MOD,        SPC,     DEL,         BSPC,        SPC,     ADJ,    LGUI,      FN,    LALT,    LCTL,
  //|--------+--------+--------+--------+--------+--+--------+--------|    |--------+--+--------+--------+--------+--------+--------+--------|
                           VOLD,    VOLU,                 SPC,     ENT,          ENT,        SPC,             DOWN,    UP
  //                      Rotary Left               |--------+--------|    |--------+-----------+              Rotary Right
      ),

  /* FN
   * ,------------------------------------------------.  ,------------------------------------------------.
   * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |      |  |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
   * |------+------+------+------+------+------|------|  |------|------+------+------+------+------+------|
   * |      |      |      |  Up  |      |      |      |  |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------|------|  |------|------+------+------+------+------+------|
   * |      |      | Left | Down | Right|      |      |  |      | Play | Next | Mute | V-Up |V-Down|      |
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   *                                    |      |      |  |      |      |
   *                                    `-------------'  `-------------'
   */
  [_FN] = LAYOUT_kc( \
  //,--------+--------+--------+--------+--------+--------+--+--------+.   ,--------+--+--------+--------+--------+--------+--------+--------+
           F1,      F2,      F3,      F4,      F5,      F6,    _______,      _______,         F7,      F8,      F9,     F10,     F11,     F12,
  //|--------+--------+--------+--------+--------+--------+--+--------|    |--------+--+--------+--------+--------+--------+--------+--------|
      _______, _______, _______,      UP, _______, _______,    _______,      _______,    _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--+--------|    |--------+--+--------+--------+--------+--------+--------+--------|
      _______, _______,    LEFT,    DOWN,    RGHT, _______,    _______,      _______,       MPLY,    MNXT,    MUTE,    VOLD,    VOLU, _______,
  //|--------+--------+--------+--------+--------+--------+--+--------|    |--------+--+--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,    _______,      _______,    _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--+--------|    |--------+--+--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______,    _______, _______,      _______,    _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--+--------+--------|    |--------+--+--------+--------+--------+--------+--------+--------|
                           VOLD,    VOLU,             _______, _______,      _______,    _______,               UP,    DOWN
  //                      Rotary Left               |--------+--------|    |--------+-----------+              Rotary Right
      ),

  /* ADJ
   * ,------------------------------------------------.  ,------------------------------------------------.
   * |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------|------|  |------|------+------+------+------+------+------|
   * |      | Sat+ | Val+ | Hue+ |Speed+|Toggle|      |  |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------|------|  |------|------+------+------+------+------+------|
   * |      | Sat- | Val- | Hue- |Speed-|Reset |      |  |      |      |QWERTY| COLE |      |      |      |
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   *                                    |      |      |  |      |      |
   *                                    `-------------'  `-------------'
   */

  [_ADJ] =  LAYOUT( \
  //,--------+--------+--------+--------+--------+--------+--+--------+.   ,--------+--+--------+--------+--------+--------+--------+--------+
        RESET, _______, _______, _______, _______, _______,    _______,      _______,    _______, _______, _______, _______, _______,   RESET, \
  //|--------+--------+--------+--------+--------+--------+--+--------|    |--------+--+--------+--------+--------+--------+--------+--------|
      _______, RGB_SAI, RGB_VAI, RGB_HUI, RGB_SPI, RGB_TOG,    _______,      _______,    _______, _______, _______, _______, _______, _______, \
  //|--------+--------+--------+--------+--------+--------+--+--------|    |--------+--+--------+--------+--------+--------+--------+--------|
      _______, RGB_SAD, RGB_VAD, RGB_HUD, RGB_SPD,  RGBRST,    _______,      _______,    _______, _______, _______, _______, _______, _______, \
  //|--------+--------+--------+--------+--------+--------+--+--------|    |--------+--+--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,    _______,      _______,    _______, _______, _______, _______, _______, _______, \
  //|--------+--------+--------+--------+--------+--------+--+--------|    |--------+--+--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______,    _______, _______,      _______, _______,    _______, _______, _______, _______, _______, \
  //|--------+--------+--------+--------+--------+--+--------+--------|    |--------+--------+--+--------+--------+--------+--------+--------|
                        _______, _______,             _______, _______,      _______, _______,             _______, _______ \
  //                      Rotary Left               |--------+--------|    |--------+--------+              Rotary Right
      )
};


// define variables for reactive RGB
bool TOG_STATUS = false;
int RGB_current_mode;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case FN:
      if (record->event.pressed) {
        layer_on(_FN);
      } else {
        layer_off(_FN);
      }
      return false;
      break;
    case ADJ:
        if (record->event.pressed) {
          layer_on(_ADJ);
        } else {
          layer_off(_ADJ);
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

void matrix_scan_user(void) {
  #ifdef SSD1306OLED
    // led_test_init();
    iota_gfx_task();  // this is what updates the display continuously
  #endif
}


//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// hook point for 'led_test' keymap
//   'default' keymap's led_test_init() is empty function, do nothing
//   'led_test' keymap's led_test_init() force rgblight_mode_noeeprom(35);
__attribute__ ((weak))
void led_test_init(void) {}

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
#define L_ADJ_TRI (L_ADJ|L_FN)

static void render_logo(struct CharacterMatrix *matrix) {

  static char logo[]={
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,
    0};
  matrix_write(matrix, logo);
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
           matrix_write_P(matrix, PSTR("Laser"));
           break;
        case L_FN:
           matrix_write_P(matrix, PSTR("Function"));
           break;
        case L_ADJ:
        case L_ADJ_TRI:
           matrix_write_P(matrix, PSTR("Adjustment"));
           break;
        default:
           matrix_write(matrix, buf);
    }

  // Host Keyboard LED Status
  char led[40];
    snprintf(led, sizeof(led), "\n%s  %s  %s",
            (host_keyboard_leds() & (1<<USB_LED_NUM_LOCK)) ? "NUMLOCK" : "       ",
            (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) ? "CAPS" : "    ",
            (host_keyboard_leds() & (1<<USB_LED_SCROLL_LOCK)) ? "SCLK" : "    ");
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

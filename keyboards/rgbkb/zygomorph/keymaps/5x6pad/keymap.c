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
    _MACROPAD,
    _FN,
    _ADJ
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  MACROPAD,
  FN,
  ADJ,
  BACKLIT,
  RGBRST
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};



#define FN_ESC  LT(_FN, KC_ESC)
#define FN_CAPS  LT(_FN, KC_CAPS)
// Define your non-alpha grouping in this define's LAYOUT, and all your BASE_LAYERS will share the same mod/macro columns

#define BASE_LAYOUT( \
  _00, _01, _02, _03, _04, \
  _10, _11, _12, _13, _14, \
  _20, _21, _22, _23, _24, \
  _30, _31, _32, _33, _34 \
) \
LAYOUT_ortho_5x6( \
      KC_GESC, _00,     _01,     _02,     _03,     _04, \
      KC_TAB,  _10,     _11,     _12,     _13,     _14, \
      FN_CAPS, _20,     _21,     _22,     _23,     _24, \
      KC_LSFT, _30,     _31,     _32,     _33,     _34, \
      KC_LCTL, KC_LGUI, KC_LALT, RGB_TOG, ADJ,  KC_SPC \
)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = BASE_LAYOUT(
      KC_1,    KC_2,    KC_3,    KC_4,    KC_5,
      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,
      KC_A,    KC_S,    KC_D,    KC_F,    KC_G,
      KC_Z,    KC_X,    KC_C,    KC_V,    KC_B
  ),

  [_MACROPAD] = BASE_LAYOUT(
      KC_F13,    KC_F14,    KC_F15,    KC_F16,    KC_F17,
      KC_F18,    KC_F19,    KC_F20,    KC_F21,    KC_F22,
      KC_A,    KC_S,    KC_D,    KC_F,    KC_G,
      KC_Z,    KC_X,    KC_C,    KC_V,    KC_B
  ),

  [_FN] = LAYOUT_ortho_5x6(
      KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,
      _______, KC_PGDN, KC_UP,   KC_PGUP, _______, _______,
      _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,
      _______, _______, _______, _______, _______, _______,
      _______, _______, _______, RGB_MOD, _______, _______
      ),

  [_ADJ] =  LAYOUT_ortho_5x6(
      KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,
      _______, RGB_SAD, RGB_VAI, RGB_SAI, QK_BOOT, _______,
      _______, RGB_HUD, RGB_VAD, RGB_HUI, RGBRST,  _______,
      _______, _______, _______, _______, _______, _______,
      _______, _______, _______, RGB_MOD, _______, _______
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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  //uint8_t shifted = get_mods() & (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT));

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case MACROPAD:
      if(record->event.pressed) {
        set_single_persistent_default_layer(_MACROPAD);
      }
      return false;
      break;
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
        case L_FN:
           matrix_write_P(matrix, PSTR("FN"));
           break;
        case L_ADJ:
        case L_ADJ_TRI:
           matrix_write_P(matrix, PSTR("ADJ"));
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

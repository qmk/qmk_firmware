#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

// NICOLA親指シフト
#include "nicola.h"
NGKEYS nicola_keys;
// NICOLA親指シフト

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
// NICOLA親指シフト
  _NICOLA, // NICOLA親指シフト入力レイヤー
// NICOLA親指シフト
    _LOWER,
    _RAISE,
    _ADJUST
};

enum custom_keycodes {
  QWERTY = NG_SAFE_RANGE,
  COLEMAK,
  DVORAK,
  LOWER,
  RAISE,
  ADJUST,
  BACKLIT,
  EISU,
  KANA,
  RGBRST
};


enum macro_keycodes {
  KC_SAMPLEMACRO,
};

//Macros
#define M_SAMPLE M(KC_SAMPLEMACRO)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT( \
      KC_ESC,  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   /**/     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, \
      KC_TAB,  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,   /**/     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, \
      KC_CAPS, KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,   /**/     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,  _______, \
      KC_LSFT, KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   /**/     KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_LSFT , KC_UP,    _______,    \
      KC_LCTL,  KC_LGUI, KC_LALT, LOWER,   KC_SPC, KC_LGUI,  ADJUST,   /**/     RAISE, KC_SPC, KC_ENT,  KC_BSPC, KC_DEL,  KC_LEFT, KC_DOWN, KC_RGHT,   _______ \
      ),
  [_NICOLA] = LAYOUT( \
      KC_ESC,  KC_GRV,  KC_1,    KC_2,  KC_3,     KC_4,    KC_5,    /**/    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, \
      KC_TAB,  KC_TAB,  NG_Q,    NG_W,  NG_E,     NG_R,    NG_T,    /**/    NG_Y,    NG_U,    NG_I,    NG_O,    NG_P,    KC_LBRC, KC_RBRC, KC_BSLS, \
      KC_CAPS, KC_LCTL, NG_A,    NG_S,  NG_D,     NG_F,    NG_G,    /**/    NG_H,    NG_J,    NG_K,    NG_L,    NG_SCLN, KC_QUOT, KC_ENT,  _______, \
      KC_LSFT, KC_LSFT, NG_Z,    NG_X,  NG_C,     NG_V,    NG_B,    /**/    NG_N,    NG_M,    NG_COMM, NG_DOT,  NG_SLSH, KC_LSFT , KC_UP,    _______,    \
      _______, _______, _______, LOWER, NG_SHFTL, KC_LGUI, EISU,    /**/    RAISE,   NG_SHFTR, KC_ENT ,KC_BSPC, KC_DEL,  KC_LEFT, KC_DOWN, KC_RGHT,   _______ \
      ),
  [_LOWER] = LAYOUT( \
      _______,       _______,       KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      /**/ KC_F6,    KC_F7,        KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, \
      _______,       LGUI(KC_TAB),  LGUI(KC_Q), LGUI(KC_W), LGUI(KC_E), LGUI(KC_R), LGUI(KC_T), /**/ KC_PGUP,  KC_HOME,      KC_UP,   KC_END,  _______, _______, _______, _______, \
      LGUI(KC_CAPS), LGUI(KC_LCTL), LGUI(KC_A), LGUI(KC_S), LGUI(KC_D), EISU,       LGUI(KC_G), /**/ KC_PGDN,  KC_LEFT,      KC_DOWN, KC_RGHT, _______, _______, _______, _______, \
      RGB_TOG,       _______,       LGUI(KC_Z), LGUI(KC_X), LGUI(KC_C), LGUI(KC_V), LGUI(KC_B), /**/ _______,  KC_BTN1,      KC_BTN2, KC_BTN3, _______, RGB_TOG, KC_UP,    _______,    \
      _______,       _______,       _______,    _______,    _______,    _______,     _______,   /**/ _______,  KANA,    LGUI(KC_ENT), _______, _______, KC_LEFT, KC_DOWN, KC_RGHT,_______\
      ),
  [_RAISE] = LAYOUT( \
      _______, _______, _______, _______, _______,  _______,  _______, /**/ _______,  _______,  _______, _______, _______, _______, _______, _______, \
      _______, _______, RESET,   RGBRST,  AU_ON,    AU_OFF,   AG_NORM, /**/ _______,  _______,  _______, _______, _______, _______, _______, _______, \
      _______, _______, RGB_TOG, RGB_HUI, RGB_SAI,  RGB_VAI,  _______, /**/ _______,  _______,  KC_MPRV, KC_VOLU, _______, _______, _______, _______, \
      _______, _______, RGB_MOD, RGB_HUD, RGB_SAD,  RGB_VAD,  _______, /**/ RGB_TOG,  _______,  KC_MNXT, KC_VOLD, KC_MPLY, _______, KC_UP,    _______,    \
      _______, _______, _______, _______, _______,  _______,  _______, /**/ _______,  _______,  _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT,  _______\
      ),
  [_ADJUST] =  LAYOUT( \
      _______, _______, _______, _______, _______,  _______,  _______, /**/ _______,  _______,  _______, _______, _______, _______, _______, _______, \
      _______, _______, _______, _______, _______,  _______,  _______, /**/ _______,  _______,  _______, _______, _______, _______, _______, _______, \
      _______, _______, _______, KC_BTN3, KC_BTN2,  KC_BTN1,  _______, /**/ _______,  _______,  _______, _______, _______, _______, _______, _______, \
      _______, _______, _______, _______, _______,  _______,  _______, /**/ _______,  _______,  _______, _______, _______, _______, _______, _______, \
      _______, _______, _______, _______, _______,  _______,  _______, /**/ _______,  _______,  _______, _______, _______, _______, _______, _______,  _______\
      )
};



#ifdef AUDIO_ENABLE

float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
float tone_plover[][2]     = SONG(PLOVER_SOUND);
float tone_plover_gb[][2]  = SONG(PLOVER_GOODBYE_SOUND);
float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);
#endif

// define variables for reactive RGB
bool TOG_STATUS = false;
int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
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
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
          //not sure how to have keyboard check mode and set it to a variable, so my work around
          //uses another variable that would be set to true after the first time a reactive key is pressed.
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
          #ifdef RGBLIGHT_ENABLE
            //rgblight_mode(RGBLIGHT_MODE_SNAKE + 1);
          #endif
        }
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        #ifdef RGBLIGHT_ENABLE
          //rgblight_mode(RGB_current_mode);   // revert RGB to initial mode prior to RGB mode change
        #endif
        TOG_STATUS = false;
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        //not sure how to have keyboard check mode and set it to a variable, so my work around
        //uses another variable that would be set to true after the first time a reactive key is pressed.
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
          #ifdef RGBLIGHT_ENABLE
            //rgblight_mode(RGBLIGHT_MODE_SNAKE);
          #endif
        }
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        #ifdef RGBLIGHT_ENABLE
          //rgblight_mode(RGB_current_mode);  // revert RGB to initial mode prior to RGB mode change
        #endif
        layer_off(_RAISE);
        TOG_STATUS = false;
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
      //led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
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
    case EISU:
      if (record->event.pressed) {
        // NICOLA親指シフト
        nicola_off();
        // NICOLA親指シフト
      }
      return false;
      break;
    case KANA:
      if (record->event.pressed) {
        // NICOLA親指シフト
        nicola_on();
        // NICOLA親指シフト
      }
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
  #ifdef CONSOLE_ENABLE
            uprintf("key input = %d %d %d %d, %d %d\n",
                    keycode,record,nicola_state(),IS_LAYER_ON(_NICOLA),NG_F,KC_F);
    #endif
  // NICOLA親指シフト
  if (nicola_state()) {
    nicola_mode(keycode, record);
    return process_nicola(keycode, record);
  }
  // NICOLA親指シフト
  return true;
}

void matrix_init_user(void) {
    #ifdef AUDIO_ENABLE
        startup_user();
    #endif
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
    #ifdef CONSOLE_ENABLE
        uprintf("nicola init = %d\n",_NICOLA);
    #endif
    persistent_default_layer_set(1UL<<_QWERTY);
    // NICOLA親指シフト
    set_nicola(_NICOLA);
    // NICOLA親指シフト
}


#ifdef AUDIO_ENABLE

void startup_user()
{
    _delay_ms(20); // gets rid of tick
}

void shutdown_user()
{
    _delay_ms(150);
    stop_all_notes();
}

void music_on_user(void)
{
    music_scale_user();
}

void music_scale_user(void)
{
    PLAY_SONG(music_scale);
}

#endif


//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

void matrix_scan_user(void) {
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
#define L_LOWER (1<<_LOWER)
#define L_RAISE (1<<_RAISE)
#define L_ADJUST (1<<_ADJUST)
#define L_ADJUST_TRI (L_ADJUST|L_RAISE|L_LOWER)

static void render_logo(struct CharacterMatrix *matrix) {
// static const char helix_logo[] PROGMEM ={
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff,
// 0xff, 0x80, 0x80, 0x00, 0xfe, 0xff, 0x30, 0x18, 0x18, 0x88, 0xc0, 0xe0, 0xe0, 0xe0, 0xe0, 0xc0,
// 0x80, 0x80, 0xc0, 0xe0, 0xe0, 0xe0, 0xe0, 0xc0, 0x03, 0xff, 0xff, 0xe0, 0x60, 0x60, 0xe0, 0xe0,
// 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff,
// 0xff, 0x01, 0x01, 0x00, 0x1f, 0xbf, 0x38, 0x30, 0x36, 0x1f, 0x1f, 0x3e, 0x36, 0x33, 0x33, 0x19,
// 0x06, 0x1f, 0x9f, 0x38, 0x30, 0xb0, 0x30, 0x18, 0x00, 0x3f, 0x3f, 0x00, 0x00, 0x00, 0x3f, 0x3f,
// 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x07, 0x03,
// 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x03, 0x00, 0x02, 0x03,
// 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x03, 0x03, 0x00, 0x03,
// 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
// matrix_write_P(matrix, helix_logo);


  matrix_write_P(matrix, PSTR("J-Tech Creations,Inc\n3D Printed Split v1.0\n"));
}

static void render_rgbled_status(bool full, struct CharacterMatrix *matrix) {
#ifdef RGBLIGHT_ENABLE
  char buf[30];
  if (RGBLIGHT_MODES > 1 && rgblight_config.enable) {
      if (full) {
          snprintf(buf, sizeof(buf), " LED %2d: %d,%d,%d ",
                   rgblight_config.mode,
                   rgblight_config.hue/RGBLIGHT_HUE_STEP,
                   rgblight_config.sat/RGBLIGHT_SAT_STEP,
                   rgblight_config.val/RGBLIGHT_VAL_STEP);
      } else {
          snprintf(buf, sizeof(buf), "[%2d] ",rgblight_config.mode);
      }
      matrix_write(matrix, buf);
  }
#endif
}

static void render_layer_status(struct CharacterMatrix *matrix) {
  // Define layers here, Have not worked out how to have text displayed for each layer. Copy down the number you see and add a case for it below
  matrix_write_P(matrix, PSTR("Layer: "));
    switch (layer_state) {
        case L_BASE:
           matrix_write_P(matrix, PSTR("Default"));
           break;
        case L_RAISE:
           matrix_write_P(matrix, PSTR("Raise"));
           break;
        case L_LOWER:
           matrix_write_P(matrix, PSTR("Lower"));
           break;
        case L_ADJUST:
        case L_ADJUST_TRI:
           matrix_write_P(matrix, PSTR("Adjust"));
           break;
        default:
           matrix_write_P(matrix, PSTR("NICOLA"));
           //snprintf(buf,sizeof(buf), "%ld", layer_state);
           //matrix_write(matrix, buf);
    }
}

void render_status(struct CharacterMatrix *matrix) {

  // Render to mode icon
  static const char os_logo[][2][3] PROGMEM  ={{{0x95,0x96,0},{0xb5,0xb6,0}},{{0x97,0x98,0},{0xb7,0xb8,0}}};
  if(keymap_config.swap_lalt_lgui==false){
    matrix_write_P(matrix, os_logo[0][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write_P(matrix, os_logo[0][1]);
  }else{
    matrix_write_P(matrix, os_logo[1][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write_P(matrix, os_logo[1][1]);
  }

  matrix_write_P(matrix, PSTR(" "));
  render_layer_status(matrix);
  matrix_write_P(matrix, PSTR("\n"));

  // Host Keyboardtatus
  matrix_write_P(matrix, (host_keyboard_leds() & (1<<USB_LED_NUM_LOCK)) ?
                 PSTR("NUMLOCK") : PSTR("       "));
  matrix_write_P(matrix, (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) ?
                 PSTR("CAPS") : PSTR("    "));
  matrix_write_P(matrix, (host_keyboard_leds() & (1<<USB_LED_SCROLL_LOCK)) ?
                 PSTR("SCLK") : PSTR("    "));
  matrix_write_P(matrix, PSTR("\n"));
  render_rgbled_status(true, matrix);
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
    render_rgbled_status(false, &matrix);
    render_layer_status(&matrix);
  }
  matrix_update(&display, &matrix);
}

#endif

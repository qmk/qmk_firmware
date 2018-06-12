#include "helix.h"
#include "bootloader.h"
#include "action_layer.h"
#include "eeconfig.h"
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif
#include "LUFA/Drivers/Peripheral/TWI.h"
#ifdef AUDIO_ENABLE
  #include "audio.h"
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

#define DELAY_TIME  75
static uint16_t key_timer;
static uint16_t tap_timer;
static uint16_t delay_registered_code;
static uint8_t delay_mat_row;
static uint8_t delay_mat_col;
static bool delay_key_stat;
static bool delay_key_pressed;
static bool tapping_key;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BASE 0
#define _OPT 1
#define _FUNC 2
#define _SYM 3
#define _NUM 4

bool RGBAnimation = false; //Flag for LED Layer color Refresh.

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  EISU,
  KANA,
  RGBRST,
  RGBOFF,
  RGB1,
  RGB2,
  RGB3,
  OPT_TAP_SP,
  DESKTOP,
  MAC,
  WIN,
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};


// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO
//Macros
#define M_SAMPLE M(KC_SAMPLEMACRO)

#if HELIX_ROWS == 5
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Base
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |  C+z |   ;  |   [  |   (  |   <  |   {  |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | KANA |   P  |   K  |   R  |   A  |   F  |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |  BS  |   D  |   T  |   H  |   E  |   O  |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   Y  |   S  |   N  |   I  |   U  |Space |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Ctrl | Alt  | win  | Sym  | Num  |  OPT | Ent  |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_BASE] = KEYMAP( \
      LCTL(KC_Z),    KC_SCLN,       KC_LBRC,       KC_LPRN,   KC_LT,     KC_LCBR,                                _______,  _______,  _______,  _______,  _______,  _______, \
      KANA,          KC_P,          KC_K,          KC_R,      KC_A,      KC_F,                                   _______,  _______,  _______,  _______,  _______,  _______, \
      KC_BSPC,       KC_D,          KC_T,          KC_H,      KC_E,      KC_O,                                   _______,  _______,  _______,  _______,  _______,  _______, \
      OSM(MOD_LSFT), KC_Y,          KC_S,          KC_N,      KC_I,      KC_U,       KC_SPC, _______,  _______,  _______,  _______,  _______,  _______,  _______, \
      OSM(MOD_LCTL), OSM(MOD_LALT), OSM(MOD_LGUI), MO(_SYM),  MO(_NUM),  OPT_TAP_SP, KC_ENT, _______,  _______,  _______,  _______,  _______,  _______,  _______ \
      ),

  /* Opt
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |  Esc |  :   |  ]   |  )   |  >   |  }   |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |  EISU|   J  |   M  |   B  |   '  |  Tab |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |   .  |   V  |   C  |   L  |   Z  |  Q   |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |   X  |   G  |   W  |   -  |  Del | Esc  |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |   ,  | DTOP |      |      |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_OPT] = KEYMAP( \
      KC_ESC,  KC_COLN,KC_RBRC, KC_RPRN,KC_GT,     KC_RCBR,                   _______,  _______,  _______,  _______,  _______,  _______, \
      EISU,    KC_J,   KC_M,    KC_B,   KC_QUOT,   KC_TAB,                    _______,  _______,  _______,  _______,  _______,  _______, \
      KC_DOT,  KC_V,   KC_C,    KC_L,   KC_Z,      KC_Q,                      _______,  _______,  _______,  _______,  _______,  _______, \
      _______, KC_X,   KC_G,    KC_W,   KC_MINUS,  KC_DEL,  KC_ESC,  _______, _______,  _______,  _______,  _______,  _______,  _______, \
      _______, _______,_______, KC_COMM,DESKTOP,   _______, _______, _______, _______,  _______,  _______,  _______,  _______,  _______ \
      ),

  /* Func
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |RGBRST|  Hue |      |  RST |  Mac |  Win |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | RGB1 | VAL+ |  F7  |  F8  |  F9  |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | RGB2 | VAL- |  F4  |  F5  |  F6  | F12  |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | RGB3 |  F10 |  F1  |  F2  |  F3  | F11  |      |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |RGBOFF|      |      |      |      |      |      |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_FUNC] = KEYMAP( \
      RGBRST,RGB_HUI, _______, RESET,   MAC,     WIN,                         _______,  _______,  _______,  _______,  _______,  _______, \
      RGB1,  RGB_VAI, KC_F7,   KC_F8,   KC_F9,   _______,                     _______,  _______,  _______,  _______,  _______,  _______, \
      RGB2,  RGB_VAD, KC_F4,   KC_F5,   KC_F6,   KC_F12,                      _______,  _______,  _______,  _______,  _______,  _______, \
      RGB3,  KC_F10,  KC_F1,   KC_F2,   KC_F3,   KC_F11,   _______,  _______, _______,  _______,  _______,  _______,  _______,  _______, \
      RGBOFF,_______, _______, _______, _______, _______,  _______,  _______, _______,  _______,  _______,  _______,  _______,  _______ \
      ),

  /* Sym
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |  Ins |  GRV |      |  PU  |  PD  |   ^  |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |   \  |   #  |   =  |   ?  |   %  |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |   $  |  upA |   @  |   !  |   |  |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |  CL  |  <-  |  dwA |  ->  |   _  |   &  |      |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |  PS  |      |   ~  |      |      |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_SYM] = KEYMAP( \
      KC_INS,  KC_GRV,  _______, KC_PGUP, KC_PGDN, KC_CIRC,                   _______,  _______,  _______,  _______,  _______,  _______, \
      _______, KC_BSLS, KC_HASH, KC_EQL,  KC_QUES, KC_PERC,                   _______,  _______,  _______,  _______,  _______,  _______, \
      _______, KC_DLR,  KC_UP,   KC_AT,   KC_EXLM, KC_PIPE,                   _______,  _______,  _______,  _______,  _______,  _______, \
      KC_CAPS, KC_LEFT, KC_DOWN, KC_RIGHT,KC_UNDS, KC_AMPR, _______, _______, _______,  _______,  _______,  _______,  _______,  _______, \
      _______, _______, KC_PSCR, _______, KC_TILD, _______, _______, _______, _______,  _______,  _______,  _______,  _______,  _______ \
      ),

  /* Raise
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |      | Func | home |  End |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |   *  |  7   |  8   |  9   |  -   |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |  .   |   /  |  4   |  5   |  6   |  +   |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |  LN  |  0   |  1   |  2   |  3   |C+S+F1|      |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |  ,   |      |      |      |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_NUM] = KEYMAP( \
      _______,  _______, OSL(_FUNC), KC_HOME, KC_END,  _______,                          _______,  _______,  _______,  _______,  _______,  _______, \
      _______,  KC_ASTR, KC_P7,      KC_P8,   KC_P9,   KC_MINS,                          _______,  _______,  _______,  _______,  _______,  _______, \
      KC_PDOT,  KC_SLSH, KC_P4,      KC_P5,   KC_P6,   KC_PLUS,                          _______,  _______,  _______,  _______,  _______,  _______, \
      KC_NLCK,  KC_P0,   KC_P1,      KC_P2,   KC_P3,   LCTL(S(KC_F1)), _______, _______, _______,  _______,  _______,  _______,  _______,  _______, \
      _______,  _______, KC_PDOT,    KC_COMM, _______, _______,        _______, _______, _______,  _______,  _______,  _______,  _______,  _______ \
      )
};
#else
#error "undefined keymaps"
#endif


#ifdef AUDIO_ENABLE

float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
float tone_plover[][2]     = SONG(PLOVER_SOUND);
float tone_plover_gb[][2]  = SONG(PLOVER_GOODBYE_SOUND);
float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);
#endif

// define variables for reactive RGB
//bool TOG_STATUS = false;
int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool find_mairix(uint16_t keycode, uint8_t *row, uint8_t *col){
  for(uint8_t i=0; i<MATRIX_ROWS; i++){
    for(uint8_t j=0; j<MATRIX_COLS; j++){
      if( pgm_read_word(&(keymaps[_BASE][i][j]))==keycode){
        *row = i;
        *col = j;
        return true;
      }
    }
  }
  return false;
}

void unregister_delay_code(void){
  if(delay_registered_code){
    unregister_code(delay_registered_code);
    if (delay_registered_code & QK_LSFT){
      unregister_code(KC_LSFT);
    }
    if (delay_registered_code & QK_LCTL){
      unregister_code(KC_LCTL);
    }
    if (delay_registered_code & QK_LALT){
      unregister_code(KC_LALT);
    }
    if (delay_registered_code & QK_LGUI){
      unregister_code(KC_LGUI);
    }
    delay_registered_code=0;
  }
}

void register_delay_code(uint8_t layer){
  if(delay_key_stat){
    unregister_delay_code();

    uint16_t code = pgm_read_word(&(keymaps[layer][delay_mat_row][delay_mat_col]));
    if (code & QK_LSFT){
      register_code(KC_LSFT);
    }
    if (code & QK_LCTL){
      register_code(KC_LCTL);
    }
    if (code & QK_LALT){
      register_code(KC_LALT);
    }
    if (code & QK_LGUI){
      register_code(KC_LGUI);
    }
    register_code(code);
    delay_registered_code = code;
    delay_key_stat = false;
    tapping_key = true;
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  if(tap_timer&&keycode!=OPT_TAP_SP){
    tapping_key = true;
  }

  if(keycode==delay_registered_code){
      if (!record->event.pressed){
        unregister_delay_code();
      }
  }

  switch (keycode) {
    case KC_SCLN:
    case KC_LBRC:
    case KC_LPRN:
    case KC_LT:
    case KC_LCBR:
    case KC_P:
    case KC_K:
    case KC_R:
    case KC_A:
    case KC_F:
    case KC_BSPC:
    case KC_D:
    case KC_T:
    case KC_H:
    case KC_E:
    case KC_O:
    case KC_Y:
    case KC_S:
    case KC_N:
    case KC_I:
    case KC_U:
    case LCTL(KC_Z):
    case KC_SPC:
      if (record->event.pressed) {
        register_delay_code(_BASE);
        if(find_mairix(keycode, &delay_mat_row, &delay_mat_col)){
          key_timer = timer_read();
          delay_key_stat = true;
          delay_key_pressed = true;
        }
      }else{
        delay_key_pressed = false;
      }
      return false;
      break;
    case OPT_TAP_SP:
      if (record->event.pressed) {
        tapping_key = false;
        register_delay_code(_OPT);
        layer_on(_OPT);
        tap_timer = timer_read();
      }else{
        layer_off(_OPT);
        if(tapping_key==false && timer_elapsed(tap_timer) < TAPPING_TERM){
          SEND_STRING(" ");
        }
        tap_timer = 0;
      }
      return false;
      break;
   case EISU:
      if (record->event.pressed) {
        if(keymap_config.swap_lalt_lgui==false){
          register_code(KC_LANG2);
        }else{
          SEND_STRING(SS_LALT("`"));
        }
      } else {
        unregister_code(KC_LANG2);
      }
      return false;
      break;
    case KANA:
      if (record->event.pressed) {
        if(keymap_config.swap_lalt_lgui==false){
          register_code(KC_LANG1);
        }else{
          SEND_STRING(SS_LALT("`"));
        }
      } else {
        unregister_code(KC_LANG1);
      }
      return false;
      break;
    case DESKTOP:
      if (record->event.pressed) {
        if(keymap_config.swap_lalt_lgui==false){
          register_code(KC_F11);
        }else{
          SEND_STRING(SS_LGUI("d"));
        }
      } else {
        unregister_code(KC_F11);
      }
      return false;
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
          RGBAnimation = false;
        }
      #endif
      break;
    case RGBOFF:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_disable();
        }
      #endif
      break;
    case RGB1:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          RGBAnimation = true;
          rgblight_mode(6);
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
    case RGB2:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          RGBAnimation = true;
          rgblight_mode(10);
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
    case RGB3:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          RGBAnimation = true;
          rgblight_mode(21);
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
    case MAC:
      if (record->event.pressed) {
        keymap_config.swap_lalt_lgui = false;
        keymap_config.swap_ralt_rgui = false;
        #ifdef AUDIO_ENABLE
          PLAY_SONG(ag_norm_song);
        #endif
      }
      break;
    case WIN:
      if (record->event.pressed) {
        keymap_config.swap_lalt_lgui = true;
        keymap_config.swap_ralt_rgui = true;
        #ifdef AUDIO_ENABLE
          PLAY_SONG(ag_swap_song);
        #endif
      }
      break;
    }
  return true;
}


//keyboard start-up code. Runs once when the firmware starts up.
void matrix_init_user(void) {
    #ifdef AUDIO_ENABLE
        startup_user();
    #endif
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        TWI_Init(TWI_BIT_PRESCALE_1, TWI_BITLENGTH_FROM_FREQ(1, 800000));
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
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


//assign the right code to your layers for OLED display
#define L_BASE 0
#define L_OPT 2
#define L_FUNC 4
#define L_SYM 8
#define L_NUM 16
#define L_FNLAYER 64
#define L_NUMLAY 128
#define L_NLOWER 136
#define L_NFNLAYER 192
#define L_MOUSECURSOR 256


uint8_t layer_state_old;

//runs every scan cycle (a lot)
void matrix_scan_user(void) {
  #ifdef SSD1306OLED
    iota_gfx_task();  // this is what updates the display continuously
  #endif

  if(delay_key_stat && (timer_elapsed(key_timer) > DELAY_TIME)){
    register_delay_code(_BASE);
    if(!delay_key_pressed){
      unregister_delay_code();
    }
  }

  if(layer_state_old != layer_state){
    switch (layer_state) {
      case L_BASE:
        #ifdef RGBLIGHT_ENABLE
          if (!RGBAnimation){
            rgblight_sethsv(187,255,255);
            rgblight_mode(1);
          }else{
            rgblight_mode(RGB_current_mode);
          }
        #endif
        break;
      case L_OPT:
        register_delay_code(_OPT);
        break;
      case L_NUM:
        register_delay_code(_NUM);
        #ifdef RGBLIGHT_ENABLE
          rgblight_sethsv(25,255,255);
          rgblight_mode(1);
        #endif
        break;
      case L_SYM:
        register_delay_code(_SYM);
        #ifdef RGBLIGHT_ENABLE
          rgblight_sethsv(96,255,255);
          rgblight_mode(1);
        #endif
        break;
      case L_FUNC:
        register_delay_code(_FUNC);
        #ifdef RGBLIGHT_ENABLE
          rgblight_sethsv(331,255,255);
          rgblight_mode(1);
        #endif
        break;
    }
    layer_state_old = layer_state;
  }
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

void matrix_update(struct CharacterMatrix *dest,
                          const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

// Render to OLED
void render_status(struct CharacterMatrix *matrix) {

  // froggy logo
  static char logo[4][1][17]=
  {
    {
      {0x65,0x66,0x67,0x68,0x69,0x6a,0x6b,0x6c,0x6d,0x6e,0x6f,0x70,0x71,0x72,0x73,0x74,0}
    },
    {
      {0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,0}
    },
    {
      {0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,0}
    },
    {
      {0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0}
    }
  };

  static char indctr[8][2][4]=
  {
    // white icon
    {
      {0x60,0x61,0x62,0},
      {0x63,0x64,0}
    },
    {
      {0x80,0x81,0x82,0},
      {0x83,0x84,0}
    },
    {
      {0xa0,0xa1,0xa2,0},
      {0xa3,0xa4,0}
    },
    {
      {0xc0,0xc1,0xc2,0},
      {0xc3,0xc4,0}
    },
    // Black icon
    {
      {0x75,0x76,0x77,0},
      {0x78,0x79,0}
    },
    {
      {0x95,0x96,0x97,0},
      {0x98,0x99,0}
    },
    {
      {0xb5,0xb6,0xb7,0},
      {0xb8,0xb9,0}
    },
    {
      {0xd5,0xd6,0xd7,0},
      {0xd8,0xd9,0}
    },
  };

  int rown = 0;
  int rowf = 0;
  int rowa = 0;
  int rows = 0;

  //Set Indicator icon
  if (host_keyboard_leds() & (1<<USB_LED_NUM_LOCK)) { rown = 4; } else { rown = 0; }
  if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) { rowa = 4; } else { rowa = 0; }
  if (host_keyboard_leds() & (1<<USB_LED_SCROLL_LOCK)) { rows = 4; } else { rows = 0; }
  if (layer_state == L_FUNC) { rowf = 4; }

  matrix_write(matrix, indctr[rown]  [0]);
  matrix_write(matrix, indctr[rowf]  [1]);
  matrix_write(matrix, logo  [0]     [0]);
  matrix_write(matrix, indctr[rown+1][0]);
  matrix_write(matrix, indctr[rowf+1][1]);
  matrix_write(matrix, logo  [1]     [0]);
  matrix_write(matrix, indctr[rowa+2][0]);
  matrix_write(matrix, indctr[rows+2][1]);
  matrix_write(matrix, logo  [2]     [0]);
  matrix_write(matrix, indctr[rowa+3][0]);
  matrix_write(matrix, indctr[rows+3][1]);
  matrix_write(matrix, logo  [3]     [0]);

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
  }
  matrix_update(&display, &matrix);
}

#endif

// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

#include QMK_KEYBOARD_H
#include "keymap_jis2us.h"
#include "action_pseudo_lut.h"
#ifdef SSD1306OLED
  #include "ssd1306.h"
  #include "keylogger.c"
#endif

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum comet46_layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _PSEUDO_US,
    _PSEUDO_US_LOWER,
    _PSEUDO_US_RAISE,
    _ADJUST
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  PSEUDO_US,
};

#define KC_LWR MO(_LOWER)
#define KC_RSE MO(_RAISE)
#define KC_P_LW MO(_PSEUDO_US_LOWER)
#define KC_P_RS MO(_PSEUDO_US_RAISE)
#define KC_QWRT QWERTY
#define KC_P_US PSEUDO_US
#define KC_SPCT CTL_T(KC_SPC)
#define KC_ENSF SFT_T(KC_ENT)
#define KC_IMON ALT_T(KC_F13)
#define KC_IMOF GUI_T(KC_F14)
#define KC_SRO S(KC_RO)
#define KC_SYEN S(KC_JYEN)
#define KC_CAD LCA(KC_DEL)
#define KC_RST RESET
// Fillers to make layering more clear
#define KC_ KC_TRNS 
#define KC_XXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_kc(  
  //,----+----+----+----+----+----+               +----+----+----+----+----+----.
     ESC , Q  , W  , E  , R  , T  ,                 Y  , U  , I  , O  , P  ,DEL ,
  //|----+----+----+----+----+----+----+     +----+----+----+----+----+----+----|
     TAB , A  , S  , D  , F  , G  ,LPRN,      RPRN, H  , J  , K  , L  ,SCLN,BSPC,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
     LSFT, Z  , X  , C  , V  , B  ,LBRC,      RBRC, N  , M  ,COMM,DOT ,SLSH,QUOT,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
                         IMOF,LWR ,SPCT,      ENSF,RSE ,IMON
  //                    +----+----+---/       \---+----+----+
  ),

  [_LOWER] = LAYOUT_kc(  
  //,----+----+----+----+----+----+               +----+----+----+----+----+----.
         ,EXLM, AT ,HASH,DLR ,PERC,                CIRC,AMPR,ASTR,LPRN,RPRN,    ,
  //|----+----+----+----+----+----+----+     +----+----+----+----+----+----+----|
         , F1 , F2 , F3 , F4 , F5 , F6 ,      GRV ,BSLS,MINS,EQL ,LBRC,RBRC,    ,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
         , F7 , F8 , F9 , F10, F11, F12,      TILD,PIPE,UNDS,PLUS,LCBR,RCBR,    ,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
                             ,    ,    ,          ,    ,    
  //                    +----+----+---/       \---+----+----+
  ),

  [_RAISE] = LAYOUT_kc(  
  //,----+----+----+----+----+----+               +----+----+----+----+----+----.
         , 1  , 2  , 3  , 4  , 5  ,                 6  , 7  , 8  , 9  , 0  ,    ,
  //|----+----+----+----+----+----+----+     +----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,      XXXX,LEFT,DOWN, UP ,RGHT,END ,    ,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,      HOME,XXXX,XXXX,XXXX,XXXX,XXXX,    ,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
                             ,    ,    ,          ,    ,    
  //                    +----+----+---/       \---+----+----+
  ),

  [_PSEUDO_US] = LAYOUT_kc(  
  //,----+----+----+----+----+----+               +----+----+----+----+----+----.
     ESC , Q  , W  , E  , R  , T  ,                 Y  , U  , I  , O  , P  ,DEL ,
  //|----+----+----+----+----+----+----+     +----+----+----+----+----+----+----|
     TAB , A  , S  , D  , F  , G  ,ASTR,      LPRN, H  , J  , K  , L  ,FN0 ,BSPC,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
     LSFT, Z  , X  , C  , V  , B  ,FN0 ,      FN0 , N  , M  ,COMM,DOT ,SLSH,FN0 ,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
                         IMOF,P_LW,SPCT,      ENSF,P_RS,IMON
  //                    +----+----+---/       \---+----+----+
  ),


  [_PSEUDO_US_LOWER] = LAYOUT_kc(  
  //,----+----+----+----+----+----+               +----+----+----+----+----+----.
         ,EXLM,LBRC,HASH,DLR ,PERC,                EQL ,CIRC, DQT,ASTR,LPRN,    ,
  //|----+----+----+----+----+----+----+     +----+----+----+----+----+----+----|
         , F1 , F2 , F3 , F4 , F5 , F6 ,      LCBR,JYEN,MINS,UNDS,RBRC,BSLS,    ,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
         , F7 , F8 , F9 , F10, F11, F12,      PLUS,SYEN,SRO ,COLN,RCBR,PIPE,    ,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
                             ,    ,    ,          ,    ,    
  //                    +----+----+---/       \---+----+----+
  ),

  [_PSEUDO_US_RAISE] = LAYOUT_kc(  
  //,----+----+----+----+----+----+               +----+----+----+----+----+----.
         , 1  , 2  , 3  , 4  , 5  ,                 6  , 7  , 8  , 9  , 0  ,    ,
  //|----+----+----+----+----+----+----+     +----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    , GRV,      XXXX,LEFT,DOWN, UP ,RGHT,END ,    ,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,      HOME,XXXX,XXXX,XXXX,XXXX,XXXX,    ,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
                             ,    ,    ,          ,    ,    
  //                    +----+----+---/       \---+----+----+
  ),

  [_ADJUST] = LAYOUT_kc(  
  //,----+----+----+----+----+----+               +----+----+----+----+----+----.
         ,    ,    ,    ,    ,    ,                    ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----+     +----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,CAD ,      QWRT,    ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,RST ,      P_US,    ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
                             ,    ,    ,          ,    ,    
  //                    +----+----+---/       \---+----+----+
  )

};


/*
 * user defined action function
 */
enum function_id {
    PSEUDO_US_FUNCTION,
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
    switch (id)
    {
    case PSEUDO_US_FUNCTION:
        action_pseudo_lut(record, _QWERTY, keymap_jis2us);
        break;
    }
}

/*
 * Fn action definition
 */
const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_FUNCTION(PSEUDO_US_FUNCTION),
};

uint32_t layer_state_set_user(uint32_t state) {
  switch (biton32(state)) {
    case _PSEUDO_US_LOWER:
    case _PSEUDO_US_RAISE: 
      return update_tri_layer_state(state, _PSEUDO_US_RAISE, _PSEUDO_US_LOWER, _ADJUST);
      break;
    default:
      return update_tri_layer_state(state, _RAISE, _LOWER, _ADJUST);
      break;
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  #ifdef SSD1306OLED
    if (record->event.pressed) {
      set_keylog(keycode, record);
    }
  #endif
    switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case PSEUDO_US:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_PSEUDO_US);
      }
      return false;
      break;
  }
  return true;
}


//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

void matrix_init_user(void) {
  iota_gfx_init(false);   // turns on the display
}

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

// static void render_logo(struct CharacterMatrix *matrix) {

//   static char logo[]={
//     0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
//     0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
//     0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,
//     0};
//   matrix_write(matrix, logo);
//   //matrix_write_P(&matrix, PSTR(" Split keyboard kit"));
// }



void render_status(struct CharacterMatrix *matrix) {

  // Define layers here, Have not worked out how to have text displayed for each layer. Copy down the number you see and add a case for it below
  char buf[40];
  snprintf(buf,sizeof(buf), "Undef-%ld", layer_state);
  matrix_write_P(matrix, PSTR("Layer: "));
  uint8_t layer = biton32(layer_state);
  uint8_t default_layer = eeconfig_read_default_layer();
    switch (layer) {
        case _RAISE:
           matrix_write_P(matrix, PSTR("Raise"));
           break;
        case _LOWER:
           matrix_write_P(matrix, PSTR("Lower"));
           break;
        case _PSEUDO_US_RAISE:
           matrix_write_P(matrix, PSTR("P_US_Raise"));
           break;
        case _PSEUDO_US_LOWER:
           matrix_write_P(matrix, PSTR("P_US_Lower"));
           break;
        case _ADJUST:
           matrix_write_P(matrix, PSTR("Adjust"));
           break;
        default:
          if (default_layer & (1UL << _QWERTY)) {
            matrix_write_P(matrix, PSTR("Qwerty"));
          }
          else if (default_layer & (1UL << _PSEUDO_US)) {
            matrix_write_P(matrix, PSTR("Psuedo_US"));
          }
          else {
            matrix_write(matrix, buf);
          }
          break;
    }

  // Host Keyboard LED Status
  static char ind[3][2][3]={{{0x97,0x98,0},{0xb7,0xb8,0}},//num lock
                           {{0x99,0x9a,0},{0xb9,0xba,0}},//caps lock
                           {{0x9b,0x9c,0},{0xbb,0xbc,0}},};//scroll lock
  static char indoff[]={0};
  bool statn = (host_keyboard_leds() & (1<<USB_LED_NUM_LOCK));
  bool statc = (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK));
  bool stats = (host_keyboard_leds() & (1<<USB_LED_SCROLL_LOCK));
  matrix_write_P(matrix, PSTR("\n"));
  matrix_write(matrix, read_keylog());
  matrix_write_P(matrix, PSTR("\n"));
  matrix_write(matrix, statn ? ind[0][0]:indoff);
  matrix_write(matrix, statc ? ind[1][0]:indoff);
  matrix_write(matrix, stats ? ind[2][0]:indoff);
  matrix_write_P(matrix, PSTR("\n"));
  matrix_write(matrix, statn ? ind[0][1]:indoff);
  matrix_write(matrix, statc ? ind[1][1]:indoff);
  matrix_write(matrix, stats ? ind[2][1]:indoff);
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;

#if DEBUG_TO_SCREEN
  if (debug_enable) {
    return;
  }
#endif

  matrix_clear(&matrix);
  render_status(&matrix);
  matrix_update(&display, &matrix);
}

#endif

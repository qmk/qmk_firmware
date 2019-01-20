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


//#include "wait.h"
#include "klackygears.h"

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

/*#define LAYOUT_helix_base( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, \
    K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A \
  ) \
  LAYOUT_wrapper( \
    KC_LRMOD, K01,        K02, K03,      K04,     K05,                        K06,     K07,     K08,     K09,     K0A,     KC_MINS, \
    KC_ESC,   ALT_T(K11), K12, K13,      K14,     K15,                        K16,     K17,     K18,     K19,     K1A, RGUI_T(KC_QUOT), \
    KC_LSFT,  CTL_T(K21), K22, K23,      K24,     K25,                        K26,     K27,     K28,     K29,  CTL_T(K2A), KC_RSFT, \
    KC_LSFT,  K31,        K32, K33,      K34,     K35,    KC_MCRT2, KC_MCRTG, K36,     K37,     K38,     K39,  K3A,        KC_RSFT,
    KC_ADJS,  KC_TAB, KC_LALT, KC_ENT, KC_ENT, KC_SPSY,   KC_BSNB,  KC_TBNB,  KC_ENSY, KC_ADJS, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT \
    )
#define LAYOUT_helix_base_wrapper(...)       LAYOUT_helix_base(__VA_ARGS__)
*/

//#if HELIX_ROWS == 5
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {



  [_DVRK] = LAYOUT_kc( \
      LRMOD,   _____, _____, _____, _____, _____,                   _____, _____, _____, _____, _____, _____, \
      ESC,     QUOT,    COMQUES, DTEX,    P,       Y,                         F,       G,       C,       R,       L,       _____, \
      LSFT,    A,       O,       E,       U,       I,                         D,       H,       T,       N,       S,       RSFT, \
      LSFT,    CSCN,    ALTQ,    GUIJ,    K,       X,       MCRT2,  MCRTG,    B,       M,       GUIW,    ALTV,    MDAZ,    RSFT, \
      ADJS,    ENT,     LALT,    ENT,     SPSY,    BSNB,    BSNB,   TBNB,     TBNB,    ENSY,    LEFT,    DOWN,    UP,      RGHT \
      ),



  [_SYMB] = LAYOUT_kc( \
      _____, _____, _____, _____, _____, _____,                   _____, _____, _____, _____, _____, _____, \
      _____, BSLS,    AT,      HASH,    DLR,     PERC,                      _____, F9,      F10,     F11,     F12,     _____, \
      _____, PLUS,    MINS,    ASTR,    SLSH,    EQL,                       _____, F5,      F6,      F7,      F8,      _____, \
      _____, LBRC,    RBRC,    LPRN,    RPRN,    AMPR,    _____, _____, GRV,     F1,      F2,      F3,      F4,      _____, \
      _____, _____, _____, _____, SPC,     DEL,     _____, _____, CAPS,    _____, _____, _____, _____, _____ \
      ),


  [_NUMB] = LAYOUT_kc( \
      GRV,     1,       2,       3,       4,       5,                         6,       7,       8,       9,       0,       _____, \
      _____, PGUP,    PGDN,    HOME,    END,     FNDR,                      MINPLS,  7,       8,       9,       COLN,    _____, \
      _____, LEFT,    UP,      DOWN,    RIGHT,   _____,                   DIVMLT,  4,       5,       6,       CSTC,    _____, \
      _____, _____, CTLA,    MCCPY,   MCPIN,   DEL,     _____, _____, DOTEQL,  1,       2,       ALT3,    RWIN,    _____, \
      _____, _____, _____, _____, SPC,     BSPC,    _____, _____, _____, 0,       0,       _____, _____, _____ \
      ),


  [_MDIA] =  LAYOUT_kc( \
      _____, _____, _____, _____, _____, _____,                   LRST,    _____, _____, _____, _____, _____, \
      _____, _____, _____, _____, _____, _____,                   _____, LHUI,    LSAI,    LVAI,    LSPI,    _____, \
      _____, _____, _____, _____, _____, _____,                   LRMOD,   LHUD,    LSAD,    LVAD,    LSPD,    _____, \
      _____, _____, _____, _____, _____, _____, _____, _____, MPLY,    MUTE,    VOLD,    VOLU,    _____, _____, \
      _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____ \
      )
/*
  [_DVRK] = LAYOUT_wrapper( \
      KC_LRMOD,   _________________KC_BLANK__________________,                     _________________KC_BLANK__________________, KC______, \
      KC_ESC,     _________________DVRK_L1___________________,                     _________________DVRK_R1___________________, KC______, \
      KC_LSFT,    _________________DVRK_L2___________________,                     _________________DVRK_R2___________________, KC_RSFT, \
      KC_LSFT,    _________________DVRK_L3___________________, KC_MCRT2, KC_MCRTG, _________________DVRK_R3___________________, KC_RSFT, \
      KC_ADJS,    KC_TAB, KC_LALT, KC_ENT, KC_ENT, KC_SPSY,   KC_BSNB,  KC_TBNB,  KC_ENSY, KC_ADJS, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT \
      ),

  [_QUER] = LAYOUT_wrapper( \
      KC______, _________________NUMBER_L__________________,                      _________________NUMBER_R__________________, KC______, \
      KC______, _________________QWERTY_L1_________________,                      _________________QWERTY_R1_________________, KC______, \
      KC______, _________________QWERTY_L2_________________,                      _________________QWERTY_R2_________________, KC______, \
      KC______, _________________QWERTY_L3_________________,  KC_MCRT2, KC_MCRTG, _________________QWERTY_R3_________________, KC______, \
      KC______, KC_TAB, KC_LCTRL, KC_LALT, KC_LGUI, KC_SPSY,   KC_BSNB, KC_TBNB,   KC_ENSY, KC_RGUI, KC_LEFT,  KC_DOWN,  KC_UP, KC_RIGHT \
      ),


  [_SYMB] = LAYOUT_wrapper( \
      KC______, _________________KC_BLANK__________________,                      _________________KC_BLANK__________________, KC_MAKE, \
      KC______, _________________KC_PUNC_L1________________,                      _________________KC_FUNC_1_________________, KC______, \
      KC______, _________________KC_PUNC_L2________________,                      _________________KC_FUNC_2_________________, KC______, \
      KC______, _________________KC_PUNC_L3________________,  KC______, KC______, _________________KC_FUNC_3_________________, KC______, \
      KC______, KC______, KC______, KC______, KC_SPC, KC_DEL, KC______, KC______, KC_CAPS,  KC______, KC______, KC______, KC______,  KC______ \
      ),


  [_NUMB] = LAYOUT_wrapper( \
      KC_GRV,    _________________KC_BLANK__________________,                       _________________KC_BLANK__________________,    KC______, \
      KC______,  _________________MACARR_L1_________________,                       _________________NUMB_R1___________________,    KC______, \
      KC______,  _________________MACARR_L2_________________,                       _________________NUMB_R2___________________,    KC______, \
      KC______,  _________________MACARR_L3_________________,   KC______, KC______, _________________NUMB_R3___________________,    KC______, \
      KC______,  KC______, KC______, KC______, KC_SPC, KC_BSPC, KC______, KC______, _________________NUMB_R4___________________,    KC______ \
      ),


  [_MDIA] =  LAYOUT_wrapper( \
      KC______, _________________KC_BLANK__________________,                     _________________LYOUT_____________________, KC______, \
      KC______, _________________KC_BLANK__________________,                     _________________RGB_1_____________________, KC______, \
      KC______, _________________KC_BLANK__________________,                     _________________RGB_2_____________________, KC______, \
      KC______, _________________KC_BLANK__________________, KC______, KC______, _________________MEDIA_____________________, KC______, \
      KC______, _________________KC_BLANK__________________, KC______, KC______, _________________KC_BLANK__________________, KC______ \
      )
*/
 };

// #else
// #error "undefined keymaps"
// #endif


#ifdef AUDIO_ENABLE

float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
float tone_plover[][2]     = SONG(PLOVER_SOUND);
float tone_plover_gb[][2]  = SONG(PLOVER_GOODBYE_SOUND);
float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);
#endif



// // define variables for reactive RGB
// bool TOG_STATUS = false;
 int RGB_current_mode;

// void persistent_default_layer_set(uint16_t default_layer) {
//   eeconfig_update_default_layer(default_layer);
//   default_layer_set(default_layer);
// }

// // Setting MDIA layer RGB back to default
// void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
//   if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
//     #ifdef RGBLIGHT_ENABLE
//       //rgblight_mode(RGB_current_mode);
//     #endif
//     layer_on(layer3);
//   } else {
//     layer_off(layer3);
//   }
// }

//bool process_record_user(uint16_t keycode, keyrecord_t *record) {

//  if (!process_record_dynamic_macro(keycode, record)) {
//         return false;
//     }

  // switch (keycode) {

  //     return false;
  //     break;

  //   case _DVORAK:
  //     if (record->event.pressed) {
  //       #ifdef AUDIO_ENABLE
  //         PLAY_SONG(tone_dvorak);
  //       #endif
  //       persistent_default_layer_set(1UL<<_DVORAK);
  //     }
  //     return false;
  //     break;
  //   case _SYMB:
  //     if (record->event.pressed) {
  //         //not sure how to have keyboard check mode and set it to a variable, so my work around
  //         //uses another variable that would be set to true after the first time a reactive key is pressed.
  //       if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
  //       } else {
  //         TOG_STATUS = !TOG_STATUS;
  //         #ifdef RGBLIGHT_ENABLE
  //           //rgblight_mode(RGBLIGHT_MODE_SNAKE + 1);
  //         #endif
  //       }
  //       layer_on(_SYMB);
  //       update_tri_layer_RGB(_SYMB, _NUMB, _MDIA);
  //     } else {
  //       #ifdef RGBLIGHT_ENABLE
  //         //rgblight_mode(RGB_current_mode);   // revert RGB to initial mode prior to RGB mode change
  //       #endif
  //       TOG_STATUS = false;
  //       layer_off(_SYMB);
  //       update_tri_layer_RGB(_SYMB, _NUMB, _MDIA);
  //     }
  //     return false;
  //     break;
  //   case _NUMB:
  //     if (record->event.pressed) {
  //       //not sure how to have keyboard check mode and set it to a variable, so my work around
  //       //uses another variable that would be set to true after the first time a reactive key is pressed.
  //       if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
  //       } else {
  //         TOG_STATUS = !TOG_STATUS;
  //         #ifdef RGBLIGHT_ENABLE
  //           //rgblight_mode(RGBLIGHT_MODE_SNAKE);
  //         #endif
  //       }
  //       layer_on(_NUMB);
  //       update_tri_layer_RGB(_SYMB, _NUMB, _MDIA);
  //     } else {
  //       #ifdef RGBLIGHT_ENABLE
  //         //rgblight_mode(RGB_current_mode);  // revert RGB to initial mode prior to RGB mode change
  //       #endif
  //       layer_off(_NUMB);
  //       TOG_STATUS = false;
  //       update_tri_layer_RGB(_SYMB, _NUMB, _MDIA);
  //     }
  //     return false;
  //     break;
  //   case _MDIA:
  //       if (record->event.pressed) {
  //         layer_on(_MDIA);
  //       } else {
  //         layer_off(_MDIA);
  //       }
  //       return false;
  //       break;
  //     //led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
  //   case RGB_MOD:
  //     #ifdef RGBLIGHT_ENABLE
  //       if (record->event.pressed) {
  //         rgblight_mode(RGB_current_mode);
  //         rgblight_step();
  //         RGB_current_mode = rgblight_config.mode;
  //       }
  //     #endif
  //     return false;
  //     break;
  //   // case EISU:
  //   //   if (record->event.pressed) {
  //   //     if(keymap_config.swap_lalt_lgui==false){
  //   //       register_code(KC_LANG2);
  //   //     }else{
  //   //       SEND_STRING(SS_LALT("`"));
  //   //     }
  //   //   } else {
  //   //     unregister_code(KC_LANG2);
  //   //   }
  //   //   return false;
  //   //   break;
  //   // case KANA:
  //   //   if (record->event.pressed) {
  //   //     if(keymap_config.swap_lalt_lgui==false){
  //   //       register_code(KC_LANG1);
  //   //     }else{
  //   //       SEND_STRING(SS_LALT("`"));
  //   //     }
  //   //   } else {
  //   //     unregister_code(KC_LANG1);
  //   //   }
  //   //   return false;
  //   //   break;
  //   case RGBRST:
  //     #ifdef RGBLIGHT_ENABLE
  //       if (record->event.pressed) {
  //         eeconfig_update_rgblight_default();
  //         rgblight_enable();
  //         RGB_current_mode = rgblight_config.mode;
  //       }
  //     #endif
  //     break;
  // }
//  return true;
// }

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

// hook point for 'led_test' keymap
//   'default' keymap's led_test_init() is empty function, do nothing
//   'led_test' keymap's led_test_init() force rgblight_mode_noeeprom(RGBLIGHT_MODE_RGB_TEST);
__attribute__ ((weak))
void led_test_init(void) {}


void matrix_scan_user(void) {
  //  rgblight_setrgb_at(0,255,0,0);
  //  rgblight_setrgb_at(0,255,0,1);
  //  rgblight_setrgb_at(0,255,0,2);
  //  rgblight_setrgb_at(0,255,0,3);
  //  rgblight_setrgb_at(0,255,0,4);
  //  rgblight_setrgb_at(0,255,0,5);
  //    rgblight_setrgb_at(0,0,255,6);
  //    rgblight_setrgb_at(10,0,255,17);
  //    rgblight_setrgb_at(10,0,230,18);
  //    rgblight_setrgb_at(20,0,220,31);

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
#define L_SYMB (1<<_SYMB)
#define L_NUMB (1<<_NUMB)
#define L_MDIA (1<<_MDIA)
#define L_MDIA_TRI (L_MDIA|L_NUMB|L_SYMB)

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
           matrix_write_P(matrix, PSTR("Dvorak"));
           break;
        case L_NUMB:
           matrix_write_P(matrix, PSTR("Numeric"));
           break;
        case L_SYMB:
           matrix_write_P(matrix, PSTR("Punctuation"));
           break;
        case L_MDIA:
        case L_MDIA_TRI:
           matrix_write_P(matrix, PSTR("MDIA"));
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

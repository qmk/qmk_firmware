#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif
//#ifdef AUDIO_ENABLE
//  #include "audio.h"
//#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif


#include "klackygears.h"

//extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {



  [_DVRK] = LAYOUT( \
      KC_LRMOD,   KC______, KC______,   KC______, KC______, KC______,                           KC______, KC______, KC______, KC______, KC______, KC______, \
      KC_ESC,     KC_QUOT,  KC_COMQUES, KC_DTEX,  KC_P,     KC_Y,                               KC_F,     KC_G,     KC_C,     KC_R,     KC_L,     KC______, \
      KC_LSFT,    KC_A,     KC_O,       KC_E,     KC_U,     KC_I,                               KC_D,     KC_H,     KC_T,     KC_N,     KC_S,     KC_RSFT, \
      KC_LSFT,    KC_CSCN,  KC_ALTQ,    KC_GUIJ,  KC_K,     KC_X,       KC_MCRT2,  KC_MCRTG,    KC_B,     KC_M,     KC_GUIW,  KC_ALTV,  KC_MDAZ,  KC_RSFT, \
      MO(_MDIA),  KC_ENT,   KC_LALT,    KC_ENT,   KC_SPSY,  KC_SPSY,    KC_BSNB,   KC_TBNB,     KC_ENSY,  KC_ENSY,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT \
      ),



  [_SYMB] = LAYOUT( \
      KC______, KC______, KC______, KC______, KC______, KC______,                     KC______, KC______, KC______, KC______, KC______, KC______, \
      KC______, KC_BSLS,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,                      KC______, KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC______, \
      KC______, KC_PLUS,  KC_MINS,  KC_ASTR,  KC_SLSH,  KC_EQL,                       KC______, KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC______, \
      KC______, KC_LBRC,  KC_RBRC,  KC_LPRN,  KC_RPRN,  KC_AMPR,  KC______, KC______, KC_GRV,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC______, \
      KC______, KC______, KC______, KC______, KC_SPC,   KC_DEL,   KC______, KC______, KC_CAPS,  KC______, KC______, KC______, KC______, KC______ \
      ),


  [_NUMB] = LAYOUT( \
      KC_GRV,   KC_1,       KC_2,       KC_3,       KC_4,       KC_5,                          KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC______, \
      KC______, KC_PGUP,    KC_PGDN,    KC_HOME,    KC_END,     KC_FNDR,                       KC_MINPLS,  KC_7,       KC_8,       KC_9,       KC_COLN,    KC______, \
      KC______, KC_LEFT,    KC_UP,      KC_DOWN,    KC_RIGHT,   KC______,                      KC_DIVMLT,  KC_4,       KC_5,       KC_6,       KC_CSTC,    KC______, \
      KC______, KC______,   KC_CTLA,    KC_MCCPY,   KC_MCPIN,   KC_DEL,    KC______, KC______, KC_DOTEQL,  KC_1,       KC_2,       KC_ALT3,    KC_RWIN,    KC______, \
      KC______, KC______,   KC______,   KC______,   KC_SPC,     KC_BSPC,   KC______, KC______, KC______,   KC_0,       KC_0,       KC______,   KC______,   KC______ \
      ),


  [_MDIA] =  LAYOUT( \
      KC______, KC______, KC______, KC______, KC______, KC______,                     KC_LRST,  KC______, KC______, KC______, KC______, KC______, \
      KC______, KC______, KC______, KC______, KC______, KC______,                     KC______, RGB_HUI,  KC_LSAI,  KC_LVAI,  KC_LSPI,  KC______, \
      KC______, KC______, KC______, KC______, KC______, KC______,                     KC_LRMOD, KC_LHUD,  KC_LSAD,  KC_LVAD,  KC_LSPD,  KC______, \
      KC______, KC______, KC______, KC______, KC______, KC______, KC______, KC______, KC_MPLY,  KC_MUTE,  KC_VOLD,  KC_VOLU,  KC______, KC______, \
      KC______, KC______, KC______, KC______, KC______, KC______, KC______, KC______, KC______, KC______, KC______, KC______, KC______, KC______ \
      )
};



// define variables for reactive RGB

int RGB_current_mode;
/*
void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}
*/



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
  //  rgblight_setrgb_at(0,0,255,6);
  //  rgblight_setrgb_at(10,0,255,17);
  //  rgblight_setrgb_at(10,0,230,18);
  //  rgblight_setrgb_at(20,0,220,31);

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
           matrix_write_P(matrix, PSTR("RGB-VOL"));
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

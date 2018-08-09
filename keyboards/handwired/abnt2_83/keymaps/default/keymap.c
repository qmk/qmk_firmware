#include QMK_KEYBOARD_H
#include "LUFA/Drivers/Peripheral/TWI.h"
#include "i2c.h"
#include "ssd1306.h"
  

/* Scan codes for the Brazilian ABNT2 keyboard layout  Copyright 2017 Potiguar Faga */

#define BR_CCDL KC_SCLN      //  Ç   same scancode as ;: on US layout
#define BR_SCLN KC_SLSH      //  ;:  same scancode as /? on US layout
#define BR_QUOT KC_GRV       //  '"  same scancode as `~ on US layout
#define BR_TILD KC_QUOT      //  ~^  dead keys, same scancode as '" on US layout
#define BR_ACUT KC_LBRC      //  ´`  dead keys, same scancode as [{ on US layout
#define BR_LBRC KC_RBRC      //  [{  same scancode as ]} on US layout
#define BR_RBRC KC_BSLS      //  ]}  same scancode as \| on US layout
#define BR_BSLS KC_NUBS      //  \|  uses the non-US hash scancode (#~, sometimes §±)
#define BR_SLSH KC_INT1      //  /?  uses the INTL1 scancode

#define BR_COLN LSFT(BR_SCLN)   // shifted :
#define BR_DQT  LSFT(BR_QUOT)   // shifted "
#define BR_CIRC LSFT(BR_TILD)   // shifted ^ (dead key)
#define BR_GRAV LSFT(BR_ACUT)   // shifted ` (dead key)
#define BR_LCBR LSFT(BR_LBRC)   // shifted {
#define BR_RCBR LSFT(BR_RBRC)   // shifted }
#define BR_PIPE LSFT(BR_BSLS)   // shifted |
#define BR_QUES LSFT(BR_SLSH)   // shifted ?
#define BR_TRMA LSFT(KC_6)      // shifted ¨ (dead key - trema accent)

// On the ABNT2 the keypad comma and the keypad dot scancodes are switched
// (presumably because in Brazil comma is used as the decimal separator)
#define BR_KPDT KC_KP_COMMA  //  keypad .
#define BR_KPCM KC_KP_DOT    //  keypad ,

#define BR_1UP    LALT(KC_1)      // 1 superscript                    ¹   alt+1
#define BR_2UP    LALT(KC_2)      // 2 superscript                    ²   alt+2
#define BR_3UP    LALT(KC_3)      // 3 superscript                    ³   alt+3
#define BR_PND    LALT(KC_4)      // Pound sign                       £   alt+4
#define BR_CENT   LALT(KC_5)      // Cent sign                        ¢   alt+5
#define BR_NOT    LALT(KC_6)      // Not sign                         ¬   alt+6
#define BR_SECT   LALT(KC_EQL)    // Section sign                     §   alt+=
#define BR_FORD   LALT(BR_LBRC)   // Feminine Ordinal Sign            ª   alt+[
#define BR_MORD   LALT(BR_RBRC)   // Masculine Ordinal Sign           º   alt+]
#define BR_DGRE   LALT(BR_SLSH)   // Degree sign                      °   alt+/

#define BR_EURO   LALT(KC_E)      // Euro sign                        €   alt+e
#define BR_NDTD   LALT(BR_TILD)   // Non-dead key tilde               ~   alt+~
#define BR_NDAC   LALT(BR_ACUT)   // Non-dead key acute accent        ´   alt+´
#define BR_NDGV   LALT(BR_QUOT)   // Non-dead key grave accent        `   alt+'
#define BR_NDCR   LALT(BR_CIRC)   // Non-dead key circumflex accent   ^   alt+^ (alt+shift+~)
#define BR_NDTR   LALT(BR_TRMA)   // Non-dead key trema accent        ¨   alt+¨ (alt+shift+6)

// For 101-key keyboard layouts, the ABNT2 layout allows
// the slash and question mark to be typed using alt+q and alt+w.
// The shortcuts are provided here for completeness' sake,
// but it's recommended to use BR_SLSH and BR_QUES instead
#define BR_ASLS   LALT(KC_Q)
#define BR_AQST   LALT(KC_W)



//Layers
enum {
  _BA = 0,
  _FC,
  _AL,
  _PN,
};

//13 characters max without re-writing the "Layer: " format in iota_gfx_task_user()
static char layer_lookup[][14] = {"Base","Funcoes","Unused 1","Unused 2"};


// Macro Declarations
enum {
    version_txt = 0,
    YOUR_MACRO_2,
    // ..., the rest of your macros
};

// Macro Definitions
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  switch(id) {

    // for basic strings
    case version_txt: {
        if (record->event.pressed) {
            send_string("1.1 08-07-2018"); // REPLACE with what you want your macro to be
          
            
            return false;
        }
    }

    // for more complex macros (want to add modifiers, etc.)
    //case YOUR_MACRO_1: {
    //  if (recond->event.pressed) {
     //   return MACRO(
     //     // INSERT CODE HERE for your macro. See https://docs.qmk.fm/macros.html
     //   );
    //  }
   // }


    //
  }
  return MACRO_NONE;
};

// Preenchimento para facilitar legibilidade 
#define _______ KC_TRNS
#define _______ KC_TRNS
#define ___T___ KC_TRNS
#define XXXXXXX KC_NO

/* ABNT2EX - Default
  * Primeira Linha - Layer Principal ML 
  * Segunda Linha - Layer Secundario FN
      * ,-------------------------------------------------------------------------------------------------------------------------------------.
      * |   '   |  1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |  -   |   =  |    Bksp     |TAB   |   /  |  *   |   -   |
      * |  ESC  |  F1 |   F2 |   F3 |   F4 |   F5 |   F6 |   F7 |   F8 |   F9 |  F10 | F11  |  F12 |    Delete   |PScren|      |      | RESET |
      * |-------------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------|
      * | Tab   |  Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  ´   |   [  |     Enter   |   7  |   8  |  9   |   +   |
      * |       |     |      |      |      |      |      |      |      |      |      |      |      |             |      |      |      |       |
      * |-------+-----+------+------+------+-------------+------+------+------+------+------+------+------+      +------+------+------+-------|
      * | _FN   |  A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ç  |  ˜   |    ]        |      |   4  |   5  |  6   |   =   |
      * | CAPS  |     |      |      |      |      |      |      |      |      |      |      |             |      |      |      |      |       |
      * |-------+-----+------+------+------+------|------+------+------+------+------+------+------+------+------+------+------+------+-------|
      * | Shift |  \  |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ;  |   >  |   /  |   Rshift    |  UP  |   1  |   2  |  3   |       |
      * |       |     |      |      |      |      |      |      |      |   ,  |   <  |      |     /?      | PGUP |      |      |      |       |
      * |-------+-----+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+ Enter |
      * | Lctrl | Lgui| LAlt |                    Space                       | Ralt | Rgui | _FN  | Left | Down | Right|   0  |  .   |       |
      * |       |     |      |                                                |      |      |      |      | PGDw |      |      |      |       |
      * `-------------------------------------------------------------------------------------------------------------------------------------/
      */




const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_BA] = LAYOUT(
       BR_BSLS,         KC_1,      KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,      KC_0,     KC_MINS,   KC_EQL,   KC_BSPC,  KC_TAB,  KC_KP_SLASH, KC_KP_ASTERISK, KC_KP_MINUS, 
        KC_TAB,         KC_Q,      KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,      KC_P,     BR_ACUT,   BR_LBRC,  KC_ENT,   KC_KP_7, KC_KP_8,     KC_KP_9,        KC_KP_PLUS,   
      LT(_FC,KC_CAPS),  KC_A,      KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,      BR_CCDL,  BR_TILD,   BR_RBRC,            KC_KP_4, KC_KP_5,     KC_KP_6,        KC_KP_EQUAL, 
            KC_LSFT, BR_QUOT,      KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,   KC_DOT,   BR_SLSH,   KC_RSFT,  KC_UP,    KC_KP_1, KC_KP_2,     KC_KP_3,        KC_KP_ENTER,
        KC_LCTL,    KC_LGUI,  KC_LALT,          KC_SPACE,                   KC_RALT,  KC_RGUI,  MO(_FC),                   KC_LEFT,  KC_DOWN,  KC_RGHT, KC_KP_0,        BR_KPCM
    ), 

 
[_FC] = LAYOUT(
        KC_ESC,         KC_F1,     KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,     KC_F10,   KC_F11,   KC_F12,   KC_DEL,   KC_NLCK, KC_PSCR,     _______,        RESET, 
        _______,        _______,   _______,_______,_______,_______,_______,_______,_______,_______,   _______,  _______,  _______,  _______,  _______, _______,     _______,        _______,   
        _______,        _______,   _______,_______,_______,_______,_______,_______,_______,_______,   _______,  _______,  _______,            _______, _______,     _______,        _______, 
        _______,        _______,   _______,_______,_______,_______,_______,_______,_______,_______,   _______,  _______,  KC_SLASH, KC_PGUP,  _______, _______,     _______,        version_txt,
        _______,    _______,  _______,          _______,                   _______,  _______,   _______,                  _______,  KC_PGDOWN,_______, _______,     KC_DOT
    ),
 
[_AL] = LAYOUT(
        _______,        _______,   _______,_______,_______,_______,_______,_______,_______,_______,   _______,  _______,  _______,  _______,  _______, _______,     _______,        _______, 
        _______,        _______,   _______,_______,_______,_______,_______,_______,_______,_______,   _______,  _______,  _______,  _______,  _______, _______,     _______,        _______,   
        _______,        _______,   _______,_______,_______,_______,_______,_______,_______,_______,   _______,  _______,  _______,            _______, _______,     _______,        _______, 
        _______,        _______,   _______,_______,_______,_______,_______,_______,_______,_______,   _______,  _______,  _______,  _______,  _______, _______,     _______,        _______,
        _______,    _______,  _______,          _______,                   _______,  _______,   _______,                  _______,  _______,  _______, _______,     _______
    ),  
 
[_PN] = LAYOUT(
        _______,        _______,   _______,_______,_______,_______,_______,_______,_______,_______,   _______,  _______,  _______,  _______,  _______, _______,     _______,        _______, 
        _______,        _______,   _______,_______,_______,_______,_______,_______,_______,_______,   _______,  _______,  _______,  _______,  _______, _______,     _______,        _______,   
        _______,        _______,   _______,_______,_______,_______,_______,_______,_______,_______,   _______,  _______,  _______,            _______, _______,     _______,        _______, 
        _______,        _______,   _______,_______,_______,_______,_______,_______,_______,_______,   _______,  _______,  _______,  _______,  _______, _______,     _______,        _______,
        _______,    _______,  _______,          _______,                   _______,  _______,   _______,                  _______,  _______,  _______, _______,     _______
    ),  
};



void led_set_user(uint8_t usb_led) {

}
void matrix_init_user(void) {
  #ifdef USE_I2C
    i2c_master_init();
  #ifdef SSD1306OLED
  // calls code for the SSD1306 OLED
        _delay_ms(400);
        TWI_Init(TWI_BIT_PRESCALE_1, TWI_BITLENGTH_FROM_FREQ(1, 800000));
        iota_gfx_init();   // turns on the display
  #endif
  #endif
    #ifdef AUDIO_ENABLE
        startup_user();
    #endif
}

void matrix_scan_user(void) {
    #ifdef SSD1306OLED
     iota_gfx_task();  // this is what updates the display continuously
    #endif
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source)
 {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
#if DEBUG_TO_SCREEN
  if (debug_enable) {
    return;
  }
#endif

  struct CharacterMatrix matrix;

  matrix_clear(&matrix);
  matrix_write_P(&matrix, PSTR("ABNT2EX-83"));
  
  uint8_t layer = biton32(layer_state);

  char buf[40];
  snprintf(buf,sizeof(buf), "Undef-%d", layer);
  matrix_write_P(&matrix, PSTR("\nLayer: "));
  matrix_write(&matrix, layer_lookup[layer]);

  // Host Keyboard LED Status
  char led[40];
    snprintf(led, sizeof(led), "\n\n%s  %s  %s",
            (host_keyboard_leds() & (1<<USB_LED_NUM_LOCK)) ? "NUMLOCK" : "       ",
            (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) ? "CAPS" : "    ",
            (host_keyboard_leds() & (1<<USB_LED_SCROLL_LOCK)) ? "SCLK" : "    ");
  matrix_write(&matrix, led);
  matrix_update(&display, &matrix);
}

/* 
void led_set_user(uint8_t usb_led) {

  if (usb_led & (1 << USB_LED_NUM_LOCK)) {
    
  } else {
    
  }

  if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
    
  } else {
    
  }

  if (usb_led & (1 << USB_LED_SCROLL_LOCK)) {
    
  } else {
    
  }

  if (usb_led & (1 << USB_LED_COMPOSE)) {
    
  } else {
    
  }

  if (usb_led & (1 << USB_LED_KANA)) {
    
  } else {
    
  }

}
*/


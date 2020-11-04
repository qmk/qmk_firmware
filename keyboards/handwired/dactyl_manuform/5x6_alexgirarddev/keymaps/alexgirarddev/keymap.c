/* A standard layout for the Dactyl Manuform 5x6 Keyboard */ 

#include QMK_KEYBOARD_H
#include <print.h>
#include "quantum.h"


#define _MAIN 0
#define _SYMBOL 1
#define _RED 2
#define _GREEN 3
#define _BLUE 4
#define _QWERTY 5
#define _GAME 6

#define GREEN MO(_GREEN)
#define RED MO(_RED)
#define SYMBOL MO(_SYMBOL)
#define BLUE MO(_BLUE)


#define L_ACG(kc) (LALT(LCTL(LGUI(kc))))
#define KC_DITTO (LALT(LCTL(LGUI(KC_GRAVE))))
#define _____________  KC_TRANSPARENT
#define PREV_TRK KC_MEDIA_PREV_TRACK
#define NEXT_TRK KC_MEDIA_NEXT_TRACK
#define PLAY_TRK KC_MEDIA_PLAY_PAUSE
#define AUD_MUTE KC_AUDIO_MUTE
#define AUD_UP  KC_AUDIO_VOL_UP
#define AUD_DOWN KC_AUDIO_VOL_DOWN 

// A Alt
// C Control
// G Gui
// S Shift

#define R_A(kc) (RALT(kc))
#define R_C(kc) (RCTL(kc))
#define R_G(kc) (RGUI(kc))
#define R_S(kc) (RSFT(kc))

#define R_AC(kc) (RALT(RCTL(kc)))
#define R_AG(kc) (RALT(RGUI(kc)))
#define R_AS(kc) (RALT(RSFT(kc)))

#define R_CG(kc) (RCTL(RGUI(kc)))
#define R_CS(kc) (RCTL(RSFT(kc)))

#define R_GS(kc) (RGUI(RSFT(kc)))

#define L_GS(kc) (LGUI(LSFT(kc)))


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_MAIN] = LAYOUT_5x6_alexgirarddev(
     _____________,_____________,_____________,_____________,_____________,_____________,_____________,_____________,_____________,_____________,_____________,_____________,
     //KC_ESCAPE,    KC_1,         KC_2,         KC_3,         KC_4,         KC_5,                                                   KC_6,         KC_7,         KC_8,         KC_9,         KC_0,         KC_GRAVE, 
     KC_TAB,       KC_QUOTE,     KC_COMMA,     KC_DOT,       KC_P,         KC_Y,                                                   KC_F,         KC_G,         KC_C,         KC_R,         KC_L,         KC_HOME, 
     KC_LCTRL,     KC_A,         KC_O,         KC_E,         KC_U,         KC_I,                                                   KC_D,         KC_H,         KC_T,         KC_N,         KC_S,         KC_END, 
     KC_LALT,      KC_SLASH,     KC_Q,         KC_J,         KC_K,         KC_X,                                                   KC_B,         KC_M,         KC_W,         KC_V,         KC_Z,         KC_ENTER, 
     KC_LGUI,      KC_UP,        KC_DOWN,                                                                                                                                    KC_LEFT,      KC_RIGHT,     KC_DELETE, 
                                               KC_SPC,       KC_LSHIFT,                                                                          RED,          GREEN, 
                                                                           BLUE,         KC_BSPACE,                  _____________,SYMBOL, 
                                                                           RED,          TO(_GAME),                  TO(_GAME)    ,_____________
  ), 
  [_SYMBOL] = LAYOUT_5x6_alexgirarddev(
//   _____________,_____________,_____________,_____________,_____________,_____________,_____________,_____________,_____________,_____________,_____________,_____________,_____________,_____________,_____________,
     _____________,_____________,_____________,_____________,_____________,_____________,                                          _____________,KC_ASTR,      KC_MINUS,     KC_PLUS,      _____________,_____________,
     _____________,KC_LBRACKET,  KC_RBRACKET,  _____________,_____________,_____________,                                          KC_DOT,       KC_7,         KC_8,         KC_9,         _____________,_____________,
     _____________,KC_LCBR,      KC_RCBR,      KC_LPRN,      KC_RPRN,      KC_MINUS,                                               KC_EQUAL,     KC_4,         KC_5,         KC_6,         _____________,_____________,
     _____________,KC_BSLASH,    KC_PIPE,      KC_COLN,      KC_SCOLON,    KC_UNDS,                                                KC_PLUS,      KC_1,         KC_2,         KC_3,         _____________,_____________,
     _____________,_____________,_____________,                                                                                                                              KC_0,         _____________,_____________,
                                               _____________,_____________,                                                                      _____________,_____________,
                                                                           _____________,_____________,              _____________,_____________,
                                                                           _____________,_____________,              _____________,_____________
  ), 
  [_RED] = LAYOUT_5x6_alexgirarddev(
//  _____________,_____________,_____________,_____________,_____________,_____________,_____________,_____________,_____________,_____________,_____________,_____________,_____________,_____________,_____________,
    KC_F1,        KC_F2,        KC_F3,        KC_F4,        KC_F5,        KC_F6,                                                  KC_F7,        KC_F8,        KC_F9,        KC_F10,       KC_F11,       KC_F12, 
    _____________,KC_DITTO,     LCTL(KC_X),   LCTL(KC_C),   LCTL(KC_V),   KC_PSCREEN,                                             KC_F14,       KC_F15,       KC_F16,       KC_F17,       KC_F18,       KC_F19, 
    _____________,KC_UP,        KC_DOWN,      KC_LEFT,      KC_RIGHT,     KC_MS_BTN4,                                             KC_F22,       KC_F23,       KC_F24,       RSFT(KC_F14), RSFT(KC_F15), RSFT(KC_F16), 
    _____________,LCTL(KC_Z),   LCTL(KC_Y),   LCTL(KC_A),   _____________,KC_MS_BTN5,                                             RSFT(KC_F17), RSFT(KC_F18), RSFT(KC_F19), RSFT(KC_F20), RSFT(KC_F21), RSFT(KC_F22), 
    PREV_TRK,     KC_PGUP,      KC_PGDOWN,                                                                                                                                  RSFT(KC_F23), RSFT(KC_F24), RCTL(KC_F13), 
                                              AUD_MUTE,     _____________,                                                                      _____________,_____________,
                                                                          AUD_UP,       AUD_DOWN,                   _____________,_____________,
                                                                          PLAY_TRK,     NEXT_TRK,                   _____________,_____________
  ), 
  [_GREEN] = LAYOUT_5x6_alexgirarddev(
//  _____________,_____________,_____________,_____________,_____________,_____________,_____________,_____________,_____________,_____________,_____________,_____________,_____________,_____________,_____________,
    RCTL(KC_F16), RCTL(KC_F17), RCTL(KC_F18), RCTL(KC_F19), RCTL(KC_F20), RCTL(KC_F21),                                           RGUI(KC_F19), RGUI(KC_F20), RGUI(KC_F21), RGUI(KC_F22), RGUI(KC_F23), RGUI(KC_F24), 
    RCTL(KC_F23), RCTL(KC_F24), RALT(KC_F13), RALT(KC_F14), RALT(KC_F15), RALT(KC_F16),                                           R_CS(KC_F13), R_CS(KC_F14), R_CS(KC_F15), R_CS(KC_F16), R_CS(KC_F17), R_CS(KC_F18), 
    RALT(KC_F17), LGUI(KC_UP),  LGUI(KC_DOWN),L_GS(KC_LEFT),L_GS(KC_RIGHT),RALT(KC_F18),                                          R_CS(KC_F19), R_CS(KC_F20), R_CS(KC_F21), R_CS(KC_F22), R_CS(KC_F23), R_CS(KC_F24), 
    RALT(KC_F19), RALT(KC_F20), RALT(KC_F21), RALT(KC_F22), RALT(KC_F23), RALT(KC_F24),                                           R_AS(KC_F13), R_AS(KC_F14), R_AS(KC_F15), R_AS(KC_F16), R_AS(KC_F17), R_AS(KC_F18), 
    RGUI(KC_F15), RGUI(KC_F16), RGUI(KC_F17),                                                                                                                               R_AS(KC_F19), R_AS(KC_F20), R_AS(KC_F21), 
                                              KC_ESCAPE,    _____________,                                                                      _____________,_____________,
                                                                           _____________,_____________,              _____________,_____________,
                                                                           _____________,_____________,              _____________,_____________
  ),
   [_GAME] = LAYOUT_5x6_alexgirarddev(
     //_____________,_____________,_____________,_____________,_____________,_____________,                                          _____________,_____________,_____________,_____________,_____________,_____________,
     KC_ESCAPE,    KC_1,         KC_2,         KC_3,         KC_4,         KC_5,                                                   KC_6,         KC_7,         KC_8,         KC_9,         KC_0,         KC_GRAVE, 
     _____________,_____________,_____________,_____________,_____________,_____________,                                          _____________,_____________,_____________,_____________,_____________,_____________,
     _____________,_____________,_____________,_____________,_____________,_____________,                                          _____________,_____________,_____________,_____________,_____________,_____________,
     _____________,_____________,_____________,_____________,_____________,_____________,                                          _____________,_____________,_____________,_____________,_____________,_____________,
     _____________,_____________,_____________,                                                                                                                              _____________,_____________,_____________,
                                               _____________,_____________,                                                                      _____________,_____________, 
                                                                           KC_LALT,         KC_BSPACE,                  _____________,_____________, 
                                                                           KC_LCTRL,        TO(_MAIN),                  TO(_MAIN)    ,_____________
  )
//  [_BLUE] = LAYOUT_ergodox_pretty(
//    R_GS(KC_F13), KC_CAPSLOCK,       KC_NUMLOCK,        KC_SCROLLLOCK,     RESET,             R_GS(KC_F14), _____________,                                   _____________,   R_CG(KC_F17), R_CG(KC_F18), R_CG(KC_F19), KC_KP_ASTERISK,    KC_MINUS,          R_CG(KC_F20), 
//    R_GS(KC_F16), R_GS(KC_F17), R_GS(KC_F18), R_GS(KC_F19), R_GS(KC_F20), R_GS(KC_F21), _____________,                                   _____________,   R_CG(KC_F22), KC_7,              KC_8,              KC_9,              R_CG(KC_F23), R_CG(KC_F24), 
//    R_GS(KC_F23), R_GS(KC_F24), R_AC(KC_F13), R_AC(KC_F14), R_AC(KC_F15), R_AC(KC_F16),                                                                   R_AG(KC_F14), KC_4,              KC_5,              KC_6,              R_AG(KC_F15), R_AG(KC_F16), 
//    R_AC(KC_F18), R_AC(KC_F19), R_AC(KC_F20), R_AC(KC_F21), R_AC(KC_F22), R_AC(KC_F23), _____________,                                   _____________,   KC_F17,            KC_1,              KC_2,              KC_3,              R_AG(KC_F18), R_AG(KC_F19), 
//    _____________,   R_AC(KC_F24), R_CG(KC_F13), R_CG(KC_F14), R_CG(KC_F15),                                                                                                   KC_0,              KC_0,              KC_DOT,            R_AG(KC_F20), R_AG(KC_F21), 
//                                                                                                    _____________,   _____________,   _____________,   _____________,
//                                                                                                                    _____________,   _____________,
//                                                                                    R_CG(KC_F14), _____________,   _____________,   _____________,   _____________,   __________
//  ), 
//  [_QWERTY] = LAYOUT_ergodox_pretty(
//    KC_ESCAPE,         KC_1,              KC_2,              KC_3,              KC_4,              KC_5,              _____________,                                   _____________,   KC_6,              KC_7,              KC_8,              KC_9,              KC_0,              KC_BSPACE, 
//    KC_TAB,            KC_Q,              KC_W,              KC_E,              KC_R,              KC_T,              _____________,                                   _____________,   KC_Y,              KC_U,              KC_I,              KC_O,              KC_P,              KC_BSLASH, 
//    _____________,   KC_A,              KC_S,              KC_D,              KC_F,              KC_G,                                                                              KC_H,              KC_J,              KC_K,              KC_L,              KC_SCOLON,         KC_ENTER, 
//    KC_LSHIFT,         KC_Z,              KC_X,              KC_C,              KC_V,              KC_B,              _____________,                                   _____________,   KC_N,              KC_M,              KC_COMMA,          KC_DOT,            KC_SLASH,          KC_LSHIFT, 
//    KC_LCTRL,          KC_LALT,           _____________,   _____________,   KC_LALT,                                                                                                           _____________,   _____________,   _____________,   _____________,   _____________,
//                                                                                                    TO(0),             _____________,   _____________,   _____________,
//                                                                                                                    _____________,   _____________,
 //                                                                                   KC_SPACE,          KC_SPACE,          _____________,   _____________,   KC_SPACE,          KC_SPACE

};

 static void render_qmk_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
        0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
        0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};

    oled_write_P(qmk_logo, false);
}


void keyboard_post_init_user(void) {
    debug_enable=true;
}


bool process_record_user(uint16_t keycode,    keyrecord_t *record) {
#ifdef CONSOLE_ENABLE
    if(record->event.pressed)
    {
    uprintf("%u%u\n",    record->event.key.row,    record->event.key.col);
    }
#endif 
    return true;
 }



static void render_status(void) {
    // QMK Logo and version information
    render_qmk_logo();
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case _MAIN:
            oled_write_P(PSTR("MAIN\n"), false);
            break;
        case _SYMBOL:
            oled_write_P(PSTR("SYMBOL\n"), false);
            break;
        case _RED:
            oled_write_P(PSTR("RED\n"), false);
            break;
        case _BLUE:
            oled_write_P(PSTR("BLUE\n"), false);
            break;
        case _GREEN:
            oled_write_P(PSTR("GREEN\n"), false);
            break;
        case _GAME:
            oled_write_P(PSTR("GAME\n"), false); 
            break; 
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
            break;
    }
}

void oled_task_user(void)
{
  render_status();
}
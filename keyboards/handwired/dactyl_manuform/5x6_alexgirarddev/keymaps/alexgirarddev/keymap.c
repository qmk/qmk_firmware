/* A standard layout for the Dactyl Manuform 5x6 Keyboard */ 

#include QMK_KEYBOARD_H
#include <print.h>
#include "quantum.h"


#define _MAIN 0
#define _LOWER 1
#define _RAISE 2

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

#define L_ACG(kc) (LALT(LCTL(LGUI(kc)))
#define KC_TR KC_TRANSPARENT

// A Alt
// C Control
// G Gui
// S Shift
#define R_AC(kc) (RALT(RCTL(kc)))
#define R_AG(kc) (RALT(RGUI(kc)))
#define R_AS(kc) (RALT(RSFT(kc)))

#define R_CG(kc) (RCTL(RGUI(kc)))
#define R_CS(kc) (RCTL(RSFT(kc)))

#define R_GS(kc) (RGUI(RSFT(kc)))



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_MAIN] = LAYOUT_5x6_alexgirarddev(
     KC_ESCAPE,      KC_1,           KC_2,           KC_3,           KC_4,           KC_5,                      KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           KC_GRAVE,
     KC_TAB,         KC_QUOTE,       KC_COMMA,       KC_DOT,         KC_P,           KC_Y,                     KC_F,           KC_G,           KC_C,           KC_R,           KC_L,           KC_HOME,
     KC_LCTRL,       KC_A,           KC_O,           KC_E,           KC_U,           KC_I,                     KC_D,           KC_H,           KC_T,           KC_N,           KC_S,           KC_END,
     KC_LALT,        KC_SLASH,       KC_Q,           KC_J,           KC_K,           KC_X,                     KC_B,           KC_M,           KC_W,           KC_V,           KC_Z,           KC_ENTER,
     KC_LGUI,        KC_UP,          KC_DOWN,                                                                                                                  KC_LEFT,        KC_RIGHT,       KC_DELETE,
                                                                     KC_SPC,         KC_LSHIFT,                   KC_ENT,         LOWER,
                                                                     KC_TAB,         KC_BSPACE  ,                  KC_END,         KC_DEL,
                                                                     KC_BSPC,        KC_GRV,                   KC_LGUI,        KC_LALT
  )

};
static void render_logo(void) {

    oled_write_P(PSTR("w"), false);
}
void keyboard_post_init_user(void) {
	  // Customise these values to desired behaviour
debug_enable=true;
 render_logo();
//render_logo();
//debug_matrix=true;
//print("wow");
	  //       //debug_keyboard=true;
	  //         //debug_mouse=true;
	  //         }
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
   //render_logo();
    render_logo();
   //If console is enabled, it will print the matrix position and status of each key pressed
	#ifdef CONSOLE_ENABLE
   if(record->event.pressed)
   {
	uprintf("%u%u\n", record->event.key.row, record->event.key.col);
   }
	#endif 
	return true;
 }
 


//static void render_logo(void) {
//static const char PROGMEM qmk_logo[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00};
//    oled_write_P(qmk_logo, false);
//}

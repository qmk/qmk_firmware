/* A standard layout for the Dactyl Manuform 5x6 Keyboard */ 

#include QMK_KEYBOARD_H
#include <print.h>


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
                                                                     KC_TAB,         KC_BSPA*  ,                  KC_END,         KC_DEL,
                                                                     KC_BSPC,        KC_GRV,                   KC_LGUI,        KC_LALT
  )

};

void keyboard_post_init_user(void) {
	  // Customise these values to desired behaviour
debug_enable=true;
//debug_matrix=true;
//print("wow");
	  //       //debug_keyboard=true;
	  //         //debug_mouse=true;
	  //         }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
   //If console is enabled, it will print the matrix position and status of each key pressed
	#ifdef CONSOLE_ENABLE
   if(record->event.pressed)
   {
	uprintf("%u%u\n", record->event.key.row, record->event.key.col);
   }
	#endif 
	return true;
 }

/* A standard layout for the Dactyl Manuform 5x6 Keyboard */ 

#include QMK_KEYBOARD_H
#include <print.h>


#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_5x6_alexgirarddev(
     KC_ESC , KC_1  , KC_2  , KC_3  , KC_4  , KC_5  ,                         KC_6  , KC_7  , KC_8  , KC_9  , KC_0  ,KC_BSPC,
     KC_TAB , KC_Q  , KC_W  , KC_E  , KC_R  , KC_T  ,                         KC_Y  , KC_U  , KC_I  , KC_O  , KC_P  ,KC_MINS,
     KC_LSFT, KC_A  , KC_S  , KC_D  , KC_F  , KC_G  ,                         KC_H  , KC_J  , KC_K  , KC_L  ,KC_SCLN,KC_QUOT,
     KC_LCTL, KC_Z  , KC_X  , KC_C  , KC_V  , KC_B  ,                         KC_N  , KC_M  ,KC_COMM,KC_DOT ,KC_SLSH,KC_BSLASH,
     KC_1,KC_2, KC_3,                                                                                  KC_PLUS, KC_EQL, KC_3,
                                      KC_V,KC_SPC,                        KC_ENT, KC_2,
                                      KC_TAB,KC_HOME,                         KC_END,  KC_DEL,
                                      KC_BSPC, KC_GRV,                        KC_LGUI, KC_LALT
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

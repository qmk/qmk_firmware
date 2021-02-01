#include QMK_KEYBOARD_H
#define _LAYER0 0
#define _LAYER1 1
#define _LAYER2 2
#define _LAYER3 3
#define _LAYER4 4
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 // 0: Base Layer
	[0] = LAYOUT(
	   KC_GESC  , KC_1    , KC_2    , KC_3 , KC_4 , KC_5 , KC_6 , KC_7 , KC_8    , KC_9   , KC_0    , KC_MINS , KC_EQL  , KC_BSPC ,\
	   KC_TAB  , KC_Q    , KC_W    , KC_E , KC_R , KC_T , KC_Y , KC_U , KC_I    , KC_O   , KC_P    , KC_LBRC , KC_RBRC , KC_BSLS ,\
	   KC_CAPS , KC_A    , KC_S    , KC_D , KC_F , KC_G , KC_H , KC_J , KC_K    , KC_L   , KC_SCLN , KC_QUOT , KC_ENT  ,\
	   KC_LSFT , KC_Z    , KC_X    , KC_C , KC_V , KC_B , KC_N , KC_M , KC_COMM , KC_DOT , KC_RSFT , KC_UP   , MO(2)   ,\
	   KC_LCTL , KC_LGUI , KC_LALT               , KC_SPC             , KC_SLSH , MO(1)  , KC_LEFT , KC_DOWN , KC_RGHT ),
  // 1: Function Layer
	[1] = LAYOUT(
	   KC_GRV , KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 , KC_F6 , KC_F7 , KC_F8 , KC_F9 , KC_F10 , KC_F11 , KC_F12 , KC_DEL ,\
	   KC_NO  , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_MAIL   , KC_CALC  , KC_NO ,\
	   KC_NO  , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_VOLU , KC_VOLD   , KC_NO  , \
	   KC_NO  , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_MPRV , KC_MNXT , KC_NO , RGB_VAI  , KC_NO, \
	   KC_NO  , KC_NO , KC_NO ,                    MO(3)              , KC_MSTP , KC_NO , KC_MUTE , RGB_VAD , KC_MSTP  ),
   
  // 2: Function Layer
	[2] = LAYOUT(
	   KC_NO  , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO   , KC_NO  , KC_DEL ,\
	   KC_NO  , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_MAIL   , KC_CALC  , KC_NO ,\
	   KC_NO  , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_INS   , KC_HOME, KC_NO   , \
	   KC_NO  , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_PGUP , KC_PGDN , KC_NO , KC_NO   , KC_NO  , \
	   KC_NO  , KC_NO , KC_NO ,                   MO(3)               , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO  ),
	     
  // 3: Function Layer
	[3] = LAYOUT(
	   KC_NO  , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO   , KC_NO  , KC_NO ,\
	   KC_NO  , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , RGB_TOG   , RGB_M_P  , KC_NO ,\
	   KC_NO  , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , RGB_SPI , RGB_SPD   , KC_NO  , \
	   KC_NO  , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , RGB_MOD	, RGB_RMOD , RGB_M_R , RGB_VAI   , KC_NO  , \
	   KC_NO  , KC_NO , KC_NO ,                 KC_NO                 , RGB_M_R , KC_NO , RGB_HUI , RGB_VAD , RGB_HUD  ),
	   
		};

void matrix_init_user(void) {
  //user initialization
}

void matrix_scan_user(void) {
  //user matrix
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	  return true;
	}

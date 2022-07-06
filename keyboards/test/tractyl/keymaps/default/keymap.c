#include QMK_KEYBOARD_H
#include "pointing_device.h"

#define constrain_hid(amt) ((amt) < -127 ? -127 : ((amt) > 127 ? 127 : (amt)))

#define _CLMK 0
#define _GAME 1
#define _MOUSE 2
#define _FN 3
#define _RALT 4
#define _FN2 5

#define CARET_VAL 50
#define SCROLL_VAL 40

/* ===== PROBLEMS ======
-KB needs to be replugged after shutdown
-Sensitivity bug
-lower profile thumb switches
-pause mouse_timer while key held down
-fix right encoder clockwise random press on keyboard startup
*/

bool LALT_HELD;
bool FN_HELD;

static bool mouse_lock = false;
static bool caret_mode = false;
static bool scrolling_mode = false;
static uint16_t mouse_timer = 0;
int8_t tempx = 0;
int8_t tempy = 0;
static bool scroll_prev = false;
static bool caret_prev = false;
//report_mouse_t currentReport;
unsigned int dragscroll_timer;

enum custom_keycodes {
	MO_FN = SAFE_RANGE,
	MO_RALT,
	CK_MSOF,
	CK_SCLN,
	ALT_TAB,
	MC_CBR,
	MC_BRC,
	MC_PRN,
	MC_COPY,
	MC_PASTE,
	MC_CUT,
	CK_DSCL,
	CK_CRET,
	CK_MSLK,
	KC_SS,
	CK_BACK
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_CLMK] = LAYOUT(
     KC_GESC, KC_1  , KC_2  , KC_3  , KC_4  , KC_5  ,                         KC_6  , KC_7  , KC_8  , KC_9  , KC_0  ,KC_BSPC,
     KC_TAB , KC_Q  , KC_W  , KC_F  , KC_P  , KC_B  ,                         KC_J  , KC_L  , KC_U  , KC_Y  , KC_SCLN, KC_MINS,
     KC_BSPC, KC_A  , KC_R  , KC_S  , KC_T  , KC_G  ,                         KC_K  , KC_N  , KC_E  , KC_I  ,KC_O, KC_QUOT,
     KC_LGUI, KC_V  , KC_X  , KC_D  , KC_C  , KC_Z  ,                         KC_M  , KC_H  ,KC_COMM,KC_DOT ,KC_SLSH,KC_BSLASH,
                      KC_LBRC,KC_RBRC,KC_SPC,MO_RALT,   			          KC_LSFT, ALT_TAB,KC_PLUS, KC_EQL,
                             KC_MPLY,KC_LCTL,KC_LALT,                         MO_FN, KC_ENT								
  ),
  
  [_GAME] = LAYOUT(
     KC_ESC , KC_1  , KC_2  , KC_3  , KC_4  , KC_5  ,                         KC_6  , KC_7  , KC_8  , KC_9  , KC_0  ,KC_BSPC,
     KC_TAB , KC_Q  , KC_W  , KC_F  , KC_P  , KC_B  ,                         KC_J  , KC_L  , KC_U  , KC_Y  , KC_COLN, KC_MINS,
     KC_LSFT, KC_A  , KC_R  , KC_S  , KC_T  , KC_G  ,                         KC_K  , KC_N  , KC_E  , KC_I  ,KC_O, KC_QUOT,
     KC_DEL , KC_V  , KC_X  , KC_D  , KC_C  , KC_Z  ,                         KC_M  , KC_H  ,KC_COMM,KC_DOT ,KC_SLSH,KC_BSLASH,
                      KC_LBRC,KC_RBRC,KC_SPC,KC_BSPC,   			          KC_LSFT,ALT_TAB,KC_PLUS, KC_EQL,
                             KC_MPLY,KC_LCTL,KC_LALT,                         MO_FN, KC_ENT								
  ),
  
  [_MOUSE] = LAYOUT(
     KC_GESC, CK_MSOF, CK_MSOF , CK_MSOF, CK_MSOF, CK_MSOF,                   _______ ,_______,_______,_______,_______,_______,
     KC_TAB , CK_MSOF, CK_MSOF , CK_MSOF, CK_MSOF, CK_MSOF,                   MC_CUT  ,CK_DSCL,CK_CRET,CK_MSLK, _______, _______,
     KC_BSPC, CK_MSOF, CK_MSOF , CK_MSOF, CK_MSOF, CK_MSOF,                   MC_COPY , KC_BTN1, KC_BTN2, KC_BTN3, KC_MPLY, KC_QUOT,
     KC_LGUI, CK_MSOF, CK_MSOF , CK_MSOF, CK_MSOF, CK_MSOF,                   MC_PASTE, KC_BTN4, KC_BTN5, KC_F5, CK_BACK, KC_BSLASH,
                       CK_MSOF , CK_MSOF, CK_MSOF, MO_RALT,                   KC_LSFT, ALT_TAB, KC_PLUS, KC_EQL,
                                 _______, KC_LCTL, KC_LALT,                   MO_FN,KC_ENT		
  ),
    
  [_FN] = LAYOUT(
     KC_ESC, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5,                       KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10  ,KC_BSPC,
     KC_TAB , KC_PGUP, KC_PGUP, KC_UP, KC_HOME , KC_SCLN ,                    KC_COMM , KC_P7  , KC_P8  , KC_P9  , KC_SCLN  ,KC_SS,
     KC_DEL, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_AT,              		  KC_COMM , KC_P4  , KC_P5  , KC_P6  ,KC_P0, KC_QUOT,
     KC_LGUI, KC_PGDN, KC_PGDN, KC_HASH, KC_END, KC_B,             		      KC_DOT  , KC_P1  ,KC_P2, KC_P3 ,KC_P0,KC_DOT,
                         DM_PLY1, TG(_GAME),KC_SPC, _______,                  KC_LSFT, KC_MPLY, KC_PLUS, KC_EQL,
                                     KC_MUTE,KC_LCTL,KC_LALT,                 _______,KC_ENT		
  ),
  
  [_RALT] = LAYOUT(
     QK_BOOT, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5,                      KC_F6  , KC_F7 , KC_F8 , KC_F9 , KC_F10 ,KC_DEL,
     KC_TAB , KC_PGUP  , MC_BRC  , KC_COLN  , KC_RBRC  , KC_LCBR,             KC_COMM  , KC_P7  , KC_P8  , KC_P9  , KC_SCLN, KC_SS,
     KC_DEL, KC_HOME  ,  MC_CBR , KC_UNDS  , CK_SCLN  , KC_AT  ,              KC_QUOT  , KC_P4  , KC_P5  , KC_P6  ,KC_SCLN,KC_QUOT,
     KC_LGUI, KC_PGDN  , MC_PRN  , KC_HASH  , KC_RPRN  , KC_RCBR,             KC_DOT  , KC_P1  ,KC_P2,KC_P3 ,KC_P0,KC_BSLASH,
                         DM_PLY1, DM_PLY2,KC_SPC, _______,                    KC_LSFT, KC_LALT, DM_REC1, DM_REC2,
                                     _______,KC_LCTL,KC_LSFT,                 MO(_FN2),KC_ENT		
  ),
  
  [_FN2] = LAYOUT(
     KC_ESC, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5,                       KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10  ,KC_BSPC,
     KC_TAB , KC_PGUP  , KC_PGUP  , KC_UP  , KC_HOME  , KC_SCLN  ,            KC_COMM , KC_P7  , KC_P8  , KC_P9  , KC_SCLN , KC_NUM,
     KC_DEL, KC_HOME  , KC_LEFT  , KC_DOWN  , KC_RGHT  , KC_AT   ,            KC_COMM  , KC_P4  , KC_P5  , KC_P6  ,KC_P0, KC_QUOT,
     KC_LGUI, KC_PGDN  , KC_PGDN  , KC_HASH  , KC_END  , KC_B  ,              KC_DOT , KC_P1  ,KC_P2, KC_P3 ,KC_P0,KC_DOT,
                         DM_PLY1, DM_PLY2,KC_SPC, _______,                    KC_LSFT, KC_LALT, KC_PLUS, KC_EQL,
                                     KC_MUTE,KC_LCTL,KC_LALT,                 _______,KC_ENT
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
		case KC_BTN1:
			if(record->event.pressed){
				mouse_timer = timer_read();
				scrolling_mode = false;
				caret_mode = false;
			}
			return true;
		case CK_MSOF:
			if(record->event.pressed){
				layer_off(_MOUSE);
				scrolling_mode = false;
				caret_mode = false;
				tap_code(KC_TRNS);
			}
			return true;
		case MC_BRC:
			if(record->event.pressed){
				tap_code16(KC_LBRC);
				tap_code16(KC_RBRC);
				tap_code(KC_LEFT);
			}
			return false;
		case MC_CBR:
			if(record->event.pressed){
				tap_code(KC_END);
				tap_code16(KC_LCBR);
				tap_code16(KC_RCBR);
				tap_code(KC_LEFT);
			}
			return false;
		case MC_PRN:
			if(record->event.pressed){
				tap_code16(KC_LPRN);
				tap_code16(KC_RPRN);
				tap_code(KC_LEFT);
			}
			return false;
		case MO_FN:
			if (record->event.pressed) {
				layer_on(_FN);
				FN_HELD = true;
			} else {
				layer_off(_FN);
				FN_HELD = false;
			}
			return false;
		case MO_RALT:
			if (record->event.pressed) {
				layer_on(_RALT);
				FN_HELD = true;
				caret_mode = true;
			} else {
				layer_off(_RALT);
				FN_HELD = false;
				caret_mode = false;
			}
			return false;
		case KC_LALT:
			if (record->event.pressed) {
				LALT_HELD = true;
			} else {
				LALT_HELD = false;
			}
			return true;
		case ALT_TAB:
			if (record->event.pressed) {
					register_code(KC_LALT);
					tap_code(KC_TAB);
					LALT_HELD = true;
			} else {
				unregister_code(KC_LALT);
				LALT_HELD = false;
			}
			return false;
		case MC_COPY:
			if(record->event.pressed){
				register_code(KC_LCTL);
				tap_code(KC_C);
				unregister_code(KC_LCTL);
			}
			return false;
		case MC_PASTE:
			if(record->event.pressed){
				register_code(KC_LCTL);
				tap_code(KC_V);
				unregister_code(KC_LCTL);
			}
			return false;
		case MC_CUT:
			if(record->event.pressed){
				register_code(KC_LCTL);
				tap_code(KC_X);
				unregister_code(KC_LCTL);
			}
			return false;
		case CK_DSCL:
			if(record->event.pressed){
				dragscroll_timer = timer_read();
				scroll_prev = scrolling_mode;
				scrolling_mode = true;
			}else{
				if(timer_elapsed(dragscroll_timer) < 200){
					scrolling_mode = !scroll_prev;
				}else{
					scrolling_mode = false;
				}
			}	
			return false;
		case CK_CRET:
			if(record->event.pressed){
				dragscroll_timer = timer_read();
				caret_prev = caret_mode;
				caret_mode = true;
			}else{
				if(timer_elapsed(dragscroll_timer) < 200){
					caret_mode = !caret_prev;
				}else{
					caret_mode = false;
				}
			}
			return false;
		case CK_MSLK:
			if(record->event.pressed){
				pointing_device_set_cpi(500);
				mouse_lock = !mouse_lock;
			}
			return false;
		case KC_SS:
			if(record->event.pressed){
				register_code16(KC_LALT);
				tap_code(KC_P0);
				tap_code(KC_P2);
				tap_code(KC_P2);
				tap_code(KC_P3);
				unregister_code16(KC_LALT);
			}
			return false;
		case CK_BACK:
			if(record->event.pressed){
				tap_code16(LCTL(KC_SPC));
			}
			return false;
		case CK_SCLN:
			if(record->event.pressed){
				tap_code(KC_END);
				tap_code(KC_SCLN);
			}
			return false;
		}
	return true;
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
		if(FN_HELD){
			if(clockwise){
				tap_code(KC_RGHT);
			}else{
				tap_code(KC_LEFT);
			}
		}else if (clockwise) {
				tap_code_delay(KC_MNXT, 10);
			} else {
				tap_code_delay(KC_MPRV, 10);
			}
	} else if (index == 1) {	
		if (LALT_HELD == true) {
			if (clockwise) {
				tap_code(KC_TAB);
			} else {
				register_code(KC_LSFT);
				tap_code(KC_TAB);
				unregister_code(KC_LSFT);
			}
		} else if (FN_HELD == true || layer_state_is(_MOUSE)){
			if (clockwise) {
				//tap_code_delay(KC_MNXT, 10);
				tap_code(KC_RGHT);
				/* register_code(KC_LCTL);
				tap_code(KC_TAB);
				unregister_code(KC_LCTL); */
			} else {
				//tap_code_delay(KC_MPRV, 10);
				tap_code(KC_LEFT);
				/* register_code(KC_LCTL);
				register_code(KC_LSFT);
				tap_code(KC_TAB);
				unregister_code(KC_LSFT);
				unregister_code(KC_LCTL); */
			}
		} else if (clockwise) {
			//tap_code(KC_RGHT);
			tap_code_delay(KC_MNXT, 10);
        } else {
			//tap_code(KC_LEFT);
			tap_code_delay(KC_MPRV, 10);
        }
    }
    return true;
};

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
	if(mouse_report.x != 0 || mouse_report.y != 0){
		if(!layer_state_is(_MOUSE)){
			layer_on(_MOUSE);
		}
		mouse_timer = timer_read();
	}else if(timer_elapsed(mouse_timer) > 500 && layer_state_is(_MOUSE) && !mouse_lock){
		layer_off(_MOUSE);
	}
	short x = mouse_report.x, y = mouse_report.y;
	x = (x > 0 ? x * x / 3 + x : -x * x / 3 + x);
	y = (y > 0 ? y * y / 3 + y : -y * y / 3 + y);
	/* float x = mouse_report.x, y = mouse_report.y;
	x = (x > 0 ? (x/20)*(x)+1 : (-x/20)*(x)-1);
	if(x == 1 || x == -1){
		x = 0;
	}
	y = (y > 0 ? (y/20)*(y)+1 : (-y/20)*(y)-1);
	if(y == 1 || y == -1){
		y = 0;
	} */
	mouse_report.x = constrain_hid(x);
	mouse_report.y = constrain_hid(y);
	if(scrolling_mode){
		caret_mode = false;
		tempx += mouse_report.x;
		tempy += mouse_report.y;
		mouse_report.x = 0;
		mouse_report.y = 0;
		if(tempy > SCROLL_VAL){
			tap_code(KC_WH_D);
			tempx = 0;
			tempy = 0;
		}else if(tempy < -SCROLL_VAL){
			tap_code(KC_WH_U);
			tempx = 0;
			tempy = 0;
		}else if(tempx > SCROLL_VAL - 10){
			tap_code(KC_WH_R);
			tempx = 0;
			tempy = 0;
		}else if(tempx < -SCROLL_VAL - 10){
			tap_code(KC_WH_L);
			tempx = 0;
			tempy = 0;
		}
	}else if(caret_mode){
		tempx += mouse_report.x;
		mouse_report.x = 0;
		tempy += mouse_report.y;
		mouse_report.y = 0;
		if(tempx > CARET_VAL){
			tap_code(KC_RGHT);
			tempx = 0;
			tempy = 0;
		}else if(tempx < -CARET_VAL){
			tap_code(KC_LEFT);
			tempx = 0;
			tempy = 0;
		}else if(tempy > CARET_VAL + 10){
			tap_code(KC_DOWN);
			tempx = 0;
			tempy = 0;
		}else if(tempy < -CARET_VAL + 10){
			tap_code(KC_UP);
			tempx = 0;
			tempy = 0;
		}
    }
    return mouse_report;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
		case _CLMK:
            //rgblight_sethsv_noeeprom(HSV_GREEN);
			rgblight_disable_noeeprom();
            break;
		case _FN:
			if(!rgblight_is_enabled()){
				rgblight_enable_noeeprom();	
			}
			rgblight_sethsv_noeeprom(HSV_RED);
			break;
		case _RALT:
			if(!rgblight_is_enabled()){
				rgblight_enable_noeeprom();	
			}
			rgblight_sethsv_noeeprom(HSV_ORANGE);
			break;
		case _MOUSE:
			if(!rgblight_is_enabled()){
				rgblight_enable_noeeprom();	
			}
			rgblight_sethsv_noeeprom(HSV_SPRINGGREEN);
			break;
		case _FN2:
			if(!rgblight_is_enabled()){
				rgblight_enable_noeeprom();	
			}
			rgblight_sethsv_noeeprom(HSV_RED);
			break;
        default:
            rgblight_sethsv_noeeprom(HSV_YELLOW);
            break;
    }
    return state;
}

void keyboard_post_init_user(void) {
  rgblight_disable_noeeprom(); // Enables RGB, without saving settings
  //rgblight_sethsv_noeeprom(HSV_GREEN);
  rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
}

/*void keyboard_post_init_user(void) {
  debug_enable=true;
  //debug_matrix=true;
  //debug_keyboard=true;
  debug_mouse=true;
}*/



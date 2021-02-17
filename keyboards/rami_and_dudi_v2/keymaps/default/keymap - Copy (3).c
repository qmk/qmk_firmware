#include QMK_KEYBOARD_H



#define _BASE 0
#define _MY_LAYER 1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_ortho_3x4
  (
    KC_MPRV, KC_MPLY, KC_MNXT,
    KC_LEFT, KC_RIGHT, KC_RIGHT,
    KC_LEFT, KC_9,  TG(_MY_LAYER),
    KC_NO, TG(_MY_LAYER), KC_NO
  ),
    [_MY_LAYER] = LAYOUT_ortho_3x4
  (
    KC_1, KC_2, KC_3,
    KC_4, KC_5, KC_6,
    KC_7, KC_8, KC_TRANSPARENT,
    KC_NO, KC_NO, KC_NO
  )
};





void dip_switch_update_user(uint8_t index, bool active) 
{ 
 switch (index) {
        case 0:		//ENC0_SW2
        if(active) //ENC2_SW2 pressed
		{ 
			tap_code(KC_MUTE);
		} 
	else //ENC2_SW2 released
                {
					
			//do nothing
		}
 break;
 }
}



#ifdef OLED_DRIVER_ENABLE
void oled_task_user(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case _BASE:
            oled_write_P(PSTR("Base\n"), false);
            break;
        case _MY_LAYER:
            oled_write_P(PSTR("Custom\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }
}
#endif
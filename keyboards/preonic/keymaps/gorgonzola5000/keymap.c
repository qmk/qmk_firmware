#include QMK_KEYBOARD_H

enum custom_keycodes {
    RELEASE = SAFE_RANGE,
};

enum layer_names {
    _DEFAULT,
    _NUMPAD,
    _ARROWS_AND_OTHER,
	_FUNCTION_AND_MEDIA
};

// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//     switch (keycode) {
//     case RELEASE:
//         if (record->event.pressed) {
// 			uint8_t mods = 0;
// 			if ((mods = get_oneshot_mods()) && !has_oneshot_mods_timed_out()) {
// 				clear_oneshot_mods();
// 				unregister_mods(mods);
// 				layer_clear();
// 			}
// 			if ((mods = get_oneshot_locked_mods())) {
// 				clear_oneshot_locked_mods();
// 				unregister_mods(mods);
// 				layer_clear();
// 			}
//         }
		
//         break;
//     }
// 	return true;
// };
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == RELEASE && record->event.pressed) {
        bool rc = true;
        uint8_t mods = 0;
        if ((mods = get_oneshot_mods()) && !has_oneshot_mods_timed_out()) {
            clear_oneshot_mods();
            unregister_mods(mods);
			layer_clear();
            rc = false;
        }
        if ((mods = get_oneshot_locked_mods())) {
            clear_oneshot_locked_mods();
            unregister_mods(mods);
			layer_clear();
            rc = false;
        }
        return rc;
    }
    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_DEFAULT] = LAYOUT_preonic_1x2uC(							
		KC_GRV,			KC_1,			KC_2,			KC_3, 			KC_4, 			KC_5, 			KC_6, 			KC_7, 			KC_8, 			KC_9, 			KC_0, 			KC_MINS,
		KC_TAB,			KC_Q, 			KC_W,			KC_E, 			KC_R, 			KC_T, 			KC_Y, 			KC_U, 			KC_I, 			KC_O, 			KC_P, 			KC_BSPC,
		KC_ESC,			KC_A, 			KC_S,			KC_D, 			KC_F, 			KC_G, 			KC_H, 			KC_J, 			KC_K, 			KC_L, 			KC_SCLN, 		KC_QUOT,
		TO(1),			KC_Z,   		KC_X,			KC_C, 			KC_V, 			KC_B, 			KC_N, 			KC_M, 			KC_COMM, 		KC_DOT, 		KC_SLSH, 		KC_ENT,
		RELEASE,		KC_LCTL, 		OSM(MOD_LGUI), 	OSM(MOD_LALT), 	OSM(MOD_LSFT), 			KC_SPC,					OSM(MOD_RALT), 	TO(2), 			KC_F13, 		TO(3),			KC_DEL
		),

	[_NUMPAD] = LAYOUT_preonic_1x2uC(	
		KC_GRV, 		KC_1, 			KC_2, 			KC_3, 			KC_4, 			KC_5, 			KC_6, 			KC_7, 			KC_8, 			KC_9, 			KC_0, 			KC_MINS,
		KC_TAB, 		KC_LBRC, 		KC_RBRC, 		KC_DLR, 		RALT(KC_U), 	KC_NO, 			KC_NO, 			KC_7, 			KC_8, 			KC_9, 			KC_NO, 			KC_BSPC,
		KC_ESC, 		KC_BSLS, 		KC_SLSH, 		KC_MINS, 		KC_EQL, 		KC_NO, 			KC_NO, 			KC_4, 			KC_5, 			KC_6, 			KC_SCLN, 		KC_QUOT,
		KC_NO, 			KC_NO, 			KC_NO, 			KC_NO, 			KC_NO, 			KC_NO, 			KC_NO, 			KC_1, 			KC_2, 			KC_3, 			KC_SLSH, 		KC_ENT,
		RELEASE, 		OSM(MOD_LCTL), 	OSM(MOD_LGUI), 	OSM(MOD_LALT), 	OSM(MOD_LSFT), 			KC_SPC, 				KC_0, 			KC_COMM, 		KC_DOT, 		KC_NO, 			KC_DEL
		),
	[_ARROWS_AND_OTHER] = LAYOUT_preonic_1x2uC(	
		KC_GRV, 		KC_1, 			KC_2, 			KC_3, 			KC_4, 			KC_5, 			KC_6, 			KC_7, 			KC_8, 			KC_9, 			KC_0, 			KC_MINS,
		KC_TAB, 		KC_NO, 			KC_NO, 			KC_UP, 			KC_NO, 			KC_NO, 			KC_NO, 			KC_PSCR, 		KC_SCRL, 		KC_PAUS, 		KC_NO, 			KC_BSPC,
		KC_ESC, 		KC_NO, 			KC_LEFT, 		KC_DOWN, 		KC_RGHT, 		KC_NO, 			KC_NO, 			KC_INS, 		KC_HOME, 		KC_PGUP, 		KC_NO, 			KC_NO,
		KC_NO, 			KC_NO, 			KC_NO, 			KC_NO, 			KC_NO, 			KC_NO, 			KC_NO, 			KC_DEL, 		KC_END, 		KC_PGDN, 		KC_NO, 			KC_ENT,
		RELEASE, 		OSM(MOD_LCTL), 	OSM(MOD_LGUI), 	OSM(MOD_LALT), 	OSM(MOD_LSFT), 			KC_SPC, 				KC_NO, 			KC_NO, 			KC_NO, 			KC_NO, 			KC_DEL
		),
	[_FUNCTION_AND_MEDIA] = LAYOUT_preonic_1x2uC(	
		KC_GRV, 		KC_1, 			KC_2, 			KC_3, 			KC_4, 			KC_5, 			KC_6, 			KC_7, 			KC_8, 			KC_9, 			KC_0, 			KC_MINS,
		KC_TAB, 		KC_NO, 			KC_MNXT, 		KC_VOLU, 		KC_MUTE, 		KC_NO, 			KC_NO, 			KC_F7, 			KC_F8, 			KC_F9, 			KC_NO, 			KC_BSPC,
		KC_ESC, 		KC_NO, 			KC_MPRV, 		KC_VOLD, 		KC_MPLY, 		KC_NO, 			KC_NO, 			KC_F4, 			KC_F5, 			KC_F6, 			KC_NO, 			KC_NO,
		KC_NO, 			KC_NO, 			KC_NO, 			KC_NO, 			KC_NO, 			KC_NO, 			KC_NO, 			KC_F1, 			KC_F2, 			KC_F3, 			KC_NO, 			KC_ENT,
		RELEASE, 		OSM(MOD_LCTL), 	OSM(MOD_LGUI), 	OSM(MOD_LALT), 	OSM(MOD_LSFT), 			KC_SPC, 				KC_F10, 		KC_F11, 		KC_F12, 		KC_NO, 			KC_DEL
		)

};

#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {

};
#endif // defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
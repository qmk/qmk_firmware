#include QMK_KEYBOARD_H


enum tap{
  TD_CTCPS = 0,
  TD_SLNUM
};
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_CTCPS] = ACTION_TAP_DANCE_DOUBLE(KC_LCTL, KC_CAPS),
    [TD_SLNUM] = ACTION_TAP_DANCE_DOUBLE(KC_PSLS, KC_NUM)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_all(
		KC_ESC,   KC_F1,  KC_F2,  KC_F3,  KC_F4, KC_F5, KC_F6,  KC_F7,  KC_F8,   KC_F9,   KC_F10, KC_F11,  KC_F12, KC_DEL,             KC_PGUP,  KC_PGDN,  KC_MUTE,
		KC_GRV,   KC_1,   KC_2,   KC_3,   KC_4,  KC_5,  KC_6,   KC_7,   KC_8,    KC_9,    KC_0,   KC_MINS, KC_EQL, KC_BSPC,            TD(TD_SLNUM), KC_PAST,
		KC_TAB,   KC_Q,   KC_W,   KC_E,   KC_R,  KC_T,  KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,   KC_LBRC, KC_RBRC,KC_BSLS,            KC_P7,    KC_P8,    KC_P9,    KC_PMNS,
		KC_LCTL,  KC_A,   KC_S,   KC_D,   KC_F,  KC_G,  KC_H,   KC_J,   KC_K,    KC_L,    KC_SCLN,KC_QUOT,         KC_ENT,             KC_P4,    KC_P5,    KC_P6,    KC_PPLS,
		KC_LSFT,  KC_Z,   KC_X,   KC_C,   KC_V,  KC_B,  KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH,KC_RSFT, KC_UP,                      KC_P1,    KC_P2,    KC_P3,
		TD(TD_CTCPS), KC_LGUI,KC_LALT,                      KC_SPC,                  KC_RALT, MO(2),  KC_LEFT, KC_DOWN,KC_RGHT,                      KC_P0,    KC_PDOT,  KC_PENT
    ),

    [1] = LAYOUT_all(
	    RGB_TOG,  RGB_MOD,RGB_HUI,RGB_SAI,KC_NO, KC_NO, KC_NO,  KC_NO,  KC_NO,   KC_NO,   KC_NO,  KC_NO,   KC_NO,  KC_NO,              KC_NO,    KC_NO,    KC_TRNS,
		KC_NO,    KC_NO,  KC_NO,  KC_NO,  KC_NO, KC_NO, KC_NO,  KC_NO,  KC_NO,   KC_NO,   KC_NO,  KC_NO,   KC_NO,  KC_NO,              KC_NO,    KC_NO,
		KC_NO,    KC_MPLY,KC_MPRV,KC_MNXT,KC_NO, KC_NO, KC_NO,  KC_NO,  KC_NO,   KC_NO,   KC_NO,  KC_NO,   KC_NO,  KC_NO,              KC_NO,    KC_NO,    KC_NO,    KC_NO,
		KC_NO,    KC_MSTP,KC_NO,  KC_NO,  KC_NO, KC_NO, KC_NO,  KC_NO,  KC_NO,   KC_NO,   KC_NO,  KC_NO,   KC_NO,                      KC_NO,    KC_NO,    KC_NO,    KC_NO,
		KC_TRNS,  KC_NO,  KC_NO,  KC_NO,  KC_NO, KC_NO, KC_NO,  KC_NO,  KC_NO,   KC_NO,   KC_NO,  KC_TRNS, RGB_VAI,                    KC_NO,    KC_NO,    KC_NO,
		KC_NO,    KC_NO,  KC_NO,                        KC_NO,                   MO(3),   KC_TRNS,RGB_SPI, RGB_VAD,RGB_SPD,                      KC_NO,    KC_NO,    KC_NO
    ),

    [2] = LAYOUT_all(
	    RGB_TOG,  RGB_MOD,RGB_HUI,RGB_SAI,KC_NO, KC_NO, KC_NO,  KC_NO,  KC_NO,   KC_NO,   KC_NO,  KC_NO,   KC_NO,  KC_NO,              KC_NO,    KC_NO,    KC_TRNS,
		KC_NO,    KC_NO,  KC_NO,  KC_NO,  KC_NO, KC_NO, KC_NO,  KC_NO,  KC_NO,   KC_NO,   KC_NO,  KC_NO,   KC_NO,  KC_NO,              KC_NUM,   KC_NO,
		KC_NO,    KC_MPLY,KC_MPRV,KC_MNXT,KC_NO, KC_NO, KC_NO,  KC_NO,  KC_NO,   KC_NO,   KC_NO,  KC_NO,   KC_NO,  KC_NO,              KC_NO,    KC_NO,    KC_NO,    KC_NO,
		KC_NO,    KC_MSTP,KC_NO,  KC_NO,  KC_NO, KC_NO, KC_NO,  KC_NO,  KC_NO,   KC_NO,   KC_NO,  KC_NO,   KC_NO,                      KC_NO,    KC_NO,    KC_NO,    KC_NO,
		KC_TRNS,  KC_NO,  KC_NO,  KC_NO,  KC_NO, KC_NO, KC_NO,  KC_NO,  KC_NO,   KC_NO,   KC_NO,  KC_TRNS, RGB_VAI,                    KC_NO,    KC_NO,    KC_NO,
		KC_NO,    KC_NO,  KC_NO,                        KC_NO,                   MO(3),   KC_TRNS,RGB_SPI, RGB_VAD,RGB_SPD,                      KC_NO,    KC_NO,    KC_NO
    ),

    [3] = LAYOUT_all(
		RGB_TOG,RGB_MOD,RGB_HUI,RGB_SAI,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,    KC_NO,             KC_NO,    KC_NO,    KC_TRNS,
		QK_BOOT,KC_NO,  KC_NO,  KC_NO,    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,    KC_NO,             KC_NO,    KC_NO,
		KC_NO,  KC_NO,  KC_NO,  KC_NO,    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,    KC_NO,             KC_NO,    KC_NO,    KC_NO,    KC_NO,
		KC_NO,  KC_NO,  KC_NO,  KC_NO,    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,                       KC_NO,    KC_NO,    KC_NO,    KC_NO,
		KC_NO,  KC_NO,  KC_NO,  KC_NO,    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  RGB_VAI,                     KC_NO,    KC_NO,    KC_NO,
		KC_NO,  KC_NO,  KC_NO,                            KC_NO,                  KC_TRNS,KC_TRNS,RGB_SPI,RGB_VAD,  RGB_SPD,                     KC_NO,    KC_NO,    KC_NO
    )

};

layer_state_t layer_state_set_user(layer_state_t state) {
	palSetPadMode(GPIOC,  0, PAL_MODE_OUTPUT_PUSHPULL);
    switch (get_highest_layer(state)) {
        case 0:
            palClearPad(GPIOC, 0);
            break;
        case 1:
            palSetPad(GPIOC, 0);
            break;
		case 2:
            palClearPad(GPIOC, 0);
            break;
        case 3:
			palClearPad(GPIOC, 0);//亮
            break;
        default:
            break;
    }
  return state;
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [1] = { ENCODER_CCW_CW(KC_NO, KC_NO)},
    [2] = { ENCODER_CCW_CW(KC_WH_D, KC_WH_U)},
    [3] = { ENCODER_CCW_CW(RGB_RMOD, RGB_MOD)},
};
#endif

bool dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0:
            if(active) { layer_on(0); } else { layer_off(0); }
            break;
        case 1:
            if(active) { layer_on(1); } else { layer_off(1); }
            break;
    }
    return true;
};


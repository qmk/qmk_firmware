#include QMK_KEYBOARD_H

#include "mousekey.h"

enum custom_keycodes {
    AUTOCLICK_TOGGLE = SAFE_RANGE,
    RAPID_CLICK,
    CYCLE_CLICK_SPEEDS
};

enum my_layers {
	_ALPHA_LAYER,
	_VIM_EDITING_LAYER,
	_MOUSE_LAYER,
	_HYPER_LAYER
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_ALPHA_LAYER] = LAYOUT_65_ansi(
		KC_GESC,		KC_1,		KC_2,	KC_3,	KC_4,	KC_5,	KC_6,	KC_7,	KC_8,		KC_9,	KC_0,		KC_MINUS,		KC_EQUAL,		KC_BSPACE,	KC_HOME,
		KC_TAB,			KC_Q,		KC_W,	KC_E,	KC_R,	KC_T,	KC_Y,	KC_U,	KC_I,		KC_O,	KC_P,		KC_LBRACKET,	KC_RBRACKET,	KC_BSLASH,	KC_PGUP,
		KC_LCTRL,		KC_A,		KC_S,	KC_D,	KC_F,	KC_G,	KC_H,	KC_J,	KC_K,		KC_L,	KC_SCOLON,	KC_QUOTE,						KC_ENTER,	KC_PGDOWN,
		KC_LSHIFT,		KC_Z,		KC_X,	KC_C,	KC_V,	KC_B,	KC_N,	KC_M,	KC_COMMA,	KC_DOT,	KC_SLASH,	KC_RSHIFT,						KC_UP,		KC_END,
		KC_CAPSLOCK,	KC_LGUI,	FN_MO13,				KC_SPACE,				FN_MO23,	KC_RALT,	KC_RCTRL,	KC_LEFT,					KC_DOWN,	KC_RIGHT
    ),
    [_VIM_EDITING_LAYER] = LAYOUT_65_ansi(
		KC_GRAVE,	KC_F1,		KC_F2,		KC_F3,		KC_F4,		KC_F5,		KC_F6,		KC_F7,		KC_F8,		KC_F9,		KC_F10,		KC_F11,		KC_F12,		KC_DELETE,	KC_INSERT,
		KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_HOME,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_SCROLLLOCK,
		KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_LEFT,	KC_DOWN,	KC_UP,		KC_RIGHT,	KC_TRNS,	KC_TRNS,				KC_TRNS,	KC_PAUSE,
		KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_END,	KC_TRNS,	KC_TRNS,	KC_TRNS,		KC_TRNS,				KC_VOLU,	KC_PSCREEN,
		KC_TRNS,	KC_TRNS,	KC_TRNS,							KC_MPLY,						KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_MPRV,					KC_VOLD,	KC_MNXT
    ),
    [_MOUSE_LAYER] = LAYOUT_65_ansi(
		KC_GRAVE,	KC_F1,				KC_F2,		KC_F3,			KC_F4,		KC_F5,		KC_F6,		KC_F7,		KC_F8,		KC_F9,		KC_F10,		KC_F11,		KC_F12,		KC_TRNS,	KC_TRNS,
		KC_ACL0,	KC_BTN1,			KC_MS_U,	KC_BTN2,		KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_BTN4,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
		KC_ACL1,	KC_MS_L,			KC_MS_D,	KC_MS_R,		KC_TRNS,	KC_TRNS,	KC_WH_L,	KC_WH_D,	KC_WH_U,	KC_WH_R,	KC_TRNS,			KC_TRNS,		KC_TRNS,	KC_TRNS,
		KC_ACL2,	AUTOCLICK_TOGGLE,	KC_BTN3,	RAPID_CLICK,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_BTN5,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,				KC_TRNS,	KC_TRNS,
		CYCLE_CLICK_SPEEDS,	KC_TRNS,	KC_TRNS,								KC_TRNS,							KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,				KC_TRNS,	KC_TRNS
    ),
    [_HYPER_LAYER] = LAYOUT_65_ansi(
		DYN_REC_STOP,	DYN_REC_START1,		DYN_REC_START2,		KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
		KC_NO,			DYN_MACRO_PLAY1,	DYN_MACRO_PLAY2,	KC_NO,		KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
		KC_NO,			KC_NO,				KC_NO,				KC_NO,		KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,				KC_TRNS,	KC_TRNS,
		KC_LSHIFT,		KC_NO,				KC_NO,				RGB_HUI,	RGB_SAI,	RGB_VAI,	RGB_SPI,	RGB_MOD,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,				KC_TRNS,	KC_TRNS,
		KC_TRNS,		KC_TRNS,			KC_TRNS,									RGB_TOG,							KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,				KC_TRNS,	KC_TRNS
    )
};

static bool autoclick = false;
static bool autoclick_state = false;
static uint16_t autoclick_timer = 0;

int clickspeed_set = 0;
#define CLICKSPEEDS 4
const int clickspeed_sets[CLICKSPEEDS] = {0, 20, 100, 1000};
int press_interval = clickspeed_sets[0];

void matrix_scan_user(void) {
  if (autoclick && timer_elapsed(autoclick_timer) > (autoclick_state ? 1 : press_interval)) {
    if (autoclick_state) {
      mousekey_off(KC_MS_BTN1);
    } else {
      mousekey_on(KC_MS_BTN1);
    }
    mousekey_send();
    autoclick_state = !autoclick_state;
    autoclick_timer = timer_read();
  }
}

bool toggle_status = false;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case AUTOCLICK_TOGGLE:
            if (record->event.pressed) {
                autoclick = !autoclick;
                autoclick_timer = timer_read();
            }
            break;
        case RAPID_CLICK:
            if (record->event.pressed){
                toggle_status = autoclick;
                autoclick = true;
                press_interval = 0;
            } else{
                autoclick = toggle_status;
                press_interval = clickspeed_sets[clickspeed_set];
            }
            break;
        case CYCLE_CLICK_SPEEDS:
            if(record->event.pressed){
                clickspeed_set++;
                clickspeed_set %= CLICKSPEEDS;
                press_interval = clickspeed_sets[clickspeed_set];
            }
            break;
    }    
    
    return true;
};

// show green indicator for layers with a keybind
void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (get_highest_layer(layer_state) > 0) {
        uint8_t layer = get_highest_layer(layer_state);

        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t index = g_led_config.matrix_co[row][col];

                if (index >= led_min && index <= led_max && index != NO_LED &&
                keymap_key_to_keycode(layer, (keypos_t){col,row}) > KC_TRNS) {
                    rgb_matrix_set_color(index, 0x00, 0xFF, 0x00);
                }
            }
        }
    }

}
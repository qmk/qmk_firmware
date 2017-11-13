#include "mitosis.h"

enum mitosis_layers
{
	BASE,
	SYMB,
  NUM
};

enum mitosis_keycodes
{
  FNKEY = SAFE_RANGE,
  SHIFT
};

#define LONGPRESS_DELAY 150
#define LAYER_TOGGLE_DELAY 300

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[BASE] = {
  {KC_Q,             KC_W,               KC_E,    KC_R,              KC_T,                 KC_Y,            KC_U,             KC_I,    KC_O,               KC_P          },
  {KC_A,             KC_S,               KC_D,    KC_F,              KC_G,                 KC_H,            KC_J,             KC_K,    KC_L,               KC_QUOT       },
  {CTL_T(KC_ESC),    KC_Z,               KC_X,    KC_C,              KC_V,                 KC_B,            KC_N,             KC_M,    KC_SCLN,            GUI_T(KC_ENT) },
  {XXXXXXX,          LT(SYMB, KC_MHEN),  KC_LALT, LT(NUM, KC_TAB),   KC_RPRN,              KC_LPRN,         LT(NUM, KC_TAB),  KC_RALT, LT(SYMB, KC_HENK),  XXXXXXX       },
  {XXXXXXX,          KC_LGUI,            KC_LGUI, LT(SYMB, KC_ENT),  SFT_T(KC_SPC),        SFT_T(KC_SPC),   LT(SYMB, KC_ENT), KC_RGUI, KC_RGUI,            XXXXXXX       }
},


[SYMB] = {
  {KC_ESC,  KC_GRV,  XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, KC_MINS, KC_EQL,  KC_BSLS, KC_DEL  },
  {KC_TAB,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, KC_LBRC, KC_RBRC, KC_BSPC },
  {_______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, KC_COMM, KC_DOT,  KC_SLSH, _______ },
  {XXXXXXX, _______, _______, _______, _______,       _______, _______, _______, _______, XXXXXXX },
  {XXXXXXX, _______, _______, _______, _______,       _______, _______, _______, _______, XXXXXXX }
},


[NUM] = {
  {KC_1,    KC_2,    KC_3,    KC_4,    KC_5,          KC_6,    KC_7,    KC_8,    KC_9,    KC_0    },
  {XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,XXXXXXX },
  {XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX },
  {_______, _______, _______, _______, _______,       _______, _______, _______, _______, _______ },
  {XXXXXXX, _______, _______, _______, _______,       _______, _______, _______, _______, XXXXXXX }
}

};

void matrix_scan_user(void) {
    uint8_t layer = biton32(layer_state);

    switch (layer) {
    	case BASE:
    		set_led_off;
    		break;
        case SYMB:
            set_led_blue;
            break;
        case NUM:
            set_led_red;
            break;
        default:
            break;
    }
};

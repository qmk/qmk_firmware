#include QMK_KEYBOARD_H

// Layer names
enum{
  // - Base layer:
  _BASE,
  // - Symbols, numbers, and functions:
  _FN
};

#define OLED_DISABLE_TIMEOUT
#define TAPPING_TERM 200

//Tap Dance Declarations
enum {
  TD_RST = 0,
  TD_DBQT = 1
};

void dance_rst_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count >= 2) {
    reset_keyboard();
    reset_tap_dance(state);
  }
}

//All tap dance functions would go here. Only showing this one.
qk_tap_dance_action_t tap_dance_actions[] = {
 [TD_RST] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, NULL, dance_rst_reset),
 [TD_DBQT] = ACTION_TAP_DANCE_DOUBLE (KC_QUOTE, KC_DQT)
};

#define FN MO(_FN)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Base layer
     *        ┌────┐ ┌────┬────┬────┬────┐ ┌────┬────┬────┬────┐   ┌────────────┐
     *        │Del │ │ F1 │ F2 │ F3 │ F4 │ │ F5 │ F6 │ F7 │ F8 │   │OLED DISPLAY│
     *        └────┘ └────┴────┴────┴────┘ └────┴────┴────┴────┘   └────────────┘
     * ┌────┐ ┌────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬─────┐
     * │Home│ │Esc │ Q  │ W  │ E  │ R  │ T  │ Y  │ U  │ I  │ O  │ P  │ -  │BkSp │
     * ├────┤ ├────┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴─────┤
     * │PgUp│ │Tab  │ A  │ S  │ D  │ F  │ G  │ H  │ J  │ K  │ L  │ ;  │  Enter  │
     * ├────┤ ├─────┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬───────┤
     * │PgDn│ │L_Shft │ Z  │ X  │ C  │ V  │ B  │ N  │ M  │ ,  │ .  │ /  │R_Shft │
     * ├────┤ ├──────┬┴────┼────┴─┬──┴────┴───┬┴────┴────┴──┬─┴────┼────┴─┬─────┤
     * │END │ │L_Ctrl│L_GUI│L_Alt │    FN     │    SPACE    │R_Ctrl│R_GUI │R_Alt│
     * └────┘ └──────┴─────┴──────┴───────────┴─────────────┴──────┴──────┴─────┘
*/
[_BASE] = LAYOUT_split_space(
               KC_DEL,       KC_F1, KC_F2, KC_F3, KC_F4,       KC_F5, KC_F6, KC_F7, KC_F8,
	KC_HOME,     KC_ESC, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,  KC_MINUS,  KC_BSPC,
	KC_PGUP,       KC_TAB, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,     KC_ENT,
	KC_PGDN,         KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM,   KC_DOT,    KC_SLSH,  KC_RSFT,
	KC_END,      KC_LCTL,   KC_LGUI,   KC_LALT,       FN,       KC_SPACE,     KC_RCTL,   KC_RGUI,   KC_RALT
),

/* Function layer
     *        ┌────┐ ┌────┬────┬────┬────┐ ┌────┬────┬────┬────┐   ┌────────────┐
     *        │RSET│ │F9  │F10 │F11 │F12 │ │F13 │F14 │F15 │PrSc│   │OLED DISPLAY│
     *        └────┘ └────┴────┴────┴────┘ └────┴────┴────┴────┘   └────────────┘
     * ┌────┐ ┌────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬─────┐
     * │ `  │ │Esc │ 1  │ 2  │ 3  │ 4  │ 5  │ 6  │ 7  │ 8  │ 9  │ 0  │ _  │     │
     * ├────┤ ├────┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴─────┤
     * │ ~  │ │Tab  │ !  │ @  │ #  │ $  │ %  │ ^  │ &  │ *  │ (  │ )  │         │
     * ├────┤ ├─────┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬───────┤
     * │ │  │ │L_Shft │    │    │    │    │    │    │    │    │ [  │  ] │       │
     * ├────┤ ├──────┬┴────┼────┴─┬──┴────┴───┬┴────┴────┴──┬─┴────┼────┴─┬─────┤
     * │ \  │ │L_Ctrl│L_GUI│L_Alt │           │             │      │      │     │
     * └────┘ └──────┴─────┴──────┴───────────┴─────────────┴──────┴──────┴─────┘
*/

[_FN] = LAYOUT_split_space(
               TD(TD_RST),      KC_F9, KC_F10, KC_F11, KC_F12,        KC_F13, KC_F14, KC_F15, KC_PSCR,
	KC_GRAVE,     _______, KC_1,  KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_UNDS,  _______,
	KC_TILD,      _______,  KC_EXLM,   KC_AT,     KC_HASH,   KC_DLR,    KC_PERC,   KC_CIRC,   KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN, TD(TD_DBQT),
	KC_PIPE,         _______,     _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,   KC_LBRC,    KC_RBRC,  _______,
	KC_BSLS,      _______,   _______,   _______,       _______,       _______,     _______,   _______,   _______
)

};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
}

#ifdef OLED_DRIVER_ENABLE
static void render_logo(void) {
  static const char PROGMEM qmk_logo[] = {
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};

  oled_write_P(qmk_logo, false);
}


extern bool oled_initialized;
void matrix_scan_user(void) {
  if(!oled_initialized) {
    wait_ms(200);
        oled_init(0);

  }
 }

uint16_t        oled_timer;
void oled_task_user(void) {

    if (timer_elapsed(oled_timer) > 200000) {
        oled_off();
        return;
    }

            render_logo();

   }

#endif

#include QMK_KEYBOARD_H

enum layers{
  _BASE,
  _SYM,
  _NUM,
  _NAV
};

enum combo_events {
 COMBO_BSPC,
 COMBO_ENT,
 COMBO_TAB,
 COMBO_ESC,
 COMBO_DEL
};

enum custom_keycodes{
	RGBRST = SAFE_RANGE,
};

#define KC_UP_SPC LT(_SYM, KC_SPC)
#define KC_GZ LGUI_T(KC_Z)
#define KC_AA LALT_T(KC_A)
#define KC_CC LCTL_T(KC_C)
#define KC_SF LSFT_T(KC_F)
#define KC_SJ RSFT_T(KC_J)
#define KC_CCOMM RCTL_T(KC_COMM)
#define KC_AQUOT RALT_T(KC_QUOT)
#define KC_GSLSH RGUI_T(KC_SLSH)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
    KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_DEL,   KC_Y,   KC_U,   KC_I,    KC_O,   KC_P,
    KC_AA,   KC_S,   KC_D,  KC_SF,   KC_G,   KC_BSPC,   KC_H,   KC_SJ,  KC_K,    KC_L,   KC_AQUOT,
    KC_GZ,   KC_X,   KC_C,   KC_V,    KC_B,   KC_LSFT,  KC_N,   KC_M,   KC_CCOMM, KC_DOT, KC_GSLSH,
                  MO(_NAV), KC_NO, KC_NO,  KC_UP_SPC, KC_NO,   KC_NO,   KC_RALT
  ),

 [_SYM] = LAYOUT(
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_TRNS, KC_6,    KC_7,    KC_8,    KC_9,     KC_0,
    KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_TRNS, KC_CIRC, KC_AMPR, KC_ASTR, KC_EQUAL, KC_MINS,
    KC_PIPE, KC_BSLS, KC_LPRN, KC_LBRC, KC_SCLN, KC_TRNS, KC_COLN, KC_RBRC, KC_RPRN, KC_PLUS,  KC_UNDS,
                    KC_TRNS,    KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,      KC_TRNS,    KC_TRNS 
  ),

  [_NAV] = LAYOUT(
    KC_HOME, KC_UP,   KC_END,   KC_PGUP, KC_TRNS, RESET,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BSPC,
    KC_LEFT, KC_DOWN, KC_RIGHT, KC_PGDN, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TAB,
    KC_MPRV, KC_MPLY, KC_MNXT,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_VOLD, KC_VOLU, KC_ENT,
                    KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS 
  ),
};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 1) { /* left encoder*/
        switch(biton32(layer_state)){

			 case _NAV:
                if (clockwise) {
                register_code(KC_LCTL);
                tap_code(KC_TAB);
                unregister_code(KC_LCTL);
                } else {
                register_code(KC_LCTL);
				register_code(KC_LSFT);
                tap_code(KC_TAB);
                unregister_code(KC_LCTL);
				unregister_code(KC_LSFT);
                }
                break;

            case _SYM:
                if (clockwise) {
                tap_code(KC_PGUP);
                } else {
                tap_code(KC_PGDN);

                }
                break;

            default:
                if (clockwise){
                    tap_code(KC_WH_U);
                } else{
                    tap_code(KC_WH_D);
                }
                break;
      }
    } else if (index == 0) { /* right encoder */
	           switch(biton32(layer_state)){
				   
            case _SYM:
                if (clockwise) {
                tap_code(KC_MPRV);
                } else {
                tap_code(KC_MNXT);
                }
                break;

            default:
                if (clockwise){
                    tap_code(KC_VOLU);
                } else{
                    tap_code(KC_VOLD);
                }
                break;
        }
    }
}

#ifdef COMBO_ENABLE
const uint16_t PROGMEM combo_bspc[] = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM combo_ent[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM combo_tab[] = {KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM combo_esc[] = {KC_T, KC_Y, COMBO_END};
const uint16_t PROGMEM combo_del[] = {KC_Q, KC_W, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [COMBO_BSPC] = COMBO(combo_bspc,KC_BSPC),
  [COMBO_ENT] = COMBO(combo_ent,KC_ENT),
  [COMBO_TAB] = COMBO(combo_tab,KC_TAB),
  [COMBO_ESC] = COMBO(combo_esc,KC_ESC),
  [COMBO_DEL] = COMBO(combo_del,KC_DEL)
};
#endif

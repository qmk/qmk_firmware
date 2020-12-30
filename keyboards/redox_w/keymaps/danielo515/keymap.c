#include QMK_KEYBOARD_H
#include "danielo515.h"

// Shortcut to make keymap more readable
# define SYM_L   OSL(_SYMB)

# define KC_ALAS LALT_T(KC_PAST) // alt or keypad *
# define KC_CTPL LCTL_T(KC_BSLS) // <C-\>

# define KC_NAGR LT(_NAV, KC_GRV)
# define KC_NAMI LT(_NAV, KC_MINS)
# define AD_ESC LT(_ADJUST, KC_ESC)
# define NAV_SPC LT(_NAV, KC_SPACE)

# define KC_ADPU LT(_ADJUST, KC_PGUP)
# define WIN_LEFT WIN_TO_LEFT
# define WIN_RIGHT WIN_TO_RIGHT
# define COPY_CUT TD(COPY_CUT)
# define TD_PASTE TD(PASTE_DANCE)
# define CTL OSM(MOD_LCTL)
# define ALT OSM(MOD_LALT)
# define GUI OSM(MOD_LGUI)
# define ENT_SYM LT(_SYMB, KC_ENT)
# define __S LT(_S,KC_S)
# define OSX_BACK LGUI(KC_GRV)
// Which key do you use to enter a layer
# define ENTRY _______


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
	 KC_EQL  ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,                                            KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,KC_DQUO ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
	 KC_TAB  ,KC_Q    ,KC_W    ,KC_E    ,KC_R    ,KC_T    ,TD_PASTE,                          KC_INS  ,KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,CMD_MINS,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
	 KC_PIPE ,KC_A    ,__S     ,FN_D    ,FN_F    ,KC_G    ,COPY_CUT,                          KC_UNDS ,HYPR_H  ,ALT_J   ,CTL_K   ,KC_L    ,TD_CLN  ,SFT_QUOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
	 KC_BSLS ,KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B    ,KC_DEL  ,KC_PLUS ,        ALT_TAB ,AD_ESC  ,KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,KC_ASTR ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
	 CTL     ,ALT     ,KC_LEFT ,KC_RIGHT,     GUI     ,    SHIFT   ,KC_BSPC ,        KC_LEAD ,NAV_SPC ,    ENT_SYM,     KC_LBRC ,KC_RBRC ,KC_DOWN ,KC_UP
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_SYMB] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                              ┌────────┬────────┬────────┬────────┬────────┬────────┐
	 _______ ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,                                               KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,KC_F12  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                            ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
	 _______ ,KC_EXLM ,KC_DLR  ,KC_LCBR ,KC_RCBR ,KC_PIPE ,_______ ,                             _______ ,KC_PSLS ,KC_P7 	,KC_P8 	 ,KC_P9   ,KC_PERC ,KC_BSPC ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                            ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
	 _______ ,KC_AT   ,KC_DLR  , KC_LPRN, KC_RPRN,KC_GRV  ,_______ ,                             _______ ,KC_PENT ,KC_P4 	,KC_P5   ,KC_P6   ,KC_PPLS ,KC_PMNS ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐          ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
	 _______ ,KC_PERC ,KC_CIRC ,KC_LBRC ,KC_RBRC ,KC_TILD ,_______ ,_______ ,           _______ ,_______ ,KC_COLN ,KC_P1 	,KC_P2   ,KC_P3   ,KC_PSLS ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤          ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
	 _______ ,_______ ,_______ ,_______ ,     _______ ,    _______ ,_______ ,           _______ ,_______ ,    ENTRY   ,     KC_P0   ,KC_PDOT ,KC_PAST ,XXXXXXX
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘          └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_NAV] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
	 _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
	 XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,                          _______ ,SFT_LEFT_END,SFT_LEFT,SFT_RIGHT,SFT_RIGHT_END ,XXXXXXX ,KC_F12  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
	 XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,                          _______ ,KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RIGHT,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
	 XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,_______ ,        _______ ,XXXXXXX ,KC_HOME ,CTL_LEFT,CTL_RIGHT,KC_END,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
	 XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,     _______ ,    _______ ,_______ ,        _______ ,  ENTRY ,    KC_MUTE ,     KC_VOLD ,KC_VOLU ,WIN_LEFT,WIN_RIGHT
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),
  [_ADJUST] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
	 XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                                            XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
	 XXXXXXX ,RESET   ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                          XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
	 XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                          XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
	 XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,        KC_MUTE ,_______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
	 XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,     XXXXXXX ,    XXXXXXX ,XXXXXXX ,        XXXXXXX ,XXXXXXX ,    XXXXXXX ,     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),
[_F] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
	 XXXXXXX ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,                                            KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,KC_F11  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
	 XXXXXXX ,XXXXXXX ,ALL_WIN ,EXPOSE  ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                          XXXXXXX ,XXXXXXX ,KC_F4   ,KC_F5   ,KC_F6   ,XXXXXXX ,KC_F12  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
	 XXXXXXX ,XXXXXXX ,SAVE    ,OSX_BACK ,ENTRY ,XXXXXXX ,XXXXXXX ,                          XXXXXXX  ,KC_PSCR ,KC_F1   ,KC_F2   ,KC_F3   ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
	 XXXXXXX ,UNDO    ,REDO    ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,        XXXXXXX ,_______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
	 XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,     XXXXXXX ,    XXXXXXX ,XXXXXXX ,        KC_PGUP ,KC_PGDOWN ,    XXXXXXX ,     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),
  [_D] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
	 XXXXXXX ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,                                            KC_A   ,KC_B   ,KC_C   ,KC_D   ,KC_E  ,KC_F  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
	 XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                          _______ ,KC_LBRACKET ,KC_P7 	,KC_P8 	 ,KC_P9   ,KC_PERC ,KC_KP_MINUS ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
	 XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,KC_F5 ,KC_F2 ,XXXXXXX ,                          _______ ,KC_RBRACKET ,KC_P4   ,KC_P5   ,KC_P6   ,KC_PPLS ,KC_PAST ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
	 XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,        _______ ,_______ ,KC_COLN ,KC_P1 	,KC_P2   ,KC_P3   ,KC_PSLS ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
	 XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,     XXXXXXX ,    XXXXXXX ,_______ ,        _______ ,_______ ,    KC_P0   ,     KC_COMMA   ,KC_PDOT ,KC_PAST ,XXXXXXX
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),
	[_S] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
	 XXXXXXX ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,                                            KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
	 XXXXXXX ,XXXXXXX ,XXXXXXX ,KC_LT   ,KC_GT   ,XXXXXXX ,XXXXXXX ,                          XXXXXXX ,KC_HASH ,KC_LCBR ,KC_RCBR ,KC_ASTR ,KC_PERC ,KC_DLR ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
	 XXXXXXX ,XXXXXXX ,_______ ,KC_EQL  ,F_ARROW ,KC_GRAVE,XXXXXXX ,                          XXXXXXX ,KC_AMPR ,KC_LPRN ,KC_RPRN ,CLN_EQ  ,KC_PLUS ,KC_PIPE ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
	 XXXXXXX ,XXXXXXX ,XXXXXXX ,KC_CIRC ,ARROW  ,XXXXXXX ,XXXXXXX ,XXXXXXX ,        XXXXXXX ,XXXXXXX ,KC_EXLM ,KC_TILD ,KC_CIRC ,ARROW  ,KC_BSLASH,IARROW  ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
	 XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,     XXXXXXX ,    XXXXXXX ,_______ ,        XXXXXXX ,ENTRY ,    XXXXXXX ,     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  )

};

void alt_tab_activated(void){
    layer_on(_NAV);
};
void alt_tab_deactivated(void){
    layer_off(_NAV);
};

layer_state_t layer_state_set_user(layer_state_t state) {
	switch (get_highest_layer(state)) {
		case _QWERTY:
			set_led_off;
			break;
		case _SYMB:
        case _D:
			set_led_green;
			break;
		case _NAV:
			set_led_blue;
			break;
		case _ADJUST:
			set_led_red;
			break;
		case _S:
			set_led_magenta;
			break;
		case _F:
			set_led_white;
			break;
		default:
			break;
	}
  return state;
}



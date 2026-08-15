/*
                                             ▀▀▀▀▀     ▀▀▀▀▀          ▀▀█▀▀
                                             ▄▀▀▀▄  ▄  ▄▀▀▀▄  ▄  ▄▀▀▀▄  █  ▄▀▀▀▄
                                             █   █  █  █   █  █  █   █  █  █   █
                                              ▀▀▀   █   ▀▀▀   █   ▀▀▀   ▀   ▀▀▀
                                                    █      ▄▄▄█▄▄▄    █   █
                                                    ▀      █  █  █     █▄█
                                                  ▀▀▀▀▀    █  █  █      ▀
                                                           ▀  ▀  ▀  G A M M A C H O

▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
*/

#include QMK_KEYBOARD_H

// ┌─────────────────────────────────────────────────┐
// │ d e f i n e   l a y e r s                       │
// └─────────────────────────────────────────────────┘
enum layers {
    _WINDOWS = 0,
    _MAC = 1,
    _NAV = 2,
    _MOUSE = 3,
    _M_FNC = 4,
    _W_FNC = 5,
    _M_NUM = 6,
    _W_NUM = 7,
};

// ┌─────────────────────────────────────────────────┐
// │ d e f i n e   t a p   d a n c e                 │
// └─────────────────────────────────────────────────┘
enum tap_dances {
    TD_BASE,
    TD_SP,
    TD_LBK,
    TD_RBK,
    TD_LPR,
    TD_RPR,
    TD_LYR,
};

// ┌─────────────────────────────────────────────────┐
// │ d e f i n e   k e y c o d e s                   │
// └─────────────────────────────────────────────────┘
enum custom_keycodes {
    DRAG_SCROLL = SAFE_RANGE,
    CC_EXLM,
    CC_AT,
    CC_HASH,
    CC_DLR,
    CC_PERC,
    CC_CIRC,
    CC_AMPR,
    CC_ASTR,
    CC_LPRN,
    CC_RPRN,
    CC_PLUS,
    CC_PIPE,
    CC_UNDS,
    CC_LABK,
    CC_RABK,
    CC_LCBR,
    CC_RCBR,
    CC_TILD,
    MAKE_H,
    SNAP
};

// declare global value
int shifted_key_delay_ms = 30;

// ┌─────────────────────────────────────────────────┐
// │ d e f i n e   a l i a s                         │
// └─────────────────────────────────────────────────┘
#define MAC      DF(_MAC)
#define WINDOWS  DF(_WINDOWS)
#define NAV      DF(_NAV)
#define MOUSE    DF(_MOUSE)
#define MAC_FNC  DF(_M_FNC)
#define WIN_FNC  DF(_W_FNC)
#define MAC_NUM  DF(_M_NUM)
#define WIN_NUM  DF(_W_NUM)
#define MOU_A   LT(_MOUSE, KC_A)
#define NAV_QUO LT(_NAV, KC_QUOTE)
#define MFNC_Q  LT(_M_FNC, KC_Q)
#define WFNC_Q  LT(_W_FNC, KC_Q)
#define MFNC_P  LT(_M_FNC, KC_P)
#define WFNC_P  LT(_W_FNC, KC_P)
#define MNUM_SP LT(_M_NUM, KC_SPC)
#define WNUM_SP LT(_W_NUM, KC_SPC)
#define HO_LSFT LSFT_T(KC_Z)
#define HO_RSFT RSFT_T(KC_SLSH)
#define LSFT_F  LSFT_T(KC_F)
#define RSFT_J  RSFT_T(KC_J)
#define NV_LSFT LSFT_T(CC_HASH)
#define MSNAP LGUI(LSFT(LCTL(KC_4)))
#define WSNAP LSFT(LGUI(KC_S))

void shifted_key_delay(int keycode) {
    register_code(KC_LSFT);
    wait_ms(shifted_key_delay_ms);
    tap_code(keycode);
    unregister_code(KC_LSFT);
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case HO_LSFT:
            return 120;
        case HO_RSFT:
            return 120;
        case NV_LSFT:
            return 130;
        case MFNC_Q:
            return 150;
        case MFNC_P:
            return 150;
        case MOU_A:
            return 150;
        case NAV_QUO:
            return 150;
        case MNUM_SP:
            return 130;
        case WFNC_Q:
            return 150;
        case WFNC_P:
            return 150;
        case WNUM_SP:
            return 130;
        default:
            return TAPPING_TERM;
    }
}

// Function to handle key events and enable/disable drag scrolling
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    uint8_t state = get_highest_layer(layer_state | default_layer_state);
    switch (keycode) {
        case CC_EXLM:
            if (record->event.pressed) { //KC_EXLM : !
                shifted_key_delay(KC_EXLM); //SEND_STRING("!");
            }
            break;
        case CC_AT:
            if (record->event.pressed) { //KC_AT : @
                shifted_key_delay(KC_AT); //SEND_STRING("@");
            }
            break;
        case CC_HASH:
            if (record->event.pressed) { //KC_HASH : #
                shifted_key_delay(KC_HASH); //SEND_STRING("#");
            }
            break;
        case CC_DLR:
            if (record->event.pressed) {//KC_DLR : $
                shifted_key_delay(KC_DLR); //SEND_STRING("$");
            }
            break;
        case CC_PERC:
            if (record->event.pressed) { //KC_PERC : %
                shifted_key_delay(KC_PERC);//SEND_STRING("%");
            }
            break;
        case CC_CIRC:
            if (record->event.pressed) { //KC_CIRC : ^
                shifted_key_delay(KC_CIRC); //SEND_STRING("^");
            }
            break;
        case CC_AMPR:
            if (record->event.pressed) { //KC_AMPR : &
                shifted_key_delay(KC_AMPR); //SEND_STRING("&");
            }
            break;
        case CC_ASTR:
            if (record->event.pressed) { //KC_ASTR : *
                shifted_key_delay(KC_ASTR); //SEND_STRING("*");
            }
            break;
        case CC_LPRN:
            if (record->event.pressed) { //KC_LPRN : (
                shifted_key_delay(KC_LPRN); //SEND_STRING("(");
            }
            break;
        case CC_RPRN:
            if (record->event.pressed) { //KC_RPRN : )
                shifted_key_delay(KC_RPRN); //SEND_STRING(")");
            }
            break;
        case CC_PLUS:
            if (record->event.pressed) { //KC_PLUS : +
                shifted_key_delay(KC_PLUS); //SEND_STRING("+");
            }
            break;
        case CC_PIPE:
            if (record->event.pressed) { //KC_PIPE : |
                shifted_key_delay(KC_PIPE); //SEND_STRING("|");
            }
            break;
        case CC_UNDS:
            if (record->event.pressed) { //KC_UNDS : _
                shifted_key_delay(KC_UNDS); //SEND_STRING("_");
            }
            break;
        case CC_LABK:
            if (record->event.pressed) { //KC_LABK : <
                shifted_key_delay(KC_LABK); //SEND_STRING("<");
            }
            break;
        case CC_RABK:
            if (record->event.pressed) { //KC_RABK : >
                shifted_key_delay(KC_RABK); //SEND_STRING(">");
            }
            break;
        case CC_LCBR:
            if (record->event.pressed) { //KC_LCBR : {
                shifted_key_delay(KC_LCBR); //SEND_STRING("{");
            }
            break;
        case CC_RCBR:
            if (record->event.pressed) { //KC_RCBR : }
                shifted_key_delay(KC_RCBR); //SEND_STRING("}");
            }
            break;
        case CC_TILD:
            if (record->event.pressed) { //KC_TILD : ~
                shifted_key_delay(KC_TILD);//SEND_STRING("~");
            }
            break;

        case MAKE_H:
            if (record->event.pressed) {
                SEND_STRING("qmk compile -kb totem -km gammacho_38_v1");
                tap_code(KC_ENTER);
            }
            break;
    }
    return true;
}

// Tap Dance definitions
void fn_td_spc_unds(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1) {
		if (state->interrupted)
			tap_code16(KC_SPC);
		else if (state->pressed)
			tap_code16(KC_SPC);
		else
			tap_code16(KC_SPC);
	}
	else if (state->count == 2) {
        shifted_key_delay(KC_MINS);
	}
    else {
        tap_code16(KC_SPC);
    }
}

void fn_td_lbrc_lcbr(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1) {
		if (state->interrupted)
			tap_code16(KC_LBRC);
		else if (state->pressed)
			tap_code16(KC_LBRC);
		else
			tap_code16(KC_LBRC);
	}
	else if (state->count == 2) {
        shifted_key_delay(KC_LBRC);
	}
    else {
		tap_code16(KC_LBRC);
    }
}

void fn_td_rbrc_rcbr(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1) {
		if (state->interrupted)
			tap_code16(KC_RBRC);
		else if (state->pressed)
			tap_code16(KC_RBRC);
		else
			tap_code16(KC_RBRC);
	}
	else if (state->count == 2) {
        shifted_key_delay(KC_RBRC);
	}
    else {
		tap_code16(KC_RBRC);
    }
}

void fn_td_lprn_labk(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1) {
		if (state->interrupted)
			shifted_key_delay(KC_9);
		else if (state->pressed)
			shifted_key_delay(KC_9);
		else
			shifted_key_delay(KC_9);
	}
	else if (state->count == 2) {
        shifted_key_delay(KC_COMM);
	}
    else {
        shifted_key_delay(KC_9);
    }
}

void fn_td_rprn_rabk(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1) {
		if (state->interrupted)
			shifted_key_delay(KC_0);
		else if (state->pressed)
			shifted_key_delay(KC_0);
		else
			shifted_key_delay(KC_0);
	}
	else if (state->count == 2) {
        shifted_key_delay(KC_DOT);
	}
    else {
        shifted_key_delay(KC_0);
    }
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_BASE] = ACTION_TAP_DANCE_DOUBLE(WINDOWS, MAC),
    [TD_SP]   = ACTION_TAP_DANCE_FN(fn_td_spc_unds), // Tap once for space, twice for Underscore
    [TD_LBK]  = ACTION_TAP_DANCE_FN(fn_td_lbrc_lcbr), // Tap once for "[", twice for "{"
    [TD_RBK]  = ACTION_TAP_DANCE_FN(fn_td_rbrc_rcbr), // Tap once for "]", twice for "}"
    [TD_LPR]  = ACTION_TAP_DANCE_FN(fn_td_lprn_labk), // Tap once for "(", twice for "<"
    [TD_RPR]  = ACTION_TAP_DANCE_FN(fn_td_rprn_rabk), // Tap once for ")", twice for ">"
    [TD_LYR]  = ACTION_TAP_DANCE_DOUBLE(TO(WINDOWS), TO(MAC)),

    //[TD_SP]   = ACTION_TAP_DANCE_DOUBLE(KC_SPC, LSFT(KC_MINS)),
    //[TD_LBK]  = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, LSFT(KC_LBRC)),
    //[TD_RBK]  = ACTION_TAP_DANCE_DOUBLE(KC_RBRC, LSFT(KC_RBRC)),
    //[TD_LPR]  = ACTION_TAP_DANCE_DOUBLE(LSFT(KC_9), LSFT(KC_COMM)),
    //[TD_RPR]  = ACTION_TAP_DANCE_DOUBLE(LSFT(KC_0), LSFT(KC_DOT)),
    //[MJ]      = ACTION_TAP_DANCE_DOUBLE(KC_J, KC_J),
    //[WJ]      = ACTION_TAP_DANCE_DOUBLE(KC_J, KC_J),
};

enum combos {
    CO_WESC,
    CO_CAPS,
    CO_SEMI,
    CO_WDEL,
    CO_LANG,
    CO_MIDCLK,
    CO_SCROLL,
    NOLOCK,
    //USE 38 key combo : layer 0 _WINDOWS
    CO_LAYER,
    CO_ESC,
    CO_TAB,
    CO_BSP,
    CO_DEL,
    CO_RTN,
    CO_L_LCLK,
    CO_L_RCLK,
    CO_L_MCLK,
    //ADD NEW COMBOS
    CO_E, //E
    CO_D, //D
    CO_C, //C
    CO_TB, //TAB
    CO_EC, //ESC
    CO_CP, //CAPS
    CO_PL, //+
    CO_AS, //*
    CO_HS, //#
    CO_3   //3
};

const uint16_t PROGMEM COM_WESC[] = {KC_TAB, WFNC_Q, COMBO_END};
const uint16_t PROGMEM COM_CAPS[] = {KC_D, LSFT_F, COMBO_END};
const uint16_t PROGMEM COM_SEMI[] = {KC_COMM, KC_DOT, COMBO_END};
const uint16_t PROGMEM COM_WDEL[] = {WFNC_P, KC_BSPC, COMBO_END};
const uint16_t PROGMEM COM_LANG[] = {RSFT_J, KC_K, COMBO_END};
const uint16_t PROGMEM COM_MIDCLK[] = {MS_BTN1, MS_BTN2, COMBO_END};
const uint16_t PROGMEM COM_SCROLL[] = {KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM COM_NOLOCK[] = {KC_M, KC_COMM, COMBO_END};
//USE 38 key combo : layer 0 _WINDOWS
const uint16_t PROGMEM COM_LAYER[] = {KC_U, KC_I, KC_O, WFNC_P, COMBO_END};
const uint16_t PROGMEM COM_ESC[] = {KC_S, KC_D, LSFT_F, COMBO_END};
const uint16_t PROGMEM COM_TAB[] = {KC_W, KC_E, KC_R, COMBO_END};
const uint16_t PROGMEM COM_BSP[] = {KC_U, KC_I, COMBO_END};
const uint16_t PROGMEM COM_DEL[] = {KC_U, KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM COM_RTN[] = {RSFT_J, KC_K, KC_L, COMBO_END};
//ADD LEFT SIDE COMBO MOUSE KEY
const uint16_t PROGMEM COM_L_LCLK[] = {LSFT_F, KC_G, COMBO_END};
const uint16_t PROGMEM COM_L_RCLK[] = {KC_R, KC_T, COMBO_END};
const uint16_t PROGMEM COM_L_MCLK[] = {KC_V, KC_B, COMBO_END};
//ADD NEW COMBO
const uint16_t PROGMEM COM_E[] = {KC_W, KC_R, COMBO_END};
const uint16_t PROGMEM COM_D[] = {KC_S, LSFT_F, COMBO_END};
const uint16_t PROGMEM COM_C[] = {KC_X, KC_V, COMBO_END};
const uint16_t PROGMEM COM_TB[] = {WFNC_Q, KC_W, KC_R, COMBO_END};
const uint16_t PROGMEM COM_EC[] = {MOU_A, KC_S, LSFT_F, COMBO_END};
const uint16_t PROGMEM COM_CP[] = {HO_LSFT, KC_X, KC_V, COMBO_END};
const uint16_t PROGMEM COM_PL[] = {CC_DLR, KC_MINS, COMBO_END};
const uint16_t PROGMEM COM_AS[] = {CC_AMPR, KC_SLSH, COMBO_END};
const uint16_t PROGMEM COM_HS[] = {CC_AT, CC_DLR, COMBO_END};
const uint16_t PROGMEM COM_3[] = {KC_2, KC_4, COMBO_END};

combo_t key_combos[] = {
  [CO_WESC] = COMBO(COM_WESC, KC_ESC),
  [CO_CAPS] = COMBO(COM_CAPS, KC_CAPS),
  [CO_SEMI] = COMBO(COM_SEMI, KC_SCLN),
  [CO_WDEL] = COMBO(COM_WDEL, KC_DEL),
  [CO_LANG] = COMBO_ACTION(COM_LANG),
  [CO_MIDCLK] = COMBO(COM_MIDCLK, MS_BTN3),
  [CO_SCROLL] = COMBO(COM_SCROLL, DRAG_SCROLL),
  [NOLOCK] = COMBO_ACTION(COM_NOLOCK),
  //USE 38 key combo : layer 0 _WINDOWS
  [CO_LAYER] = COMBO_ACTION(COM_LAYER),
  [CO_ESC] = COMBO(COM_ESC, KC_ESC),
  [CO_TAB] = COMBO(COM_TAB, KC_TAB),
  [CO_BSP] = COMBO(COM_BSP, KC_BSPC),
  [CO_DEL] = COMBO(COM_DEL, KC_DEL),
  [CO_RTN] = COMBO(COM_RTN, KC_ENT),
  [CO_L_LCLK] = COMBO(COM_L_LCLK, MS_BTN1),
  [CO_L_RCLK] = COMBO(COM_L_RCLK, MS_BTN2),
  [CO_L_MCLK] = COMBO(COM_L_MCLK, MS_BTN3),
  //ADD NEW COMBO
  [CO_E] = COMBO(COM_E, KC_E),
  [CO_D] = COMBO(COM_D, KC_D),
  [CO_C] = COMBO(COM_C, KC_C),
  [CO_TB] = COMBO(COM_TB, KC_TAB),
  [CO_EC] = COMBO(COM_EC, KC_ESC),
  [CO_CP] = COMBO(COM_CP, KC_CAPS),
  [CO_PL] = COMBO(COM_PL, CC_PLUS),
  [CO_AS] = COMBO(COM_AS, CC_ASTR),
  [CO_HS] = COMBO(COM_HS, CC_HASH),
  [CO_3] = COMBO(COM_3, KC_3)
};

bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
    /* Disable combo `SOME_COMBO` on layer `_LAYER_A` */
    switch (combo_index) {
        case CO_E:
            if (layer_state_is(_WINDOWS) || layer_state_is(_MAC)) {
                return true;
            }
        case CO_D:
            if (layer_state_is(_WINDOWS) || layer_state_is(_MAC)) {
                return true;
            }
        case CO_C:
            if (layer_state_is(_WINDOWS) || layer_state_is(_MAC)) {
                return true;
            }
        case CO_TB:
            if (layer_state_is(_WINDOWS) || layer_state_is(_MAC)) {
                return true;
            }
        case CO_EC:
            if (layer_state_is(_WINDOWS) || layer_state_is(_MAC)) {
                return true;
            }
        case CO_CP:
            if (layer_state_is(_WINDOWS) || layer_state_is(_MAC)) {
                return true;
            }
        case CO_PL:
            if (layer_state_is(_NAV)) {
                return true;
            }
        case CO_AS:
            if (layer_state_is(_NAV)) {
                return true;
            }
        case CO_HS:
            if (layer_state_is(_NAV) || layer_state_is(_W_NUM) || layer_state_is(_M_NUM)) {
                return true;
            }
        case CO_3:
            if (layer_state_is(_W_NUM) || layer_state_is(_M_NUM)) {
                return true;
            }
    }

    return false;
};

void process_combo_event(uint16_t combo_index, bool pressed) {
    led_t led_usb_state = host_keyboard_led_state();
    uint8_t state = get_highest_layer(layer_state | default_layer_state);
    switch(combo_index) {
        case NOLOCK:
            if (pressed) {
                if (led_usb_state.caps_lock ) {
                    SEND_STRING(" with(nolock)");
                }
                else {
                    SEND_STRING(" WITH(NOLOCK)");
                }
            }
            break;

        case CO_LAYER:
            if (pressed){
                if (state == _MAC) {
                    set_single_persistent_default_layer(_WINDOWS);
                }
                else if (state == _WINDOWS) {
                    set_single_persistent_default_layer(_MAC);
                }
            }
            break;

        case CO_LANG:
            if (pressed){
                if (state == _MAC) {
                    tap_code16(LCTL(KC_SPC));
                }
                else if (state == _WINDOWS) {
                    tap_code16(KC_RALT);
                }
            }
            break;
    }
};

void keyboard_post_init_user(void) {
    // Initialize RGB to static black
    //rgblight_enable_noeeprom();
    //rgblight_sethsv_noeeprom(HSV_BLACK);
    //rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);

    // Set default layer based on the detected OS after a 500 ms delay.
    uint32_t get_host_os(uint32_t trigger_time, void* cb_arg) {
        switch (detected_host_os()) {
        case OS_UNSURE:  // Don't change default layer if unsure.
            break;
        case OS_MACOS:
            set_single_persistent_default_layer(_MAC);
            break;
        case OS_IOS:
            set_single_persistent_default_layer(_MAC);
            break;
        case OS_LINUX:
            set_single_persistent_default_layer(_WINDOWS);
            break;
        case OS_WINDOWS:
            set_single_persistent_default_layer(_WINDOWS);
            break;
        default:
            break;
        }
        return 0;
  }
  defer_exec(800, get_host_os, NULL);
}

// ┌────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ K E Y M A P S                                                                                                          │
// └────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /*
      ┌─────────────────────────────────────────────────┐
      │ l a y o u t                                     │      ╭╮╭╮╭╮╭╮
      └─────────────────────────────────────────────────┘      │╰╯╰╯╰╯│
                ┌─────────┬─────────┬─────────┬─────────┬──────╨──┐┌──╨──────┬─────────┬─────────┬─────────┬─────────┐
        ╌┄┈┈───═╡    Q    │    W    │    E    │    R    │    T    ││    Y    │    U    │    I    │    O    │    P    │
                ├─────────┼─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┼─────────┤
                │    A    │    S    │    D    │    F    │    G    ││    H    │    J    │    K    │    L    │    ;    │
      ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐
      │    Q    │    Z    │    X    │    C    │    V    │    B    ││    N    │    M    │    ,    │    .    │    /    │    P    │
      └─────────┴─────────┴─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┴─────────┴─────────┘
                                    │  CTRL   │  LOWER  │  SPACE  ││  ENTER  │  RAISE  │  BSPC   │
                                    └─────────┴─────────┴─────────┘└─────────┴─────────┴─────────┘*/
    [_WINDOWS] = LAYOUT(
                 WFNC_Q,  KC_W, KC_E,    KC_R,    KC_T,                          KC_Y,      KC_U,    KC_I,    KC_O,   WFNC_P,
                 MOU_A,   KC_S, KC_D,    LSFT_F,  KC_G,                          KC_H,      RSFT_J,  KC_K,    KC_L,   NAV_QUO,
        KC_LSFT, HO_LSFT, KC_X, KC_C,    KC_V,    KC_B,                          KC_N,      KC_M,    KC_COMM, KC_DOT, HO_RSFT, XXXXXXX,
                                         KC_LALT, KC_LCTL, WNUM_SP,     WNUM_SP, TD(TD_SP), KC_LGUI
    ),

    [_MAC] = LAYOUT(
                 MFNC_Q,  KC_W, KC_E,    KC_R,    KC_T,                          KC_Y,      KC_U,    KC_I,    KC_O,   MFNC_P,
                 MOU_A,   KC_S, KC_D,    LSFT_F,  KC_G,                          KC_H,      RSFT_J,  KC_K,    KC_L,   NAV_QUO,
        KC_LSFT, HO_LSFT, KC_X, KC_C,    KC_V,    KC_B,                          KC_N,      KC_M,    KC_COMM, KC_DOT, HO_RSFT, KC_RSFT,
                                         KC_LALT, KC_LGUI, WNUM_SP,     WNUM_SP, TD(TD_SP), KC_LCTL
    ),

    [_NAV] = LAYOUT(
                 CC_EXLM, CC_AT,   CC_HASH, KC_EQL,  TD(TD_LBK),                       TD(TD_RBK), XXXXXXX, KC_UP,   XXXXXXX, XXXXXXX,
                 CC_PERC, CC_AMPR, CC_ASTR, KC_SLSH, TD(TD_LPR),                       TD(TD_RPR), KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX,
        KC_LSFT, CC_HASH, CC_DLR,  CC_PLUS, KC_MINS, CC_PIPE,                          KC_BSLS,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                            _______, _______,    _______,     _______, _______, _______
    ),

    [_MOUSE] = LAYOUT(
                 XXXXXXX, XXXXXXX, MS_WHLU, XXXXXXX, KC_PGUP,                       KC_HOME, XXXXXXX, MS_UP,   XXXXXXX, XXXXXXX,
                 XXXXXXX, MS_WHLL, MS_WHLD, MS_WHLR, KC_PGDN,                       KC_END,  MS_LEFT, MS_DOWN, MS_RGHT, XXXXXXX,
        KC_LSFT, XXXXXXX, XXXXXXX, MAKE_H,  XXXXXXX, QK_RBT,                        KC_BSLS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                            KC_LEFT, KC_RGHT, _______,     _______, _______, _______
    ),

    [_M_FNC] = LAYOUT(
                 XXXXXXX, KC_VOLU, XXXXXXX, LGUI(KC_LBRC), LGUI(KC_RBRC),                            LCTL(KC_UP),  KC_F9, KC_F10, KC_F11, KC_F12,
                 XXXXXXX, KC_VOLD, XXXXXXX, XXXXXXX,       LGUI(KC_GRV),                             LGUI(KC_GRV), KC_F5, KC_F6,  KC_F7,  KC_F8,
        KC_LSFT, XXXXXXX, KC_MUTE, XXXXXXX, XXXXXXX,       LGUI(LALT(KC_ESC)),                       MSNAP,        KC_F1, KC_F2,  KC_F3,  KC_F4,  XXXXXXX,
                                            _______,       _______,            _______,     _______, _______,      _______
    ),

    [_W_FNC] = LAYOUT(
                 XXXXXXX, KC_VOLU, XXXXXXX, LALT(KC_LEFT), LALT(KC_RGHT),                            LGUI(KC_TAB), KC_F9, KC_F10, KC_F11, KC_F12,
                 XXXXXXX, KC_VOLD, XXXXXXX, XXXXXXX,       LALT(KC_TAB),                             LALT(KC_TAB), KC_F5, KC_F6,  KC_F7,  KC_F8,
        KC_LSFT, XXXXXXX, KC_MUTE, XXXXXXX, XXXXXXX,       LCTL(LSFT(KC_ESC)),                       WSNAP,        KC_F1, KC_F2,  KC_F3,  KC_F4,  XXXXXXX,
                                            _______,       _______,            _______,     _______, _______,      _______
    ),

    [_M_NUM] = LAYOUT(
                 CC_EXLM, CC_AT,   CC_HASH, CC_DLR,  CC_PERC,                       CC_CIRC, CC_AMPR, CC_ASTR, CC_LPRN, CC_RPRN,
                 KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                          KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        KC_LSFT, KC_GRV,  CC_TILD, CC_PLUS, KC_MINS, CC_ASTR,                       KC_BSLS, KC_EQL,  KC_COMM, KC_DOT,  KC_SLSH, XXXXXXX,
                                            _______, _______, _______,     _______, _______, _______
    ),

    [_W_NUM] = LAYOUT(
                 CC_EXLM, CC_AT,   CC_HASH, CC_DLR,  CC_PERC,                       CC_CIRC, CC_AMPR, CC_ASTR, CC_LPRN, CC_RPRN,
                 KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                          KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        KC_LSFT, KC_GRV,  CC_TILD, CC_PLUS, KC_MINS, CC_ASTR,                       KC_BSLS, KC_EQL,  KC_COMM, KC_DOT,  KC_SLSH, XXXXXXX,
                                            _______, _______, _______,     _______, _______, _______
    ),

    /*
    [_QWERTY] = LAYOUT(
                 KC_Q,               KC_W,                KC_E,               KC_R,               KC_T,       KC_Y,    KC_U,               KC_I,               KC_O,               KC_P,
                 MT(MOD_LGUI, KC_A), MT(MOD_LALT, KC_S),  MT(MOD_LCTL, KC_D), MT(MOD_LSFT, KC_F), KC_G,       KC_H,    MT(MOD_RSFT, KC_J), MT(MOD_LCTL, KC_K), MT(MOD_LALT, KC_L), MT(MOD_LGUI, KC_SCLN),
        KC_Q,    KC_Z,               KC_X,                KC_C,               KC_V,               KC_B,       KC_N,    KC_M,               KC_COMM,            KC_DOT,             KC_SLSH,               KC_P,
                                                          KC_DEL,             LT(2, KC_TAB),      KC_SPC,     KC_ENT,  LT(3, KC_ESC),      KC_BSPC
    ),

    */
    /*
      ┌─────────────────────────────────────────────────┐
      │ l o w e r                                       │      ╭╮╭╮╭╮╭╮
      └─────────────────────────────────────────────────┘      │╰╯╰╯╰╯│
                ┌─────────┬─────────┬─────────┬─────────┬──────╨──┐┌──╨──────┬─────────┬─────────┬─────────┬─────────┐
        ╌┄┈┈───═╡ CAPSLCK │ NUMLCK  │    ↑    │    =    │    {    ││    }    │    7    │    8    │    9    │    +    │
                ├─────────┼─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┼─────────┤
                │  HOME   │    ←    │    ↓    │    →    │    [    ││    ]    │    4    │    5    │    6    │    -    │
      ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐
      │ SCRNSHT │   END   │   PG↑   │  SAVE   │   PG↓   │    (    ││    )    │    1    │    2    │    3    │    *    │    ▼    │
      └─────────┴─────────┴─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┴─────────┴─────────┘
                                    │    ▼    │    ▼    │    ▼    ││    ▼    │ ADJUST  │    0    │
                                    └─────────┴─────────┴─────────┘└─────────┴─────────┴─────────┘ */
    /*
    [_LOWER] = LAYOUT(
                 KC_CAPS, KC_NUM,  KC_UP,   KC_EQL,  KC_LCBR,    KC_RCBR, KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
                 KC_QUOT, KC_LEFT, KC_DOWN, KC_RGHT, KC_LBRC,    KC_RBRC, KC_P4,   KC_P5,   KC_P6,   KC_MINS,
        SNAP,    KC_END,  KC_PGUP, C(KC_S), KC_PGDN, KC_LPRN,    KC_RPRN, KC_P1,   KC_P2,   KC_P3,   KC_PAST, _______,
                                   _______, _______, _______,    _______, MO(4),   KC_P0
    ),
    */
    /*
      ┌─────────────────────────────────────────────────┐
      │ r a i s e                                       │      ╭╮╭╮╭╮╭╮
      └─────────────────────────────────────────────────┘      │╰╯╰╯╰╯│
                ┌─────────┬─────────┬─────────┬─────────┬──────╨──┐┌──╨──────┬─────────┬─────────┬─────────┬─────────┐
        ╌┄┈┈───═╡    !    │    @    │    #    │    $    │    %    ││    ^    │    &    │    Ü    │    °    │    /    │
                ├─────────┼─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┼─────────┤
                │    Ä    │    è    │    SZ   │    é    │         ││         │    ¥    │    €    │    £    │    Ö    │
      ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐
      │         │    `    │    ~    │   CUE   │         │         ││         │         │         │ DM REC1 │ DM STOP │ DM PLY1 │
      └─────────┴─────────┴─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┴─────────┴─────────┘
                                    │  GIPHY  │ ADJUST  │    ▼    ││    ▼    │    ▼    │    ▼    │
                                    └─────────┴─────────┴─────────┘└─────────┴─────────┴─────────┘ */
    /*
    [_RAISE] = LAYOUT(
        //╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷
                 KC_EXLM,      KC_AT,      KC_HASH,    KC_DLR,     KC_PERC,    KC_CIRC, KC_AMPR,          RALT(KC_U), RALT(KC_3), KC_BSLS,
                 RALT(KC_A),   RALT(KC_F), RALT(KC_S), RALT(KC_G), XXXXXXX,    XXXXXXX, LSFT(RALT(KC_4)), RALT(KC_5), RALT(KC_4), RALT(KC_O),
        XXXXXXX, LSFT(KC_GRV), KC_TILD,    RALT(KC_C), XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX,          XXXXXXX,    DM_REC1,    DM_RSTP,    DM_PLY1,
                                           _______,    MO(4),      _______,    _______, _______,          _______
    ),
    */
    /*
      ╺━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╸

      ┌─────────────────────────────────────────────────┐
      │ a d j u s t                                     │      ╭╮╭╮╭╮╭╮
      └─────────────────────────────────────────────────┘      │╰╯╰╯╰╯│
                ┌─────────┬─────────┬─────────┬─────────┬──────╨──┐┌──╨──────┬─────────┬─────────┬─────────┬─────────┐
        ╌┄┈┈───═╡  RESET  │         │         │         │         ││         │   F7    │   F8    │   F9    │   F12   │
                ├─────────┼─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┼─────────┤
                │ DEBUG   │ QWERTY  │         │         │         ││         │   F4    │   F5    │   F6    │   F11   │
      ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐
      │  MAKE   │ OS SWAP │ COLEMAK │         │         │         ││         │   F1    │   F2    │   F3    │   F10   │   F13   │
      └─────────┴─────────┴─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┴─────────┴─────────┘
                                    │    ▼    │    ▼    │    ▼    ││    ▼    │    ▼    │    ▼    │
                                    └─────────┴─────────┴─────────┘└─────────┴─────────┴─────────┘ */
    /*
    [_ADJUST] = LAYOUT(
        //╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷
                 QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, KC_F7,   KC_F8,   KC_F9,   KC_F12,
                 DB_TOGG, QWERTY,  XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, KC_F4,   KC_F5,   KC_F6,   KC_F11,
        MAKE_H,  CG_TOGG, COLEMAK, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F10,  KC_F13,
                                   _______, _______, _______,    _______, _______, _______
    )
    */
};

// ┌────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ M A C R O S                                                                                                            │
// └────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
// ▝▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▘
/*
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CG_TOGG:
            if (record->event.pressed) {
                if (!keymap_config.swap_lctl_lgui) {
                    keymap_config.swap_lctl_lgui = true; // ─── MAC
                } else {
                    keymap_config.swap_lctl_lgui = false; // ─── WIN
                }
                eeconfig_update_keymap(keymap_config.raw);
                clear_keyboard(); // ──── clear to prevent stuck keys
                return false;
            }

            // ┌─────────────────────────────────────────────────┐
            // │ l a y e r                                       │
            // └─────────────────────────────────────────────────┘

        case COLEMAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_COLEMAK);
            }
            return false;
        case QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;

            // ┌─────────────────────────────────────────────────┐
            // │ q m k                                           │
            // └─────────────────────────────────────────────────┘

        case MAKE_H:
            if (record->event.pressed) {
                SEND_STRING("qmk compile -kb geigeigeist/totem -km default");
                tap_code(KC_ENTER);
            }
            break;

            // ┌─────────────────────────────────────────────────┐
            // │ p r o d u c t i v i t y                         │
            // └─────────────────────────────────────────────────┘

        case SNAP:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    SEND_STRING(SS_LSFT(SS_LCMD(SS_LCTL("4")))); // MAC
                } else {
                    SEND_STRING(SS_LSFT(SS_LWIN("S"))); // WIN
                }
            }
            break;
    }
    return true;
}*/
/*
  ╺━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╸


                                                          ██████
                                                            ██  ▄▄▄▄
                                                            ██ ██▀▀██
                                                            ▀▀ ██▄▄██
                                                        ██████  ▀▀▀▀
                                                          ██ ▄▄▄▄▄▄
                                                          ██ ██▀▀▀▀
                                                          ██ ██████
                                                             ██▄▄▄▄
                                                             ▀▀▀▀▀▀
                                                           ████████
                                                           ██ ██ ██
                                                           ██ ██ ██
                                                           ▀▀ ▀▀ ▀▀
                                                          ████████

*/

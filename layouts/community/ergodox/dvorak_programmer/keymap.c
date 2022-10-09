
#include QMK_KEYBOARD_H
#include "led.h"
#include "debug.h"
#include "action_layer.h"
#include "action_code.h"

#define BASE    0 // default layer
#define SHELL_NAV 2
#define KEY_NAV 3 // key navigation layer
#define KEY_SEL 4 // key selection layer
#define NUMBER  5  // number layer
#define SYMBOL  6
#define BRACKETS  7
#define SHORTCUTS 8
#define MOUSE 9

// macros
#define MC_COPY_LINE  0
#define MC_CUT_LINE   1
#define MC_PASTE_LINE 2
#define MC_NEW_SEARCH_TAB 3
#define SCREEN_TAB_LEFT 4
#define SCREEN_TAB_RIGHT 5
#define SCREEN_NEW_TAB 6
#define SWITCH_NDS 7
#define SCREEN_COPY_MODE 8
#define SCREEN_PASTE 9
#define OPEN_CLOSE_PAREN 10
#define OPEN_CLOSE_BRACKET 11
#define OPEN_CLOSE_CURLY 12
#define OPEN_CLOSE_SINGLE_QUOTE 13
#define OPEN_CLOSE_DOUBLE_QUOTE 14
#define SHELL_RECALL_LAST_ARG_REMOVE_FIRST_COMMAND 15
#define SEMICOLON_NEWLINE 16
#define END_NEWLINE 17



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// base layer
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_ESC,                    KC_F1,          KC_F2,       KC_F3,        KC_F4,       KC_F5,       KC_F6,
        KC_TAB,                    KC_QUOT,        KC_COMM,     KC_DOT,       KC_P,        KC_Y,        MO(KEY_SEL),
        MO(BRACKETS),              KC_A,           KC_O,        KC_E,         KC_U,        KC_I,
        MO(SHELL_NAV),             KC_SCLN,        KC_Q,        KC_J,         KC_K,        KC_X,        MO(KEY_NAV),
                   OSL(SHORTCUTS),OSM(MOD_LCTL), OSM(MOD_LALT),OSL(SYMBOL),MO(NUMBER),
                                              // thumb cluster
                                               OSM(MOD_LSFT), RCTL(KC_S),
                                                          RCTL(KC_DEL),
                                               KC_BSPC,RCTL(KC_BSPC),KC_DEL,
        // right hand
             KC_F7,       KC_F8,       KC_F9,       KC_F10,        KC_F11,       KC_F12,       KC_BSLS,
             KC_PGUP,     KC_F,        KC_G,        KC_C,          KC_R,         KC_L,         KC_SLSH,
                          KC_D,        KC_H,        KC_T,          KC_N,         KC_S,         KC_MINS,
             KC_PGDN,     KC_B,        KC_M,        KC_W,          KC_V,         KC_Z,         OSM(MOD_LSFT),
                                  // lower keys - browser tab control
                                  RSFT(RCTL(KC_TAB)), RCTL(KC_TAB), RCTL(KC_T), LALT(KC_LEFT), RCTL(KC_W),
             // thumb cluster
             KC_HOME,KC_END,
             KC_UP,
             KC_DOWN,KC_ENT, KC_SPC
    ),




// shell navigation layer
[SHELL_NAV] = LAYOUT_ergodox(
       // left hand
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
               // bottom row
               KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                       // thumb cluster
                                       KC_TRNS,KC_TRNS,
                                               LALT(KC_D),
                               KC_TRNS,RCTL(KC_W),KC_TRNS,
       // right hand
       KC_TRNS,    KC_TRNS,        KC_TRNS,             KC_TRNS,         KC_TRNS,         KC_TRNS,        KC_TRNS,
       RCTL(KC_L), RCTL(KC_W),     KC_HOME,             KC_UP,           KC_END,          LALT(KC_D),     RCTL(KC_R),
                   LALT(KC_B),     KC_LEFT,             KC_DOWN,         KC_RIGHT,        LALT(KC_F),     LALT(KC_DOT),
       RCTL(KC_C), RCTL(KC_U),     M(SCREEN_COPY_MODE), M(SCREEN_PASTE), MEH(KC_V),      RCTL(KC_K),     M(SHELL_RECALL_LAST_ARG_REMOVE_FIRST_COMMAND),
                // bottom row
                 M(SCREEN_TAB_LEFT), M(SCREEN_TAB_RIGHT), M(SCREEN_NEW_TAB),  KC_TRNS,    KC_TRNS,
       // thumb cluster
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),


// key navigation layer
[KEY_NAV] = LAYOUT_ergodox(
       // left hand
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
               // bottom row
               KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                       // thumb cluster
                                       KC_TRNS,KC_TRNS,
                                               KC_TRNS,
                               KC_TRNS,KC_TRNS,KC_TRNS,
       // right hand
       KC_TRNS, KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,        KC_TRNS,
       KC_TRNS, KC_PGDN,        KC_HOME,    KC_UP,      KC_END,     KC_PGUP,        M(MC_COPY_LINE),
                RCTL(KC_LEFT),  KC_LEFT,    KC_DOWN,    KC_RIGHT,   RCTL(KC_RIGHT), M(MC_CUT_LINE),
       KC_TRNS, KC_TRNS,        RCTL(KC_C), RCTL(KC_X), RCTL(KC_V), KC_TRNS,        M(MC_PASTE_LINE),
                // bottom row
                KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,    KC_TRNS,
       // thumb cluster
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),

// key selection layer
[KEY_SEL] = LAYOUT_ergodox(
       // left hand
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
               // bottom row
               KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                       // thumb cluster
                                       KC_TRNS,KC_TRNS,
                                               KC_TRNS,
                               KC_TRNS,KC_TRNS,KC_TRNS,
       // right hand
       KC_TRNS,       KC_TRNS,             KC_TRNS,       KC_TRNS,       KC_TRNS,        KC_TRNS,              KC_TRNS,
       RSFT(KC_PGUP), RSFT(KC_PGDN),       RSFT(KC_HOME), RSFT(KC_UP),   RSFT(KC_END),   RSFT(KC_PGUP),        M(MC_COPY_LINE),
                      RSFT(RCTL(KC_LEFT)), RSFT(KC_LEFT), RSFT(KC_DOWN), RSFT(KC_RIGHT), RSFT(RCTL(KC_RIGHT)), M(MC_CUT_LINE),
       RSFT(KC_PGDN), KC_TRNS,             RCTL(KC_C),    RCTL(KC_X),    RCTL(KC_V),     KC_TRNS,              M(MC_PASTE_LINE),
                // bottom row
                KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,    KC_TRNS,
       // thumb cluster
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),

// number layer
[NUMBER] = LAYOUT_ergodox(
       // left hand
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
               // bottom row
               KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                       // thumb cluster
                                       KC_TRNS,KC_TRNS,
                                               KC_TRNS,
                               KC_TRNS,KC_TRNS,KC_TRNS,
       // right hand
       KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,
       KC_TRNS, KC_PLUS,  KC_7,    KC_8,    KC_9,     KC_ASTR, KC_TRNS,
                KC_MINS,  KC_4,    KC_5,    KC_6,     KC_SLSH, KC_TRNS,
       KC_TRNS, KC_EQUAL, KC_1,    KC_2,    KC_3,     KC_COLN, KC_TRNS,
                               // bottom row
                                KC_0, KC_DOT, KC_COMMA, KC_TRNS,  KC_TRNS,
       // thumb cluster
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),


[SYMBOL] = LAYOUT_ergodox(
       // left hand
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                       KC_TRNS,KC_TRNS,
                                               KC_TRNS,
                               KC_TRNS,KC_TRNS,KC_TRNS,
       // right hand
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_PLUS, KC_AMPR, KC_ASTR, KC_GRAVE,KC_TILD, KC_TRNS,
                KC_MINS, KC_DLR,  KC_PERC, KC_CIRC, KC_PIPE, KC_TRNS,
       KC_TRNS, KC_EQUAL,KC_EXLM, KC_AT,   KC_HASH, KC_TRNS, KC_TRNS,
                         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       M(SEMICOLON_NEWLINE), M(END_NEWLINE),
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),

[BRACKETS] = LAYOUT_ergodox(
       // left hand
       KC_TRNS,KC_TRNS,KC_TRNS,             KC_TRNS,            KC_TRNS,               KC_TRNS,KC_TRNS,
       KC_TRNS,KC_TRNS,M(OPEN_CLOSE_CURLY), M(OPEN_CLOSE_PAREN),M(OPEN_CLOSE_BRACKET), KC_TRNS,KC_TRNS,
       KC_TRNS,KC_LPRN, KC_RPRN,            KC_LBRC,            KC_RBRC,               KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,             KC_LCBR,            KC_RCBR,               KC_TRNS,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,             KC_TRNS,            KC_TRNS,
                                        KC_TRNS,KC_TRNS,
                                               KC_TRNS,
                               KC_TRNS,KC_TRNS,KC_TRNS,
       // right hand
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
       KC_TRNS, KC_TRNS, M(OPEN_CLOSE_BRACKET),M(OPEN_CLOSE_PAREN),M(OPEN_CLOSE_CURLY),KC_TRNS,KC_TRNS,
                KC_TRNS, KC_LBRC, KC_RBRC, KC_LPRN, KC_RPRN, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_LCBR, KC_RCBR, KC_TRNS, KC_TRNS, KC_TRNS,
                         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),

[SHORTCUTS] = LAYOUT_ergodox(
       // left hand
       KC_NO,  MEH(KC_F1), MEH(KC_F2), MEH(KC_F3),  MEH(KC_F4), MEH(KC_F5), MEH(KC_F6),
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                         MEH(KC_0),MEH(KC_1),
                                                   MEH(KC_2),
                               MEH(KC_3),MEH(KC_4),MEH(KC_5),
       // right hand
       MEH(KC_F7), MEH(KC_F8), MEH(KC_F9), MEH(KC_F10),  MEH(KC_F11), MEH(KC_F12),  M(SWITCH_NDS),
       KC_TRNS, MEH(KC_A), MEH(KC_B),    MEH(KC_C),    MEH(KC_D),    MEH(KC_E), MEH(KC_F),
                MEH(KC_G), MEH(KC_H),    MEH(KC_I),    MEH(KC_J),    MEH(KC_K), MEH(KC_L),
       KC_TRNS, MEH(KC_M), MEH(KC_N),    MEH(KC_O),    MEH(KC_P),    MEH(KC_Q), KC_CAPSLOCK,
                           MEH(KC_S),    MEH(KC_T),    MEH(KC_U),    MEH(KC_V), MEH(KC_X),
       MEH(KC_6), MEH(KC_7),
       MEH(KC_8),
       MEH(KC_9), MEH(KC_Y), MEH(KC_Z)
),


[MOUSE] = LAYOUT_ergodox(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
	   KC_TRNS, KC_BTN1, KC_BTN2
),

};



const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case MC_COPY_LINE:
            if (record->event.pressed) {
                return MACRO( T(HOME), D(LSFT), T(END), U(LSFT), D(LCTL), T(C), U(LCTL), END);
            }
            break;
        case MC_CUT_LINE:
            if (record->event.pressed) {
                return MACRO( T(HOME), D(LSFT), T(END), U(LSFT), D(LCTL), T(X), U(LCTL), END);
            }
            break;
        case MC_PASTE_LINE:
            if (record->event.pressed) {
                return MACRO( T(END), T(ENTER), D(LCTL), T(V), U(LCTL), END);
            }
            break;
        case MC_NEW_SEARCH_TAB:
             if (record->event.pressed) {
                return MACRO( D(LCTL), T(T), T(K), U(LCTL), END);
            }
            break;
        case SCREEN_TAB_LEFT:
             if (record->event.pressed) {
                return MACRO( D(LCTL), T(A), U(LCTL), T(P), END);
            }
            break;
        case SCREEN_TAB_RIGHT:
             if (record->event.pressed) {
                return MACRO( D(LCTL), T(A), U(LCTL), T(N), END);
            }
            break;
        case SCREEN_NEW_TAB:
             if (record->event.pressed) {
                return MACRO( D(LCTL), T(A), U(LCTL), T(C), END);
            }
        break;
        case SCREEN_COPY_MODE:
            if (record->event.pressed) {
                return MACRO( D(LCTL), T(A), U(LCTL), T(ESC), END);
            }
        break;
        case SCREEN_PASTE:
            if (record->event.pressed) {
                return MACRO( D(LCTL), T(A), U(LCTL), T(RBRC), END);
            }
        break;
        case SWITCH_NDS:
             if (record->event.pressed) {
                return MACRO( D(LSFT), T(F11), U(LSFT), W(255), D(LALT), T(TAB), U(LALT), END);
            }
        break;
        case OPEN_CLOSE_PAREN:
            if (record->event.pressed) {
                return MACRO( D(LSFT), T(9), T(0), U(LSFT), T(LEFT), END);
            }
        break;
        case OPEN_CLOSE_BRACKET:
            if (record->event.pressed) {
                return MACRO( T(LBRC), T(RBRC), T(LEFT), END);
            }
        break;
        case OPEN_CLOSE_CURLY:
            if (record->event.pressed) {
                return MACRO( D(LSFT), T(LBRC), T(RBRC), U(LSFT), T(LEFT), END);
            }
        break;
        case OPEN_CLOSE_SINGLE_QUOTE:
            if (record->event.pressed) {
                return MACRO( T(QUOT), T(QUOT), T(LEFT), END);
            }
        break;
        case OPEN_CLOSE_DOUBLE_QUOTE:
            if (record->event.pressed) {
                return MACRO( D(LSFT), T(QUOT), T(QUOT), U(LSFT), T(LEFT), END);
            }
        break;
        case SHELL_RECALL_LAST_ARG_REMOVE_FIRST_COMMAND:
            if (record->event.pressed) {
                return MACRO( T(UP), T(HOME), D(LALT), T(D), U(LALT), END);
            }
        break;
		case SEMICOLON_NEWLINE:
            if (record->event.pressed) {
                return MACRO( T(END), T(SCLN), T(ENTER), END);
            }
		break;
		case END_NEWLINE:
            if (record->event.pressed) {
                return MACRO( T(END), T(ENTER), END);
            }
		break;


      }
    return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

    return;
};

void led_set_user(uint8_t usb_led) {
    if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
        ergodox_right_led_1_on();
    } else {
        ergodox_right_led_1_off();
    }
}


// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = get_highest_layer(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
        case NUMBER:
        case SYMBOL:
		case BRACKETS:
		//case SHELL_LAYER:
            ergodox_right_led_2_on();
            break;
        case KEY_NAV:
        case KEY_SEL:
            ergodox_right_led_3_on();
            break;
        case SHORTCUTS:
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
            break;
        default:
            // none
            break;
    }
    return;
};

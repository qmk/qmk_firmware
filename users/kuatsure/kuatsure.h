#ifndef KUATSURE
#define KUATSURE

#include "quantum.h"

void tmux_prefix(void);
void tmux_pane_zoom(void);
void tmux_pane_switch(uint16_t keycode);
void tmux_window_switch(uint16_t keycode);

#define KT_CESC CTL_T(KC_ESC)

#undef LEADER_TIMEOUT
#define LEADER_TIMEOUT 300

#define LAYOUT_preonic_grid_wrapper(...)   LAYOUT_preonic_grid(__VA_ARGS__)

#define _________________NUMBER_L1_________________        KC_1,    KC_2,    KC_3,    KC_4,    KC_5
#define _________________NUMBER_R1_________________        KC_6,    KC_7,    KC_8,    KC_9,    KC_0

#define _________________QWERTY_L1_________________        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T
#define _________________QWERTY_L2_________________        KC_A,    KC_S,    KC_D,    KC_F,    KC_G
#define _________________QWERTY_L3_________________        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define _________________QWERTY_R1_________________        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P
#define _________________QWERTY_R2_________________        KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN
#define _________________QWERTY_R3_________________        KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLASH

#define ____________FUNCTION_1____________                 KC_F1,   KC_F2,   KC_F3,   KC_F4
#define ____________FUNCTION_2____________                 KC_F5,   KC_F6,   KC_F7,   KC_F8
#define ____________FUNCTION_3____________                 KC_F9,   KC_F10,  KC_F11,  KC_F12

#endif

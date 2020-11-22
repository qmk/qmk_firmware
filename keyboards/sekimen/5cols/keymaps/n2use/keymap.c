/* Copyright 2020 n2
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "keymap_jp.h"
#include <stdio.h>
#include "keycode.h"

// Script for the trackball and mousekey start.
#ifdef POINTING_DEVICE_ENABLE
#include "paw3204.h"
#include "pointing_device.h"
report_mouse_t mouse_rep;
#ifdef MOUSEKEY_ENABLE
#include "mousekey.h"
report_mouse_t mouse_rep_temp;
static int  mouse_wheel_count = 0;
static bool mouse_wheel_flag = 0;
static int w_offset = 1;
static int mouse_wheel_interval = 10;
#endif
#endif
// Script for the trackball and mousekey end.

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _DEFAULT = 0,
    _RAISE,
    _LOWER
/*    _FN */
};

//Script for the tap dance start.
typedef struct {
    bool is_press_action;
    uint8_t state;
} tap;

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    DOUBLE_SINGLE_TAP, // Send two single taps
    TRIPLE_TAP,
    TRIPLE_HOLD
};

// Tap dance enums
enum {
    SPC_BSC,
    P_AT,
    SCLN_COLN,
    SLSH_BSLS, 
    LBRC_RBRC,
    ZKHK_ESC,
    Z_LSFT,
    ENT_RSFT,
    MCY,
    NUM345,
    NUM678,
    SOME_OTHER_DANCE
};

uint8_t cur_dance(qk_tap_dance_state_t *state);

void MCY_finished(qk_tap_dance_state_t *state, void *user_data); //MINS,CIRC,YEN
void MCY_reset(qk_tap_dance_state_t *state, void *user_data);
void num345_finished(qk_tap_dance_state_t *state, void *user_data);
void num345_reset(qk_tap_dance_state_t *state, void *user_data);
void num678_finished(qk_tap_dance_state_t *state, void *user_data);
void num678_reset(qk_tap_dance_state_t *state, void *user_data);
void ENT_RSFT_finished(qk_tap_dance_state_t *state, void *user_data);
void ENT_RSFT_reset(qk_tap_dance_state_t *state, void *user_data);
// Script for the tap dance end.

#ifdef OLED_DRIVER_ENABLE

// Script for detect shift and ctrl start.
char detector_result[24];
void shift_ctrl_detector(uint16_t keycode, bool keypless_flag);
// Script for detect shift and ctrl end.

// Script for memorandum start.
char for_memorandum[24];
// Script for memorandum end.

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
    }
    return rotation;
}

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };
    oled_write_P(qmk_logo, false);
}

void oled_task_user(void) {
  if (!is_keyboard_master()) {
      render_logo();
  } else {
  // Host Keyboard Layer Status
  oled_write_P(PSTR("Layer: "), false);
  switch (biton32(layer_state)) {
    case _DEFAULT:
      oled_write_P(PSTR("DEFAULT\n"), false);
      break;
    case _RAISE:
      oled_write_P(PSTR("RAISE\n"), false);
      break;
    case _LOWER:
      oled_write_P(PSTR("LOWER\n"), false);
      break;
    default:
      // Or use the write_ln shortcut over adding '\n' to the end of your string
      oled_write_ln_P(PSTR("Undefined"), false);
  };
  // Host Keyboard LED Status
  uint8_t led_usb_state = host_keyboard_leds();
  oled_write_P(led_usb_state & (1<<USB_LED_NUM_LOCK) ? PSTR("NUMLCK ") : PSTR("       "), false);
  oled_write_P(led_usb_state & (1<<USB_LED_CAPS_LOCK) ? PSTR("CAPLCK ") : PSTR("       "), false);
  oled_write_P(led_usb_state & (1<<USB_LED_SCROLL_LOCK) ? PSTR("SCRLCK\n") : PSTR("      \n"), false);

// Script for detect shift and ctrl start.
  oled_write_ln(detector_result, false);
// Script for detect shift and ctrl end.

// Script for the memorandum start.
   if((biton32(layer_state) == _RAISE)){
       oled_write_ln(for_memorandum, false);
   } else {
       oled_write_P(PSTR("                    "), false);
   }
// Script for the memorandum end.
   }
}
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
   /* DEFAULT
    * ,-----------------------------.                                   .--------------------------.
    * |ZEN/HAN,ESC|  TAB   |  DEL   |                                   |  [,]   | -,^,\  | BSPC   |
    * |-----------+--------+--------+-----------------------------------+--------+--------+--------|
    * |    q      |   w    |   e    |   r    |   t    |   y    |   u    |   i    |   o    |  p,@   |
    * |-----------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    * |    a      |   s    |   d    |   f    |   g    |   h    |   j    |   k    |   l    |  ;,:   |
    * |-----------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    * | z,SHIFT   |   x    |   c    |   v    |   b    |   n    |   m    |   ,    |   .    |  /,\   |
    * |-----------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    * |   CTRL    |  ALT   |  WIN   | MUHEN  | SPACE  | RAISE  | LOWER  |  CTRL  | SHIFT  |ENT,SFT |
    * `--------------------------------------------------------------------------------------------'
    */
    [_DEFAULT] = LAYOUT(
      TD(ZKHK_ESC), KC_TAB,  KC_DEL,                                           TD(LBRC_RBRC), TD(MCY), KC_BSPC,
      KC_Q,         KC_W,    KC_E,    KC_R,    KC_T,   KC_Y,       KC_U,       KC_I,          KC_O,    TD(P_AT),
      KC_A,         KC_S,    KC_D,    KC_F,    KC_G,   KC_H,       KC_J,       KC_K,          KC_L,    TD(SCLN_COLN),
      TD(Z_LSFT),   KC_X,    KC_C,    KC_V,    KC_B,   KC_N,       KC_M,       KC_COMM,       KC_DOT,  TD(SLSH_BSLS),
      KC_LSFT,      KC_LALT, KC_LGUI, KC_MHEN, KC_SPC, MO(_RAISE), MO(_LOWER), KC_RCTL,       KC_RSFT, TD(ENT_RSFT)
    ),
   /* RAISE
    * ,--------------------------.                                   .--------------------------.
    * |        |        |        |                                   |        |        |  DEL   |
    * |--------+--------+--------+-----------------------------------+--------+--------+--------|
    * |   1    |   2    |   3    |   4    |   5    |   6    |   7    |   8    |   9    |   0    |
    * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    * |        |        |        |        |        |        |        |        |        |        |
    * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    * |        |        |        |        |        |        |        |        |        |        |
    * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    * |        |        |        |        |        |        |        |        |        |        |
    * `-----------------------------------------------------------------------------------------'
    */
    [_RAISE] = LAYOUT(
      _______, _______, _______,                                     _______, _______, KC_DEL,
      KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
   /* LOWER
    * ,--------------------------.                                   .--------------------------.
    * |        |        |        |                                   |   -    |   ^    |   \    |
    * |--------+--------+--------+-----------------------------------+--------+--------+--------|
    * |        |  UP    |        |        |        |        |        |        |   @    |   [    |
    * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    * | LEFT   | DOWN   | RIGHT  |        |        |        |        |        |   :    |   ]    |
    * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    * |        |        |        |        |        |        |        |        |        |   \    |
    * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    * |RGB_TOG |RGB_VAI |RGB_HUI |RGB_SAI |        |        |        |        |        |        |
    * `-----------------------------------------------------------------------------------------'
    */
    [_LOWER] = LAYOUT(
      _______, _______, _______,                                     JP_MINS, JP_CIRC, JP_YEN,
      _______, KC_UP,   _______, _______, _______, _______, _______, _______, JP_AT,   JP_LBRC,
      KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, _______, JP_COLN, JP_RBRC,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, JP_BSLS,
      RGB_TOG, RGB_VAI, RGB_HUI, RGB_SAI, _______, _______, _______, _______, _______, _______
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
// Script for the mousekey start.
#ifdef POINTING_DEVICE_ENABLE
#ifdef MOUSEKEY_ENABLE
    switch (keycode) {
        case KC_MS_BTN1:                            // Override the behavior of mouse key.
            if (record->event.pressed) {
                mouse_rep.buttons |= MOUSE_BTN1;
            } else {
                mouse_rep.buttons &= ~MOUSE_BTN1;
            }
            pointing_device_set_report(mouse_rep);
            return false;
            break;
        case KC_MS_BTN2:
            if (record->event.pressed) {
                mouse_rep.buttons |= MOUSE_BTN2;
            } else {
                mouse_rep.buttons &= ~MOUSE_BTN2;
            }
            pointing_device_set_report(mouse_rep);
            return false;
            break;
        case KC_MS_BTN3:
            if (record->event.pressed) {
                mouse_rep.buttons |= MOUSE_BTN3;
            } else {
                mouse_rep.buttons &= ~MOUSE_BTN3;
            }
            pointing_device_set_report(mouse_rep);
            return false;
            break;
        case KC_MS_BTN4:
            if (record->event.pressed) {
                mouse_rep.buttons |= MOUSE_BTN4;
            } else {
                mouse_rep.buttons &= ~MOUSE_BTN4;
            }
            pointing_device_set_report(mouse_rep);
            return false;
            break;
        case KC_MS_BTN5:
            if (record->event.pressed) {
                mouse_rep.buttons |= MOUSE_BTN5;
            } else {
                mouse_rep.buttons &= ~MOUSE_BTN5;
            }
            pointing_device_set_report(mouse_rep);
            return false;
            break;
        case KC_MS_WH_UP:
            if (record->event.pressed) {
                mouse_rep_temp.v = w_offset;
                mouse_wheel_flag = 1;
            } else if(mouse_rep_temp.v > 0){
                mouse_rep_temp.v = 0;
                mouse_wheel_flag = 0;
            }
            return false;
            break;
        case KC_MS_WH_DOWN:
            if (record->event.pressed) {
                mouse_rep_temp.v = w_offset * -1;
                mouse_wheel_flag = 1;
            } else if(mouse_rep_temp.v < 0){
                mouse_rep_temp.v = 0;
                mouse_wheel_flag = 0;
            }
            return false;
            break;
        case KC_MS_WH_LEFT:
            if (record->event.pressed) {
                mouse_rep_temp.h = w_offset * -1;
                mouse_wheel_flag = 1;
            } else if(mouse_rep_temp.h < 0){
                mouse_rep_temp.h = 0;
                mouse_wheel_flag = 0;
            }
            return false;
            break;
        case KC_MS_WH_RIGHT:
            if (record->event.pressed) {
                mouse_rep_temp.h = w_offset;
                mouse_wheel_flag = 1;
            } else if(mouse_rep_temp.h > 0){
                mouse_rep_temp.h = 0;
                mouse_wheel_flag = 0;
            }
            return false;
            break;
        default:
            break;
    }  
#endif
#endif
// Script for the mousekey end.

// Script for detect shift and ctrl start.
    if(record->event.pressed){
        shift_ctrl_detector(keycode, 1);
    } else {
        shift_ctrl_detector(keycode, 0);
    }
// Script for detect shift and ctrl end.

    return true;
}

// Script for the trackball start.
#ifdef POINTING_DEVICE_ENABLE

void matrix_init_user(void) {
    init_paw3204();
}

void matrix_scan_user(void) {
    static int  cnt;
    static bool paw_ready;

// Script for the mousekey start.
#ifdef MOUSEKEY_ENABLE
    if (mouse_wheel_flag == 1) {
        mouse_wheel_count++;
        if(mouse_wheel_count == mouse_wheel_interval){
            mouse_rep.v = mouse_rep_temp.v;
            mouse_rep.h	= mouse_rep_temp.h;
            pointing_device_set_report(mouse_rep);
            mouse_rep.v = 0;
            mouse_rep.h	= 0;	
            mouse_wheel_count = 0;
        }
    }
#endif
// Script for the mousekey end.

    if (cnt++ % 50 == 0) {
        uint8_t pid = read_pid_paw3204();
        if (pid == 0x30) {
            dprint("paw3204 OK\n");
            paw_ready = true;
        } else {
            dprintf("paw3204 NG:%d\n", pid);
            paw_ready = false;
        }
    }

    if (paw_ready) {
        uint8_t stat;
        int8_t x, y;

        read_paw3204(&stat, &x, &y);
        mouse_rep.x       = y;
        mouse_rep.y       = -x;

        if (cnt % 10 == 0) {
            dprintf("stat:%3d x:%4d y:%4d\n", stat, mouse_rep.x, mouse_rep.y);
        }
        if (stat & 0x80) {
                pointing_device_set_report(mouse_rep);
        }
    }
}
#endif
// Script for the trackball end.

// Script for detect shift and ctrl start.
void shift_ctrl_detector(uint16_t keycode, bool keypress_flag) {

    static int lshift_count = 0;
    static int lctrl_count  = 0;
    static int rshift_count = 0;
    static int rctrl_count  = 0;

    if (keypress_flag == 1){              // key is pressed
        if (keycode == KC_LSHIFT){
            lshift_count++;
        } else if (keycode == KC_RSHIFT){
            rshift_count++;
        } else if (keycode == KC_LCTRL){
            lctrl_count++;
        } else if (keycode == KC_RCTRL){
            rctrl_count++;
        }
    } else {                              // key is released
        if (keycode == KC_LSHIFT){
            lshift_count--;
        } else if  (keycode == KC_RSHIFT){
            rshift_count--;
        } else if (keycode == KC_LCTRL){
            lctrl_count--;
        } else if (keycode == KC_RCTRL){
            rctrl_count--;
        }
    }

    /*setting for oled*/
    if (lshift_count > 0 || rshift_count > 0){
        if (lctrl_count > 0 || rctrl_count > 0){
            snprintf(detector_result, sizeof(detector_result), "Pressing: CTRL&SHIFT");
        } else { 
            snprintf(detector_result, sizeof(detector_result), "Pressing: SHIFT");
        }
    } else if (lctrl_count > 0 || rctrl_count > 0){
        if (lshift_count > 0 || rshift_count > 0){
            snprintf(detector_result, sizeof(detector_result), "Pressing: CTRL&SHIFT");
        } else {
            snprintf(detector_result, sizeof(detector_result), "Pressing: CTRL");
        }
    } else {
        snprintf(detector_result, sizeof(detector_result), "                    ");
    }

   /*setting for memorandum*/
    if (lshift_count > 0 || rshift_count > 0){
            snprintf(for_memorandum, sizeof(for_memorandum), "memo:!\"#$%%&'()");
    } else {
            snprintf(for_memorandum, sizeof(for_memorandum), "                    ");
    }
}
// Script for detect shift and ctrl end.

// Script for tap dance start.
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TD(ENT_RSFT):
            return 110;
        case TD(Z_LSFT):
            return 110;
        default:
            return TAPPING_TERM;
    }
}

uint8_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TRIPLE_TAP;
        else return TRIPLE_HOLD;
    } else return 8; // Magic number. At some point this method will expand to work for more presses
}

// Create an instance of 'tap' for the tap dance.
static tap tap_state = {
    .is_press_action = true,
    .state = 0
};

void MCY_finished(qk_tap_dance_state_t *state, void *user_data) {
    tap_state.state = cur_dance(state);
    switch (tap_state.state) {
        case SINGLE_TAP: register_code(JP_MINS); break;
        case DOUBLE_TAP: register_code(JP_CIRC); break;
        case TRIPLE_TAP: register_code(JP_YEN); break;
        case DOUBLE_SINGLE_TAP: tap_code(JP_MINS); register_code(JP_MINS);
    }
}

void MCY_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (tap_state.state) {
        case SINGLE_TAP: unregister_code(JP_MINS); break;
        case DOUBLE_TAP: unregister_code(JP_CIRC); break;
        case TRIPLE_TAP: unregister_code(JP_YEN); break;
        case DOUBLE_SINGLE_TAP: unregister_code(JP_MINS);
    }
    tap_state.state = 0;
}

void num345_finished(qk_tap_dance_state_t *state, void *user_data) {
    tap_state.state = cur_dance(state);
    switch (tap_state.state) {
        case SINGLE_TAP: register_code(KC_3); break;
        case DOUBLE_TAP: register_code(KC_4); break;
        case TRIPLE_TAP: register_code(KC_5); break;
        case DOUBLE_SINGLE_TAP: tap_code(KC_3); register_code(KC_3);
    }
}

void num345_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (tap_state.state) {
        case SINGLE_TAP: unregister_code(KC_3); break;
        case DOUBLE_TAP: unregister_code(KC_4); break;
        case TRIPLE_TAP: unregister_code(KC_5); break;
        case DOUBLE_SINGLE_TAP: unregister_code(KC_3);
    }
    tap_state.state = 0;
}

void num678_finished(qk_tap_dance_state_t *state, void *user_data) {
    tap_state.state = cur_dance(state);
    switch (tap_state.state) {
        case SINGLE_TAP: register_code(KC_6); break;
        case DOUBLE_TAP: register_code(KC_7); break;
        case TRIPLE_TAP: register_code(KC_8); break;
        case DOUBLE_SINGLE_TAP: tap_code(KC_6); register_code(KC_6);
    }
}

void num678_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (tap_state.state) {
        case SINGLE_TAP: unregister_code(KC_6); break;
        case DOUBLE_TAP: unregister_code(KC_7); break;
        case TRIPLE_TAP: unregister_code(KC_8); break;
        case DOUBLE_SINGLE_TAP: unregister_code(KC_6);
    }
    tap_state.state = 0;
}

void ENT_RSFT_finished(qk_tap_dance_state_t *state, void *user_data) {
    tap_state.state = cur_dance(state);
    switch (tap_state.state) {
        case SINGLE_TAP: register_code(KC_ENT); break;
        case SINGLE_HOLD: register_code(KC_RSFT); shift_ctrl_detector(KC_RSFT,1); break;
        case DOUBLE_SINGLE_TAP: tap_code(KC_ENT); register_code(KC_ENT);
    }
}

void ENT_RSFT_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (tap_state.state) {
        case SINGLE_TAP: unregister_code(KC_ENT); break;
        case SINGLE_HOLD: unregister_code(KC_RSFT); shift_ctrl_detector(KC_RSFT,0); break;
        case DOUBLE_SINGLE_TAP: unregister_code(KC_ENT);
    }
    tap_state.state = 0;
}

void Z_LSFT_finished(qk_tap_dance_state_t *state, void *user_data) {
    tap_state.state = cur_dance(state);
    switch (tap_state.state) {
        case SINGLE_TAP: register_code(KC_Z); break;
        case SINGLE_HOLD: register_code(KC_LSFT); shift_ctrl_detector(KC_LSFT,1); break;
        case DOUBLE_SINGLE_TAP: tap_code(KC_Z); register_code(KC_Z);
    }
}

void Z_LSFT_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (tap_state.state) {
        case SINGLE_TAP: unregister_code(KC_Z); break;
        case SINGLE_HOLD: unregister_code(KC_LSFT); shift_ctrl_detector(KC_LSFT,0); break;
        case DOUBLE_SINGLE_TAP: unregister_code(KC_Z);
    }
    tap_state.state = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [SPC_BSC]   = ACTION_TAP_DANCE_DOUBLE(KC_SPC,KC_BSPACE),
    [P_AT]      = ACTION_TAP_DANCE_DOUBLE(KC_P,JP_AT),
    [SCLN_COLN] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN,JP_COLN),
    [SLSH_BSLS] = ACTION_TAP_DANCE_DOUBLE(KC_SLSH,JP_BSLS),
    [LBRC_RBRC] = ACTION_TAP_DANCE_DOUBLE(JP_LBRC,JP_RBRC),
    [ZKHK_ESC]  = ACTION_TAP_DANCE_DOUBLE(KC_ZKHK,KC_ESC),
    [Z_LSFT]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, Z_LSFT_finished, Z_LSFT_reset),
    [ENT_RSFT]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ENT_RSFT_finished, ENT_RSFT_reset),
    [MCY]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL, MCY_finished, MCY_reset),
    [NUM345]      = ACTION_TAP_DANCE_FN_ADVANCED(NULL, num345_finished, num345_reset),
    [NUM678]      = ACTION_TAP_DANCE_FN_ADVANCED(NULL, num678_finished, num678_reset),
};
// Script for tap dance end.

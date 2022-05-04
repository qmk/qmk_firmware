/* Copyright 2020 sekigon-gonnoc
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

#pragma once

#include "quantum.h"

#define REPORT_PARSER_DEFAULT 1 /* Parse report descriptor based on simple subset */
#define REPORT_PARSER_FIXED   2 /* Small size, only boot keyboard report is acceptable */
#define REPORT_PARSER_USER 3    /* Use user defined parser */
#define REPORT_PARSER_BMP 4     /* Use BMP parser */

typedef enum {
    LEN_L = 0,
    LEN_H,
    MSG_TYP,
    DEV_TYP,
    DEV_NUM,
    EP,
    VID_L,
    VID_H,
    PID_L,
    PID_H,
    REPORT_START,
} packet_index_t;

typedef enum {
    NONE = 0,
    POINTER,
    MOUSE,
    RESERVED,
    JOYSTICK,
    GAMEPAD,
    KEYBOARD,
    KEYPAD,
    MULTI_AXIS,
    SYSTEM,
} dev_type_t;

typedef struct {
    uint16_t len;
    uint8_t  msg_type;
    uint8_t  dev_type;
    uint8_t  dev_num;
    uint8_t  ep_num;
    uint16_t vid;
    uint16_t pid;
    uint8_t  data_start;
} __attribute__((packed)) packet_header_t;

bool report_parser_fixed(uint8_t const* buf, uint8_t msg_len, uint8_t* pre_keyreport, matrix_row_t* current_matrix);
void report_descriptor_parser_user(uint8_t dev_num, uint8_t const * buf, uint16_t len);
bool report_parser_user(uint8_t const * buf, uint16_t len, matrix_row_t * current_matrix);
void on_disconnect_device_user(uint8_t device);

bool process_packet(matrix_row_t current_matrix[]);
int  send_reset_cmd(void);

typedef enum {
    DISABLE_OVERRIDE,
    US_KEY_ON_JP_OS_OVERRIDE,
    JP_KEY_ON_US_OS_OVERRIDE,
} OVERRIDE_MODE;

void set_key_override(OVERRIDE_MODE mode);

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT(\
esc, f1, f2, f3, f4,     f5, f6, f7, f8,     f9, f10, f11, f12,           pscr, scrl, pause, \
hanzen, k1, k2, k3, k4, k5, k6, k7, k8, k9, k0, min, circ, yen, bspc,     ins, home, pageup,       numlock, kp_slsh, kp_astr, kp_min, \
tab,     q,  w,  e,  r,  t,  y,  u,  i,  o,  p,  at, lbrc,     ent,       del, end, pagedown,      kp7, kp8, kp9, kp_plus, \
caps,    a,  s,  d,  f,  g,  h,  j,  k,  l,  scln, cln, rbrc,                                      kp4, kp5, kp6, \
lsft,    z,  x,  c,  v,  b,  n,  m, comm, dot, slsh, bsls, rsft,                up,                kp1, kp2, kp3, kp_ent, \
lctrl, lgui, lalt, mhen, spc, henk, kana, ralt, rgui, app, rctrl,        left, down, right,        kp0,      kp_dot \
) { \
    { KC_NO, KC_NO, KC_NO, KC_NO, a, b, c, d }, \
    { e, f, g, h, i, j, k, l}, \
    { m, n, o, p, q, r, s, t}, \
    { u, v, w, x, y, z, k1, k2}, \
    { k3, k4, k5, k6, k7, k8, k9, k0}, \
    {ent, esc, bspc, tab, spc, min, circ, at}, \
    {lbrc, KC_BSLASH, rbrc, scln, cln, hanzen, comm, dot}, \
    {slsh, caps, f1, f2, f3, f4, f5, f6}, \
    {f7, f8, f9, f10, f11, f12, pscr, scrl}, \
    {pause, ins, home, pageup, del, end, pagedown, right}, \
    {left, down, up, numlock, kp_slsh, kp_astr, kp_min, kp_plus}, \
    {kp_ent, kp1, kp2, kp3, kp4, kp5, kp6, kp7}, \
    {kp8, kp9, kp0, kp_dot, KC_NONUS_BSLASH, app, KC_POWER, KC_KP_EQUAL}, \
    {KC_F13, KC_F14, KC_F15, KC_F16, KC_F17, KC_F18, KC_F19, KC_F20}, \
    {KC_F21, KC_F22, KC_F23, KC_F24, KC_EXECUTE, KC_HELP, KC_MENU, KC_SELECT}, \
    {KC_STOP, KC_AGAIN, KC_UNDO, KC_CUT, KC_COPY, KC_PASTE, KC_FIND, KC__MUTE}, \
    {KC__VOLUP, KC__VOLDOWN, KC_LOCKING_CAPS, KC_LOCKING_NUM, KC_LOCKING_SCROLL, KC_KP_COMMA, KC_KP_EQUAL_AS400, bsls},\
    { kana, yen, henk, mhen, KC_INT6, KC_INT7, KC_INT8, KC_INT9} , \
    { KC_LANG1, KC_LANG2, KC_LANG3, KC_LANG4, KC_LANG5, KC_LANG6, KC_LANG7, KC_LANG8} ,\
    { KC_LANG9, KC_ALT_ERASE, KC_SYSREQ, KC_CANCEL, KC_CLEAR, KC_PRIOR, KC_RETURN, KC_SEPARATOR} , \
    { KC_OUT,  KC_OPER, KC_CLEAR_AGAIN, KC_CRSEL, KC_EXSEL, KC_NO, KC_NO, KC_NO} ,\
    { lctrl, lsft, lalt, lgui, rctrl, rsft, ralt, rgui } \
}

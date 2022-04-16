// Copyright 2022 takashicompany (@takashicompany)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    LAYOUT(
        LT(6, KC_Q), KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, 
        KC_A, KC_S, LT(5, KC_D), KC_F, KC_G, KC_H, KC_J, LT(5, KC_K), KC_L, KC_ENT, 
        LSFT_T(KC_Z), LGUI_T(KC_X), KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, LCTL_T(KC_DOT), KC_BSPC, 
        KC_LCTL, KC_LGUI, LALT_T(KC_LANG2), LSFT_T(KC_TAB), KC_SPC, LT(1, KC_LANG1), KC_PGUP, KC_NO
    ),

    LAYOUT(
        KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, 
        LCTL_T(KC_EQL), KC_LBRC, KC_SLSH, KC_MINS, KC_RO, KC_SCLN, KC_QUOT, KC_RBRC, KC_NUHS, KC_JYEN, 
        KC_LSFT, KC_LGUI, KC_LALT, KC_LANG2, KC_LSFT, KC_SPC, KC_LANG1, KC_TRNS, KC_TRNS, KC_DEL, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),

    LAYOUT(LT(6, KC_Q), KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, 
        KC_A, KC_S, LT(5, KC_D), KC_F, KC_G, KC_H, KC_J, LT(5, KC_K), KC_L, KC_ENT, 
        LSFT_T(KC_Z), LGUI_T(KC_X), KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, LCTL_T(KC_DOT), KC_BSPC, 
        KC_TRNS, KC_TRNS, LALT_T(KC_LANG2), LSFT_T(KC_TAB), KC_SPC, LT(3, KC_LANG1), KC_TRNS, KC_TRNS
    ),

    LAYOUT(
        KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, 
        KC_CIRC, KC_AT, KC_SLSH, KC_MINS, KC_UNDS, KC_SCLN, KC_COLN, KC_LBRC, KC_RBRC, KC_JYEN, 
        MO(4), KC_LGUI, KC_LALT, KC_LANG2, KC_LSFT, KC_SPC, KC_LANG1, KC_TRNS, KC_TRNS, KC_DEL, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),

    LAYOUT(
        KC_EXLM, KC_DQUO, KC_HASH, KC_DLR, KC_PERC, KC_AMPR, KC_QUOT, KC_LPRN, KC_RPRN, KC_0, 
        KC_TILD, KC_GRV, KC_QUES, KC_EQL, KC_UNDS, KC_PLUS, KC_ASTR, KC_LCBR, KC_RCBR, KC_PIPE, 
        KC_LSFT, KC_LGUI, KC_LALT, KC_LANG2, KC_LSFT, KC_SPC, KC_LANG1, KC_TRNS, KC_TRNS, KC_DEL, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),

    LAYOUT(
        KC_ESC, KC_TAB, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_UP, KC_NO, KC_NO, 
        KC_LCTL, KC_TRNS, KC_QUES, KC_EXLM, KC_NO, KC_WH_U, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO, 
        KC_LSFT, KC_LGUI, KC_LALT, KC_LANG2, KC_TRNS, KC_WH_D, KC_LANG1, KC_NO, KC_NO, KC_DEL, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),

    LAYOUT(
        KC_NO, KC_TAB, KC_NO, KC_NO, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, 
        KC_NO, KC_NO, KC_NO, KC_NO, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, 
        KC_LSFT, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, MO(7), MO(8), 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),

    LAYOUT(
        RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, KC_NO, KC_NO, KC_NO, DF(0), DF(2), 
        RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW, RGB_M_SN, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
        RGB_M_K, RGB_M_X, RGB_M_G, KC_NO, KC_NO, RESET, KC_NO, KC_NO, KC_NO, KC_NO, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    )
};

// 自前の絶対数を返す関数
int16_t my_abs(int16_t num) {
    if (num < 0) {
        num = -num;
    }

    return num;
}

int16_t sign(int16_t num) {
    if (num < 0) {
        return -1;
    }

    return 1;
}


void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
//   debug_enable=true;
//   debug_matrix=true;
  //debug_keyboard=true;
  // debug_mouse=true;
}

int16_t mouse_x;
int16_t mouse_y;

int16_t count;

int mag = 30;

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    dprintf("x:%d y:%d \n", mouse_report.x, mouse_report.y);

    int16_t x = mouse_report.x;
    int16_t y = mouse_report.y;

    mouse_report.x = 0;
    mouse_report.y = 0;
    
    int16_t sign_x = sign(x);
    int16_t sign_y = sign(y);

    int16_t abs_x = my_abs(x);
    int16_t abs_y = my_abs(y);

    if (abs_x < abs_y) {
        if (count + abs_x >= mag) {
            abs_x = count - mag;
            
            mouse_x += (count - mag) * sign_x;

            mouse_report.x = mouse_x;
            mouse_report.y = mouse_y;

            mouse_x = abs_x * sign_x;
            mouse_y += y;
            count = 0;

            return mouse_report;
        }

        count += abs_x;
        mouse_x += x;

        if (count + abs_y >= mag) {
            abs_y = count - mag;
            
            mouse_y += (count - mag) * sign_y;

            mouse_report.y = mouse_y;
            mouse_report.x = mouse_x;

            mouse_y = abs_y * sign_y;
            //mouse_x += x;
            count = 0;

            return mouse_report;
        }

        count += abs_y;
        mouse_y += y;

    } else {

         if (count + abs_y >= mag) {
            abs_y = count - mag;
            
            mouse_y += (count - mag) * sign_y;

            mouse_report.y = mouse_y;
            mouse_report.x = mouse_x;

            mouse_y = abs_y * sign_y;
            mouse_x += x;
            count = 0;

            return mouse_report;
        }

        count += abs_y;
        mouse_y += y;

        if (count + abs_x >= mag) {
            abs_x = count - mag;
            
            mouse_x += (count - mag) * sign_x;

            mouse_report.x = mouse_x;
            mouse_report.y = mouse_y;

            mouse_x = abs_x * sign_x;
            //mouse_y += y;
            count = 0;

            return mouse_report;
        }

        count += abs_x;
        mouse_x += x;
    }


    // if (mouse_report.x != 0 || mouse_report.y != 0)
    // {
    //     dprintf("x:%d y:%d \n", mouse_report.x, mouse_report.y);
    //     mouse_report.x *= 10;
    //     mouse_report.y *= 10;
    // }

    return mouse_report;

}
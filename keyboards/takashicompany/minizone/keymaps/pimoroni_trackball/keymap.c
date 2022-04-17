// Copyright 2022 takashicompany (@takashicompany)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "math.h"

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

int16_t max(int16_t a, int16_t b) {
    if (a > b) {
        return a;
    }

    return b;
}

int16_t min(int16_t a, int16_t b) {
    if (a < b) {
        return a;
    }

    return b;
}



void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  //debug_keyboard=true;
  // debug_mouse=true;
}

/*
int history_length = 100;

int16_t history_x[100] = {};
int16_t history_y[100] = {};
int16_t history_t[100] = {};

int16_t record_start;
bool is_recording;
int history_index = 0;

int16_t move_x;
int16_t move_y;
int16_t remain_move;



report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {

    int16_t current_x = mouse_report.x;
    int16_t current_y = mouse_report.y;

    mouse_report.x = 0;
    mouse_report.y = 0;

    if (current_x != 0 || current_y != 0)
    {
        history_x[history_index] = current_x;
        history_y[history_index] = current_y;
        history_t[history_index] = timer_read();

        history_index++;
        if (!is_recording)
        {
            is_recording = true;
            record_start = timer_read();
        }
    }

    if (is_recording)
    {
        if (timer_elapsed(record_start) > 10)
        {
            // move_x *= remain_move;
            // move_y *= remain_move;

            for (int i = 0; i < history_index; i++)
            {
                move_x += history_x[i];
                move_y += history_y[i];
                history_x[i] = 0;
                history_y[i] = 0;
            }

            // double rad = atan2(move_y, move_x);
            // // double length = sqrt(pow(move_x, 2) + pow(move_y, 2));

            // move_x = (int16_t)(cos(rad) * 2);
            // move_y = (int16_t)(sin(rad) * 2);

            remain_move += 3;
            // move_x /= remain_move;
            // move_y /= remain_move;

            // mouse_report.x = move_x;
            // mouse_report.y = move_y;

            // move_x = 0;
            // move_y = 0;

            is_recording = false;
            history_index = 0;

            dprintf("fire: %d x:%d y:%d \n", timer_elapsed(record_start), move_x, move_y);
        }
    }

   

    if (remain_move > 0)
    {
        mouse_report.x = move_x;
        mouse_report.y = move_y;

        remain_move--;
    }

    return mouse_report;

}
*/


int history_length = 10;

int16_t history_x[10] = {};
int16_t history_y[10] = {};
int16_t history_t[10] = {};


report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    dprintf("time:%d x:%d y:%d \n", timer_elapsed(0), mouse_report.x, mouse_report.y);

    int16_t current_x = history_x[0];
    int16_t current_y = history_y[0];

    int start = 1;
    int read_count = 10;

    if (current_x != 0 || current_y != 0)
    {
        for (int i = start; i < start + read_count && i < history_length; i++)
        {
            current_x += history_x[i];
            current_y += history_y[i];
            start = i;
        }
    }

    for (int i = start; i < history_length; i++)
    {
        history_x[i - start] = history_x[i];
        history_y[i - start] = history_y[i];
    }

    history_x[history_length - 1] = mouse_report.x;
    history_y[history_length - 1] = mouse_report.y;

    mouse_report.x = current_x * 2;
    mouse_report.y = current_y * 2;

    return mouse_report;

}

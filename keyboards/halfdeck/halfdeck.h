// Copyright 2018 Wez Furlong (@wez)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include "quantum.h"

// This maps the human perceived logical keycap layout to the less intuitive
// minimized hardware key matrix wiring.  This mapping is coupled with the
// row and column pin bindings in matrix.c
// lsw == "left switch", a switch position on the left half
// rsw == "right switch", a switch position on the right half
// LSW00 is the switch position labeled SW00 in the top left corner
// of the left half of the keyboard.  RSW00 is the switch position
// labeled SW00 on the top right corner of the right half
#define KEYMAP(\
               lsw00, lsw10, lsw50, lsw02, lsw52, lsw04, lsw54, \
               lsw30, lsw20, lsw11, lsw12, lsw22, lsw14, lsw44, \
               lsw40, lsw51, lsw01, lsw21, lsw32, lsw24, lsw34, \
               lsw03, lsw13, lsw41, lsw31, lsw42, lsw05, \
                                                         lsw55, \
                      lsw23,                      lsw15, lsw25, \
               lsw53, lsw33, lsw43,               lsw45, lsw35, \
               rhs64, rhs11_4, rhs62, rhs11_2, rhs60, rhs10_0, rhs11_0, \
               rhs74, rhs10_4, rhs92, rhs10_2, rhs10_1, rhs90, rhs80, \
               rhs84, rhs94, rhs82, rhs91, rhs11_1, rhs61, rhs70, \
                      rhs11_5, rhs72, rhs81, rhs71, rhs10_3, rhs11_3, \
               rhs65,                                           \
               rhs95, rhs10_5,                      rhs93,        \
               rhs85, rhs75,               rhs73, rhs83, rhs63) \
      {\
        {    lsw00, lsw01, lsw02, lsw03, lsw04, lsw05, rhs11_0, rhs11_1, rhs11_2, rhs11_3, rhs11_4, rhs11_5 }, \
        {    lsw10, lsw11, lsw12, lsw13, lsw14, lsw15, rhs10_0, rhs10_1, rhs10_2, rhs10_3, rhs10_4, rhs10_5 }, \
        {    lsw20, lsw21, lsw22, lsw23, lsw24, lsw25, rhs90, rhs91, rhs92, rhs93, rhs94, rhs95 }, \
        {    lsw30, lsw31, lsw32, lsw33, lsw34, lsw35, rhs80, rhs81, rhs82, rhs83, rhs84, rhs85 }, \
        {    lsw40, lsw41, lsw42, lsw43, lsw44, lsw45, rhs70, rhs71, rhs72, rhs73, rhs74, rhs75 }, \
        {    lsw50, lsw51, lsw52, lsw53, lsw54, lsw55, rhs60, rhs61, rhs62, rhs63, rhs64, rhs65 }}


bool sx1509_init(void);
uint16_t sx1509_read(void);
bool sx1509_make_ready(void);
bool sx1509_select_row(uint8_t row);
bool sx1509_unselect_row(uint8_t row);
bool sx1509_unselect_rows(void);
uint8_t sx1509_read_b(uint8_t current_row);

void halfdeck_led_enable(bool on);
void halfdeck_blink_led(int times);

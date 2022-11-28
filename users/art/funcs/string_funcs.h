// Copyright 2022 Artjoms Rizihs (@artjomsR)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include QMK_KEYBOARD_H

bool is_mac_with_base_layer_off(void);
void switch_lang(void);
void press_n_times(int times, uint16_t key);
bool handle_del_bspace(void);
void send_string_with_translation(char *string);
void send_string_remembering_length(char *string);
void send_shifted_strings(char *string1, char *string2);
void send_shifted_strings_add(char *string1, char *string2);
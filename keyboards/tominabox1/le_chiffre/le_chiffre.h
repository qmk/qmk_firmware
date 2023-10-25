// Copyright 2020 tominabox1 (@tominabox1) and sickbabies
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define KEYLOG_LEN 11

extern const char PROGMEM code_to_name[53];
extern const char PROGMEM lechiffre_logo[96];
extern const char PROGMEM oled_section_break[6];

void add_keylog(uint16_t keycode, keyrecord_t* record);
void render_keylock_status(led_t led_state);
void render_keylogger_status(void);
void render_layer_status(const char* layer_name);
void render_mod_status(uint8_t modifiers);
void update_layer_namebuf(layer_state_t layer, bool force_update);

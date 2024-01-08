// Copyright 2022 Álvaro Cortés (@ACortesDev)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#ifdef OLED_ENABLE
    bool process_record_oled(uint16_t keycode, keyrecord_t *record);
    oled_rotation_t oled_init_user(oled_rotation_t rotation);
    void render_layer_symbol(void);
    void render_layer_name(void);
    void render_mod_state(uint8_t modifiers);
    void render_status(void);
    bool oled_task_user(void);
#endif
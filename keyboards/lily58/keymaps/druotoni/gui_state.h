// Copyright 2021 Nicolas Druoton (druotoni)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// states timing
#define BOOTING_TIME_TRESHOLD 7000
#define WAKING_UP_TIME_TRESHOLD 300
#define IDLE_TIME_TRESHOLD 4000
#define HALTING_TIME_TRESHOLD IDLE_TIME_TRESHOLD + 6000
#define SLEEP_TIME_TRESHOLD HALTING_TIME_TRESHOLD + 8000

typedef uint8_t gui_state_t;
enum gui_state { _WAKINGUP = 0, _IDLE, _SLEEP, _UP, _BOOTING, _HALTING };

gui_state_t get_gui_state(void);
void        update_gui_state(void);
uint8_t     get_glitch_probability(void);
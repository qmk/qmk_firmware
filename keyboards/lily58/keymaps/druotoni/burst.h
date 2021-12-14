// Copyright 2021 Nicolas Druoton (druotoni)
// Copyright 2020 Richard Sutherland (rich@brickbots.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// burst
#define MAX_WPM_INIT 40
#define BURST_FENETRE 500

// wpm
#define LIMIT_MAX_WPM 150
#define WPM_ESTIMATED_WORD_SIZE 5
#define WPM_SMOOTHING 0.0487

// scope
#define SIZE_SCOPE 26
#define SCOPE_Y_BOTTOM 127

void update_scope(void);
void render_scope(gui_state_t t);

void reset_scope(void);
void decay_scope(void);

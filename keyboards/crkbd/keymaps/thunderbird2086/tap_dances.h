// Copyright 2021 Allen Choi (@thunderbird2086)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

enum custom_tapdances {
    TD_ESC_CAPS = 0,
    TD_TAB_CTRLTAB,
    TD_GRV_CTRLGRV,
    TD_GUI_GUISPC,
};

#define T_ESC  TD(TD_ESC_CAPS)          // Tap for ESC, double tap for CAPSLOCK
#define T_TAB  TD(TD_TAB_CTRLTAB)       // Tap for TAB, double tap for CTRL + TAB
#define T_GRV  TD(TD_GRV_CTRLGRV)       // Tap for GRV, double tap for Cmd + GRV
#define T_GUI  TD(TD_GUI_GUISPC)        // Tap for Cmd, double tap for Cmd + Space

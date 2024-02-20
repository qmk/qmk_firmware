// Copyright 2023 @boardsource
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"
__attribute__((weak)) void ui_init(void) {};
__attribute__((weak)) void ui_task(void) {};

#ifdef QUANTUM_PAINTER_ENABLE
void keyboard_post_init_kb(void) {
    // Init the display
    ui_init();
    keyboard_post_init_user();
}

void housekeeping_task_kb(void) {
    // Draw the display
    ui_task();
}
#endif //QUANTUM_PAINTER_ENABLE

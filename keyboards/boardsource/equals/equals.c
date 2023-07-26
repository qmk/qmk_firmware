// Copyright 2023 @boardsource
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"
extern void ui_init(void);
extern void ui_task(void);

#ifdef QUANTUM_PAINTER_ENABLE
void keyboard_post_init_kb(void) {
    // Init the display
    ui_init();
    keyboard_post_init_user();
}

void housekeeping_task_kb(void) {
    // Draw the display
    ui_task();
    housekeeping_task_user();
}
#endif //QUANTUM_PAINTER_ENABLE

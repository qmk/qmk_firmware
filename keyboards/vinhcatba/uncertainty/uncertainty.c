// Copyright 2023 Vinh Le (@vinhcatba)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

#ifdef OLED_ENABLE
#include "bongo.h"
// Used to draw on to the oled screen
bool oled_minimal = true;
bool oled_task_kb(void) {
    draw_bongo(oled_minimal);
    return false;
}
#endif // endif OLED_ENABLE

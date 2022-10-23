#pragma once

#include "keycode.h"

// use these instead of QMK's to keep the eep data in-synched
void set_custom_combo_enable(bool enabled);
bool is_custom_combo_enabled(void);
void custom_combo_toggle(void);
void custom_combo_init(void);

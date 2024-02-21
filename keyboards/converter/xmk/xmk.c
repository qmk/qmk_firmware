// Copyright 2022 Manna Harbour (@manna-harbour)
// https://github.com/manna-harbour/xmk

// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

#if defined (XMK_DEBUG)
void keyboard_post_init_kb(void) {
  debug_enable=true;
  debug_matrix=true;
  debug_keyboard=true;
}
#endif

// Copyright 2021 Jörg Markert (@venc0r)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "venc0r.h"

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

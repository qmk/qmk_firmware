// Copyright 2021 Google LLC
// Copyright 2021 @filterpaper
// SPDX-License-Identifier: Apache-2.0
// Original source: https://getreuer.info/posts/keyboards/autocorrection

#pragma once

#include "quantum.h"

bool process_autocorrect(uint16_t keycode, keyrecord_t *record);
bool process_autocorrect_user(uint16_t *keycode, keyrecord_t *record, uint8_t *typo_buffer_size, uint8_t *mods);
bool apply_autocorrect(uint8_t backspaces, const char *str);

bool autocorrect_is_enabled(void);
void autocorrect_enable(void);
void autocorrect_disable(void);
void autocorrect_toggle(void);

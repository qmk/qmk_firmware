// Copyright 2025 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/**
 * @file lumino.h
 * @brief Lumino module: opinionated control scheme for RGB matrix lighting
 *
 * This module for RGB matrix lighting is born from my personal use. I want
 * lighting at a dim or strong level depending on my environment, and I want to
 * minimize distractions. A simple control scheme is implemented:
 *
 *  - Pressing the `LUMINO` key cycles the lighting brightness between 3 states:
 *    off, 40%, and 100%. The set brightness is saved to EEPROM.
 *
 *  - Lighting turns off after 2 minutes of inactivity. However, if the keyboard
 *    had few key strokes since it last awoke, it turns off after 5 seconds.
 *
 *  - Brightness changes are smoothly animated to minimize distraction.
 *
 *  - When `QK_BOOT` is pressed, lighting is set to red color.
 *
 * Brightnesses and details above are configurable.
 *
 * For full documentation, see
 * <https://getreuer.info/posts/keyboards/lumino>
 */

#pragma once

#include "quantum.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Cycles between off, low, and high brightness.
 *
 * This function invokes the same effect as the `LUMINO` keycode, cycling the
 * brightness between 0, `LUMINO_LOW_BRIGHTNESS`, and `LUMINO_HIGH_BRIGHTNESS`.
 */
void lumino_cycle_3_state(void);

/**
 * Gets the current brightness.
 *
 * @returns Value between 0 and `RGB_MATRIX_MAXIMUM_BRIGHTNESS`.
 */
uint8_t lumino_get_value(void);

/** Sets a brightness between 0 and `RGB_MATRIX_MAXIMUM_BRIGHTNESS`. */
void lumino_set_value(uint8_t new_value);

/**
 * Tells lighting to sleep soon, provided few keystrokes occur.
 *
 * This function is useful to hint that the keyboard will likely go idle soon,
 * for instance when pressing a lock screen key. Lighting will sleep after
 * `LUMINO_SOON_TIMEOUT`, provided that few keystrokes occur in that time.
 */
void lumino_sleep_soon(void);

#ifdef __cplusplus
}
#endif


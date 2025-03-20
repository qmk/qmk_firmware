// Copyright 2023-2025 Google LLC
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
 * @file orbital_mouse.h
 * @brief Orbital Mouse community module: a polar approach to mouse control.
 *
 * Orbital Mouse is a module that replaces QMK Mouse Keys. The pointer moves
 * according to a heading direction. Two keys move forward and backward along
 * that direction while another two keys steer.
 *
 * For documentation, see
 * <https://getreuer.info/posts/keyboards/orbital-mouse>
 */

#pragma once

#include "quantum.h"

/**
 * Sets the pointer movement speed curve at run time.
 *
 * This function enables dynamically switching between multiple speed curves.
 *
 * @param speed_curve Pointer to an array of size 16. If NULL, the speed curve
 *                    defined by ORBITAL_MOUSE_SPEED_CURVE is set.
 */
void set_orbital_mouse_speed_curve(const uint8_t* speed_curve);

/**
 * Gets the heading direction as a value in 0-63.
 *
 * Value 0 is up, and values increase in the counter-clockwise direction.
 *
 *      0 = up            32 = down
 *      8 = up-left       40 = down-right
 *     16 = left          48 = right
 *     24 = down-left     56 = up-right
 */
uint8_t get_orbital_mouse_angle(void);

/** Sets the heading direction. */
void set_orbital_mouse_angle(uint8_t angle);

// The following defines keycodes for Orbital Mouse. Being a Mouse Keys
// replacement, we repurpose the Mouse Keys keycodes (`MS_UP`, `MS_BTN1`,
// etc.) for the analogous functions in Orbital Mouse.
enum {
  /** Move forward. */
  OM_U = MS_UP,
  /** Move backward. */
  OM_D = MS_DOWN,
  /** Steer left (counter-clockwise). */
  OM_L = MS_LEFT,
  /** Steer right (clockwise). */
  OM_R = MS_RGHT,
  /** Mouse wheel up. */
  OM_W_U = MS_WHLU,
  /** Mouse wheel down. */
  OM_W_D = MS_WHLD,
  /** Mouse wheel left. */
  OM_W_L = MS_WHLL,
  /** Mouse wheel right. */
  OM_W_R = MS_WHLR,
  /** Press mouse button 1. */
  OM_BTN1 = MS_BTN1,
  /** Press mouse button 2. */
  OM_BTN2 = MS_BTN2,
  /** Press mouse button 3. */
  OM_BTN3 = MS_BTN3,
  /** Press mouse button 4. */
  OM_BTN4 = MS_BTN4,
  /** Press mouse button 5. */
  OM_BTN5 = MS_BTN5,
  /** Press mouse button 6. */
  OM_BTN6 = MS_BTN6,
  /** Press mouse button 7. */
  OM_BTN7 = MS_BTN7,
  /** Press mouse button 8. */
  OM_BTN8 = MS_BTN8,
};


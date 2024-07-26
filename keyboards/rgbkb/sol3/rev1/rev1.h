/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <https://github.com/Legonut> wrote this file.  As long as you retain this
 * notice you can do whatever you want with this stuff. If we meet some day, and
 * you think this stuff is worth it, you can buy me a beer in return. David Rauseo
 * ----------------------------------------------------------------------------
 */

#pragma once

#include "quantum.h"
#include "touch_encoder.h"
#include "common_oled.h"

// weak functions overridable by the user
void render_layer_status(void);
void render_leds_status(void);
void render_touch_status(void);
void render_audio_status(void);

#ifdef RGB_MATRIX_ENABLE
// utility function to cycle active led zones
void rgb_matrix_increase_flags(void);
#endif
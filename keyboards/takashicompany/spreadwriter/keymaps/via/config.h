// Copyright 2022 takashicompany (@takashicompany)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define DYNAMIC_KEYMAP_LAYER_COUNT 7

//------------------------------------------------------------------------------
// Rotary Encoder
//------------------------------------------------------------------------------
// Encoder triggers specific key matrix position,
// when turn knob clockwise or counterclockwise.
// This is handy to assign key codes by VIA.

// Mappings of encoder rotation to key position in key matrix.
#define ENCODERS_CW_KEY  { { 0, 4 }}
#define ENCODERS_CCW_KEY { { 6, 0 }}
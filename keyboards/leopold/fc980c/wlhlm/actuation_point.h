// Copyright 2023 Wilhelm Schuster
// Copyright 2017 Balz Guenat
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdint.h>

// Check out keymaps/actuation_point_example to see how these functions can be used.
// Read current actuation point value
int8_t actuation_point_read_rdac(void);
// Read factory stored actuation point value
int8_t actuation_point_read_eeprom(void);
// Set new actuation point value (discarded on power loss)
int8_t actuation_point_write_rdac(uint8_t value);

// Adjust current actuation point value (discarded on power loss)
int8_t actuation_point_make_shallower(void);
int8_t actuation_point_make_deeper(void);
int8_t actuation_point_adjust(int8_t offset);

// Restore factory actuation point value
void actuation_point_reset(void);

#pragma once

//------------------------------------------------------------------------------
// External EEPROM
//------------------------------------------------------------------------------

// Use 24LC64 EEPROM
#define EEPROM_I2C_24LC64

// Set MAX_ADDR to specify actual EEPROM size.
// If it's not set, EEPROM size will be set ATmega32u4's 1023.
#define DYNAMIC_KEYMAP_EEPROM_MAX_ADDR 8191

// How many layers to use with VIA / Remap.
#define DYNAMIC_KEYMAP_LAYER_COUNT 6 // default:4

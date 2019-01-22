#pragma once

#include "raw_hid.h"
#include "dynamic_keymap.h"
#include "timer.h"
#include "tmk_core/common/eeprom.h"


#define PROTOCOL_VERSION 0x0008

#define DYNAMIC_KEYMAP_LAYER_COUNT 4



enum via_command_id {
	id_get_protocol_version = 0x01, // always 0x01
	id_get_keyboard_value,
	id_set_keyboard_value,
	id_dynamic_keymap_get_keycode,
	id_dynamic_keymap_set_keycode,
	id_dynamic_keymap_reset,
	id_backlight_config_set_value,
	id_backlight_config_get_value,
	id_backlight_config_save,
	id_eeprom_reset,
	id_bootloader_jump,
	id_dynamic_keymap_macro_get_count,
	id_dynamic_keymap_macro_get_buffer_size,
	id_dynamic_keymap_macro_get_buffer,
	id_dynamic_keymap_macro_set_buffer,
	id_dynamic_keymap_macro_reset,
	id_dynamic_keymap_get_layer_count,
	id_dynamic_keymap_get_buffer,
	id_dynamic_keymap_set_buffer,
	id_unhandled = 0xFF,
};

enum zeal60_keyboard_value_id {
	id_uptime = 0x01
};



void via_init(void);
bool process_via(uint16_t keycode, keyrecord_t *record);

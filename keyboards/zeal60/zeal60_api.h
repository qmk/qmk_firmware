#ifndef ZEAL60_API_H
#define ZEAL60_API_H

#define PROTOCOL_VERSION 0x0007

enum zeal60_command_id
{
	id_get_protocol_version = 0x01, // always 0x01
	id_get_keyboard_value,
	id_set_keyboard_value,
	id_dynamic_keymap_get_keycode,
	id_dynamic_keymap_set_keycode,
	id_dynamic_keymap_clear_all,
	id_backlight_config_set_value,
	id_backlight_config_get_value,
	id_backlight_config_save,

	id_unhandled = 0xFF,
};

#endif // ZEAL60_API_H

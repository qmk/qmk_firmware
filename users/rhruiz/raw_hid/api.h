enum rhruiz_command_id {
    id_get_protocol_version = 0x01,  // always 0x01
    id_get_keyboard_value,
    id_set_keyboard_value,
    id_bootloader_jump,
    id_backlight_toggle,
    id_rgblight_toggle,
    id_rgblight_reset,
    id_rgblight_color,
    id_unhandled = 0xFF,
};

enum rhruiz_keyboard_value_id { id_uptime = 0x01 };

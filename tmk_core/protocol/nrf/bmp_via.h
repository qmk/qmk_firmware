
#pragma once

enum via_bmp_set_id {
    id_control_save_flag = 0xFF,
    id_bmp_item = 0xFE,
};

enum via_bmp_item_id {
    item_protocol_version,
    item_extend_keycode_count,
    item_extend_keycode,
    item_config_len,
    item_config_buffer,
    item_tapping_term_len,
    item_tapping_term_buffer,
    item_encoder_len,
    item_encoder_buffer,
    item_remove_files,
};

#define BMP_VIA_PROTOCOL_VER 0x01


void dynamic_keymap_reset(void);

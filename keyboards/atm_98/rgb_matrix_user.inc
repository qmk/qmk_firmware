// rgb_matrix_user.inc
RGB_MATRIX_EFFECT(CUSTOM_COLOR)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

#include <string.h>
#include "raw_hid.h"
#include "eeconfig.h"
#include "print.h"
#include "timer.h"
#include "flash.h"
#include "flash_spi.h"

#ifndef EECONFIG_KB_DATA_SIZE
#    error "EECONFIG_KB_DATA_SIZE must be defined"
#endif

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} user_color_t;

#define KEY_NUM 98
#define CUSTOM_RGB_MODE 45
#define RGBS_PER_PACKET 8
#define RGB_BYTES_PER_PACKET 24
#define MAX_FRAMES 255
#define PACKETS_PER_FRAME ((KEY_NUM + RGBS_PER_PACKET - 1) / RGBS_PER_PACKET)
#define FRAME_BYTE_COUNT (KEY_NUM * sizeof(user_color_t))
#define LAST_PACKET_RGB_BYTES ((KEY_NUM % RGBS_PER_PACKET) * sizeof(user_color_t))

#define CUSTOM_RGB_MAGIC   0xA5
#define CUSTOM_RGB_VERSION 0x04

#define CUSTOM_ANIM_FLASH_ADDR      EXTERNAL_FLASH_BLOCK_SIZE
#define CUSTOM_ANIM_FLASH_MAX_BYTES (MAX_FRAMES * FRAME_BYTE_COUNT)
#define CUSTOM_ANIM_FLASH_END       (CUSTOM_ANIM_FLASH_ADDR + CUSTOM_ANIM_FLASH_MAX_BYTES)

typedef struct __attribute__((packed)) {
    uint8_t  magic;
    uint8_t  version;
    uint8_t  key_num;
    uint8_t  frame_count;
    uint8_t  frame_interval_ms;
    uint8_t  packet_count;
    uint16_t frame_bytes;
    uint32_t data_address;
    uint32_t data_length;
    uint8_t  reserved[EECONFIG_KB_DATA_SIZE - 16];
} custom_rgb_anim_config_t;

_Static_assert(sizeof(custom_rgb_anim_config_t) == EECONFIG_KB_DATA_SIZE, "custom RGB config size must match EECONFIG_KB_DATA_SIZE");
_Static_assert(CUSTOM_ANIM_FLASH_END <= EXTERNAL_FLASH_SIZE, "custom RGB animation region exceeds external flash size");

static custom_rgb_anim_config_t eeconfig_write_buffer;
static custom_rgb_anim_config_t eeconfig_read_buffer;

static user_color_t current_frame_buffer[KEY_NUM];
static uint16_t     received_packets_mask[MAX_FRAMES] = {0};

static uint8_t  anim_frame_count    = 0;
static uint8_t  pending_frame_count = 0;
static uint8_t  anim_interval_ms    = 0x32;
static uint8_t  pending_interval_ms = 0x32;
static uint8_t  current_frame       = 0;
static uint32_t last_frame_tick     = 0;

static bool use_custom_color_table = false;
static bool custom_colors_valid    = false;
static bool rgb_data_dirty         = false;
static bool upload_started         = false;

void custom_color_activate_and_persist(void);



static uint32_t frame_flash_addr(uint8_t frame_idx) {
    return CUSTOM_ANIM_FLASH_ADDR + ((uint32_t)frame_idx * FRAME_BYTE_COUNT);
}

#ifdef VIA_ENABLE
static bool erase_animation_storage(void) {
    for (uint32_t addr = CUSTOM_ANIM_FLASH_ADDR; addr < CUSTOM_ANIM_FLASH_END; addr += EXTERNAL_FLASH_SECTOR_SIZE) {
        flash_status_t status = flash_erase_sector(addr);
        if (status != FLASH_STATUS_SUCCESS) {
            return false;
        }
    }

    return true;
}
#endif

static bool load_frame_from_flash(uint8_t frame_idx) {
    if (frame_idx >= anim_frame_count) {
        return false;
    }

    flash_status_t status = flash_read_range(frame_flash_addr(frame_idx), current_frame_buffer, FRAME_BYTE_COUNT);
    if (status != FLASH_STATUS_SUCCESS) {
        memset(current_frame_buffer, 0, sizeof(current_frame_buffer));
        return false;
    }

    return true;
}

static void save_anim_to_eeconfig(void) {
    memset(&eeconfig_write_buffer, 0, sizeof(eeconfig_write_buffer));
    eeconfig_write_buffer.magic             = CUSTOM_RGB_MAGIC;
    eeconfig_write_buffer.version           = CUSTOM_RGB_VERSION;
    eeconfig_write_buffer.key_num           = KEY_NUM;
    eeconfig_write_buffer.frame_count       = anim_frame_count;
    eeconfig_write_buffer.frame_interval_ms = anim_interval_ms;
    eeconfig_write_buffer.packet_count      = PACKETS_PER_FRAME;
    eeconfig_write_buffer.frame_bytes       = FRAME_BYTE_COUNT;
    eeconfig_write_buffer.data_address      = CUSTOM_ANIM_FLASH_ADDR;
    eeconfig_write_buffer.data_length       = (uint32_t)anim_frame_count * FRAME_BYTE_COUNT;

    eeconfig_update_kb_datablock(&eeconfig_write_buffer);
}

static bool load_anim_from_eeconfig(void) {
    eeconfig_read_kb_datablock(&eeconfig_read_buffer);

    if (eeconfig_read_buffer.magic != CUSTOM_RGB_MAGIC) {
        return false;
    }

    if (eeconfig_read_buffer.version != CUSTOM_RGB_VERSION) {
        return false;
    }

    if (eeconfig_read_buffer.key_num != KEY_NUM) {
        return false;
    }

    if (eeconfig_read_buffer.frame_count == 0 || eeconfig_read_buffer.frame_count > MAX_FRAMES) {
        return false;
    }

    if (eeconfig_read_buffer.packet_count != PACKETS_PER_FRAME || eeconfig_read_buffer.frame_bytes != FRAME_BYTE_COUNT) {
        return false;
    }

    if (eeconfig_read_buffer.data_address != CUSTOM_ANIM_FLASH_ADDR ||
        eeconfig_read_buffer.data_length == 0 ||
        eeconfig_read_buffer.data_length > CUSTOM_ANIM_FLASH_MAX_BYTES) {
        return false;
    }

    anim_frame_count = eeconfig_read_buffer.frame_count;
    anim_interval_ms = eeconfig_read_buffer.frame_interval_ms < 0x32 ? 0x32 : eeconfig_read_buffer.frame_interval_ms;
    current_frame    = 0;
    last_frame_tick  = timer_read32();

    if (!load_frame_from_flash(0)) {
        return false;
    }

    return true;
}

static bool is_eeconfig_initialized(void) {
    if (!eeconfig_is_kb_datablock_valid()) {
        return false;
    }

    eeconfig_read_kb_datablock(&eeconfig_read_buffer);

    return (eeconfig_read_buffer.magic == CUSTOM_RGB_MAGIC &&
            eeconfig_read_buffer.version == CUSTOM_RGB_VERSION &&
            eeconfig_read_buffer.key_num == KEY_NUM &&
            eeconfig_read_buffer.frame_count > 0 &&
            eeconfig_read_buffer.frame_count <= MAX_FRAMES &&
            eeconfig_read_buffer.packet_count == PACKETS_PER_FRAME &&
            eeconfig_read_buffer.frame_bytes == FRAME_BYTE_COUNT &&
            eeconfig_read_buffer.data_address == CUSTOM_ANIM_FLASH_ADDR &&
            eeconfig_read_buffer.data_length > 0 &&
            eeconfig_read_buffer.data_length <= CUSTOM_ANIM_FLASH_MAX_BYTES);
}

static void reset_pending_state(void) {
    memset(received_packets_mask, 0, sizeof(received_packets_mask));
    pending_frame_count = 0;
    pending_interval_ms = 0x32;
    upload_started      = false;
}

static void init_empty_anim(void) {
    memset(current_frame_buffer, 0, sizeof(current_frame_buffer));
    reset_pending_state();

    anim_frame_count    = 0;
    anim_interval_ms    = 0x32;
    current_frame       = 0;
    last_frame_tick     = timer_read32();
    custom_colors_valid = false;
    rgb_data_dirty      = false;

}

#ifdef VIA_ENABLE
static void commit_pending_animation(void) {
    anim_frame_count = pending_frame_count;
    anim_interval_ms = pending_interval_ms < 0x32 ? 0x32 : pending_interval_ms;
    current_frame    = 0;
    last_frame_tick  = timer_read32();

    custom_colors_valid = (anim_frame_count > 0) && load_frame_from_flash(0);
    rgb_data_dirty      = custom_colors_valid;
    upload_started      = false;

}

static bool write_packet_to_flash(uint8_t frame_idx, uint8_t packet_idx, uint8_t rgb_len, const uint8_t *rgb_bytes) {
    uint8_t start_led = packet_idx * RGBS_PER_PACKET;
    uint32_t addr = frame_flash_addr(frame_idx) + ((uint32_t)start_led * sizeof(user_color_t));
    size_t   len  = rgb_len;

    flash_status_t status = flash_write_range(addr, rgb_bytes, len);
    if (status != FLASH_STATUS_SUCCESS) {
        return false;
    }

    return true;
}
#endif

#ifdef VIA_ENABLE
static void process_rgb_packet(uint8_t *data, uint8_t length) {
    if (length < 32 || data[0] != 0xF0) {
        return;
    }

    uint8_t frame_idx  = data[2];
    uint8_t packet_idx = data[3];
    uint8_t interval   = data[5];
    uint8_t rgb_len    = data[6];



    if (packet_idx == 0xFF) {
        uint8_t final_packet_idx = PACKETS_PER_FRAME - 1;

        if (frame_idx >= MAX_FRAMES) {
            data[0] = 0xF1;
            raw_hid_send(data, length);
            return;
        }

        if (rgb_len != LAST_PACKET_RGB_BYTES) {
            data[0] = 0xF1;
            raw_hid_send(data, length);
            return;
        }

        if (!upload_started) {
            data[0] = 0xF1;
            raw_hid_send(data, length);
            return;
        }

        pending_interval_ms = interval < 0x32 ? 0x32 : interval;
        // 0xFF means this is the final packet of the whole upload.
        pending_frame_count = frame_idx + 1;

        if (!write_packet_to_flash(frame_idx, final_packet_idx, rgb_len, &data[7])) {
            data[0] = 0xF1;
            raw_hid_send(data, length);
            return;
        }

        received_packets_mask[frame_idx] |= (1u << final_packet_idx);
        data[0] = 0xF1;
        raw_hid_send(data, length);

        commit_pending_animation();
        if (custom_colors_valid) {
            custom_color_activate_and_persist();
        }
        memset(received_packets_mask, 0, sizeof(received_packets_mask));
        return;
    }

    if (frame_idx >= MAX_FRAMES) {
        data[0] = 0xF1;
        raw_hid_send(data, length);
        return;
    }

    if (packet_idx >= PACKETS_PER_FRAME) {
        data[0] = 0xF1;
        raw_hid_send(data, length);
        return;
    }

    uint8_t expected_rgb_len = (packet_idx == (PACKETS_PER_FRAME - 1)) ? LAST_PACKET_RGB_BYTES : RGB_BYTES_PER_PACKET;
    if (rgb_len != expected_rgb_len) {
        data[0] = 0xF1;
        raw_hid_send(data, length);
        return;
    }

    if (interval < 0x32) {
        interval = 0x32;
    }

    if (packet_idx == 0 && frame_idx == 0) {
        reset_pending_state();
        if (!erase_animation_storage()) {
            data[0] = 0xF1;
            raw_hid_send(data, length);
            return;
        }
        upload_started = true;
    }

    if (!upload_started) {
        data[0] = 0xF1;
        raw_hid_send(data, length);
        return;
    }

    pending_interval_ms = interval;
    if ((frame_idx + 1) > pending_frame_count) {
        pending_frame_count = frame_idx + 1;
    }

    if (!write_packet_to_flash(frame_idx, packet_idx, rgb_len, &data[7])) {
        data[0] = 0xF1;
        raw_hid_send(data, length);
        return;
    }

    received_packets_mask[frame_idx] |= (1u << packet_idx);


    data[0] = 0xF1;
    raw_hid_send(data, length);
}

static void handle_firmware_version_read(uint8_t *data, uint8_t length) {
    data[3] = ATM_FIRMWARE_VERSION_PATCH;
    data[4] = ATM_FIRMWARE_VERSION_MINOR;
    data[5] = ATM_FIRMWARE_VERSION_MAJOR;
    for (uint8_t i = 6; i < 31; i++) {
        data[i] = 0x00;
    }
    data[31] = 0xFF;
    raw_hid_send(data, length);
}

bool via_command_kb(uint8_t *data, uint8_t length) {
    if (length >= 32 && data[0] == 0xF0) {
        // 固件版本读取: F0 0E 01 ...
        if (data[1] == 0x0E && data[2] == 0x01) {
            handle_firmware_version_read(data, length);
            return true;
        }
        // RGB 自定义包处理
        process_rgb_packet(data, length);
        return true;
    }
    return false;
}
#endif

void custom_color_init(void) {

    flash_init();
    reset_pending_state();
    rgb_data_dirty      = false;
    custom_colors_valid = false;

    if (!is_eeconfig_initialized()) {
        init_empty_anim();
    } else {
        if (!load_anim_from_eeconfig()) {
            init_empty_anim();
        } else {
            pending_frame_count = anim_frame_count;
            pending_interval_ms = anim_interval_ms;
            custom_colors_valid = true;
        }
    }

    if (custom_colors_valid) {

    }
}

bool custom_color_flush_task(void) {
    if (rgb_data_dirty) {
        rgb_data_dirty = false;
        save_anim_to_eeconfig();
        return true;
    }
    return false;
}

const user_color_t *custom_color_get_table(void) {
    if (!custom_colors_valid || anim_frame_count == 0) {
        return NULL;
    }
    return current_frame_buffer;
}

void custom_color_set_enabled(bool enabled) {
    use_custom_color_table = enabled;
}

bool custom_color_is_enabled(void) {
    return use_custom_color_table;
}

bool custom_color_has_valid_data(void) {
    return custom_colors_valid;
}

void custom_color_clear_runtime(void) {
    init_empty_anim();
    use_custom_color_table = false;
}

static bool CUSTOM_COLOR(effect_params_t *params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    if (!custom_colors_valid || anim_frame_count == 0) {
        return rgb_matrix_check_finished_leds(led_max);
    }

    if (anim_frame_count > 1 && timer_elapsed32(last_frame_tick) >= anim_interval_ms) {
        last_frame_tick = timer_read32();
        current_frame   = (current_frame + 1) % anim_frame_count;
        if (!load_frame_from_flash(current_frame)) {
            return rgb_matrix_check_finished_leds(led_max);
        }
    }

    const user_color_t *frame = current_frame_buffer;

    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        if (i < KEY_NUM) {
            rgb_matrix_set_color(i, frame[i].r, frame[i].g, frame[i].b);
        }
    }

    return rgb_matrix_check_finished_leds(led_max);
}
#endif


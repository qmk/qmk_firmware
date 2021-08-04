
#include "bmp_macro.h"

#include <string.h>

#include "send_string.h"
#include "debug.h"

#include "apidef.h"

static uint8_t* macro_file;
static uint32_t macro_file_length;
static int8_t   active_macro = -1;
static uint16_t active_macro_offset;

#define ASSERT_MACRO_FILE()       \
    if (macro_file == NULL) {     \
        bmp_macro_load_file();    \
        if (macro_file == NULL) { \
            return;               \
        }                         \
    }

void bmp_macro_task(void) {
    if (active_macro < 0) {
        return;
    }

    char data[4] = {0, 0, 0, 0};
    data[0]      = macro_file[active_macro_offset++];
    data[1]      = 0;

    if (data[0] == 0) {
        active_macro = -1;
        return;
    }

    if (data[0] == SS_TAP_CODE || data[0] == SS_DOWN_CODE ||
        data[0] == SS_UP_CODE) {
        data[1] = data[0];
        data[0] = SS_QMK_PREFIX;
        data[2] = macro_file[active_macro_offset++];
        if (data[2] == 0) {
            active_macro = -1;
            return;
        }
    }

    send_string(data);
}

uint8_t* bmp_macro_get_file_buffer(void) { return macro_file; }

void bmp_macro_load_file(void) {
    BMPAPI->app.get_file(BMP_MACRO_RECORD, &macro_file, &macro_file_length);
    if (macro_file == NULL) {
        BMPAPI->app.save_file(BMP_MACRO_RECORD);  // create file
    }
}

void bmp_macro_save_file(void) { BMPAPI->app.save_file(BMP_MACRO_RECORD); }

void bmp_macro_send(uint8_t id) {
    ASSERT_MACRO_FILE();

    if (id >= BMP_MACRO_COUNT) {
        dprintf("[Macro] Invalid ID:%d\n", id);
        return;
    }

    const uint8_t* end_addr = macro_file + BMP_MACRO_FILE_LEN - 1;

    if (*end_addr != 0) {
        dprintf("[Macro] Invalid macro\n");
        return;
    }

    if (active_macro >= 0) {
        dprintf("[Macro] Other macro running\n");
        return;
    }

    dprintf("[Macro] Activate %d\n", id);

    active_macro_offset = 0;

    for (active_macro = 0; active_macro < id; active_macro++) {
        while (macro_file[active_macro_offset++] != 0) {
            continue;
        }

        if (active_macro_offset >= BMP_MACRO_FILE_LEN - 1) {
            dprintf("Invalid macro file\n");
            active_macro = -1;
            return;
        }
    }
}

void bmp_macro_get_buffer(uint16_t offset, uint16_t size, uint8_t* buffer) {
    ASSERT_MACRO_FILE();

    memcpy(buffer, macro_file + offset, size);
}

void bmp_macro_set_buffer(uint16_t offset, uint16_t size, uint8_t* buffer) {
    ASSERT_MACRO_FILE();

    if (offset + size >= BMP_MACRO_FILE_LEN) {
        dprintf("[Macro] Invalid size: %d\n", offset + size);
        return;
    }

    memcpy(macro_file + offset, buffer, size);
}

void bmp_macro_reset(void) {
    ASSERT_MACRO_FILE();

    memset(macro_file, 0, BMP_MACRO_FILE_LEN);
}


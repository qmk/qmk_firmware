// Copyright 2016 Jack Humbert
// Copyright 2019 Wojciech Siewierski < wojciech dot siewierski at onet dot pl >
// Copyright 2023 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "keyrecords/dynamic_macros.h"
#include "keyrecords/process_records.h"
#include "wait.h"
#include "debug.h"
#include "eeprom.h"
#include "eeconfig.h"
#include <string.h>

static uint8_t macro_id        = 255;
static uint8_t recording_state = STATE_NOT_RECORDING;

#if EECONFIG_USER_DATA_SIZE < 4
#    error "EECONFIG_USER_DATA_SIZE not set. Don't step on others eeprom."
#endif
#ifndef DYNAMIC_MACRO_EEPROM_BLOCK0_ADDR
#    define DYNAMIC_MACRO_EEPROM_BLOCK0_ADDR (uint8_t*)(EECONFIG_USER_DATABLOCK + 4)
#endif

dynamic_macro_t dynamic_macros[DYNAMIC_MACRO_COUNT];
_Static_assert((sizeof(dynamic_macros)) <= (EECONFIG_USER_DATA_SIZE - 4), "User Data Size must be large enough to host all macros");

__attribute__((weak)) void dynamic_macro_record_start_user(void) {}

__attribute__((weak)) void dynamic_macro_play_user(uint8_t macro_id) {}

__attribute__((weak)) void dynamic_macro_record_key_user(uint8_t macro_id, keyrecord_t* record) {}

__attribute__((weak)) void dynamic_macro_record_end_user(uint8_t macro_id) {}

/**
 * @brief Gets the current macro ID
 *
 * @return uint8_t
 */
uint8_t dynamic_macro_get_current_id(void) {
    return macro_id;
}

/**
 * @brief Gets the current recording state
 *
 * @return uint8_t
 */
uint8_t dynamic_macro_get_recording_state(void) {
    return recording_state;
}

/**
 * Start recording of the dynamic macro.
 *
 * @param macro_id[in]     The id of macro to be recorded
 */
bool dynamic_macro_record_start(uint8_t macro_id) {
    if (macro_id >= (uint8_t)(DYNAMIC_MACRO_COUNT)) {
        return false;
    }
    dprintf("dynamic macro recording: started for slot %d\n", macro_id);

    dynamic_macro_record_start_user();

    clear_keyboard();
    layer_clear();

    dynamic_macros[macro_id].length = 0;
    return true;
}

/**
 * Play the dynamic macro.
 *
 * @param macro_id[in]     The id of macro to be played
 */
void dynamic_macro_play(uint8_t macro_id) {
    if (macro_id >= (uint8_t)(DYNAMIC_MACRO_COUNT)) {
        return;
    }

    dprintf("dynamic macro: slot %d playback, length %d\n", macro_id, dynamic_macros[macro_id].length);

    layer_state_t saved_layer_state = layer_state;

    clear_keyboard();
    layer_clear();

    for (uint8_t i = 0; i < dynamic_macros[macro_id].length; ++i) {
        process_record(&dynamic_macros[macro_id].events[i]);
    }

    clear_keyboard();

    layer_state_set(saved_layer_state);

    dynamic_macro_play_user(macro_id);
}

/**
 * Record a single key in a dynamic macro.
 *
 * @param macro_id[in] The start of the used macro buffer.
 * @param record[in]     The current keypress.
 */
void dynamic_macro_record_key(uint8_t macro_id, keyrecord_t* record) {
    dynamic_macro_t* macro  = &dynamic_macros[macro_id];
    uint8_t          length = macro->length;

    /* If we've just started recording, ignore all the key releases. */
    if (!record->event.pressed && length == 0) {
        dprintln("dynamic macro: ignoring a leading key-up event");
        return;
    }

    if (length < DYNAMIC_MACRO_SIZE) {
        macro->events[length] = *record;
        macro->length         = ++length;
    } else {
        dynamic_macro_record_key_user(macro_id, record);
    }

    dprintf("dynamic macro: slot %d length: %d/%d\n", macro_id, length, DYNAMIC_MACRO_SIZE);
}

/**
 * End recording of the dynamic macro. Essentially just update the
 * pointer to the end of the macro.
 */
void dynamic_macro_record_end(uint8_t macro_id) {
    if (macro_id >= (uint8_t)(DYNAMIC_MACRO_COUNT)) {
        return;
    }
    dynamic_macro_record_end_user(macro_id);

    dynamic_macro_t* macro  = &dynamic_macros[macro_id];
    uint8_t          length = macro->length;

    keyrecord_t* events_begin   = &(macro->events[0]);
    keyrecord_t* events_pointer = &(macro->events[length - 1]);

    dprintf("dynamic_macro: macro length before trimming: %d\n", macro->length);
    while (events_pointer != events_begin && (events_pointer)->event.pressed) {
        dprintln("dynamic macro: trimming a trailing key-down event");
        --(macro->length);
        --events_pointer;
    }

    macro->checksum = dynamic_macro_calc_crc(macro);
    dynamic_macro_save_eeprom(macro_id);

    dprintf("dynamic macro: slot %d saved, length: %d\n", macro_id, length);
}

bool process_record_dynamic_macro(uint16_t keycode, keyrecord_t* record) {
    if (STATE_NOT_RECORDING == recording_state) {
        /* Program key pressed to request programming mode */
        if (keycode == DYN_MACRO_PROG && record->event.pressed) {
            // dynamic_macro_led_blink();

            recording_state = STATE_RECORD_KEY_PRESSED;
            dprintf("dynamic macro: programming key pressed, waiting for macro slot selection. %d\n", recording_state);

            return false;
        }
        /* Macro key pressed to request macro playback */
        if (IS_DYN_KEYCODE(keycode) && record->event.pressed) {
            dynamic_macro_play(keycode - DYN_MACRO_KEY00);

            return false;
        }

        /* Non-dynamic macro key, process it elsewhere. */
        return true;
    } else if (STATE_RECORD_KEY_PRESSED == recording_state) {
        /* Program key pressed again before a macro selector key, cancel macro recording.
           Blink leds to indicate cancelation. */
        if (keycode == DYN_MACRO_PROG && record->event.pressed) {
            // dynamic_macro_led_blink();

            recording_state = STATE_NOT_RECORDING;
            dprintf("dynamic macro: programming key pressed, programming mode canceled. %d\n", recording_state);

            return false;
        } else if (IS_DYN_KEYCODE(keycode) && record->event.pressed) {
            macro_id = keycode - DYN_MACRO_KEY00;

            if (dynamic_macro_record_start(macro_id)) {
                /* Macro slot selected, enter recording state. */
                recording_state = STATE_CURRENTLY_RECORDING;
            } else {
                recording_state = STATE_NOT_RECORDING;
            }

            return false;
        }
        /* Ignore any non-macro key press while in RECORD_KEY_PRESSED state. */
        return false;
    } else if (STATE_CURRENTLY_RECORDING == recording_state) {
        /* Program key pressed to request end of macro recording. */
        if (keycode == DYN_MACRO_PROG && record->event.pressed) {
            dynamic_macro_record_end(macro_id);
            recording_state = STATE_NOT_RECORDING;

            return false;
        }
        /* Don't record other macro key presses. */
        else if (IS_DYN_KEYCODE(keycode) && record->event.pressed) {
            dprintln("dynamic macro: playback key ignored in programming mode.");
            return false;
        }
        /* Non-macro keypress that should be recorded  */
        else {
            dynamic_macro_record_key(macro_id, record);

            /* Don't output recorded keypress. */
            return false;
        }
    }

    return true;
}

static inline uint16_t crc16_update(uint16_t crc, uint8_t a) {
    crc ^= a;
    for (uint8_t i = 0; i < 8; ++i) {
        if (crc & 1)
            crc = (crc >> 1) ^ 0xA001;
        else
            crc = (crc >> 1);
    }
    return crc;
}

uint16_t dynamic_macro_calc_crc(dynamic_macro_t* macro) {
    uint16_t crc  = 0;
    uint8_t* data = (uint8_t*)macro;

    for (uint16_t i = 0; i < DYNAMIC_MACRO_CRC_LENGTH; ++i) {
        crc = crc16_update(crc, *(data++));
    }
    return crc;
}

inline void* dynamic_macro_eeprom_macro_addr(uint8_t macro_id) {
    return DYNAMIC_MACRO_EEPROM_BLOCK0_ADDR + sizeof(dynamic_macro_t) * macro_id;
}

void dynamic_macro_load_eeprom_all(void) {
    for (uint8_t i = 0; i < DYNAMIC_MACRO_COUNT; ++i) {
        dynamic_macro_load_eeprom(i);
    }
}

void dynamic_macro_load_eeprom(uint8_t macro_id) {
    dynamic_macro_t* dst = &dynamic_macros[macro_id];

    eeprom_read_block(dst, dynamic_macro_eeprom_macro_addr(macro_id), sizeof(dynamic_macro_t));

    /* Validate checksum, ifchecksum is NOT valid for macro, set its length to 0 to prevent its use. */
    if (dynamic_macro_calc_crc(dst) != dst->checksum) {
        dprintf("dynamic macro: slot %d not loaded, checksum mismatch\n", macro_id);
        dst->length = 0;

        return;
    }

    dprintf("dynamic macro: slot %d loaded from eeprom, checksum okay\n", macro_id);
}

void dynamic_macro_save_eeprom(uint8_t macro_id) {
    dynamic_macro_t* src = &dynamic_macros[macro_id];

    eeprom_update_block(src, dynamic_macro_eeprom_macro_addr(macro_id), sizeof(dynamic_macro_t));
    dprintf("dynamic macro: slot %d saved to eeprom\n", macro_id);
}

void dynamic_macro_init(void) {
    /* zero out macro blocks  */
    memset(&dynamic_macros, 0, DYNAMIC_MACRO_COUNT * sizeof(dynamic_macro_t));
    dynamic_macro_load_eeprom_all();
}

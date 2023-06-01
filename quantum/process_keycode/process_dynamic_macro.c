/* Copyright 2016 Jack Humbert
 * Copyright 2019 Drashna Jael're (@drashna, aka Christopher Courtney)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* Author: Wojciech Siewierski < wojciech dot siewierski at onet dot pl > */
#include "process_dynamic_macro.h"

// default feedback method
void dynamic_macro_led_blink(void) {
#ifdef BACKLIGHT_ENABLE
    backlight_toggle();
    wait_ms(100);
    backlight_toggle();
#endif
}

/* User hooks for Dynamic Macros */

__attribute__((weak)) void dynamic_macro_record_start_user(int8_t direction) {
    dynamic_macro_led_blink();
}

__attribute__((weak)) void dynamic_macro_play_user(int8_t direction) {
    dynamic_macro_led_blink();
}

__attribute__((weak)) void dynamic_macro_record_key_user(int8_t direction, keyrecord_t *record) {
    dynamic_macro_led_blink();
}

__attribute__((weak)) void dynamic_macro_record_end_user(int8_t direction) {
    dynamic_macro_led_blink();
}

__attribute__((weak)) bool dynamic_macro_valid_key_user(uint16_t keycode, keyrecord_t *record) {
    return true;
}

/* Convenience macros used for retrieving the debug info. All of them
 * need a `direction` variable accessible at the call site.
 */
#define DYNAMIC_MACRO_CURRENT_SLOT() (direction > 0 ? 1 : 2)
#define DYNAMIC_MACRO_CURRENT_LENGTH(BEGIN, POINTER) ((int)(direction * ((POINTER) - (BEGIN))))
#define DYNAMIC_MACRO_CURRENT_CAPACITY(BEGIN, END2) ((int)(direction * ((END2) - (BEGIN)) + 1))

/**
 * Start recording of the dynamic macro.
 *
 * @param[out] macro_pointer The new macro buffer iterator.
 * @param[in]  macro_buffer  The macro buffer used to initialize macro_pointer.
 */
void dynamic_macro_record_start(keyrecord_t **macro_pointer, keyrecord_t *macro_buffer, int8_t direction) {
    dprintln("dynamic macro recording: started");

    dynamic_macro_record_start_user(direction);

    clear_keyboard();
    layer_clear();
    *macro_pointer = macro_buffer;
}

/**
 * Play the dynamic macro.
 *
 * @param macro_buffer[in] The beginning of the macro buffer being played.
 * @param macro_end[in]    The element after the last macro buffer element.
 * @param direction[in]    Either +1 or -1, which way to iterate the buffer.
 */
void dynamic_macro_play(keyrecord_t *macro_buffer, keyrecord_t *macro_end, int8_t direction) {
    dprintf("dynamic macro: slot %d playback\n", DYNAMIC_MACRO_CURRENT_SLOT());

    layer_state_t saved_layer_state = layer_state;

    clear_keyboard();
    layer_clear();

    while (macro_buffer != macro_end) {
        process_record(macro_buffer);
        macro_buffer += direction;
#ifdef DYNAMIC_MACRO_DELAY
        wait_ms(DYNAMIC_MACRO_DELAY);
#endif
    }

    clear_keyboard();

    layer_state_set(saved_layer_state);

    dynamic_macro_play_user(direction);
}

/**
 * Record a single key in a dynamic macro.
 *
 * @param macro_buffer[in] The start of the used macro buffer.
 * @param macro_pointer[in,out] The current buffer position.
 * @param macro2_end[in] The end of the other macro.
 * @param direction[in]  Either +1 or -1, which way to iterate the buffer.
 * @param record[in]     The current keypress.
 */
void dynamic_macro_record_key(keyrecord_t *macro_buffer, keyrecord_t **macro_pointer, keyrecord_t *macro2_end, int8_t direction, keyrecord_t *record) {
    /* If we've just started recording, ignore all the key releases. */
    if (!record->event.pressed && *macro_pointer == macro_buffer) {
        dprintln("dynamic macro: ignoring a leading key-up event");
        return;
    }

    /* The other end of the other macro is the last buffer element it
     * is safe to use before overwriting the other macro.
     */
    if (*macro_pointer - direction != macro2_end) {
        **macro_pointer = *record;
        *macro_pointer += direction;
    } else {
        dynamic_macro_record_key_user(direction, record);
    }

    dprintf("dynamic macro: slot %d length: %d/%d\n", DYNAMIC_MACRO_CURRENT_SLOT(), DYNAMIC_MACRO_CURRENT_LENGTH(macro_buffer, *macro_pointer), DYNAMIC_MACRO_CURRENT_CAPACITY(macro_buffer, macro2_end));
}

/**
 * End recording of the dynamic macro. Essentially just update the
 * pointer to the end of the macro.
 */
void dynamic_macro_record_end(keyrecord_t *macro_buffer, keyrecord_t *macro_pointer, int8_t direction, keyrecord_t **macro_end) {
    dynamic_macro_record_end_user(direction);

    /* Do not save the keys being held when stopping the recording,
     * i.e. the keys used to access the layer DM_RSTP is on.
     */
    while (macro_pointer != macro_buffer && (macro_pointer - direction)->event.pressed) {
        dprintln("dynamic macro: trimming a trailing key-down event");
        macro_pointer -= direction;
    }

    dprintf("dynamic macro: slot %d saved, length: %d\n", DYNAMIC_MACRO_CURRENT_SLOT(), DYNAMIC_MACRO_CURRENT_LENGTH(macro_buffer, macro_pointer));

    *macro_end = macro_pointer;
}

/* Handle the key events related to the dynamic macros. Should be
 * called from process_record_user() like this:
 *
 *   bool process_record_user(uint16_t keycode, keyrecord_t *record) {
 *       if (!process_record_dynamic_macro(keycode, record)) {
 *           return false;
 *       }
 *       <...THE REST OF THE FUNCTION...>
 *   }
 */
bool process_dynamic_macro(uint16_t keycode, keyrecord_t *record) {
    /* Both macros use the same buffer but read/write on different
     * ends of it.
     *
     * Macro1 is written left-to-right starting from the beginning of
     * the buffer.
     *
     * Macro2 is written right-to-left starting from the end of the
     * buffer.
     *
     * &macro_buffer   macro_end
     *  v                   v
     * +------------------------------------------------------------+
     * |>>>>>> MACRO1 >>>>>>      <<<<<<<<<<<<< MACRO2 <<<<<<<<<<<<<|
     * +------------------------------------------------------------+
     *                           ^                                 ^
     *                         r_macro_end                  r_macro_buffer
     *
     * During the recording when one macro encounters the end of the
     * other macro, the recording is stopped. Apart from this, there
     * are no arbitrary limits for the macros' length in relation to
     * each other: for example one can either have two medium sized
     * macros or one long macro and one short macro. Or even one empty
     * and one using the whole buffer.
     */
    static keyrecord_t macro_buffer[DYNAMIC_MACRO_SIZE];

    /* Pointer to the first buffer element after the first macro.
     * Initially points to the very beginning of the buffer since the
     * macro is empty. */
    static keyrecord_t *macro_end = macro_buffer;

    /* The other end of the macro buffer. Serves as the beginning of
     * the second macro. */
    static keyrecord_t *const r_macro_buffer = macro_buffer + DYNAMIC_MACRO_SIZE - 1;

    /* Like macro_end but for the second macro. */
    static keyrecord_t *r_macro_end = r_macro_buffer;

    /* A persistent pointer to the current macro position (iterator)
     * used during the recording. */
    static keyrecord_t *macro_pointer = NULL;

    /* 0   - no macro is being recorded right now
     * 1,2 - either macro 1 or 2 is being recorded */
    static uint8_t macro_id = 0;

    if (macro_id == 0) {
        /* No macro recording in progress. */
        if (!record->event.pressed) {
            switch (keycode) {
                case QK_DYNAMIC_MACRO_RECORD_START_1:
                    dynamic_macro_record_start(&macro_pointer, macro_buffer, +1);
                    macro_id = 1;
                    return false;
                case QK_DYNAMIC_MACRO_RECORD_START_2:
                    dynamic_macro_record_start(&macro_pointer, r_macro_buffer, -1);
                    macro_id = 2;
                    return false;
                case QK_DYNAMIC_MACRO_PLAY_1:
                    dynamic_macro_play(macro_buffer, macro_end, +1);
                    return false;
                case QK_DYNAMIC_MACRO_PLAY_2:
                    dynamic_macro_play(r_macro_buffer, r_macro_end, -1);
                    return false;
            }
        }
    } else {
        /* A macro is being recorded right now. */
        switch (keycode) {
            case QK_DYNAMIC_MACRO_RECORD_START_1:
            case QK_DYNAMIC_MACRO_RECORD_START_2:
            case QK_DYNAMIC_MACRO_RECORD_STOP:
                /* Stop the macro recording. */
                if (record->event.pressed ^ (keycode != QK_DYNAMIC_MACRO_RECORD_STOP)) { /* Ignore the initial release
                                                                                          * just after the recording
                                                                                          * starts for DM_RSTP. */
                    switch (macro_id) {
                        case 1:
                            dynamic_macro_record_end(macro_buffer, macro_pointer, +1, &macro_end);
                            break;
                        case 2:
                            dynamic_macro_record_end(r_macro_buffer, macro_pointer, -1, &r_macro_end);
                            break;
                    }
                    macro_id = 0;
                }
                return false;
#ifdef DYNAMIC_MACRO_NO_NESTING
            case QK_DYNAMIC_MACRO_PLAY_1:
            case QK_DYNAMIC_MACRO_PLAY_2:
                dprintln("dynamic macro: ignoring macro play key while recording");
                return false;
#endif
            default:
                if (dynamic_macro_valid_key_user(keycode, record)) {
                    /* Store the key in the macro buffer and process it normally. */
                    switch (macro_id) {
                        case 1:
                            dynamic_macro_record_key(macro_buffer, &macro_pointer, r_macro_end, +1, record);
                            break;
                        case 2:
                            dynamic_macro_record_key(r_macro_buffer, &macro_pointer, macro_end, -1, record);
                            break;
                    }
                }
                return true;
                break;
        }
    }

    return true;
}

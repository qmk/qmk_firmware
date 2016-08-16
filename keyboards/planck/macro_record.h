/* File: macro_record.h */
#pragma once

#include "action_layer.h"
#include <stdlib.h>

#define MACRO_SIZE 256

/* Macros */
enum {
    _REC_START1 = 240,
    _REC_KEY1,
    _REC_STOP1,
    _MACRO_PLAY1,

    _REC_START2,
    _REC_KEY2,
    _REC_STOP2,
    _MACRO_PLAY2,
};

/* Layers */
enum {
    _MACRO_RECORD_LAYER1 = NUM_LAYERS,
    _MACRO_RECORD_LAYER2,
};

void macro_record_start(
    keyrecord_t **macro_pointer,
    keyrecord_t *macro_buffer,
    uint8_t rec_layer,
    bool pressed)
{
    backlight_toggle();
    if (!pressed) {
        clear_keyboard();
        layer_clear();
        *macro_pointer = macro_buffer;
        layer_on(rec_layer);
    }
}

void macro_play(
    keyrecord_t **macro_pointer,
    keyrecord_t *macro_buffer,
    keyrecord_t *macro_end,
    signed int direction,
    bool pressed)
{
    backlight_toggle();
    if (!pressed) {
        uint32_t saved_layer_state = layer_state;

        clear_keyboard();
        layer_clear();

        *macro_pointer = macro_buffer;
        while (*macro_pointer != macro_end) {
            process_record(*macro_pointer);
            *macro_pointer += direction;
        }

        clear_keyboard();

        layer_state = saved_layer_state;
    }
}

void macro_record_key(
    keyrecord_t **macro_pointer,
    keyrecord_t *macro_buffer,
    keyrecord_t *macro_end,
    keyrecord_t *macro_end2,
    uint8_t rec_layer,
    signed int direction,
    keyrecord_t *record)
{
    if (labs(*macro_pointer - macro_buffer) < MACRO_SIZE &&
        *macro_pointer != macro_end2+direction) {

        **macro_pointer = *record;
        *macro_pointer += direction;

        layer_off(rec_layer);
        process_record_nocache(record);
        layer_on(rec_layer);
    } else {
        backlight_toggle(); /* Notify about the end of buffer. */
    }
}

void macro_record_end(
    keyrecord_t *macro_pointer,
    keyrecord_t *macro_buffer,
    keyrecord_t **macro_end,
    bool pressed,
    uint8_t rec_layer)
{
    bool macro_is_empty = (macro_pointer == macro_buffer);

    if (!macro_is_empty) {
        backlight_toggle(); /* Notify about the end of recording. */
    }

    if ((!macro_is_empty && !pressed) ||
        (macro_is_empty && pressed)) {

        *macro_end = macro_pointer;
        layer_off(rec_layer);
    }
}

#define MACRO_RECORD_KEYMAPS \
    [_MACRO_RECORD_LAYER1] = { \
        {M(_REC_KEY1), M(_REC_KEY1),  M(_REC_KEY1), M(_REC_KEY1), M(_REC_KEY1), M(_REC_KEY1), M(_REC_KEY1), M(_REC_KEY1), M(_REC_KEY1), M(_REC_KEY1), M(_REC_KEY1), M(_REC_KEY1)}, \
        {M(_REC_KEY1), M(_REC_KEY1),  M(_REC_KEY1), M(_REC_KEY1), M(_REC_KEY1), M(_REC_KEY1), M(_REC_KEY1), M(_REC_KEY1), M(_REC_KEY1), M(_REC_KEY1), M(_REC_KEY1), M(_REC_KEY1)}, \
        {M(_REC_KEY1), M(_REC_KEY1),  M(_REC_KEY1), M(_REC_KEY1), M(_REC_KEY1), M(_REC_KEY1), M(_REC_KEY1), M(_REC_KEY1), M(_REC_KEY1), M(_REC_KEY1), M(_REC_KEY1), M(_REC_KEY1)}, \
        {M(_REC_KEY1), M(_REC_STOP1), M(_REC_KEY1), M(_REC_KEY1), M(_REC_KEY1), M(_REC_KEY1), M(_REC_KEY1), M(_REC_KEY1), M(_REC_KEY1), M(_REC_KEY1), M(_REC_KEY1), M(_REC_KEY1)}  \
    }, \
    [_MACRO_RECORD_LAYER2] = { \
        {M(_REC_KEY2), M(_REC_KEY2),  M(_REC_KEY2), M(_REC_KEY2), M(_REC_KEY2), M(_REC_KEY2), M(_REC_KEY2), M(_REC_KEY2), M(_REC_KEY2), M(_REC_KEY2), M(_REC_KEY2), M(_REC_KEY2)}, \
        {M(_REC_KEY2), M(_REC_KEY2),  M(_REC_KEY2), M(_REC_KEY2), M(_REC_KEY2), M(_REC_KEY2), M(_REC_KEY2), M(_REC_KEY2), M(_REC_KEY2), M(_REC_KEY2), M(_REC_KEY2), M(_REC_KEY2)}, \
        {M(_REC_KEY2), M(_REC_KEY2),  M(_REC_KEY2), M(_REC_KEY2), M(_REC_KEY2), M(_REC_KEY2), M(_REC_KEY2), M(_REC_KEY2), M(_REC_KEY2), M(_REC_KEY2), M(_REC_KEY2), M(_REC_KEY2)}, \
        {M(_REC_KEY2), M(_REC_STOP2), M(_REC_KEY2), M(_REC_KEY2), M(_REC_KEY2), M(_REC_KEY2), M(_REC_KEY2), M(_REC_KEY2), M(_REC_KEY2), M(_REC_KEY2), M(_REC_KEY2), M(_REC_KEY2)}  \
    }

bool macro_record_macro_handler(keyrecord_t *record, uint8_t id)
{
    static keyrecord_t macro_buffer[MACRO_SIZE];
    static keyrecord_t *macro_end = macro_buffer;
    static keyrecord_t *const r_macro_buffer = macro_buffer + MACRO_SIZE - 1;
    static keyrecord_t *r_macro_end = r_macro_buffer;
    static keyrecord_t *macro_pointer = NULL;

    switch (id) {
    case _REC_START1:
        macro_record_start(&macro_pointer, macro_buffer, _MACRO_RECORD_LAYER1, record->event.pressed);
        break;
    case _REC_START2:
        macro_record_start(&macro_pointer, r_macro_buffer, _MACRO_RECORD_LAYER2, record->event.pressed);
        break;
    case _MACRO_PLAY1:
        macro_play(&macro_pointer, macro_buffer, macro_end, +1, record->event.pressed);
        break;
    case _MACRO_PLAY2:
        macro_play(&macro_pointer, r_macro_buffer, r_macro_end, -1, record->event.pressed);
        break;
    case _REC_KEY1:
        macro_record_key(&macro_pointer, macro_buffer, macro_end, r_macro_end, _MACRO_RECORD_LAYER1, +1, record);
        break;
    case _REC_KEY2:
        macro_record_key(&macro_pointer, r_macro_buffer, r_macro_end, macro_end, _MACRO_RECORD_LAYER2, -1, record);
        break;
    case _REC_STOP1:
        macro_record_end(macro_pointer, macro_buffer, &macro_end, record->event.pressed, _MACRO_RECORD_LAYER1);
        break;
    case _REC_STOP2:
        macro_record_end(macro_pointer, r_macro_buffer, &r_macro_end, record->event.pressed, _MACRO_RECORD_LAYER2);
        break;
    default:
        return false;
    }
    return true;
}

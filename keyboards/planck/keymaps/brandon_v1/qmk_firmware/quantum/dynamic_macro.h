/* Author: Wojciech Siewierski < wojciech dot siewierski at onet dot pl > */
#ifndef DYNAMIC_MACROS_H
#define DYNAMIC_MACROS_H

#include "action_layer.h"

#ifndef DYNAMIC_MACRO_SIZE
/* May be overridden with a custom value. Be aware that the effective
 * macro length is half of this value: each keypress is recorded twice
 * because of the down-event and up-event. This is not a bug, it's the
 * intended behavior.
 *
 * Usually it should be fine to set the macro size to at least 256 but
 * there have been reports of it being too much in some users' cases,
 * so 128 is considered a safe default.
 */
#define DYNAMIC_MACRO_SIZE 128
#endif

/* DYNAMIC_MACRO_RANGE must be set as the last element of user's
 * "planck_keycodes" enum prior to including this header. This allows
 * us to 'extend' it.
 */
enum dynamic_macro_keycodes {
    DYN_REC_START1 = DYNAMIC_MACRO_RANGE,
    DYN_REC_START2,
    DYN_MACRO_PLAY1,
    DYN_MACRO_PLAY2,
};

/* Blink the LEDs to notify the user about some event. */
void dynamic_macro_led_blink(void)
{
    backlight_toggle();
    _delay_ms(100);
    backlight_toggle();
}

/**
 * Start recording of the dynamic macro.
 *
 * @param[out] macro_pointer The new macro buffer iterator.
 * @param[in]  macro_buffer  The macro buffer used to initialize macro_pointer.
 */
void dynamic_macro_record_start(
    keyrecord_t **macro_pointer, keyrecord_t *macro_buffer)
{
    dynamic_macro_led_blink();

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
void dynamic_macro_play(
    keyrecord_t *macro_buffer, keyrecord_t *macro_end, int8_t direction)
{
    uint32_t saved_layer_state = layer_state;

    clear_keyboard();
    layer_clear();

    while (macro_buffer != macro_end) {
        process_record(macro_buffer);
        macro_buffer += direction;
    }

    clear_keyboard();

    layer_state = saved_layer_state;
}

/**
 * Record a single key in a dynamic macro.
 *
 * @param macro_pointer[in,out] The current buffer position.
 * @param macro_end2[in] The end of the other macro which shouldn't be overwritten.
 * @param direction[in]  Either +1 or -1, which way to iterate the buffer.
 * @param record[in]     The current keypress.
 */
void dynamic_macro_record_key(
    keyrecord_t **macro_pointer,
    keyrecord_t *macro_end2,
    int8_t direction,
    keyrecord_t *record)
{
    if (*macro_pointer + direction != macro_end2) {
        **macro_pointer = *record;
        *macro_pointer += direction;
    } else {
        /* Notify about the end of buffer. The blinks are paired
         * because they should happen on both down and up events. */
        backlight_toggle();
    }
}

/**
 * End recording of the dynamic macro. Essentially just update the
 * pointer to the end of the macro.
 */
void dynamic_macro_record_end(keyrecord_t *macro_pointer, keyrecord_t **macro_end)
{
    dynamic_macro_led_blink();

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
bool process_record_dynamic_macro(uint16_t keycode, keyrecord_t *record)
{
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
     * |>>>>>> MACRO1 >>>>>>|    |<<<<<<<<<<<<< MACRO2 <<<<<<<<<<<<<|
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
            case DYN_REC_START1:
                dynamic_macro_record_start(&macro_pointer, macro_buffer);
                macro_id = 1;
                return false;
            case DYN_REC_START2:
                dynamic_macro_record_start(&macro_pointer, r_macro_buffer);
                macro_id = 2;
                return false;
            case DYN_MACRO_PLAY1:
                dynamic_macro_play(macro_buffer, macro_end, +1);
                return false;
            case DYN_MACRO_PLAY2:
                dynamic_macro_play(r_macro_buffer, r_macro_end, -1);
                return false;
            }
        }
    } else {
        /* A macro is being recorded right now. */
        switch (keycode) {
        case MO(_DYN):
            /* Use the layer key used to access the macro recording as
             * a stop button. */
            if (record->event.pressed) { /* Ignore the initial release
                                          * just after the recoding
                                          * starts. */
                switch (macro_id) {
                case 1:
                    dynamic_macro_record_end(macro_pointer, &macro_end);
                    break;
                case 2:
                    dynamic_macro_record_end(macro_pointer, &r_macro_end);
                    break;
                }
                macro_id = 0;
            }
            return false;
        default:
            /* Store the key in the macro buffer and process it normally. */
            switch (macro_id) {
            case 1:
                dynamic_macro_record_key(&macro_pointer, r_macro_end, +1, record);
                break;
            case 2:
                dynamic_macro_record_key(&macro_pointer, macro_end, -1, record);
                break;
            }
            return true;
            break;
        }
    }

    return true;
}

#endif

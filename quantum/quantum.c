/* Copyright 2016-2017 Jack Humbert
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

#include "quantum.h"
#include "magic.h"

#ifdef BLUETOOTH_ENABLE
#    include "outputselect.h"
#endif

#ifdef BACKLIGHT_ENABLE
#    include "backlight.h"
#endif

#ifdef API_ENABLE
#    include "api.h"
#endif

#ifdef MIDI_ENABLE
#    include "process_midi.h"
#endif

#ifdef VELOCIKEY_ENABLE
#    include "velocikey.h"
#endif

#ifdef HAPTIC_ENABLE
#    include "haptic.h"
#endif

#ifdef AUDIO_ENABLE
#    ifndef GOODBYE_SONG
#        define GOODBYE_SONG SONG(GOODBYE_SOUND)
#    endif
float goodbye_song[][2] = GOODBYE_SONG;
#    ifdef DEFAULT_LAYER_SONGS
float default_layer_songs[][16][2] = DEFAULT_LAYER_SONGS;
#    endif
#endif

__attribute__((weak)) bool process_action_kb(keyrecord_t *record) { return true; }

__attribute__((weak)) bool process_record_kb(uint16_t keycode, keyrecord_t *record) { return process_record_user(keycode, record); }

__attribute__((weak)) bool process_record_user(uint16_t keycode, keyrecord_t *record) { return true; }

__attribute__((weak)) void post_process_record_kb(uint16_t keycode, keyrecord_t *record) { post_process_record_user(keycode, record); }

__attribute__((weak)) void post_process_record_user(uint16_t keycode, keyrecord_t *record) {}

void reset_keyboard(void) {
    clear_keyboard();
#if defined(MIDI_ENABLE) && defined(MIDI_BASIC)
    process_midi_all_notes_off();
#endif
#ifdef AUDIO_ENABLE
#    ifndef NO_MUSIC_MODE
    music_all_notes_off();
#    endif
    uint16_t timer_start = timer_read();
    PLAY_SONG(goodbye_song);
    shutdown_user();
    while (timer_elapsed(timer_start) < 250) wait_ms(1);
    stop_all_notes();
#else
    shutdown_user();
    wait_ms(250);
#endif
#ifdef HAPTIC_ENABLE
    haptic_shutdown();
#endif
    bootloader_jump();
}

/* Get keycode, and then process pre tapping functionality */
bool pre_process_record_quantum(keyrecord_t *record) {
    if (!(
#ifdef COMBO_ENABLE
        process_combo(get_record_keycode(record, true), record) &&
#endif
        true)) {
        return false;
    }
    return true; // continue processing
}

/* Get keycode, and then call keyboard function */
void post_process_record_quantum(keyrecord_t *record) {
    uint16_t keycode = get_record_keycode(record, false);
    post_process_record_kb(keycode, record);
}

/* Core keycode function, hands off handling to other functions,
    then processes internal quantum keycodes, and then processes
    ACTIONs.                                                      */
bool process_record_quantum(keyrecord_t *record) {
    uint16_t keycode = get_record_keycode(record, true);

    // This is how you use actions here
    // if (keycode == KC_LEAD) {
    //   action_t action;
    //   action.code = ACTION_DEFAULT_LAYER_SET(0);
    //   process_action(record, action);
    //   return false;
    // }

#ifdef VELOCIKEY_ENABLE
    if (velocikey_enabled() && record->event.pressed) {
        velocikey_accelerate();
    }
#endif

#ifdef WPM_ENABLE
    if (record->event.pressed) {
        update_wpm(keycode);
    }
#endif

#ifdef TAP_DANCE_ENABLE
    preprocess_tap_dance(keycode, record);
#endif

    if (!(
#if defined(KEY_LOCK_ENABLE)
            // Must run first to be able to mask key_up events.
            process_key_lock(&keycode, record) &&
#endif
#if defined(DYNAMIC_MACRO_ENABLE) && !defined(DYNAMIC_MACRO_USER_CALL)
            // Must run asap to ensure all keypresses are recorded.
            process_dynamic_macro(keycode, record) &&
#endif
#if defined(AUDIO_ENABLE) && defined(AUDIO_CLICKY)
            process_clicky(keycode, record) &&
#endif
#ifdef HAPTIC_ENABLE
            process_haptic(keycode, record) &&
#endif
#if defined(VIA_ENABLE)
            process_record_via(keycode, record) &&
#endif
            process_record_kb(keycode, record) &&
#if defined(SEQUENCER_ENABLE)
            process_sequencer(keycode, record) &&
#endif
#if defined(MIDI_ENABLE) && defined(MIDI_ADVANCED)
            process_midi(keycode, record) &&
#endif
#ifdef AUDIO_ENABLE
            process_audio(keycode, record) &&
#endif
#if defined(BACKLIGHT_ENABLE) || defined(LED_MATRIX_ENABLE)
            process_backlight(keycode, record) &&
#endif
#ifdef STENO_ENABLE
            process_steno(keycode, record) &&
#endif
#if (defined(AUDIO_ENABLE) || (defined(MIDI_ENABLE) && defined(MIDI_BASIC))) && !defined(NO_MUSIC_MODE)
            process_music(keycode, record) &&
#endif
#ifdef KEY_OVERRIDE_ENABLE
            process_key_override(keycode, record) &&
#endif
#ifdef TAP_DANCE_ENABLE
            process_tap_dance(keycode, record) &&
#endif
#if defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE) || defined(UCIS_ENABLE)
            process_unicode_common(keycode, record) &&
#endif
#ifdef LEADER_ENABLE
            process_leader(keycode, record) &&
#endif
#ifdef PRINTING_ENABLE
            process_printer(keycode, record) &&
#endif
#ifdef AUTO_SHIFT_ENABLE
            process_auto_shift(keycode, record) &&
#endif
#ifdef TERMINAL_ENABLE
            process_terminal(keycode, record) &&
#endif
#ifdef SPACE_CADET_ENABLE
            process_space_cadet(keycode, record) &&
#endif
#ifdef MAGIC_KEYCODE_ENABLE
            process_magic(keycode, record) &&
#endif
#ifdef GRAVE_ESC_ENABLE
            process_grave_esc(keycode, record) &&
#endif
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
            process_rgb(keycode, record) &&
#endif
#ifdef JOYSTICK_ENABLE
            process_joystick(keycode, record) &&
#endif
            true)) {
        return false;
    }

    if (record->event.pressed) {
        switch (keycode) {
#ifndef NO_RESET
            case RESET:
                reset_keyboard();
                return false;
#endif
#ifndef NO_DEBUG
            case DEBUG:
                debug_enable ^= 1;
                if (debug_enable) {
                    print("DEBUG: enabled.\n");
                } else {
                    print("DEBUG: disabled.\n");
                }
#endif
                return false;
            case EEPROM_RESET:
                eeconfig_init();
                return false;
#ifdef VELOCIKEY_ENABLE
            case VLK_TOG:
                velocikey_toggle();
                return false;
#endif
#ifdef BLUETOOTH_ENABLE
            case OUT_AUTO:
                set_output(OUTPUT_AUTO);
                return false;
            case OUT_USB:
                set_output(OUTPUT_USB);
                return false;
            case OUT_BT:
                set_output(OUTPUT_BLUETOOTH);
                return false;
#endif
#ifndef NO_ACTION_ONESHOT
            case ONESHOT_TOGGLE:
                oneshot_toggle();
                break;
            case ONESHOT_ENABLE:
                oneshot_enable();
                break;
            case ONESHOT_DISABLE:
                oneshot_disable();
                break;
#endif
        }
    }

    return process_action_kb(record);
}

void set_single_persistent_default_layer(uint8_t default_layer) {
#if defined(AUDIO_ENABLE) && defined(DEFAULT_LAYER_SONGS)
    PLAY_SONG(default_layer_songs[default_layer]);
#endif
    eeconfig_update_default_layer((layer_state_t)1 << default_layer);
    default_layer_set((layer_state_t)1 << default_layer);
}

layer_state_t update_tri_layer_state(layer_state_t state, uint8_t layer1, uint8_t layer2, uint8_t layer3) {
    layer_state_t mask12 = ((layer_state_t)1 << layer1) | ((layer_state_t)1 << layer2);
    layer_state_t mask3  = (layer_state_t)1 << layer3;
    return (state & mask12) == mask12 ? (state | mask3) : (state & ~mask3);
}

void update_tri_layer(uint8_t layer1, uint8_t layer2, uint8_t layer3) { layer_state_set(update_tri_layer_state(layer_state, layer1, layer2, layer3)); }

void matrix_init_quantum() {
    magic();
    led_init_ports();
#ifdef BACKLIGHT_ENABLE
    backlight_init_ports();
#endif
#ifdef AUDIO_ENABLE
    audio_init();
#endif
#ifdef LED_MATRIX_ENABLE
    led_matrix_init();
#endif
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_init();
#endif
#if defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE) || defined(UCIS_ENABLE)
    unicode_input_mode_init();
#endif
#ifdef HAPTIC_ENABLE
    haptic_init();
#endif
#if defined(BLUETOOTH_ENABLE) && defined(OUTPUT_AUTO_ENABLE)
    set_output(OUTPUT_AUTO);
#endif

    matrix_init_kb();
}

void matrix_scan_quantum() {
#if defined(AUDIO_ENABLE) && defined(AUDIO_INIT_DELAY)
    // There are some tasks that need to be run a little bit
    // after keyboard startup, or else they will not work correctly
    // because of interaction with the USB device state, which
    // may still be in flux...
    //
    // At the moment the only feature that needs this is the
    // startup song.
    static bool     delayed_tasks_run  = false;
    static uint16_t delayed_task_timer = 0;
    if (!delayed_tasks_run) {
        if (!delayed_task_timer) {
            delayed_task_timer = timer_read();
        } else if (timer_elapsed(delayed_task_timer) > 300) {
            audio_startup();
            delayed_tasks_run = true;
        }
    }
#endif

#if defined(AUDIO_ENABLE) && !defined(NO_MUSIC_MODE)
    music_task();
#endif

#ifdef KEY_OVERRIDE_ENABLE
    key_override_task();
#endif

#ifdef SEQUENCER_ENABLE
    sequencer_task();
#endif

#ifdef TAP_DANCE_ENABLE
    tap_dance_task();
#endif

#ifdef COMBO_ENABLE
    combo_task();
#endif

#ifdef LED_MATRIX_ENABLE
    led_matrix_task();
#endif

#ifdef WPM_ENABLE
    decay_wpm();
#endif

#ifdef HAPTIC_ENABLE
    haptic_task();
#endif

#ifdef DIP_SWITCH_ENABLE
    dip_switch_read(false);
#endif

#ifdef AUTO_SHIFT_ENABLE
    autoshift_matrix_scan();
#endif

    matrix_scan_kb();
}

#ifdef HD44780_ENABLED
#    include "hd44780.h"
#endif

void api_send_unicode(uint32_t unicode) {
#ifdef API_ENABLE
    uint8_t chunk[4];
    dword_to_bytes(unicode, chunk);
    MT_SEND_DATA(DT_UNICODE, chunk, 5);
#endif
}

//------------------------------------------------------------------------------
// Override these functions in your keymap file to play different tunes on
// different events such as startup and bootloader jump

__attribute__((weak)) void startup_user() {}

__attribute__((weak)) void shutdown_user() {}

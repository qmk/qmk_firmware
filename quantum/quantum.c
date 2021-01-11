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

#if !defined(RGBLIGHT_ENABLE) && !defined(RGB_MATRIX_ENABLE)
#    include "rgb.h"
#endif

#ifdef PROTOCOL_LUFA
#    include "outputselect.h"
#endif

#ifndef BREATHING_PERIOD
#    define BREATHING_PERIOD 6
#endif

#include "backlight.h"
extern backlight_config_t backlight_config;

#ifdef FAUXCLICKY_ENABLE
#    include "fauxclicky.h"
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

#ifdef ENCODER_ENABLE
#    include "encoder.h"
#endif

#ifdef AUDIO_ENABLE
#    ifndef GOODBYE_SONG
#        define GOODBYE_SONG SONG(GOODBYE_SOUND)
#    endif
#    ifndef AG_NORM_SONG
#        define AG_NORM_SONG SONG(AG_NORM_SOUND)
#    endif
#    ifndef AG_SWAP_SONG
#        define AG_SWAP_SONG SONG(AG_SWAP_SOUND)
#    endif
#    ifndef CG_NORM_SONG
#        define CG_NORM_SONG SONG(AG_NORM_SOUND)
#    endif
#    ifndef CG_SWAP_SONG
#        define CG_SWAP_SONG SONG(AG_SWAP_SOUND)
#    endif
float goodbye_song[][2] = GOODBYE_SONG;
float ag_norm_song[][2] = AG_NORM_SONG;
float ag_swap_song[][2] = AG_SWAP_SONG;
float cg_norm_song[][2] = CG_NORM_SONG;
float cg_swap_song[][2] = CG_SWAP_SONG;
#    ifdef DEFAULT_LAYER_SONGS
float default_layer_songs[][16][2] = DEFAULT_LAYER_SONGS;
#    endif
#endif

static void do_code16(uint16_t code, void (*f)(uint8_t)) {
    switch (code) {
        case QK_MODS ... QK_MODS_MAX:
            break;
        default:
            return;
    }

    if (code & QK_LCTL) f(KC_LCTL);
    if (code & QK_LSFT) f(KC_LSFT);
    if (code & QK_LALT) f(KC_LALT);
    if (code & QK_LGUI) f(KC_LGUI);

    if (code < QK_RMODS_MIN) return;

    if (code & QK_RCTL) f(KC_RCTL);
    if (code & QK_RSFT) f(KC_RSFT);
    if (code & QK_RALT) f(KC_RALT);
    if (code & QK_RGUI) f(KC_RGUI);
}

static inline void qk_register_weak_mods(uint8_t kc) {
    add_weak_mods(MOD_BIT(kc));
    send_keyboard_report();
}

static inline void qk_unregister_weak_mods(uint8_t kc) {
    del_weak_mods(MOD_BIT(kc));
    send_keyboard_report();
}

static inline void qk_register_mods(uint8_t kc) {
    add_weak_mods(MOD_BIT(kc));
    send_keyboard_report();
}

static inline void qk_unregister_mods(uint8_t kc) {
    del_weak_mods(MOD_BIT(kc));
    send_keyboard_report();
}

void register_code16(uint16_t code) {
    if (IS_MOD(code) || code == KC_NO) {
        do_code16(code, qk_register_mods);
    } else {
        do_code16(code, qk_register_weak_mods);
    }
    register_code(code);
}

void unregister_code16(uint16_t code) {
    unregister_code(code);
    if (IS_MOD(code) || code == KC_NO) {
        do_code16(code, qk_unregister_mods);
    } else {
        do_code16(code, qk_unregister_weak_mods);
    }
}

void tap_code16(uint16_t code) {
    register_code16(code);
#if TAP_CODE_DELAY > 0
    wait_ms(TAP_CODE_DELAY);
#endif
    unregister_code16(code);
}

__attribute__((weak)) bool process_action_kb(keyrecord_t *record) { return true; }

__attribute__((weak)) bool process_record_kb(uint16_t keycode, keyrecord_t *record) { return process_record_user(keycode, record); }

__attribute__((weak)) bool process_record_user(uint16_t keycode, keyrecord_t *record) { return true; }

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
// this is also done later in bootloader.c - not sure if it's neccesary here
#ifdef BOOTLOADER_CATERINA
    *(uint16_t *)0x0800 = 0x7777;  // these two are a-star-specific
#endif
    bootloader_jump();
}

/* true if the last press of GRAVE_ESC was shifted (i.e. GUI or SHIFT were pressed), false otherwise.
 * Used to ensure that the correct keycode is released if the key is released.
 */
static bool grave_esc_was_shifted = false;

/* Convert record into usable keycode via the contained event. */
uint16_t get_record_keycode(keyrecord_t *record) { return get_event_keycode(record->event); }

/* Convert event into usable keycode. Checks the layer cache to ensure that it
 * retains the correct keycode after a layer change, if the key is still pressed.
 */
uint16_t get_event_keycode(keyevent_t event) {
#if !defined(NO_ACTION_LAYER) && !defined(STRICT_LAYER_RELEASE)
    /* TODO: Use store_or_get_action() or a similar function. */
    if (!disable_action_cache) {
        uint8_t layer;

        if (event.pressed) {
            layer = layer_switch_get_layer(event.key);
            update_source_layers_cache(event.key, layer);
        } else {
            layer = read_source_layers_cache(event.key);
        }
        return keymap_key_to_keycode(layer, event.key);
    } else
#endif
        return keymap_key_to_keycode(layer_switch_get_layer(event.key), event.key);
}

/* Main keycode processing function. Hands off handling to other functions,
 * then processes internal Quantum keycodes, then processes ACTIONs.
 */
bool process_record_quantum(keyrecord_t *record) {
    uint16_t keycode = get_record_keycode(record);

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

#ifdef TAP_DANCE_ENABLE
    preprocess_tap_dance(keycode, record);
#endif

    if (!(
#if defined(KEY_LOCK_ENABLE)
            // Must run first to be able to mask key_up events.
            process_key_lock(&keycode, record) &&
#endif
#if defined(AUDIO_ENABLE) && defined(AUDIO_CLICKY)
            process_clicky(keycode, record) &&
#endif  // AUDIO_CLICKY
#ifdef HAPTIC_ENABLE
            process_haptic(keycode, record) &&
#endif  // HAPTIC_ENABLE
#if defined(RGB_MATRIX_ENABLE)
            process_rgb_matrix(keycode, record) &&
#endif
            process_record_kb(keycode, record) &&
#if defined(MIDI_ENABLE) && defined(MIDI_ADVANCED)
            process_midi(keycode, record) &&
#endif
#ifdef AUDIO_ENABLE
            process_audio(keycode, record) &&
#endif
#ifdef STENO_ENABLE
            process_steno(keycode, record) &&
#endif
#if (defined(AUDIO_ENABLE) || (defined(MIDI_ENABLE) && defined(MIDI_BASIC))) && !defined(NO_MUSIC_MODE)
            process_music(keycode, record) &&
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
#ifdef COMBO_ENABLE
            process_combo(keycode, record) &&
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
            true)) {
        return false;
    }

    // Shift / paren setup

    switch (keycode) {
        case RESET:
            if (record->event.pressed) {
                reset_keyboard();
            }
            return false;
        case DEBUG:
            if (record->event.pressed) {
                debug_enable ^= 1;
                if (debug_enable) {
                    print("DEBUG: enabled.\n");
                } else {
                    print("DEBUG: disabled.\n");
                }
            }
            return false;
        case EEPROM_RESET:
            if (record->event.pressed) {
                eeconfig_init();
            }
            return false;
#ifdef FAUXCLICKY_ENABLE
        case FC_TOG:
            if (record->event.pressed) {
                FAUXCLICKY_TOGGLE;
            }
            return false;
        case FC_ON:
            if (record->event.pressed) {
                FAUXCLICKY_ON;
            }
            return false;
        case FC_OFF:
            if (record->event.pressed) {
                FAUXCLICKY_OFF;
            }
            return false;
#endif
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
        case RGB_TOG:
// Split keyboards need to trigger on key-up for edge-case issue
#    ifndef SPLIT_KEYBOARD
            if (record->event.pressed) {
#    else
            if (!record->event.pressed) {
#    endif
                rgblight_toggle();
            }
            return false;
        case RGB_MODE_FORWARD:
            if (record->event.pressed) {
                uint8_t shifted = get_mods() & (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT));
                if (shifted) {
                    rgblight_step_reverse();
                } else {
                    rgblight_step();
                }
            }
            return false;
        case RGB_MODE_REVERSE:
            if (record->event.pressed) {
                uint8_t shifted = get_mods() & (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT));
                if (shifted) {
                    rgblight_step();
                } else {
                    rgblight_step_reverse();
                }
            }
            return false;
        case RGB_HUI:
// Split keyboards need to trigger on key-up for edge-case issue
#    ifndef SPLIT_KEYBOARD
            if (record->event.pressed) {
#    else
            if (!record->event.pressed) {
#    endif
                rgblight_increase_hue();
            }
            return false;
        case RGB_HUD:
// Split keyboards need to trigger on key-up for edge-case issue
#    ifndef SPLIT_KEYBOARD
            if (record->event.pressed) {
#    else
            if (!record->event.pressed) {
#    endif
                rgblight_decrease_hue();
            }
            return false;
        case RGB_SAI:
// Split keyboards need to trigger on key-up for edge-case issue
#    ifndef SPLIT_KEYBOARD
            if (record->event.pressed) {
#    else
            if (!record->event.pressed) {
#    endif
                rgblight_increase_sat();
            }
            return false;
        case RGB_SAD:
// Split keyboards need to trigger on key-up for edge-case issue
#    ifndef SPLIT_KEYBOARD
            if (record->event.pressed) {
#    else
            if (!record->event.pressed) {
#    endif
                rgblight_decrease_sat();
            }
            return false;
        case RGB_VAI:
// Split keyboards need to trigger on key-up for edge-case issue
#    ifndef SPLIT_KEYBOARD
            if (record->event.pressed) {
#    else
            if (!record->event.pressed) {
#    endif
                rgblight_increase_val();
            }
            return false;
        case RGB_VAD:
// Split keyboards need to trigger on key-up for edge-case issue
#    ifndef SPLIT_KEYBOARD
            if (record->event.pressed) {
#    else
            if (!record->event.pressed) {
#    endif
                rgblight_decrease_val();
            }
            return false;
        case RGB_SPI:
            if (record->event.pressed) {
                rgblight_increase_speed();
            }
            return false;
        case RGB_SPD:
            if (record->event.pressed) {
                rgblight_decrease_speed();
            }
            return false;
        case RGB_MODE_PLAIN:
            if (record->event.pressed) {
                rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
            }
            return false;
        case RGB_MODE_BREATHE:
#    ifdef RGBLIGHT_EFFECT_BREATHING
            if (record->event.pressed) {
                if ((RGBLIGHT_MODE_BREATHING <= rgblight_get_mode()) && (rgblight_get_mode() < RGBLIGHT_MODE_BREATHING_end)) {
                    rgblight_step();
                } else {
                    rgblight_mode(RGBLIGHT_MODE_BREATHING);
                }
            }
#    endif
            return false;
        case RGB_MODE_RAINBOW:
#    ifdef RGBLIGHT_EFFECT_RAINBOW_MOOD
            if (record->event.pressed) {
                if ((RGBLIGHT_MODE_RAINBOW_MOOD <= rgblight_get_mode()) && (rgblight_get_mode() < RGBLIGHT_MODE_RAINBOW_MOOD_end)) {
                    rgblight_step();
                } else {
                    rgblight_mode(RGBLIGHT_MODE_RAINBOW_MOOD);
                }
            }
#    endif
            return false;
        case RGB_MODE_SWIRL:
#    ifdef RGBLIGHT_EFFECT_RAINBOW_SWIRL
            if (record->event.pressed) {
                if ((RGBLIGHT_MODE_RAINBOW_SWIRL <= rgblight_get_mode()) && (rgblight_get_mode() < RGBLIGHT_MODE_RAINBOW_SWIRL_end)) {
                    rgblight_step();
                } else {
                    rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL);
                }
            }
#    endif
            return false;
        case RGB_MODE_SNAKE:
#    ifdef RGBLIGHT_EFFECT_SNAKE
            if (record->event.pressed) {
                if ((RGBLIGHT_MODE_SNAKE <= rgblight_get_mode()) && (rgblight_get_mode() < RGBLIGHT_MODE_SNAKE_end)) {
                    rgblight_step();
                } else {
                    rgblight_mode(RGBLIGHT_MODE_SNAKE);
                }
            }
#    endif
            return false;
        case RGB_MODE_KNIGHT:
#    ifdef RGBLIGHT_EFFECT_KNIGHT
            if (record->event.pressed) {
                if ((RGBLIGHT_MODE_KNIGHT <= rgblight_get_mode()) && (rgblight_get_mode() < RGBLIGHT_MODE_KNIGHT_end)) {
                    rgblight_step();
                } else {
                    rgblight_mode(RGBLIGHT_MODE_KNIGHT);
                }
            }
#    endif
            return false;
        case RGB_MODE_XMAS:
#    ifdef RGBLIGHT_EFFECT_CHRISTMAS
            if (record->event.pressed) {
                rgblight_mode(RGBLIGHT_MODE_CHRISTMAS);
            }
#    endif
            return false;
        case RGB_MODE_GRADIENT:
#    ifdef RGBLIGHT_EFFECT_STATIC_GRADIENT
            if (record->event.pressed) {
                if ((RGBLIGHT_MODE_STATIC_GRADIENT <= rgblight_get_mode()) && (rgblight_get_mode() < RGBLIGHT_MODE_STATIC_GRADIENT_end)) {
                    rgblight_step();
                } else {
                    rgblight_mode(RGBLIGHT_MODE_STATIC_GRADIENT);
                }
            }
#    endif
            return false;
        case RGB_MODE_RGBTEST:
#    ifdef RGBLIGHT_EFFECT_RGB_TEST
            if (record->event.pressed) {
                rgblight_mode(RGBLIGHT_MODE_RGB_TEST);
            }
#    endif
            return false;
#endif  // defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
#ifdef VELOCIKEY_ENABLE
        case VLK_TOG:
            if (record->event.pressed) {
                velocikey_toggle();
            }
            return false;
#endif
#ifdef PROTOCOL_LUFA
        case OUT_AUTO:
            if (record->event.pressed) {
                set_output(OUTPUT_AUTO);
            }
            return false;
        case OUT_USB:
            if (record->event.pressed) {
                set_output(OUTPUT_USB);
            }
            return false;
#    ifdef BLUETOOTH_ENABLE
        case OUT_BT:
            if (record->event.pressed) {
                set_output(OUTPUT_BLUETOOTH);
            }
            return false;
#    endif
#endif
        case MAGIC_SWAP_CONTROL_CAPSLOCK ... MAGIC_TOGGLE_ALT_GUI:
        case MAGIC_SWAP_LCTL_LGUI ... MAGIC_EE_HANDS_RIGHT:
            if (record->event.pressed) {
                // MAGIC actions (BOOTMAGIC without the boot)
                if (!eeconfig_is_enabled()) {
                    eeconfig_init();
                }
                /* keymap config */
                keymap_config.raw = eeconfig_read_keymap();
                switch (keycode) {
                    case MAGIC_SWAP_CONTROL_CAPSLOCK:
                        keymap_config.swap_control_capslock = true;
                        break;
                    case MAGIC_CAPSLOCK_TO_CONTROL:
                        keymap_config.capslock_to_control = true;
                        break;
                    case MAGIC_SWAP_LALT_LGUI:
                        keymap_config.swap_lalt_lgui = true;
                        break;
                    case MAGIC_SWAP_RALT_RGUI:
                        keymap_config.swap_ralt_rgui = true;
                        break;
                    case MAGIC_SWAP_LCTL_LGUI:
                        keymap_config.swap_lctl_lgui = true;
                        break;
                    case MAGIC_SWAP_RCTL_RGUI:
                        keymap_config.swap_rctl_rgui = true;
                        break;
                    case MAGIC_NO_GUI:
                        keymap_config.no_gui = true;
                        break;
                    case MAGIC_SWAP_GRAVE_ESC:
                        keymap_config.swap_grave_esc = true;
                        break;
                    case MAGIC_SWAP_BACKSLASH_BACKSPACE:
                        keymap_config.swap_backslash_backspace = true;
                        break;
                    case MAGIC_HOST_NKRO:
                        keymap_config.nkro = true;
                        break;
                    case MAGIC_SWAP_ALT_GUI:
                        keymap_config.swap_lalt_lgui = keymap_config.swap_ralt_rgui = true;
#ifdef AUDIO_ENABLE
                        PLAY_SONG(ag_swap_song);
#endif
                        break;
                    case MAGIC_SWAP_CTL_GUI:
                        keymap_config.swap_lctl_lgui = keymap_config.swap_rctl_rgui = true;
#ifdef AUDIO_ENABLE
                        PLAY_SONG(cg_swap_song);
#endif
                        break;
                    case MAGIC_UNSWAP_CONTROL_CAPSLOCK:
                        keymap_config.swap_control_capslock = false;
                        break;
                    case MAGIC_UNCAPSLOCK_TO_CONTROL:
                        keymap_config.capslock_to_control = false;
                        break;
                    case MAGIC_UNSWAP_LALT_LGUI:
                        keymap_config.swap_lalt_lgui = false;
                        break;
                    case MAGIC_UNSWAP_RALT_RGUI:
                        keymap_config.swap_ralt_rgui = false;
                        break;
                    case MAGIC_UNSWAP_LCTL_LGUI:
                        keymap_config.swap_lctl_lgui = false;
                        break;
                    case MAGIC_UNSWAP_RCTL_RGUI:
                        keymap_config.swap_rctl_rgui = false;
                        break;
                    case MAGIC_UNNO_GUI:
                        keymap_config.no_gui = false;
                        break;
                    case MAGIC_UNSWAP_GRAVE_ESC:
                        keymap_config.swap_grave_esc = false;
                        break;
                    case MAGIC_UNSWAP_BACKSLASH_BACKSPACE:
                        keymap_config.swap_backslash_backspace = false;
                        break;
                    case MAGIC_UNHOST_NKRO:
                        keymap_config.nkro = false;
                        break;
                    case MAGIC_UNSWAP_ALT_GUI:
                        keymap_config.swap_lalt_lgui = keymap_config.swap_ralt_rgui = false;
#ifdef AUDIO_ENABLE
                        PLAY_SONG(ag_norm_song);
#endif
                        break;
                    case MAGIC_UNSWAP_CTL_GUI:
                        keymap_config.swap_lctl_lgui = keymap_config.swap_rctl_rgui = false;
#ifdef AUDIO_ENABLE
                        PLAY_SONG(cg_norm_song);
#endif
                        break;
                    case MAGIC_TOGGLE_ALT_GUI:
                        keymap_config.swap_lalt_lgui = !keymap_config.swap_lalt_lgui;
                        keymap_config.swap_ralt_rgui = keymap_config.swap_lalt_lgui;
#ifdef AUDIO_ENABLE
                        if (keymap_config.swap_ralt_rgui) {
                            PLAY_SONG(ag_swap_song);
                        } else {
                            PLAY_SONG(ag_norm_song);
                        }
#endif
                        break;
                    case MAGIC_TOGGLE_CTL_GUI:
                        keymap_config.swap_lctl_lgui = !keymap_config.swap_lctl_lgui;
                        keymap_config.swap_rctl_rgui = keymap_config.swap_lctl_lgui;
#ifdef AUDIO_ENABLE
                        if (keymap_config.swap_rctl_rgui) {
                            PLAY_SONG(cg_swap_song);
                        } else {
                            PLAY_SONG(cg_norm_song);
                        }
#endif
                        break;
                    case MAGIC_TOGGLE_NKRO:
                        keymap_config.nkro = !keymap_config.nkro;
                        break;
                    case MAGIC_EE_HANDS_LEFT:
                        eeconfig_update_handedness(true);
                        break;
                    case MAGIC_EE_HANDS_RIGHT:
                        eeconfig_update_handedness(false);
                        break;
                    default:
                        break;
                }
                eeconfig_update_keymap(keymap_config.raw);
                clear_keyboard();  // clear to prevent stuck keys

                return false;
            }
            break;

        case GRAVE_ESC: {
            uint8_t shifted = get_mods() & ((MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT) | MOD_BIT(KC_LGUI) | MOD_BIT(KC_RGUI)));

#ifdef GRAVE_ESC_ALT_OVERRIDE
            // if ALT is pressed, ESC is always sent
            // this is handy for the cmd+opt+esc shortcut on macOS, among other things.
            if (get_mods() & (MOD_BIT(KC_LALT) | MOD_BIT(KC_RALT))) {
                shifted = 0;
            }
#endif

#ifdef GRAVE_ESC_CTRL_OVERRIDE
            // if CTRL is pressed, ESC is always sent
            // this is handy for the ctrl+shift+esc shortcut on windows, among other things.
            if (get_mods() & (MOD_BIT(KC_LCTL) | MOD_BIT(KC_RCTL))) {
                shifted = 0;
            }
#endif

#ifdef GRAVE_ESC_GUI_OVERRIDE
            // if GUI is pressed, ESC is always sent
            if (get_mods() & (MOD_BIT(KC_LGUI) | MOD_BIT(KC_RGUI))) {
                shifted = 0;
            }
#endif

#ifdef GRAVE_ESC_SHIFT_OVERRIDE
            // if SHIFT is pressed, ESC is always sent
            if (get_mods() & (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT))) {
                shifted = 0;
            }
#endif

            if (record->event.pressed) {
                grave_esc_was_shifted = shifted;
                add_key(shifted ? KC_GRAVE : KC_ESCAPE);
            } else {
                del_key(grave_esc_was_shifted ? KC_GRAVE : KC_ESCAPE);
            }

            send_keyboard_report();
            return false;
        }

#if defined(BACKLIGHT_ENABLE) && defined(BACKLIGHT_BREATHING)
        case BL_BRTG: {
            if (record->event.pressed) {
                backlight_toggle_breathing();
            }
            return false;
        }
#endif
    }

    return process_action_kb(record);
}

__attribute__((weak)) const bool ascii_to_shift_lut[128] PROGMEM = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

                                                                    0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0};

__attribute__((weak)) const bool ascii_to_altgr_lut[128] PROGMEM = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

                                                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

__attribute__((weak)) const uint8_t ascii_to_keycode_lut[128] PROGMEM = {// NUL   SOH      STX      ETX      EOT      ENQ      ACK      BEL
                                                                         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                                                         // BS    TAB      LF       VT       FF       CR       SO       SI
                                                                         KC_BSPC, KC_TAB, KC_ENT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                                                         // DLE   DC1      DC2      DC3      DC4      NAK      SYN      ETB
                                                                         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                                                         // CAN   EM       SUB      ESC      FS       GS       RS       US
                                                                         XXXXXXX, XXXXXXX, XXXXXXX, KC_ESC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,

                                                                         //       !        "        #        $        %        &        '
                                                                         KC_SPC, KC_1, KC_QUOT, KC_3, KC_4, KC_5, KC_7, KC_QUOT,
                                                                         // (     )        *        +        ,        -        .        /
                                                                         KC_9, KC_0, KC_8, KC_EQL, KC_COMM, KC_MINS, KC_DOT, KC_SLSH,
                                                                         // 0     1        2        3        4        5        6        7
                                                                         KC_0, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7,
                                                                         // 8     9        :        ;        <        =        >        ?
                                                                         KC_8, KC_9, KC_SCLN, KC_SCLN, KC_COMM, KC_EQL, KC_DOT, KC_SLSH,
                                                                         // @     A        B        C        D        E        F        G
                                                                         KC_2, KC_A, KC_B, KC_C, KC_D, KC_E, KC_F, KC_G,
                                                                         // H     I        J        K        L        M        N        O
                                                                         KC_H, KC_I, KC_J, KC_K, KC_L, KC_M, KC_N, KC_O,
                                                                         // P     Q        R        S        T        U        V        W
                                                                         KC_P, KC_Q, KC_R, KC_S, KC_T, KC_U, KC_V, KC_W,
                                                                         // X     Y        Z        [        \        ]        ^        _
                                                                         KC_X, KC_Y, KC_Z, KC_LBRC, KC_BSLS, KC_RBRC, KC_6, KC_MINS,
                                                                         // `     a        b        c        d        e        f        g
                                                                         KC_GRV, KC_A, KC_B, KC_C, KC_D, KC_E, KC_F, KC_G,
                                                                         // h     i        j        k        l        m        n        o
                                                                         KC_H, KC_I, KC_J, KC_K, KC_L, KC_M, KC_N, KC_O,
                                                                         // p     q        r        s        t        u        v        w
                                                                         KC_P, KC_Q, KC_R, KC_S, KC_T, KC_U, KC_V, KC_W,
                                                                         // x     y        z        {        |        }        ~        DEL
                                                                         KC_X, KC_Y, KC_Z, KC_LBRC, KC_BSLS, KC_RBRC, KC_GRV, KC_DEL};

void send_string(const char *str) { send_string_with_delay(str, 0); }

void send_string_P(const char *str) { send_string_with_delay_P(str, 0); }

void send_string_with_delay(const char *str, uint8_t interval) {
    while (1) {
        char ascii_code = *str;
        if (!ascii_code) break;
        if (ascii_code == SS_TAP_CODE) {
            // tap
            uint8_t keycode = *(++str);
            register_code(keycode);
            unregister_code(keycode);
        } else if (ascii_code == SS_DOWN_CODE) {
            // down
            uint8_t keycode = *(++str);
            register_code(keycode);
        } else if (ascii_code == SS_UP_CODE) {
            // up
            uint8_t keycode = *(++str);
            unregister_code(keycode);
        } else {
            send_char(ascii_code);
        }
        ++str;
        // interval
        {
            uint8_t ms = interval;
            while (ms--) wait_ms(1);
        }
    }
}

void send_string_with_delay_P(const char *str, uint8_t interval) {
    while (1) {
        char ascii_code = pgm_read_byte(str);
        if (!ascii_code) break;
        if (ascii_code == SS_TAP_CODE) {
            // tap
            uint8_t keycode = pgm_read_byte(++str);
            register_code(keycode);
            unregister_code(keycode);
        } else if (ascii_code == SS_DOWN_CODE) {
            // down
            uint8_t keycode = pgm_read_byte(++str);
            register_code(keycode);
        } else if (ascii_code == SS_UP_CODE) {
            // up
            uint8_t keycode = pgm_read_byte(++str);
            unregister_code(keycode);
        } else {
            send_char(ascii_code);
        }
        ++str;
        // interval
        {
            uint8_t ms = interval;
            while (ms--) wait_ms(1);
        }
    }
}

void send_char(char ascii_code) {
    uint8_t keycode    = pgm_read_byte(&ascii_to_keycode_lut[(uint8_t)ascii_code]);
    bool    is_shifted = pgm_read_byte(&ascii_to_shift_lut[(uint8_t)ascii_code]);
    bool    is_altgred = pgm_read_byte(&ascii_to_altgr_lut[(uint8_t)ascii_code]);

    if (is_shifted) {
        register_code(KC_LSFT);
    }
    if (is_altgred) {
        register_code(KC_RALT);
    }
    tap_code(keycode);
    if (is_altgred) {
        unregister_code(KC_RALT);
    }
    if (is_shifted) {
        unregister_code(KC_LSFT);
    }
}

void set_single_persistent_default_layer(uint8_t default_layer) {
#if defined(AUDIO_ENABLE) && defined(DEFAULT_LAYER_SONGS)
    PLAY_SONG(default_layer_songs[default_layer]);
#endif
    eeconfig_update_default_layer(1U << default_layer);
    default_layer_set(1U << default_layer);
}

layer_state_t update_tri_layer_state(layer_state_t state, uint8_t layer1, uint8_t layer2, uint8_t layer3) {
    layer_state_t mask12 = (1UL << layer1) | (1UL << layer2);
    layer_state_t mask3  = 1UL << layer3;
    return (state & mask12) == mask12 ? (state | mask3) : (state & ~mask3);
}

void update_tri_layer(uint8_t layer1, uint8_t layer2, uint8_t layer3) { layer_state_set(update_tri_layer_state(layer_state, layer1, layer2, layer3)); }

void tap_random_base64(void) {
#if defined(__AVR_ATmega32U4__)
    uint8_t key = (TCNT0 + TCNT1 + TCNT3 + TCNT4) % 64;
#else
    uint8_t key = rand() % 64;
#endif
    switch (key) {
        case 0 ... 25:
            register_code(KC_LSFT);
            register_code(key + KC_A);
            unregister_code(key + KC_A);
            unregister_code(KC_LSFT);
            break;
        case 26 ... 51:
            register_code(key - 26 + KC_A);
            unregister_code(key - 26 + KC_A);
            break;
        case 52:
            register_code(KC_0);
            unregister_code(KC_0);
            break;
        case 53 ... 61:
            register_code(key - 53 + KC_1);
            unregister_code(key - 53 + KC_1);
            break;
        case 62:
            register_code(KC_LSFT);
            register_code(KC_EQL);
            unregister_code(KC_EQL);
            unregister_code(KC_LSFT);
            break;
        case 63:
            register_code(KC_SLSH);
            unregister_code(KC_SLSH);
            break;
    }
}

__attribute__((weak)) void bootmagic_lite(void) {
    // The lite version of TMK's bootmagic based on Wilba.
    // 100% less potential for accidentally making the
    // keyboard do stupid things.

    // We need multiple scans because debouncing can't be turned off.
    matrix_scan();
#if defined(DEBOUNCING_DELAY) && DEBOUNCING_DELAY > 0
    wait_ms(DEBOUNCING_DELAY * 2);
#elif defined(DEBOUNCE) && DEBOUNCE > 0
    wait_ms(DEBOUNCE * 2);
#else
    wait_ms(30);
#endif
    matrix_scan();

    // If the Esc and space bar are held down on power up,
    // reset the EEPROM valid state and jump to bootloader.
    // Assumes Esc is at [0,0].
    // This isn't very generalized, but we need something that doesn't
    // rely on user's keymaps in firmware or EEPROM.
    if (matrix_get_row(BOOTMAGIC_LITE_ROW) & (1 << BOOTMAGIC_LITE_COLUMN)) {
        eeconfig_disable();
        // Jump to bootloader.
        bootloader_jump();
    }
}

void matrix_init_quantum() {
#ifdef BOOTMAGIC_LITE
    bootmagic_lite();
#endif
    if (!eeconfig_is_enabled()) {
        eeconfig_init();
    }
#ifdef BACKLIGHT_ENABLE
#    ifdef LED_MATRIX_ENABLE
    led_matrix_init();
#    else
    backlight_init_ports();
#    endif
#endif
#ifdef AUDIO_ENABLE
    audio_init();
#endif
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_init();
#endif
#ifdef ENCODER_ENABLE
    encoder_init();
#endif
#if defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE) || defined(UCIS_ENABLE)
    unicode_input_mode_init();
#endif
#ifdef HAPTIC_ENABLE
    haptic_init();
#endif
#ifdef OUTPUT_AUTO_ENABLE
    set_output(OUTPUT_AUTO);
#endif
#ifdef DIP_SWITCH_ENABLE
    dip_switch_init();
#endif

    matrix_init_kb();
}

void matrix_scan_quantum() {
#if defined(AUDIO_ENABLE) && !defined(NO_MUSIC_MODE)
    matrix_scan_music();
#endif

#ifdef TAP_DANCE_ENABLE
    matrix_scan_tap_dance();
#endif

#ifdef COMBO_ENABLE
    matrix_scan_combo();
#endif

#if defined(BACKLIGHT_ENABLE)
#    if defined(LED_MATRIX_ENABLE)
    led_matrix_task();
#    elif defined(BACKLIGHT_PIN)
    backlight_task();
#    endif
#endif

#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_task();
#endif

#ifdef ENCODER_ENABLE
    encoder_read();
#endif

#ifdef HAPTIC_ENABLE
    haptic_task();
#endif

#ifdef DIP_SWITCH_ENABLE
    dip_switch_read(false);
#endif

    matrix_scan_kb();
}
#if defined(BACKLIGHT_ENABLE) && (defined(BACKLIGHT_PIN) || defined(BACKLIGHT_PINS))

// This logic is a bit complex, we support 3 setups:
//
//   1. Hardware PWM when backlight is wired to a PWM pin.
//      Depending on this pin, we use a different output compare unit.
//   2. Software PWM with hardware timers, but the used timer
//      depends on the Audio setup (Audio wins over Backlight).
//   3. Full software PWM, driven by the matrix scan, if both timers are used by Audio.

#    if (defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB647__) || defined(__AVR_AT90USB1286__) || defined(__AVR_AT90USB1287__) || defined(__AVR_ATmega16U4__) || defined(__AVR_ATmega32U4__)) && (BACKLIGHT_PIN == B5 || BACKLIGHT_PIN == B6 || BACKLIGHT_PIN == B7)
#        define HARDWARE_PWM
#        define ICRx ICR1
#        define TCCRxA TCCR1A
#        define TCCRxB TCCR1B
#        define TIMERx_OVF_vect TIMER1_OVF_vect
#        define TIMSKx TIMSK1
#        define TOIEx TOIE1

#        if BACKLIGHT_PIN == B5
#            define COMxx1 COM1A1
#            define OCRxx OCR1A
#        elif BACKLIGHT_PIN == B6
#            define COMxx1 COM1B1
#            define OCRxx OCR1B
#        elif BACKLIGHT_PIN == B7
#            define COMxx1 COM1C1
#            define OCRxx OCR1C
#        endif
#    elif (defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB647__) || defined(__AVR_AT90USB1286__) || defined(__AVR_AT90USB1287__) || defined(__AVR_ATmega16U4__) || defined(__AVR_ATmega32U4__)) && (BACKLIGHT_PIN == C4 || BACKLIGHT_PIN == C5 || BACKLIGHT_PIN == C6)
#        define HARDWARE_PWM
#        define ICRx ICR3
#        define TCCRxA TCCR3A
#        define TCCRxB TCCR3B
#        define TIMERx_OVF_vect TIMER3_OVF_vect
#        define TIMSKx TIMSK3
#        define TOIEx TOIE3

#        if BACKLIGHT_PIN == C4
#            if (defined(__AVR_ATmega16U4__) || defined(__AVR_ATmega32U4__))
#                error This MCU has no C4 pin!
#            else
#                define COMxx1 COM3C1
#                define OCRxx OCR3C
#            endif
#        elif BACKLIGHT_PIN == C5
#            if (defined(__AVR_ATmega16U4__) || defined(__AVR_ATmega32U4__))
#                error This MCU has no C5 pin!
#            else
#                define COMxx1 COM3B1
#                define OCRxx OCR3B
#            endif
#        elif BACKLIGHT_PIN == C6
#            define COMxx1 COM3A1
#            define OCRxx OCR3A
#        endif
#    elif (defined(__AVR_ATmega16U2__) || defined(__AVR_ATmega32U2__)) && (BACKLIGHT_PIN == B7 || BACKLIGHT_PIN == C5 || BACKLIGHT_PIN == C6)
#        define HARDWARE_PWM
#        define ICRx ICR1
#        define TCCRxA TCCR1A
#        define TCCRxB TCCR1B
#        define TIMERx_OVF_vect TIMER1_OVF_vect
#        define TIMSKx TIMSK1
#        define TOIEx TOIE1

#        if BACKLIGHT_PIN == B7
#            define COMxx1 COM1C1
#            define OCRxx OCR1C
#        elif BACKLIGHT_PIN == C5
#            define COMxx1 COM1B1
#            define OCRxx OCR1B
#        elif BACKLIGHT_PIN == C6
#            define COMxx1 COM1A1
#            define OCRxx OCR1A
#        endif
#    elif defined(__AVR_ATmega32A__) && (BACKLIGHT_PIN == D4 || BACKLIGHT_PIN == D5)
#        define HARDWARE_PWM
#        define ICRx ICR1
#        define TCCRxA TCCR1A
#        define TCCRxB TCCR1B
#        define TIMERx_OVF_vect TIMER1_OVF_vect
#        define TIMSKx TIMSK
#        define TOIEx TOIE1

#        if BACKLIGHT_PIN == D4
#            define COMxx1 COM1B1
#            define OCRxx OCR1B
#        elif BACKLIGHT_PIN == D5
#            define COMxx1 COM1A1
#            define OCRxx OCR1A
#        endif
#    elif defined(__AVR_ATmega328P__) && (BACKLIGHT_PIN == B1 || BACKLIGHT_PIN == B2)
#        define HARDWARE_PWM
#        define ICRx ICR1
#        define TCCRxA TCCR1A
#        define TCCRxB TCCR1B
#        define TIMERx_OVF_vect TIMER1_OVF_vect
#        define TIMSKx TIMSK1
#        define TOIEx TOIE1

#        if BACKLIGHT_PIN == B1
#            define COMxx1 COM1A1
#            define OCRxx OCR1A
#        elif BACKLIGHT_PIN == B2
#            define COMxx1 COM1B1
#            define OCRxx OCR1B
#        endif
#    else
#        if !defined(BACKLIGHT_CUSTOM_DRIVER)
#            if !defined(B5_AUDIO) && !defined(B6_AUDIO) && !defined(B7_AUDIO)
// Timer 1 is not in use by Audio feature, Backlight can use it
#                pragma message "Using hardware timer 1 with software PWM"
#                define HARDWARE_PWM
#                define BACKLIGHT_PWM_TIMER
#                define ICRx ICR1
#                define TCCRxA TCCR1A
#                define TCCRxB TCCR1B
#                define TIMERx_COMPA_vect TIMER1_COMPA_vect
#                define TIMERx_OVF_vect TIMER1_OVF_vect
#                if defined(__AVR_ATmega32A__)  // This MCU has only one TIMSK register
#                    define TIMSKx TIMSK
#                else
#                    define TIMSKx TIMSK1
#                endif
#                define TOIEx TOIE1

#                define OCIExA OCIE1A
#                define OCRxx OCR1A
#            elif !defined(C6_AUDIO) && !defined(C5_AUDIO) && !defined(C4_AUDIO)
#                pragma message "Using hardware timer 3 with software PWM"
// Timer 3 is not in use by Audio feature, Backlight can use it
#                define HARDWARE_PWM
#                define BACKLIGHT_PWM_TIMER
#                define ICRx ICR1
#                define TCCRxA TCCR3A
#                define TCCRxB TCCR3B
#                define TIMERx_COMPA_vect TIMER3_COMPA_vect
#                define TIMERx_OVF_vect TIMER3_OVF_vect
#                define TIMSKx TIMSK3
#                define TOIEx TOIE3

#                define OCIExA OCIE3A
#                define OCRxx OCR3A
#            else
#                pragma message "Audio in use - using pure software PWM"
#                define NO_HARDWARE_PWM
#            endif
#        else
#            pragma message "Custom driver defined - using pure software PWM"
#            define NO_HARDWARE_PWM
#        endif
#    endif

#    ifndef BACKLIGHT_ON_STATE
#        define BACKLIGHT_ON_STATE 0
#    endif

void backlight_on(uint8_t backlight_pin) {
#    if BACKLIGHT_ON_STATE == 0
    writePinLow(backlight_pin);
#    else
    writePinHigh(backlight_pin);
#    endif
}

void backlight_off(uint8_t backlight_pin) {
#    if BACKLIGHT_ON_STATE == 0
    writePinHigh(backlight_pin);
#    else
    writePinLow(backlight_pin);
#    endif
}

#    if defined(NO_HARDWARE_PWM) || defined(BACKLIGHT_PWM_TIMER)  // pwm through software

// we support multiple backlight pins
#        ifndef BACKLIGHT_LED_COUNT
#            define BACKLIGHT_LED_COUNT 1
#        endif

#        if BACKLIGHT_LED_COUNT == 1
#            define BACKLIGHT_PIN_INIT \
                { BACKLIGHT_PIN }
#        else
#            define BACKLIGHT_PIN_INIT BACKLIGHT_PINS
#        endif

#        define FOR_EACH_LED(x)                                 \
            for (uint8_t i = 0; i < BACKLIGHT_LED_COUNT; i++) { \
                uint8_t backlight_pin = backlight_pins[i];      \
                { x }                                           \
            }

static const uint8_t backlight_pins[BACKLIGHT_LED_COUNT] = BACKLIGHT_PIN_INIT;

#    else  // full hardware PWM

// we support only one backlight pin
static const uint8_t backlight_pin = BACKLIGHT_PIN;
#        define FOR_EACH_LED(x) x

#    endif

#    ifdef NO_HARDWARE_PWM
__attribute__((weak)) void backlight_init_ports(void) {
    // Setup backlight pin as output and output to on state.
    FOR_EACH_LED(setPinOutput(backlight_pin); backlight_on(backlight_pin);)

#        ifdef BACKLIGHT_BREATHING
    if (is_backlight_breathing()) {
        breathing_enable();
    }
#        endif
}

__attribute__((weak)) void backlight_set(uint8_t level) {}

uint8_t backlight_tick = 0;

#        ifndef BACKLIGHT_CUSTOM_DRIVER
void backlight_task(void) {
    if ((0xFFFF >> ((BACKLIGHT_LEVELS - get_backlight_level()) * ((BACKLIGHT_LEVELS + 1) / 2))) & (1 << backlight_tick)) {
        FOR_EACH_LED(backlight_on(backlight_pin);)
    } else {
        FOR_EACH_LED(backlight_off(backlight_pin);)
    }
    backlight_tick = (backlight_tick + 1) % 16;
}
#        endif

#        ifdef BACKLIGHT_BREATHING
#            ifndef BACKLIGHT_CUSTOM_DRIVER
#                error "Backlight breathing only available with hardware PWM. Please disable."
#            endif
#        endif

#    else  // hardware pwm through timer

#        ifdef BACKLIGHT_PWM_TIMER

// The idea of software PWM assisted by hardware timers is the following
// we use the hardware timer in fast PWM mode like for hardware PWM, but
// instead of letting the Output Match Comparator control the led pin
// (which is not possible since the backlight is not wired to PWM pins on the
// CPU), we do the LED on/off by oursleves.
// The timer is setup to count up to 0xFFFF, and we set the Output Compare
// register to the current 16bits backlight level (after CIE correction).
// This means the CPU will trigger a compare match interrupt when the counter
// reaches the backlight level, where we turn off the LEDs,
// but also an overflow interrupt when the counter rolls back to 0,
// in which we're going to turn on the LEDs.
// The LED will then be on for OCRxx/0xFFFF time, adjusted every 244Hz.

// Triggered when the counter reaches the OCRx value
ISR(TIMERx_COMPA_vect) { FOR_EACH_LED(backlight_off(backlight_pin);) }

// Triggered when the counter reaches the TOP value
// this one triggers at F_CPU/65536 =~ 244 Hz
ISR(TIMERx_OVF_vect) {
#            ifdef BACKLIGHT_BREATHING
    if (is_breathing()) {
        breathing_task();
    }
#            endif
    // for very small values of OCRxx (or backlight level)
    // we can't guarantee this whole code won't execute
    // at the same time as the compare match interrupt
    // which means that we might turn on the leds while
    // trying to turn them off, leading to flickering
    // artifacts (especially while breathing, because breathing_task
    // takes many computation cycles).
    // so better not turn them on while the counter TOP is very low.
    if (OCRxx > 256) {
        FOR_EACH_LED(backlight_on(backlight_pin);)
    }
}

#        endif

#        define TIMER_TOP 0xFFFFU

// See http://jared.geek.nz/2013/feb/linear-led-pwm
static uint16_t cie_lightness(uint16_t v) {
    if (v <= 5243)     // if below 8% of max
        return v / 9;  // same as dividing by 900%
    else {
        uint32_t y = (((uint32_t)v + 10486) << 8) / (10486 + 0xFFFFUL);  // add 16% of max and compare
        // to get a useful result with integer division, we shift left in the expression above
        // and revert what we've done again after squaring.
        y = y * y * y >> 8;
        if (y > 0xFFFFUL)  // prevent overflow
            return 0xFFFFU;
        else
            return (uint16_t)y;
    }
}

// range for val is [0..TIMER_TOP]. PWM pin is high while the timer count is below val.
static inline void set_pwm(uint16_t val) { OCRxx = val; }

#        ifndef BACKLIGHT_CUSTOM_DRIVER
__attribute__((weak)) void backlight_set(uint8_t level) {
    if (level > BACKLIGHT_LEVELS) level = BACKLIGHT_LEVELS;

    if (level == 0) {
#            ifdef BACKLIGHT_PWM_TIMER
        if (OCRxx) {
            TIMSKx &= ~(_BV(OCIExA));
            TIMSKx &= ~(_BV(TOIEx));
            FOR_EACH_LED(backlight_off(backlight_pin);)
        }
#            else
        // Turn off PWM control on backlight pin
        TCCRxA &= ~(_BV(COMxx1));
#            endif
    } else {
#            ifdef BACKLIGHT_PWM_TIMER
        if (!OCRxx) {
            TIMSKx |= _BV(OCIExA);
            TIMSKx |= _BV(TOIEx);
        }
#            else
        // Turn on PWM control of backlight pin
        TCCRxA |= _BV(COMxx1);
#            endif
    }
    // Set the brightness
    set_pwm(cie_lightness(TIMER_TOP * (uint32_t)level / BACKLIGHT_LEVELS));
}

void backlight_task(void) {}
#        endif  // BACKLIGHT_CUSTOM_DRIVER

#        ifdef BACKLIGHT_BREATHING

#            define BREATHING_NO_HALT 0
#            define BREATHING_HALT_OFF 1
#            define BREATHING_HALT_ON 2
#            define BREATHING_STEPS 128

static uint8_t breathing_period = BREATHING_PERIOD;
static uint8_t breathing_halt = BREATHING_NO_HALT;
static uint16_t breathing_counter = 0;

#            ifdef BACKLIGHT_PWM_TIMER
static bool breathing = false;

bool is_breathing(void) { return breathing; }

#                define breathing_interrupt_enable() \
                    do {                             \
                        breathing = true;            \
                    } while (0)
#                define breathing_interrupt_disable() \
                    do {                              \
                        breathing = false;            \
                    } while (0)
#            else

bool is_breathing(void) { return !!(TIMSKx & _BV(TOIEx)); }

#                define breathing_interrupt_enable() \
                    do {                             \
                        TIMSKx |= _BV(TOIEx);        \
                    } while (0)
#                define breathing_interrupt_disable() \
                    do {                              \
                        TIMSKx &= ~_BV(TOIEx);        \
                    } while (0)
#            endif

#            define breathing_min()        \
                do {                       \
                    breathing_counter = 0; \
                } while (0)
#            define breathing_max()                                 \
                do {                                                \
                    breathing_counter = breathing_period * 244 / 2; \
                } while (0)

void breathing_enable(void) {
    breathing_counter = 0;
    breathing_halt = BREATHING_NO_HALT;
    breathing_interrupt_enable();
}

void breathing_pulse(void) {
    if (get_backlight_level() == 0)
        breathing_min();
    else
        breathing_max();
    breathing_halt = BREATHING_HALT_ON;
    breathing_interrupt_enable();
}

void breathing_disable(void) {
    breathing_interrupt_disable();
    // Restore backlight level
    backlight_set(get_backlight_level());
}

void breathing_self_disable(void) {
    if (get_backlight_level() == 0)
        breathing_halt = BREATHING_HALT_OFF;
    else
        breathing_halt = BREATHING_HALT_ON;
}

void breathing_toggle(void) {
    if (is_breathing())
        breathing_disable();
    else
        breathing_enable();
}

void breathing_period_set(uint8_t value) {
    if (!value) value = 1;
    breathing_period = value;
}

void breathing_period_default(void) { breathing_period_set(BREATHING_PERIOD); }

void breathing_period_inc(void) { breathing_period_set(breathing_period + 1); }

void breathing_period_dec(void) { breathing_period_set(breathing_period - 1); }

/* To generate breathing curve in python:
 * from math import sin, pi; [int(sin(x/128.0*pi)**4*255) for x in range(128)]
 */
static const uint8_t breathing_table[BREATHING_STEPS] PROGMEM = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 3, 4, 5, 6, 8, 10, 12, 15, 17, 20, 24, 28, 32, 36, 41, 46, 51, 57, 63, 70, 76, 83, 91, 98, 106, 113, 121, 129, 138, 146, 154, 162, 170, 178, 185, 193, 200, 207, 213, 220, 225, 231, 235, 240, 244, 247, 250, 252, 253, 254, 255, 254, 253, 252, 250, 247, 244, 240, 235, 231, 225, 220, 213, 207, 200, 193, 185, 178, 170, 162, 154, 146, 138, 129, 121, 113, 106, 98, 91, 83, 76, 70, 63, 57, 51, 46, 41, 36, 32, 28, 24, 20, 17, 15, 12, 10, 8, 6, 5, 4, 3, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// Use this before the cie_lightness function.
static inline uint16_t scale_backlight(uint16_t v) { return v / BACKLIGHT_LEVELS * get_backlight_level(); }

#            ifdef BACKLIGHT_PWM_TIMER
void breathing_task(void)
#            else
/* Assuming a 16MHz CPU clock and a timer that resets at 64k (ICR1), the following interrupt handler will run
 * about 244 times per second.
 */
ISR(TIMERx_OVF_vect)
#            endif
{
    uint16_t interval = (uint16_t)breathing_period * 244 / BREATHING_STEPS;
    // resetting after one period to prevent ugly reset at overflow.
    breathing_counter = (breathing_counter + 1) % (breathing_period * 244);
    uint8_t index = breathing_counter / interval % BREATHING_STEPS;

    if (((breathing_halt == BREATHING_HALT_ON) && (index == BREATHING_STEPS / 2)) || ((breathing_halt == BREATHING_HALT_OFF) && (index == BREATHING_STEPS - 1))) {
        breathing_interrupt_disable();
    }

    set_pwm(cie_lightness(scale_backlight((uint16_t)pgm_read_byte(&breathing_table[index]) * 0x0101U)));
}

#        endif  // BACKLIGHT_BREATHING

__attribute__((weak)) void backlight_init_ports(void) {
    // Setup backlight pin as output and output to on state.
    FOR_EACH_LED(setPinOutput(backlight_pin); backlight_on(backlight_pin);)

    // I could write a wall of text here to explain... but TL;DW
    // Go read the ATmega32u4 datasheet.
    // And this: http://blog.saikoled.com/post/43165849837/secret-konami-cheat-code-to-high-resolution-pwm-on

#        ifdef BACKLIGHT_PWM_TIMER
    // TimerX setup, Fast PWM mode count to TOP set in ICRx
    TCCRxA = _BV(WGM11);  // = 0b00000010;
    // clock select clk/1
    TCCRxB = _BV(WGM13) | _BV(WGM12) | _BV(CS10);  // = 0b00011001;
#        else  // hardware PWM
    // Pin PB7 = OCR1C (Timer 1, Channel C)
    // Compare Output Mode = Clear on compare match, Channel C = COM1C1=1 COM1C0=0
    // (i.e. start high, go low when counter matches.)
    // WGM Mode 14 (Fast PWM) = WGM13=1 WGM12=1 WGM11=1 WGM10=0
    // Clock Select = clk/1 (no prescaling) = CS12=0 CS11=0 CS10=1

    /*
    14.8.3:
    "In fast PWM mode, the compare units allow generation of PWM waveforms on the OCnx pins. Setting the COMnx1:0 bits to two will produce a non-inverted PWM [..]."
    "In fast PWM mode the counter is incremented until the counter value matches either one of the fixed values 0x00FF, 0x01FF, or 0x03FF (WGMn3:0 = 5, 6, or 7), the value in ICRn (WGMn3:0 = 14), or the value in OCRnA (WGMn3:0 = 15)."
    */
    TCCRxA = _BV(COMxx1) | _BV(WGM11);             // = 0b00001010;
    TCCRxB = _BV(WGM13) | _BV(WGM12) | _BV(CS10);  // = 0b00011001;
#        endif
    // Use full 16-bit resolution. Counter counts to ICR1 before reset to 0.
    ICRx = TIMER_TOP;

    backlight_init();
#        ifdef BACKLIGHT_BREATHING
    if (is_backlight_breathing()) {
        breathing_enable();
    }
#        endif
}

#    endif  // hardware backlight

#else  // no backlight

__attribute__((weak)) void backlight_init_ports(void) {}

__attribute__((weak)) void backlight_set(uint8_t level) {}

#endif  // backlight

#ifdef HD44780_ENABLED
#    include "hd44780.h"
#endif

// Functions for spitting out values
//

void send_dword(uint32_t number) {  // this might not actually work
    uint16_t word = (number >> 16);
    send_word(word);
    send_word(number & 0xFFFFUL);
}

void send_word(uint16_t number) {
    uint8_t byte = number >> 8;
    send_byte(byte);
    send_byte(number & 0xFF);
}

void send_byte(uint8_t number) {
    uint8_t nibble = number >> 4;
    send_nibble(nibble);
    send_nibble(number & 0xF);
}

void send_nibble(uint8_t number) {
    switch (number) {
        case 0:
            register_code(KC_0);
            unregister_code(KC_0);
            break;
        case 1 ... 9:
            register_code(KC_1 + (number - 1));
            unregister_code(KC_1 + (number - 1));
            break;
        case 0xA ... 0xF:
            register_code(KC_A + (number - 0xA));
            unregister_code(KC_A + (number - 0xA));
            break;
    }
}

__attribute__((weak)) uint16_t hex_to_keycode(uint8_t hex) {
    hex = hex & 0xF;
    if (hex == 0x0) {
        return KC_0;
    } else if (hex < 0xA) {
        return KC_1 + (hex - 0x1);
    } else {
        return KC_A + (hex - 0xA);
    }
}

void api_send_unicode(uint32_t unicode) {
#ifdef API_ENABLE
    uint8_t chunk[4];
    dword_to_bytes(unicode, chunk);
    MT_SEND_DATA(DT_UNICODE, chunk, 5);
#endif
}

__attribute__((weak)) void led_set_user(uint8_t usb_led) {}

__attribute__((weak)) void led_set_kb(uint8_t usb_led) { led_set_user(usb_led); }

__attribute__((weak)) void led_init_ports(void) {}

__attribute__((weak)) void led_set(uint8_t usb_led) {
#if defined(BACKLIGHT_CAPS_LOCK) && defined(BACKLIGHT_ENABLE)
    // Use backlight as Caps Lock indicator
    uint8_t bl_toggle_lvl = 0;

    if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK) && !backlight_config.enable) {
        // Turning Caps Lock ON and backlight is disabled in config
        // Toggling backlight to the brightest level
        bl_toggle_lvl = BACKLIGHT_LEVELS;
    } else if (IS_LED_OFF(usb_led, USB_LED_CAPS_LOCK) && backlight_config.enable) {
        // Turning Caps Lock OFF and backlight is enabled in config
        // Toggling backlight and restoring config level
        bl_toggle_lvl = backlight_config.level;
    }

    // Set level without modify backlight_config to keep ability to restore state
    backlight_set(bl_toggle_lvl);
#endif

    led_set_kb(usb_led);
}

//------------------------------------------------------------------------------
// Override these functions in your keymap file to play different tunes on
// different events such as startup and bootloader jump

__attribute__((weak)) void startup_user() {}

__attribute__((weak)) void shutdown_user() {}

//------------------------------------------------------------------------------

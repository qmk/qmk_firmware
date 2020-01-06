/* Copyright 2019 Jack Humbert
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
#include "process_magic.h"

#ifdef AUDIO_ENABLE
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
float ag_norm_song[][2] = AG_NORM_SONG;
float ag_swap_song[][2] = AG_SWAP_SONG;
float cg_norm_song[][2] = CG_NORM_SONG;
float cg_swap_song[][2] = CG_SWAP_SONG;
#endif

/**
 * MAGIC actions (BOOTMAGIC without the boot)
 */
bool process_magic(uint16_t keycode, keyrecord_t *record) {
    // skip anything that isn't a keyup
    if (record->event.pressed) {
        switch (keycode) {
            case MAGIC_SWAP_CONTROL_CAPSLOCK ... MAGIC_TOGGLE_ALT_GUI:
            case MAGIC_SWAP_LCTL_LGUI ... MAGIC_TOGGLE_CTL_GUI:
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
                        clear_keyboard();  // clear first buffer to prevent stuck keys
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
                        clear_keyboard();  // clear first buffer to prevent stuck keys
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
                        clear_keyboard();  // clear first buffer to prevent stuck keys
                        keymap_config.nkro = !keymap_config.nkro;
                        break;
#if 0
                    case MAGIC_EE_HANDS_LEFT:
                        eeconfig_update_handedness(true);
                        break;
                    case MAGIC_EE_HANDS_RIGHT:
                        eeconfig_update_handedness(false);
                        break;
#endif
                }
                eeconfig_update_keymap(keymap_config.raw);
                clear_keyboard();  // clear to prevent stuck keys

                return false;
        }
    }

    // Not a magic keycode so continue processing
    return true;
}
